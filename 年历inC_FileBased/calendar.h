#define LunarDateCode(A,B) A*32+B

//Functions
void head(int y,int g);//overall head
void sepl(int g);//seprate line
void mohead(int m);//month head
void wkhead();//week head
int isRUN(int y);//is Run-Nian
int ds(int y,int m);//DaySum
int m1w(int y,int m);//month 1st day in week
void wkl(int y,int m, int w);//WeekLine
void mg(int y,int g,int f,int s);//MonthGroup
int DoY(int y,int m,int d);//Days in Year
int CharComp(char *val,int dat);//CharacterComparison
void ReadData(char ld[][2],int y,int m,int d);//Read Data from Text
int LunarDate(char ld[][2]);//Resolve Lunar Date
//LunarDate只能读取日或月的一个，下面的函数获取最终农历日期
int GetLunarDate(char ld[][2],int y,int m,int d);//Get Lunar Date
void PrintFest(int IsQingming,int LDate,char ld[][2],int y,int m,int d);

int Func1 (int y);
int Func2 (int y,int m);
int Func3 (int y,int m,int d);

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
int CharComp(char *val,int dat){
	return val[0]==((char)(dat>>8))&&val[1]==((char)(dat%256)) ? 1 : 0 ;
}
void ReadData(char ld[][2],int y,int m,int d){
	
	char addr[]="./data/0000.txt";
	char yc[4]={y/1000,(y%1000)/100,(y%100)/10,y%10};//各位分离
	for(int i=0;i<4;i++) addr[i+7]=yc[i]+48;//补齐字符值差值
	FILE *fp=fopen(addr,"r");
	char c[100];
	int doy=DoY(y,m,d);//Days in Year


	//文件移位到目标位置
	for(int i=0;i<3+doy-1;i++){
		fgets(c,100,fp);
//		printf("%s",c);
	}
	for(int i=0;i<22;i++) fgetc(fp);


	//逐字节读取文件内容，由于ANSI汉字占2字节，通过二维数组将读取到的数据拼合起来
	for(int i=0;i<6;i++) ld[i/2][i%2]=fgetc(fp);
	
	
	//根据文件格式再次移位18字节
	for(int i=0;i<18;i++){
		fgetc(fp);
	}
	
	
	//逐字节读取节气，同上
	for(int i=6;i<10;i++) ld[i/2][i%2]=fgetc(fp);
	
	fclose(fp);
}
int LunarDate(char ld[][2]){
	int tab[2][20]={{'一','二','三','四','五','六','七','八','九','十','正','初','廿','  ','月'},
					{1   ,2   ,3   ,4   ,5   ,6   ,7   ,8   ,9   ,10  ,1   ,0   ,2   ,'  ','月'}};
	int ml=0,dl=0;//Month in Lunar,Day in Lunar
	for(int i=0;i<5;i++){
		for(int j=0;j<13;j++){
			if(CharComp(ld[i],tab[0][j])){
				dl*=10;
				dl+=tab[1][j];
				break;
			}
		}
		if(CharComp(ld[i],'月')){
			ml=dl;
			dl=1;
			ld[0][0]=((char)('初'>>8));
			ld[0][1]=((char)('初'%256));
			ld[1][0]=((char)('一'>>8));
			ld[1][1]=((char)('一'%256));
			break;
		}
		else if((int)*ld[i]==32){
			break;
		}
	}
	if(dl==30||dl==30) dl-=10;
	else if(dl>100) dl-=90;
	if(ml>100) ml-=90;
	return ml*32+dl;
}

int GetLunarDate(char ld[][2],int y,int m,int d){
	int days[2][12]={{31,28,31,30,31,30,31,31,30,31,30,31},{31,29,31,30,31,30,31,31,30,31,30,31}};
	int LDate=LunarDate(ld);
	char ldbackup[5][2];
	for(int i=0;i<10;i++)ldbackup[i/2][i%2]=ld[i/2][i%2];
	if(!(LDate/32)){//如果读取到的不是月份而只有日期，则往前找月份
		d++;
		
		
		//借位
		if(LDate%32>=d){
			if(m==1){
				y--;
				m=12;
				d+=31;
			}
			else{
				m--;
				d+=days[isRUN(y)][m-1];
			}
		}
		
		
		d-=(LDate%32);
		ReadData(ld,y,m,d);
		LDate=(LDate%32)+32*(LunarDate(ld)/32);//改月份
	}
	for(int i=0;i<10;i++)ld[i/2][i%2]=ldbackup[i/2][i%2];
	return LDate;
}

void PrintFest(int IsQingming,int LDate,char ld[][2],int y,int m,int d){
	if(IsQingming){
		printf("清明");
	}
	else if(LDate==LunarDateCode(12,29)){//考虑到春节有29或30，则对腊月29的下一天特判，若下一天是30则不是除夕，否则是除夕
		ReadData(ld,y,m,d+1);
		int tmp=GetLunarDate(ld,y,m,d+1);
		if(tmp==LunarDateCode(12,30))printf("没有传统节日");
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
int Func3 (int y,int m,int d) {
	char ld[5][2];//LunarDay
	ReadData(ld,y,m,d);

	//检测清明
	int IsQingming = (CharComp(ld[3],'清')&&CharComp(ld[4],'明')) ? 1 : 0;

	//检测农历节日
	int LDate = GetLunarDate(ld,y,m,d);//LDate/32为月，LDate%32为日
	
	char dln[4];//LunarDayName
	for(int i=0;i<4;i++)dln[i]=ld[i/2][i%2];
	
//	int mmm=LDate/32,ddd=LDate%32;
	
	char MonthName[12][5]={"正","二","三","四","五","六","七","八","九","十","冬","腊"};
	printf("农历%2.2s月%4.4s,",MonthName[LDate/32-1],dln);
	PrintFest(IsQingming,LDate,ld,y,m,d);

	return 0;
}
