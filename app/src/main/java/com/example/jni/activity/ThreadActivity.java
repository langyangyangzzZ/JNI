package com.example.jni.activity;

import android.os.Bundle;
import android.os.PersistableBundle;
import android.view.View;

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
}
