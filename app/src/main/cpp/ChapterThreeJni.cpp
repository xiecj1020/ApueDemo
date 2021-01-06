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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#ifndef TIOCGWINSZ
#include <sys/ioctl.h>
#endif
#include "include/com_crab_test_apuedemo_jni_ChapterThreeJni.h"

#define TAG "mytag"

#ifdef __cplusplus
extern "C" {
#endif
char buff1[] = "abcdefghij";
char buff2[] = "ABCDEFGHIJ";
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterThreeJni_createHoleFile
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterThreeJni createHoleFile.");
    int fd;
    if ((fd = creat("/sdcard/file.hole", S_IRWXU)) < 0) {
        char *err = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterThreeJni create error=%s.", err);
        return;
    }
    if (write(fd, buff1, 10) != 10) {
        char *err = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterThreeJni write error=%s.", err);
        return;
    }
    if (lseek(fd, 16384, SEEK_SET) == -1) {
        char *err = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterThreeJni lseek error=%s.", err);
        return;
    }
    if (write(fd, buff2, 10) != 10) {
        char *err = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterThreeJni write error=%s.", err);
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterThreeJni close fd=%d.", fd);
    close(fd);
}


#define TEST_FILE_SIZE 516581760

JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterThreeJni_ioEfficiency
        (JNIEnv *env, jclass classz, jint bufferSize) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterThreeJni ioEfficiency bufferSize=%d.",
                        bufferSize);
    int rFd, wFd;
    int n, i;
    //first write
    __android_log_print(ANDROID_LOG_ERROR, TAG, "write from.txt start.");
    rFd = open("/sdcard/from.txt", O_RDWR | O_CREAT, S_IRWXU);
    if (rFd < 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "can't open from.txt");
        return;
    }
    char buff[bufferSize];
    for (i = 0; i < bufferSize; i++) {
        buff[i] = 'A';
    }
    int count = TEST_FILE_SIZE / bufferSize;
    int mode = TEST_FILE_SIZE % bufferSize;
    for (i = 0; i < count; i++) {
        if (write(rFd, buff, bufferSize) != bufferSize) {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "write from.txt error");
            break;
        }
    }
    if (write(rFd, buff, mode) != mode) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "write from.txt error");
    }
    close(rFd);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "write from.txt end.");
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterThreeJni ioEfficiency test start");
    rFd = open("/sdcard/from.txt", O_RDWR | O_CREAT, S_IRWXU);
    if (rFd < 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "can't open from.txt");
        return;
    }
    wFd = open("/sdcard/to.txt", O_RDWR | O_CREAT, S_IRWXU);
    if (wFd < 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "can't open to.txt");
        return;
    }
    while ((n = read(rFd, buff, bufferSize)) > 0) {
        if (write(wFd, buff, n) != n) {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "write error");
            break;
        }
    }
    if (n < 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "read error");
    }
    close(rFd);
    close(wFd);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterThreeJni ioEfficiency test end");
}

JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterThreeJni_fcntl
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterThreeJni fcntl");
    int fd, val;
    if ((fd = creat("/sdcard/fcntl.txt", S_IRWXU)) < 0) {
        char *err = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterThreeJni create error=%s.", err);
        return;
    }
    if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
        char *err = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fcntl error=%s for fd=%d", err, fd);
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "fcntl val=%d", val);
    switch (val & O_ACCMODE) {
        case O_RDONLY:
            __android_log_print(ANDROID_LOG_ERROR, TAG, "read only");
            break;
        case O_WRONLY:
            __android_log_print(ANDROID_LOG_ERROR, TAG, "write only");
            break;
        case O_RDWR:
            __android_log_print(ANDROID_LOG_ERROR, TAG, "read and write");
            break;
        default:
            __android_log_print(ANDROID_LOG_ERROR, TAG, "unknown access mode.");
    }
    if (val & O_APPEND) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "append");
    }
    if (val & O_NONBLOCK) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "noblocking");
    }
    if (val & O_SYNC) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "sync writes");
    }
    close(fd);
}
static void pr_winsize(int fd){
    struct winsize size;
    if(ioctl(fd,TIOCGWINSZ,&size)<0){
        char *err = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "ioctl error=%s.", err);
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "rows=%d cols=%d",size.ws_row,size.ws_col);
}
static void sign_winch(int signo){
    __android_log_print(ANDROID_LOG_ERROR, TAG, "SIGNWINCH received.");
    pr_winsize(STDIN_FILENO);
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterThreeJni_ioctl
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterThreeJni ioctl");
    if(isatty(STDIN_FILENO)){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "isatty return.");
        return;
    }
    if(signal(SIGWINCH,sign_winch)==SIG_ERR){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "signal error.");
        return;
    }
    pr_winsize(STDIN_FILENO);
}
#ifdef __cplusplus
}
#endif