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

package com.crab.test.apuedemo;

import android.util.Log;
import android.view.View;
import android.widget.AdapterView;

import com.crab.test.apuedemo.jni.ChapterElevenJni;

import java.util.ArrayList;
import java.util.List;

public class ChapterElevenActivity extends AbsListActivity<String> {
    @Override
    public List<String> getListData() {
        ArrayList<String> list = new ArrayList<>();
        list.add("11.0 test");
        list.add("11.4 thread_create");
        list.add("11.5.1 thread_exit1");
        list.add("11.5.2 thread_exit2");
        list.add("11.5.3 thread_exit3");
        list.add("11.6.1 thread_mutex");
        list.add("11.6.3 thread_mutex_timelock");
        list.add("11.6.4 thread_read_write_lock");
        list.add("11.6.6 thread_condition");
        list.add("11.6.7 thread_spin");
        list.add("11.6.7 thread_barrier");
        return list;
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        switch (position) {
            case 0:
                ChapterElevenJni.test();
                Log.e("mytag","java thread id="+Thread.currentThread().getId());
                break;
            case 1:
                ChapterElevenJni.threadCreate();
                break;
            case 2:
                ChapterElevenJni.threadExit1();
                break;
            case 3:
                ChapterElevenJni.threadExit2();
                break;
            case 4:
                ChapterElevenJni.threadExit3();
                break;
            case 5:
                ChapterElevenJni.threadMutex();
                break;
            case 6:
                ChapterElevenJni.threadMutexTimed();
                break;
            case 7:
                ChapterElevenJni.threadReadWriteLock();
                break;
            case 8:
                ChapterElevenJni.threadCondition();
                break;
            case 9:
                ChapterElevenJni.threadSpin();
                break;
            case 10:
                ChapterElevenJni.threadBarrier();
                break;
        }
    }
}
