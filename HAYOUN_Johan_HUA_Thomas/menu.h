# include <stdlib.h>
# include <stdio.h>
# include <wchar.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>


 
#define clear() printf("\033[H\033[J")
void loadBye();
void loadTitle();
char key_pressed();
void loadingScreen();
