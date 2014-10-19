#
# Copyright (C) 2014 The Android Open Source Project
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

LOCAL_PATH:= $(call my-dir)

lsan_src_files := \
    lsan_allocator.cc \
    lsan.cc \
    lsan_common.cc \
    lsan_common_linux.cc \
    lsan_interceptors.cc \
    lsan_preinit.cc \
    lsan_thread.cc \

lsan_c_includes := \
    external/compiler-rt/lib \
    external/compiler-rt/include \

lsan_cflags := -Wno-unused-parameter

ifeq ($(TARGET_ARCH),x86_64)
include $(CLEAR_VARS)
LOCAL_MODULE := liblsan
LOCAL_MODULE_TAGS := optional
LOCAL_C_INCLUDES := $(lsan_c_includes)
LOCAL_CFLAGS := $(lsan_cflags)
LOCAL_SRC_FILES := $(lsan_src_files)
LOCAL_CPP_EXTENSION := .cc
LOCAL_CLANG := true
LOCAL_ADDITIONAL_DEPENDENCIES := $(LOCAL_PATH)/Android.mk
include $(BUILD_STATIC_LIBRARY)
endif

include $(CLEAR_VARS)
LOCAL_MODULE := liblsan
LOCAL_MODULE_TAGS := optional
LOCAL_C_INCLUDES := $(lsan_c_includes)
LOCAL_CFLAGS := $(lsan_cflags)
LOCAL_SRC_FILES := $(lsan_src_files)
LOCAL_CPP_EXTENSION := .cc
LOCAL_CLANG := true
LOCAL_ADDITIONAL_DEPENDENCIES := $(LOCAL_PATH)/Android.mk
include $(BUILD_HOST_STATIC_LIBRARY)
