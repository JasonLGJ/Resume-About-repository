/***内存初始化***/
package com.Jason.FaceAttendance;

import android.app.Application;
import android.util.Log;
import cn.bmob.v3.Bmob;

public class MyApplication extends Application {

	@Override
	public void onCreate() {
		super.onCreate();
		//第一：默认初始化
		Bmob.initialize(this, "2d31bbc1ee272b985052a20be3acb029");
		Log.i("onCreate: ","bmob!!!!");
	}
}
