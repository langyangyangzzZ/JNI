package com.example.jni.bean;

import android.util.Log;

/**
 * author : Tiaw.
 * date   : 4/28/21
 * 博客：https://blog.csdn.net/weixin_44819566
 * desc   :
 */
public class Dog {

    private Persion persion;

    public void DogShow(Persion persion) {
        this.persion = persion;
        Log.i("szjjava层 DogShow 方法", persion.toString());
    }

    public Dog() {
        Log.i("szjjava层 Dog 方法", "无参构造");
    }

    public Dog(int arg0, int arg1) {
        Log.i("szjjava层 Dog 方法", arg0 + "\t" + arg1);
    }

    public Dog(int arg0, int arg1, int arg2) {
        Log.i("szjjava层 Dog 方法", arg0 + "\t" + arg1 + "\t" + arg2);
    }
}
