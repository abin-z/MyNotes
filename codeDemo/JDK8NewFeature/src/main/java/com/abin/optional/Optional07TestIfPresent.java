package com.abin.optional;

import com.abin.lambda.Entity.Person;
import java.util.Optional;

/**
 * @author Abin
 * @date 2022/02/16
 */
public class Optional07TestIfPresent {

  public static void main(String[] args) {

    Optional<String> s = Optional.of("张三");
    Optional<Object> empty = Optional.empty();

    s.ifPresent(i -> {
      System.out.println("存在执行的操作1111 " + i);
    });

    empty.ifPresent(i -> {
      System.out.println("存在执行的操作2222 " + i);
    });
  }
}
