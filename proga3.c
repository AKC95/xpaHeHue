#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <pthread.h>

void *Fvis1();// первый гость
void *Fvis2();// второй гость
void *Fvis3();// третий гость
void *Fboss();// хозяин

int nbotle_refr = 10; //в холодильнике 10 бутылок
int vis[3][2]; //состояние гостя и количество выпитых им бутылок
bool bossdo=0; //состояние владельца
int i;  

pthread_mutex_t refr; 
pthread_t vis1,vis2,vis3, boss;	

int main()
{
	initscr();	
	pthread_create(&boss, NULL, Fboss, NULL);	
        pthread_create(&vis1, NULL, Fvis1, NULL);
	pthread_create(&vis2, NULL, Fvis2, NULL);
	pthread_create(&vis3, NULL, Fvis3, NULL); 
	
	vis[1][2]=0; //количество выпитых буьылок 0
	vis[2][2]=0;
	vis[3][2]=0;
       
	//цикл печати информации о состоянии
	while(1)
	{
		

		for(i=1; i<=3; i++)
		{
			//имя гостя
			if(i==1) 
			  printw("Vasyan ");
			if(i==2) 
			  printw("Hattab ");
			if(i==3) 
			  printw("Ivan ");

			//состояние гостя
			printw("vypil %d butilok. Teper' on ", vis[i][2]);
			if(vis[i][1]==1) 
			  printw("v o4eredi.");
			if(vis[i][1]==2) 
			  printw("beret butilku.");
			if(vis[i][1]==3) 
			  printw("vypivaet.");
			if(vis[i][1]==4) 
			  printw("dryhnet.");
			
			printw("\n");
				
		}
		if(bossdo==1)   
                  printw("Boss kladet 1 butilku. Gosti ne mogut podoyti k holodilniku.\n");
		if(bossdo==0)   
                  printw("Boss gulyaet\n");
		printw("Butilok v holodilnike = %d\n", nbotle_refr );		
		refresh();		
		napms(1000);
		clear();
		if(nbotle_refr==0) 
		{ 
		  printw("The END"); 
		  refresh();  
		  napms(60000);//ждем минуту
		  endwin();
		  return 0;
		}
		
	}
	
}
	


void *Fboss()
{
	pthread_mutex_init(&refr, NULL);
	srand(time(NULL));
	//хозяин	
	while(1)
	{
		//с веротяностью 1/25 владелец зайдет, посчитает бутылки и добавит 1 новую 
		if(rand()%25 +1 == 1) 
		{
			bossdo=1;//хозяин открыл холодильник и снял все lock
			pthread_mutex_init(&refr, NULL);
			pthread_mutex_lock(&refr);
			napms(30000); 
			pthread_mutex_unlock(&refr);
			nbotle_refr+=1;	
			bossdo=0;//гуляет
		}
		napms(1000);	
	}
}


void *Fvis1()
{
	//первый гость
	while(1)
	{
		vis[1][1]=1;//гость встал в очередь за пивом
       		pthread_mutex_lock(&refr);
		vis[1][1]=2;//гость берет бутылку из холодильника (5 секунд)
		napms(5000);
		//если в холодильнике нет владельца, то закрывает mutex
		if(bossdo==0)
		pthread_mutex_unlock(&refr);  		
		
		vis[1][1]=3;//пьет пиво 20 секунд
		napms(20000);
 		nbotle_refr--;
		vis[1][2]++;//количество выпитых бутылок +1
		//проверка на трезвость
		if(vis[1][2]==7) 
		{
		  vis[1][1]=4; 
		  napms(120000);
		} //если выпито 7 бутылок, спит 2 минуты
	}
}

void *Fvis2()
{
	//второй гость
	while(1)
	{
		vis[2][1]=1;//гость встал в очередь за пивом
       		pthread_mutex_lock(&refr);
		vis[2][1]=2;//пгость берет бутылку из холодильника (5 секунд)
		napms(5000);
		//если в холодильнике нет владельца, то закрывает mutex
		if(bossdo==0)
		pthread_mutex_unlock(&refr);  
		
		
		vis[2][1]=3;//пьет пиво 20 секунд
		napms(20000); 
                nbotle_refr--;
		vis[2][2]++;//количество выпитых бутылок +1
		//проверка на трезвость
		if(vis[2][2]==7) 
		{
		  vis[2][1]=4; 
		  napms(120000);
		} //если выпито 7 бутылок, спит 2 минуты
	}
}

void *Fvis3()
{
	//третий гость
	while(1)
	{
		vis[3][1]=1;//гость встал в очередь за пивом
       		pthread_mutex_lock(&refr);
		vis[3][1]=2;//гость берет бутылку из холодильника (5 секунд)
		napms(5000);
		//если в холодильнике нет владельца, то закрывает mutex
		if(bossdo==0)
		pthread_mutex_unlock(&refr);  
		
		
		vis[3][1]=3;//пьет пиво 20 секунд
		napms(20000);
		nbotle_refr--; 
		vis[3][2]++;//количество выпитых бутылок +1
		//проверка на трезвость
		if(vis[3][2]==7) 
		{
		  vis[3][1]=4; 
		  napms(120000);
		} //если выпито 7 бутылок, спит 2 минуты
	}
}
