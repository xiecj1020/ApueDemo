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
        lists.add("0: HelloJni");
        lists.add("1: Unix基础知识");
        lists.add("2: Unix标准及实现");
        lists.add("3: 文件IO");
        lists.add("4: 文件和目录");
        lists.add("5: 标准IO库");
        lists.add("6: 系统数据文件和信息");
        lists.add("7: 进程环境");
        lists.add("8: 进程控制");
        lists.add("9: 进程关系");
        lists.add("10: 信号");
        lists.add("11: 线程");
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
            case 6:
                intent = new Intent(this, ChapterSixActivity.class);
                break;
            case 7:
                intent = new Intent(this, ChapterSevenActivity.class);
                break;
            case 8:
                intent = new Intent(this, ChapterEightActivity.class);
                break;
            case 9:
                intent = new Intent(this, ChapterNineActivity.class);
                break;
            case 10:
                intent = new Intent(this, ChapterTenActivity.class);
                break;
            case 11:
                intent = new Intent(this, ChapterElevenActivity.class);
                break;
            default:
                intent = null;
        }
        if (intent != null) {
            startActivity(intent);
        }
    }
}
