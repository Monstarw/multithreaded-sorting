# 多线程排序

## 题目要求

> 设计程序（个数不限），实现多线程排序。
>
> 通过使用rand函数生成一个乱序数组，再使用pthread库的pthread_create函数创建多个线程，将等额数量的待排序数分配给这些线程后，分别进行排序，然后再输出排好序的数组。
>
> 比较不同排序算法和不同线程数量时的程序运行时间。
>
> 其中线程数量选择3、5、6个分别进行测试，待排序数总数量为90000个，排序算法包括：冒泡排序、选择排序、插入排序、快速排序、希尔排序（选择三种即可）。
>
> 对比相同排序算法不同线程数量的运行时间、相同线程数量不同排序算法的运行时间，如能生成实时显示的图形用户界面最佳，如不能请画出比较图表，并在实验报告中对结果进行分析说明。

### 编译运行环境

Linux + GCC

### 编译指令

gcc main.c -lpthread

### 运行指令

./a.out
