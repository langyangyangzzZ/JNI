package com.example.jni.bean;

import android.util.Log;

/**
 * author : Tiaw.
 * date   : 4/28/21
 * 博客：https://blog.csdn.net/weixin_44819566
 * desc   :
 */
public class Persion {
    public String name ="";
    public int age = 0;

    public Persion(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        Log.i("szjjava 层 setName方法:",name);
        this.name = name;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public static void show(String name) {
        Log.i("szjjava 层show方法:", name);
    }

    @Override
    public String toString() {
        return "Persion{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }
}
