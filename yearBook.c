#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#define nl printf("\n")
struct New {
	char about [100];
	char topic [30];
	int done;
};
struct Day {
	int day;
	int num;
	struct New task[10];
	struct New event[10];
	int pt , pe;
};
struct Month{
	char name[30];
	struct Day days[31];
}months[12];
int exiter=0,leapYear=0,menu=0;
/*-------------------------------------------------------------------------------*/
void setTime(char *);
void setDate(long int date[]);
void nameMonths(struct Month *);
void mainMenu(int ,struct Month *);
int balance(int );
void numberDays(int ,int ,struct Month *);
void goToMonth(int , int , int ,struct Month *);
void goToDay(int , int , int , struct Month * ,struct Day*);
void add(int , int ,struct New *);
void goToEvents(int , int , int ,  struct Month * ,struct Day*);
void goToTasks(int ,int , int ,  struct Month * ,struct Day*);
int countDay(int , int , int *);
void search_sth(int , struct Month *);
/*-------------------------------------------------------------------------------*/
int main(int argc, char *argv[]) {
	int i,choice,year=1398,errorFlag=0,balancer;
	while(1){
		printf("<<Welcome to shamsi yearBook>>\n1. this year\n2. other years\nEnter a number: ");
		scanf("%d",&choice);
		if(choice==1){
			system("cls");
			break;
		}
		else if(choice==2){
			while(1){
				if(errorFlag==0)	
					system("cls");	
				printf("Enter the year you want to be shown\nyear ");
				scanf("%d",&year);
				if(year<=1400 && year>=1380)
					break;
				else{
					system("cls");
					errorFlag=1;
					printf("Error!!! ( you can just choose years between 1380 and 1400 )\n");
				}
			}
			break;
		}
	}
	if((year-1379)%4==0)
		leapYear=1;
	balancer=balance(year);
	numberDays(balancer,year,months);
	nameMonths(months); 
	while(1){
		char time[6];
		long int date[3];
		setTime(time);
		setDate(date);
		system("cls");
		printf("time:%s                            << year %d >>                            current date: %d/%d/%d",time,year,date[0],date[1],date[2]);
		printf("\n_______________________________________________________________________________________________________\n");
		printf("|");
		for(i=0;i<6;i++){
			if(i==date[1]-1)
				printf("*");
			printf(" %2d.%11s |",i+1,(months+i)->name);
		}
		printf("\n_______________________________________________________________________________________________________\n");
		printf("|");
		for(i=6;i<12;i++){
			if(i==date[1]-1)
				printf("*");
			printf(" %2d.%11s |",i+1,(months+i)->name);
		}
		printf("\n_______________________________________________________________________________________________________\n*this month\n\n      <<< MENU >>>\n");
		printf("\nchoose a month by number: (example: Mehr -> 7)\nSearch ->'13'\nExit ->'0'\n ->");
		while(1) {
			scanf("%d",&choice);
			if(choice==0) 
				return 0;
			else if(choice>=1 && choice<=6)
			{
				system("cls");goToMonth(1,choice,year,months+choice-1);break;
			}
			else if(choice>=7 && choice<12)
			{
				system("cls");goToMonth(2,choice,year,months+choice-1);break;
			}
			else if(choice==12){
				if(leapYear==1){
					system("cls");goToMonth(2,choice,year,months+choice-1);break;
				}
				system("cls");goToMonth(3,choice,year,months+choice-1);break;
			}
			else if(choice==13){
				system("cls");search_sth( year, months );break;
			}
			else
				printf("\nwrong path!!! retry:(example: Aban -> 8) ->");
		}
		if(exiter==1)
			return 0;
		if(menu==1)
			menu=0;
	}
}
/*-------------------------------------------------------------------------------*/
void produceDate(int dayNum , int wantedDate[]){
	int i;
	wantedDate[1]=1;
	for(i=0;i<6;i++){
	if(dayNum<=31)
		break;
	dayNum-=31;
	wantedDate[1]++;
	}
	for(i=0;i<5;i++){
		if(dayNum<=30)
			break;
		dayNum-=30;
		wantedDate[1]++;
	}
	wantedDate[0]=dayNum;
} 
/*-------------------------------------------------------------------------------*/
void printResultDays(struct Day *days , struct Month *months , int k){
	int i;
	printf("results:\n_______________________________________________________________________\n");
	for(i=0;i<k;i++){
		int result_date[2];
		produceDate((days+k)->num , result_date);
		printf("|%2d. %2d/%2d : %2d of %s\n_______________________________________________________________________\n",k+1,*(result_date+1),*result_date,*result_date,(months+k)->name);
	}
}
/*-------------------------------------------------------------------------------*/
void searchTopic(int year,struct Month * months){
	int i,j,t,choice2,k=0,type[20];
	struct Day *result_day[20];
	struct Month *result_month[20];
	char searchTitle[30];
	printf("Title (maximum 30 characters): ");
	for(i=0;i<30;i++){
		searchTitle[i]=getche();
		if(searchTitle[i]=='\r')
			break;
	}
	searchTitle[i]=0;
	system("cls");
	for(i=0;i<6;i++)
		for(j=0;j<31;j++){
			for(t=0;t<(((months+i)->days)+j)->pe;t++){
				if(strstr(((((months+i)->days)+j)->event+t)->topic,searchTitle)!=0){
					result_day[k]=((months+i)->days)+j;
					result_month[k]=months+i;
					k++;
				}
			}
			for(t=0;t<(((months+i)->days)+j)->pt;t++){
				if(strstr(((((months+i)->days)+j)->task+t)->topic,searchTitle)!=0){
					result_day[k]=((months+i)->days)+j;
					result_month[k]=months+i;
					k++;
				}
			}
		}
	for(i=6;i<11;i++)
		for(j=0;j<30;j++){
			for(t=0;t<(((months+i)->days)+j)->pe;t++){
				if(strstr(((((months+i)->days)+j)->event+t)->topic,searchTitle)!=0){
					result_day[k]=((months+i)->days)+j;
					result_month[k]=months+i;
					k++;
				}
			}
			for(t=0;t<(((months+i)->days)+j)->pt;t++){
				if(strstr(((((months+i)->days)+j)->task+t)->topic,searchTitle)!=0){
					result_day[k]=((months+i)->days)+j;
					result_month[k]=months+i;
					k++;
				}
			}
		}
	if(leapYear==1){
		for(j=0;j<30;j++){
			for(t=0;t<(((months+11)->days)+j)->pe;t++){
				if(strstr(((((months+11)->days)+j)->event+t)->topic,searchTitle)!=0){
					result_day[k]=((months+11)->days)+j;
					result_month[k]=months+11;
					k++;
				}
			}
			for(t=0;t<(((months+11)->days)+j)->pt;t++){
				if(strstr(((((months+11)->days)+j)->task+t)->topic,searchTitle)!=0){
					result_day[k]=((months+11)->days)+j;
					result_month[k]=months+11;
					k++;
				}
			}
		}
	}
	else{
		for(j=0;j<29;j++){
			for(t=0;t<(((months+11)->days)+j)->pe;t++){
				if(strstr(((((months+11)->days)+j)->event+t)->topic,searchTitle)!=0){
					result_day[k]=((months+11)->days)+j;
					result_month[k]=months+11;
					k++;
				}
			}
			for(t=0;t<(((months+11)->days)+j)->pt;t++){
				if(strstr(((((months+11)->days)+j)->task+t)->topic,searchTitle)!=0){
					result_day[k]=((months+11)->days)+j;
					result_month[k]=months+11;
					k++;
				}
			}
		}
	}
	printf("results:(%d titles found)\n_______________________________________________________________________\n",k);
	for(i=0;i<k;i++){
		int result_date[2];
		produceDate(result_day[i]->num , result_date);
		countDay(result_date[1],result_date[0],type+i);
		printf("|%2d. %2d/%2d : %2d %s\n_______________________________________________________________________\n",i+1,result_date[1],result_date[0],result_date[0],result_month[i]->name);
	}
	printf("\nchoose a day \nMenu ->'21'\nExit ->'0'\n-> ");
	while(1){
		scanf("%d",&choice2);
		if(choice2==0){
			exiter=1;
			break;
		}
		else if(choice2<=k){
			int result_date[2];
			produceDate(result_day[choice2-1]->num , result_date);
			goToDay(year,*(type+choice2-1) ,result_date[0], result_month[choice2-1] , result_day[choice2-1]  );
			break;
		}
		else if(choice2==21)
			break;
	}
}
/*-------------------------------------------------------------------------------*/
void searchDate(int year,struct Month * months){
	int searchDay,searchMonth,i,j,d=0,type;
	struct Day *resultDay;
	struct Month *resultMonth;
	first:
	system("cls");
	printf("\nday : ");
	scanf("%d",&searchDay);
	printf("\nmonth : ");
	scanf("%d",&searchMonth);
	if((searchDay>30 && searchMonth>6 && searchMonth<12) || (searchDay>31) || (searchMonth>12) || (searchDay>29 && searchMonth==12 && leapYear==0) || (searchDay>30 && searchMonth==12 && leapYear==1))
		goto first;
	searchMonth++;
	d=countDay(searchMonth,searchDay,&type);
	for(i=0;i<6;i++)
		for(j=0;j<31;j++){
			if(((((months+i)->days)+j)->num)==d)
			{
				resultDay=(((months+i)->days)+j);
				resultMonth=(months+i);
				break;
			}
		}
	for(i=6;i<11;i++)
		for(j=0;j<30;j++){
			if(((((months+i)->days)+j)->num)==d)
			{
				resultDay=(((months+i)->days)+j);
				resultMonth=(months+i);
				break;
			}
		}
	if(leapYear==1){
		for(j=0;j<30;j++){
			if(((((months+11)->days)+j)->num)==d)
			{
				resultDay=(((months+11)->days)+j);
				resultMonth=(months+11);
				break;
			}
		}
	}
	else{
		for(j=0;j<29;j++){
			if(((((months+11)->days)+j)->num)==d)
			{
				resultDay=(((months+11)->days)+j);
				resultMonth=(months+11);
				break;
			}
		}
	}
	resultMonth-=1;resultDay=(resultMonth->days)+searchDay-1;
	goToDay(year , type , searchDay , resultMonth ,resultDay);
}
/*-------------------------------------------------------------------------------*/
void searchOutOfDate(int year,struct Month * months){
	struct Day *result_day[20];
	struct Month *result_month[20];
	long int date[3];
	int t,i,j,k=0,d,type1,choice2,type[20];
	char time[6];
	setTime(time);
	setDate(date);
	system("cls");
	printf("\n_______________________________________________________________________\n");
	printf("|time:%s                                   current date: %d/%d/%d|",time,date[0],date[1],date[2]);
	printf("\n_______________________________________________________________________\n");
	d=countDay(date[1],date[2],&type1);
	for(i=0;i<6;i++)
		for(j=0;j<31;j++){
			if(((((months+i)->days)+j)->num)<d)
			{t=0;
				//for(t=0;t<(((months+i)->days)+j)->pt;t++){
					if(((((months+i)->days)+j)->task+t)->topic[0]!=0){
						result_day[k]=(((months+i)->days)+j);
						result_month[k]=(months+i);
						k++;
					}	
				//}
			}
		}
	for(i=6;i<11;i++)
		for(j=0;j<30;j++){
			if(((((months+i)->days)+j)->num)<d)
			{t=0;
				//for(t=0;t<(((months+i)->days)+j)->pt;t++){
					if(((((months+i)->days)+j)->task+t)->topic[0]!=0){
						result_day[k]=(((months+i)->days)+j);
						result_month[k]=(months+i);
						k++;
					}	
				//}
			}
		}
	if(leapYear==1){
		for(j=0;j<30;j++){
			if(((((months+11)->days)+j)->num)<d)
			{t=0;
			//	for(t=0;t<(((months+11)->days)+j)->pt;t++){
					if(((((months+11)->days)+j)->task+t)->topic[0]!=0){
						result_day[k]=(((months+11)->days)+j);
						result_month[k]=(months+11);
						k++;
					}	
			//	}
			}
		}
	}
	else{
		for(j=0;j<29;j++){
			if(((((months+11)->days)+j)->num)<d)
			{
				t=0;
				//for(t=0;t<(((months+i)->days)+j)->pt;t++){
					if(((((months+i)->days)+j)->task+t)->topic[0]!=0){
						result_day[k]=(((months+i)->days)+j);
						result_month[k]=(months+i);
						k++;
					}	
				//}
			}
		}
	}
	for(i=0;i<k;i++){
		int result_date[2];
		produceDate(result_day[i]->num , result_date);
		countDay(result_date[1],result_date[0],type+i);
		printf("|%2d. %2d/%2d : %2d %s -> %d task(s) not done! \n_______________________________________________________________________\n",i+1,result_date[1],result_date[0],result_date[0],result_month[i]->name,result_day[i]->pt);
	}
	printf("\nchoose a day \nMenu ->'21'\nExit ->'0'\n-> ");
	while(1){
		scanf("%d",&choice2);
		if(choice2==0){
			exiter=1;
			break;
		}
		else if(choice2<=k){
			int result_date[2];
			produceDate(result_day[choice2-1]->num , result_date);
			goToDay(year,*(type+choice2-1) ,result_date[0], result_month[choice2-1] , result_day[choice2-1]  );
			break;
		}
		else if(choice2==21)
			break;
	}
}
/*-------------------------------------------------------------------------------*/
void search_sth(int year,struct Month * months){
	int choice;
	char time[6];
	long int date[3];
	setTime(time);
	setDate(date);
	system("cls");
	printf("\n_______________________________________________________________________\n");
	printf("|time:%s                                   current date: %d/%d/%d|",time,date[0],date[1],date[2]);
	printf("\n_______________________________________________________________________\n");
	printf("Search Options:\n1.date\n2.Title\n3.Out of date Tasks\n4.Menu ->");
	while(1){
		scanf("%d",&choice);
		if(choice==1){
			searchDate(year, months);
			break;
		}
		else if(choice==2){
			searchTopic(year,months);
			break;
		}
		else if(choice==3){
			searchOutOfDate(year,months);
			break;
		}
		else if(choice==4)
			break;
	}
	
}
/*-------------------------------------------------------------------------------*/
int countDay(int month , int day , int *type){
	int i,d=0;
	d=day;
	for(i=0;i<6;i++){
		if(month==1)
			break;
		d+=31;
		*type=1;
		month--;
	}
	for(i=0;i<5;i++){
		if(month==1)
			break;
		d+=30;
		*type=2;
		month--;
	}
	if(leapYear==0 && month!=1){
		d+=30;
		*type=2;
	}
	else if(month!=1){
		d+29;
		*type=3;
	}
	return d;
}
/*-------------------------------------------------------------------------------*/
int balance(int year){
	if(year==1380 ||year==1386 ||year==1397){
		return 4;
	}
	else if(year==1381 ||year==1387 ||year==1392||year==1398){
		return 5;
	}
	else if(year==1382 ||year==1393 ||year==1399){
		return 6;
	}
	else if(year==1383 ||year==1388 ||year==1394){
		return 0;
	}
	else if(year==1384 ||year==1390 ){
		return 2;
	}
	else if(year==1385 ||year==1391 ||year==1396){
		return 3;
	}
	else if(year==1389 ||year==1395 ||year==1400){
		return 1;
	}
}
/*-------------------------------------------------------------------------------*/
void nameMonths(struct Month *months){
	(months+0)->name[0]='F';(months+0)->name[1]='a';(months+0)->name[2]='r';(months+0)->name[3]='v';(months+0)->name[4]='a';(months+0)->name[5]='r';(months+0)->name[6]='d';(months+0)->name[7]='i';(months+0)->name[8]='n';(months+0)->name[9]=0;
	(months+1)->name[0]='O';(months+1)->name[1]='r';(months+1)->name[2]='d';(months+1)->name[3]='i';(months+1)->name[4]='b';(months+1)->name[5]='e';(months+1)->name[6]='h';(months+1)->name[7]='e';(months+1)->name[8]='s';(months+1)->name[9]='h';(months+1)->name[10]='t';(months+1)->name[11]=0;
	(months+2)->name[0]='K';(months+2)->name[1]='h';(months+2)->name[2]='o';(months+2)->name[3]='r';(months+2)->name[4]='d';(months+2)->name[5]='a';(months+2)->name[6]='d';(months+2)->name[7]=0;
	(months+3)->name[0]='T';(months+3)->name[1]='i';(months+3)->name[2]='r';(months+3)->name[3]=0;
	(months+4)->name[0]='M';(months+4)->name[1]='o';(months+4)->name[2]='r';(months+4)->name[3]='d';(months+4)->name[4]='a';(months+4)->name[5]='d';(months+4)->name[6]=0;
	(months+5)->name[0]='S';(months+5)->name[1]='h';(months+5)->name[2]='a';(months+5)->name[3]='h';(months+5)->name[4]='r';(months+5)->name[5]='i';(months+5)->name[6]='v';(months+5)->name[7]='a';(months+5)->name[8]='r';(months+5)->name[9]=0;

	(months+6)->name[0]='M';(months+6)->name[1]='e';(months+6)->name[2]='h';(months+6)->name[3]='r';(months+6)->name[4]=0;
	(months+7)->name[0]='A';(months+7)->name[1]='b';(months+7)->name[2]='a';(months+7)->name[3]='n';(months+7)->name[4]=0;
	(months+8)->name[0]='A';(months+8)->name[1]='z';(months+8)->name[2]='a';(months+8)->name[3]='r';(months+8)->name[4]=0;
	(months+9)->name[0]='D';(months+9)->name[1]='e';(months+9)->name[2]='y';(months+9)->name[3]=0;
	(months+10)->name[0]='B';(months+10)->name[1]='a';(months+10)->name[2]='h';(months+10)->name[3]='m';(months+10)->name[4]='a';(months+10)->name[5]='n';(months+10)->name[6]=0;
	(months+11)->name[0]='E';(months+11)->name[1]='s';(months+11)->name[2]='f';(months+11)->name[3]='a';(months+11)->name[4]='n';(months+11)->name[5]='d';(months+11)->name[6]=0;
}
/*---------------------------------------------------------------------------------------------------*/
void goToMonth(int type ,int num , int year ,struct Month *month){
	int i,k=0,choice,m=0;
	long int date[3];
	char time[6];
	setTime(time);
	setDate(date);
	while(1){
		system("cls");
		printf("time:%s            << year %d >>          current date: %d/%d/%d",time,year,date[0],date[1],date[2]);
		printf("\n\n                        %s",month->name);
		printf("\n______________________________________________________________________|");
		printf("\n|    Sh   |   1Sh   |   2Sh   |   3Sh   |   4Sh   |   5Sh   |   Jom   |");
		printf("\n_______________________________________________________________________\n|");
		for(i=0;i<(month->days[0]).day;i++)
			printf("         |");
		k+=(month->days[0]).day;
		if(type==1){
			m=31;
			for(i=0;i<31;i++){
				if(i+1==date[2] && num==date[1])
					printf("*");
				printf("   %2d    |",i+1);
				if(k==6 || k==13 || k==20 || k==27 || k==34)
					printf("\n_______________________________________________________________________\n|");		
				k++;
			}
		}
		else if(type==3 && leapYear==0){
			m=29;
			for(i=0;i<29;i++){
				if(i+1==date[2] && num==date[1])
					printf("*");
				printf("   %2d    |",i+1);
				if(k==6 || k==13 || k==20 || k==27 || k==34)
					printf("\n_______________________________________________________________________\n|");		
				k++;
			}
		}
		else{
			m=30;
			for(i=0;i<30;i++){
				if(i+1==date[2] && num==date[1])
					printf("*");
				printf("   %2d    |",i+1);
				if(k==6 || k==13 || k==20 || k==27 || k==34)
					printf("\n_______________________________________________________________________\n|");		
				k++;
			}
		}
		k=0;
		printf("\n_______________________________________________________________________\n");
		printf("Choose a Day by number-> \nMenu ->'%d'\nExit ->'0'\n-> ",m+1);	
		while(1){
			scanf("%d",&choice);
			if(choice==0){
				exiter= 1;
				break;
			}
			else if(choice<=m && choice>0){
				system("cls");
				goToDay(year , 1 , choice , month , (month->days)+choice-1 );
				break;
			}
			else if(choice==m+1)
				break;
			
		}
		if(exiter==1 || choice==m+1 || menu==1)
			break;
	}
}
/*---------------------------------------------------------------------------------------------------*/
void goToDay(int year , int type , int num , struct Month *month , struct Day *day1){
	char time[6];
	long int date[3];
	int i,choice;
	char dd[7][4]={"Sh","1Sh","2Sh","3Sh","4Sh","5Sh","Jom"};
	while(1){
		system("cls");
		setTime(time);
		setDate(date);
		printf("\n_______________________________________________________________________\n");
		printf("|time:%s                                   current date: %d/%d/%d|",time,date[0],date[1],date[2]);
		printf("\n_______________________________________________________________________\n");
		printf("                          %s: %d %s %d         ",dd[day1->day],num,month->name,year);
		printf("\n_______________________________________________________________________\n");
		printf("|                            Events                                   |");
		printf("\n.......................................................................");		
		for(i=0;i<10;i++){
			if((day1->event[i]).topic[0]!=0){
				printf("\n| %2d. %62s  |",i+1,(day1->event[i]).topic);
				printf("\n_______________________________________________________________________");
			}
			else{
				printf("\n|                          ----------                                 |");
				break;
			}
		}
		printf("\n_______________________________________________________________________\n");
		printf("|                            Tasks                                    |");
		printf("\n.......................................................................");

		for(i=0;i<10;i++){
			if((day1->task[i]).topic[0]!=0){
				printf("\n| %2d. %62s  |",i+1,(day1->task[i]).topic);
				printf("\n_______________________________________________________________________");
			}
			else{
				printf("\n|                          ----------                                 |");
				break;
			}
		}
		printf("\n_______________________________________________________________________\n");
		printf("New Event ->'1'\nNew Task ->'2'\nEvents ->'3'\nTasks ->'4'\nNext day ->'5'\nPrevious day ->'6'\nBack ->'7'\nMenu ->'8'\nExit ->'0'\n-> ");
		while(1){
			scanf("%d",&choice);
			if(choice==0){
				exiter= 1;
				break;
			}
			else if(choice==1){
				system("cls");
				add(3,1,(day1->event)+(day1->pe));
				(day1->pe)++;
				break;
			}
			else if(choice==2){
				system("cls");
				add(3,2,(day1->task)+(day1->pt));
				(day1->pt)++;
				break;
			}
			else if(choice==3){
				system("cls");
				goToEvents(year,type , num , month , day1);
				break;
			}
			else if(choice==4){
				system("cls");
				goToTasks(year,type , num , month , day1);
				break;
			}
			else if(choice==5){
				if(type==1){
					if(num!=31){
						goToDay(year , type , num+1 , month ,day1+1);
						choice=7;
					}
					else{
						printf("\nUnavailable");
						sleep(1);
					}
				}
				else if(type==3 && leapYear==0){
					if(num!=29){
						goToDay(year , type , num+1 , month ,day1+1);
						choice=7;
					}
					else{
						printf("\nUnavailable");
						sleep(1);
					}
				}
				else{
					if(num!=30){
						goToDay(year , type , num+1 , month ,day1+1);
						choice=7;
					}
					else{
						printf("\nUnavailable");
						sleep(1);
					}
				}
				break;
			}
			else if(choice==6){
				if(num!=1){
					goToDay(year , type , num-1 , month ,day1-1);
					choice=7;
				}
				else{
					printf("\nUnavailable");
					sleep(1);
				}
				break;
			}
			else if(choice==7)
				break;
			else if(choice==8){
				menu=1;
				break;
			}
		}
		if(exiter==1 ||choice==7 ||menu==1)
			break;
	}
}
/*---------------------------------------------------------------------------------------------------*/
void newcpy(struct New *n1 , struct New *n2){
	int i;
	for(i=0;i<30;i++)
		n1->topic[i]=n2->topic[i];
	for(i=0;i<100;i++)
		n1->about[i]=n2->about[i];
	n1->done=n2->done;
}
/*---------------------------------------------------------------------------------------------------*/
void arrangeNews(int code , struct Day *day1){
	int i;
	struct New n;
	for(i=9;i>0;i--){
		if(code==2)
			if((day1->task+i)->topic[1]!=0 && (day1->task+i-1)->topic[1]==0){
				newcpy((day1->task+i-1),(day1->task+i));
				newcpy((day1->task+i),&n);
			}
		else if(code==1)
			if((day1->event+i)->topic[1]!=0 && (day1->event+i-1)->topic[1]==0){
				newcpy((day1->event+i-1),(day1->event+i));
				newcpy((day1->event+i),&n);
			}
	}
}
/*---------------------------------------------------------------------------------------------------*/
void newMove(int code , struct Day *day1 ,struct New *new ){
	int i,j;
	struct New n;
	int move_day,move_month,type,d,answer_flag=0;
	first1:
		if(code!=3){
			system("cls");
			printf("move to:\nday: ");
			scanf("%d",&move_day);
			printf("\nmonth: ");
			scanf("%d",&move_month);
			if((move_day>30 && move_month>6 && move_month<12) || (move_day>31) || (move_month>12) || (move_day>29 && move_month==12 && leapYear==0) || (move_day>30 && move_month==12 && leapYear==1))
				goto first1;
			d=countDay(move_month,move_day,&type);
			
			if(answer_flag==0)
				for(i=0;i<6;i++){
					for(j=0;j<31;j++){
						if(((((months+i)->days)+j)->num)==d)
						{
							answer_flag=1;
							if(code==1){
								newcpy(((((months+i)->days)+j)->event)+(((months+i)->days)+j)->pe,new);
								(((months+i)->days)+j)->pe++;
								newcpy(new,&n);
								day1->pe--;
								arrangeNews(1,day1);
								arrangeNews(1,(((months+i)->days)+j));
							}
							else {
								newcpy(((((months+i)->days)+j)->task)+(((months+i)->days)+j)->pt,new);
								(((months+i)->days)+j)->pt++;
								newcpy(new,&n);
								day1->pt--;
								arrangeNews(2,day1);
								arrangeNews(2,(((months+i)->days)+j));
							}
							break;
						}
					}
					if(answer_flag==1)
						break;
				}
			if(answer_flag==0)
				for(i=6;i<11;i++){
					for(j=0;j<30;j++){
						if(((((months+i)->days)+j)->num)==d)
						{
							answer_flag=1;
							if(code==1){
								newcpy(((((months+i)->days)+j)->event)+(((months+i)->days)+j)->pe,new);
								(((months+i)->days)+j)->pe++;
								newcpy(new,&n);
								day1->pe--;
								arrangeNews(1,day1);
								arrangeNews(1,(((months+i)->days)+j));
							}
							else {
								newcpy(((((months+i)->days)+j)->task)+(((months+i)->days)+j)->pt,new);
								(((months+i)->days)+j)->pt++;
								newcpy(new,&n);
								day1->pt--;
								arrangeNews(2,day1);
								arrangeNews(2,(((months+i)->days)+j));
							}
							break;
						}
					}
					if(answer_flag==1)
						break;
				}
			if(leapYear==1 && answer_flag==0){
				for(j=0;j<30;j++){
					if(((((months+11)->days)+j)->num)==d)
					{
						answer_flag=1;
						if(code==1){
							newcpy(((((months+11)->days)+j)->event)+(((months+11)->days)+j)->pe,new);
							(((months+11)->days)+j)->pe++;
							newcpy(new,&n);
							day1->pe--;
							arrangeNews(1,day1);
							arrangeNews(1,(((months+11)->days)+j));
						}
						else {
							newcpy(((((months+11)->days)+j)->task)+(((months+11)->days)+j)->pt,new);
							(((months+11)->days)+j)->pt++;
							newcpy(new,&n);
							day1->pt--;
							arrangeNews(2,day1);
							arrangeNews(2,(((months+i)->days)+j));
						}
						break;
					}
				}
			}
			else if(leapYear==0 && answer_flag==0){
				for(j=0;j<29;j++){
					if(((((months+11)->days)+j)->num)==d)
					{
						answer_flag=1;
						if(code==1){
							newcpy(((((months+11)->days)+j)->event)+(((months+11)->days)+j)->pe,new);
							(((months+11)->days)+j)->pe++;
							newcpy(new,&n);
							day1->pe--;
							arrangeNews(1,day1);
							arrangeNews(1,(((months+i)->days)+j));
						}
						else {
							newcpy(((((months+11)->days)+j)->task)+(((months+11)->days)+j)->pt,new);
							(((months+11)->days)+j)->pt++;
							newcpy(new,&n);
							day1->pt--;
							arrangeNews(2,day1);
							arrangeNews(2,(((months+i)->days)+j));
						}
						break;
					}
				}
			}
		}
		else if(code==3){
			newcpy(new,&n);
			day1->pt--;
			arrangeNews(1,day1);
			arrangeNews(2,day1);
		}
}
/*---------------------------------------------------------------------------------------------------*/
void printGoToEvents(int year ,int type, int num , struct Month *month , struct Day *day1 ){
	char time[6];
	long int date[3];
	int i;
	system("cls");
	setTime(time);
	setDate(date);
	printf("\n_______________________________________________________________________\n");
	printf("|time:%s                                   current date: %d/%d/%d|",time,date[0],date[1],date[2]);
	printf("\n_______________________________________________________________________\n");
	printf("                           %d %s %d          ",num,month->name,year);
	printf("\n_______________________________________________________________________\n");
	printf("|                            Events                                   |");
	printf("\n.......................................................................");		
	for(i=0;i<10;i++){
		if((day1->event[i]).topic[0]!=0){
			printf("\n| %2d. %62s  |",i+1,(day1->event[i]).topic);
			printf("\n_______________________________________________________________________");
		}
		else{
			printf("\n|                          ----------                                 |");
			break;
		}
	}
	printf("\nchoose a Event by number \nBack '11'\nMenu ->'12'\nExit '0'\n-> ");
}
/*---------------------------------------------------------------------------------------------------*/
void goToEvents(int year ,int type, int num , struct Month *month , struct Day *day1 ){
	char time[6];
	long int date[3];
	int i,choice,choice2,choice3;
	while(1){
		printGoToEvents(year,type,num,month,day1);
		while(1){
			scanf("%d",&choice);
			if(choice==11)
				break;
			else if(choice==12){
				menu=1;
				break;
			}
			else if(choice==0){
				exiter=1;
				break;
			}
			else if(choice<=day1->pe){
				while(1){
					system("cls");
					setTime(time);
					setDate(date);
					printf("\n_______________________________________________________________________\n");
					printf("|time:%s                                   current date: %d/%d/%d|",time,date[0],date[1],date[2]);
					printf("\n_______________________________________________________________________\n");
					printf("                           %d %s %d          ",num,month->name,year);
					printf("\n_______________________________________________________________________\n");	
				
					printf("\n| title: %59s  |",(day1->event[choice-1]).topic);
					printf("\n\n|    Description: \n      ");
					for(i=0;i<100 && (day1->event[choice-1]).about[i]!=0 ;i++){
						printf("%c",(day1->event[choice-1]).about[i]);
						if(i==62){
							printf("\n     ");
						}
					}
					printf("\n_______________________________________________________________________\n");
					printf("Edit ->'1'\nmove to tomorrow ->'2'\nmove to yesterday ->'3'\nBack ->'4'\nmove to another day ->'5'\nDelete ->'6'\nMenu ->'7'\nExit ->'0'\n-> ");						
					while(1){
						scanf("%d",&choice2);
						if(choice2==0){
							exiter=1;
							break;
						}
						if(choice2==7){
							menu=1;
							break;
						}
						else if(choice2==1){
							printf("\nwhich part do you want to be Edited?\ntitle ->'1'\nDescription ->'2'\nBoth ->'3'\nBack ->'4'\nMenu ->'5'\nExit ->'0'\n-> ");
							scanf("%d",&choice3);
							if(choice3<=3 && choice3>=1){
								add(choice3,1,(day1->event)+choice-1);
								break;
							}
							else if(choice3==4)
								break;
							else if(choice3==0){
								exiter==1;
								break;
							}
							else if(choice3==5){
								menu=1;
								break;
							}
						}
						else if(choice2==2){
							struct New n;
							if(type==1){
								if(num!=31){
									newcpy(((day1+1)->event)+(day1+1)->pe,(day1->event)+choice-1);
									(day1+1)->pe++;
									newcpy((day1->event)+choice-1,&n);
									day1->pe--;
									choice2=4;
								}
								else{
									printf("\nUnavailable");
									sleep(1);
								}
							}
							else if(type==3 && leapYear==0){
								if(num!=29){
									newcpy(((day1+1)->event)+(day1+1)->pe,(day1->event)+choice-1);
									(day1+1)->pe++;
									newcpy((day1->event)+choice-1,&n);
									day1->pe--;
									choice2=4;
								}
								else{
									printf("\nUnavailable");
									sleep(1);
								}
							}
							else{
								if(num!=30){
									newcpy(((day1+1)->event)+(day1+1)->pe,(day1->event)+choice-1);
									(day1+1)->pe++;
									newcpy((day1->event)+choice-1,&n);
									day1->pe--;
									choice2=4;
								}
								else{
									printf("\nUnavailable");
									sleep(1);
								}
							}
							break;
						}
						else if(choice2==3){
							if(num!=1){
								struct New n;
								newcpy(((day1-1)->event)+(day1-1)->pe,(day1->event)+choice-1);
								(day1-1)->pe++;
								newcpy((day1->event)+choice-1,&n);
								day1->pe--;
								choice2=4;
							}
							else{
								printf("\nUnavailable");
								sleep(1);
							}
							break;
						}
						else if(choice2==4)
							break;
						else if(choice2==5){
							newMove(1,day1,(day1->event)+choice-1);
							choice2=4;
							break;
						}
						else if(choice2==6){
							newMove(3,day1,(day1->event)+choice-1);
							choice2=4;
							break;
						}
						if(exiter==1 || choice3==4 || menu==1)
							break;
					}
					if(exiter==1 ||choice2==4 || choice3==4 || menu==1)
						break;
				}
			}
			if(exiter==1 || choice==11|| choice2==4 || choice3==4 || menu==1)
				break;
		}
		if(exiter==1 || choice==11|| choice2==4 || menu==1)
			break;
	}
	
}
/*---------------------------------------------------------------------------------------------------*/
void printGoToTasks(int year ,int type , int num , struct Month *month , struct Day *day1){
	int i;
	char time[6];
	long int date[3];
	system("cls");
	setTime(time);
	setDate(date);
	printf("\n_______________________________________________________________________\n");
	printf("|time:%s                                   current date: %d/%d/%d|",time,date[0],date[1],date[2]);
	printf("\n_______________________________________________________________________\n");
	printf("                           %d %s %d          ",num,month->name,year);
	printf("\n_______________________________________________________________________\n");
	printf("|                            Tasks                                   |");
	printf("\n.......................................................................");		
	for(i=0;i<10;i++){
		if((day1->task[i]).topic[0]!=0){
			printf("\n| %2d. %62s  |",i+1,(day1->task[i]).topic);
			printf("\n_______________________________________________________________________");
		}
		else{
			printf("\n|                          ----------                                 |");
			break;
		}
	}
}
/*---------------------------------------------------------------------------------------------------*/
void goToTasks(int year ,int type , int num , struct Month *month , struct Day *day1 ){
	int i,choice,choice2,choice3;
	char time[6];
	long int date[3];
	char answer[2][4]={"NO","Yes"};
	while(1){
		printGoToTasks(year,type,num,month,day1);
		printf("\nchoose a task by number \nBack '11'\nMenu ->'12'\nExit '0'\n-> ");
		while(1){
			scanf("%d",&choice);
			if(choice==11)
				break;
			else if(choice==12){
				menu==1;
				break;
			}
			else if(choice==0){
				exiter=1;
				break;
			}
			else if(choice<=day1->pt){
				while(1){
					system("cls");
					setTime(time);
					setDate(date);
					printf("\n_______________________________________________________________________\n");
					printf("|time:%s                                   current date: %d/%d/%d|",time,date[0],date[1],date[2]);
					printf("\n_______________________________________________________________________\n");
					printf("                           %d %s %d          ",num,month->name,year);
					printf("\n_______________________________________________________________________\n");	
				
					printf("\n| title: %59s  |",(day1->task[choice-1]).topic);
					printf("\n\n|    Description: \n      ");
					for(i=0;i<100 && (day1->task[choice-1]).about[i]!=0 ;i++){
						printf("%c",(day1->task[choice-1]).about[i]);
						if(i==62){
							printf("\n     ");
						}
					}
					printf("\n\n|    Done? %s",answer[(day1->task[choice-1]).done]);
					printf("\n_______________________________________________________________________\n");
					printf("Edit ->'1'\nmove to tomorrow ->'2'\nmove to yesterday ->'3'\nBack ->'4'\nmove to another day ->'5'\nDelete ->'6'\nMenu ->'7'\nExit ->'0'\n-> ");						
					while(1){
						scanf("%d",&choice2);
						if(choice2==0){
							exiter=1;
							break;
						}
						else if(choice2==7){
							menu=1;
							break;
						}
						else if(choice2==1){
							printf("\nwhich part do you want to be Edited?\ntitle ->'1'\nDescription ->'2'\nBoth ->'3'\nDone? ->'4'\nBack ->'5'\nMenu ->'6'\n-> ");
							scanf("%d",&choice3);
							if(choice3<=4 && choice3>=1){
								add(choice3,2,(day1->task)+choice-1);
								break;
							}
							else if(choice3==5)
								break;
							else if(choice3==0){
								exiter==1;
								break;
							}
							else if(choice==6){
								menu=1;
								break;
							}
						}
						else if(choice2==2){
							struct New n;
							if(type==1){
								if(num!=31){
									newcpy(((day1+1)->task)+(day1+1)->pt,(day1->task)+choice-1);
									(day1+1)->pt++;
									newcpy((day1->task)+choice-1,&n);
									day1->pt--;
									choice2=4;
								}
								else{
									printf("\nUnavailable");
									sleep(1);
								}
							}
							else if(type==3 && leapYear==0){
								if(num!=29){
									newcpy(((day1+1)->task)+(day1+1)->pt,(day1->task)+choice-1);
									(day1+1)->pt++;
									newcpy((day1->task)+choice-1,&n);
									day1->pt--;
									choice2=4;
								}
								else{
									printf("\nUnavailable");
									sleep(1);
								}
							}
							else{
								if(num!=30){
									newcpy(((day1+1)->task)+(day1+1)->pt,(day1->task)+choice-1);
									(day1+1)->pt++;
									newcpy((day1->task)+choice-1,&n);
									day1->pt--;
									choice2=4;
								}
								else{
									printf("\nUnavailable");
									sleep(1);
								}
							}
							break;
						}
						else if(choice2==3){
							if(num!=1){
								struct New n;
								newcpy(((day1-1)->task)+(day1-1)->pt,(day1->task)+choice-1);
								(day1-1)->pt++;
								newcpy((day1->task)+choice-1,&n);
								day1->pt--;
								choice2=4;
							}
							else{
								printf("\nUnavailable");
								sleep(1);
							}
							break;
						}
						else if(choice2==4)
							break;
						else if(choice2==5){
							newMove(2,day1,(day1->task)+choice-1);
							choice2=4;
							break;
						}
						else if(choice2==6){
							newMove(3,day1,(day1->task)+choice-1);
							choice2=4;
							break;
						}
						if(exiter==1 || choice3==5 || menu==1)
							break;
					}
					if(exiter==1 ||choice2==4 || choice3==5 || menu==1)
						break;
				
				}
			}
			if(exiter==1 || choice==11|| choice2==4 || choice3==5 || menu==1)
				break;
		}
		if(exiter==1 || choice==11|| choice2==4 || menu==1 )
			break;
	}
	
}
/*---------------------------------------------------------------------------------------------------*/
void add(int code,int type,struct New * new){
	system("cls");
	int i;
	if(code==3){
		printf("\nTitle (maximum 30 characters):");
		for(i=0;i<29;i++){
			new->topic[i]=getche();
			if(new->topic[i]=='\r')
				break;
		}
		new->topic[i]=0;
		printf("\nDescription (maximum 100 characters):");
		for(i=0;i<99;i++){
			new->about[i]=getche();
			if(new->about[i]=='\r')
				break;
		}
		new->about[i]=0;
		if(type==2)
			new->done=0;
	}
	else if(code==1){
		printf("\nTitle (maximum 30 characters):");
		for(i=0;i<29;i++){
			new->topic[i]=getche();
			if(new->topic[i]=='\r')
				break;
		}
		new->topic[i]=0;
	}
	else if(code==2){
		printf("\nDescription (maximum 100 characters):");
		for(i=0;i<99;i++){
			new->about[i]=getche();
			if(new->about[i]=='\r')
				break;
		}
		new->about[i]=0;
	}
	else if(code==4){
		printf("\nDone ?( yes ->'1' , no ->'0'):-> ");
		while(1){
		scanf("%d",&new->done);
		if(new->done==1 || new->done==0)
			break;
		}
	}
	printf("\nsaved successfuly.");
	sleep(1);
}
/*---------------------------------------------------------------------------------------------------*/
void setTime(char *time1){
	int i;
	char *t1;
	time_t current_time=time(NULL);
	t1=ctime(&current_time);
	for(i=0;i<5;i++){
		*(time1+i)=*(t1+11+i);
	}
	time1[5]=0;
}
/*---------------------------------------------------------------------------------------------------*/
void setDate(long int date[]){	
	FILE *fp;
	fp=fopen("index_year_book.txt","r");
	fscanf(fp,"%d",&date[0]);
	fscanf(fp,"%d",&date[1]);
	fscanf(fp,"%d",&date[2]);
	fclose(fp);
}
/*---------------------------------------------------------------------------------------------------*/
void numberDays(int balancer,int leapYear,struct Month *months){
	int i,j;
	for(i=0;i<31;i++){
		(months+0)->days[i].day=(i+balancer)%7;
		(months+0)->days[i].num=i+1;
		(months+0)->days[i].pt=0;(months+0)->days[i].pt=0;
	}
	(months+0)->days[30].day=100;
	for(i=0;i<31;i++){
		(months+1)->days[i].day=(i+31+balancer)%7;
		(months+1)->days[i].num=i+32;
		(months+1)->days[i].pt=0;(months+1)->days[i].pt=0;
	}
	(months+1)->days[30].day=100;
	for(i=0;i<31;i++){
		(months+2)->days[i].day=(i+62+balancer)%7;
		(months+2)->days[i].num=i+63;
		(months+2)->days[i].pt=0;(months+2)->days[i].pt=0;
	}
	(months+2)->days[30].day=100;
	for(i=0;i<31;i++){
		(months+3)->days[i].day=(i+93+balancer)%7;
		(months+3)->days[i].num=i+94;
		(months+3)->days[i].pt=0;(months+3)->days[i].pt=0;
	}
	(months+3)->days[30].day=100;
	for(i=0;i<31;i++){
		(months+4)->days[i].day=(i+124+balancer)%7;
		(months+4)->days[i].num=i+125;
		(months+4)->days[i].pt=0;(months+4)->days[i].pt=0;
	}
	(months+4)->days[30].day=100;
	for(i=0;i<31;i++){
		(months+5)->days[i].day=(i+155+balancer)%7;
		(months+5)->days[i].num=i+156;
		(months+5)->days[i].pt=0;(months+5)->days[i].pt=0;
	}
	(months+5)->days[30].day=100;
	for(i=0;i<30;i++){
		(months+6)->days[i].day=(i+186+balancer)%7;
		(months+6)->days[i].num=i+187;
		(months+6)->days[i].pt=0;(months+6)->days[i].pt=0;
	}
	(months+6)->days[30].day=100;
	for(i=0;i<30;i++){
		(months+7)->days[i].day=(i+216+balancer)%7;
		(months+7)->days[i].num=i+217;
		(months+7)->days[i].pt=0;(months+7)->days[i].pt=0;
	}
	(months+7)->days[30].day=100;
	for(i=0;i<30;i++){
		(months+8)->days[i].day=(i+246+balancer)%7;
		(months+8)->days[i].num=i+247;
		(months+8)->days[i].pt=0;(months+8)->days[i].pt=0;
	}
	(months+8)->days[30].day=100;
	for(i=0;i<30;i++){
		(months+9)->days[i].day=(i+276+balancer)%7;
		(months+9)->days[i].num=i+277;
		(months+9)->days[i].pt=0;(months+9)->days[i].pt=0;
	}
	(months+9)->days[30].day=100;
	for(i=0;i<30;i++){
		(months+10)->days[i].day=(i+306+balancer)%7;
		(months+10)->days[i].num=i+307;
		(months+10)->days[i].pt=0;(months+10)->days[i].pt=0;
	}
	(months+10)->days[30].day=100;
	if(leapYear==1){
		for(i=0;i<30;i++){
			(months+11)->days[i].day=(i+336+balancer)%7;
			(months+11)->days[i].num=i+337;
			(months+11)->days[i].pt=0;(months+11)->days[i].pt=0;
		}
		(months+11)->days[30].day=100;
	}
	else{
		for(i=0;i<29;i++){
			(months+11)->days[i].day=(i+336+balancer)%7;
			(months+11)->days[i].num=i+337;
			(months+11)->days[i].pt=0;(months+11)->days[i].pt=0;
		}
		(months+11)->days[29].day=100;
		(months+11)->days[30].day=100;
	}
}
