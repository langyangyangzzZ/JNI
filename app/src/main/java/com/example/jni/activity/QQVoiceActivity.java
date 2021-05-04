package com.example.jni.activity;

import androidx.appcompat.app.AppCompatActivity;
import androidx.databinding.DataBindingUtil;
import androidx.databinding.ViewDataBinding;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import com.example.jni.R;
import com.example.jni.bean.QQBean;
import com.example.jni.databinding.QQBinDing;

import org.fmod.FMOD;

/**
 * QQ语音实战
 */
public class QQVoiceActivity extends AppCompatActivity implements SeekBar.OnSeekBarChangeListener {

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

    private QQBinDing binding;

    //调用 ntive 声音
    public native void showVoice(int mode, String path);

    //自定义音频
    public native void showCustomVoice(String path, int yindiao, int huiying, int shuaijian, int candou, int sudu);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = DataBindingUtil.setContentView(this, R.layout.activity_q_q_voice);

        //初始化 fmod
        FMOD.init(this);

        binding.setBean1(new QQBean(2, 0, 0, "音调"));
//        10-5000
        binding.setBean2(new QQBean(50000, 10, 10, "回音"));
        ////声音衰减(默认 50 范围:10-100)
        binding.setBean3(new QQBean(100, 10, 10, "声音衰减"));
        //颤抖声音(默认 5  范围:0-20)
        binding.setBean4(new QQBean(20, 0, 0, "声音颤抖"));
        //音速度
        binding.setBean5(new QQBean(2, 0, 1, "声音速度"));

        binding.seekBar1.setOnSeekBarChangeListener(this);
        binding.seekBar2.setOnSeekBarChangeListener(this);
        binding.seekBar3.setOnSeekBarChangeListener(this);
        binding.seekBar4.setOnSeekBarChangeListener(this);
        binding.seekBar5.setOnSeekBarChangeListener(this);
    }

    /**
     * 原生
     */
    public void onClick1(View view) {
        new Thread(() -> showVoice(MODE_YUANSHENG, mPath)).start();
    }

    /**
     * 萝莉
     */
    public void onClick2(View view) {
        new Thread(() -> showVoice(MODE_lUOLI, mPath)).start();
    }

    /**
     * 大叔
     */
    public void onClick3(View view) {
        new Thread(() -> showVoice(MODE_DASHU, mPath)).start();
    }

    /**
     * 惊悚
     */
    public void onClick4(View view) {
        new Thread(() -> showVoice(MODE_JINGSONG, mPath)).start();
    }

    /**
     * 搞怪
     */
    public void onClick5(View view) {
        new Thread(() -> showVoice(MODE_GAOGUAI, mPath)).start();
    }

    /**
     * 回音
     */
    public void onClick6(View view) {
        new Thread(() -> showVoice(MODE_KONGLING, mPath)).start();
    }

    // 给C++调用的函数
    // JNI 调用 Java函数的时候，忽略掉 私有、公开 等
    private void playerEnd(String msg) {
        runOnUiThread(() -> {
            Toast.makeText(this, "" + msg, Toast.LENGTH_SHORT).show();
        });
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        FMOD.close();
    }

    @Override
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
        switch (seekBar.getId()) {
            case R.id.seekBar1:
                binding.setBean1(new QQBean(2, 0, progress, "音调"));
                break;
            case R.id.seekBar2:
//        10-5000
                binding.setBean2(new QQBean(50000, 10, progress, "回音"));
                break;
            case R.id.seekBar3:
                ////声音衰减(默认 50 范围:10-100)
                binding.setBean3(new QQBean(100, 10, progress, "声音衰减"));
                break;
            case R.id.seekBar4:
                //颤抖声音(默认 5  范围:0-20)
                binding.setBean4(new QQBean(20, 0, progress, "声音颤抖"));
                break;
            case R.id.seekBar5:
                //音速度
                binding.setBean5(new QQBean(2, 0, progress, "声音速度"));
                break;
            default:
                throw new IllegalStateException("Unexpected value: " + seekBar.getId());
        }
    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {

    }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {

    }

    /**
     * 播放调节后的音频
     *
     * @param view
     */
    public void onClick7(View view) {
        Log.i("onClick7",
                binding.seekBar1.getProgress()+"\t"+
                binding.seekBar2.getProgress()+"\t"+
                binding.seekBar3.getProgress()+"\t"+
                binding.seekBar4.getProgress()+"\t"+
                binding.seekBar5.getProgress());

        new Thread(() -> showCustomVoice(mPath,
                binding.seekBar1.getProgress(),
                binding.seekBar2.getProgress(),
                binding.seekBar3.getProgress(),
                binding.seekBar4.getProgress(),
                binding.seekBar5.getProgress()
        )).start();

    }
}