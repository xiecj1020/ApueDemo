#include <android/log.h>
#include "include/com_crab_test_apuedemo_jni_HelloJni.h"
#define TAG "mytag"
#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_HelloJni_sayHello
        (JNIEnv *, jclass){
    __android_log_print(ANDROID_LOG_ERROR, TAG, "Native say Hello World.");
}
#ifdef __cplusplus
}
#endif