package com.abin.stream.parallelstream;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;
import java.util.function.Supplier;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

/**
 * @author Abin
 * @date 2022/02/14
 */
public class ParallelStream09ForkJoin {

  /**
   * 使用 Fork/Join计算1-10000的和, 当一个任务的计算数量大于3000的时候拆分任务。数 量小于3000的时候就计算
   *
   * @param args
   */
  public static void main(String[] args) {
    long startTime = System.currentTimeMillis();
    ForkJoinPool forkJoinPool = new ForkJoinPool();
    SumTask sumTask = new SumTask(1, 100000L);
    Long result = forkJoinPool.invoke(sumTask);
    System.out.println("result = " + result);
    long endTime = System.currentTimeMillis();
    System.out.println("总共耗时:" + (endTime - startTime));
  }
}

class SumTask extends RecursiveTask<Long> {

  //定义一个拆分的临界值
  private static final long THRESHOLD = 5000L;

  //起始坐标
  private final long start;
  //尾部坐标
  private final long end;

  public SumTask(long start, long end) {
    this.start = start;
    this.end = end;
  }

  @Override
  protected Long compute() {
    long length = end - start;
    if (length <= THRESHOLD) {
      //长度小于临界值， 不需要再做拆分，直接进行计算
      long sum = 0;
      for (long i = start; i <= end; i++) {
        sum += i;
      }
      System.out.println("计算： " + start + "--" + end + " 的结果为" + sum);
      return sum;
    } else {
      //长度大于临界值， 还需要再做拆分
      long middle = (start + end) / 2;
      System.out.println("拆分: 左边" + start + "-->" + middle + ", 右边: " + (middle + 1) + "-->" + end);
      SumTask left = new SumTask(start, middle);
      left.fork();      //拆分
      SumTask right = new SumTask(middle + 1, end);
      right.fork();     //拆分
      return left.join() + right.join(); // 合并
    }
  }
}















