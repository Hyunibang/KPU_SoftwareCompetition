/**
Lotto Algorithm problem
FILE	problem1.c
DATE	2017-11-23
AUTHOR Lee Young Hyun
*/


#include <stdio.h>
#include <stdlib.h>

#define true	1
#define false	0

typedef struct {
	int num[5];
	int serial;
}RandomCard;
	
typedef struct {
	RandomCard fisrt[11000];
	int numOfPerson;
	int prize;
}FirstPrize;

typedef struct {
	RandomCard second[11000];
	int numOfPerson;
	int prize;
}SecondPrize;

typedef struct {
	RandomCard third[11000];
	int numOfPerson;
	int prize;
}ThirdPrize;

typedef struct {
	RandomCard forth[11000];
	int numOfPerson;
	int prize;
}ForthPrize;

typedef struct {
	RandomCard ** rand;
	int goal[5]; // 당첨번호

	int fullnum; // 총 인원수
	int gigum; // 기금
	int income; //매출
	int totalprize; // 상금액

	FirstPrize * first;
	SecondPrize * second;
	ThirdPrize * third;
	ForthPrize * forth;
}TotalPrize;

void TotalInit(TotalPrize * tp) {
	FILE * file;
		
	file = fopen("win_01.txt", "rt");

	if(file == NULL)
	{
		printf("shit\n");
		exit(-1);
	}
	fscanf(file, "%d	%d	%d	%d	%d", &tp->goal[0], &tp->goal[1], &tp->goal[2], &tp->goal[3], &tp->goal[4]);
	fclose(file);

	tp->rand = (RandomCard **)malloc(sizeof(RandomCard *) * 11000);
	tp->fullnum = 0;
	tp->gigum = 0;
	tp->income = 0;

	tp->first = (FirstPrize *)malloc(sizeof(FirstPrize));
	tp->first->numOfPerson = 0;
	
	tp->second = (SecondPrize *)malloc(sizeof(SecondPrize));
	tp->second->numOfPerson = 0;

	tp->third = (ThirdPrize *)malloc(sizeof(ThirdPrize));
	tp->third->numOfPerson = 0;

	tp->forth = (ForthPrize *)malloc(sizeof(ForthPrize));
	tp->forth->numOfPerson = 0;
}

void FileInput(TotalPrize * tp) {
	FILE * file = fopen("sales_01.txt", "rt");
	RandomCard * temp;

	if(file == NULL)
	{
		printf("shit");
		exit(-1);
	}

	while(!(feof(file))) {
		temp = (RandomCard *)malloc(sizeof(RandomCard));
		fscanf(file, "%d	%d	%d	%d	%d	%d\n", &temp->serial, &temp->num[0], &temp->num[1],  &temp->num[2], &temp->num[3], &temp->num[4]);

		tp->income += 1000;
		tp->rand[tp->fullnum++] = temp;
	}

	fclose(file);

}

int ThirdCompare(RandomCard * rc, int * goal) {
	int i=0;
	for(i=0; i<5; i++) {
		if(rc->num[i] != goal[i])
			return false;
	}
	return true;
}

int ForthCompare(RandomCard * rc, int * goal) {
	int i, j;
	int least1 = 0, least2=0;
	int temp1[5];
	int temp2[5];

	for(i=0; i< 4; i++){
		least1 = i;
		least2 = i;
		for(j=i+1; j<5; j++) {
			if(rc->num[least1] > rc->num[j])
				least1 = j;
			if(goal[least2] > goal[j])
				least2 = j;
		}

		temp1[i] = rc->num[least1];
		temp2[i] = goal[least2];
	}

	for(i=0; i<5; i++) {
		if(temp1[i] != temp2[i])
			return false;
	}
	return true;
}

int Prize(TotalPrize * tp) {
	int i, j;

	for(i = 0; i<tp->fullnum; i++) {
		if((tp->rand[i]->num[0] == tp->goal[0]) && (tp->rand[i]->num[1] == tp->goal[1]) && (tp->rand[i]->num[2] == tp->goal[2]) && (tp->rand[i]->num[3] == tp->goal[3]) && (tp->rand[i]->num[4] == tp->goal[4]))
		{
			tp->first->fisrt[tp->first->numOfPerson++] = *tp->rand[i];
		}
		else if((tp->rand[i]->num[0] == tp->goal[0]) && (tp->rand[i]->num[1] == tp->goal[1]) && (tp->rand[i]->num[2] == tp->goal[2]) && (tp->rand[i]->num[3] == tp->goal[3]))
		{
			tp->second->second[tp->second->numOfPerson++] = *tp->rand[i];
		}
		else if(ThirdCompare(tp->rand[i], tp->goal))
		{
			tp->third->third[tp->third->numOfPerson++] = *tp->rand[i];
		}
		else if(ForthCompare(tp->rand[i], tp->goal))
		{
			tp->forth->forth[tp->forth->numOfPerson++] = *tp->rand[i];
		}
	}
	return true;
}

void PrintResult(TotalPrize * tp) {
	FILE * file = fopen("result_01.txt", "wt");
	int i = 0;
	int temp;
	int fprizeperson;
	int sprizeperson;
	int tprizeperson;
	int foprizeperson;

	if(file == NULL) {
		printf("fuck!\n");
		exit(-1);
	}

	
	tp->totalprize = tp->income / 100 * 50; // 총 배당금액
	tp->gigum = tp->income / 100 * 50; // 기금 계산
	temp = tp->totalprize;
	tp->first->prize = temp / 100 * 50;
	temp = temp - tp->first->prize;
	tp->second->prize = temp / 100 * 50;
	temp = temp - tp->second->prize;
	tp->third->prize = temp / 100 * 50;
	temp = temp - tp->third->prize;
	tp->forth->prize = temp;

	if(tp->first->numOfPerson == 0)
	{
		tp->gigum += tp->first->prize;
		tp->first->prize = 0;
	}
	if(tp->second->numOfPerson == 0)
	{
		tp->gigum += tp->second->prize;
		tp->second->prize = 0;
	}
	if(tp->third->numOfPerson == 0)
	{
		tp->gigum += tp->third->prize;
		tp->third->prize = 0;
	}
	if(tp->forth->numOfPerson == 0)
	{
		tp->gigum += tp->forth->prize;
		tp->forth->prize = 0;
	}

	if(tp->first->numOfPerson != 0)
	{
		int temp;
		fprizeperson = tp->first->prize / tp->first->numOfPerson;
		temp = fprizeperson % 100; 
		tp->gigum += temp * tp->first->numOfPerson;

		fprizeperson -= temp;
	}

	if(tp->second->numOfPerson != 0)
	{
		int temp;
		sprizeperson = tp->second->prize / tp->second->numOfPerson;
		temp = sprizeperson % 100; 
		tp->gigum += temp * tp->second->numOfPerson;

		sprizeperson -= temp;
	}

	if(tp->third->numOfPerson != 0)
	{
		int temp;
		tprizeperson = tp->third->prize / tp->third->numOfPerson;
		temp = tprizeperson % 100; 
		tp->gigum += temp * tp->third->numOfPerson;

		tprizeperson -= temp;
	}

	if(tp->forth->numOfPerson != 0)
	{
		int temp;
		foprizeperson = tp->forth->prize / tp->forth->numOfPerson;
		temp = foprizeperson % 100; 
		tp->gigum += temp * tp->forth->numOfPerson;

		foprizeperson -= temp;
	}


	fputs("- 총 판매량: ", file);
	fprintf(file, "%d장\n", tp->fullnum);
	fputs("- 총 판매금액: ", file);
	fprintf(file, "%d원\n", tp->fullnum * 1000);
	fputs("- 총 기금 편입금액: ", file);
	fprintf(file, "%d원\n", tp->gigum);
	fputs("- 총 배당금액: ", file);
	fprintf(file, "%d원\n", tp->totalprize);
	fputs("- 당첨번호: ",file);
	fprintf(file, " %d %d %d %d %d\n", tp->goal[0], tp->goal[1], tp->goal[2], tp->goal[3], tp->goal[4]);

	fprintf(file, "- 1등상 당첨자 수 및 배당 금액 : %d장, %d원\n", tp->first->numOfPerson, tp->first->prize);
	for(i=0; i<tp->first->numOfPerson; i++) {
		fprintf(file, "	%d	%d	%d %d %d %d %d %d원\n", i+1, tp->first->fisrt[i].serial, tp->first->fisrt[i].num[0], tp->first->fisrt[i].num[1], tp->first->fisrt[i].num[2], tp->first->fisrt[i].num[3], tp->first->fisrt[i].num[4], fprizeperson);
	}

	fprintf(file, "- 아차상 당첨자 수 및 배당 금액 : %d장, %d원\n", tp->second->numOfPerson, tp->second->prize);
	for(i=0; i<tp->second->numOfPerson; i++) {
		fprintf(file, "	%d	%d	%d %d %d %d %d %d원\n", i+1, tp->second->second[i].serial, tp->second->second[i].num[0], tp->second->second[i].num[1], tp->second->second[i].num[2], tp->second->second[i].num[3], tp->second->second[i].num[4], sprizeperson);
	}
	fprintf(file, "- 차차상 당첨자 수 및 배당 금액 : %d장, %d원\n", tp->third->numOfPerson, tp->third->prize);
	for(i=0; i<tp->third->numOfPerson; i++) {
		fprintf(file, "	%d	%d	%d %d %d %d %d %d원\n", i+1, tp->third->third[i].serial, tp->third->third[i].num[0], tp->third->third[i].num[1], tp->third->third[i].num[2], tp->third->third[i].num[3], tp->third->third[i].num[4], tprizeperson);
	}
	fprintf(file, "- 셔플상 당첨자 수 및 배당 금액 : %d장, %d원\n", tp->forth->numOfPerson, tp->forth->prize);
	for(i=0; i<tp->forth->numOfPerson; i++) {
		fprintf(file, "	%d	%d	%d %d %d %d %d %d원\n", i+1, tp->forth->forth[i].serial, tp->forth->forth[i].num[0], tp->forth->forth[i].num[1], tp->forth->forth[i].num[2], tp->forth->forth[i].num[3], tp->forth->forth[i].num[4], foprizeperson);
	}
}

int main(void) {
	TotalPrize tp;

	TotalInit(&tp);

	FileInput(&tp);
	Prize(&tp);

	PrintResult(&tp);
	return 0;
}