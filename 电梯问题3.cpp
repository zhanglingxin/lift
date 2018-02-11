#include<stdio.h>
#include<stdlib.h>
void pickup(int ,int ,int ,int *,int* );
void stop(int*);
int getData(char);
void lift(char*);
/*function that generate all pickup possibility*/
void getComb(int); /*get all Possible pickup*/
void writeComb(); /*write pickup order*/
void swap(int, int); /*support function for getComb*/
 
/*define comb vars*/
int a[5];
int pickupOrder[120][5];
int combCount=0; 
/*define possible time cost for pickup*/
int leastCost=1000;
int leastCostPickup=0;

int main()
{
    int i,j;
 /*define vars and initial vars,
  time is realworld time, 
  floor is lifter floor at last state
 */
 int time=0,floor=1;
 /*define passenger var*/
 int passengerFloor=1;
 int targetFloor=1;
 int requestTime=0;
 /*define tmp var for processing input*/
 char input[5][100]={'\0'};
 int in[5][100];
 char tmp[2];
 
 /* get request : 5 inputs */
 int cot1=0,cot2=0;
 int cota[5]={0},cotb[5]={0};
 printf("input:(5 input,for example: 0 1 2    0 8 1   1 2 3   1 2 5   3 1 0)\n");
 for(i=0;i<5;i++)
 {
 	for(j=0;j<3;j++)
 	{
 		if(j<2)
 		scanf("%d ",&in[i][j]);
 		else scanf("%d",&in[i][j]);
	 }
  } 
  for(i=0;i<5;i++)
  {
  	for(j=0;j<3;j++)
  	{
  		input[i][j]=in[i][j]+48;
	  }
  }
  for(i=0;i<4;i++)
  {
  	if(input[i][1]!=input[i+1][1])
  	{
  		cota[i]++;
	  }
	  if(input[i][2]!=input[i+1][2])
	  cotb[i]++;
	  cot1+=cota[i];
	  cot2+=cotb[i];
   } 

 //scanf("%s %s %s %s %s",in[0],in[1],in[2],in[3],in[4]);
 //printf("last lifter status:[time:%d,floor:%d]\n",time,floor);
 //printf("passenger request: [%s %s %s %s %s]\n",input[0],input[1],input[2],input[3],input[4]);

/* get all pick up possibility*/
    for(i = 0; i < 5; i++)
	{
        a[i] = i ;
    }
    getComb(0);
    /* display all possible pickup*/
    //for(j=0;j<120;j++){
     //for (i=0;i<5;i++){
     //printf("%d ",pickupOrder[j][i]);
     //}
     //printf("\n");
   // }


 /*process all pickup order*/
 for(j=0;j<120;j++)
 {
 /*process request data for each pickup order*/
 for(i=0;i<5;i++)
 {
 requestTime=getData(input[pickupOrder[j][i]][0]);
 passengerFloor=getData(input[pickupOrder[j][i]][1]);
 targetFloor=getData(input[pickupOrder[j][i]][2]);

 /* process floor 10 special case*/

 if(passengerFloor==0) passengerFloor=10;
 if(targetFloor==0) targetFloor=10;

 /* lifter basic actions*/
 pickup(passengerFloor,targetFloor,requestTime,&time,&floor);
 stop(&time);

 /*disply last result*/ 
 }
 //printf("last state for pickup[%d]:time cost:%d , stop floor :%d\n",j,time,floor); 
//printf("last lifter status:[time:%d,floor:%d]\n",time,floor);
 /* choose best pickup order by least time*/

 if (time<leastCost) 
 {
  leastCost=time;
  leastCostPickup=j;
 }
 /*reset lift to original state for each pick up order*/
 time=0;
 floor=1;
 }
 if(cot1==0&&cot2==0)
{
	time=0;
	 pickup(passengerFloor,targetFloor,requestTime,&time,&floor);
 stop(&time);
 leastCost=time; 
}
else if(cot1!=0&&cot2==0)
{
	time=0;
	for(int k=0;k<5;k++)
	{
 			stop(&time);
	}
	pickup(passengerFloor,targetFloor,requestTime,&time,&floor);
leastCost=time;	
}
 
 printf("the best pick time cost is:%d\n",leastCost);
 for(i=0;i<5;i++)
 {
  printf("%d[%s] ",pickupOrder[leastCostPickup][i],input[pickupOrder[leastCostPickup][i]]);

 } 


 return 0;

 } 
void stop(int* time)
{
 *time+=1; 
}
void pickup(int passengerFloor,int targetFloor,int requestTime,int *time,int* floor)
{
 *time+=requestTime;
 *time+=(abs)(*floor - passengerFloor);    
 *time+=(abs)(passengerFloor-targetFloor);    
 *floor=targetFloor;
}
int getData(char data){
 char tmp[2];
 tmp[0]=data;
 tmp[1]='\0';
 return atoi(tmp);
 }

void getComb(int offset){
    int i, temp;
    if(offset == 5-1){  // BaseCase
        writeComb();
        return;
    }else{
        for(i = offset;i < 5; ++i){
            swap(i, offset);//swap 
            getComb(offset + 1);//recursive
            swap(i, offset);//swap back
        }
    }
}

void writeComb(){
    int i;
    for(i = 0; i < 5; ++i)
    {
      pickupOrder[combCount][i]=a[i];
    }
    combCount++;
}

void swap(int i, int offset){
    int temp;
    temp = a[offset];
    a[offset] = a[i];
    a[i] = temp;
}

