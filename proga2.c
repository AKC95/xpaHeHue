#include <ncurses.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define SLEEP 50

static void *threadFunc(void *arg);


int main()
{
  initscr();
  printw("Please enter the name of the file : \n");
  char fname[10];
  getstr(fname);
  FILE * file = fopen(fname, "r");
  if (file==NULL)
  {
	  endwin();
	  printf("\nSorry. I cannot find file '%s'\n", fname);		 
	  return 0;
  } 	
	
	keypad(stdscr, true);
	noecho();
        pthread_t thread;
	halfdelay(100);
	printw(" 'C' - continue\n 'S' - stop\n 'Q' - exit \n");
	
	bool ex = false;
	while(!ex)
	{
		int ch = getch();
		switch(ch)
		{
			case ERR: 
				{
				break;
				}
			case 99:
				{
				pthread_create(&thread, NULL, threadFunc, file);
				break;
				}	
			case 115:
				{
				 printw("\nPAUSE \n 'C' - continue\n 'S' - stop\n 'Q' - exit \n");
				 pthread_cancel(thread);
				 break;
				}
			case 113: 
				{
				pthread_cancel(thread);
                                ex=true; 
				break;
				}
			default:
				{
				printw("unknown key \n 'C' - continue\n 'S' - PAUSE\n 'Q' - exit \n"); 
				break;
				}
		}
		refresh();
	}
	pthread_join(thread, NULL);
	endwin();
	return 0;
}


static void *threadFunc(void *arg)

{

    char spases;
    fread(&spases, 1, 1, arg);	
    while (!feof(arg))
    {

        printw("%c", spases);
        fread(&spases, 1, 1, arg);
	napms(SLEEP);    
	refresh();
    }
    pthread_exit(NULL);

}
