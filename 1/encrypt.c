/**
String Print problem
FILE	encrypt.c
DATE	2017-11-23
AUTHOR Lee Young Hyun
*/

#include <stdio.h>
#include <string.h>

int main(void) {
	char str[5];
	int key;
	int mod;
	char passward[5];
	int i;
	int index;

	printf("Input string : "); scanf("%s", str);
	printf("Input Key : "); scanf("%d", &key);

	mod = key % 26;

	for(i=0; i<4; i++) {
		index = str[i] - 97;
		passward[i] = (((index + (i+1) * mod) % 26) + 97);
	}
	passward[4] = '\0';

	printf("Encrypted data : %s\n", passward);
	return;
}
