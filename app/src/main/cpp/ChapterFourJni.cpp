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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include "include/com_crab_test_apuedemo_jni_ChapterFourJni.h"

#define TAG "mytag"

#ifdef __cplusplus
extern "C" {
#endif
static void printFileType(const char *path) {
    struct stat buf;
    if (lstat(path, &buf) < 0) {
        char *errStr = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s lstat error=%s.", path, errStr);
        return;
    }
    char *ptr;
    uid_t myUid = buf.st_uid;
    gid_t myGid = buf.st_gid;
    __android_log_print(ANDROID_LOG_ERROR, TAG, "uid=%d gid=%d", myUid, myGid);
    if (S_ISREG(buf.st_mode)) {
        ptr = "regular file";
    } else if (S_ISDIR(buf.st_mode)) {
        ptr = "directory";
    } else if (S_ISCHR(buf.st_mode)) {
        ptr = "character device";
    } else if (S_ISBLK(buf.st_mode)) {
        ptr = "block device";
    } else if (S_ISFIFO(buf.st_mode)) {
        ptr = "FIFO (named pipe)";
    } else if (S_ISLNK(buf.st_mode)) {
        ptr = "symbolic link";
    } else if (S_ISSOCK(buf.st_mode)) {
        ptr = "socket";
    }
    if (buf.st_mode & S_ISUID) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "user id is set");
    } else {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "user id is not set");
    }
    if (buf.st_mode & S_ISGID) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "group id is set");
    } else {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "group id is not set");
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "  buf.st_nlink = %d", buf.st_nlink);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "  file access time = %ld", buf.st_atim.tv_nsec);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "  file modify time = %ld,sec=%ld",
                        buf.st_mtim.tv_nsec, buf.st_mtim.tv_sec);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "  file inode time = %ld", buf.st_ctim.tv_nsec);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "%s is a %s", path, ptr);
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterFourJni_fileType
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterFourJni fileType.");
    __android_log_print(ANDROID_LOG_ERROR, TAG, "process uid=%d,gid=%d,euid=%d,egid=%d.", getuid(),
                        getgid(), geteuid(), getegid());
    printFileType("/sdcard");
    printFileType("/sdcard/new_issue.mp4");
    printFileType("/sdcard/Android");
    printFileType("/sdcard/nofile.txt");
    printFileType("/dev/logcat_main");
}
static void printAccessInfo(const char *path) {
    if (access(path, F_OK) < 0) {
        char *errStr = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s access  F_OK error=%s.", path, errStr);
        return;
    }
    if (access(path, R_OK) < 0) {
        char *errStr = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s  access  R_OK  error=%s.", path, errStr);
    }
    if (access(path, W_OK) < 0) {
        char *errStr = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s  access  W_OK  error=%s.", path, errStr);
    }

}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterFourJni_access
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterFourJni access.");
    printAccessInfo("/sdcard");
    printAccessInfo("/sdcard/new_issue.mp4");
    printAccessInfo("/sdcard/Android");
    printAccessInfo("/sdcard/nofile.txt");
    printAccessInfo("/dev/logcat_main");
}
#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterFourJni_umask
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterFourJni umask.");
    umask(0);
    if (creat("/sdcard/foo.txt", RWRWRW) < 0) {
        char *errStr = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s creat error=%s.", "foo.txt", errStr);
    }
    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (creat("/sdcard/bar.txt", RWRWRW) < 0) {
        char *errStr = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s creat error=%s.", "bar.txt", errStr);
    }

}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterFourJni_fileLength
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterFourJni fileLength .");
    struct stat buf;
    if (lstat("/sdcard/bar.txt", &buf) < 0) {
        char *errStr = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s access  F_OK error=%s.", "/sdcard/bar.txt",
                            errStr);
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "%s file length is %lld", "/sdcard/bar.txt",
                        buf.st_size);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "%s blksize is %lu", "/sdcard/bar.txt",
                        buf.st_blksize);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "%s blocks is %llu", "/sdcard/bar.txt",
                        buf.st_blocks);
}
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterFourJni_truncate
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterFourJni truncate .");
    struct stat buf;
    if (lstat("/sdcard/bar.txt", &buf) < 0) {
        char *errStr = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s lstat error=%s.", "/sdcard/bar.txt",
                            errStr);
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "%s file length is %lld", "/sdcard/bar.txt",
                        buf.st_size);
    if (truncate("/sdcard/bar.txt", buf.st_size - 2) < 0) {
        char *errStr = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s truncate error=%s.", "/sdcard/bar.txt",
                            errStr);
        return;
    }
    if (lstat("/sdcard/bar.txt", &buf) < 0) {
        char *errStr = strerror(errno);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "%s lstat error=%s.", "/sdcard/bar.txt",
                            errStr);
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "%s new file length is %lld", "/sdcard/bar.txt",
                        buf.st_size);
}
/*function type that is called for each filename.*/
typedef int Myfunc(const char *, const struct stat *, int);
static Myfunc myfunc;
static int myftw(char *, Myfunc *);
static int dopath(Myfunc *);
static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;
JNIEXPORT void JNICALL Java_com_crab_test_apuedemo_jni_ChapterFourJni_readDir
        (JNIEnv *env, jclass clazz) {
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterFourJni readDir.");
    int ret;
    ret = myftw("/storage/emulated/0", myfunc);
    ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
    if (ntot == 0) {
        ntot = 1;
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "regular files=%7ld ,%5.2f %%", nreg,
                        nreg * 100.0 / ntot);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "directories=%7ld ,%5.2f %%", ndir,
                        ndir * 100.0 / ntot);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "block special=%7ld ,%5.2f %%", nblk,
                        nblk * 100.0 / ntot);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "char special=%7ld ,%5.2f %%", nchr,
                        nchr * 100.0 / ntot);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "FIFOS=%7ld ,%5.2f %%", nfifo,
                        nfifo * 100.0 / ntot);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "symbolic links=%7ld ,%5.2f %%", nslink,
                        nslink * 100.0 / ntot);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "sockets=%7ld ,%5.2f %%", nsock,
                        nsock * 100.0 / ntot);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ChapterFourJni readDir ret=%d.", ret);
}
#define FTW_F 1
#define FTW_D 2
#define FTW_DNR 3
#define FTW_NS 4
#define  NAMEMAX 255;
static char *fullpath;
static size_t pathlen;
static int myftw(char *pathname, Myfunc *func) {
    fullpath = static_cast<char *>(malloc(pathlen));
    if (pathlen < strlen(pathname)) {
        pathlen = strlen(pathname) * 2;
        free(fullpath);
        if ((fullpath = static_cast<char *>(malloc(pathlen))) == NULL) {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "myftw remalloc fail.");
            return 0;
        }
    }
    strcpy(fullpath, pathname);
    return (dopath(func));
}
static int dopath(Myfunc *func) {
    struct stat statbuf;
    struct dirent *dirp;
    DIR *dp;
    int ret, n;
    //__android_log_print(ANDROID_LOG_ERROR, TAG, "dopath: %s",fullpath);
    if (lstat(fullpath, &statbuf) < 0) {
        return func(fullpath, &statbuf, FTW_NS);
    }
    if (S_ISDIR(statbuf.st_mode) == 0) {
        //not a dir
        return func(fullpath, &statbuf, FTW_F);
    }
    if ((ret = func(fullpath, &statbuf, FTW_D)) != 0) {
        return ret;
    }
    n = strlen(fullpath);
    if (n + NAMEMAX+2 > pathlen) {
        pathlen *= 2;
        if ((fullpath = static_cast<char *>(malloc(pathlen))) == NULL) {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "myftw remalloc fail.");
            return 0;
        }
    }
    fullpath[n++] = '/';
    fullpath[n] = 0;
    if ((dp = opendir(fullpath)) == NULL) {
        return func(fullpath, &statbuf, FTW_DNR);
    }
    while ((dirp = readdir(dp)) != NULL) {
        char *dName = dirp->d_name;
        if (strcmp(dName, ".") == 0 || strcmp(dName, "..") == 0) {
            continue;
        }
        strcpy(&fullpath[n], dName);
        if ((ret = dopath(func)) != 0) {
            break;
        }
    }
    fullpath[n - 1] = 0;
    if (closedir(dp) < 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "can't close dirctories %s", fullpath);
        return 0;
    }
    return ret;
}
static int myfunc(const char *pathname, const struct stat *startptr, int type) {
    //__android_log_print(ANDROID_LOG_ERROR, TAG, "myfunc: %s type %d.",pathname, type);
    switch (type) {
        case FTW_F:
            switch (startptr->st_mode & S_IFMT) {
                case S_IFREG :
                    nreg++;
                    break;
                case S_IFBLK :
                    nblk++;
                    break;
                case S_IFCHR :
                    nchr++;
                    break;
                case S_IFIFO :
                    nfifo++;
                    break;
                case S_IFLNK :
                    nslink++;
                    break;
                case S_IFSOCK :
                    nsock++;
                    break;
                case S_IFDIR :
                    __android_log_print(ANDROID_LOG_ERROR, TAG, "dir should type FTW_D.");
                    break;
            }
            break;
        case FTW_D:
            ndir++;
            break;
        case FTW_DNR:
            __android_log_print(ANDROID_LOG_ERROR, TAG, "dir FTW_DNR error.");
            break;
        case FTW_NS:
            __android_log_print(ANDROID_LOG_ERROR, TAG, "stat type error.");
            break;
        default:
            __android_log_print(ANDROID_LOG_ERROR, TAG, "type error.");
    }
    return 0;
}
#ifdef __cplusplus
}
#endif