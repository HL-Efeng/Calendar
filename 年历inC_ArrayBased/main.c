#include<stdio.h>
#include"calendar.h"
int main(){
	int y=0,m=0,d=0;
	char c;
	int con=1;//Continue 遇到\n则不再读取
	for(;con;){
		c=getchar();
		if(c==' ')break;
		if(c=='\n'){
			con=0;
			break;
		}
		y*=10;
		y+=(c-48);
	}
	for(;con;){
		c=getchar();
		if(c==' ')break;
		if(c=='\n'){
			con=0;
			break;
		}
		m*=10;
		m+=(c-48);
	}
	for(;con;){
		c=getchar();
		if(c==' ')break;
		if(c=='\n')break;
		d*=10;
		d+=(c-48);
	}
	if(!m)Func1(y);
	else if(!d)Func2(y,m);
	else{
		Func3_ArrayBased(y,m,d);
		printf("\n是这一年第%d天\n",DoY(y,m,d));
		char wkName[7][2]={"日","一","二","三","四","五","六"};
		printf("是第%d周周%2.2s\n",(DoY(y,m,d)-m1w(y,1))/7+1,wkName[(DoY(y,m,d)-m1w(y,1))%7]);
	}
	main();
}
