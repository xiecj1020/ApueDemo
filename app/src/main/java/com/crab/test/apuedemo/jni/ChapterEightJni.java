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

public class ChapterEightJni {
    static {
        System.loadLibrary("chapterEightJni");
    }
    public static native void test();
    public static native void processId();
    public static native void fork();
    public static native void vfork();
    public static native void exit();
    public static native void waitTest();
    public static native void waitpid();
    public static native void waitid();
    public static native void wait4();
    public static native void competition();
    public static native void exec();
    public static native void nice();
    public static native void times();
}
