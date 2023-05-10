LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := myBlur
LOCAL_SRC_FILES := myBlur.cpp
LOCAL_LDLIBS += -lc -lm -llog
include $(BUILD_SHARED_LIBRARY)