package com.crab.test.apuedemo;

import android.app.Activity;
import android.os.Bundle;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import java.util.List;

public abstract  class AbsListActivity<T> extends Activity implements AdapterView.OnItemClickListener {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.list_activity);
        ListView listView = findViewById(R.id.list_view);
        listView.setAdapter(new ArrayAdapter<T>(this,android.R.layout.simple_list_item_1,android.R.id.text1,getListData()));
        listView.setOnItemClickListener(this);

    }
    public abstract List<T> getListData();
}
