package com.example.jni.activity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.example.jni.R;

/**
 * author : Tiaw.
 * date   : 5/3/21
 * 博客：https://blog.csdn.net/weixin_44819566
 * desc   :
 */
public class ExceptionActivity extends AppCompatActivity {

    private static final String TAG = "ExceptionActivity:";

    static {
        System.loadLibrary("native-exception-lib");
    }

    //TODO JNI 异常处理
    //方式一:native 层自己消费消息
    public native void nativeException1();



    //方式三:native 层调用 java 层的异常信息
    public native void nativeException3();

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_exception);
    }

    /**
     * 异常处理一 :测试1(native 层自己消费)
     *
     * @param view
     */
    public void onClick1(View view) {
        nativeException1();
    }

    //方式二:native 层反映给 java 层
    public native void nativeException2() throws NullPointerException;
    /**
     * 测试2(native 层反映给 java 层消费)
     *
     * @param view
     */
    public void onClick2(View view) {

        try {
            nativeException2();
        } catch (Exception e) {
            e.printStackTrace();
            Log.i(TAG, e.getMessage() + "");
        }
    }

    /**
     * 测试3(native 层调用 java 层的异常方法)
     *
     * @param view
     */
    public void onClick3(View view) {
        nativeException3();
    }

    //异常
    public static void showExpetcion() throws NullPointerException {

        Log.i(TAG, "java 层异常了1");
        Log.i(TAG, "java 层异常了2");
        Log.i(TAG, "java 层异常了3");

        throw new NullPointerException("Null 了");
    }
}
