C语言编写一个随机生成电话号码且按大小排序的程序
```cpp
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>

#define MAX_NUM 100

void suijishu(char phone[]);
void paixu(char phone[MAX_NUM][12], int M);

int main(int argc, char * argv[])
{
	char phone[MAX_NUM][12];
	int count;
	int M;

	printf("输入需要几组号码\n");
	scanf("%d", &M);

	srand(time(0));
	for(count=0; count<M; count++)
	{
		memset(phone[count], 0, sizeof(phone[count]));
		suijishu(phone[count]);
	}

	paixu(phone, M);

	for(count=0; count<M; count++)
	{
		printf("Phone%02d:%s\n",count+1, phone[count]);
	}	
	return 0;
}

void suijishu(char phone[])
{
	int i;
	char p1[14][4]={"134","135","136","137","138","139","150","151","152","157","158","159","187","188"};

	strcpy( phone, p1[rand()%14]);
	for(i=3;i<11;i++)
		phone[i]=rand()%10 + '0';
}

void paixu(char phone[MAX_NUM][12], int M)
{
	int i,j;
	char temp[12];

	for(i=0; i<M-1; i++)
	{
		for(j=i+1; j< M;j++)
		{
			if(strcmp(phone[i], phone[j]) > 0)
			{
				strncpy(temp, phone[i], 11);
				strncpy(phone[i], phone[j], 11);
				strncpy(phone[j], temp, 11);
			}
		}
	}
}
```
