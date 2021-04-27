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
#include <pthread.h>
#include <unistd.h>
#include "include/com_crab_test_apuedemo_jni_ChapterTwelveJni.h"

#define TAG "mytag"

#ifdef __cplusplus
extern "C" {
#endif
//pthread_attr_t 线程属性变量
//pthread_attr_init 初始化属性变量
//pthread_attr_destroy 销毁属性变量
void *thr_fun(void *args) {
    //wait the pthread_create method execute over
    sleep(1);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "thr_fun tid=%ld", pthread_self());
    return (void *) 0;
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterTwelveJni_pthreadAttr
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwelveJni pthreadAttr.");
    pthread_attr_t attr_t;
    pthread_t tid;
    if (pthread_attr_init(&attr_t) != 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "pthread_attr_init error.");
        return;
    }
    if (pthread_attr_setdetachstate(&attr_t, PTHREAD_CREATE_DETACHED) != 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "pthread_attr_setdetachstate error.");
        return;
    }
    int detachState;
    if (pthread_attr_getdetachstate(&attr_t, &detachState) != 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "pthread_attr_getdetachstate error.");
        return;
    }
    switch (detachState) {
        case PTHREAD_CREATE_DETACHED:
            __android_log_print(ANDROID_LOG_ERROR, TAG, "pthreadAttr PTHREAD_CREATE_DETACHED");
            break;
        case PTHREAD_CREATE_JOINABLE:
            __android_log_print(ANDROID_LOG_ERROR, TAG, "pthreadAttr PTHREAD_CREATE_JOINABLE");
            break;
        default:
            __android_log_print(ANDROID_LOG_ERROR, TAG, "pthreadAttr unkown");
    }
    if (pthread_create(&tid, &attr_t, thr_fun, NULL) != 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "pthread_create error.");
        return;
    }
    if (pthread_join(tid, NULL) != 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "pthread_join error.");
    }
    if (pthread_attr_destroy(&attr_t) != 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "pthread_attr_destroy error.");
    }
}
//pthread_mutexattr_t       互斥量属性
//pthread_mutexattr_init    初始化
//pthread_mutexattr_destroy 销毁
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterTwelveJni_mutexAttr
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTwelveJni mutexAttr.");
}
#ifdef __cplusplus
}
#endif