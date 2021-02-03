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
#include <sys/time.h>
#include <sys/resource.h>

#include "include/com_crab_test_apuedemo_jni_ChapterSevenJni.h"

#define TAG "mytag"

#ifdef __cplusplus
extern "C" {
#endif
static void my_exit() {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "myexit handler.");
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterSevenJni_atexit
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterSevenJni atexit.");
    atexit(my_exit);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "atexit done.");
    exit(0);
}
extern char **environ;
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterSevenJni_environ
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterSevenJni environ.");
    int i;
    for (i = 0;; i++) {
        char *ptr = *(environ + i);
        if (ptr == NULL) {
            break;
        }
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s", ptr);
    }
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterSevenJni_alloc
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterSevenJni alloc.");
    int nmemb = 4, i = 0;
    int *mallocMethod = (int *) malloc(nmemb * sizeof(int));
    for (i = 0; i < nmemb; i++) {
        int value = *(mallocMethod + i);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "malloc init value=%d", value);
    }
    free(mallocMethod);
    int *callocMethod = (int *) calloc(nmemb, sizeof(int));
    for (i = 0; i < nmemb; i++) {
        int value = *(callocMethod + i);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "calloc init value=%d", value);
    }
    free(callocMethod);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterSevenJni alloc end.");
}
//doit中使用了IOS C的字符串创建符#,以便为每个资源名创建字符串
//比如 doit(RLIMIT_CORE) 将有C预处理程序扩展为:
//pr_limits("RLIMIT_CORE",RLIMIT_CORE)
#define doit(name) pr_limits(#name,name)
static void pr_limits(char *, int);
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterSevenJni_rlimit
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterSevenJni rlimit.");
#ifdef RLIMIT_AS
    doit(RLIMIT_AS);
#endif
    doit(RLIMIT_CORE);
    doit(RLIMIT_CPU);
    doit(RLIMIT_DATA);
    doit(RLIMIT_FSIZE);
#ifdef RLIMIT_MEMLOCK
    doit(RLIMIT_MEMLOCK);
#endif
#ifdef RLIMIT_MSGQUEUE
    doit(RLIMIT_MSGQUEUE);
#endif
#ifdef RLIMIT_NICE
    doit(RLIMIT_NICE);
#endif
    doit(RLIMIT_NOFILE);
#ifdef RLIMIT_NPROC
    doit(RLIMIT_NPROC);
#endif
#ifdef RLIMIT_NPTS
    doit(RLIMIT_NPTS);
#endif
#ifdef RLIMIT_RSS
    doit(RLIMIT_RSS);
#endif
#ifdef RLIMIT_RSS
    doit(RLIMIT_RSS);
#endif
#ifdef RLIMIT_SBSIZE
    doit(RLIMIT_SBSIZE);
#endif
#ifdef RLIMIT_SIGPENDING
    doit(RLIMIT_SIGPENDING);
#endif
    doit(RLIMIT_STACK);
#ifdef RLIMIT_SWAP
    doit(RLIMIT_SWAP);
#endif
#ifdef RLIMIT_VMEM
    doit(RLIMIT_VMEM);
#endif
}
static void pr_limits(char *name,int resource){
    struct rlimit limit;
    unsigned long long lim;
    if(getrlimit(resource,&limit)<0){
        char *errMsg = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "getrlimit error for %s : %s", name,errMsg);
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, " %-14s", name);
    if(limit.rlim_cur==RLIM_INFINITY){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s","(infinity)");
    }else{
        lim = limit.rlim_cur;
        __android_log_print(ANDROID_LOG_ERROR, TAG, " %10lld", lim);
    }
    if(limit.rlim_max==RLIM_INFINITY){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s","(infinity)");
    }else{
        lim = limit.rlim_max;
        __android_log_print(ANDROID_LOG_ERROR, TAG, " %10lld", lim);
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, " ---------------------------------------------");
}
#ifdef __cplusplus
}
#endif