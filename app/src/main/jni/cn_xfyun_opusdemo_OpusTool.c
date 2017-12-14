#include <jni.h>
#include "cn_xfyun_opusdemo_OpusTool.h"
#include "opus_tool.h"

#define DATA_SIZE 1024 * 1024 * 4

JNIEXPORT jstring JNICALL Java_cn_xfyun_opusdemo_OpusTool_nativeGetString(JNIEnv *env, jobject obj){
    return (*env)->NewStringUTF(env, "Hello Opus");
}

JNIEXPORT jbyteArray JNICALL Java_cn_xfyun_opusdemo_OpusTool_encode_1data(JNIEnv *env, jobject obj, jbyteArray in, jint len){
    jbyte* in_data = (*env)->GetByteArrayElements(env, in, NULL);
    unsigned char *out = (unsigned char*) malloc(DATA_SIZE);
    memset(out, 0, DATA_SIZE);
    int out_len = 0;
    //jbyte* out_data = (*env)->GetByteArrayElements(env, opus, NULL);
    encode(in_data, len, out, &out_len);

    jbyte *by = (jbyte*)out;
    jbyteArray jarrRV =(*env)->NewByteArray(env,out_len);
    (*env)->SetByteArrayRegion(env,jarrRV, 0,out_len,by);

    return jarrRV;
}

JNIEXPORT jbyteArray JNICALL Java_cn_xfyun_opusdemo_OpusTool_decode_1data(JNIEnv *env, jobject obj, jbyteArray in, jint len){
    jbyte* in_data = (*env)->GetByteArrayElements(env, in, NULL);
    short *out = (short *) malloc(DATA_SIZE);
    memset(out, 0, DATA_SIZE);
    int out_len = 0;
    //jbyte* out_data = (*env)->GetByteArrayElements(env, opus, NULL);
    decode(in_data, len, (short *)out, &out_len);

    jbyte *by = (jbyte*)out;
    jbyteArray jarrRV =(*env)->NewByteArray(env,out_len);
    (*env)->SetByteArrayRegion(env,jarrRV, 0,out_len,by);

    return jarrRV;
}