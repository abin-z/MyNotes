package com.abin.service.impl;

import com.abin.dao.UserDao;
import com.abin.service.UserService;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

/**
 * @author Abin
 * @date 2022/03/29
 */
public class UserServiceImpl implements UserService {
  private  UserDao userDao;

  public UserServiceImpl(UserDao userDao) {
    this.userDao = userDao;
  }
//  public void setUserDao(UserDao userDao) {
//    this.userDao = userDao;
//  }

  @Override
  public void saveUser() {
//    ApplicationContext appContext = new ClassPathXmlApplicationContext("ApplicationContext.xml");
//    UserDao userDao = (UserDao) appContext.getBean("userDao");
    userDao.save();
  }
}
