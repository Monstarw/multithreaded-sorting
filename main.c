#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#define kNumberCount 30	//定义乱序数组中元素个数
#define kNumberCap 100	//定义乱序数组中元素值的上限
#define kThreadCount 3

typedef struct parameters{
	int (* numbers)[kNumberCount];
	int start;
	int end;
}parameters;

void * bubble_sort(void * params);
void * selection_sort(void * params);
void * insertion_sort(void * params);

int main(){
	int random_numbers[kNumberCount];
	int i, j = 0, k;
	//int thread_count;	//使用的线程个数
	
	srand((unsigned) time(0));	//初始化随机数生成种子
	for(i = 0; i < kNumberCount; i++){	//初始化乱序数组
		random_numbers[i] = rand() % kNumberCap;
	}
	
	//输出乱序数组
	for(i = 0; i < kThreadCount; i++){
		for(k = 0; k < kNumberCount / kThreadCount; k++){
			printf("%d\t", random_numbers[j]);
			j++;
		}
		printf("\n");
	}
	j = 0;

	//printf("请输入使用的线程个数(3/5/6):");
	//scanf("%d", &thread_count);

	//分配各线程所需参数
	parameters * param[kThreadCount];
	for(i = 0; i < kThreadCount; i++){
		param[i] = (parameters *) malloc(sizeof(parameters));
		param[i]->numbers = &random_numbers;
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
	
	//输出排序结果
	printf("\n");
	j = 0;
	for(i = 0; i < kThreadCount; i++){
		for(k = 0; k < kNumberCount / kThreadCount; k++){
			printf("%d\t", random_numbers[j]);
			j++;
		}
		printf("\n");
	}
	printf("\n");
	return 0;
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
