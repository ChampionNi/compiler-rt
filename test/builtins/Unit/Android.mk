#
# Copyright (C) 2012 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := aeabi_drsub_test
LOCAL_CFLAGS_arm += -D__ARM_EABI
LOCAL_SRC_FILES_arm := arm/aeabi_drsub_test.c
LOCAL_CLANG := true
LOCAL_MODULE_TARGET_ARCH := arm
LOCAL_CXX_STL := none
LOCAL_NO_LIBGCC := true
LOCAL_WHOLE_STATIC_LIBRARIES := libcompiler_rt
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_MODULE := aeabi_frsub_test
LOCAL_CFLAGS_arm += -D__ARM_EABI
LOCAL_SRC_FILES_arm := arm/aeabi_frsub_test.c
LOCAL_CLANG := true
LOCAL_MODULE_TARGET_ARCH := arm
LOCAL_CXX_STL := none
LOCAL_NO_LIBGCC := true
LOCAL_WHOLE_STATIC_LIBRARIES := libcompiler_rt
include $(BUILD_EXECUTABLE)
