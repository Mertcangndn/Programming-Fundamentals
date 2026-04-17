#include <stdio.h>
int a=1;

float islem(float,float,int);

int main(void){
	float x,y;
	int z;
	char i;
	
	printf("X= ");
	scanf("%f",&x);
	printf("Y= ");
	scanf("%f",&y);
	printf("Islem Seciniz (1:+ 2:- 3:* 4:/): ");
	scanf("%d",&z);
	
	switch(z){
		case 1:
			i='+';
			break;
		case 2:
			i='-';
			break;
		case 3:
			i='x';
			break;
		case 4:
			i='/';
			break;
	}
	if(!(y==0&&z==4)){
	printf("%.2f %d %.2f = %.2f\n",x,i,y,islem(x,y,z));
	}
	else{
		printf("MATH ERROR");
	}
	return 0;
}

float islem(float a,float b, int c){
	
	switch(c){
		case 1:
			return a+b;
		case 2:
			return a-b;
		case 3:
			return a*b;
		case 4:
			if(b!=0){
				return a/b;
			}
			else{
				return -0;
			}
	}
	
}
