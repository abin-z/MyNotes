package com.abin.lambda;

/**
 * @author Abin
 * @date 2022/01/19
 */
public class LambdaDemo01 {

  public static void main(String[] args) {
//    functionOrdinary(); //调用普通的方法
    functionLambda(); //调用使用了Lambda的方法
  }

/*
  public static void functionOrdinary() {
    //开启一个新线程
    new Thread(new Runnable() {
      @Override
      public void run() {
        System.out.println("新线程的输出语句..." + Thread.currentThread().getName());
      }
    }).start();
    System.out.println("主线程的输出语句..." + Thread.currentThread().getName());
  }
*/

  public static void functionLambda() {
    //开启一个新线程,使用Lambda表达式
    new Thread(() -> {
      System.out.println("新线程lambda表达式执行的语句..." + Thread.currentThread().getName());
    }).start();
    System.out.println("主线程的输出语句..." + Thread.currentThread().getName());
  }
}