package com.example.jni.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.example.jni.R;


public class SimpleActivity extends AppCompatActivity {

    /**
     * JNI :java native interface (java 本地接口)
     *
     * javah com.example.jni.MainActivity 生产该类的头文件
     */
    static {
        System.loadLibrary("native-simple-lib");
    }

    //
    /**
     * javah com.example.jni.MainActivity
     * 常量会通过该命令生成宏
     */
    static final int A = 234;

    public String name = "张三";

    public native String getString();
//    public native String getString2();

    //JNI 交互操作

    //通过 native 修改名字 为"李四"
    public native void changeName();

    //通过 native 修改年龄+10
    public static native void changeAge();

    //native 调用 java 方法
    public native int nativeAdd();

    public int add(int number1, int number2) {
        return number1 + number2;
    }


    public static int age = 25;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_simple);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        //非静态 通过 C++改变 为"李四"
        changeName();
        //静态 通过 C++改变为 age+10
        changeAge();
        nativeAdd();
//        getString();
        tv.setText(name + "\t" + age);
    }

    /**
     * java 本地方法 实现在 native 层
     * @return
     */
//    public native String stringFromJNI();
}