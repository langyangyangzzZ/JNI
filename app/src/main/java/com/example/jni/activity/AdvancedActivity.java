package com.example.jni.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.example.jni.R;
import com.example.jni.bean.Dog;
import com.example.jni.bean.Persion;

/**
 * JNI 进阶
 * 基本类型,引用类型传值
 */
public class AdvancedActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-advanced-lib");
    }

    //基本类型调用
    public native void nativeBasicTypes(int arg0, double arg2, boolean arg3, String arg4, String[] arg5, int[] arg6);

    //引用类型调用
    public native void nativeMethod(Persion persion);

    //引用类型调用 Dog 中的 DogShow(Persion)方法
    public native void nativeMethod2(Dog dog);

    //全局引用测试
    public native void nativeAllQuote();

    //修复全局引用
    public native void nativeRepairAllQuote();

    //调用构造方法
    public native void nativeStructure(Dog dog);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_advanced);
    }

    /**
     * 基本类型传值(java->native)
     *
     * @param view
     */
    public void onClick1(View view) {
        String strarray[] = {"成龙", "李小龙", "松井宝", "迪丽热巴", "ohh"};
        int ints[] = {1, 4, 2, 62, 61};
        nativeBasicTypes(42, 24.42, true, "李元霸", strarray, ints);

        for (int i = 0; i < ints.length; i++) {
            Log.i("szjjava 层打印", ints[i] + "");
        }
    }

    /**
     * 引用类型方法调用
     *
     * @param view
     */
    public void onClick2(View view) {
        nativeMethod(new Persion("洪静宝", 42));
    }

    /**
     * 引用类型2
     *
     * @param view
     */
    public void onClick3(View view) {
        nativeMethod2(new Dog());
    }

    /**
     * 全局引用测试(会崩溃)
     *
     * @param view
     */
    public void onClick4(View view) {
        nativeAllQuote();
    }

    /**
     * 修复全局引用 BUG
     *
     * @param view
     */
    public void onClick5(View view) {
        nativeRepairAllQuote();
    }

    /**
     * 调用构造方法
     *
     * @param view
     */
    public void onClick6(View view) {
        nativeStructure(new Dog());
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        //在 Activity 结束的时候,释放全局引用
        nativeRepairAllQuote();
    }
}