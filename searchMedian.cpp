#include "algorithm.h"

//输入  每级像素数目数组 ,像素总数
//输出  级数
int  searchMedian(int a[],int num){
	int sum = 0;
	for (int i = 0; i < num; i++){
		sum += a[i];
		if (sum >= num / 2){
			return i;
		}
	}
}