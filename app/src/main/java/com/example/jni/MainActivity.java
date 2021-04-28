package com.example.jni;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.example.jni.activity.AdvancedActivity;
import com.example.jni.activity.SimpleActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    }

    /**
     * JNI 简单入门
     * @param view
     */
    public void onClick1(View view) {
        srartActivity(SimpleActivity.class);
    }

    /**
     * JNI 进阶(基本数据类型,引用数据类型传值等)
     * @param view
     */
    public void onClick2(View view) {
        srartActivity(AdvancedActivity.class);
    }

    /**
     * 跳转的页面
     * @param classs
     */
    private void srartActivity(Class<?> classs) {
        Intent intent = new Intent(MainActivity.this, classs);
        startActivity(intent);
    }


}