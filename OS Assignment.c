#include<stdio.h>
#include <stdlib.h>
struct processes{
	int prio;
	int bt;
	int rt;
	int at;
};

void get_Input();
void prtq(struct processes *q,int size);
void prtqI(struct processes);
void prtq(struct processes *,int);
void Round_Robin();
void Priority_Sorting();
void FC_FS();


int q1_n=0,q2_n=0,q3_n=0,n=0; 

struct processes *q1,*q2,*q3;

int time_quant = 4;

void get_Input()
{
	printf("\n Total Number of processes:\t");
	scanf("%d",&n);

	q1 = (struct processes *)malloc(n*sizeof(struct processes));
	q2 = (struct processes *)malloc(n*sizeof(struct processes));
	q3 = (struct processes *)malloc(n*sizeof(struct processes));
	int i=0;
	for(i=0;i<n;i++){
		struct processes p;
		printf("\n\t\tprocesses %d\n********************************************************\n\n",i+1);
		p.at = (rand())%(n+1);				
		printf("prio (1-9):\t");
		scanf("%d",&p.prio);
		printf("\nBurst Time: %d\t",p.bt);
		scanf("%d",&p.bt);
		p.rt = p.bt;

		if(p.prio>0 && p.prio<=3)
		{
			q1[q1_n++]  = p;
		}
		else if(p.prio>3 && p.prio<=6)
		{
			q2[q2_n++] = p;
		}
		else
		{
			q3[q3_n++] = p;
		}		
	}
}

void prtq(struct processes *q,int size)
{	
	printf("\nprio\t\tBurst Time\t\tArrival");
	printf("\n*********************************************************************************\n");
	int i=0;
	for(i=0;i<size;i++)
	{
		prtqI(q[i]);
	}
	printf("\n\n\n");
}

void prtqI(struct processes p){
	printf("\n%d\t\t\t%d\t\t%d",p.prio,p.bt,p.at);
}


void Round_RobinAlgo(struct processes *q,int size){
	int time=0,i=0,remain=size,flag=0,total_times=0;
	for(time=0,i=0;remain!=0;){
		struct processes p = q[i];
		if(p.rt<=time_quant && p.rt>0){
			time += p.rt;
			p.rt = 0;
			flag = 1;
		}else if(p.rt>time_quant){
			p.rt -= time_quant;
			time += time_quant;
		}
		if(p.rt==0 && flag==1){
			remain--;
			printf("\n%d\t\t\t%d",p.prio,p.bt);
			flag = 0;
		}
		
		if(i==remain-1){
			i=0;
		}else if(q[i+1].at<time){
			i++;
		}else{
			i=0;
		}

		q[i] = p;
	}
	 	
}
void Round_Robin(){
	printf("\n\n****************************************************************************");
	printf("\n\t\tRound Robin\t");
	printf("\n****************************************************************************\n\n");

	printf("\nprio\t\tBurst Time");
	printf("\n****************************************************************************\n");
	

	Round_RobinAlgo(q3,q3_n);
}
void Priority_SortingAlgo(struct processes *q,int size){
	int i=0;
	int j=0;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(q[j].prio>q[i].prio){
				struct processes t = q[i];
				q[i] = q[j];
				q[j] = t;
			}
		}
	}
}
void Priority_Sorting(){
	printf("\n\n\n****************************************************************************");
	printf("\n\n\t\tPriority Sorting\t");
	printf("\n\n****************************************************************************\n\n\n");
	Priority_SortingAlgo(q2,q2_n);
	prtq(q2,q2_n);
}
void FC_FSAlgo(struct processes *q,int size){
	int i=0;
	int j=0;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(q[j].at>q[i].at){
				struct processes t = q[i];
				q[i] = q[j];
				q[j] = t;
			}
		}
	}
}

void FC_FS(){
	printf("\n\n****************************************************************************");
	printf("\n\t\tFirst_Come_First_Serve\t");
	printf("\n****************************************************************************\n\n");
	FC_FSAlgo(q1,q1_n);
	prtq(q1,q1_n);
}

int main(){
	get_Input();
	int i=1;
	while(n>0){
		if(i==1)
		{
			FC_FS();
		}
		else if(i==2)
		{
			Priority_Sorting();
		}
		else if(i==3)
		{
			Round_Robin();	
		}
		i++;
		sleep(10);
		printf("\n\n");
	}
}


