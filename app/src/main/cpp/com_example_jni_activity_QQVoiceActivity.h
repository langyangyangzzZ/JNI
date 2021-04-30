#include <jni.h>

//TODO .h和.hpp 文件区别:
//.h 是 C 的头文件
//.cpp 是 C++的头文件
//C++也可以使用.h 文件,没有区别!

#include <fmod.hpp>//fmod 必须导入
#include <string>
#include <android/log.h>
#include <unistd.h>
#include <pthread.h>

//TODO 打印
#define TAG "native 层"
//...我都不知道要传什么,可以借助 JNI 中的宏来传入
#define LOGD(...)__android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__);
#define LOGI(...)__android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__);
#define LOGE(...)__android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__);

#ifndef _Included_com_example_jni_activity_QQVoiceActivity
#define _Included_com_example_jni_activity_QQVoiceActivity
#ifdef __cplusplus
extern "C" {
#endif
#undef com_example_jni_activity_QQVoiceActivity_MODE_YUANSHENG
#define com_example_jni_activity_QQVoiceActivity_MODE_YUANSHENG 0L
#undef com_example_jni_activity_QQVoiceActivity_MODE_lUOLI
#define com_example_jni_activity_QQVoiceActivity_MODE_lUOLI 1L
#undef com_example_jni_activity_QQVoiceActivity_MODE_DASHU
#define com_example_jni_activity_QQVoiceActivity_MODE_DASHU 2L
#undef com_example_jni_activity_QQVoiceActivity_MODE_JINGSONG
#define com_example_jni_activity_QQVoiceActivity_MODE_JINGSONG 3L
#undef com_example_jni_activity_QQVoiceActivity_MODE_GAOGUAI
#define com_example_jni_activity_QQVoiceActivity_MODE_GAOGUAI 4L
#undef com_example_jni_activity_QQVoiceActivity_MODE_KONGLING
#define com_example_jni_activity_QQVoiceActivity_MODE_KONGLING 5L

JNIEXPORT void JNICALL
Java_com_example_jni_activity_QQVoiceActivity_showVoice(JNIEnv *, jobject, jint,
                                                        jstring);

JNIEXPORT void JNICALL
Java_com_example_jni_activity_QQVoiceActivity_showCustomVoice(JNIEnv *, jobject,
                                                              jstring, jint,
                                                              jint, jint,
                                                              jint, jint);

#ifdef __cplusplus
}
#endif
#endif
