package com.abin.funcref.entity;

import java.util.Objects;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

/**
 * @author Abin
 * @date 2022/01/24
 */
//@Data
//@AllArgsConstructor
//@NoArgsConstructor
public class Person {
  private String name;
  private Integer age;
  private Double height;

  public Person(String name, Integer age) {
    this.name = name;
    this.age = age;
  }

  public Person(String name, Integer age, Double height) {
    this.name = name;
    this.age = age;
    this.height = height;
  }

  public Person() {

  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  public Integer getAge() {
    return age;
  }

  public void setAge(Integer age) {
    this.age = age;
  }

  public Double getHeight() {
    return height;
  }

  public void setHeight(Double height) {
    this.height = height;
  }

  @Override
  public String
  toString() {
    return "Person{" +
        "name='" + name + '\'' +
        ", age=" + age +
        ", height=" + height +
        '}';
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) {
      return true;
    }
    if (o == null || getClass() != o.getClass()) {
      return false;
    }
    Person person = (Person) o;
    return Objects.equals(name, person.name) && Objects.equals(age, person.age);
  }

  @Override
  public int hashCode() {
    return Objects.hash(name, age);
  }
}
