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

public class ChapterElevenJni {
    static {
        System.loadLibrary("chapterElevenJni");
    }

    public static native void test();
    public static native void threadCreate();
    public static native void threadExit1();
    public static native void threadExit2();
    public static native void threadExit3();
    public static native void threadMutex();
    public static native void threadMutexTimed();
    public static native void threadReadWriteLock();
    public static native void threadCondition();
    public static native void threadSpin();
    public static native void threadBarrier();
}
