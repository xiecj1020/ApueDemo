package com.crab.test.apuedemo;

import android.view.View;
import android.widget.AdapterView;

import java.util.ArrayList;
import java.util.List;

public class ChapterOneActivity extends AbsListActivity<String> {
    @Override
    public List<String> getListData() {
        return new ArrayList<>();
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {

    }
}
