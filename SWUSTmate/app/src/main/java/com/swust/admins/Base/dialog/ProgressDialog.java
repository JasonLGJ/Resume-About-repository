package com.swust.admins.Base.dialog;

import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.support.annotation.NonNull;
import android.view.KeyEvent;
import android.widget.TextView;

import com.swust.admins.R;

/**
 * Created by sky on 05/09/2018.
 */

public class ProgressDialog extends Dialog {

    private TextView textView;

    public ProgressDialog(@NonNull Context context) {
        super(context, R.style.styleProgressDialog);
        setContentView(R.layout.dialog_progress);
        setCanceledOnTouchOutside(false);
        setOnKeyListener(new OnKeyListener() {
            @Override
            public boolean onKey(DialogInterface dialog, int keyCode, KeyEvent event) {
                return keyCode == KeyEvent.KEYCODE_BACK;
            }
        });

        textView = findViewById(R.id.dialogProgressText);
    }

    public void show(String text) {
        textView.setText(text);

        super.show();
    }
}
