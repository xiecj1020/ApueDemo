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
import android.os.Process;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;

import com.crab.test.apuedemo.jni.ChapterOneJni;

import java.util.ArrayList;
import java.util.List;

public class ChapterOneActivity extends AbsListActivity<String> {
    @Override
    public List<String> getListData() {
        ArrayList<String> list = new ArrayList<>();
        list.add("1.4 ls");
        list.add("1.5 io");
        list.add("1.6.1 printPid");
        list.add("1.7 perror");
        list.add("1.8 uid,gid");
        list.add("1.9 signal");
        return list;
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        switch (position) {
            case 0:
                if (checkSelfPermission("android.permission.READ_EXTERNAL_STORAGE") != PackageManager.PERMISSION_GRANTED) {
                    requestPermissions(new String[]{"android.permission.READ_EXTERNAL_STORAGE"}, 1000);
                } else {
                    ChapterOneJni.ls("/sdcard/Android");
                }
                break;
            case 1:
                new Thread() {
                    public void run() {
                        //will cause the application restart when a error happen.
                        ChapterOneJni.io();
                    }
                }.start();
                break;
            case 2:
                Log.e("mytag", "java pid is " + Process.myPid());
                ChapterOneJni.printPid();
                break;
            case 3:
                ChapterOneJni.perror();
                break;
            case 4:
                Log.e("mytag", "java uid=" + Process.myUid() + ",gid=none");
                ChapterOneJni.printUidAndGid();
                break;
            case 5:
                ChapterOneJni.signal();
                break;
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        if (requestCode == 1000) {
            if (checkSelfPermission("android.permission.READ_EXTERNAL_STORAGE") == PackageManager.PERMISSION_GRANTED) {
                ChapterOneJni.ls();
            } else {
                Log.e("mytag", "please allow the android.permission.READ_EXTERNAL_STORAGE.");
            }
        }
    }
}
