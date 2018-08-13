package com.swust.admins.Exam.controller;

import com.swust.admins.Base.controller.AsyncController;
import com.swust.admins.User.controller.UserAsyncController;
import com.swust.admins.Exam.delegate.UpdateExamTableDelegate;
import com.swust.admins.Exam.model.ExamTable;
import com.swust.admins.Tool.ConfigHelper;
import com.swust.admins.Exam.web.ExamInterface;

import java.io.IOException;

/**
 * Created by sky on 24/02/2018.
 */

public class ExamAsyncController extends AsyncController {

    private UserAsyncController userController;

    private ConfigHelper            configHelper;

    private ExamTable               examTable;

    private ExamInterface           examInterface;

    private UpdateExamTableDelegate updateExamTableDelegate;

    public ExamAsyncController(UserAsyncController userController, ConfigHelper configHelper) {
        super(userController.getThreadPool());
        this.userController = userController;
        this.configHelper   = configHelper;
        this.examTable      = new ExamTable();
        this.examInterface  = new ExamInterface(
                this.configHelper.GetSystemValue("host"),
                userController);
    }

    public void SyncData() {
        threadPool.execute(new Runnable() {
            @Override
            public void run() {
                try {
                    examTable = examInterface.GetExamTable(
                            userController.getData().getAccount(),
                            userController.getData().getName());
                    updateExamTableDelegate.UpdatedExamTable();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
    }

    public ExamTable GetData() {
        return examTable;
    }

    public void setUpdateExamTableDelegate(UpdateExamTableDelegate updateExamTableDelegate) {
        this.updateExamTableDelegate = updateExamTableDelegate;
    }
}
