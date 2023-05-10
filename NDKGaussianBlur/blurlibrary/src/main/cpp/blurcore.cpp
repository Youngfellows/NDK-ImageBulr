//
// Created by Administrator on 2016/4/12.
//

#include <cmath>
#include <cstdlib>
#include <cstdint>

#include "joe_com_blurlibrary_BlurCore.h"
#include "android/log.h"
#include "android/bitmap.h"

#define  LOG_TAG    "JNILog"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

void boxBlurV(uint32_t *scl, uint32_t *tcl, int w, int h, int r) {
    int j = 0;
    for (j = 0; j < w; ++j) {
        uint32_t totalr = 0;
        uint32_t totalg = 0;
        uint32_t totalb = 0;
        // Process entire window for first pixel
        for (int kx = -r; kx <= r; ++kx) {
            if (kx < 0) {
                totalr += (scl[j] & 0x00FF0000) >> 16;
                totalg += (scl[j] & 0x0000FF00) >> 8;
                totalb += (scl[j] & 0x000000FF) >> 0;
            } else {
                totalr = totalr + ((scl[kx * w + j] & 0x00FF0000) >> 16);
                totalg = totalg + ((scl[kx * w + j] & 0x0000FF00) >> 8);
                totalb = totalb + ((scl[kx * w + j] & 0x000000FF) >> 0);
            }
        }
        tcl[j] = (scl[j] & 0xFF000000) |
                 ((totalr / (2 * r + 1)) << 16) |
                 ((totalg / (2 * r + 1)) << 8) |
                 ((totalb / (2 * r + 1)) << 0);
        // Subsequent pixels just update window total
        for (int i = 1; i < h; ++i) {
            // Subtract pixel leaving window
            if (i - r < 0) {
                totalr -= (scl[j] & 0x00FF0000) >> 16;
                totalg -= (scl[j] & 0x0000FF00) >> 8;
                totalb -= (scl[j] & 0x000000FF) >> 0;
            } else {
                totalr -= (scl[j + (i - r) * w] & 0x00FF0000) >> 16;
                totalg -= (scl[j + (i - r) * w] & 0x0000FF00) >> 8;
                totalb -= (scl[j + (i - r) * w] & 0x000000FF) >> 0;
            }

            // Add pixel entering window
            if (i + r >= h) {
                totalr += (scl[j + (h - 1) * w] & 0x00FF0000) >> 16;
                totalg += (scl[j + (h - 1) * w] & 0x0000FF00) >> 8;
                totalb += (scl[j + (h - 1) * w] & 0x000000FF) >> 0;
            } else {
                totalr += (scl[j + (i + r) * w] & 0x00FF0000) >> 16;
                totalg += (scl[j + (i + r) * w] & 0x0000FF00) >> 8;
                totalb += (scl[j + (i + r) * w] & 0x000000FF) >> 0;
            }

            tcl[i * w + j] = (scl[i * w + j] & 0xFF000000) |
                             ((totalr / (r * 2 + 1)) << 16) |
                             ((totalg / (r * 2 + 1)) << 8) |
                             ((totalb / (r * 2 + 1)) << 0);
        }
    }
}

void boxBlurH(uint32_t *scl, uint32_t *tcl, int w, int h, int r) {
    int i = 0;
    for (i = 0; i < h; ++i) {
        uint32_t totalr = 0;
        uint32_t totalg = 0;
        uint32_t totalb = 0;
        // Process entire window for first pixel
        for (int kx = -r; kx <= r; ++kx) {
            if (kx < 0) {
                totalr += (scl[w * i] & 0x00FF0000) >> 16;
                totalg += (scl[w * i] & 0x0000FF00) >> 8;
                totalb += (scl[w * i] & 0x000000FF) >> 0;
            } else {
                totalr = totalr + ((scl[kx + w * i] & 0x00FF0000) >> 16);
                totalg = totalg + ((scl[kx + w * i] & 0x0000FF00) >> 8);
                totalb = totalb + ((scl[kx + w * i] & 0x000000FF) >> 0);
            }
        }
        tcl[0 + w * i] = (scl[0 + w * i] & 0xFF000000) |
                         ((totalr / (r * 2 + 1)) << 16) |
                         ((totalg / (r * 2 + 1)) << 8) |
                         ((totalb / (r * 2 + 1)) << 0);
        // Subsequent pixels just update window total
        for (int j = 1; j < w; ++j) {
            // Subtract pixel leaving window
            if (j - r < 0) {
                totalr -= (scl[w * i] & 0x00FF0000) >> 16;
                totalg -= (scl[w * i] & 0x0000FF00) >> 8;
                totalb -= (scl[w * i] & 0x000000FF) >> 0;
            } else {
                totalr -=((scl[w * i + j - r] & 0x00FF0000) >> 16);
                totalg -=((scl[w * i + j - r] & 0x0000FF00) >> 8);
                totalb -=((scl[w * i + j - r] & 0x000000FF) >> 0);
            }

            // Add pixel entering window
            if (j + r >= w) {
                totalr += (scl[w * i + w - 1] & 0x00FF0000) >> 16;
                totalg += (scl[w * i + w - 1] & 0x0000FF00) >> 8;
                totalb += (scl[w * i + w - 1] & 0x000000FF) >> 0;
            } else {
                totalr +=(scl[w * i + j + r] & 0x00FF0000) >> 16;
                totalg +=(scl[w * i + j + r] & 0x0000FF00) >> 8;
                totalb +=(scl[w * i + j + r] & 0x000000FF) >> 0;
            }

            tcl[j + w * i] = (scl[j + w * i] & 0xFF000000) |
                             ((totalr / (r * 2 + 1)) << 16) |
                             ((totalg / (r * 2 + 1)) << 8) |
                             ((totalb / (r * 2 + 1)) << 0);
        }
    }
}

void boxBlur(void *pixels, uint32_t *temp, int width, int height, int radius) {
    boxBlurH((uint32_t *) pixels, temp, width, height, radius);
    boxBlurV(temp, (uint32_t *) pixels, width, height, radius);
}

int *boxesForGauss(double sigma, int n) {
    double wIdeal = sqrt((12 * sigma * sigma / n) + 1);  // Ideal averaging filter width
    int wl = floor(wIdeal);
    if (wl % 2 == 0) wl--;
    int wu = wl + 2;

    double mIdeal = (12 * sigma * sigma - n * wl * wl - 4 * n * wl - 3 * n) / (-4 * wl - 4);
    int m = round(mIdeal);

    int *sizes = (int *) malloc(sizeof(int) * 3);
    for (int i = 0; i < n; i++) {
        sizes[i] = (i < m ? wl : wu);
    }
    return sizes;
}

void gaussBlur(void *pixels, int width, int height, int radius) {
    double sigma = 1.0 * radius;
    int *bxs = boxesForGauss(sigma, 3);
    uint32_t *temp = (uint32_t *) malloc(sizeof(uint32_t) * width * height);
    boxBlur(pixels, temp, width, height, (bxs[0] - 1) / 2);
    boxBlur(pixels, temp, width, height, (bxs[1] - 1) / 2);
    boxBlur(pixels, temp, width, height, (bxs[2] - 1) / 2);
}

JNIEXPORT jint

JNICALL Java_joe_com_blurlibrary_BlurCore_blurBitmap
        (JNIEnv *env, jclass thiz, jobject bitmap, jint radius) {
    AndroidBitmapInfo info;
    int ret;
    void *pixels;
    if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0) {
        LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
        return 0;
    }
    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGE("Bitmap format is not RGBA_8888 !");
        return 0;
    }
    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &pixels)) < 0) {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
        return 0;
    }
    gaussBlur(pixels, info.width, info.height, radius);
    return 1;
}