package cn.xfyun.opusdemo;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;

public class MainActivity extends AppCompatActivity {

    private final static String PCM_FILE_PATH = Environment.getExternalStorageDirectory().getPath() + "/OpusDemo/1.pcm";
    private final static String OPUS_FILE_PATH = Environment.getExternalStorageDirectory().getPath() + "/OpusDemo/1.opus";

    private final static String REPCM_FILE_PATH = Environment.getExternalStorageDirectory().getPath() + "/OpusDemo/2.pcm";

   // private final static String OPUS_FILE_PATH_SYS = Environment.getExternalStorageDirectory().getPath() + "/OpusDemo/sys.opus";
    //private final static String REPCM_FILE_PATH_SYS = Environment.getExternalStorageDirectory().getPath() + "/OpusDemo/sys.pcm";

    private Button mPCMConvertFileBtn;
    private Button mOPUSConvertFileBtn;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Toast.makeText(MainActivity.this, OpusTool.nativeGetString(), Toast.LENGTH_SHORT).show();

        mPCMConvertFileBtn = findViewById(R.id.pcm_convert_btn);
        mPCMConvertFileBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                convert();
            }
        });

        mOPUSConvertFileBtn = findViewById(R.id.opus_convert_btn);
        mOPUSConvertFileBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                reconvert();
            }
        });
    }

    private void convert(){
        try {
            File file = new File(PCM_FILE_PATH);
            if(file.exists()){
                FileInputStream is = new FileInputStream(file);
                byte[] b = new byte[is.available()];
                is.read(b);
                byte[] opus = OpusTool.encode_data(b,b.length);
                try {
                    File output = new File(OPUS_FILE_PATH);
                    FileOutputStream fos = new FileOutputStream(output);
                    fos.write(opus);
                    fos.close();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }else{
                Toast.makeText(MainActivity.this, "文件不存在", Toast.LENGTH_SHORT).show();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void reconvert(){
        try {
            File file = new File(OPUS_FILE_PATH);
            if(file.exists()){
                FileInputStream is = new FileInputStream(file);
                byte[] b = new byte[is.available()];
                is.read(b);
                byte[] pcm = OpusTool.decode_data(b,b.length);
                try {
                    File output = new File(REPCM_FILE_PATH);
                    FileOutputStream fos = new FileOutputStream(output);
                    fos.write(pcm);
                    fos.close();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }else{
                Toast.makeText(MainActivity.this, "文件不存在", Toast.LENGTH_SHORT).show();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    static {
        System.loadLibrary("opustool");
    }

}
