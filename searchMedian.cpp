#include "algorithm.h"

//����  ÿ��������Ŀ���� ,��������
//���  ����
int  searchMedian(int a[],int num){
	int sum = 0;
	for (int i = 0; i < num; i++){
		sum += a[i];
		if (sum >= num / 2){
			return i;
		}
	}
}