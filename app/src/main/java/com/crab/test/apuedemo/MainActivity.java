package com.crab.test.apuedemo;


import android.content.Intent;
import android.view.View;
import android.widget.AdapterView;

import com.crab.test.apuedemo.jni.HelloJni;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AbsListActivity<String> {

    @Override
    public List<String > getListData() {
        ArrayList<String> lists = new ArrayList<>();
        lists.add("HelloJni");
        lists.add("Chapter One");
        lists.add("Chapter two");
        return lists;
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        Intent intent = null;
        switch (position){
            case 0:
                HelloJni.sayHello();
                break;
            case 1:
                intent = new Intent(this, ChapterOneActivity.class);
                break;
            case 2:
                break;
            default:
                intent = null;
        }
        if(intent!=null){
            startActivity(intent);
        }
    }
}
