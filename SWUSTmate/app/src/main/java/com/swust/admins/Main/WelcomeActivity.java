package com.swust.admins.Main;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import com.swust.admins.MainApplication;
import com.swust.admins.R;
import com.swust.admins.Tool.ConfigHelper;
import com.swust.admins.Tool.OSSHelper;

import java.io.IOException;

public class WelcomeActivity extends AppCompatActivity {

    private MainApplication mainApplication;

    private OSSHelper       ossHelper;

    private ConfigHelper    configHelper;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_welcome);

        mainApplication = (MainApplication) getApplicationContext();
        ossHelper       = mainApplication.getOssHelper();
        configHelper    = mainApplication.getConfigHelper();
    }

    @Override
    protected void onStart() {
        super.onStart();

        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    ossHelper.syncData();
                    configHelper.SetValue("nowTermFirstWeek", ossHelper.getStudyTime());
                    finish();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }
}
