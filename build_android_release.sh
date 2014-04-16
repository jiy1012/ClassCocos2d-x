#!/bin/bash

cur_dir=`cd "$(dirname ${BASH_SOURCE[0]})" && pwd`
#echo "enter dir $cur_dir"
cd $cur_dir
SYS_TYPE=`uname -s`
#echo ${SYS_TYPE:0:6}

if [ $SYS_TYPE = "Linux" ]; then

export ANT_HOME=/usr/local/apache-ant-1.9.2
export JAVA_HOME=/usr/java/latest
export COCOS2DX_ROOT=/data/tools/cocos2d-x-2.1.4
export NDK_ROOT=/data/tools/android-ndk-r8e
export ANDROID_SDK_ROOT=/data/tools/android-sdk-linux
export ANDROID_HOME=$ANDROID_SDK_ROOT
export ANDROID_NDK_ROOT=$NDK_ROOT
export PATH=$PATH:$ANDROID_NDK_ROOT:$ANDROID_SDK_ROOT
ANT="/usr/local/sbin/ant"

elif [ $SYS_TYPE = "Darwin" ]; then
	ANT=`which ant`

elif [ ${SYS_TYPE:0:6} = "CYGWIN" ]; then
	export NDK_ROOT="i:/android/android-ndk-r8e"
	ANT="ant"

fi


cd $cur_dir/ClassCocos2d-x/proj.android
# sh build_native.sh
if [ $? -eq 0 ]; then
	echo "build native lib success"
	echo "start to use ant to package the apk for android"
	$ANT release
else
	echo "build native lib fail"
	exit 1
fi

