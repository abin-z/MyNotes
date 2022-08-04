package com.abin.lambda;

import com.abin.lambda.userService.UserService;

/**
 * @author Abin
 * @date 2022/01/19
 */
public class LambdaDemo02 {

  public static void main(String[] args) {
    System.out.println("==================匿名内部类实现==================");
    function(new UserService() {
      @Override
      public void show() {
        System.out.println("匿名内部类实现方法....");
      }
    });
    System.out.println("==================Lambda方式实现==================");
    function(() -> {
      System.out.println("Lambda表达式方法实现....");
    });
    function(() -> System.out.println("Lambda的最简写法..."));
  }

  public static void function(UserService userService) {
    userService.show();
  }
}
