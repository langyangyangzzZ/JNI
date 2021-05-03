#include <jni.h>
#include <android/log.h>
#include <pthread.h>

#define TAG "native 层:"
//...我都不知道要传什么,可以借助 JNI 中的宏来传入
#define LOGD(...)__android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__);
#define LOGI(...)__android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__);
#define LOGE(...)__android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__);

JavaVM *jvm = nullptr;

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
    ::jvm = javaVm;
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


//TODO  ================  JNI 线程 ===============

class MyThread {
public:
    jobject jobj = nullptr;
} my_thread;

//函数回调
void *my_thread_action(void *pVoid) {
    MyThread *thread = static_cast<MyThread *>(pVoid);
    /**
     * JVM 只有一个 jNIEnv
     * jNIEnv解决方式:
     */
    JNIEnv *newJniEnv = nullptr;
    /**
     *  jint AttachCurrentThread(JNIEnv** p_env, void* thr_args)
     *   得到全新的 JNIEnv
     */
    jint result = ::jvm->AttachCurrentThread(&newJniEnv, nullptr);

    //结果 == 0 表示成功
    if (result != JNI_OK) {
        return 0; // 附加失败，返回了
    }

    jclass j_c = newJniEnv->GetObjectClass(thread->jobj);
    jmethodID j_id = newJniEnv->GetMethodID(j_c, "isThread", "()V");
    //调用 java 层的 isThread 方法
    newJniEnv->CallVoidMethod(thread->jobj, j_id);

    //解除附加
    ::jvm->DetachCurrentThread();
    //不能直接释放引用
    return nullptr;
}

extern "C"
JNIEXPORT void JNICALL
/**
 * JNIEnv 不能跨越线程,可以跨越函数
 * jobject 不能跨越线程,不能跨越函数[解决思路:吧 jobject 提升为全局引用]
 * javaVM 能跨越线程,能跨越函数
 */
Java_com_example_jni_activity_ThreadActivity_nativeThread(JNIEnv *env, jobject thiz) {

    MyThread *thread = new MyThread;

    //将 thiz 提升为全局引用 (默认为局部引用)
    thread->jobj = env->NewGlobalRef(thiz);

    pthread_t pid;
    /**
     * 参数一:线程 ID
     * 参数二:线程属性(一般都是 0 或者 nullptr)
     * 参数三:函数回调
     * 参数四:传递的值
     */
    pthread_create(&pid, nullptr, my_thread_action, thread);

    //挂起当前线程，用于阻塞式地等待线程结束，如果线程已结束则立即返回，0=成功
    pthread_join(pid, nullptr);

    //释放引用
    delete thread;
}

//TODO 释放全局引用
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_activity_ThreadActivity_nativeRelease(JNIEnv *env, jobject thiz) {
    env->DeleteGlobalRef(my_thread.jobj);
}