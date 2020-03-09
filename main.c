#include <stdio.h>
#include <stdlib.h>
//#include <pthread.h>
//!!!�����̺߳���linux�����½��к�������
#include <time.h>
#include <stdbool.h>
#define kNumberCount 10	//��������������Ԫ�ظ���
#define kNumberCap 100	//��������������Ԫ��ֵ������

void bubble_sort(int numbers[], int start, int end);
void selection_sort(int numbers[], int start, int end);
void insertion_sort(int numbers[], int start, int end);

int main(){
	int random_numbers[kNumberCount];
	int i;
	srand((unsigned) time(0));	//��ʼ���������������
	for(i = 0; i < kNumberCount; i++){	//��ʼ����������
		random_numbers[i] = rand() % kNumberCap;
		printf("%d\n", random_numbers[i]);
	}
	
	//����ð������
	//bubble_sort(random_numbers, 0, kNumberCount);
	
	//����ѡ������
	selection_sort(random_numbers, 0, kNumberCount);
	
	//���ò�������
	//insertion_sort(random_numbers, 0, kNumberCount);
	
	//���������
	printf("=========\n");
	for(i = 0; i < kNumberCount; i++){
		printf("%d\n", random_numbers[i]);
	}
	
	return 0;
}

//ð������
//!!!�Ż�Ϊ˫��ð�����򣺴Ӻ�ǰ��������Сֵ��λ
void bubble_sort(int numbers[], int start, int end){
	int i, j, swap_temp;
	for(i = start; i < end; i++){	
	//������ܱ���
		bool is_sorted = true;
		for(j = 0; j < end - 1 - i; j++){
		//�Ƚ�ÿһ������Ԫ�أ�ͬʱ��������Ԫ�صĶ���Ƚ�
			if(numbers[j] > numbers[j + 1]){
			//�Ƚ�����Ԫ�ش�С��ǰ��>�����򽻻�
				is_sorted = false;
				swap_temp = numbers[j];
				numbers[j] = numbers[j + 1];
				numbers[j + 1] = swap_temp;
			}
		}
		if(is_sorted == true){
		//���˴α����������Ѿ���������ֹ����
			return;
		}
	}
}

//ѡ������
//!!!�Ż�Ϊ˫��ѡ������ͬʱ�����ֵ�鵽���
void selection_sort(int numbers[], int start, int end){
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
void insertion_sort(int numbers[], int start, int end){
	//����������ûд�أ�������ʦ.gif��
}