package com.swust.admins.User.model;

import com.swust.admins.Base.model.Model;

import java.io.Serializable;

/**
 * Created by Jason on 05/07/2018.
 */
/*序列化接口，https://www.cnblogs.com/huhx/p/serializable.html*/
public class User extends Model implements Serializable {

    private String        name;

    private String        account;

    private String        password;

    private String        institute;

    private int           enrollment;

    private String        clas;

    private String        token;

    private boolean       isLogin;

    public int getEnrollment() {
        return enrollment;
    }

    public String getClas() {
        return clas;
    }

    public String getInstitute() {
        return institute;
    }

    public void setInstitute(String institute) {
        this.institute = institute;
    }

    public void setClas(String clas) {
        this.clas = clas;
    }

    public void setEnrollment(int enrollment) {
        this.enrollment = enrollment;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public boolean isLogin() {
        return isLogin;
    }

    public String getAccount() {
        return account;
    }

    public String getPassword() {
        return password;
    }

    public String getToken() {
        return token;
    }

    public void setAccount(String account) {
        this.account = account;
    }

    public void setLogin(boolean login) {
        isLogin = login;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void setToken(String token) {
        this.token = token;
    }
}
