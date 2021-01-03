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

package com.crab.test.apuedemo.jni;

public class ChapterOneJni {
    static {
        System.loadLibrary("chapterOneJni");
    }

    public static void ls() {
        ls("/sdcard");
    }

    public static native void ls(String path);

    public static native void io();

    public static native void printPid();

    public static native void perror();

    public static native void printUidAndGid();

    public static native void signal();
}
