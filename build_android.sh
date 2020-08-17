#!/usr/bin/env sh
export ANDROID_NDK_ROOT=/workspace/android-ndk/android-ndk-r20
NDK_BUILD=${ANDROID_NDK_ROOT}/ndk-build

ROOT_DIR=$(pwd)
SRCS=$(pwd)
BUILD_DIR=$(pwd)/build

build_rilc()
{
    mkdir -p ${BUILD_DIR}/rilc
    cd ${BUILD_DIR}/rilc
	${NDK_BUILD} V=0 NDK_APPLICATION_MK=${SRCS}/Application.mk APP_BUILD_SCRIPT=${SRCS}/Android.mk NDK_PROJECT_PATH=`pwd` NDK_DEBUG=0 APP_ABI=${ANDROID_TARGET_PLATFORM}
    cd -
}

rm -rf ${BUILD_DIR}
mkdir -p ${BUILD_DIR}

for ANDROID_TARGET_PLATFORM in armeabi-v7a #arm64-v8a
do
    build_rilc
	if [ $? -ne 0 ]; then
		echo "Error executing: build_rilc"
		exit 1
	fi
done

echo "Find target in dir ${BUILD_DIR}/rilc/"