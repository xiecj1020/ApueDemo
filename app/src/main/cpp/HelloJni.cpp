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
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "include/com_crab_test_apuedemo_jni_HelloJni.h"
#define TAG "mytag"
#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_HelloJni_sayHello
        (JNIEnv *env, jclass clazz){
#ifdef __ANDROID__
    __android_log_print(ANDROID_LOG_ERROR, TAG, "define __ANDROID__.");
#else
    __android_log_print(ANDROID_LOG_ERROR, TAG, "don't define __ANDROID__.");
#endif

    __android_log_print(ANDROID_LOG_ERROR, TAG, "Native say Hello World.");

    const char* cmd = "/data/user/0/com.crab.test.apuedemo/cache/testcp";
    int result = execl(cmd,"testcp","-fpr","/data/user/0/com.crab.test.apuedemo/cache/*","/data/user/0/com.crab.test.apuedemo/cache/cp/",NULL);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "execl result=%d.",result);
    char *errMsg = strerror(errno);
    __android_log_print(ANDROID_LOG_ERROR, TAG,"Failed starting command %s, fail msg:%s\n", "testcp",errMsg);

}
#ifdef __cplusplus
}
#endif