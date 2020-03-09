#include <stdio.h>
#include <stdlib.h>
//#include <pthread.h>
//!!!加入线程后在linux环境下进行后续测试
#include <time.h>
#include <stdbool.h>
#define kNumberCount 10	//定义乱序数组中元素个数
#define kNumberCap 100	//定义乱序数组中元素值的上限

void bubble_sort(int numbers[], int start, int end);
void selection_sort(int numbers[], int start, int end);
void insertion_sort(int numbers[], int start, int end);

int main(){
	int random_numbers[kNumberCount];
	int i;
	srand((unsigned) time(0));	//初始化随机数生成种子
	for(i = 0; i < kNumberCount; i++){	//初始化乱序数组
		random_numbers[i] = rand() % kNumberCap;
		printf("%d\n", random_numbers[i]);
	}
	
	//调用冒泡排序
	//bubble_sort(random_numbers, 0, kNumberCount);
	
	//调用选择排序
	selection_sort(random_numbers, 0, kNumberCount);
	
	//调用插入排序
	//insertion_sort(random_numbers, 0, kNumberCount);
	
	//输出排序结果
	printf("=========\n");
	for(i = 0; i < kNumberCount; i++){
		printf("%d\n", random_numbers[i]);
	}
	
	return 0;
}

//冒泡排序
//!!!优化为双向冒泡排序：从后到前遍历将最小值归位
void bubble_sort(int numbers[], int start, int end){
	int i, j, swap_temp;
	for(i = start; i < end; i++){	
	//数组的总遍历
		bool is_sorted = true;
		for(j = 0; j < end - 1 - i; j++){
		//比较每一对相邻元素，同时避免对最大元素的多余比较
			if(numbers[j] > numbers[j + 1]){
			//比较相邻元素大小，前面>后面则交换
				is_sorted = false;
				swap_temp = numbers[j];
				numbers[j] = numbers[j + 1];
				numbers[j + 1] = swap_temp;
			}
		}
		if(is_sorted == true){
		//若此次遍历后数组已经有序则终止排序
			return;
		}
	}
}

//选择排序
//!!!优化为双向选择排序：同时将最大值归到最后
void selection_sort(int numbers[], int start, int end){
	int i, j, min_index, swap_temp;
	for(i = start; i < end; i++){
	//数组的总遍历
		min_index = i;	//初始化最小元素下标
		for(j = i + 1; j < end; j++){
		//找出本次遍历中最小元素的下标
			if(numbers[j] < numbers[min_index]){
				min_index = j;
			}
		}
		//将本次遍历中最小元素换到最前端
		swap_temp = numbers[i];
		numbers[i] = numbers[min_index];
		numbers[min_index] = swap_temp;
	}
}

//插入排序
void insertion_sort(int numbers[], int start, int end){
	//啊不……还没写呢！（郭老师.gif）
}