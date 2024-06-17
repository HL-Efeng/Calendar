#define LunarDateCode(A,B) A*32+B

//Functions
void head(int y,int g);//overall head
void sepl(int g);//seprate line
void mohead(int m);//month head
void wkhead();//week head
int isRUN(int y);//is Run-Nian 返回值为真假
int ds(int y,int m);//DaySumofMonth 返回值为给定年月的天数
int m1w(int y,int m);//month 1st day in week 返回给定年月的第一天是星期几。0=周日，1=周一
void wkl(int y,int m, int w);//WeekLine 
void mg(int y,int g,int f,int s);//MonthGroup
int DoY(int y,int m,int d);//Days in Year 返回值为给定日期为当年的第几天
//LunarDate只能读取日或月的一个，下面的函数获取最终农历日期
int ReadArray(int y,int m,int d);

int Func1 (int y);
int Func2 (int y,int m);
int Func3 (int y,int m,int d);
int Func3_ArrayBased(int y,int m,int d);
void PrintFest_A(int IsQingming,int LDate,int y,int m,int d);

//Declarations
#include<stdio.h>
void head(int y,int g){
    int headl=((30*(12/g))-4)/2;
    for(int i=0;i<headl;i++){
        printf("-");
    }
    printf("%d",y);
    for(int i=0;i<headl;i++){
        printf("-");
    }
    // cout<<endl;
}
void sepl(int g){
    int headl=((30*(12/g)));
    for(int i=0;i<headl;i++){
        printf("-");
    }
}
void mohead(int m){
    char mch[10][4]={"一","二","三","四","五","六","七","八","九","十"};
    for(int i=0;i<10;i++) printf(" ");
    switch(m){
        case 11:
        	printf("十一月");
            break;
        case 12:
        	printf("十二月");
            break;
        default:
        	printf(" %s月 ",mch[m-1]);
    }
    for(int i=0;i<10;i++) printf(" ");
}
void wkhead(){
    printf("   日  一  二  三  四  五  六");
}
int isRUN(int y){
    return y%4!=0?0:y%400==0?1:y%100==0?0:1;
}
int ds(int y,int m){
    int daynum[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    return daynum[m-1]+isRUN(y)*(m==2);
}
int m1w(int y,int m){
    // int sum=0;
    // for(int i=1905;i<y;i++){
    //     sum+=isRUN(i);
    //     sum+=365;
    //     //sum%=7;
    // }
    // for(int i=1;i<m;i++){
    //     sum+=ds(y,m);
    //     //sum%=7;
    // }
    // sum%=7;
    // return sum;
    int w=0;
    y-=m<=2;
    int mm=m+12*(m<=2);
    w=(1+1+2*mm+3*(mm+1)/5+y+y/4-y/100+y/400)%7;
    return w;
}
void wkl(int y,int m, int w){
    int c=m1w(y,m)-1;
    int count=1;
    int q=ds(y,m);//Quit date
    if(w==1)for(int i=0;i<m1w(y,m);i++)printf("    ");
    for(int i=0;i<ds(y,m);i++){
        c+=1;
        c%=7;
        if(c==0&&i!=0) count+=1;
        if(count==w){
            printf("  %2d",i+1);
            q=i+1;
        }
    }
    if((!(w==6&&count==5))&&q==ds(y,m))for(int i=c+1;i<7;i++)printf("    ");
    if(w==6&&count==5)for(int i=0;i<7;i++)printf("    ");
}
void mg(int y,int g,int f,int s){
    printf("  ");
    if(!f){
        for(int i=0;i<(12/g);i++){
            mohead(s+g*(i));
            if(i!=(12/g)-1)printf("    ");
        }
        printf("  \n");
        for(int i=0;i<(12/g);i++){
            wkhead();
            printf(" ");
        }
        printf("\n");
        // k=
        for(int j=0;j<6;j++){
            printf(" ");
            for(int i=0;i<(12/g);i++){
                wkl(y,s+g*(i),j+1);
                if(i!=(12/g)-1)printf("  ");
            }
            printf(" \n");
        }
    }
    else{
        for(int i=0;i<(12/g);i++){
            mohead((12/g)*(s-1)+i+1);
            if(i!=(12/g)-1)printf("    ");
        }
        printf("  \n");
        for(int i=0;i<(12/g);i++){
            wkhead();
            printf(" ");
        }
        printf("\n");
        for(int j=0;j<6;j++){
            printf(" ");
            for(int i=0;i<(12/g);i++){
                wkl(y,(12/g)*(s-1)+i+1,j+1);
                if(i!=(12/g)-1)printf("  ");
            }
            printf(" \n");
        }
    }
}
int DoY(int y,int m,int d){
		int days[2][12]={{31,28,31,30,31,30,31,31,30,31,30,31},{31,29,31,30,31,30,31,31,30,31,30,31}};
		int run=isRUN(y);
		int sum=d;
		for(int i=0;i<m-1;i++) sum +=days[run][i];
		return sum;
}

int Func1(int y){
	printf("输入组数：");
    int g=3;
	scanf("%d",&g);
	
	printf("输入方向(1为横向，0为竖向)：");
    int f=1;
    scanf("%d",&f);
    
    head(y,g);
    printf("\n");
    for(int i=0;i<g;i++){
        mg(y,g,f,i+1);
    }
    sepl(g);
    printf("\n以上为%d年%d组%s向年历\n",y,g,f?"横":"竖");

    return 0;
}
int Func2(int y,int m){
    int g=12;
    
    mohead(m);
    printf("\n");
    wkhead();
    printf("\n");
    for(int i=0;i<6;i++){
		wkl(y,m,i+1);
		printf("\n");
    }
    return 0;
}

//0~4 共5bit 春节日份
//5~6 共2bit 春节月份
//7~19 共13bit 13个月的大小月情况(如果无闰月，最后位无效)，大月为1,小月为0
//20~23 共4bit 记录闰月的月份，如果没有闰月为0
static const unsigned int LunarData[199] = {

     0x04AE53,0x0A5748,0x5526BD,0x0D2650,0x0D9544,
     0x46AAB9,0x056A4D,0x09AD42,0x24AEB6,0x04AE4A, //1901年-1910年

     0x6A4DBE,0x0A4D52,0x0D2546,0x5D52BA,0x0B544E,
     0x0D6A43,0x296D37,0x095B4B,0x749BC1,0x049754, //1911年-1920年

     0x0A4B48,0x5B25BC,0x06A550,0x06D445,0x4ADAB8,
     0x02B64D,0x095742,0x2497B7,0x04974A,0x664B3E, //1921年-1930年

     0x0D4A51,0x0EA546,0x56D4BA,0x05AD4E,0x02B644,
     0x393738,0x092E4B,0x7C96BF,0x0C9553,0x0D4A48, //1931年-1940年

     0x6DA53B,0x0B554F,0x056A45,0x4AADB9,0x025D4D,
     0x092D42,0x2C95B6,0x0A954A,0x7B4ABD,0x06CA51, //1941年-1950年

     0x0B5546,0x555ABB,0x04DA4E,0x0A5B43,0x352BB8,
     0x052B4C,0x8A953F,0x0E9552,0x06AA48,0x7AD53C, //1951年-1960年

     0x0AB54F,0x04B645,0x4A5739,0x0A574D,0x052642,
     0x3E9335,0x0D9549,0x75AABE,0x056A51,0x096D46, //1961年-1970年

     0x54AEBB,0x04AD4F,0x0A4D43,0x4D26B7,0x0D254B,
     0x8D52BF,0x0B5452,0x0B6A47,0x696D3C,0x095B50, //1971年-1980年

     0x049B45,0x4A4BB9,0x0A4B4D,0xAB25C2,0x06A554,
     0x06D449,0x6ADA3D,0x0AB651,0x093746,0x5497BB, //1981年-1990年

     0x04974F,0x064B44,0x36A537,0x0EA54A,0x86B2BF,
     0x05AC53,0x0AB647,0x5936BC,0x092E50,0x0C9645, //1991年-2000年

     0x4D4AB8,0x0D4A4C,0x0DA541,0x25AAB6,0x056A49,
     0x7AADBD,0x025D52,0x092D47,0x5C95BA,0x0A954E, //2001年-2010年

     0x0B4A43,0x4B5537,0x0AD54A,0x955ABF,0x04BA53,
     0x0A5B48,0x652BBC,0x052B50,0x0A9345,0x474AB9, //2011年-2020年

     0x06AA4C,0x0AD541,0x24DAB6,0x04B64A,0x69573D,
     0x0A4E51,0x0D2646,0x5E933A,0x0D534D,0x05AA43, //2021年-2030年

     0x36B537,0x096D4B,0xB4AEBF,0x04AD53,0x0A4D48,
     0x6D25BC,0x0D254F,0x0D5244,0x5DAA38,0x0B5A4C, //2031年-2040年

     0x056D41,0x24ADB6,0x049B4A,0x7A4BBE,0x0A4B51,
     0x0AA546,0x5B52BA,0x06D24E,0x0ADA42,0x355B37, //2041年-2050年

     0x09374B,0x8497C1,0x049753,0x064B48,0x66A53C,
     0x0EA54F,0x06B244,0x4AB638,0x0AAE4C,0x092E42, //2051年-2060年

     0x3C9735,0x0C9649,0x7D4ABD,0x0D4A51,0x0DA545,
     0x55AABA,0x056A4E,0x0A6D43,0x452EB7,0x052D4B, //2061年-2070年

     0x8A95BF,0x0A9553,0x0B4A47,0x6B553B,0x0AD54F,
     0x055A45,0x4A5D38,0x0A5B4C,0x052B42,0x3A93B6, //2071年-2080年

     0x069349,0x7729BD,0x06AA51,0x0AD546,0x54DABA,
     0x04B64E,0x0A5743,0x452738,0x0D264A,0x8E933E, //2081年-2090年

     0x0D5252,0x0DAA47,0x66B53B,0x056D4F,0x04AE45,
     0x4A4EB9,0x0A4D4C,0x0D1541,0x2D92B5 //2091年-2099年 

};
int ReadArray (int y,int m,int d){
	int LSFDays=DoY(y,((LunarData[y-1901]&0b000000000000000001100000)>>5),(LunarData[y-1901]&0b000000000000000000011111));//LunarSpringFest.DateInYear
	int CheckedDays=DoY(y,m,d);//ChekedDaysInYear
	
	//若查询日期早于当年春节，则其基准（即正月初一）应更换为上一年春节
	if(CheckedDays<LSFDays){
		LSFDays=DoY(y-1,((LunarData[y-1901-1]&0b000000000000000001100000)>>5),(LunarData[y-1901-1]&0b000000000000000000011111));
		CheckedDays+=365+isRUN(y-1)-LSFDays;
	}
	
	int diff=CheckedDays-LSFDays;
	int ml=0,dl=0;
	int sum=0;
	do{
		sum+=29+!!(LunarData[y-1901]&(0b000010000000000000000000>>(ml)));
		ml++;
	}while(sum<=diff);
	dl+=diff-sum+29+!!(LunarData[y-1901]&(0b000010000000000000000000>>(ml-1)));
	int RunYue=(LunarData[y-1901]>>20);
	int isRunYue=0;
	if(RunYue&&(ml>RunYue)){
		ml-=1;
		isRunYue=(RunYue&&ml==RunYue);
	}
	return LunarDateCode(ml,(dl+1))*(1-2*isRunYue);
}

int Func3_ArrayBased(int y,int m,int d){
	int LDate=ReadArray(y,m,d);
	if(LDate<0){
		LDate*=(-1);
		printf("农历闰");
	}
	else printf("农历");
	printf("%d月%d日 ",LDate/32,LDate%32);
	
	int IsQingming=((m==4)&&(((float)(y%100)*0.2422+(4.81+0.78*(y/100==19))-(int)((y%100)/4))==d));
	PrintFest_A(IsQingming,LDate,y,m,d);
	return 0;
}

void PrintFest_A(int IsQingming,int LDate,int y,int m,int d){
	if(IsQingming){
		printf("清明");
	}
	else if(LDate==LunarDateCode(12,29)){//考虑到春节有29或30，则对腊月29的下一天特判，若下一天是30则不是除夕，否则是除夕
		if(ReadArray(y,m,d+1)==LunarDateCode(12,30))printf("没有传统节日");
		else printf("除夕");
	}
	else{
		switch (LDate){
			case LunarDateCode(1,1):
				printf("春节");
				break;
			case LunarDateCode(1,15):
				printf("元宵");
				break;
			case LunarDateCode(3,3):
				printf("上巳");
				break;
			case LunarDateCode(5,5):
				printf("端午");
				break;
			case LunarDateCode(7,7):
				printf("七夕");
				break;
			case LunarDateCode(7,15):
				printf("中元");
				break;
			case LunarDateCode(8,15):
				printf("中秋");
				break;
			case LunarDateCode(9,9):
				printf("重阳");
				break;
			case LunarDateCode(12,8):
				printf("腊八");
				break;
			case LunarDateCode(12,30):
				printf("除夕");
				break;
			default:
				printf("没有传统节日");
		}
	}
}
