package com.abin.lambda.userService;

import com.abin.lambda.Entity.Person;

/**
 * @author Abin
 * @date 2022/01/19
 */
@FunctionalInterface
public interface PersonService {
  Integer getPersonAge( Person person);
}
