#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#define kNumberCount 90		//定义乱序数组中元素个数
#define kNumberCap 999999	//定义乱序数组中元素值的上限
#define kThreadCount 3
#define kNumbersPerRow 30

typedef struct parameters{
	int (* numbers)[kNumberCount];
	int start;
	int end;
}parameters;

void initialize_threads(int numbers[]);
void * bubble_sort(void * params);
void * selection_sort(void * params);
void * insertion_sort(void * params);
void output(int array[]);

int main(){
	int i;
	int random_numbers[kNumberCount];
	int nums_for_bubble[kNumberCount];
	int nums_for_selection[kNumberCount];
	int nums_for_insertion[kNumberCount];
	
	//int thread_count;	//使用的线程个数
	
	srand((unsigned) time(0));	//初始化随机数生成种子
	for(i = 0; i < kNumberCount; i++){	//初始化乱序数组
		random_numbers[i] = rand() % kNumberCap;
		nums_for_bubble[i] = random_numbers[i];
		nums_for_selection[i] = random_numbers[i];
		nums_for_insertion[i] = random_numbers[i];
	}
	
	//输出乱序数组
	
	//printf("请输入使用的线程个数(3/5/6):");
	//scanf("%d", &thread_count);

	//分配各线程所需参数
	initialize_threads(nums_for_bubble);
	
	//归并各个线程的排序结果
	/*
	parameters * merge_param = (parameters *) malloc(sizeof(parameters));
	merge_param->numbers = &random_numbers;
	merge_param->start = 0;
	merge_param->end = kNumberCount - 1;
	
	pthread_t merge;
	pthread_create(&merge, NULL, bubble_sort, (void *) merge_param);
	pthread_join(merge, NULL);
	*/
	
	//输出数组
	
	return 0;
}

void initialize_threads(int numbers[]){
	int i, j = 0;
	parameters * param[kThreadCount];
	for(i = 0; i < kThreadCount; i++){
		param[i] = (parameters *) malloc(sizeof(parameters));
		param[i]->numbers = &(&numbers);
		param[i]->start = j;
		j = j + kNumberCount / kThreadCount;
		param[i]->end = j - 1;
	}
	
	pthread_t threads[kThreadCount];
	
	for(i = 0; i < kThreadCount; i++){
		pthread_create(&threads[i], NULL, bubble_sort, (void *) param[i]);
	}
	for(i = 0; i < kThreadCount; i++){
		pthread_join(threads[i], NULL);
	}
	output(numbers);
}

//冒泡排序
//!!!优化为双向冒泡排序：从后到前遍历将最小值归位
void * bubble_sort(void * params){
	parameters * data = (parameters *) params;
	int start = data->start;
	int end = data->end;
	int i, j, swap_temp;
	
	for(i = start; i <= end; i++){
	//数组的总遍历
		bool is_sorted = true;
		for(j = start; j <= start + end - 1 - i; j++){
		//比较每一对相邻元素，同时避免对最大元素的多余比较
			if((*data->numbers)[j] > (*data->numbers)[j + 1]){
			//比较相邻元素大小，前面>后面则交换
				is_sorted = false;
				swap_temp = (*data->numbers)[j];
				(*data->numbers)[j] = (*data->numbers)[j + 1];
				(*data->numbers)[j + 1] = swap_temp;
			}
		}
		if(is_sorted == true){
		//若此次遍历后数组已经有序则终止排序
			return NULL;
		}
	}
	return NULL;
}

//选择排序
//!!!优化为双向选择排序：同时将最大值归到最后
void * selection_sort(void * params){
	parameters * data = (parameters *) params;
	int start = data->start;
	int end = data->end;
	int i, j, min_index, swap_temp;
	for(i = start; i <= end; i++){
	//数组的总遍历
		min_index = i;	//初始化最小元素下标
		for(j = i + 1; j <= end; j++){
		//找出本次遍历中最小元素的下标
			if((*data->numbers)[j] < (*data->numbers)[min_index]){
				min_index = j;
			}
		}
		//将本次遍历中最小元素换到最前端
		swap_temp = (*data->numbers)[i];
		(*data->numbers)[i] = (*data->numbers)[min_index];
		(*data->numbers)[min_index] = swap_temp;
	}
	return NULL;
}

//插入排序
void * insertion_sort(void * params){
	parameters * data = (parameters *) params;
	int start = data->start;
	int end = data->end;
	int i, j, key;
	for(i = start + 1; i <= end; i++){
		key = (*data->numbers)[i];
		j = i - 1;
		while((j >= start) && ((*data->numbers)[j] > key)){
			(*data->numbers)[j + 1] = (*data->numbers)[j];
			j--;
		}
		(*data->numbers)[j + 1] = key;
	}
	return NULL;
}

//输出数组
void output(int array[]){
	int i, j = 0, k;
	for(i = 0; i < kNumberCount / kNumbersPerRow; i++){
		for(k = 0; k < kNumbersPerRow; k++){
			printf("%6d ", array[j]);
			j++;
		}
		printf("\n");
	}
}