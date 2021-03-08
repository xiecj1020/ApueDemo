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

import android.content.pm.PackageManager;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;

import com.crab.test.apuedemo.jni.ChapterEightJni;

import java.util.ArrayList;
import java.util.List;

public class ChapterEightActivity extends AbsListActivity<String> {
    @Override
    public List<String> getListData() {
        ArrayList<String> list = new ArrayList<>();
        list.add("8.0 test");
        list.add("8.2 processId");
        list.add("8.3 fork");
        list.add("8.4 vfork");
        list.add("8.5 exit");
        list.add("8.6 wait");
        list.add("8.6.1 waitpid");
        list.add("8.7 waitid");
        list.add("8.8 wait4");
        list.add("8.9 competition");
        list.add("8.10 exec");
        list.add("8.16 nice");
        list.add("8.17 process times");
        return list;
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        switch (position) {
            case 0:
                boolean hasReadPermission = checkSelfPermission("android.permission.READ_EXTERNAL_STORAGE") == PackageManager.PERMISSION_GRANTED;
                boolean hasWritePermission = checkSelfPermission("android.permission.WRITE_EXTERNAL_STORAGE") == PackageManager.PERMISSION_GRANTED;
                ArrayList<String> requestPermissions = new ArrayList<>();
                if (!hasReadPermission) {
                    requestPermissions.add("android.permission.READ_EXTERNAL_STORAGE");
                }
                if (!hasWritePermission) {
                    requestPermissions.add("android.permission.WRITE_EXTERNAL_STORAGE");
                }
                int size = requestPermissions.size();
                if (size > 0) {
                    String[] arr = new String[size];
                    requestPermissions(requestPermissions.toArray(arr), 1000);
                } else {
                    ChapterEightJni.test();
                }
                break;
            case 1:
                ChapterEightJni.processId();
                break;
            case 2:
                ChapterEightJni.fork();
                break;
            case 3:
                ChapterEightJni.vfork();
                break;
            case 4:
                ChapterEightJni.exit();
                break;
            case 5:
                ChapterEightJni.waitTest();
                break;
            case 6:
                ChapterEightJni.waitpid();
                break;
            case 7:
                ChapterEightJni.waitid();
            case 8:
                ChapterEightJni.wait4();
                break;
            case 9:
                ChapterEightJni.competition();
                break;
            case 10:
                ChapterEightJni.exec();
                break;
            case 11:
                ChapterEightJni.nice();
                break;
            case 12:
                ChapterEightJni.times();
                break;
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        if (requestCode == 1000) {
            boolean hasReadPermission = checkSelfPermission("android.permission.READ_EXTERNAL_STORAGE") == PackageManager.PERMISSION_GRANTED;
            boolean hasWritePermission = checkSelfPermission("android.permission.WRITE_EXTERNAL_STORAGE") == PackageManager.PERMISSION_GRANTED;
            if (!hasReadPermission || !hasWritePermission) {
                Log.e("mytag", "please allow the android.permission.READ_EXTERNAL_STORAGE and android.permission.WRITE_EXTERNAL_STORAGE.");
                return;
            }
        }
    }
}
