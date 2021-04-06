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

//使用gcc和gdb调试步骤
//1.为了能够使用gdb调试程序，在编译阶段加上-g参数，
//2.使用gdb命令调试程序：gdb ./pthread_test1
//3.进入gdb后，运行程序：
//  (gdb) run
//4.完成调试后，输入quit命令退出gdb：
//  (gdb) quit
//编译方法:gcc -g pthread_test1.c -o pthread_test1 -lpthread
#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#include "include/com_crab_test_apuedemo_jni_ChapterElevenJni.h"

#define TAG "mytag"

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterElevenJni_test
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterElevenJni test pid=%d",getpid());
    __android_log_print(ANDROID_LOG_ERROR, TAG, "native thread id=%ld",pthread_self());
}
pthread_t ntid;
void printids(const char *s){
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    __android_log_print(ANDROID_LOG_ERROR, TAG, "%s pid %lu tid %lu (0x%lx)\n",s,(unsigned long)pid,
           (unsigned long)tid,(unsigned long)tid);
}
void *thr_fn(void *arg){
    printids(" new thread: ");
    return ((void*)0);
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterElevenJni_threadCreate
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterElevenJni threadCreate pid=%d",getpid());
    int err;
    //线程属性参数
    pthread_attr_t *attr = NULL;
    //线程执行的函数
    void*(*start_run)(void*) = thr_fn;
    //执行函数的参数
    void *args = NULL;
    err = pthread_create(&ntid,attr,start_run,args);
    if(err!=0){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "can't create thread,the error =% d\n",err);
        return;
    }
    printids("main thread: ");
    __android_log_print(ANDROID_LOG_ERROR, TAG, "threadCreate over.\n");
}
void *thr_fn1(void *args){
    printf("thread 1 returing.\n");
    return ((void*)1);
}
void *thr_fn2(void *args){
    printf("thread 2 exiting.\n");
    pthread_exit((void*)2);
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterElevenJni_threadExit1
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterElevenJni threadExit1 pid=%d", getpid());
    int err;
    pthread_t tid1,tid2;
    void* tret;
    err = pthread_create(&tid1,NULL,thr_fn1,NULL);
    if(err!=0){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Can't create thread 1.\n");
        return;
    }
    err = pthread_create(&tid2,NULL,thr_fn2,NULL);
    if(err!=0){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Can't create thread 2.\n");
        return;
    }
    err = pthread_join(tid1,&tret);
    if(err!=0){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Can't join thread 1.\n");
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "thread 1 exit code is %ld.\n",(long)tret);
    err = pthread_join(tid2,&tret);
    if(err!=0){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Can't join thread 2.\n");
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "thread 2 exit code is %ld.\n",(long)tret);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "main over.\n");
}

struct foo{
    int a,b,c,d;
};
void printfoo(const char *s,const struct foo *fp){
    __android_log_print(ANDROID_LOG_ERROR, TAG,"%s",s);
    __android_log_print(ANDROID_LOG_ERROR, TAG," structure at 0x%lx\n",(unsigned long)fp);
    __android_log_print(ANDROID_LOG_ERROR, TAG," foo.a = %d\n",fp->a);
    __android_log_print(ANDROID_LOG_ERROR, TAG," foo.b = %d\n",fp->b);
    __android_log_print(ANDROID_LOG_ERROR, TAG," foo.c = %d\n",fp->c);
    __android_log_print(ANDROID_LOG_ERROR, TAG," foo.d = %d\n",fp->d);
}
void *thr_fn21(void *args){
    //分配在栈上
    struct foo f = {1,2,3,4};
    printfoo("thread1:\n",&f);
    return ((void*)&f);
}
void *thr_fn22(void *args){
    printf("thread 2 id is %lu.\n",(unsigned long)pthread_self());
    pthread_exit((void*)0);
}

JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterElevenJni_threadExit2
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterElevenJni threadExit2 pid=%d", getpid());
    int err;
    pthread_t tid1,tid2;
    struct foo *fp;
    err = pthread_create(&tid1,NULL,thr_fn21,NULL);
    if(err!=0){
        __android_log_print(ANDROID_LOG_ERROR, TAG,"Can't create thread 1.\n");
        return;
    }
    err = pthread_join(tid1,(void**)&fp);
    if(err!=0){
        __android_log_print(ANDROID_LOG_ERROR, TAG,"Can't join thread 1.\n");
        return;
    }
    sleep(1);
    __android_log_print(ANDROID_LOG_ERROR, TAG,"Parent start thread 2.\n");
    err = pthread_create(&tid2,NULL,thr_fn22,NULL);
    if(err!=0){
        __android_log_print(ANDROID_LOG_ERROR, TAG,"Can't create thread 2.\n");
        return;
    }
    printfoo("parent:\n",fp);
    __android_log_print(ANDROID_LOG_ERROR, TAG,"main over.\n");
}
void cleanup(void *arg) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "cleanup:%s\n", (char *) arg);
}
void *thr_fn31(void *args) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "thread 1 start.\n");
    char *arg1 = "thread 1 first handler";
    pthread_cleanup_push(cleanup, arg1);
        char *arg2 = "thread 1 second handler";
        pthread_cleanup_push(cleanup, arg2);
            __android_log_print(ANDROID_LOG_ERROR, TAG, "thread 1 push complete.\n");
            if (args) {
                __android_log_print(ANDROID_LOG_ERROR, TAG,"thread 1 return.\n");
                return ((void *) 1);
            }
            pthread_cleanup_pop(0);
            pthread_cleanup_pop(0);
    return ((void *) 1);
}
void *thr_fn32(void *args) {
    __android_log_print(ANDROID_LOG_ERROR, TAG,"thread 2 start.\n");
    char *arg1 = "thread 2 first handler";
    pthread_cleanup_push(cleanup, arg1);
        char *arg2 = "thread 2 second handler";
        pthread_cleanup_push(cleanup, arg2);
            __android_log_print(ANDROID_LOG_ERROR, TAG,"thread 2 push complete.\n");
            if (args) {
                __android_log_print(ANDROID_LOG_ERROR, TAG,"thread 2 return.\n");
                pthread_exit((void *) 2);
            }
                pthread_cleanup_pop(0);
            pthread_cleanup_pop(0);
    pthread_exit((void *) 2);
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterElevenJni_threadExit3
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterElevenJni threadExit3 pid=%d", getpid());
    int err;
    pthread_t tid1,tid2;
    void* tret;
    err = pthread_create(&tid1,NULL,thr_fn31,(void*)1);
    if(err!=0){
        __android_log_print(ANDROID_LOG_ERROR, TAG,"Can't create thread 1.\n");
        return;
    }
    err = pthread_create(&tid2,NULL,thr_fn32,(void*)1);
    if(err!=0){
        __android_log_print(ANDROID_LOG_ERROR, TAG,"Can't create thread 2.\n");
        return;
    }
    err = pthread_join(tid1,&tret);
    if(err!=0){
        __android_log_print(ANDROID_LOG_ERROR, TAG,"Can't join thread 1.\n");
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG,"thread 1 exit code is %ld.\n",(long)tret);
    err = pthread_join(tid2,&tret);
    if(err!=0){
        __android_log_print(ANDROID_LOG_ERROR, TAG,"Can't join thread 2.\n");
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG,"thread 2 exit code is %ld.\n",(long)tret);
    __android_log_print(ANDROID_LOG_ERROR, TAG,"main over.\n");
}
//互斥量要么是锁住状态，要么是没锁住状态，一次只有一个线程对其加锁
//如果线程对同一个互斥量加锁两次，将会产生死锁。
//pthread_mutex_t        互斥量变量
//pthread_mutex_init     互斥量初始化
//pthread_mutex_destory  互斥量销毁
//pthread_mutex_lock     互斥量锁定锁
//pthread_mutex_unlock   互斥量释放锁

#define NHASH 29
#define HASH(id) (((unsigned long)id)%NHASH)
struct foo2{
    int fcount;
    pthread_mutex_t flock;
    int fid;
    struct foo2 *fnext;
};
struct foo2 *fh[NHASH];
pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;
struct foo2 *foo_alloc(int id){
    struct foo2 *fp;
    int idx;
    if((fp=(struct foo2*)malloc(sizeof(struct foo2)))!=NULL){
        fp->fcount = 1;
        fp->fid= id;
        if(pthread_mutex_init(&fp->flock,NULL)!=0){
            free(fp);
            return NULL;
        }
        idx = HASH(id);
        pthread_mutex_lock(&hashlock);
        fp->fnext = fh[idx];
        fh[idx] = fp;
        pthread_mutex_lock(&fp->flock);
        pthread_mutex_unlock(&hashlock);
        pthread_mutex_unlock(&fp->flock);
    }
    return fp;
}
void foo_hold(struct foo2 *fp){
    pthread_mutex_lock(&fp->flock);
    fp->fcount++;
    pthread_mutex_unlock(&fp->flock);
}
void foo_rele(struct foo2 *fp){
    pthread_mutex_lock(&fp->flock);
    if(--fp->fcount==0){
        pthread_mutex_unlock(&fp->flock);
        pthread_mutex_destroy(&fp->flock);
        free(fp);
    }else{
        pthread_mutex_unlock(&fp->flock);
    }
}
pthread_mutex_t m;
static void *add(void *args) {
    pthread_mutex_lock(&m);
    int *a = (int *) args;
    int i = 0;
    for (i = 0; i < 1000000; i++) {
        (*a)++;
    }
    pthread_mutex_unlock(&m);
    //这里需要有返回语句，否则程序会崩溃。如果没有return语句，好像返回的地址信息是不确定的
    return ((void*)1);
    //return NULL;
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterElevenJni_threadMutex
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterElevenJni threadMutex pid=%d", getpid());
    pthread_mutex_init(&m,NULL);
    int count = 0;
    int err;
    pthread_t tid1, tid2;
    __android_log_print(ANDROID_LOG_ERROR, TAG, "count=%p\n",&count);
    err = pthread_create(&tid1, NULL, add, &count);
    if (err != 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Can't create thread 1.\n");
        return;
    }
    err = pthread_create(&tid2, NULL, add, &count);
    if (err != 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Can't create thread 2.\n");
        return;
    }
    //等待计算线程1,2执行完毕
    err = pthread_join(tid1,NULL);
    if(err!=0){
        __android_log_print(ANDROID_LOG_ERROR, TAG,"Can't join thread 1.\n");
        return;
    }
    err = pthread_join(tid2,NULL);
    if(err!=0){
        __android_log_print(ANDROID_LOG_ERROR, TAG,"Can't join thread 2.\n");
        return;
    }
    pthread_mutex_destroy(&m);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "count =%d", count);
}
//这个程序故意对它已经有的互斥量加锁，目的是演示pthread_mutex_timedlock是如何工作的。
//不推荐在实际中使用这种策略，因为会导致死锁。
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterElevenJni_threadMutexTimed
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterElevenJni threadMutexTimed pid=%d", getpid());
    struct timespec tout;
    struct tm *tmp;
    int err;
    char buf[64];
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&lock);
    __android_log_print(ANDROID_LOG_ERROR, TAG,"mutex is locked.\n");
    clock_gettime(CLOCK_REALTIME,&tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf,sizeof(buf),"%r",tmp);
    __android_log_print(ANDROID_LOG_ERROR, TAG,"current time is %s.\n",buf);
    tout.tv_sec += 5;
    pthread_t tid1,tid2;
    err = pthread_mutex_timedlock(&lock,&tout);
    clock_gettime(CLOCK_REALTIME,&tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf,sizeof(buf),"%r",tmp);
    __android_log_print(ANDROID_LOG_ERROR, TAG,"the time is now %s.\n",buf);
    if(err==0){
        __android_log_print(ANDROID_LOG_ERROR, TAG,"mutex lock again.\n");
    }else{
        __android_log_print(ANDROID_LOG_ERROR, TAG,"can't mutex lock again:%s.\n",strerror(err));
    }
}
//读写锁有3中状态，读模式下加锁状态，写模式下加锁状态，不加锁状态。
//一次只有一个线程可以占有写模式下的读写锁，但是可以多个线程同时占有读模式下的读写锁。
//pthread_rw_t          读写锁变量
//pthread_rw_init       读写锁初始化
//pthread_rw_destroy    读写锁销毁
//pthread_rw_rdlock     读写锁读状态锁定
//pthread_rw_wrlock     读写锁锁状态锁定
//pthread_rw_unlock     读写锁释放
struct job{
    struct job *j_next;
    struct job *j_prev;
    pthread_t j_id;
    int jobNumber;
};
struct queue{
    struct job* q_head;
    struct job* q_tail;
    pthread_rwlock_t q_lock;
};
int queue_init(struct queue *qp){
    int err;
    qp->q_head = NULL;
    qp->q_tail = NULL;
    err = pthread_rwlock_init(&qp->q_lock,NULL);
    if(err!=0){
        return err;
    }
    return 0;
}
void job_insert(struct queue *qp,struct job *job){
    pthread_rwlock_wrlock(&qp->q_lock);
    job->j_next = qp->q_head;
    job->j_prev = NULL;
    if(qp->q_head!=NULL){
        qp->q_head->j_prev = job;
    }else{
        qp->q_tail = job; //queue is empty
    }
    qp->q_head = job;
    pthread_rwlock_unlock(&qp->q_lock);
}
void job_append(struct queue *qp,struct job *job){
    pthread_rwlock_wrlock(&qp->q_lock);
    job->j_next = NULL;
    job->j_prev = qp->q_tail;
    if(qp->q_tail!=NULL){
        qp->q_tail->j_next = job;
    }else{
        qp->q_head = job; //queue is empty
    }
    pthread_rwlock_unlock(&qp->q_lock);
}
void job_remove(struct queue *qp,struct job *job){
    pthread_rwlock_wrlock(&qp->q_lock);
    if(job==qp->q_head){
        qp->q_head = job->j_next;
        if(qp->q_tail==job){
            qp->q_tail = NULL;
        }else{
            job->j_next->j_prev = job->j_prev;
        }
    }else if(job==qp->q_tail){
        qp->q_tail = job->j_prev;
        job->j_prev->j_next = job->j_next;

    }else{
        job->j_prev->j_next = job->j_next;
        job->j_next->j_prev = job->j_prev;
    }
    pthread_rwlock_unlock(&qp->q_lock);
}
struct job *job_find(struct queue *qp,pthread_t id){
    struct job *jp;
    if(pthread_rwlock_rdlock(&qp->q_lock)!=0){
        return NULL;
    }
    for(jp=qp->q_head;jp!=NULL;jp=jp->j_next){
        if(pthread_equal(jp->j_id,id)){
            break;
        }
    }
    pthread_rwlock_unlock(&qp->q_lock);
    return jp;
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterElevenJni_threadReadWriteLock
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterElevenJni threadReadWriteLock pid=%d", getpid());
    struct queue myQueue;
    int err;
    err = queue_init(&myQueue);
    if(err!=0){
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Can't init queue.");
        return;
    }
    struct job job1;
    job1.j_id = pthread_self();
    job1.jobNumber = 1;
    struct job job2;
    job2.j_id = pthread_self();
    job2.jobNumber = 2;
    job_insert(&myQueue,&job1);
    job_append(&myQueue,&job2);
    struct job *getJob = job_find(&myQueue,pthread_self());
    __android_log_print(ANDROID_LOG_ERROR, TAG, "job number=%d.",getJob->jobNumber);
}
//条件本身是由互斥量保护的，线程在改变条件变量之前必须锁住互斥量。
//pthread_cond_t       条件变量
//pthread_cond_init    条件变量初始化
//pthread_cond_destroy 条件变量销毁
//pthread_cond_wait    等待条件标量变为真
//pthread_cond_timedwait 等待条件标量变为真，带有超时时间
//pthread_cond_signal   至少能够唤醒一个等待该条件的线程
//pthread_cond_broadcast   能够唤醒等待该条件的所有线程
struct msg{
    struct msg *m_next;
};
struct msg *workq;
pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;
int msgCount = 0;
void process_msg(){
    struct msg *mp;
    for(;;){
        pthread_mutex_lock(&qlock);
        //条件是工作队列的状态,用互斥量保护条件,在while循环中判断条件
        while(workq==NULL){
            pthread_cond_wait(&qready,&qlock);
        }
        mp = workq;
        __android_log_print(ANDROID_LOG_ERROR, TAG, "process_msg %p.\n",mp);
        workq = mp->m_next;
        pthread_mutex_unlock(&qlock);
        free(mp);
        //读取2此后停止
        msgCount++;
        if(msgCount==2){
            break;
        }
        sleep(2);
    }
}
void enqueue_msg(struct msg *mp){
    __android_log_print(ANDROID_LOG_ERROR, TAG, "enqueue_msg %p.\n",mp);
    pthread_mutex_lock(&qlock);
    mp->m_next = workq;
    workq = mp;
    pthread_mutex_unlock(&qlock);
    pthread_cond_signal(&qready);
}
void *thr_fn61(void *args){
    struct msg * first_msg = (struct msg*)malloc(sizeof(struct msg));
    enqueue_msg(first_msg);
    sleep(1);
    first_msg = (struct msg*)malloc(sizeof(struct msg));
    enqueue_msg(first_msg);
    return ((void*)1);
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterElevenJni_threadCondition
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterElevenJni threadCondition pid=%d",getpid());
    msgCount = 0;
    pthread_t tid1;
    int err;
    err = pthread_create(&tid1,NULL,thr_fn61,NULL);
    if(err!=0){
        __android_log_print(ANDROID_LOG_ERROR, TAG,"Can't create thread 1.\n");
        return;
    }
    process_msg();
    __android_log_print(ANDROID_LOG_ERROR, TAG,"threadCondition end.\n");
}
//自旋锁与互斥量类似，但它不是休眠使进程阻塞，而是在获取锁之前一直处于忙等(自旋)阻塞状态。
//自旋可以用于以下情况:锁被持有的时间短，而且线程不想再重新调度上花费太多的成本。
//pthread_spinlock_t   自旋变量
//pthread_spin_init    自旋变量初始化
//pthread_spin_destroy 自旋变量销毁
//pthread_spin_lock    自旋加锁
//pthread_spin_trylock 自旋加锁
//pthread_spin_unlock  自旋解锁

pthread_spinlock_t spinlock;
int count = 0;
void *work(void *param) {
    for (int i = 0; i < 10000000; i++) {
        pthread_spin_lock(&spinlock);
        ++count;
        //将会导致问题
        //usleep(0);
        pthread_spin_unlock(&spinlock);
    }
    return NULL;
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterElevenJni_threadSpin
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterElevenJni threadSpin pid=%d",getpid());
    pthread_t pt = 0;
    count = 0;
    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
    pthread_create(&pt, NULL, work, NULL);
    for (int i = 0; i < 10000000; i++){
        pthread_spin_lock(&spinlock);
        ++count;
        pthread_spin_unlock(&spinlock);
    }
    pthread_join(pt, NULL);
    pthread_spin_destroy(&spinlock);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "threadSpin count=%d",count);
}
//屏障是用户协调多个线程并行工作的同步机制。屏障允许每个线程等待，直到所有的合作线程都到达某个点
//然后从该点继续执行。
//pthread_barrier_t    屏障变量
//pthread_barrier_init 屏障变量初始化
//pthread_barrier_destory 屏障变量销毁
//pthread_barrier_wait 表明线程已经完成工作，等待所有线程赶上来

#define NTHR 8
#define NUMNUM 80L
#define TNUM (NUMNUM/NTHR)
long nums[NUMNUM];
long snums[NUMNUM];
pthread_barrier_t b;
//#ifdef SOLARIS
//#define heapsort qsort
//#else
//extern int heapsort(void*,size_t,size_t,int(*)(const void *,const void *));
//#endif

int heapsort(void *base,size_t nel,size_t width,int(*comp)(const void *,const void *)){
    return 0;
}
int complong(const void *arg1,const void *arg2){
    long l1 = *((long*)arg1);
    long l2 = *((long*)arg2);
    if(l1==l2){
        return 0;
    }else if(l1<l2){
        return -1;
    }else{
        return 1;
    }

}
void* thr_fn71(void * arg){
    long idx = (long)arg;
    heapsort(&nums[idx],TNUM,sizeof(long),complong);
    //等待所有线程执行完毕
    pthread_barrier_wait(&b);
    return ((void*)0);
}
void merge(){
    long idx[NTHR];
    long i,minidx,sidx,num;
    for(i=0;i<NTHR;i++){
        idx[i] = i * TNUM;
    }
    for(sidx=0;sidx<NUMNUM;sidx++){
        num = LONG_MAX;
        for(i=0;i<NTHR;i++){
            if((idx[i]<(i+1)*TNUM) && (nums[idx[i]]<num)){
                num = nums[idx[i]];
                minidx = i;
            }
            //printf("sidx= %ld minidx= %ld idx[%ld]=%ld.\n",sidx,minidx,minidx,idx[minidx]);
            snums[sidx]=nums[idx[minidx]];
            //idx[minidx]++;
        }
    }
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterElevenJni_threadBarrier
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterElevenJni threadBarrier pid=%d", getpid());
    unsigned long i;
    struct timeval start,end;
    long long startusec,endusec;
    double elpased;
    int err;
    pthread_t tid;
    srandom(1);
    for(i=0;i<NUMNUM;i++){
        nums[i] = random();
    }
    gettimeofday(&start,NULL);
    pthread_barrier_init(&b,NULL,NTHR+1);
    for(i=0;i<NTHR;i++){
        err = pthread_create(&tid,NULL,thr_fn71,(void*)(i*TNUM));
        if(err!=0){
            __android_log_print(ANDROID_LOG_ERROR, TAG, "can't create thread %ld.\n",i);
            return;
        }
    }
    pthread_barrier_wait(&b);
    merge();
    gettimeofday(&end,NULL);
    startusec = start.tv_sec * 1000000+start.tv_usec;
    endusec = end.tv_sec * 1000000+end.tv_usec;
    elpased = (endusec-startusec)/1000000.0;
    __android_log_print(ANDROID_LOG_ERROR, TAG, "sort take %.4f seconds.\n",elpased);
    for(i=0;i<NUMNUM;i++){
       // __android_log_print(ANDROID_LOG_ERROR, TAG, "%ld\n",snums[i]);
    }
}
#ifdef __cplusplus
}
#endif