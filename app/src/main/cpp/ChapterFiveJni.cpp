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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "include/com_crab_test_apuedemo_jni_ChapterFiveJni.h"

#define TAG "mytag"

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterFiveJni_fopen
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterFiveJni fopen.");
    const char *fileName = "/sdcard/test.txt";
    //first check the file exist
    if (access(fileName, F_OK) < 0) {
        if (errno != ENOENT) {
            char *errMsg = strerror(errno);
            __android_log_print(ANDROID_LOG_ERROR, TAG, "access %s fail: %s.", fileName, errMsg);
            return;
        }
        //create file.
        int fd = 0;
        if ((fd = creat(fileName, O_CREAT | O_RDWR)) < 0) {
            char *errMsg = strerror(errno);
            __android_log_print(ANDROID_LOG_ERROR, TAG, "creat %s fail: %s.", fileName, errMsg);
            return;
        }
        if (close(fd) < 0) {
            char *errMsg = strerror(errno);
            __android_log_print(ANDROID_LOG_ERROR, TAG, "close %s fail:%s.", fileName, errMsg);
            return;
        }
    }
    //fopen the stream
    FILE *fp = NULL;
    if ((fp = fopen(fileName, "r+")) == NULL) {
        char *errMsg = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fopen %s fail: %s.", fileName, errMsg);
        return;
    }
    //write the stream
    //fputc,fgetc 一次一个字符
    //fputs,fgets 一次一行
    if (fputs("abcd\n", fp) < 0) {
        char *errMsg = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fputs %s fail:%s.", fileName, errMsg);
    }
    if (fputs("efgh\n", fp) < 0) {
        char *errMsg = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fputs %s fail:%s.", fileName, errMsg);
    }
    if (fclose(fp) < 0) {
        char *errMsg = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fclose %s fail:%s.", fileName, errMsg);
    }
    //int pos = fseek(fp,0,SEEK_CUR);
    //__android_log_print(ANDROID_LOG_ERROR, TAG, "%s pos:%d.", fileName, pos);
    //read the stream
    if ((fp = fopen(fileName, "r+")) == NULL) {
        char *errMsg = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fopen %s fail: %s.", fileName, errMsg);
        return;
    }
    char buf[4096];
    while ((fgets(buf, 4096, fp)) != NULL) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "read line:%s", buf);
    }
    if (fclose(fp) < 0) {
        char *errMsg = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fclose %s fail:%s.", fileName, errMsg);
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterFiveJni fopen test end.");
}
#define MAXLINE 4096
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterFiveJni_ioEffective
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterFiveJni ioEffective.");
    char buf[MAXLINE];
    while ((fgets(buf, MAXLINE, stdin)) != NULL) {
        if (fputs(buf, stdout) == EOF) {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "output error");
            break;
        }
    }
    if (ferror(stdin)) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "input error");
    }
    //exit(0);
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterFiveJni_fread
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterFiveJni fread.");
    const char *fileName = "/sdcard/test.txt";
    //first check the file exist
    if (access(fileName, F_OK) < 0) {
        if (errno != ENOENT) {
            char *errMsg = strerror(errno);
            __android_log_print(ANDROID_LOG_ERROR, TAG, "access %s fail: %s.", fileName, errMsg);
            return;
        }
        //create file.
        int fd = 0;
        if ((fd = creat(fileName, O_CREAT | O_RDWR)) < 0) {
            char *errMsg = strerror(errno);
            __android_log_print(ANDROID_LOG_ERROR, TAG, "creat %s fail: %s.", fileName, errMsg);
            return;
        }
        if (close(fd) < 0) {
            char *errMsg = strerror(errno);
            __android_log_print(ANDROID_LOG_ERROR, TAG, "close %s fail:%s.", fileName, errMsg);
            return;
        }
    }
    //fopen the stream
    FILE *fp = NULL;
    if ((fp = fopen(fileName, "wb")) == NULL) {
        char *errMsg = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fopen %s fail: %s.", fileName, errMsg);
        return;
    }
    //write the stream
    //fwrite 二进制流
    float data[10] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
    if (fwrite(&data[2], sizeof(float), 4, fp) != 4) {
        char *errMsg = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fwrite %s fail: %s.", fileName, errMsg);
        return;
    }
    if (fclose(fp) < 0) {
        char *errMsg = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fclose %s fail:%s.", fileName, errMsg);
    }
    //read the stream
    //fread 二进制流
    if ((fp = fopen(fileName, "rb")) == NULL) {
        char *errMsg = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fopen %s fail: %s.", fileName, errMsg);
        return;
    }
    float buf[10];
    if (fread(buf, sizeof(float), 4, fp) != 4) {
        char *errMsg = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fread %s fail:%s.", fileName, errMsg);
        return;
    }
    int i = 0;
    for (i = 0; i < 4; i++) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fread : %f", buf[i]);
    }
    if (fclose(fp) < 0) {
        char *errMsg = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fclose %s fail:%s.", fileName, errMsg);
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterFiveJni fopen test end.");
}
#ifdef __cplusplus
}
#endif