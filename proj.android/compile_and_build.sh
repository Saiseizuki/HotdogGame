#!/bin/bash

./build_native.sh
NDK_BUILD_STATUS=$?
if [ $NDK_BUILD_STATUS -eq 0 ]
then
	ant debug
	ANT_BUILD_STATUS=$?
	if [ $ANT_BUILD_STATUS -eq $? ]
		then
        		cd ..
        		PROJECT_NAME=${PWD##*/}
        		cd proj.android
       			adb -d install -r ./bin/$PROJECT_NAME-debug.apk
        		echo "Build and install succeeded."
		fi
fi
