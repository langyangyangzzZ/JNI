//
// Created by 史振江 on 4/28/21.
//
#include "com_example_jni_activity_AdvancedActivity.h"

//TODO 基本类型
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_activity_AdvancedActivity_nativeBasicTypes(JNIEnv *env, jobject thiz,
                                                                jint arg0, jdouble arg2,
                                                                jboolean arg3, jstring arg4,
                                                                jobjectArray arg5,
                                                                jintArray arg6) {

    // 接收int类型
    int j_int_arg0 = arg0;
    LOGE("参数一为%d", j_int_arg0);

    // 接收double类型
    double j_double_arg2 = arg2;
    LOGE("参数二为%f", j_double_arg2);


    // 接收bool类型  1=true 0=false
    int j_bool_arg3 = arg3;
    LOGE("参数三为%d", j_bool_arg3);

    //接收 String 类型的值
//    const char* GetStringUTFChars(jstring string, jboolean* isCopy)
    char * j_string = const_cast<char *>(env->GetStringUTFChars(arg4, NULL));
    LOGE("参数四为%s", j_string);

    //接收 String[]类型的值
    // jsize GetArrayLength(jarray array)
    jsize j_size = env->GetArrayLength(arg5);
    for (int i = 0; i < j_size; i++) {
//        jobject GetObjectArrayElement(jobjectArray array, jsize index)
        jstring j_string2 = static_cast<jstring>(env->GetObjectArrayElement(arg5, i));

        //修改为 C++认识的 char*类型
        const char *jstr = env->GetStringUTFChars(j_string2, NULL);
        LOGE("参数五为%s", jstr);

        //释放 jstring
        env->ReleaseStringChars(j_string2, reinterpret_cast<const jchar *>(jstr));
    }

    //int[] 元素打印
    jint *j_ints = env->GetIntArrayElements(arg6, NULL);
    jsize j_size_ints = env->GetArrayLength(arg6);
    for (int i = 0; i < j_size_ints; i++) {
        *(j_ints + i) += 100;
        LOGE("第六个参数为:%d", *(j_ints + i))
    }
    //返回修改后的数组给 java 层
    env->ReleaseIntArrayElements(arg6, j_ints, 0);
}

//TODO 引用类型

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_activity_AdvancedActivity_nativeMethod(JNIEnv *env, jobject thiz,
                                                            jobject persion) {

    /**
     * 获取 Persion 的 class
     *  源码: jclass FindClass(const char* name)
     */
    jclass j_class = env->FindClass("com/example/jni/bean/Persion");

    /**
     * 获取方法 ID:
     * jmethodID GetMethodID(jclass clazz, const char* name, const char* sig)
     */
    jmethodID j_method_id = env->GetMethodID(j_class, "getName", "()Ljava/lang/String;");

    //获取 Persion getName方法返回值
    jstring j_strName = static_cast<jstring>(env->CallObjectMethod(persion, j_method_id));

    //修改为 C++认识的 char*类型
    char *j_char_name = const_cast<char *>(env->GetStringUTFChars(j_strName, NULL));
    LOGE("通过 getName获取值为:%s", j_char_name)


    //获取 setName的 ID
    jmethodID j_setName_id = env->GetMethodID(j_class, "setName", "(Ljava/lang/String;)V");
    //获取静态的 show 方法
    jmethodID j_show_id = env->GetStaticMethodID(j_class, "show", "(Ljava/lang/String;)V");

    env->CallVoidMethod(persion, j_setName_id, env->NewStringUTF("糖果超甜"));
    env->CallStaticVoidMethod(j_class, j_show_id, env->NewStringUTF("糖果超甜"));
}

//TODO 引用类型进阶

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_activity_AdvancedActivity_nativeMethod2(JNIEnv *env, jobject thiz,
                                                             jobject dog_jobj) {

    //获取 Dog 类的 Class
    jclass j_dog_class = env->GetObjectClass(dog_jobj);

    //获取 Dog 类中的 DogShow 方法 ID
    jmethodID jmethodId = env->GetMethodID(j_dog_class, "DogShow",
                                           "(Lcom/example/jni/bean/Persion;)V");

    //获取 Persion 的 jclass
    jclass j_persion_class = env->FindClass("com/example/jni/bean/Persion");
    //获取 Persion 的 jobj //AllocObject只实例化对象,不会调用构造函数
    jobject j_persion_job = env->AllocObject(j_persion_class);

    //给 Persion 赋值
    jmethodID j_setName_id = env->GetMethodID(j_persion_class, "setName", "(Ljava/lang/String;)V");
    jmethodID j_setAge_id = env->GetMethodID(j_persion_class, "setAge", "(I)V");

    //调用 Persion 的 setName 和 setAge 给 name 和 age 赋值
    env->CallVoidMethod(j_persion_job, j_setName_id, env->NewStringUTF("蔡徐坤"));
    env->CallVoidMethod(j_persion_job, j_setAge_id, 52);

    //调用 Dog 的 DogShow(Persion)方法
    env->CallVoidMethod(dog_jobj, jmethodId, j_persion_job);

    //释放引用类型 class 和 job 都建议释放
    env->DeleteGlobalRef(j_dog_class);
    env->DeleteGlobalRef(j_persion_class);
    env->DeleteGlobalRef(j_persion_job);

    //String 类型也得释放
//    jstring str = env->NewStringUTF("模拟释放数据");
//    //释放 String类型
//    env->ReleaseStringUTFChars(str, NULL);
}

//TODO 调用 Dog 的构造方法
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_activity_AdvancedActivity_nativeStructure(JNIEnv *env, jobject thiz,
                                                               jobject dog) {

    //获取 Dog 的 jclass
    jclass j_dog_class = env->GetObjectClass(dog);

    //获取构造方法
    jmethodID id1 = env->GetMethodID(j_dog_class, "<init>", "()V");
    jmethodID id2 = env->GetMethodID(j_dog_class, "<init>", "(II)V");
    jmethodID id3 = env->GetMethodID(j_dog_class, "<init>", "(III)V");

    //调用构造方法
    env->CallVoidMethod(dog, id1);
    env->CallVoidMethod(dog, id2, 100, 200);
    env->CallVoidMethod(dog, id3, 300, 400, 500);
}

//TODO 全局引用 BUG
    /**
     * jclass / jclass 都是属于局部引用
     * 局部引用: 函数结束后会自动释放(自己释放的话,如果代码量特别大, 不回引起 JNI 调用波动太大)
     * 全局引用:不会自动释放,需要手动释放
     */
jclass dogClass;
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_activity_AdvancedActivity_nativeAllQuote(JNIEnv *env, jobject thiz) {
    if (NULL == dogClass) {
        //这个是局部引用,(和 java 不同)
//        dogClass = env->FindClass("com/example/jni/bean/Dog");

        //这个是全局引用NewGlobalRef (全局引用:JNI函数不释放,如果要释放,需要手动释放)
        const char *a = "com/example/jni/bean/Dog";
        jclass temp = env->FindClass(a);
        //全局引用
        dogClass = static_cast<jclass>(env->NewGlobalRef(temp));
        //释放临时的 jclass
        env->DeleteLocalRef(temp);
    }
    //获取 Dog 的 jclass
    jclass j_dog_class = env->GetObjectClass(dogClass);

    //获取构造方法
    jmethodID id1 = env->GetMethodID(dogClass, "<init>", "()V");
    jmethodID id2 = env->GetMethodID(dogClass, "<init>", "(II)V");
    jmethodID id3 = env->GetMethodID(dogClass, "<init>", "(III)V");

    //调用构造方法
    env->CallVoidMethod(j_dog_class, id1);
    env->CallVoidMethod(j_dog_class, id2, 100, 200);
    env->CallVoidMethod(j_dog_class, id3, 300, 400, 500);
//    dogClass =  NULL;//专门注释掉的!

}//因为当方法结束的时候,dogClass 会弹栈,但是dogClass还是不等于 NULL,此时只是内存地址消失,但是指针还指向内一个地址,是悬空指针状态


//TODO 修复全局引用 BUG 在 Activity 的 onDecto
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_activity_AdvancedActivity_nativeRepairAllQuote(JNIEnv *env, jobject thiz) {
    if (dogClass != NULL) {
        //释放全局引用
        LOGE("释放全局引用")
        env->DeleteLocalRef(dogClass);
        dogClass = NULL;
    }
}