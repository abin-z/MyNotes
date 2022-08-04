package com.abin.functionalinterface;

import java.util.Locale;

/**
 * @author Abin
 * @date 2022/01/20
 */
public class FuncInterface {

  public static void main(String[] args) {
    String str = "Hello World!";
    String s = fun1(msg -> msg.toUpperCase(Locale.ROOT), str);
    System.out.println(s);
  }

  public static String fun1(Operator operator, String argument){
    return operator.handle(argument);
  }
}

@FunctionalInterface
interface Operator{
  String handle(String s);
}