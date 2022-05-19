package com.abin.dao.impl;

import com.abin.dao.UserDao;
import com.abin.service.UserService;

/**
 * @author Abin
 * @date 2022/03/29
 */
public class UserDaoImpl implements UserDao {


  @Override
  public void save() {
    System.out.println("saveDao 被调用!!");
  }

  @Override
  public void init() {
    System.out.println("init初始化方法被调用");
  }

  @Override
  public void destroy() {
    System.out.println("destroy初始化方法被调用");
  }
}
