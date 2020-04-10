#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#define kNumberCount 90000	//定义乱序数组中元素个数
#define kNumberCap 999999	//定义乱序数组中元素值的上限
#define kNumbersPerRow 20	//输出时每行显示的元素数量

typedef struct parameters{	//包含排序线程所需参数的结构体
	int (* numbers)[kNumberCount];	//待排序数组的指针
	int start;	//排序起点下标
	int end;	//排序终点下标
} parameters;

void initialize_threads(int thread_count, int sort_method, int random_numbers[]);	//完成线程操作
void * bubble_sort(void * params);		//冒泡排序
void * selection_sort(void * params);	//选择排序
void * insertion_sort(void * params);	//插入排序
void output(int array[], char file_name[]);	//将数组array的内容写入名为file_name的外部文件

int main(){
	int random_numbers[kNumberCount];	//乱序数组
	int thread_count, sort_method;	//使用的线程数量、使用的排序算法编号
	srand((unsigned) time(0));	//初始化随机数生成种子
	for(int i = 0; i < kNumberCount; i++){	//初始化乱序数组
		random_numbers[i] = rand() % kNumberCap;	//将每个元素赋为一个小于kNumberCap的随机数
	}
	output(random_numbers, "random_numbers");	//将随机数数组写入文件random_numbers
	while(1){
		printf("请输入使用的线程数：");
		scanf("%d", &thread_count);
		printf("请输入使用的排序算法（1冒泡，2选择，3插入）：");
		scanf("%d", &sort_method);
		initialize_threads(thread_count, sort_method, random_numbers);	//完成线程操作
	}
	return 0;
}

//完成线程操作
void initialize_threads(int thread_count, int sort_method, int random_numbers[]){
	int i, j = 0;
	int numbers[kNumberCount];
	clock_t start_time, end_time;	//声明记录排序运行开始时刻、结束时刻的时间变量
	parameters *param = malloc(sizeof *param * thread_count);	//建立结构体并分配所需内存空间
	pthread_t *threads = malloc(sizeof *threads * thread_count);	//声明线程数组
	
	//复制一份乱序数组给numbers便于随后使用
	for(i = 0; i < kNumberCount; i++){
		numbers[i] = random_numbers[i];
	}
	
	//分配线程结构体参数
	for(i = 0; i < thread_count; i++){
		param[i].numbers = &numbers;	//待排序数组的指针
		param[i].start = j;	//排序起点下标
		j = j + kNumberCount / thread_count;	//更新终点位置
		param[i].end = j - 1;	//排序终点下标
	}
	
	//根据不同排序算法编号运行使用相应函数的线程
	switch(sort_method){
		case 1:	//执行冒泡线程
			start_time = clock();	//记录排序运行开始时刻
			for(i = 0; i < thread_count; i++){
				pthread_create(&threads[i], NULL, bubble_sort, &param[i]);	
			}
			break;
		case 2:	//执行选择线程
			start_time = clock();	//记录排序运行开始时刻
			for(i = 0; i < thread_count; i++){
				pthread_create(&threads[i], NULL, selection_sort, &param[i]);
			}
			break;
		case 3:	//执行插入线程
			start_time = clock();	//记录排序运行开始时刻
			for(i = 0; i < thread_count; i++){
				pthread_create(&threads[i], NULL, insertion_sort, &param[i]);
			}
			break;
	}
	
	//等待所有线程运行完毕
	for(i = 0; i < thread_count; i++){
		pthread_join(threads[i], NULL);
	}
	
	end_time = clock();	//记录排序运行结束时刻
	double sort_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;	//得到排序用时
	output(numbers, "sorted_numbers");	//将排好序的数组内容写入文件sorted_numbers
	
	//根据不同排序算法输出相应信息
	switch(sort_method){
		case 1:
			printf("%d 线程冒泡排序用时 %f 秒\n", thread_count, sort_time);
			break;
		case 2:
			printf("%d 线程选择排序用时 %f 秒\n", thread_count, sort_time);
			break;
		case 3:
			printf("%d 线程插入排序用时 %f 秒\n", thread_count, sort_time);
			break;
	}
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
void output(int array[], char file_name[]){
	int i, j = 0, k;
	FILE *fp = fopen(file_name, "w");
	for(i = 0; i < kNumberCount / kNumbersPerRow; i++){	//循环次数为输出所有元素所需行数
		for(k = 0; k < kNumbersPerRow; k++){
			fprintf(fp, "%6d ", array[j++]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}
