package com.abin.stream.pojo;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.ToString;

/**
 * @author Abin
 * @date 2022/01/28
 */
@Data
@NoArgsConstructor
@AllArgsConstructor
@ToString
public class Student {
  private String name;
  private Integer age;
  private Integer score;
}
