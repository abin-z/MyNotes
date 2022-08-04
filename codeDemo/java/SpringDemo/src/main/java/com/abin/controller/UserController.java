package com.abin.controller;

import com.abin.service.UserService;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

/**
 * @author Abin
 * @date 2022/03/29
 */
public class UserController {
  public static void main(String[] args) {
    ClassPathXmlApplicationContext applicationContext = new ClassPathXmlApplicationContext("ApplicationContext.xml");
//    UserService userService = (UserService) applicationContext.getBean("userService");
    UserService userService = applicationContext.getBean(UserService.class);
    userService.saveUser();
    applicationContext.registerShutdownHook();
  }
}
