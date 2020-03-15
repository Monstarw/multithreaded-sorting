#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#define kNumberCount 90		//定义乱序数组中元素个数
#define kNumberCap 999999	//定义乱序数组中元素值的上限
#define kThreadCount 3		//线程数
#define kNumbersPerRow 30	//输出时每行显示的元素数量

typedef struct parameters{	//包含排序线程所需参数的结构体
	int (* numbers)[kNumberCount];	//待排序数组的指针
	int start;	//排序起点下标
	int end;	//排序终点下标
}parameters;

//初始化线程（分配线程结构体参数、建立线程、等待线程运行完毕）
void initialize_threads(int numbers[]);	
void * bubble_sort(void * params);		//冒泡排序
void * selection_sort(void * params);	//选择排序
void * insertion_sort(void * params);	//插入排序
void output(int array[]);	//按行输出数组内容

int main(){
	int i;
	int random_numbers[kNumberCount];		//乱序数组
	int nums_for_bubble[kNumberCount];		//进行冒泡排序的数组
	int nums_for_selection[kNumberCount];	//进行选择排序的数组
	int nums_for_insertion[kNumberCount];	//进行插入排序的数组
	
	srand((unsigned) time(0));	//初始化随机数生成种子
	for(i = 0; i < kNumberCount; i++){	//初始化乱序数组及三个不同算法所需数组
		random_numbers[i] = rand() % kNumberCap;	//为每个元素赋值一个小于kNumberCap的随机数
		nums_for_bubble[i] = random_numbers[i];		//复制到进行冒泡排序的数组
		nums_for_selection[i] = random_numbers[i];	//复制到进行选择排序的数组
		nums_for_insertion[i] = random_numbers[i];	//复制到进行插入排序的数组
	}
	
	//输出乱序数组

	//初始化线程（分配线程结构体参数、建立线程、等待线程运行完毕）
	int * pNumsForBubble = nums_for_bubble;
	initialize_threads(pNumsForBubble);
	
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

//初始化线程（分配线程结构体参数、建立线程、等待线程运行完毕）
void initialize_threads(int (* numbers[])){
	int i, j = 0;
	int * p;
	parameters * param[kThreadCount];	//建立结构体
	for(i = 0; i < kThreadCount; i++){
		param[i] = (parameters *) malloc(sizeof(parameters));	//分配所需内存空间
		
		/*↓↓↓↓↓  error when compiling: assignment from incompatible pointer type ↓↓↓↓↓*/
		p = numbers;
		param[i]->numbers = &p;	//待排序数组的指针
		
		param[i]->start = j;	//排序起点下标
		j = j + kNumberCount / kThreadCount;	//更新终点位置
		param[i]->end = j - 1;	//排序终点下标
	}
	
	pthread_t threads[kThreadCount];	//声明线程数组
	
	for(i = 0; i < kThreadCount; i++){
		pthread_create(&threads[i], NULL, bubble_sort, (void *) param[i]);	//建立数组
	}
	for(i = 0; i < kThreadCount; i++){
		pthread_join(threads[i], NULL);	//等待线程运行完毕
	}
	//output(numbers);	//输出数组
}

//冒泡排序
//!!!优化为双向冒泡排序：从后到前遍历将最小值归位
void * bubble_sort(void * params){
	parameters * data = (parameters *) params;
	int start = data->start;
	int end = data->end;
	int i, j, swap_temp;
	bool is_sorted;	//标记本次遍历时数组是否已经有序
	
	for(i = start; i <= end; i++){
	//数组的总遍历
		is_sorted = true;
		for(j = start; j <= start + end - 1 - i; j++){
		//比较每一对相邻元素，同时避免对最大元素的多余比较
			if((*data->numbers)[j] > (*data->numbers)[j + 1]){
			//比较相邻元素大小，前面>后面则交换
				//若发生交换则标记此时数组为非有序状态
				is_sorted = false;
				//交换元素
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
	//循环次数为输出所有元素所需行数
		for(k = 0; k < kNumbersPerRow; k++){
			printf("%6d ", array[j]);
			j++;
		}
		printf("\n");
	}
}