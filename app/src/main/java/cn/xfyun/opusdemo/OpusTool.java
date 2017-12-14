package cn.xfyun.opusdemo;

public class OpusTool {

    public static native String nativeGetString();

    public static native byte[] encode_data(byte[] in, int len);

    public static native byte[] decode_data(byte[] in, int len);
}