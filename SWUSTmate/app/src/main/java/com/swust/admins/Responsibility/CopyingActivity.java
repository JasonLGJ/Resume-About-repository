package com.swust.admins.Responsibility;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.swust.admins.Base.controller.TitleBarController;
import com.swust.admins.Base.delegate.TitleBarButtonOnClickedDelegate;
import com.swust.admins.MainApplication;
import com.swust.admins.R;
import com.swust.admins.Tool.ConfigHelper;

public class CopyingActivity extends AppCompatActivity implements TitleBarButtonOnClickedDelegate {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_copying);

        TitleBarController titleBarController  = new TitleBarController(this);
        titleBarController
                .setBigPageTitle("GNU开源协议")
                .setHeadBack()
                .setOnClickedListener(this);

        ConfigHelper configHelper = ((MainApplication)getApplication()).getConfigHelper();
        TextView     copyingView  = findViewById(R.id.copyingView);
        copyingView.setText(configHelper.getCopying());
    }

    @Override
    public void titleBarOnClicked(int id) {
        finish();
    }
}
