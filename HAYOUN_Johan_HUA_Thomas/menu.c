# include <stdlib.h>
# include <stdio.h>
# include <wchar.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
#define PROGRESS_BAR_WIDTH 30 
#define LOADING_TIME_SECONDS 10 


void loadingScreen();
void loadTitle();
char key_pressed();
void loadBye();



void loadingScreen(){
 char progress_bar[PROGRESS_BAR_WIDTH + 1] ; 
    int progress_level = 0 ; 
    int percent ; 

    /* Initialise progress bar string */ 
    memset( progress_bar, '-', PROGRESS_BAR_WIDTH ) ; 
    progress_bar[PROGRESS_BAR_WIDTH] = '\0' ; 
     
    /* for 0 to 100%... */ 
    for( percent = 0; percent <= 100; percent++ ) 
    { 
        /* Calculate progress bar level, and modify string */ 
        progress_level = (percent * PROGRESS_BAR_WIDTH) / 100 ; 
        memset(progress_bar, '#', progress_level ) ; 

        /* return cursor to start of line and display bar */ 
        printf( "\r%s(%d%%)", progress_bar, percent ) ; 
        usleep( LOADING_TIME_SECONDS * 1000 ) ; 
    }
}
 
void loadTitle(){
char str[2];
FILE* fichier = NULL;
int i=0;
	
	fichier = fopen("title.txt","r+");
	
	char c;
 

char tab[10000];
	
	while ((c=getc(fichier))!=EOF) {
		str[0] = c;
		str[1] = '\0';
		strcat(tab, str);
		if(c == '\n')
		{
			i++;
		}
		
	}	
	
	printf("%s", tab);

	fclose(fichier);
}

void loadBye(){
char str[2];
FILE* fichier = NULL;
int i=0;
	
	fichier = fopen("goodBye.txt","r+");
	
	char c;
 

char tab[5000];
	
	while ((c=getc(fichier))!=EOF) {
		str[0] = c;
		str[1] = '\0';
		strcat(tab, str);
		if(c == '\n')
		{
			i++;
		}
		
	}	
	
	printf("%s", tab);

	fclose(fichier);
}

char key_pressed()
{
    struct termios oldterm, newterm;
    int oldfd; 
    char c, result = 0;

    tcgetattr (STDIN_FILENO, &oldterm);
    newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
    tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
    oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
    c = getchar();
    tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
    fcntl (STDIN_FILENO, F_SETFL, oldfd);

    if (c != EOF) {
        ungetc(c, stdin); result = getchar();
    }
    return result;
}





