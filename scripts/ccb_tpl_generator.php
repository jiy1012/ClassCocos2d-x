#!/usr/bin/php -q
<?php
date_default_timezone_set('Asia/Shanghai');

// error_reporting(0);
error_reporting(E_ALL ^ E_NOTICE);

$output_dir = dirname(__FILE__);
$options = array();
if (!empty($_REQUEST)) {
    foreach ($_REQUEST as $key => $value) {
        $opt = ltrim($key, '-');
        $options[$opt] = $value;
    }
}
if (!empty($argv)) {
    $short_opts = 'c:f:o:h';
    $long_opts = array(
            'class',
            'file::',
            'output:',
    		'cell',
            'help');
    $options = getopt($short_opts,$long_opts);
}
// print_r($options);

if (isset($options['h']) || isset($options['help'])) {
   usage();
}

if (isset($options['output']) || isset($options['o'])) {
    $output_dir = $options['output'] ? $options['output'] : $options['o'];
    if (!is_dir($output_dir)) {
        echo "the output dir [$output_dir] is not a dirctory\n";
        exit(1);
    }
    if (is_writable($output_dir)) {
        echo "the output dir [$output_dir] is not writable\n";
        exit(1);
    }
}

$ccb_file = $options['file'] ? $options['file'] : $options['f'];
if (empty($ccb_file) || ! file_exists($ccb_file)) {
    usage();
}
$class_name = $options['c'] ? $options['c'] : $options['class'];
$is_table_cell_ccb = isset($options['cell']);

$generator = new CCBFileGenerator();
$generator->setOutputDir($output_dir);
if ($is_table_cell_ccb) {
	$generator->setBaseClassName('HFCellBase');
	$generator->setCcbFileType(CCBFileGenerator::CCB_TYPE_TABLE_CELL);
}
$generator->generate($ccb_file,$class_name);

function usage(){
    $file = basename(__FILE__);
    $help =  <<<HELP
Usage:
    $file --file=<ccb file name> [--output=<output dir> --class=<class name> --cell] 
        -f,--file      the input ccb file path
        -o,--output    the output dirctory for generated code files 
        -c,--class     the final class name for generated code 
    	--cell 		   the ccb file is type of table view cell
HELP;
    echo $help,PHP_EOL;
    exit(2);
}


class CCBFileGenerator{
    /**
      * @var CCBNodeParseResult
      */
    private $node_graph;
    private $file_name;
    private $ccbi_file_name;
    private $generator_version = 'v0.1.0';
    private $author_name = 'CCB Auto Generator';
    private $login_user = '';
    private $project_name = 'HappyFarm';
    private $class_prefix = 'HF';
    private $class_suffix = 'Base';
    private $data_member_prefix = 'm_';
    private $function_member_prefix = 'on';
    private $function_member_suffix = 'Click';
    
    private $output_dir = './';

    private $base_class = 'HFPopup';

    private $class_name;
    private $header_file;
    private $source_file;
    private $header_file_content = '';
    private $source_file_content = '';
    
    private $class_name_impl;
    private $header_file_impl;
    private $source_file_impl;
    private $header_file_content_impl = '';
    private $source_file_content_impl = '';

    private $ccb_type = self::CCB_TYPE_POPUP;

    /**
     *   @var CCBCodeTemplateProvider
    **/
    private $base_class_tpl_provider;
    /**
     *   @var CCBCodeTemplateProvider
    **/
    private $impl_class_tpl_provider;

    const CCB_TYPE_POPUP = 1;
    const CCB_TYPE_TABLE_CELL = 2;

    const DEFAULT_HEADER_FILE_EXT = '.h';
    const DEFAULT_SOURCE_FILE_EXT = '.cpp';
    const DEFAULT_CCBI_FILE_EXT = '.ccbi';
    const MEMBER_ASSIGN_TYPE_OWNER = 2;
    const HANDLER_TARGET_TYPE_OWNER = 2;
    
    public function generate($ccb_file, $class_name = ''){
        $this->setClassName($class_name);
        $this->init($ccb_file);
        $this->parseNodeGraph();
        // print_r($this->node_graph);
        if ($this->node_graph && !$this->node_graph->isEmpty()) {
            $this->generateCode();
            $this->writeFile();
        }
    }

    public function __set($name , $value ){
        if (property_exists($this,$name)) {
            $this->$name = $value;
        }
    }

    public function setCcbFileType($type){
        $this->ccb_type = $type;
        if ($this->ccb_type != self::CCB_TYPE_POPUP && $this->ccb_type != self::CCB_TYPE_TABLE_CELL) {
            $this->ccb_type = self::CCB_TYPE_POPUP;
        }
    }

    public function setBaseClassName($base_class){
        if (!empty($base_class)) {
            $this->base_class = $base_class;
        }
    }

    public function setClassName($class_name){
        if (empty($class_name)) {
            return;
        }
        $this->class_name_impl = ucwords(trim($class_name));
        if (!empty($this->class_name_impl)) {
            if (strncasecmp($this->class_name_impl, $this->class_prefix, strlen($this->class_prefix))) {
                $this->class_name_impl = $this->class_prefix . $this->class_name_impl;
            }
            $this->class_name = $this->class_name_impl . $this->class_suffix;
        }
        echo "generate class $this->class_name_impl and base class $this->class_name \n";
    }

    public function setOutputDir($output_dir){
        if (!is_dir($output_dir) ) {
            echo "Warning: set the output dir [$output_dir] is not a dirctory\n";
            return;
        }
        if (!is_writable($output_dir)) {
            echo "Warning: set the output dir [$output_dir] is not writable\n";
            return;
        }
        $this->output_dir = $output_dir;
        echo "output dir: $this->output_dir\n";
    }

    protected function generateCode(){
        $this->genCallfuncHandlers();
        $this->genMembers();
        $this->genControlHandlers();
        $this->genMenuHandlers();
    }

    protected function genCallfuncHandlers(){
        $handers = '';
        $this->implSourceCode('callfunc_assign',$handers);
    }

    protected function genMembers(){
        $member_list = $this->node_graph->getMemberList();
        $member_decl = '';
        $member_release = '';
        $member_assign = '';
        $member_init = '';
        
        $mem_list = $this->groupMemberByType($member_list);
        
        foreach ($mem_list as $member_type => $var_list) {
            sort($var_list);
            foreach ($var_list as $member_var) {
                $member_name = $this->getMemberName($member_var);
                $member_decl .= "\t${member_type}* $member_name;\n";
                if (empty($member_init)) {
                    $member_init = ":\n${member_name}(NULL)\n";
                }else{
                    $member_init .= ",$member_name(NULL)\n";
                }
                $member_release .= "\tCC_SAFE_RELEASE($member_name);\n";
                $member_assign .= "\tCCB_MEMBERVARIABLEASSIGNER_GLUE(this, \"$member_var\", $member_type*,this->$member_name);\n";
            }
        }
        $this->implHeaderCode('member_assign_decl',$member_decl);
        $this->implSourceCode('member_release',$member_release);
        $this->implSourceCode('member_assign',$member_assign);
        $this->implSourceCode('member_init',$member_init);
    }

    protected function groupMemberByType($member_list){
        $result = array();
        foreach ($member_list as $var_name => $type) {
            $result[$type][] = $var_name;
        }
        return $result;
    }

    protected function genControlHandlers(){
        $control_handlers = $this->node_graph->getControlHandlers();
        $control_decl = '';
        $control_assign = '';
        $control_impl_decl = '';
        $control_impl = '';
        sort($control_handlers);

        foreach ($control_handlers as $handler) {
            $event_name = $this->getHandlerName($handler);
            $control_decl .= "\tvirtual void $event_name(CCObject * pSender, CCControlEvent pCCControlEvent) = 0;\n";
            $control_assign .= "\tCCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, \"$handler\", {$this->class_name}::$event_name);\n";
            $control_impl_decl .= "\tvirtual void $event_name(CCObject * pSender, CCControlEvent pCCControlEvent);\n";
            $control_impl  .= "void {$this->class_name_impl}::$event_name(CCObject * pSender, CCControlEvent pCCControlEvent)\n{\n\t// TODO: auto generated code\n}\n\n";
        }
        $this->implHeaderCode('control_event_decl',$control_decl);
        $this->implSourceCode('control_handler_assign',$control_assign);
        $this->implHeaderImplCode('control_event_decl',$control_impl_decl);
        $this->implSourceImplCode('control_event_impl',$control_impl);
    }

    protected function genMenuHandlers(){
        $menu_handlers = $this->node_graph->getMenuHandlers();
        $menu_decl = '';
        $menu_assign = '';
        $menu_impl_decl = '';
        $menu_impl = '';
        foreach ($menu_handlers as $handler) {
            $event_name = $this->getHandlerName($handler);
            $menu_decl .= "\tvirtual void $event_name(CCObject * pSender) = 0;\n";
            $menu_assign .= "\tCCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, \"$handler\", {$this->class_name}::$event_name);\n";
            $menu_impl_decl .= "\tvirtual void $event_name(CCObject * pSender);\n";
            $menu_impl  .= "void {$this->class_name_impl}::$event_name(CCObject * pSender)\n{\n\t// TODO: auto generated code\n}\n\n";
        }
        $this->implHeaderCode('menu_event_decl',$menu_decl);
        $this->implSourceCode('menuhandler_assign',$menu_assign);
        $this->implHeaderImplCode('menu_handler_decl',$menu_impl_decl);
        $this->implSourceImplCode('menu_handler_impl',$menu_impl);
    }

    protected function implHeaderCode($segmen,$code){
        $this->header_file_content = str_replace("#$segmen#", $code, $this->header_file_content);
    }
    protected function implSourceCode($segmen,$code){
        $this->source_file_content = str_replace("#$segmen#", $code, $this->source_file_content);
    }
    protected function implHeaderImplCode($segmen,$code){
        $this->header_file_content_impl = str_replace("#$segmen#", $code, $this->header_file_content_impl);
    }
    protected function implSourceImplCode($segmen,$code){
        $this->source_file_content_impl = str_replace("#$segmen#", $code, $this->source_file_content_impl);
    }

    protected function getMemberName($name){
        if (strncasecmp($name, $this->data_member_prefix, strlen($this->data_member_prefix)) != 0) {
            return $this->data_member_prefix . $name;
        }
        return $name;
    }

    protected function getHandlerName($handler){
        $name = $handler;
        if (strncasecmp($name, $this->function_member_prefix, strlen($this->function_member_prefix)) != 0) {
            $name = $this->function_member_prefix . $handler;
        }
        if (stripos($name, $this->function_member_suffix) === false) {
            $name .= $this->function_member_suffix;
        }
        return $name;
    }

    protected function writeFile(){
        echo "write file $this->header_file\n";
        file_put_contents($this->output_dir . '/' . $this->header_file, $this->header_file_content . "\n");
        echo "write file $this->source_file\n";
        file_put_contents($this->output_dir . '/' . $this->source_file, $this->source_file_content . "\n");
        echo "write file $this->header_file_impl\n";
        file_put_contents($this->output_dir . '/' . $this->header_file_impl, $this->header_file_content_impl . "\n");
        echo "write file $this->source_file_impl\n";
        file_put_contents($this->output_dir . '/' . $this->source_file_impl, $this->source_file_content_impl . "\n");
    }

    protected function init($ccb_file){
        $this->file_name = $ccb_file;
        $this->ccbi_file_name = basename($ccb_file, '.ccb') . self::DEFAULT_CCBI_FILE_EXT;
        if (empty($this->class_name)) {
            $this->setClassName($this->getOutputClassName($ccb_file));
        }
        $this->login_user = get_current_user();
        
        $this->base_class_tpl_provider = new CCBClassBaseTemplateProvider();
        if ($this->ccb_type == self::CCB_TYPE_POPUP){
            $this->impl_class_tpl_provider = new CCBPopupImplTemplateProvider();
        }else{
            $this->impl_class_tpl_provider = new CCBTableCellImplTemplateProvider();
        }
        $this->header_file = $this->class_name . self::DEFAULT_HEADER_FILE_EXT;
        $this->source_file = $this->class_name . self::DEFAULT_SOURCE_FILE_EXT;
        $this->header_file_content = $this->getHeaderFileTpl();
        $this->source_file_content = $this->getSourceFileTpl();

        $this->header_file_impl = $this->class_name_impl . self::DEFAULT_HEADER_FILE_EXT;
        $this->source_file_impl = $this->class_name_impl . self::DEFAULT_SOURCE_FILE_EXT;
        $this->header_file_content_impl = $this->getHeaderFileImplTpl();
        $this->source_file_content_impl = $this->getSourceFileImplTpl();
    }

    protected function getHeaderFileImplTpl(){
        $create_date = date('Y-m-d H:i:s');
        $tpl = $this->impl_class_tpl_provider->getHeaderFileTemplate();
        $replace_pairs = array(
                        '#header_file_name#' => $this->header_file_impl,
                        '#project_name#' => $this->project_name,
                        '#author#' => $this->login_user,
                        '#create_date#' => $create_date,
                        '#class_name#' => $this->class_name_impl,
                        '#base_class#' => $this->class_name,
                        '#base_class_header_file#' => $this->header_file,
                        );
        
        $result = strtr($tpl,$replace_pairs);
        return $result;
    }

    protected function getSourceFileImplTpl(){
        $create_date = date('Y-m-d H:i:s');
        $tpl = $this->impl_class_tpl_provider->getSourceFileTemplate();
        $replace_pairs = array(
                        '#header_file_name#' => $this->header_file_impl,
                        '#project_name#' => $this->project_name,
                        '#author#' => $this->login_user,
                        '#create_date#' => $create_date,
                        '#class_name#' => $this->class_name_impl,
                        '#source_file_name#' => $this->source_file_impl,
                        '#ccbi_file_name#' => $this->ccbi_file_name,
        				'#base_class#' => $this->base_class,
                        );
        
        $result = strtr($tpl,$replace_pairs);
        return $result;
    }

    protected function getHeaderFileTpl(){
        $create_date = date('Y-m-d H:i:s');
        $tpl = $this->base_class_tpl_provider->getHeaderFileTemplate();
        $replace_pairs = array(
                        '#header_file_name#' => $this->header_file,
                        '#project_name#' => $this->project_name,
                        '#author#' => $this->login_user,
                        '#create_date#' => $create_date,
                        '#class_name#' => $this->class_name,
                        '#base_class#' => $this->base_class,
                        );
        
        $result = strtr($tpl,$replace_pairs);
        return $result;
    }

    protected function getSourceFileTpl(){
        $create_date = date('Y-m-d H:i:s');
        $tpl = $this->base_class_tpl_provider->getSourceFileTemplate();
        $replace_pairs = array(
                        '#header_file_name#' => $this->header_file,
                        '#project_name#' => $this->project_name,
                        '#author#' => $this->login_user,
                        '#create_date#' => $create_date,
                        '#class_name#' => $this->class_name,
                        '#source_file_name#' => $this->source_file,
                        );
        
        $result = strtr($tpl,$replace_pairs);
        return $result;
    }

    protected function parseNodeGraph(){
        $result = parse_plist($this->file_name);
        $node_graph = $result['nodeGraph'];
        $this->node_graph = new CCBNodeParseResult();
        $this->parseNode($node_graph );
    }

    protected function parseNode($node){
        if (empty($node)) {
            return;
        }
        // print_r($node);
        $type = $node['baseClass'];
        if (!empty($node['customClass'])) {
            $type = $node['customClass'];
        }
        if (!empty($node['memberVarAssignmentName']) && $node['memberVarAssignmentType'] == self::MEMBER_ASSIGN_TYPE_OWNER) {
            $var_name = $node['memberVarAssignmentName'];
            $this->node_graph->addMember($var_name,$type);
        }
        foreach ($node['properties'] as $property) {
            if ($property['name'] == 'ccControl' && $type == 'CCControlButton' && $property['value'][1] == self::HANDLER_TARGET_TYPE_OWNER) {
                $this->node_graph->addControlHandler($property['value'][0]);
                break;
            }
            if ($property['name'] == 'block' && $type == 'CCMenuItemImage' && $property['value'][1] == self::HANDLER_TARGET_TYPE_OWNER) {
                $this->node_graph->addMenuHandler($property['value'][0]);
                break;
            }
        }
        
        if (!empty($node['children'])) {
            foreach ($node['children'] as $value) {
                $this->parseNode($value);
            }
        }
    }

    protected function getOutputClassName($ccb_file_name){
        $basename = basename($ccb_file_name , '.ccb');
        return $basename;
    }

}

interface CCBCodeTemplateProvider{
    public function getHeaderFileTemplate();
    public function getSourceFileTemplate();
}

class CCBClassBaseTemplateProvider{
    public function getHeaderFileTemplate(){
        $tpl = <<<TPL
//
//  #header_file_name#
//  #project_name#
//
//  Created by #author#  on #create_date#.
//
//  DON'T MODIFY THIS FILE!
//

#ifndef __#project_name#__#class_name#__
#define __#project_name#__#class_name#__

#include "HFCommon.h"
#include "#base_class#.h"

NS_HF_BEGIN

class #class_name# : public #base_class#
{
public:
    #class_name#();
    virtual ~#class_name#();

public:
    bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName);

protected:
#control_event_decl#
#menu_event_decl#
protected:
#member_assign_decl#};
NS_HF_END

#endif /* defined(__#project_name#__#class_name#__) */

TPL;
    return $tpl;
    }

    public function getSourceFileTemplate(){
        $tpl = <<<TPL
//
//  #source_file_name#
//  #project_name#
//
//  Created by Created by #author#  on #create_date#.
//
//  DON'T MODIFY THIS FILE!
//

#include "#header_file_name#"

NS_HF_BEGIN

#class_name#::#class_name#()#member_init#{
}

#class_name#::~#class_name#()
{
#member_release#}

SEL_CCControlHandler #class_name#::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName)
{
#control_handler_assign#    return NULL;
}

SEL_MenuHandler #class_name#::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
#menuhandler_assign#    return NULL;
}

SEL_CallFuncN #class_name#::onResolveCCBCCCallFuncSelector(CCObject * pTarget, const char* pSelectorName)
{
#callfunc_assign#    return NULL;
}

bool #class_name#::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
#member_assign#    return false;
}
NS_HF_END

TPL;
        return $tpl;
    }
}



class CCBPopupImplTemplateProvider{
	
	protected function getHeaderFileFrameTpl(){
		$tpl = <<<TPL
//
//  #header_file_name#
//  #project_name#
//
//  Created by #author# on #create_date#.
//
//
		
#ifndef __#project_name#__#class_name#__
#define __#project_name#__#class_name#__
		
#include "HFCommon.h"
#include "#base_class_header_file#"
		
NS_HF_BEGIN
		
class #class_name# : public #base_class#
{
public:
    #class_name#();
    virtual ~#class_name#();
#class_body#
protected:
#control_event_decl#
#menu_handler_decl#};
NS_HF_END
		
#endif /* defined(__#project_name#__#class_name#__) */
		
TPL;
		return $tpl;
	}
	
	protected function getHeaderClassBody(){
		$class_body = <<<BODY
    virtual void initialize();
    virtual void onActive();
    CREATE_STATIC_DECL(#class_name#);
		
protected:
    virtual void purgePopup();
		
BODY;
		return $class_body;
	}

    public function getHeaderFileTemplate(){
        $tpl = $this->getHeaderFileFrameTpl();
        $class_body = $this->getHeaderClassBody();
        $result = strtr($tpl, array( '#class_body#' => $class_body));
        return $result;
    }
    
    public function getSourceFileTemplate(){
        $tpl = <<<TPL
//
//  #source_file_name#
//  #project_name#
//
//  Created by #author# on #create_date#.
//
//

#include "#header_file_name#"


NS_HF_BEGIN
    		
#class_body#
		
#control_event_impl#
#menu_handler_impl#

NS_HF_END

TPL;
        $class_body = $this->getSourceClassBody();
        $result = strtr($tpl, array( '#class_body#' => $class_body));
        return $result;
    }
    
    protected function getSourceClassBody(){
    	$tpl = <<<TPL
CREATE_STATIC_POPUP(#class_name#);
PURGE_STATIC_POPUP(#class_name#);

#class_name#::#class_name#()
{
    setCCBFileName("#ccbi_file_name#");
    __CLASS_SET__
}

#class_name#::~#class_name#()
{

}

void #class_name#::initialize()
{

}

void #class_name#::onActive()
{

}
TPL;
    	return $tpl;
    }
}


class CCBTableCellImplTemplateProvider extends CCBPopupImplTemplateProvider{
	protected function getHeaderClassBody(){
		$tpl = <<<TPL
    virtual bool init();
    CREATE_FUNC(#class_name#);
	virtual void drawCell(const int idx);
TPL;
		return $tpl;
	}
	protected function getSourceClassBody(){
		$tpl = <<<TPL
#class_name#::#class_name#()
{
    // TODO: auto generated code
}

#class_name#::~#class_name#()
{
    // TODO: auto generated code
}

bool #class_name#::init()
{
    bool bRet = false;
    do
    {
    	CC_BREAK_IF(! #base_class#::init());
		readCcbiFile("#ccbi_file_name#");
    	// TODO: auto generated code

    	bRet = true;
    } while (0);
	return bRet;
}

void #class_name#::drawCell(const int idx)
{
    // TODO: auto generated code
}
TPL;
		return $tpl;
	}
}

class CCBNodeParseResult{
    private $control_handlers = array();
    private $callfunc_handlers = array();
    private $member_list = array();
    private $menu_handlers = array();
    public function getMemberList(){
        return $this->member_list;
    }
    public function getMenuHandlers(){
        return $this->menu_handlers;
    }
    public function getControlHandlers(){
        return $this->control_handlers;
    }
    public function getCallfunHandlers(){
        return $this->callfunc_handlers;
    }
    public function addMember($name,$type){
        $this->member_list[$name] = $type;
    }
    public function addControlHandler($handler_name){
        $this->control_handlers[] = $handler_name;
    }

    public function addMenuHandler($handler_name){
        $this->menu_handlers[] = $handler_name;
    }

    public function addCallfuncHandler($handler_name){
        $this->callfunc_handlers[] = $handler_name;
    }
    public function isEmpty(){
        return empty($this->control_handlers) && empty($this->member_list) && 
        empty($this->callfunc_handlers) && empty($this->menu_handlers);
    }
}

class CCBFolderGenerator{
    public function generate($ccb_folder_path){
        if (!is_dir($ccb_folder_path)) {
            exit(1);
        }
        $file_list = glob("$ccb_folder_path/*.ccb");
        if (empty($file_list)) {
            exit(0);
        }
        $generator = new CCBFileGenerator();
        foreach ($file_list as  $ccb_file) {
            $generator->generate($ccb_file);
        }
    }
}


function parse_value( $valueNode ) {
  $valueType = $valueNode->nodeName;

  $transformerName = "parse_$valueType";

  if ( is_callable($transformerName) ) {
    // there is a transformer function for this node type
    return call_user_func($transformerName, $valueNode);
  }

  // if no transformer was found
  return null;
}

function parse_integer( $integerNode ) {
  return $integerNode->textContent;
}

function parse_string( $stringNode ) {
  return $stringNode->textContent;  
}

function parse_date( $dateNode ) {
  return $dateNode->textContent;
}

function parse_true( $trueNode ) {
  return true;
}

function parse_false( $trueNode ) {
  return false;
}

function parse_dict( $dictNode ) {
  $dict = array();

  // for each child of this node
  for (
    $node = $dictNode->firstChild;
    $node != null;
    $node = $node->nextSibling
  ) {
    if ( $node->nodeName == "key" ) {
      $key = $node->textContent;

      $valueNode = $node->nextSibling;

      // skip text nodes
      while ( $valueNode->nodeType == XML_TEXT_NODE ) {
        $valueNode = $valueNode->nextSibling;
      }

      // recursively parse the children
      $value = parse_value($valueNode);

      $dict[$key] = $value;
    }
  }

  return $dict;
}

function parse_array( $arrayNode ) {
  $array = array();

  for (
    $node = $arrayNode->firstChild;
    $node != null;
    $node = $node->nextSibling
  ) {
    if ( $node->nodeType == XML_ELEMENT_NODE ) {
      array_push($array, parse_value($node));
    }
  }

  return $array;
}

function parse_plist($file_name) {
    $document = new DOMDocument();
    $document->load($file_name);
    $plistNode = $document->documentElement;

    $root = $plistNode->firstChild;
    // skip any text nodes before the first value node
    while ( $root->nodeName == "#text" ) {
        $root = $root->nextSibling;
    }

    return parse_value($root);
}