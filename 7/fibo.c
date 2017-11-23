/**
 Fibonacci Programming
 FILE	fibo.c
 DATE	2017-11-23
 AUTHOR Lee Young Hyun
 */


#include <stdio.h>
#include <stdlib.h>

static int cnt = 0;

int fibo(int n, int * arr) {

	printf("%d번째 호출: Fibo(%d)\n", cnt+1, n);
	cnt++;
	
	arr[n-1]++;

	if( n == 1 )
		return 0;
	else if( n == 2)
		return 1;

	return fibo( n - 1, arr) + fibo(n  - 2, arr);
}

int main(void) {
	int num, i;
	int * arr;

	while(1) {
		printf("-----n번째 수열 입력-----: "); scanf("%d", &num);
		if(num == 0)
			return 0;

		arr = (int *)malloc(sizeof(int) * num);

		for(i=0; i<num; i++)
			arr[i] = 0;

		printf("Fibo(%d)의 값: %d\n\n", num, fibo(num, arr));

		for(i=0; i<num; i++)
			printf("Fibo(%d)의 호출 횟수: %d\n", i+1, arr[i]);
	}
}