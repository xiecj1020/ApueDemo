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

import android.view.View;
import android.widget.AdapterView;

import com.crab.test.apuedemo.jni.ChapterTwoJni;

import java.util.ArrayList;
import java.util.List;

public class ChapterTwoActivity extends AbsListActivity<String> {
    @Override
    public List<String> getListData() {
        ArrayList<String> list = new ArrayList<>();
        list.add("2.2.1 isoc");
        list.add("2.2.2 IEEE POSIX");
        list.add("2.5.1 isoc limits");
        list.add("2.5.2 posix limits");
        return list;
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        switch (position) {
            case 0:
                ChapterTwoJni.isoc();
                break;
            case 1:
                ChapterTwoJni.posix();
                break;
            case 2:
                ChapterTwoJni.isocLimits();
                break;
            case 3:
                ChapterTwoJni.posixLimits();
                break;
        }
    }
}
