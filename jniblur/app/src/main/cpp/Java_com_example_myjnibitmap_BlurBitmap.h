//
// Created by F2847881 on 2023/5/10.
//
#include <jni.h>

#ifndef MYJNIBITMAP_JAVA_COM_EXAMPLE_MYJNIBITMAP_BLURBITMAP_H
#define MYJNIBITMAP_JAVA_COM_EXAMPLE_MYJNIBITMAP_BLURBITMAP_H

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
Java_com_example_myjnibitmap_BlurBitmap_blurBitmap(JNIEnv *env, jobject thiz, jobject bmp,
                                                   jint radius);

#ifdef __cplusplus
}
#endif

#endif //MYJNIBITMAP_JAVA_COM_EXAMPLE_MYJNIBITMAP_BLURBITMAP_H
