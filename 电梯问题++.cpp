#include<stdio.h>
#include<stdlib.h>
//int time=0; 
void lift(char*);
void pickup(int ,int ,int ,int *,int* );
void stop(int*);
int getData(char);

int main()
{
int i,j;
char input[100];
 printf("input:\n");
scanf("%s",input);
lift(input);


 return 0;
}
void lift(char a[])//模拟电梯的函数 
{
	 /*define vars and initial vars,
  time is realworld time, 
  floor is lifter floor at last state
 */
 int i,j;
 int time1=0, floor=1,time2=0;
 /*define passenger var*/
 int passengerFloor=1;
 int targetFloor=1;
 int requestTime=0;
 /*define tmp var for processing input*/
 char input[100];
 for(i=0;i<3;i++)
 input[i]=a[i];
 char tmp[2];
	 printf("last lifter status:[time:%d,floor:%d]\n",time1,floor);
 printf("passenger request: [%s]\n",input);
 
 /*process request data*/
 requestTime=getData(input[0]);
 passengerFloor=getData(input[1]);
 targetFloor=getData(input[2]);

 /* process floor 10 special case*/

 if(passengerFloor==0) passengerFloor=10;
 if(targetFloor==0) targetFloor=10;

 /* lifter basic actions*/
 pickup(passengerFloor,targetFloor,requestTime,&time1,&floor);
 stop(&time1);
 printf("stoptime: %d\n",time1-(abs)(passengerFloor-targetFloor)-1);
printf("stopfloor: %d\n",passengerFloor);
 /*disply final result*/ 
 printf("final state:time cost:%d , stop floor :%d\n",time1,floor); 
}
void stop(int* time1)
{
 *time1+=1; 
}
void pickup(int passengerFloor,int targetFloor,int requestTime,int *time1,int* floor)
{
 *time1+=requestTime;
 *time1+=(abs)(*floor - passengerFloor);    //printf("stoptime:%d",time);
 *time1+=(abs)(passengerFloor-targetFloor);  
 *floor=targetFloor;
}
int getData(char data){
 char tmp[2];
 tmp[0]=data;
 tmp[1]='\0';
 return atoi(tmp);
 }
