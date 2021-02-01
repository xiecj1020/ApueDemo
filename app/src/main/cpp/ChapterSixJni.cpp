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
#include <pwd.h>
#include <grp.h>
#include <stddef.h>
#include <sys/utsname.h>
#include <time.h>
#include <sys/time.h>

#include "include/com_crab_test_apuedemo_jni_ChapterSixJni.h"

#define TAG "mytag"

#ifdef __cplusplus
extern "C" {
#endif
struct passwd *getpwnam(const char *name) {
    struct passwd *ptr;
//    setpwent();
//    while ((ptr=getpwent)!=null){
//        if(strcmp(nae,ptr->pw_name)==0){
//            break;
//        }
//    }
//    endpwent();
    return ptr;
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterSixJni_getpwnam
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterFiveJni getpwnam.");
    //getpwnam("user");
    struct passwd *pw = getpwuid(getuid());
    __android_log_print(ANDROID_LOG_ERROR, TAG, "pw_name =%s.", pw->pw_name);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "pw_passwd =%s.", pw->pw_passwd);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "pw_uid =%d.", pw->pw_uid);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "pw_gid =%d.", pw->pw_gid);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "pw_dir =%s.", pw->pw_dir);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "pw_shell =%s.", pw->pw_shell);

    struct group *gr = getgrgid(getgid());
    __android_log_print(ANDROID_LOG_ERROR, TAG, "gr_name =%s.", gr->gr_name);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "gr_passwd =%s.", gr->gr_passwd);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "gr_gid =%d.", gr->gr_gid);
    if (gr->gr_mem != NULL) {
        int i = 0;
        for (i = 0;; i++) {
            char *ptr = *(gr->gr_mem + i);
            if (ptr == NULL) {
                break;
            }
            __android_log_print(ANDROID_LOG_ERROR, TAG, "ptr =%s.", ptr);
        }
    }
}

JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterSixJni_uname
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterFiveJni uname.");
    struct utsname buf;
    int ret = uname(&buf);
    if (ret < 0) {
        char *errMsg = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "uname fail:%s.", errMsg);
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "domainname =%s.", buf.domainname);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "machine =%s.", buf.machine);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "nodename =%s.", buf.nodename);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "release =%s.", buf.release);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "sysname =%s.", buf.sysname);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "version =%s.", buf.version);
}
//各个时间函数的关系
/*************************************内核**********************************/
/******                                /|\                             ********/
/******  gettimeofday                time                    clock_gettime ******/
/******     |                          |                        |          ******/
/******  timeval    -> tv_sec        time_t            tv_sec <- timespec       ******/
/*********************************     |       *******************************/
/***************     gmtime  localtime(下箭头)|mktime(上箭头)  ***************************/
/*********************************    struct tm  *****************************/
/**        |(右上角箭头)                        |(右下角箭头)                          **/
/**     strptime                        strftime/strftime1      **/
/**     字符串                                             格式化字符串          **/
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterSixJni_time
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterFiveJni time.");
    //UTC 1970年1月1日 00:00:00这一特定时间经过的秒数
    time_t time1 = time(NULL);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "time1=%ld.", time1);
    struct timespec tp;
    if (clock_gettime(CLOCK_REALTIME, &tp) < 0) {
        char *errMsg = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "clock_gettime fail:%s.", errMsg);
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "clock_gettime tv_sec=%ld.", tp.tv_sec);
    if (clock_getres(CLOCK_REALTIME, &tp) < 0) {
        char *errMsg = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "clock_gettime fail:%s.", errMsg);
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "clock_getres tv_sec=%ld.", tp.tv_sec);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "clock_getres tv_nsec=%ld.", tp.tv_nsec);
    struct timeval tv;
    if (gettimeofday(&tv, NULL) < 0) {
        char *errMsg = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "gettimeofday fail:%s.", errMsg);
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "gettimeofday tv_sec=%ld.", tv.tv_sec);
    struct tm *tm1 = localtime(&(tv.tv_sec));
    __android_log_print(ANDROID_LOG_ERROR, TAG, "gmtime tm_zone=%s.", tm1->tm_zone);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "gmtime tm_gmtoff=%ld.", tm1->tm_gmtoff);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "gmtime tm_isdst=%d.", tm1->tm_isdst);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "gmtime tm_yday=%d.", tm1->tm_yday);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "gmtime tm_wday=%d.", tm1->tm_wday);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "gmtime tm_year=%d.", tm1->tm_year);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "gmtime tm_mon=%d.", tm1->tm_mon);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "gmtime tm_mday=%d.", tm1->tm_mday);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "gmtime tm_hour=%d.", tm1->tm_hour);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "gmtime tm_min=%d.", tm1->tm_min);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "gmtime tm_sec=%d.", tm1->tm_sec);
}
/**
 *     %a     The abbreviated name of the day of the week according to the current locale. e.g:Thu

       %A     The full name of the day of the week according to the current locale.        e.g:Thursday

       %b     The abbreviated month name according to the current locale.                  e.g:Jan

       %B     The full month name according to the current locale.                         e.g:January

       %c     The preferred date and time representation for the current locale.           e.g:Thu Jan 19 21:24:52 2012

       %C     The century number (year/100) as a 2-digit integer. (SU)                     e.g:20

       %d     The day of the month as a decimal number (range 01 to 31).                   e.g:19

       %D     Equivalent to %m/%d/%y.  (Yecch—for Americans only.  Americans should note that in other countries %d/%m/%y is rather common.  This means that in international context this  format  is
              ambiguous and should not be used.) (SU)                                      e.g:01/19/12 (MM/DD/YY)

       %e     Like %d, the day of the month as a decimal number, but a leading zero is replaced by a space. (SU) e.g:19 (一位数字前加空格)

       %E     Modifier: use alternative format, see below. (SU)

       %F     Equivalent to %Y-%m-%d (the ISO 8601 date format). (C99)                     e.g:2012-01-19 (YYYY-MM-DD)

       %G     The  ISO 8601  week-based year (see NOTES) with century as a decimal number.  The 4-digit year corresponding to the ISO week number (see %V).  This has the same format and value as %Y,
              except that if the ISO week number belongs to the previous or next year, that year is used instead. (TZ)  e.g:2012

       %g     Like %G, but without century, that is, with a 2-digit year (00-99). (TZ)     e.g:12

       %h     Equivalent to %b.  (SU)                                                     e.g:Jan

       %H     The hour as a decimal number using a 24-hour clock (range 00 to 23).        e.g:21

       %I     The hour as a decimal number using a 12-hour clock (range 01 to 12).        e.g:09

       %j     The day of the year as a decimal number (range 001 to 366).                 e.g:019

       %k     The hour (24-hour clock) as a decimal number (range 0 to 23); single digits are preceded by a blank.  (See also %H.)  (TZ)

       %l     The hour (12-hour clock) as a decimal number (range 1 to 12); single digits are preceded by a blank.  (See also %I.)  (TZ)

       %m     The month as a decimal number (range 01 to 12).                            e.g:01

       %M     The minute as a decimal number (range 00 to 59).                           e.g:24

       %n     A newline character. (SU)                                                  e.g:换行符

       %O     Modifier: use alternative format, see below. (SU)

       %p     Either "AM" or "PM" according to the given time value, or the corresponding strings for the current locale.  Noon is treated as "PM" and midnight as "AM". e.g:PM

       %P     Like %p but in lowercase: "am" or "pm" or a corresponding string for the current locale. (GNU)

       %r     The time in a.m. or p.m. notation.  In the POSIX locale this is equivalent to %I:%M:%S %p.  (SU) 本地时间(12小时制) e.g:09:24:52 PM

       %R     The time in 24-hour notation (%H:%M).  (SU) For a version including the seconds, see %T below. e.g:21:24 与(%H:%M)相同

       %s     The number of seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC). (TZ)

       %S     The second as a decimal number (range 00 to 60).  (The range is up to 60 to allow for occasional leap seconds.) e.g:52

       %t     A tab character. (SU) 水平制表符

       %T     The time in 24-hour notation (%H:%M:%S).  (SU)                                                 e.g:21:24:52 PM

       %u     The day of the week as a decimal, range 1 to 7, Monday being 1.  See also %w.  (SU)            e.g:4

       %U     The week number of the current year as a decimal number, range 00 to 53, starting with the first Sunday as the first day of week 01.  See also %V and %W. e.g:03 星期日的周数

       %V     The ISO 8601 week number (see NOTES) of the current year as a decimal number, range 01 to 53, where week 1 is the first week that has at least 4 days in the new year.  See also %U  and
              %W.  (SU) e.g:03 星期日的周数

       %w     The day of the week as a decimal, range 0 to 6, Sunday being 0.  See also %u.                  e.g:01 周几,(0=Sunday,0~6)

       %W     The week number of the current year as a decimal number, range 00 to 53, starting with the first Monday as the first day of week 01. e.g:03 星期一的周数

       %x     The preferred date representation for the current locale without the time. e.g:01/19/12 本地日期

       %X     The preferred time representation for the current locale without the date. e.g:21:24:52 本地时间

       %y     The year as a decimal number without a century (range 00 to 99).          e.g:12 年的最后两位数字

       %Y     The year as a decimal number including the century.                       e.g:2012

       %z     The +hhmm or -hhmm numeric timezone (that is, the hour and minute offset from UTC). (SU)

       %Z     The timezone name or abbreviation.                                        e.g:EST 时区名字

       %+     The date and time in date(1) format. (TZ) (Not supported in glibc2.)

       %%     A literal '%' character.                                                  翻译为1个%
 */
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterSixJni_strftime
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterFiveJni strftime.");
    time_t t;
    struct tm *tmp;
    char buf1[16];
    char buf2[64];
    time(&t);
    tmp = localtime(&t);
    if (strftime(buf1, 16, "time and date: %r, %a %b %d, %Y", tmp) == 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "buff length 16 is too small.");
    } else {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s", buf1);
    }
    if (strftime(buf2, 64, "time and date: %r, %a %b %d, %Y", tmp) == 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "buff length 16 is too small.");
    } else {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s", buf2);
    }
}
#ifdef __cplusplus
}
#endif