//
// Created by 史振江 on 5/3/21.
//
#include <jni.h>
#include <pthread.h>

#include <android/log.h>

#define TAG "native 层:"
//...我都不知道要传什么,可以借助 JNI 中的宏来传入
#define LOGD(...)__android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__);
#define LOGI(...)__android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__);
#define LOGE(...)__android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__);

//TODO 方式一
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_activity_ExceptionActivity_nativeException1(JNIEnv *env, jobject thiz) {

    jclass j_class = env->GetObjectClass(thiz);

    //这行代码会报错!!!
    jfieldID j_id = env->GetFieldID(j_class, "name", "Ljava/lang/String;");
    //TODO 方式一
    //判断是否发生过异常
    jthrowable j_thr = env->ExceptionOccurred();
    if (j_thr) {
        LOGE("检测到异常");
        //清除异常
        env->ExceptionClear();
    }
}


//TODO 方式二
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_activity_ExceptionActivity_nativeException2(JNIEnv *env, jobject thiz) {
    jclass j_class = env->GetObjectClass(thiz);
    //这行代码会报错!!!
    jfieldID j_id = env->GetFieldID(j_class, "name", "Ljava/lang/String;");

    //TODO 方式一
    //判断是否发生过异常
    jthrowable j_thr = env->ExceptionOccurred();
    //非 0 级 true
    if (j_thr) {
        LOGE("检测到异常");
        //清除异常
        env->ExceptionClear();

        //参数填写的是异常包名路径
        jclass null_class = env->FindClass("java/lang/NullPointerException");

        env->ThrowNew(null_class, "报错啦报错啦 NullPointerException!!");
    }
}

//TODO 方式三
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_activity_ExceptionActivity_nativeException3(JNIEnv *env, jobject thiz) {
    jclass j_class = env->GetObjectClass(thiz);

    jmethodID j_id = env->GetStaticMethodID(j_class, "showExpetcion", "()V");
    //调用 java 层的异常方法 ,走到这里会崩溃
    env->CallStaticVoidMethod(j_class, j_id);

    //检查是否会崩溃(可以理解为 判断 java 层是否抛出异常)
    if (env->ExceptionCheck()) {
        //输出描述错误信息
        env->ExceptionDescribe();
        //清除掉崩溃信息
        env->ExceptionClear();
    }
}
