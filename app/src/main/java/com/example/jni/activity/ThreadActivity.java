package com.example.jni.activity;

import android.os.Bundle;
import android.os.Looper;
import android.view.View;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.example.jni.R;

/**
 * author : Tiaw.
 * date   : 4/30/21
 * 博客：https://blog.csdn.net/weixin_44819566
 * desc   : 动态注册与 C++线程
 */
public class ThreadActivity extends AppCompatActivity {
    //
    static {
        System.loadLibrary("native-thread-lib");
    }

    //TODO 动态注册
    public native void nativeDynamicRegist();

    public native int nativeDynamicRegist2(String name);

    //TODO JNI 线程
    public native void nativeThread();

    //TODO 释放引用
    public native void nativeRelease();

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_thread);
    }

    /**
     * 动态注册
     *
     * @param view
     */
    public void onClick1(View view) {
        nativeDynamicRegist();
        nativeDynamicRegist2("李元霸");
    }

    /**
     * JNI 线程
     *
     * @param view
     */
    public void onClick2(View view) {
        nativeThread();
    }

    public void isThread() {
        if (Looper.getMainLooper() == Looper.myLooper()) {
            Toast.makeText(this, "当前是主线程", Toast.LENGTH_SHORT).show();
        } else {
            runOnUiThread(() -> Toast.makeText(this, "当前是子线程", Toast.LENGTH_SHORT).show());
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        //释放 native 层引用
        nativeRelease();
    }


}
