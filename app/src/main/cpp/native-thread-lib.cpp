#include <jni.h>
#include <android/log.h>

#define TAG "native 层:"
//...我都不知道要传什么,可以借助 JNI 中的宏来传入
#define LOGD(...)__android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__);
#define LOGI(...)__android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__);
#define LOGE(...)__android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__);

//JavaVM *jvm = nullptr;

const char *path = "com/example/jni/activity/ThreadActivity";

void javaDynamicRegist(JNIEnv *jniEnv, jobject jobj) {
    LOGE("javaDynamicRegist")
}

int javaDynamicRegist2(JNIEnv *jniEnv, jobject jobj, jstring name) {
    const char *name2 = jniEnv->GetStringUTFChars(name, nullptr);
    LOGE("javaDynamicRegist2%s\n", name2);
    return 200;
}

/**
     typedef struct {
        const char* name;   //调用的名字
        const char* signature;  //签名
        void*       fnPtr;  //具体实现
    } JNINativeMethod;
 */
static const JNINativeMethod jniNativeMethod[] = {
        {"nativeDynamicRegist",  "()V",                   (void *) javaDynamicRegist},
        {"nativeDynamicRegist2", "(Ljava/lang/String;)I", (void *) javaDynamicRegist2},
};



//动态注册,类似于 java 的构造器
jint JNI_OnLoad(JavaVM *javaVm, void *) {
//    ::jvm = javaVm;
    JNIEnv *jniEnv = nullptr;

    //获取 jVM 中的 Env
    int result = javaVm->GetEnv(reinterpret_cast<void **>(&jniEnv), JNI_VERSION_1_6);

    //result != 0 则失败
    if (result != JNI_OK) {
        //失败
        return -1;
    }

    //获取 jclass
    jclass thread_class = jniEnv->FindClass(path);
    /**
     * 源码:
     * jint RegisterNatives(jclass clazz, const JNINativeMethod* methods, jint nMethods)
     * 参数一:class
     * 参数二:结构体数组
     * 参数三:结构体大小
     */
    jniEnv->RegisterNatives(thread_class, jniNativeMethod,
                            sizeof(jniNativeMethod) / sizeof(JNINativeMethod));

        //返回 JNI 版本号
    return JNI_VERSION_1_6;
}