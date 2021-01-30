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

import android.content.Intent;
import android.view.View;
import android.widget.AdapterView;

import com.crab.test.apuedemo.jni.HelloJni;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AbsListActivity<String> {

    @Override
    public List<String> getListData() {
        ArrayList<String> lists = new ArrayList<>();
        lists.add("HelloJni");
        lists.add("Chapter One");
        lists.add("Chapter Two");
        lists.add("Chapter Three");
        lists.add("Chapter Four");
        lists.add("Chapter Five");
        return lists;
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        Intent intent = null;
        switch (position) {
            case 0:
                HelloJni.sayHello();
                break;
            case 1:
                intent = new Intent(this, ChapterOneActivity.class);
                break;
            case 2:
                intent = new Intent(this, ChapterTwoActivity.class);
                break;
            case 3:
                intent = new Intent(this, ChapterThreeActivity.class);
                break;
            case 4:
                intent = new Intent(this, ChapterFourActivity.class);
                break;
            case 5:
                intent = new Intent(this, ChapterFiveActivity.class);
                break;
            default:
                intent = null;
        }
        if (intent != null) {
            startActivity(intent);
        }
    }
}
