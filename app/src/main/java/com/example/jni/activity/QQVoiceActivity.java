package com.example.jni.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import com.example.jni.R;

import org.fmod.FMOD;

/**
 * QQ语音实战
 */
public class QQVoiceActivity extends AppCompatActivity {

    private static final int MODE_YUANSHENG = 0;//原生
    private static final int MODE_lUOLI = 1;//萝莉
    private static final int MODE_DASHU = 2;//大叔
    private static final int MODE_JINGSONG = 3;//惊悚
    private static final int MODE_GAOGUAI = 4;//搞怪
    private static final int MODE_KONGLING = 5;//空灵

    //播放路径
    private static final String mPath = "file:///android_asset/voice.mp3";

    static {
        System.loadLibrary("native-qq-voice-lib");
    }

    //调用 ntive 声音
    public native void showVoice(int mode, String path);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_q_q_voice);

        //初始化 fmod
        FMOD.init(this);
    }

    /**
     * 原生
     */
    public void onClick1(View view) {
        showVoice(MODE_YUANSHENG, mPath);
    }

    /**
     * 萝莉
     */
    public void onClick2(View view) {
        showVoice(MODE_lUOLI, mPath);
    }

    /**
     * 大叔
     */
    public void onClick3(View view) {
        showVoice(MODE_DASHU, mPath);
    }

    /**
     * 惊悚
     */
    public void onClick4(View view) {
        showVoice(MODE_JINGSONG, mPath);
    }

    /**
     * 搞怪
     */
    public void onClick5(View view) {
        showVoice(MODE_GAOGUAI, mPath);
    }

    /**
     * 回音
     */
    public void onClick6(View view) {
        showVoice(MODE_KONGLING, mPath);
    }

    // 给C++调用的函数
    // JNI 调用 Java函数的时候，忽略掉 私有、公开 等
    private void playerEnd(String msg) {
        Toast.makeText(this, "" + msg, Toast.LENGTH_SHORT).show();
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        FMOD.close();
    }
}