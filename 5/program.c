/**
calculation of circle Area
FILE	program.c
DATE	2017-11-23
AUTHOR Lee Young Hyun
*/

#include <stdio.h>

#define PI 3.14

int main(void){
	FILE *fp;
	int num[11];
	int i=0;
	double result[11];

	fp = fopen("data_r.txt", "r");

	
	for(i=0; i< 11; i++){
	fscanf(fp,"%d", &num[i]);
	}
	

	for(i=0; i< 10; i++){
	result[i+1] = PI * (double)num[i+1] * (double)num[i+1];
	printf("%.2lf ",result[i+1]);
	}
	fclose(fp);

	return 0;
}