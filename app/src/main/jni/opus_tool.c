#include "opus_tool.h"
#include<android/log.h>

#define SAMPLE_RATE 16000
#define CHANNEL_NUM 1
#define BIT_RATE 16000
#define BIT_PER_SAMPLE 16
#define WB_FRAME_SIZE 320
#define DATA_SIZE 1024 * 1024 * 4

#define TAG "Opus_Log"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型

int encode(char* in, int len, unsigned char* opus, int* opus_len) {
    int err = 0;
    opus_int32 skip = 0;

    OpusEncoder *enc = opus_encoder_create(SAMPLE_RATE, CHANNEL_NUM,
                                           OPUS_APPLICATION_VOIP, &err);
    if (err != OPUS_OK) {
        fprintf(stderr, "cannnot create opus encoder: %s\n",
                opus_strerror(err));
        enc = NULL;
        return -1;
    }

    opus_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_BANDWIDTH_WIDEBAND));
    opus_encoder_ctl(enc, OPUS_SET_BITRATE(BIT_RATE));
    opus_encoder_ctl(enc, OPUS_SET_VBR(1));
    opus_encoder_ctl(enc, OPUS_SET_COMPLEXITY(10));
    opus_encoder_ctl(enc, OPUS_SET_INBAND_FEC(0));
    opus_encoder_ctl(enc, OPUS_SET_FORCE_CHANNELS(OPUS_AUTO));
    opus_encoder_ctl(enc, OPUS_SET_DTX(0));
    opus_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(0));
    opus_encoder_ctl(enc, OPUS_GET_LOOKAHEAD(&skip));
    opus_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(16));

    short frame_size = WB_FRAME_SIZE;
    int frame_bytes = (frame_size << 1);

    opus_int16 *frame = (opus_int16 *) in;
    unsigned char *cbits = opus;

    while (len > frame_bytes) {
        int nbytes = opus_encode(enc, frame, frame_size, cbits + sizeof(char),
                                 640 - sizeof(short));
        if (nbytes > frame_size * 2 || nbytes < 0) {
            return -1;
        }
        cbits[0] = nbytes;
        frame += WB_FRAME_SIZE;
        cbits += nbytes + sizeof(char);
        len -= frame_bytes;
        *opus_len += nbytes + sizeof(char);
    }
    opus_encoder_destroy(enc);
    return 0;
}

int decode(unsigned char* in, int len, short* out, int* out_len) {
    int err = 0;
    opus_int32 skip = 0;
    *out_len = 0;

    OpusDecoder *dec = opus_decoder_create(SAMPLE_RATE, 1, &err);
    if (err != OPUS_OK) {
        fprintf(stderr, "cannnot decode opus: %s\n", opus_strerror(err));
        dec = NULL;
        return -1;
    }

    short frame_size = WB_FRAME_SIZE;

    opus_int16 *frame = (opus_int16 *) in;

    while (len > 0) {
        int nbytes = in[0];
        if (nbytes <= 0) {
            return -1;
        }
        int decode_len = opus_decode(dec, in + sizeof(char), nbytes, out,
                                     frame_size, 0);
        if (decode_len != frame_size) {
            return -1;
        }

        in += sizeof(char) + nbytes;
        out += frame_size;
        len -= nbytes - sizeof(char);
        *out_len += frame_size;
    }
    opus_decoder_destroy(dec);
    return 0;
}