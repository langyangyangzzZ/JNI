//
// Created by 史振江 on 4/29/21.
//
#include <unistd.h>
#include "com_example_jni_activity_QQVoiceActivity.h"

//FMOD 命名空间
using namespace FMOD;

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_activity_QQVoiceActivity_showVoice(JNIEnv *env, jobject thiz, jint mode,
                                                        jstring path) {

    char *content = "播放完毕";

    //接收传过来的路径
    const char *path_ = env->GetStringUTFChars(path, NULL);

    //音效引擎系统
    System *system = 0;

    //声音
    Sound *sound = 0;

    //声音通道(音轨)
    Channel *channel = 0;

    //DSP (digital signal process 数字信号处理)
    //音效的核心通过这个来改变
    DSP *dsp = 0;

    //TODO 第一步,创建系统
    System_Create(&system);

    //TODO 第二步,系统初始化
    /**
     * 参数一:通道数(这里随便取正数)
     * 参数二:宏定义初始化系统
     * 参数三:(不认识)
     */
    system->init(32, FMOD_INIT_NORMAL, 0);

    //TODO 第三步:创建声音
    /**
     * 参数一:声音播放路径
     * 参数二:声音初始化标记
     * 参数三:额外数据(不认识)
     * 参数四:声音
     */
    system->createSound(path_, FMOD_DEFAULT, 0, &sound);

    //TODO 第四步:播放声音
    /**
     * 参数一:声音
     * 参数二:音轨分组(0 代表不分组)
     * 参数三:控制(不认识)
     * 参数四:通道
     */
    system->playSound(sound, 0, false, &channel);

    //TODO 增加特效
    switch (mode) {
        case com_example_jni_activity_QQVoiceActivity_MODE_YUANSHENG:
            //TODO 正常
            content = "原声 播放完毕";
            break;
        case com_example_jni_activity_QQVoiceActivity_MODE_lUOLI:
            //TODO 萝莉
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);

            //调节音调Pitch为 2.0(范围0-2.0)
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 2.0);

            //添加音效到通道
            //参数一:通道
            channel->addDSP(0, dsp);

            content = "萝莉音 播放完毕";
            break;
        case com_example_jni_activity_QQVoiceActivity_MODE_DASHU:
            //TODO 大叔
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);

            //调节音调Pitch为 2.0(范围0-2.0)
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.7);

            //添加音效到通道
            //参数一:通道
            channel->addDSP(0, dsp);
            content = "大叔音 播放完毕";
            break;
        case com_example_jni_activity_QQVoiceActivity_MODE_JINGSONG:
            //TODO 惊悚
            //特点:很多声音的拼接
            //音调低,有回声 声音颤抖

            //=======  调节音调  ======
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.7);
            channel->addDSP(0, dsp);

            //=======  调节音调  ======
            //FMOD_DSP_TYPE_ECHO回音
            system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
            //回音 (默认 500  范围:10-5000)
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 200);
            //声音衰减(默认 50 范围:10-100)
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 20);
            //添加到通道
            channel->addDSP(1, dsp);

            //=======  声音颤抖  ======
            //FMOD_DSP_TYPE_TREMOLO 颤抖声音(默认 5  范围:0-20)
            system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_TREMOLO_FREQUENCY, 10);
            //添加到通道
            channel->addDSP(2, dsp);
            content = "惊悚音 播放完毕";
            break;
        case com_example_jni_activity_QQVoiceActivity_MODE_KONGLING:
            //TODO 回声
            //FMOD_DSP_TYPE_ECHO回音
            system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);

            //回音 (默认 500  范围:10-5000)
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 200);
            //声音衰减(默认 50 范围:10-100)
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 20);

            //添加到通道
            channel->addDSP(0, dsp);
            content = "回声 播放完毕";
            break;
        case com_example_jni_activity_QQVoiceActivity_MODE_GAOGUAI:
            //TODO 搞怪(小黄人)
            //小黄人说话频率很快(调节语速)
            float frequency = 0;
            //从音轨拿频率
            channel->getFrequency(&frequency);

            //调节频率
            channel->setFrequency(frequency * 1.5);
            content = "搞怪音 播放完毕";
            break;
    }

    //TODO 播放完毕
    bool is_play = true;
    while (is_play) {
        //是否播放完成,音轨最清楚,如果播放完成音轨会将 is_play 修改成 false
        channel->isPlaying(&is_play);

        //每隔一秒睡眠一次
        usleep(1000 * 1000);
    }

    //TODO 一定要回收
    sound->release();
    system->close();
    system->release();
    env->ReleaseStringUTFChars(path, path_);

    // 告知Java播放完毕
    jclass mainCls = env->GetObjectClass(thiz);
    jmethodID endMethod = env->GetMethodID(mainCls, "playerEnd", "(Ljava/lang/String;)V");
    jstring value = env->NewStringUTF(content);
    env->CallVoidMethod(thiz, endMethod, value);
}