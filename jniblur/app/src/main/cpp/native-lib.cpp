#include <jni.h>
#include <string>
#include <android/bitmap.h>
#include "blur.h"
#include <android/log.h>
#include "Java_com_example_myjnibitmap_BlurBitmap.h"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,"bmp",__VA_ARGS__)


#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
Java_com_example_myjnibitmap_BlurBitmap_blurBitmap(JNIEnv *env, jobject thiz, jobject bmp,
                                                   jint radius) {
    LOGD("DD1");
    AndroidBitmapInfo bmpInfo;
    //第一步AndroidBitmap_getInfo 获取bitmap信息
    int res = AndroidBitmap_getInfo(env, bmp, &bmpInfo);
    if (res != ANDROID_BITMAP_RESULT_SUCCESS) { return; }
    if (bmpInfo.format != ANDROID_BITMAP_FORMAT_RGBA_8888 &&
        bmpInfo.format != ANDROID_BITMAP_FORMAT_RGB_565) {
        //只支持8888和565格式
        return;
    }

    LOGD("DD2");
    //第二步上锁,获取rgb像素数据
    void *pixels;
    res = AndroidBitmap_lockPixels(env, bmp, &pixels);
    LOGD("DD3");
    if (res != ANDROID_BITMAP_RESULT_SUCCESS) { return; }
    //第三步数据处理（各种算法处理像素数据）
    uint32_t h = bmpInfo.height;//获取高度
    uint32_t w = bmpInfo.width;//获取宽度
    uint32_t format = bmpInfo.format;//图片格式
    uint32_t stride = bmpInfo.stride;//图片每一行占用字节数
    LOGD("DD4");
    LOGD("%ld:: w:%d,h:%d,format:%d,stride:%d", __LINE__, w, h, format, stride);
    if (bmpInfo.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        // 调用stackblur.c中的blur_ARGB_8888()或blur_RGB_565()
        pixels = blur_ARGB_8888((int *) pixels, w, h, radius);
    } else if (bmpInfo.format == ANDROID_BITMAP_FORMAT_RGB_565) {
        pixels = blur_RGB_565((short *) pixels, w, h, radius);
    }
    LOGD("DD5");
    //第四步解锁
    AndroidBitmap_unlockPixels(env, bmp);
}

#ifdef __cplusplus
}
#endif