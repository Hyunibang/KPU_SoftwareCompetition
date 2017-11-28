/**
Alphabet Count problem
FILE	debug_3.c
DATE	2017-11-23
AUTHOR Lee Young Hyun
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char c;
	FILE *fp;
	int freq[52];
	int index;
	int i;

	fp = fopen("C:\\Temp\\data_eng.txt", "rt");
	if( fp == NULL )
	{
		printf("<error> 파일 오픈 실패 \n");
		return 0;
	}

	for(i=0; i<52; i++)
		freq[i] = 0;


	while( (c=fgetc(fp)) != EOF )
	{
		if( c >= 'a' && c <= 'z' )
		{
			freq[ 'z'- c ]++;
		}
		else if( c >= 'A' && c <= 'Z' )
		{
			freq[ c - 39 ]++;
		}
	}

	printf("> 각 글자별 빈도수 \n");
	for( index=0; index<('z'-'a'+1); index++)
	{
		printf(" %c :  %d \n", 'a'+index, freq[index] );
	}
	for( index=0; index<('Z'-'A'+1); index++)
	{
		printf(" %c :  %d \n", 'A'+index, freq[26+index] );
	}
	return 0;
}