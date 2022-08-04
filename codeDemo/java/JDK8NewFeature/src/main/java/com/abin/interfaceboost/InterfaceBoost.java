package com.abin.interfaceboost;

/**
 * @author Abin
 * @date 2022/01/20
 */
public class InterfaceBoost {
  public static void main(String[] args) {
    AAA aaa = new AAA();
    BBB bbb = new BBB();
    aaa.abstractFunc();
    aaa.defaultFunc();
    bbb.defaultFunc();
    III.staticFunc(); //接口中的静态方法只能通过接口来调用
  }
}

interface III {
  //接口中有些关键字可以省略
  public static final Integer number = 12;   //静态常量
  public void abstractFunc();                //抽象方法

  public default void  defaultFunc(){
    System.out.println("接口中的默认default方法");
  }

  public static void staticFunc(){
    System.out.println("接口中的静态方法, 不能被实现类重写, 只能通过接口名.静态方法名调用");
  }

}

class AAA implements III {

  @Override
  public void abstractFunc() {
    System.out.println("实现类AAA中的重写的方法...");
  }
}

class BBB implements III{

  @Override
  public void defaultFunc() {
    III.super.defaultFunc();
    System.out.println("实现类中重写接口中的默认方法...");
  }

  @Override
  public void abstractFunc() {

  }
}

interface OOO extends III{

}

