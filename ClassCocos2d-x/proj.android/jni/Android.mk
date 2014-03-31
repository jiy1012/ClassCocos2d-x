LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

define all-cpp-files
$(patsubst jni/%,%, $(shell find $(LOCAL_PATH)/../../Classes/ $(LOCAL_PATH)/ -name "*.cpp"))  
endef

define all-cpp-dir
	$(patsubst jni/%,$(LOCAL_PATH)/%, $(shell find $(LOCAL_PATH)/../../Classes/ -type d -not -wholename '*.svn*'))  
endef

LOCAL_SRC_FILES := $(call all-cpp-files)

LOCAL_C_INCLUDES := $(call all-cpp-dir)

#$(info $(LOCAL_SRC_FILES))
#$(info $(LOCAL_C_INCLUDES))
#include $(LOCAL_PATH)/Sources.mk
#include $(LOCAL_PATH)/Includes.mk

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
