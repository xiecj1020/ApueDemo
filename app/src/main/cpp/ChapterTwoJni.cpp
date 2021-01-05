/*
 * Copyright (C) 2021 XieChaoJun
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <android/log.h>
#include <cstdio>
#include <climits>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "include/com_crab_test_apuedemo_jni_ChapterTwoJni.h"

#define TAG "mytag"

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterTwoJni_isoc
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwoJni isoc.");
    //#include <assert.h> 验证程序断言
    //#include <complex.h> 复数算术运算支持
    //#include <ctype.h> 字符分类和映射支持
    //#include <errno.h> 错误码
    //#include <fenv.h> 浮点环境
    //#include <float.h> 浮点常量及特性
    //#include <inttypes.h> 整形格式变换
    //#include <iso646.h> 赋值,关系运算,一元操作符
    //#include <limits.h> 实现常量
    //#include <locale.h> 本地化类别及相关定义
    //#include <math.h> 数学函数和类型声明及常量
    //#include <setjmp.h> 非局部goto
    //#include <signal.h> 信号
    //#include <stdarg.h> 可变长度参数列表
    //#include <stdbool.h> 布尔类型和值
    //#include <stddef.h> 标准定义
    //#include <stdint.h> 整形
    //#include <stdio.h> 标准io库
    //#include <stdlib.h> 实用函数
    //#include <string.h> 字符操作
    //#include <tgmath.h> 通用类型数学宏
    //#include <time.h> 时间和日期
    //#include <wchar.h> 扩充的多字符和宽字符支持
    //#include <wctype.h> 宽字符分类和映射支持
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterTwoJni_posix
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwoJni posix.");
    //-------------------------------------
    //POSIX标准定义的必须的头文件
    //#include <dirent.h> 目录项
    //#include <dlfcn.h> 动态链接
    //#include <fcntl.h> 文件控制
    //#include <fnmatch.h> 文件名匹配类型
    //#include <glob.h> 路径名模式匹配与生成
    //#include <grp.h> 组文件
    //#include <iconv.h> 代码集变换实用程序
    //#include <langinfo.h> 语言信息常量
    //#include <netdb.h> 网络数据库操作
    //#include <nl_types.h> 消息类
    //#include <poll.h> 投票函数
    //#include <pthread.h> 线程
    //#include <pwd.h> 口令文件
    //#include <regex.h> 正则表达式
    //#include <sched.h> 执行调度
    //#include <semaphore.h> 信号量
    //#include <strings.h> 字符串操作
    //#include <tar.h> tar归档值
    //#include <termios.h> 终端IO
    //#include <unistd.h> 符号常量
    //#include <arpa/inet.h> 因特网定义
    //#include <net/if.h> 套接字本地接口
    //#include <netinet/in.h> 因特网地址族
    //#include <netinet/tcp.h> 传输控制协议定义
    //#include <sys/mman.h> 存储管理声明
    //#include <sys/select.h> select函数
    //#include <sys/socket.h> 套接字接口
    //#include <sys/stat.h> 文件状态
    //#include <sys/statvfs.h> 文件系统信息
    //#include <sys/times.h> 进程时间
    //#include <sys/types.h> 基本系统数据类型
    //#include <sys/un.h> UNIX域套接字定义
    //#include <sys/utsname.h> 系统名
    //#include <sys/wait.h> 进程控制
    //-------------------------------------
    //POSIX标准定义的XSI可选头文件
    //#include <ftw.h> 文件树漫游
    //#include <libgen.h> 路径名管理函数
    //#include <search.h> 搜索表
    //#include <syslog.h> 系统出错日志记录
    //#include <sys/ipc.h> ipc
    //#include <sys/msg.h> XSI的消息队列
    //#include <sys/resource.h> 资源操作
    //#include <sys/sem.h> XSI信号量
    //#include <sys/shm.h> XSI共享存储
    //#include <sys/time.h> 时间类型
    //#include <sys/uio.h> 矢量IO操作
    //-------------------------------------
    //POSIX标准定义的可选头文件
    //#include <spawn.h> 实时spawn接口
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterTwoJni_isocLimits
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwoJni isocLimits.");
    //ISO C编译时限制都列在了头文件<limits.h>
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwoJni CHAR_BIT=%d", CHAR_BIT);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwoJni CHAR_MAX=%d", CHAR_MAX);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwoJni CHAR_MIN=%d", CHAR_MIN);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwoJni INT_MAX=%d", INT_MAX);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwoJni INT_MIN=%d", INT_MIN);
    //在一个多字节字符常量中的最大字节数
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwoJni MB_LEN_MAX=%d", MB_LEN_MAX);
    //<stdio.h>
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwoJni FOPEN_MAX=%d", FOPEN_MAX);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwoJni FOPEN_MAX=%d", TMP_MAX);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwoJni FOPEN_MAX=%d", FILENAME_MAX);
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterTwoJni_posixLimits
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwoJni posixLimits.");
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwoJni posixLimits=%d.", _POSIX_ARG_MAX);
    long i = sysconf(_SC_ATEXIT_MAX);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwoJni _SC_ATEXIT_MAX=%ld.", i);
    i = sysconf(_SC_ARG_MAX);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwoJni _SC_ARG_MAX=%ld.", i);
    i = sysconf(_SC_THREAD_THREADS_MAX);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwoJni _SC_THREAD_THREADS_MAX=%ld.", i);
    char *error = strerror(errno);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwoJni error=%s", error);
}
static void pr_sysconf(char *, int);
static void pr_pathsconf(char *, char *, int);

#ifdef __cplusplus
}
#endif