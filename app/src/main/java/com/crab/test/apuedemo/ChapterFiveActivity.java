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

import com.crab.test.apuedemo.jni.ChapterFiveJni;

import java.util.ArrayList;
import java.util.List;

public class ChapterFiveActivity extends AbsListActivity<String> {
    @Override
    public List<String> getListData() {
        ArrayList<String> list = new ArrayList<>();
        list.add("5.5 fopen");
        list.add("5.8 io effective");
        list.add("5.9 fread");
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
                    ChapterFiveJni.fopen();
                }
                break;
            case 1:
                ChapterFiveJni.ioEffective();
                break;
            case 2:
                ChapterFiveJni.fread();
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
