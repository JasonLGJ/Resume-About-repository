package com.swust.admins.Base.controller;

import java.util.concurrent.ExecutorService;

/**
 * Created by Jason on 05/07/2018.
 */

public class AsyncController {//线程池异步控制

    protected ExecutorService threadPool;

    public AsyncController(ExecutorService threadPool) {
        this.threadPool = threadPool;
    }

    public void setThreadPool(ExecutorService threadPool) {
        this.threadPool = threadPool;
    }

    public ExecutorService getThreadPool() {
        return threadPool;
    }
}
