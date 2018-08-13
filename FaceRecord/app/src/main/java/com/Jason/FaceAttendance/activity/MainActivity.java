package com.Jason.FaceAttendance.activity;

import android.content.DialogInterface;
import android.content.Intent;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.widget.Button;
import com.Jason.FaceAttendance.R;
import static android.content.DialogInterface.BUTTON_NEGATIVE;
import static android.content.DialogInterface.BUTTON_POSITIVE;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
	private Button button_register,button_sign_in,button_manage,button_sign_log;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		initUI();
	}

	private void initUI() {
		button_register = (Button) this.findViewById(R.id.button_register);
		button_sign_in = (Button) this.findViewById(R.id.button_sign_in);
		button_manage = (Button) this.findViewById(R.id.button_manage);
		button_sign_log = (Button) this.findViewById(R.id.button_sign_log);
		button_register.setOnClickListener(this);
		button_sign_in.setOnClickListener(this);
		button_manage.setOnClickListener(this);
		button_sign_log.setOnClickListener(this);
	}

	@Override
	public void onClick(View v) {
		switch (v.getId()){
			case R.id.button_register:
				Intent intent = new Intent(this,RegisterFaceActivity.class);
				startActivity(intent);
				break;
			case R.id.button_sign_in:
				startActivity(new Intent(this,SignInActivity.class));
				break;
			case R.id.button_manage:
				startActivity(new Intent(this,ManageActivity.class));
				break;
			case R.id.button_sign_log:
				startActivity(new Intent(this,SignLogActivity.class));
				break;
			default:
				break;
		}
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			showMyDialog(); //点击BACK弹出对话框
		}
		return false;
	}

	private void showMyDialog() {
		// 创建退出对话框
		AlertDialog isExit = new AlertDialog.Builder(this).create();
		// 设置对话框标题
		isExit.setTitle("提示");
		// 设置对话框消息
		isExit.setMessage("确定要退出吗?");
		// 添加选择按钮并注册监听
		isExit.setButton(BUTTON_POSITIVE, "确定", listener);
		isExit.setButton(BUTTON_NEGATIVE, "取消", listener);
		// 显示对话框
		isExit.show();
	}

	/**
	 * 监听对话框里面的button点击事件
	 */
	DialogInterface.OnClickListener listener = new DialogInterface.OnClickListener() {
		public void onClick(DialogInterface dialog, int which) {
			switch (which) {
				case BUTTON_POSITIVE:// "确认"按钮退出程序
					finish();
					break;
				case BUTTON_NEGATIVE:// "取消"第二个按钮取消对话框
					break;
				default:
					break;
			}
		}
	};

}
