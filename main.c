#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#define kNumberCount 90		//��������������Ԫ�ظ���
#define kNumberCap 999999	//��������������Ԫ��ֵ������
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
	
	//int thread_count;	//ʹ�õ��̸߳���
	
	srand((unsigned) time(0));	//��ʼ���������������
	for(i = 0; i < kNumberCount; i++){	//��ʼ����������
		random_numbers[i] = rand() % kNumberCap;
		nums_for_bubble[i] = random_numbers[i];
		nums_for_selection[i] = random_numbers[i];
		nums_for_insertion[i] = random_numbers[i];
	}
	
	//�����������
	
	//printf("������ʹ�õ��̸߳���(3/5/6):");
	//scanf("%d", &thread_count);

	//������߳��������
	initialize_threads(nums_for_bubble);
	
	//�鲢�����̵߳�������
	/*
	parameters * merge_param = (parameters *) malloc(sizeof(parameters));
	merge_param->numbers = &random_numbers;
	merge_param->start = 0;
	merge_param->end = kNumberCount - 1;
	
	pthread_t merge;
	pthread_create(&merge, NULL, bubble_sort, (void *) merge_param);
	pthread_join(merge, NULL);
	*/
	
	//�������
	
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

//ð������
//!!!�Ż�Ϊ˫��ð�����򣺴Ӻ�ǰ��������Сֵ��λ
void * bubble_sort(void * params){
	parameters * data = (parameters *) params;
	int start = data->start;
	int end = data->end;
	int i, j, swap_temp;
	
	for(i = start; i <= end; i++){
	//������ܱ���
		bool is_sorted = true;
		for(j = start; j <= start + end - 1 - i; j++){
		//�Ƚ�ÿһ������Ԫ�أ�ͬʱ��������Ԫ�صĶ���Ƚ�
			if((*data->numbers)[j] > (*data->numbers)[j + 1]){
			//�Ƚ�����Ԫ�ش�С��ǰ��>�����򽻻�
				is_sorted = false;
				swap_temp = (*data->numbers)[j];
				(*data->numbers)[j] = (*data->numbers)[j + 1];
				(*data->numbers)[j + 1] = swap_temp;
			}
		}
		if(is_sorted == true){
		//���˴α����������Ѿ���������ֹ����
			return NULL;
		}
	}
	return NULL;
}

//ѡ������
//!!!�Ż�Ϊ˫��ѡ������ͬʱ�����ֵ�鵽���
void * selection_sort(void * params){
	parameters * data = (parameters *) params;
	int start = data->start;
	int end = data->end;
	int i, j, min_index, swap_temp;
	for(i = start; i <= end; i++){
	//������ܱ���
		min_index = i;	//��ʼ����СԪ���±�
		for(j = i + 1; j <= end; j++){
		//�ҳ����α�������СԪ�ص��±�
			if((*data->numbers)[j] < (*data->numbers)[min_index]){
				min_index = j;
			}
		}
		//�����α�������СԪ�ػ�����ǰ��
		swap_temp = (*data->numbers)[i];
		(*data->numbers)[i] = (*data->numbers)[min_index];
		(*data->numbers)[min_index] = swap_temp;
	}
	return NULL;
}

//��������
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

//�������
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