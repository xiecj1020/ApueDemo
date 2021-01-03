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
#include <dirent.h>
#include <unistd.h>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include "include/com_crab_test_apuedemo_jni_ChapterOneJni.h"

#define TAG "mytag"

#ifdef __cplusplus
extern "C" {
#endif
//ls example
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterOneJni_ls
        (JNIEnv *env, jclass clazz, jstring path) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterOneJni ls.");
    const char *cPath = env->GetStringUTFChars(path, 0);
    DIR *dp;
    struct dirent *dirp;
    if ((dp = opendir(cPath)) == nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "can't open %s", cPath);
        return;
    }
    while ((dirp = readdir(dp)) != nullptr) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s\n", dirp->d_name);
    }
    env->ReleaseStringUTFChars(path, cPath);
}
//io example
#define BUFFSIZE 4096
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterOneJni_io
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterOneJni io.");
    int n;
    char buf[BUFFSIZE];
    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "write error");
            exit(EXIT_FAILURE);
        }
    }
    if (n < 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "read error");
        exit(EXIT_FAILURE);
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterOneJni end.");
    //exit(EXIT_SUCCESS);
}
//printPid example
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterOneJni_printPid
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterOneJni printPid.");
    __android_log_print(ANDROID_LOG_ERROR, TAG, "this app pid is %ld.", (long) getpid());
}
//perror example
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterOneJni_perror
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterOneJni perror.");
    errno = ENOENT;
    perror("perror test");
}
//printUidAndGid example
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterOneJni_printUidAndGid
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterOneJni printUidAndGid.");
    __android_log_print(ANDROID_LOG_ERROR, TAG, "native uid=%d, gid=%d", getuid(), getgid());
}
//signal example
#define MAXLINE 1000
static void sig_int(int signal);
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterOneJni_signal
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterOneJni signal.");
    char buf[MAXLINE];
    pid_t pid;
    int status;
    if (signal(SIGINT, sig_int) == SIG_ERR) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "signal error.");
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "%%");
    while ((fgets(buf, MAXLINE, stdin)) != nullptr) {
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = 0;
        }
        if ((pid = fork()) < 0) {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "fork error");
            return;
        } else if (pid == 0) {
            execlp(buf, buf, (char *) 0);
            __android_log_print(ANDROID_LOG_ERROR, TAG, "can't execute:%s", buf);
            exit(127);
        }
        if ((pid == waitpid(pid, &status, 0)) < 0) {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "wait pid error.");
            return;
        }
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%%");
    }
}
static void sig_int(int signal) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "interrupt\n%%  ");
}
#ifdef __cplusplus
}
#endif