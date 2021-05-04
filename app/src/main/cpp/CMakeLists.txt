# 最低支持版本
cmake_minimum_required(VERSION 3.4.1)

# TODO 第一步:引入 inc
include_directories("inc")

# 批量导入所有源文件
file(GLOB allCPP *.c *.h *.cpp)

# cpp 文件在这里添加
add_library(
       # native-simple-lib # TODO JNI 基本使用
        #native-advanced-lib # TODO JNI 进阶
        native-qq-voice-lib # TODO QQ 语音实战
        # native-thread-lib # TODO JNI 线程与动态注册
        #native-exception-lib # TODO 异常处理

        SHARED # 动态库 (STATIC 静态库)
        ${allCPP}
)

# TODO 第二步:导入库文件
# CMAKE_CXX_FLAGS 保留之前内容
# CMAKE_SOURCE_DIR CMakeLists.txt 所在路径
# /../推出到上一级
# CMAKE_ANDROID_ARCH_ABI 获取当前手机 CPU 架构
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}")

# 寻找 NDK 的库
find_library(
        log-lib # 只是一个名字 不用在意
        log # 去寻找 liblog.so(<android.log.h>) 库
)

# 链接具体的库到我们的 libXX.io
target_link_libraries(
        # native-simple-lib # TODO JNI 基本使用
        #native-advanced-lib # TODO JNI 进阶
       native-qq-voice-lib # TODO QQ 语音实战
        # native-thread-lib # TODO JNI 线程与动态注册
        #native-exception-lib # TODO 异常处理

        ${log-lib} # 自动寻找  # 具体的库 链接到 libnative-lib.so里面去
        # TODO 配置 fmod
        fmod # 具体的库 链接到 libnative-lib.so里面去
        fmodL # 具体的库 链接到 libnative-lib.so里面去
)

#CPU 架构模式:
# 1.arm64-v8a     现在基本 Android 以这个为主
# 2.armeabi-v7a   2015 早期的手机
# 3.armeabi       2011 基本没人用
# 4.x86 5.x86_64  模拟器

# 如何知道自己手机 CUP 架构(终端输入):
# adb shell getprop ro.product.cpu.abi