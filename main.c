#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int main(){

	/*��ʼ����������*/
	
	int random_numbers[90];
	int i;
	
	//��ʼ�������������
	time_t t;
	srand((unsigned) time(&t));
	
	for(i = 0; i < 90; i++){
		random_numbers[i] = rand() % 90000;
		printf("%d\n", random_numbers[i]);
	}
	return 0;
}