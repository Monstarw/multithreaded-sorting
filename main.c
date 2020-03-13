#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#define kNumberCount 10	//��������������Ԫ�ظ���
#define kNumberCap 100	//��������������Ԫ��ֵ������
#define kThreadCount 1

typedef struct parameters{
	int (* numbers)[kNumberCount];
	int start;
	int end;
}parameters;

void * bubble_sort(void * params);
//void * selection_sort(parameters * params);
//void * insertion_sort(parameters * params);

int main(){
	int random_numbers[kNumberCount];
	int i, j = 0;
	//int thread_count;	//ʹ�õ��̸߳���
	
	srand((unsigned) time(0));	//��ʼ���������������
	for(i = 0; i < kNumberCount; i++){	//��ʼ����������
		random_numbers[i] = rand() % kNumberCap;
		printf("%d\n", random_numbers[i]);
	}
	
	//printf("������ʹ�õ��̸߳���(3/5/6):");
	//scanf("%d", &thread_count);

	parameters * param[kThreadCount];
	for(i = 0; i < kThreadCount; i++){
		param[i] = (parameters *) malloc(sizeof(parameters));
		//parameters * param0 = (parameters *) malloc(sizeof(parameters));
		param[i]->numbers = &random_numbers;
		param[i]->start = j;
		j = j + kNumberCount / kThreadCount;
		param[i]->end = j - 1;
	}
	
	pthread_t thread[kThreadCount];
	
	for(i = 0; i < kThreadCount; i++){
		pthread_create(&thread[i], NULL, bubble_sort, (void *) param[i]);
	}
	for(i = 0; i < kThreadCount; i++){
		pthread_join(thread[i], NULL);
	}
	
	//����ð������
	//bubble_sort(random_numbers, 0, kNumberCount);
	
	//����ѡ������
	//selection_sort(random_numbers, 0, kNumberCount);
	
	//���ò�������
	//insertion_sort(random_numbers, 0, kNumberCount);
	
	//���������
	printf("\n");
	for(i = 0; i < kNumberCount; i++){
		printf("%d\n", random_numbers[i]);
	}
	
	return 0;
}

//ð������
//!!!�Ż�Ϊ˫��ð�����򣺴Ӻ�ǰ��������Сֵ��λ
void * bubble_sort(void * params){
	parameters * data = (parameters *) params;
	int start = data->start;
	int end = data->end;
	int i, j, swap_temp;
	
	for(i = start; i < end; i++){
	//������ܱ���
		bool is_sorted = true;
		for(j = 0; j < end - 1 - i; j++){
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
/*
//ѡ������
//!!!�Ż�Ϊ˫��ѡ������ͬʱ�����ֵ�鵽���
void selection_sort(parameters * params){
	int i, j, min_index, swap_temp;
	for(i = start; i < end; i++){
	//������ܱ���
		min_index = i;	//��ʼ����СԪ���±�
		for(j = i + 1; j < end; j++){
		//�ҳ����α�������СԪ�ص��±�
			if(numbers[j] < numbers[min_index]){
				min_index = j;
			}
		}
		//�����α�������СԪ�ػ�����ǰ��
		swap_temp = numbers[i];
		numbers[i] = numbers[min_index];
		numbers[min_index] = swap_temp;
	}
}

//��������
void insertion_sort(parameters * params){
	int i, j, swap_temp;
	for(i = start + 1; i < end; i++){
		for(){

		}
		
		
		
		swap_temp = numbers[i];
		numbers[i] = numbers[j];
		numbers[j] = swap_temp;
	}
}
*/