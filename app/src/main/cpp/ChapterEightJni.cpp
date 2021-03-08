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
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/times.h>
#include <signal.h>

#include "include/com_crab_test_apuedemo_jni_ChapterEightJni.h"

#define TAG "mytag"

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterEightJni_test
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterEightJni test.");
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterEightJni_processId
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterEightJni processId.");
    //调用进程的pid
    __android_log_print(ANDROID_LOG_ERROR, TAG, "pid =%d.", getpid());
    //调用进程的父进程id
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ppid =%d.", getppid());
    //调用进程的实际用户id
    __android_log_print(ANDROID_LOG_ERROR, TAG, "uid =%d.", getuid());
    //调用进程的有效用户id
    __android_log_print(ANDROID_LOG_ERROR, TAG, "euid =%d.", geteuid());
    //调用进程的实际组id
    __android_log_print(ANDROID_LOG_ERROR, TAG, "gid =%d.", getgid());
    //调用进程的有效组id
    __android_log_print(ANDROID_LOG_ERROR, TAG, "egid =%d.", getegid());
}
int globalvar = 6;
char buf[] = "a write to stdout.";
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterEightJni_fork
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterEightJni fork.");
    int var;
    pid_t pid;
    __android_log_print(ANDROID_LOG_ERROR, TAG, "%s", buf);
    var = 88;
    __android_log_print(ANDROID_LOG_ERROR, TAG, "%s pid=%d", "before fork",getpid());
    //一般来说,fork之后是父进程还是子进程先执行是不确定的,子进程是父进程的副本，子进程获得父进程数据空间，堆和栈的副本。
    //注意，这是子进程所拥有的副本。父进程与子进程并不共享这些存储空间。子进程与父进程共享正文段。
    if ((pid = fork()) < 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fork error");
        return;
    } else if (pid == 0) {
        //child process
        globalvar++;
        var++;
    } else {
        //parent
        sleep(1);
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, " pid=%d, global=%d, var=%d", getpid(), globalvar,
                        var);
}
//vfork用于创建一个新进程，该进程的目的是exec一个新程序。vfork与fork一样都创建一个子进程
//但是它并不父进程的地址空间复制到子进程中，因为子进程会立即调用exec或者exit，于是也就不会引用改地址空间
//不过在子进程调用exec或者exit之前，他运行在父进程的空间运行。
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterEightJni_vfork
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterEightJni vfork.");
    int var;
    pid_t pid;
    var = 88;
    __android_log_print(ANDROID_LOG_ERROR, TAG, "before vfork pid=%d", getpid());
    if ((pid = vfork()) < 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "vfork error");
        return;
    } else if (pid == 0) {
        //child process,下面代码运行在父进程的空间中
        globalvar++;
        var++;
        //需要调用exit或者exec方法,在调用这两个函数之前子进程依赖父进程的进一步动作，则会导致死锁
        _exit(0);
    } else {
        //parent,vfork不需要等待
        //sleep(2);
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, " pid=%d, global=%d, var=%d", getpid(), globalvar,
                        var);
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterEightJni_exit
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterEightJni exit.");
    //exit,_Exit是ISO定义
    //exit(0);
    //_Exit(0);
    //_exit直接内核调用
    _exit(0);
}
void pr_exit(int status) {
    if (WIFEXITED(status)) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "normal termination,exit status=%d.",
                            WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "abnormal termination,signal number=%d%s.",
                            WTERMSIG(status),
#ifdef WCOREDUMP
                            WCOREDUMP(status) ? "core file generated." : ""
#else
                ""
#endif
        );
    } else if (WIFSTOPPED(status)) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "child stopped,signal number=%d.",
                            WSTOPSIG(status));
    }
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterEightJni_waitTest
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterEightJni waitTest pid=%d",getpid());
    pid_t pid;
    int status;
//    if ((pid = fork()) < 0) {
//        __android_log_print(ANDROID_LOG_ERROR, TAG, "fork error");
//        return;
//    } else if (pid == 0) {
//         //子进程调用exit
//         exit(7);
//    }
//    if(wait(&status)!=pid){
//        __android_log_print(ANDROID_LOG_ERROR, TAG, "wait error 1111");
//        return;
//    }
//    pr_exit(status);


//    if ((pid = fork()) < 0) {
//        __android_log_print(ANDROID_LOG_ERROR, TAG, "fork error");
//        return;
//    } else if (pid == 0) {
//        abort();
//    }
//    if(wait(&status)!=pid){
//        __android_log_print(ANDROID_LOG_ERROR, TAG, "wait error 222 ");
//        return;
//    }
//    pr_exit(status);

    if ((pid = fork()) < 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fork error");
        return;
    } else if (pid == 0) {
        status /= 0;
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "wait pid=%d getpid=%d",pid,getpid());
    if(wait(&status)!=pid){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "wait error 3333 pid=%d",getpid());
        return;
    }
    pr_exit(status);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterEightJni waitpid end.");
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterEightJni_waitpid
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterEightJni waitpid current pid=%d",getpid());
    pid_t pid;
    if ((pid = fork()) < 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fork error");
        return;
    }else if(pid==0){
        //child process
        if ((pid = fork()) < 0) {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "fork error");
            return;
        }else if(pid>0){
            //parent process
            exit(0);
        }
        //休眠2秒保证子进程比父进程晚执行
        sleep(2);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "second child,parent pid=%d",getppid());
        exit(0);
    }
    //wait for first child
    __android_log_print(ANDROID_LOG_ERROR, TAG, "waitpid 1111 current pid=%d",getpid());
    if(waitpid(pid,NULL,0)!=pid){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "waitpid error");
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterEightJni waitpid end");
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterEightJni_waitid
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterEightJni waitid current pid=%d",getpid());
    pid_t pid;
    if ((pid = fork()) < 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fork error");
        return;
    }else if(pid==0) {
        //child process
        sleep(1);
        _exit(0);
    }
    if(waitid(P_PID,pid,NULL,WEXITED)<0){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "waitid error");
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterEightJni waitid current pid=%d end.",getpid());
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterEightJni_wait4
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterEightJni wait4 current pid=%d",getpid());
    pid_t pid;
    if ((pid = fork()) < 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fork error");
        return;
    }else if(pid==0) {
        //child process
        sleep(1);
        _exit(0);
    }
    int status;
    struct rusage tr;
    if(wait4(pid,&status,0,&tr)!=pid){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "wait4 error");
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "system time=%ld,user time=%ld",tr.ru_stime.tv_sec,tr.ru_utime.tv_sec);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterEightJni wait4 current pid=%d end",getpid());
}
//如果子进程需要等待父进程终止，可以采用下面轮询，但是浪费了CPU时间，因为调用者每隔1秒就会被唤醒
//while(getppid()!=1){
//    sleep(1);
//}
static void charatattime(const char*);
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterEightJni_competition
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterEightJni competition current pid=%d",getpid());
    pid_t pid;
    if ((pid = fork()) < 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fork error");
        return;
    }else if(pid==0) {
        //child process
        charatattime("output from child");
    }else{
        //parent
        charatattime("output from parent");
    }
}
static void charatattime(const char *str){
    int length = strlen(str);
    int i =0;
    for(i=0;i<length;i++){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%c",*(str+i));
    }
}

//int execl(const char *path, const char *arg, ... /* (char  *) NULL */);
//int execlp(const char *file, const char *arg, .../* (char  *) NULL */);
//int execle(const char *path, const char *arg, .../*, (char *) NULL, char * const envp[] */);
//int execv(const char *path, char *const argv[]);
//int execvp(const char *file, char *const argv[]);
//int execvpe(const char *file, char *const argv[],char *const envp[]);
//字母l代表列表(变长参数),v代表矢量(数组),p代表是文件还是路径,e代表环境变量

JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterEightJni_exec
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterEightJni exec current pid=%d",getpid());

    pid_t pid;
    if ((pid = fork()) < 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fork error");
        return;
    }else if(pid==0) {
        //child process
        int n = execl("cat","cat","/sdcard/test.txt",NULL);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "child exec error pid=% n=%d",getpid(),n);
        char *errMsg = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "execl %s fail: %s.", errMsg);
        _exit(0);
    }else{
        //parent
        if(waitpid(pid,NULL,0)<0){
            __android_log_print(ANDROID_LOG_ERROR, TAG, "waitpid error");
        }
        __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterEightJni exec current pid=%d end",getpid());
    }
}


#define bufsize 20
unsigned long long count;
struct timeval end;
void checktime(char *str){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    if (tv.tv_sec >= end.tv_sec && tv.tv_usec >= end.tv_usec){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s count = %lld",str, count);
        exit(0);
    }
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterEightJni_nice
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterEightJni nice current pid=%d", getpid());
    pid_t pid;
    char *s;
    int nzero, ret;
    int adj = 8;
    setbuf(stdout, NULL);
#if defined(NZERO)
    nzero = NZERO;
#elif defined(_SC_NZERO)
    nzero = sysconf(_SC_NZERO);
#else
#error NZERO undefined
#endif
    __android_log_print(ANDROID_LOG_ERROR, TAG, "NZERO = %d", nzero);
    gettimeofday(&end, NULL);
    end.tv_sec += 10; /* run for 10 seconds */
    if ((pid = fork()) < 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "fork error");
        return;
    } else if (pid == 0) { /* child */
        s = "child";
        __android_log_print(ANDROID_LOG_ERROR, TAG,
                            "current nice value in child is %d, adjusting by %d", nice(0) + nzero,
                            adj);
        errno = 0;
        if ((ret = nice(adj)) == -1 && errno != 0){
            __android_log_print(ANDROID_LOG_ERROR, TAG,"child set scheduling priority");
            return;
        }
        __android_log_print(ANDROID_LOG_ERROR, TAG,"now child nice value is %d", ret + nzero);
        __android_log_print(ANDROID_LOG_ERROR, TAG,"current nice value in child is %d, adjusting by %d", nice(0) + nzero, adj);
    } else { /* parent */
        s = "parent";
        __android_log_print(ANDROID_LOG_ERROR, TAG,"current nice value in parent is %d getpriority=%d", nice(0) + nzero,getpriority(PRIO_PROCESS,getpid()));
    }
    //for (;;) {
    //    if (++count == 0)
    //        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s counter wrap", s);
    //   checktime(s);
    //}
}
static void pr_times(clock_t, struct tms *, struct tms *);
static void do_cmd(const char *);
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterEightJni_times
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterEightJni process times current pid=%d", getpid());
    do_cmd("sleep 3");
    do_cmd("date");
    do_cmd("dumpsys window > /dev/null");
}
static void do_cmd(const char* cmd){
    struct tms tmstart,tmsend;
    clock_t  start,end;
    int status;
    __android_log_print(ANDROID_LOG_ERROR, TAG, "      command:%s", cmd);
    if((start=times(&tmstart))==-1){
        __android_log_print(ANDROID_LOG_ERROR, TAG,"times start error.");
        return;
    }
    if((status=system(cmd))<0){
        __android_log_print(ANDROID_LOG_ERROR, TAG,"system error.");
        return;
    }
    if((end=times(&tmsend))==-1){
        __android_log_print(ANDROID_LOG_ERROR, TAG,"times end error.");
        return;
    }
    pr_times(end-start,&tmstart,&tmsend);
    pr_exit(status);
}
static void pr_times(clock_t real,struct tms *timestart,struct tms *timeend){
    static long clktck = 0;
    if(clktck==0){
        //fetch clock ticks per second first time
        if((clktck=sysconf(_SC_CLK_TCK))<0){
            __android_log_print(ANDROID_LOG_ERROR, TAG,"sys config error.");
            return;
        }
        __android_log_print(ANDROID_LOG_ERROR, TAG,"clktck=%ld.",clktck);
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG,"      real:   %7.2f",real/(double)clktck);
    __android_log_print(ANDROID_LOG_ERROR, TAG,"      user:   %7.2f",(timeend->tms_utime-timestart->tms_utime)/(double)clktck);
    __android_log_print(ANDROID_LOG_ERROR, TAG,"       sys:   %7.2f",(timeend->tms_stime-timestart->tms_stime)/(double)clktck);
    __android_log_print(ANDROID_LOG_ERROR, TAG,"child user:   %7.2f",(timeend->tms_cutime-timestart->tms_cutime)/(double)clktck);
    __android_log_print(ANDROID_LOG_ERROR, TAG,"child  sys:   %7.2f",(timeend->tms_cstime-timestart->tms_cstime)/(double)clktck);
}
#ifdef __cplusplus
}
#endif