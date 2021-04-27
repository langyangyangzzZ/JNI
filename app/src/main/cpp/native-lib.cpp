#include "com_example_jni_MainActivity.h"

//NDK 工具链中的 log库
#include <android/log.h>

#define TAG "szj"
//...我都不知道要传什么,可以借助 JNI 中的宏来传入
#define LOGD(...)__android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__);
#define LOGI(...)__android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__);
#define LOGE(...)__android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__);


//TODO  参数介绍 ----------start------------
//JNIEnv 是 C++ 的最终会调用到 C 的 JNINativeInterface方法 ,所以必须采用 C 的方式(extern "C")
extern "C" //采用 C 的编译方式

JNIEXPORT //标记该方法会被外部调用(VS 会报错,AS 不会报错)

jstring // java中方法的返回值,
// 这里返回 jstring,表示 java 中是 String 类型
//如果是 jint则表示 java 中是 int 类型

JNICALL//表示是 JIN 的标记(这个可以去掉)

//函数名,由 JDK设计的(JNI 是 java 的技术,不是 native 的技术)
Java_com_example_jni_MainActivity_getString
        (JNIEnv *env, jobject job) {
    /**
     * 参数一:(JNIEnv):是 Java 与 C/C++通信最重要的东西(精华)
     * 参数二 :情况一(jobject)非静态:谁调用它,就是谁的实例,这里 MainActivity 调用,job 就是 MainActivity(this)
     *      :情况二:(jclass)静态: 谁调用它,就是谁的class,这里 MainActivity 调用,jclass 就是 MainActivity.class
     */
}
//TODO  参数介绍 ----------stop------------


//TODO 获取 java 的属性name,修改为"李四"
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_MainActivity_changeName(JNIEnv *env, jobject thiz) {
    /**
     *  获取 class
     */
    jclass j_cls = env->GetObjectClass(thiz);

    /**
     * jfieldID GetFieldID(jclass clazz, const char* name, const char* sig)
     * 参数一:MainActivity.class
     * 参数二:属性名
     * 参数三:属性签名 L 表示引用类型
     */
    jfieldID j_fid = env->GetFieldID(j_cls, "name", "Ljava/lang/String;");

    /**
     * jobject GetObjectField(jobject obj, jfieldID fieldID)
     * 把 java 属性变成 jstring 类型
     * 参数一:jobject
     * 参数二:签名 ID
     * static_cast<jstring>强制转换为 jstring 类型
     */
    jstring j_str = static_cast<jstring>(env->GetObjectField(thiz, j_fid));

    /**
     * 将JNI 的jstring 转换为C++的 char 类型
     * const char* GetStringUTFChars(jstring string, jboolean* isCopy)
     *  打印字符串
     *  参数一:需要转换的字符串
     *  参数二:不知道是啥
     */
    const char *chars = env->GetStringUTFChars(j_str, NULL);
    LOGD("native %s", chars);
    LOGI("native %s", chars);
    LOGE("native %s", chars);

    jstring st = env->NewStringUTF("李四");

    /**
     * void SetObjectField(jobject obj, jfieldID fieldID, jobject value)
     *  修改成 李四
     *  参数一:jobject
     *  参数二:签名 ID
     *  参数三:修改后的 jstring
     */
    env->SetObjectField(thiz, j_fid, st);

}

//TODO 获取静态属性Age,修改年龄+10
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_MainActivity_changeAge(JNIEnv *env, jclass clazz) {
    /**
     * 参数三:基本类型签名(int 对应 I)
     */
    jfieldID j_id = env->GetStaticFieldID(clazz, "age", "I");

    /**
     * 获取静态int 类型的属性
     *jint GetStaticIntField(jclass clazz, jfieldID fieldID)
     * 参数一:jclass
     * 参数二:静态 属性ID
     */
    jint j_age = env->GetStaticIntField(clazz, j_id);

    //修改参数
    j_age += 10;

    /**
     * 修改值后,在设置回去新的值
     * void SetStaticIntField(jclass clazz, jfieldID fieldID, jint value)
     * 参数一:jclass
     * 参数二:静态属性 ID
     * 参数三:新的静态值
     */
    env->SetStaticIntField(clazz, j_id, j_age);
}


//TODO  调用 java 层的方法
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jni_MainActivity_nativeAdd(JNIEnv *env, jobject thiz) {
    /**
     * 通过 jobject 获取 jclass
     * jclass GetObjectClass(jobject obj)
     */
    jclass j_c = env->GetObjectClass(thiz);

    /**
     * 获取方法 ID;
     * jmethodID GetMethodID(jclass clazz, const char* name, const char* sig)
     * 参数一:jclass 对象
     * 参数二:调用的方法名
     * 参数三:参数与返回值签名
     */
    jmethodID jmethodId = env->GetMethodID(j_c, "add", "(II)I");

    /**
     * jint(*CallIntMethod)(JNIEnv*, jobject, jmethodID, ...);
     *  调用 java 的方法返回值为int
     */
    jint jint1 = env->CallIntMethod(thiz, jmethodId, 4, 2);
    LOGE("native %d", jint1);


    //方法结束必须返回 0 ,否则会报以下错误,(不要问,问就是找了 20 分钟)
    //Fatal signal 5 (SIGTRAP), code 1 (TRAP_BRKPT), fault addr 0x7675a751dc in tid 18347 (com.example.jni),
    // pid 18347 (com.example.jni)
    return 0;
}


/**
 * 签名:
 * java 的 boolean  --- Z  注意!
 * java 的 short  --- S
 * java 的 int  --- Z
 * java 的 byte  --- B
 * java 的 double  --- D
 * java 的 float  --- F
 * java 的 char  --- C
 * java 的  long  --- J  注意!
 * java 的 boolean  --- Z
 * java 的 对象  --- L 包名/类名; (;一定要加!!)
 *                    例如:String Ljava/lang/String;
 * java 中的 array int[]  ---- [I
 * java 中的 array int[][]  ---- [[I
 *
 * javap -s -p xxx.class
 * -s 输出 xxx.class 的所有属性和方法名
 * -p 忽略私有公开的属性
 */
