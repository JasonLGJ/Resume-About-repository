package com.swust.admins.About;

import android.os.Bundle;
import android.widget.TextView;

import com.swust.admins.Base.BaseActivity;
import com.swust.admins.Base.controller.TitleBarController;
import com.swust.admins.Base.delegate.TitleBarButtonOnClickedDelegate;
import com.swust.admins.R;
import com.swust.admins.Tool.GlobalLib;

import java.util.Locale;

public class AboutActivity extends BaseActivity implements TitleBarButtonOnClickedDelegate {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_about);

        TitleBarController titleBarController = new TitleBarController(this);
        titleBarController
                .setHeadBack()
                .setBigPageTitle("关于iSWUST")
                .setOnClickedListener(this);
        TextView aboutAppSubName = findViewById(R.id.aboutAppSubName);

        aboutAppSubName.setText(String.format(
                Locale.getDefault(), getString(R.string.app_sub_name),
                GlobalLib.GetLocalVersionName(this)));
    }

    @Override
    public void titleBarOnClicked(int id) {
        finish();
    }
}
