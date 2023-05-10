//
// Created by Administrator on 2017/11/7 0007.
//
#include <jni.h>

#ifndef KELADEMO_HELLO_JNI_H
#define KELADEMO_HELLO_JNI_H

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_kela_gausspicture_ndk_Codec_initCBlur1(JNIEnv *env,
                                                                       jobject obj,
                                                                       jintArray pix,
                                                                       jint w,
                                                                       jint h, jint r);

JNIEXPORT void JNICALL Java_com_kela_gausspicture_ndk_Codec_initCBlur2(JNIEnv *env,
                                                                       jobject obj,
                                                                       jintArray pix,
                                                                       jint w,
                                                                       jint h,
                                                                       jint r);

#ifdef __cplusplus
}
#endif
#endif //KELADEMO_HELLO_JNI_H
