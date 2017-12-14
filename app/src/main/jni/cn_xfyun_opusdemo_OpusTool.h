#include <jni.h>
#include "opus_tool.h"
#ifndef _Included_cn_xfyun_opusdemo_OpusTool
#define _Included_cn_xfyun_opusdemo_OpusTool
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL Java_cn_xfyun_opusdemo_OpusTool_nativeGetString
        (JNIEnv *, jobject);

JNIEXPORT jint JNICALL Java_cn_xfyun_opusdemo_encode_1wav_1file
        (JNIEnv *, jobject, jstring, jstring);

JNIEXPORT jint JNICALL Java_cn_xfyun_opusdemo_decode_1opus_1file
        (JNIEnv *, jobject, jstring, jstring);

#ifdef __cplusplus
}
#endif
#endif