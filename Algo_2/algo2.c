/**
Parentheses problem
FILE	algo2.c
DATE	2017-11-23
AUTHOR Lee Young Hyun
*/

#include <stdio.h>
#include <stdlib.h>

typedef char element;

#define MAX 30

typedef struct Node{
	element data;
	struct Node *next;
}Stack;

Stack* ap;

void buffer(void){
	while(getchar()!='\n');
}

void push(element item)

{	
	Stack* temp=(Stack *)malloc(sizeof(Stack));
	if(temp==NULL){
		fprintf(stderr,"memory error\n");
		return;
	}
	temp->data = item;	
	temp->next = ap;
	ap = temp;
} 

element pop(void)
{ 
	element item;
	Stack* temp=ap; 
	
	if(ap == NULL)
	{ 	 
		return 0;
	} 
	else 
	{ 
		item = temp->data;
		ap = temp->next;
		free(temp);	
		return item;
	} 
} 

int main(int argc, char* argv[]){

	char sample[MAX];
	int cnt=0, count=0;
	int i=0;
	char dummy1[MAX], dummy2[MAX];
	printf("===== ������ �� =====\n");
	printf("�Է� : ");
	scanf("%s", sample);
	buffer();
	for(i=0; i<sizeof(sample); i++){
	push(sample[i]);
	if(sample[i] == '('){
		dummy1[cnt] = pop();
		cnt++;
		dummy2[cnt] = dummy1[cnt];
		}
	else if(sample[i] == ')'){
		dummy1[cnt] = pop();
		cnt++;
		dummy2[cnt] = dummy1[cnt];
		count = i+1;

	}
	}

	printf("��� : ");

	if(cnt %2 == 0 && dummy1[cnt-1] == ')'){
		for(i=0; i<cnt; i++)
		printf("%c", dummy1[i]);
		printf(" �����Դϴ�.\n");
	}
	else if(cnt %2 == 0 && dummy1[cnt-1] == '('){
		for(i=0; i<cnt; i++)
		printf("%c", dummy1[i]);
		printf(" %d��° ��ġ���� ������ ��ȣ �̽���ġ.\n", count);
	}
	else if(cnt %2 != 0){
		for(i=0; i<cnt; i++)
		printf("%c", dummy1[i]);
		printf(" ���� ��ȣ ������ ������ ��ȣ ���� ����ġ\n");
	}

	
	return 0;
}

