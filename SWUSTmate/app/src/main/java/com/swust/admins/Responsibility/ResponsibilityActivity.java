package com.swust.admins.Responsibility;

import android.os.Bundle;

import com.swust.admins.Base.BaseActivity;
import com.swust.admins.Base.controller.TitleBarController;
import com.swust.admins.Base.delegate.TitleBarButtonOnClickedDelegate;
import com.swust.admins.R;

public class ResponsibilityActivity extends BaseActivity implements
        TitleBarButtonOnClickedDelegate {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_responsibility);

        TitleBarController titleBarController  = new TitleBarController(this);
        titleBarController
                .setBigPageTitle("iFAFU隐私条款及免责说明")
                .setHeadBack()
                .setOnClickedListener(this);
    }

    @Override
    public void titleBarOnClicked(int id) {
        finish();
    }
}
