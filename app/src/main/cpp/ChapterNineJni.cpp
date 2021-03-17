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

#include "include/com_crab_test_apuedemo_jni_ChapterNineJni.h"

#define TAG "mytag"

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterNineJni_processGroupId
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterNineJni processGroupId.");
    __android_log_print(ANDROID_LOG_ERROR, TAG, "getpgrp=%d.",getpgrp());
}
static void sig_hup(int signo){
    __android_log_print(ANDROID_LOG_ERROR, TAG, "SIGHUP received,pid =%d.",getpid());
}
static void pr_ids(const char * name){
    __android_log_print(ANDROID_LOG_ERROR, TAG, "%s: pid=%d,ppid=%d,pgrp=%d,tpgrp=%d ",name,
            getpid(),getppid(),getpgrp(),tcgetpgrp(STDIN_FILENO));
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterNineJni_orphanProcessGroup
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterNineJni orphanProcessGroup.");
    char c;
    pid_t pid;
    pr_ids("parent");
    if((pid=fork())<0){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fork error.");
        return;
    }else if(pid>0){
        //parent
        sleep(3);
    } else{
        //child
        pr_ids("child");
        signal(SIGHUP,sig_hup);
        kill(getpid(),SIGTSTP);
        pr_ids("child");
        if(read(STDIN_FILENO,&c,1)!=1){
            char *errMsg = strerror(errno);
            __android_log_print(ANDROID_LOG_ERROR, TAG, "read fail:%s.", errMsg);
        }
    }
    _exit(0);
}
#ifdef __cplusplus
}
#endif