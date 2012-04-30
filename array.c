#include<stdio.h>
void printNum(int * num,int size){
int i=0;
 for( i=size-1;i>-1;i--){
      printf("%d",num[i]);
 }
      printf("\n");
}
int main(){
  const int length=40;
	int p,tmp=1;
	int i=0,j=0,r=0,k=0;
	int num [length];
	int size=1;
	for(i=0;i<length;i++){
		num[i]=0;
	}
num[0]=1;
	/*-----------------------------*/
printf("input a num n ,then we will compute n!:");
	scanf("%d",&p);
	for(i=1;i<=p;i++){
           for(j=0;j<size;j++){
              num[j]*=i;
           }
         for(j=0;j<size;j++){
               if(num[size-1]>10){
                     size++;
                 } 
             if (num[j]>10){
                    num[j+1]+=(num[j]/10);
                    num[j]=num[j]%10;
             }
         }
	}
printf("%s%d%s","the ",p,"! =");
printNum(num,length);
	return 0;
}
