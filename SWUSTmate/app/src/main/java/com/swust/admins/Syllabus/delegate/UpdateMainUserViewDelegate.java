package com.swust.admins.Syllabus.delegate;

import com.swust.admins.User.model.User;

/**
 * Created by sky on 14/02/2018.
 */

public interface UpdateMainUserViewDelegate {

    void updateMainUser(User user);

    void updateError(String error);
}
