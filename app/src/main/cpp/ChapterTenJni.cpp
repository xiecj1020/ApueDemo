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
#include <signal.h>

#include "include/com_crab_test_apuedemo_jni_ChapterTenJni.h"

#define TAG "mytag"

#ifdef __cplusplus
extern "C" {
#endif
/*on handler for both signals*/
static void sig_usr(int);
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterTenJni_signal
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTenJni signal pid=%d.",getpid());
    if(signal(SIGUSR1,sig_usr)==SIG_ERR){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "signal SIGUSR1 error.");
        return;
    }
    //kill -USR2 pid
    if(signal(SIGUSR2,sig_usr)==SIG_ERR){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "signal SIGUSR2 error.");
        return;
    }
    //kill pid
    if(signal(SIGTERM,sig_usr)==SIG_ERR){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "signal SIGTERM error.");
        return;
    }
    //test signal can catch
    //#define SIGHUP 1
    //...
    //#define SIGSYS 31
//    int i;
//    for(i=1;i<=31;i++){
//        if((signal(i,sig_usr)==SIG_ERR)){
//            //#define SIGKILL 9
//            //#define SIGSTOP 19
//            __android_log_print(ANDROID_LOG_ERROR, TAG, "signal %d error.",i);
//        }
//    }
}
static void sig_usr(int signo){
    if(signo==SIGUSR1){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "receive SIGUSR1.");
    }else if(signo==SIGUSR2){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "receive SIGUSR2.");
    }
    else if(signo==SIGTERM){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "receive SIGTERM.");
    }else{
        __android_log_print(ANDROID_LOG_ERROR, TAG, "receive signal = %d.",signo);
    }
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterTenJni_kill
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTenJni kill pid=%d.",getpid());
    //kill self
    //if(kill(getpid(),SIGTERM)<0){
    //    __android_log_print(ANDROID_LOG_ERROR, TAG, "kill SIGTERM error.");
    //}
    if(kill(getpid(),0)<0){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "kill 0 error.");
    }
}
static void sig_alarm(int signo){
    if(signo==SIGALRM){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "receive  alarm signal pid=%d.",getpid());
    }else{
        __android_log_print(ANDROID_LOG_ERROR, TAG, "receive signal = %d, pid=%d.",signo,getpid());
    }
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterTenJni_alarm
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterTenJni alarm pid=%d.",getpid());
    if(signal(SIGALRM,sig_alarm)==SIG_ERR){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "SIGALRM error.");
        return;
    }
    unsigned int i = alarm(2);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "i=%d.",i);
}
#ifdef __cplusplus
}
#endif