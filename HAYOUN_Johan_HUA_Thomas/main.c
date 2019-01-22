#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "menu.h"
#include "dangerMode.h"
#include "trafic.h"





int main(){
	char userchoice;
	clearScreen();
	
	
	loadTitle();
	while (1) //loop to scan the button state
	{  
		userchoice = key_pressed();
		if (userchoice) 
        {
        		
            if(userchoice == '1'){
           
            loadingScreen();
            system("play -q 'A-Town-With-An-Ocean-View-Jazz-Ver.-Kikis-Delivery-Service.mp3'&");
            srand (time(NULL));
            gameLoop();
            }
            
            else if (userchoice == '2'){
            system("play -q 'One-Summers-Day-Jazz-Ver.-Spirited-Away.mp3'&");
            loadingScreen();
            srand (time(NULL));
            gameLoop2();
            }
            
            else if (userchoice == '3'){
            clearScreen();
            loadBye();
            break;
            }
        }
     
    }	

	return 0;
}
