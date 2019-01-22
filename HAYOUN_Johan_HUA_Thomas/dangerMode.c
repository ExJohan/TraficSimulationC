#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>


typedef struct Voiture2 Voiture2;
struct Voiture2
{
	char direction;	/*N => Nord, S => Sud, E => EST, O => OUEST*/
	int posx;	/*Position courante x de la voiture*/
	int posy;	/*Position courante y de la voiture*/
	int ravitaillement; /*1=>ravitaillement 2=>carburant et 0=>sinon*/
	int parking;
	int etat;        /*État du véhicule => actif ou inactif*/
	char color;
	int madCar;
	int pompier;
	int crazy;
	
	struct Voiture2 * NXT; /*Pointeur vers une prochaine voiture,necessaire pour la liste chainée*/
	};

typedef struct Liste2 Liste2;
struct Liste2 {
	Voiture2  * premier;
	};

typedef struct Pietons2 Pietons2;
struct Pietons2
{
	int direction;	//aller =  0 ou retour = 1
	int posx;	/*Position courante x du pieton*/
	int posy;	/*Position courante y du pieton*/	
	int spawnx; 
	int spawny;
	struct Pietons2 * NXT; /*Pointeur vers une prochaine voiture,necessaire pour la liste chainée*/
	};

typedef struct ListePiet2 ListePiet2;
struct ListePiet2 {
	Pietons2  * premier;
	};

Liste2 *initialisation2(){

	Liste2 *liste2 = malloc(sizeof(*liste2));
	Voiture2 * maVoiture2 = malloc(sizeof(*maVoiture2));


	if (liste2 == NULL || maVoiture2 == NULL){
		exit(EXIT_FAILURE);
		}

	maVoiture2 -> direction = 'S';
	maVoiture2 -> posx = 10;
	maVoiture2 -> posy = 0;
	maVoiture2 -> ravitaillement = 0;
	maVoiture2 -> parking = 0;
	maVoiture2 -> etat = 1;
	maVoiture2 -> NXT = NULL;
	maVoiture2 -> color = 'R';
	liste2->premier = maVoiture2;
	return liste2;

	}

ListePiet2 *initPiet2(){

	ListePiet2 *listePiet2 = malloc(sizeof(*listePiet2));
	Pietons2 * monPiet2 = malloc(sizeof(*monPiet2));


	if (listePiet2 == NULL || monPiet2 == NULL){
		exit(EXIT_FAILURE);
		}

	monPiet2 -> direction = 0;
	monPiet2 -> posx = 97;
	monPiet2 -> posy = 33;
	monPiet2->NXT = NULL;
	listePiet2->premier = monPiet2;
	return listePiet2;

	}

void insertion2(Liste2 *liste, int *dirPos, int theMadCar, int thePompier){

	int aleaVoit = rand()%2; //Si fait spawn une voiture (actuellement une fois sur deux)
	int aleaColor = rand()%5;

	if(theMadCar == 1){
		Voiture2 *nouveau = malloc(sizeof(*nouveau));
		if (liste == NULL || nouveau == NULL){
	    	exit(EXIT_FAILURE);
		}
		nouveau->madCar = 1;
		nouveau->etat = 1;
		nouveau->posx = 147;
		nouveau->posy = 46;
		switch(aleaColor){
			case 0 :
				nouveau->color = 'R';
				break;
			case 1 : 
				nouveau->color = 'D';
				break;
			case 2 :
				nouveau->color = '5';
				break;
			case 3 :
				nouveau->color = '4';
				break;
			case 4 :
				nouveau->color = 'S';
				break;
		}
		nouveau->direction = 'N';
		nouveau->ravitaillement = 0;
		nouveau->parking = 0;
		/* Insertion de l'élément au début de la liste */
		nouveau->NXT = liste->premier;
		liste->premier = nouveau;
	}

	else if(theMadCar == 2){
		Voiture2 *nouveau = malloc(sizeof(*nouveau));
		if (liste == NULL || nouveau == NULL){
	    	exit(EXIT_FAILURE);
		}
		nouveau->madCar = 1;
		nouveau->etat = 1;
		nouveau->posx = 10;
		nouveau->posy = 0;
		switch(aleaColor){
			case 0 :
				nouveau->color = 'R';
				break;
			case 1 : 
				nouveau->color = 'D';
				break;
			case 2 :
				nouveau->color = '5';
				break;
			case 3 :
				nouveau->color = '4';
				break;
			case 4 :
				nouveau->color = 'S';
				break;
		}
		nouveau->direction = 'S';
		nouveau->ravitaillement = 0;
		nouveau->parking = 0;
		/* Insertion de l'élément au début de la liste */
		nouveau->NXT = liste->premier;
		liste->premier = nouveau;
	}

	else if(theMadCar == 3){
		Voiture2 *nouveau = malloc(sizeof(*nouveau));
		if (liste == NULL || nouveau == NULL){
	    	exit(EXIT_FAILURE);
		}
		nouveau->pompier = 0;
		nouveau->etat = 1;
		nouveau->posx = 145;
		nouveau->posy = 10;
		switch(aleaColor){
			case 0 :
				nouveau->color = 'R';
				break;
			case 1 : 
				nouveau->color = 'D';
				break;
			case 2 :
				nouveau->color = '5';
				break;
			case 3 :
				nouveau->color = '4';
				break;
			case 4 :
				nouveau->color = 'S';
				break;
		}
		nouveau->direction = 'O';
		nouveau->ravitaillement = 0;
		nouveau->parking = 0;
		nouveau->crazy = 1;
		/* Insertion de l'élément au début de la liste */
		nouveau->NXT = liste->premier;
		liste->premier = nouveau;
	}

	else if(thePompier == 1){
		Voiture2 *nouveau = malloc(sizeof(*nouveau));
		if (liste == NULL || nouveau == NULL){
	    	exit(EXIT_FAILURE);
		}
		nouveau->pompier = 1;
		nouveau->etat = 1;
		nouveau->posx = 147;
		nouveau->posy = 46;
		nouveau->color = 'Y';
		nouveau->direction = 'N';
		nouveau->ravitaillement = 0;
		nouveau->parking = 0;
		/* Insertion de l'élément au début de la liste */
		nouveau->NXT = liste->premier;
		liste->premier = nouveau;
	}

		else if(thePompier == 2){
		Voiture2 *nouveau = malloc(sizeof(*nouveau));
		if (liste == NULL || nouveau == NULL){
	    	exit(EXIT_FAILURE);
		}
		nouveau->pompier = 1;
		nouveau->etat = 1;
		nouveau->posx = 10;
		nouveau->posy = 0;
		nouveau->color = 'Y';
		nouveau->direction = 'S';
		nouveau->ravitaillement = 0;
		nouveau->parking = 0;
		/* Insertion de l'élément au début de la liste */
		nouveau->NXT = liste->premier;
		liste->premier = nouveau;
	}


	else{
		if (aleaVoit == 0){
			/* Création du nouvel élément */
			Voiture2 *nouveau = malloc(sizeof(*nouveau));
			if (liste == NULL || nouveau == NULL){
		        	exit(EXIT_FAILURE);
				}
			nouveau->etat = 1;
			nouveau->posx = dirPos[0];
			nouveau->posy = dirPos[1];
			switch(aleaColor){
				case 0 :
					nouveau->color = 'R';
					break;
				case 1 : 
					nouveau->color = 'D';
					break;
				case 2 :
					nouveau->color = '5';
					break;
				case 3 :
					nouveau->color = '4';
					break;
				case 4 :
					nouveau->color = 'S';
					break;
				}


			switch(dirPos[2]){
				case 0 :			
					nouveau->direction = 'N';
					nouveau->ravitaillement = 0;
					nouveau->parking = dirPos[3];
					break;
				
				case 1 : 
					nouveau->direction = 'S';
					nouveau->ravitaillement = dirPos[3];
					nouveau->parking = 0;
					break;
		
				case 2 :
					nouveau->direction = 'E';
					nouveau->ravitaillement = 0;
					nouveau->parking = 0;
					break;

				case 3 :
					nouveau->direction = 'O';
					nouveau->ravitaillement = 0;
					nouveau->parking = 0;
					break;
				}
			/* Insertion de l'élément au début de la liste */
			nouveau->NXT = liste->premier;
			liste->premier = nouveau;
			}
		}
	}

void insertPiet2(ListePiet2 *liste, int posx, int posy, int direction, int spawnx, int spawny){

		/* Création du nouvel élément */
	Pietons2 *nouveau = malloc(sizeof(*nouveau));
	if (liste == NULL || nouveau == NULL){
        	exit(EXIT_FAILURE);
		}
	nouveau->posx = posx;
	nouveau->posy = posy;
	nouveau->spawny = spawny;
	nouveau->spawnx = spawnx;
	nouveau->direction = direction;
	/* Insertion de l'élément au début de la liste */
	nouveau->NXT = liste->premier;
	liste->premier = nouveau;
	}

void RemoveNode2(Voiture2 * node, Voiture2 ** premier) {

	Voiture2 * current = (*premier)->NXT;
	Voiture2 * previous = *premier;
	while (current != NULL && previous != NULL) {
		if (current == node) {
			Voiture2 * temp = current;
			previous->NXT = current->NXT;
			free(temp);
			return;
			}
		previous = current;
		current = current->NXT;
		}
	return;
	}

void RemovePiet2(Pietons2 * node, Pietons2 ** premier) {

	Pietons2 * current = (*premier)->NXT;
	Pietons2 * previous = *premier;
	while (current != NULL && previous != NULL) {
		if (current == node) {
			Pietons2 * temp = current;
			previous->NXT = current->NXT;
			free(temp);
			return;
			}
		previous = current;
		current = current->NXT;
		}
	return;
	}


void clearScreen2(){
	const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
	write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
	}

void setDirPos2(int *dirPos){
	
	int alea = rand()%4;
	//if (alea != 4) { alea = alea%4; }
	int aleaDir = rand()%2;
	int aleaRav = rand()%10; //pour l'instant rav et park
	int aleaPark = rand()%4;
	switch (alea){
		
		case 0 : 
			dirPos[0] = 10;
			dirPos[1] = 0;
			dirPos[2] = 1;
			if(aleaRav == 0){
				dirPos[3] = 1;
				}
			else{
				dirPos[3] = 0;
				}
			break;
		case 1 : 
			dirPos[0] = 147;
			dirPos[1] = 46;
			dirPos[3] = 0;
			if(aleaDir == 0){
				dirPos[2] = 0;
				if(aleaPark == 0){
					dirPos[3] = 1;
					}
				else{
					dirPos[3] = 0;
					}
				}
			else{
				dirPos[2] = 3;
				}
			break;
		case 2 :
			dirPos[3] = 0;
			dirPos[0] = 147;
			dirPos[1] = 10;
			if(aleaDir == 0){
				dirPos[2] = 0;
				}
			else{
				dirPos[2] = 3;
				}
			break;

		case 3 :
			dirPos[0] = 0;
			dirPos[1] = 12;
			if(aleaDir == 0){
				dirPos[2] = 2;
				dirPos[3] = 0;
				}
			else{
				dirPos[2] = 1;
				if(aleaRav == 0) {
					dirPos[3] = 1;
					}
				else{
					dirPos[3] = 0;
					}
				}
			break;
		}
	}

void printAccident(char ** matDisplay){

	matDisplay[19][50] = 'a';
	matDisplay[19][51] = 'c';
	matDisplay[19][52] = 'c';
	matDisplay[19][53] = 'i';
	matDisplay[19][54] = 'd';
	matDisplay[19][55] = 'e';
	matDisplay[19][56] = 'n';
	matDisplay[19][57] = 't';
	}

void dispVoitOnMat2(char ** matDisplay, Liste2 * liste){
	if (liste == NULL){
        	exit(EXIT_FAILURE);
		}
	Voiture2 *actuel = liste->premier;
	while(actuel != NULL){
		matDisplay[actuel->posy][actuel->posx] = 'R';
		actuel = actuel->NXT;
		}
	}

void dispVoitOnMatVoit2(char ** matDisplay, Liste2 * liste){
	if (liste == NULL){
        	exit(EXIT_FAILURE);
		}
	Voiture2 *actuel = liste->premier;
	while(actuel != NULL){
		matDisplay[actuel->posy][actuel->posx] = actuel->color;
		actuel = actuel->NXT;
		}
	}

void dispPietOnMat2(char ** matDisplay, ListePiet2 * liste){
	if (liste == NULL){
        	exit(EXIT_FAILURE);
		}
	Pietons2 *actuel = liste->premier;
	while(actuel != NULL){
		matDisplay[actuel->posy][actuel->posx] = '9';
		actuel = actuel->NXT;
		}
	}


void getDisplay2(char ** matDisplayBase){

	FILE * fichPlan = NULL;
	fichPlan = fopen("Plan_infoV2.txt","r+");
	char c;
	int i;
	int j;
	for(i = 0; i<50 ; i++){
		for(j = 0; j<149 ; j++){
			c = fgetc(fichPlan);
			matDisplayBase[i][j] = c;
			}
		}
	fclose(fichPlan);
	}

void getVoitMat2(int ** voitMat){
	int i,j;
	printf("\n\n");
	FILE * fichMat = NULL;
	fichMat = fopen("Matrice.txt","r+");
	for( i = 0; i<50 ; i++){
		for( j = 0; j<148 ; j++){
			fscanf(fichMat, "%d", &voitMat[i][j]);
			}
		}
	fclose(fichMat);
	}

void getPietMat2(int ** pietMat){
	int i,j;
	printf("\n\n");
	FILE * fichMat = NULL;
	fichMat = fopen("MatPietons.txt","r+");
	for( i = 0; i<50 ; i++){
		for( j = 0; j<148 ; j++){
			fscanf(fichMat, "%d", &pietMat[i][j]);
			}
		}
	fclose(fichMat);
	}

void printMatTest2(int ** voitMat){
	int i,j;
	printf("\n");
	for( i = 0; i<50 ; i++){
		for(j = 0; j<149 ; j++){
			printf("%d",voitMat[i][j]);
			}
		printf("\n");
		}
	}

void copy2(char ** mat1, char ** mat2){

	int i;
	int j;
	for(i = 0; i < 50 ; i++){
		for(j = 0 ; j < 149; j++){
			mat1[i][j] = mat2[i][j];
			}
		}
	}


void display2(char ** matDisplay){
	
	printf("\n");
	char theChar;
	int i;
	int j;
	for(i = 0 ; i<50 ; i++) {
		for(j = 0 ; j < 149 ; j++){
			theChar = matDisplay[i][j]; // On lit le caractère
			switch(theChar) {
				case 'f':
					printf("\033[0;31m▀");
					break;
				case 'z':
					printf("\033[0;32m▀");
					break;
				
				case 'v':
					printf("\033[0;32m▄");
					break;

				case 'j':
					printf("\033[0;31m▄");
					break;

				case '(':
					printf("\033[42;31m🚋");
					break;

				case '+':
					printf("\033[42;31m🚂");
					break;

				case 'x':
					printf("\033[42;31m🚂");
					break;

				case 'C':
				printf("\033[37;40m-");
				break;

				case 'G':
				printf("\033[37;40m|");
				break;
			
				case 'V': 
					printf("\033[0;35m║");
					break;
			
				case 'H':
					printf("\033[0;35m═");
					break;

				case 'U':
					printf("\033[0;35m╝");
					break;
	
				case 'I':
					printf("\033[0;35m╚");
					break;

				case 'J':
					printf("\033[0;35m╗");
					break;

				case 'K':
					printf("\033[0;35m╔");
					break;

				case 'E':
					printf("\033[0;44m ");
					break;
			
				case 'T':
					printf("\033[0;35m╦");
					break;

				case 'N':
					printf("\033[0;35m╩");
					break;

				case 'X':
					printf("\033[0;35m╬");
					break;

				case 'Q':
					printf("\033[0;35m╠");
					break;

				case 'Z':
					printf("\033[0;35m╣");
					break;
			
				case 'A': 
					printf("\033[0;32m🌲");
					break;

				case 'L':
					printf("\033[0;42m─");
					break;
				
				case 'u':
					printf("\033[0;32m▓");
					break;

				case ';':
					printf("\033[37;40m▮");
					break;

				case 'B': 
					printf("\033[34;40m ");
					break;

				case '0': 
					printf("\033[1;33m░");
					break;

				case '#': 
					printf("\033[0;0m─");
					break;
			
				case '!': 
					printf("\033[0;0m│");
					break;

				case '8': 
					printf("\033[0;0m┌");
					break;

				case '7': 
					printf("\033[0;0m┐");
					break;

				case '>': 
					printf("\033[0;0m┘");
					break;

				case '<': 
					printf("\033[0;0m└");
					break;


				case 'W': 
					printf("\033[0;40m─");
					break;

				case '1': 
					printf("\033[0;32m🌱");
					break;

				case '2': 
					printf("\033[0;33m🌻");
					break;

				case '3': 
					printf("\033[0;31m🌹");
					break;

				case '9': 
					printf("\033[37m🚶");
					break;

				case '6': 
					printf("👫");
					break;

				case 'R':
					printf("\033[37m🚖");
					break;

				case '5':
					printf("\033[34m🚖");
					break;

				case 'D':
					printf("\033[32m🚖");
					break;

				case '4':
					printf("\033[33m🚖");
					break;

				case 'Y':
					printf("\033[31m🚍");
					break;

				case 'S':
					printf("\033[31m🚘");
					break;


				case '%': 
					printf("\033[34;41m ");
					break;

				case 'M':
					printf("\033[0;31m▮");
					break;

				case '$':
					printf("\033[0;34m🚔");
					break;

				case '@':
					printf("\033[0;34m⛲️");
					break;

				case '?':
					printf("🍲");
					break;

				case '_':
					printf("\033[44;30m_");
					break;

				case '|':
					printf("\033[0;0m|");
					break;

				case ')':
					printf("\033[0;44m ");
					break;

				case '.':
					printf("\033[0;44m.");
					break;

				case 'q':
					printf("\033[0;0m¯");
					break;

				case 'y':
					printf("\033[0;0m_");
					break;
			
				case 'P':
					printf("\033[0;40m_");
					break;
			
				case '~':
					printf("\033[0;31m🏮");
					break;
			
			
				case 'h':
					printf("\033[0;32m🌳");
					break;
					
				case '&':
					printf("\033[33m█");
					break;
					
				case '`':
					printf("\033[33m▀");
					break;
					
				case 'w':
					printf("\033[33m▄");
					break;
					
				/*case '{':
					printf("\033[42;31m🚂");
					break;
					
				case '}':
					printf("\033[42;30m🚋");
					break; */

				default :
						printf("\033[0m%c",theChar);
						break;
				
				}
			}	         
	    }
	}

void printTram2(char ** matDisplay, int time, int timeBoucle){
	
	
	if(timeBoucle == 0){
	
		if(time == 5){
			system("play -q 'Le-son-de-la-cloche-du-tramway-de-Besançon..mp3'&");
			matDisplay[15][0] = 'x';
			matDisplay[18][147] = '+';
			}
		else if(time == 6){
			matDisplay[15][0] = '(';
			matDisplay[15][1] = 'x';
			matDisplay[18][147] = '(';
			matDisplay[18][146] = '+';
		
			}
		else if(time == 7){
			matDisplay[15][0] = '(';
			matDisplay[15][1] = '(';
			matDisplay[15][2] = 'x';
			matDisplay[18][147] = '(';
			matDisplay[18][146] = '(';
			matDisplay[18][145] = '+';
			}
		else if(time == 8){
			matDisplay[15][0] = '(';
			matDisplay[15][1] = '(';
			matDisplay[15][2] = '(';
			matDisplay[15][3] = 'x';
			matDisplay[18][147] = '(';
			matDisplay[18][146] = '(';
			matDisplay[18][145] = '(';
			matDisplay[18][144] = '+';
			}

		else if(time == 9){
			matDisplay[15][0] = '(';
			matDisplay[15][1] = '(';
			matDisplay[15][2] = '(';
			matDisplay[15][3] = '(';
			matDisplay[15][4] = 'x';
			matDisplay[18][147] = '(';
			matDisplay[18][146] = '(';
			matDisplay[18][145] = '(';
			matDisplay[18][144] = '(';
			matDisplay[18][143] = '+';
			}
	
		else if(time == 10){
			matDisplay[15][0] = '(';
			matDisplay[15][1] = '(';
			matDisplay[15][2] = '(';
			matDisplay[15][3] = '(';
			matDisplay[15][4] = '(';
			matDisplay[15][5] = 'x';
			matDisplay[18][147] = '(';
			matDisplay[18][146] = '(';
			matDisplay[18][145] = '(';
			matDisplay[18][144] = '(';
			matDisplay[18][143] = '(';
			matDisplay[18][142] = '+';
			}
		else if(time == 11){
			matDisplay[15][0] = '+';
			matDisplay[15][1] = '(';
			matDisplay[15][2] = '(';
			matDisplay[15][3] = '(';
			matDisplay[15][4] = '(';
			matDisplay[15][5] = '(';
			matDisplay[15][6] = 'x';
			matDisplay[18][147] = 'x';
			matDisplay[18][146] = '(';
			matDisplay[18][145] = '(';
			matDisplay[18][144] = '(';
			matDisplay[18][143] = '(';
			matDisplay[18][142] = '(';
			matDisplay[18][141] = '+';
			}
		else if(time >= 12 && time <= 59){
			matDisplay[15][time - 11] = '+';
			matDisplay[15][time - 10] = '(';
			matDisplay[15][time - 9] = '(';
			matDisplay[15][time - 8] = '(';
			matDisplay[15][time - 7] = '(';
			matDisplay[15][time - 6] = '(';
			matDisplay[15][time - 5] = 'x';
			matDisplay[18][158 - time] = 'x';
			matDisplay[18][157 - time] = '(';
			matDisplay[18][156 - time] = '(';
			matDisplay[18][155 - time] = '(';
			matDisplay[18][154 - time] = '(';
			matDisplay[18][153 - time] = '(';
			matDisplay[18][152 - time] = '+';
			}
		}
	if(timeBoucle == 1){
		if(time >= 0 && time <= 59){
			matDisplay[15][time + 49] = '+';
			matDisplay[15][time + 50] = '(';
			matDisplay[15][time + 51] = '(';
			matDisplay[15][time + 52] = '(';
			matDisplay[15][time + 53] = '(';
			matDisplay[15][time + 54] = '(';
			matDisplay[15][time + 55] = 'x';
			matDisplay[18][99 - time] = 'x';
			matDisplay[18][98 - time] = '(';
			matDisplay[18][97 - time] = '(';
			matDisplay[18][96 - time] = '(';
			matDisplay[18][95 - time] = '(';
			matDisplay[18][94 - time] = '(';
			matDisplay[18][93 - time] = '+';

			}
		}
	if(timeBoucle == 2){
		if(time >= 0 && time < 33){
			matDisplay[15][time + 109] = '+';
			matDisplay[15][time + 110] = '(';
			matDisplay[15][time + 111] = '(';
			matDisplay[15][time + 112] = '(';
			matDisplay[15][time + 113] = '(';
			matDisplay[15][time + 114] = '(';
			matDisplay[15][time + 115] = 'x';
			matDisplay[18][39 - time] = 'x';
			matDisplay[18][38 - time] = '(';
			matDisplay[18][37 - time] = '(';
			matDisplay[18][36 - time] = '(';
			matDisplay[18][35 - time] = '(';
			matDisplay[18][34 - time] = '(';
			matDisplay[18][33 - time] = '+';
			}

		else if(time == 33){
			matDisplay[15][time + 109] = '+';
			matDisplay[15][time + 110] = '(';
			matDisplay[15][time + 111] = '(';
			matDisplay[15][time + 112] = '(';
			matDisplay[15][time + 113] = '(';
			matDisplay[15][time + 114] = '(';
			matDisplay[18][39 - time] = 'x';
			matDisplay[18][38 - time] = '(';
			matDisplay[18][37 - time] = '(';
			matDisplay[18][36 - time] = '(';
			matDisplay[18][35 - time] = '(';
			matDisplay[18][34 - time] = '(';

			}
		else if(time == 34){
			matDisplay[15][time + 109] = '+';
			matDisplay[15][time + 110] = '(';
			matDisplay[15][time + 111] = '(';
			matDisplay[15][time + 112] = '(';
			matDisplay[15][time + 113] = '(';
			matDisplay[18][39 - time] = 'x';
			matDisplay[18][38 - time] = '(';
			matDisplay[18][37 - time] = '(';
			matDisplay[18][36 - time] = '(';
			matDisplay[18][35 - time] = '(';
			}
		else if(time == 35){
			matDisplay[15][time + 109] = '+';
			matDisplay[15][time + 110] = '(';
			matDisplay[15][time + 111] = '(';
			matDisplay[15][time + 112] = '(';
			matDisplay[18][39 - time] = '+';
			matDisplay[18][38 - time] = '(';
			matDisplay[18][37 - time] = '(';
			matDisplay[18][36 - time] = '(';
			}
		else if(time == 36){
			matDisplay[15][time + 109] = '+';
			matDisplay[15][time + 110] = '(';
			matDisplay[15][time + 111] = '(';
			matDisplay[18][39 - time] = 'x';
			matDisplay[18][38 - time] = '(';
			matDisplay[18][37 - time] = '(';
			}
		else if(time == 37){
			matDisplay[15][time + 109] = '+';
			matDisplay[15][time + 110] = '(';
			matDisplay[18][39 - time] = 'x';
			matDisplay[18][38 - time] = '(';
			}
		else if(time == 38){
			matDisplay[15][time + 109] = '+';
			matDisplay[18][39 - time] = 'x';
			}
		}
	}






void setObjectTime2(char ** matDisplay, int theTime){
	
	if(theTime <= 30){
		matDisplay[25][55] = 'f';
		matDisplay[34][55] = 'f';
		matDisplay[34][49] = 'j';
		matDisplay[8][8] = 'j';
		matDisplay[19][43] = 'f';
		matDisplay[19][43] = 'f';

		}
	else{
		matDisplay[25][55] = 'v';
		matDisplay[19][43] = 'v';
		matDisplay[34][55] = 'v';
		matDisplay[34][49] = 'z';
		matDisplay[8][8] = 'z';
		}

	
	
	}

void nextPos2(char ** matDisplay, int ** voitMat, int ** pietMat, Liste2 * liste, ListePiet2 * listePiet, int theTime, char ** matDisplayVoit){
		
	if (liste == NULL){
		exit(EXIT_FAILURE);
		}

	int aleaMarket;

	Voiture2 * voiture = liste->premier;
	Voiture2 * voitPrem = liste->premier;

	Pietons2 * pietons = listePiet->premier;
	Pietons2 * pietPrem = listePiet->premier;
	while(voiture != NULL){
//if pietons a coté de voiture etat se remet a 1
		if(voiture->etat == 1){

			if(voiture->direction == 'S'){

				if(voiture->posy <= 45 && voitMat[(voiture->posy)+2][(voiture->posx)-1] == 6 && theTime <= 30){
				}
				else if(voitMat[voiture->posy][voiture->posx] == 1){
					if(voitMat[voiture->posy][voiture->posx-1] == 8 && voiture->madCar == 1){
						voiture->posx = voiture->posx-2;
						voiture->etat = 0;
						}
					else if(matDisplay[(voiture->posy)+1][voiture->posx] != 'R'){
						if(voitMat[voiture->posy+1][voiture->posx] == 5 && voitMat[voiture->posy+1][(voiture->posx)-1] == 4 && matDisplay[(voiture->posy)+1][(voiture->posx)-1] == 'R'){ }
						else if(voitMat[voiture->posy+1][voiture->posx] == 5 && voitMat[voiture->posy+1][(voiture->posx)-1] == 4 && matDisplay[(voiture->posy)+1][(voiture->posx)-2] == 'R'){ }
						else if(voitMat[voiture->posy+1][voiture->posx] == 5 && voitMat[voiture->posy+1][(voiture->posx)-1] == 4 && matDisplay[(voiture->posy)+1][(voiture->posx)-3] == 'R'){ }
						else if(voitMat[voiture->posy+1][voiture->posx] == 5 && voitMat[voiture->posy+1][(voiture->posx)-1] == 4 && matDisplay[(voiture->posy)+1][(voiture->posx)-4] == 'R'){ }
						else if(matDisplay[voiture->posy+1][voiture->posx] == 'x' || matDisplay[voiture->posy+1][voiture->posx] == '+' || matDisplay[voiture->posy+1][voiture->posx] == '('){ }
						else if(matDisplay[voiture->posy][voiture->posx+3] == '&') {
							voiture->etat = 0;
							insertPiet2(listePiet, voiture->posx-1, voiture->posy, 0, 0, 0);
							}
						else if(matDisplay[voiture->posy][voiture->posx-3] == '&') {
							voiture->etat = 0;
							insertPiet2(listePiet, voiture->posx+1, voiture->posy, 0, 0, 0);
							}
						else{
						voiture->posy = (voiture->posy)+1;
							}
						}
					}
				else if(voitMat[voiture->posy][voiture->posx] == 5){
					if(voitMat[(voiture->posy)+1][voiture->posx] == 1){
						if(matDisplay[(voiture->posy)+1][voiture->posx] != 'R'){
							voiture->posy = (voiture->posy)+1;
							}
						}

					else if(voitMat[voiture->posy+1][voiture->posx] == 6 && voiture->ravitaillement == 1){
						if(matDisplay[voiture->posy+1][voiture->posx] != 'R'){
							voiture->posy = voiture->posy + 1;
							}
						}
					else if(voitMat[voiture->posy][(voiture->posx)+1] == 4){
						if(matDisplay[voiture->posy][voiture->posx+1] != 'R'){
							voiture->posx = voiture->posx + 1;
							}
						}
					}

				else if(voitMat[voiture->posy][voiture->posx] == 6){
					if(voitMat[(voiture->posy)+1][voiture->posx] == 1){
						if(matDisplay[(voiture->posy)+1][voiture->posx] != 'R'){
							voiture->posy = (voiture->posy)+1;
							}
						}

					else if(voitMat[voiture->posy][(voiture->posx)+1] == 4 && matDisplay[30][13] != 'R'){
						if(matDisplay[voiture->posy][voiture->posx+1] != 'R'){
							voiture->posx = voiture->posx + 1;
							}
						}

					else if(voitMat[voiture->posy][voiture->posx-1] == 3 && matDisplay[30][5] != 'R'){
						if(matDisplay[voiture->posy][voiture->posx-1] != 'R'){
							voiture->posx = voiture->posx - 1;
							}
						}
					}

				else if(voitMat[voiture->posy][voiture->posx] == 3 && voiture->posx > 0){
					if(matDisplay[voiture->posy][(voiture->posx)-1] != 'R'){
						voiture->posx = (voiture->posx)-1;
						} 
					}

				else if(voitMat[voiture->posy][voiture->posx] == 4 && voiture->posx != 146){
					if(matDisplay[voiture->posy][(voiture->posx)+1] != 'R'){
						voiture->posx = (voiture->posx)+1;
						}
					}
				else if(voitMat[voiture->posy][voiture->posx] == 4 && voiture->posx == 146){
					RemoveNode2(voiture, &voitPrem);	
					}
				}

			if(voiture->direction == 'N'){

				if(voiture->posy >= 3 && voitMat[(voiture->posy)-2][(voiture->posx)+1] == 6 && theTime <= 30){
				}


				else if(voitMat[voiture->posy][voiture->posx] == 2 && voiture->posy != 0){
					if(matDisplay[(voiture->posy)-1][voiture->posx] != 'R' && matDisplay[(voiture->posy)-1][voiture->posx] != '9'){
						if(voitMat[voiture->posy-1][voiture->posx] == 5 && voitMat[voiture->posy-1][(voiture->posx)+1] == 3 && matDisplay[(voiture->posy)-1][(voiture->posx)+1] == 'R'){ }
						else if(voitMat[voiture->posy-1][voiture->posx] == 5 && voitMat[voiture->posy-1][(voiture->posx)+1] == 3 && matDisplay[(voiture->posy)-1][(voiture->posx)+2] == 'R'){ }
						else if(voitMat[voiture->posy-1][voiture->posx] == 5 && voitMat[voiture->posy-1][(voiture->posx)+1] == 3 && matDisplay[(voiture->posy)-1][(voiture->posx)+3] == 'R'){ }
						else if(voitMat[voiture->posy-1][voiture->posx] == 5 && voitMat[voiture->posy-1][(voiture->posx)+1] == 3 && matDisplay[(voiture->posy)-1][(voiture->posx)+4] == 'R'){ }
						else if(matDisplay[voiture->posy-1][voiture->posx] == 'x' || matDisplay[voiture->posy-1][voiture->posx] == '+' || matDisplay[voiture->posy-1][voiture->posx] == '('){ }

						else{
						voiture->posy = (voiture->posy)-1;
							}
						}
					}
				else if(voitMat[voiture->posy][voiture->posx] == 2 && voiture->posy == 0){
						RemoveNode2(voiture, &voitPrem);	
						}
				else if(voitMat[voiture->posy][voiture->posx] == 5){

					if(voiture->parking == 1){
						if(matDisplay[voiture->posy][voiture->posx+1] != 'R' && matDisplay[(voiture->posy)-1][voiture->posx] != '9'){
							voiture->posx = (voiture->posx)+1;
							}
						}

					else if(voitMat[(voiture->posy)-1][voiture->posx] == 2){
						if(matDisplay[(voiture->posy)-1][voiture->posx] != 'R' && matDisplay[(voiture->posy)-1][voiture->posx] != '9'){
							voiture->posy = (voiture->posy)-1;
							}
						}
					else if(voitMat[voiture->posy][(voiture->posx)-1] == 3){
						if(matDisplay[voiture->posy][(voiture->posx)-1] != 'R' && matDisplay[(voiture->posy)-1][voiture->posx] != '9'){
							voiture->posx = (voiture->posx)-1;
							}
						}
					}
				else if(voitMat[voiture->posy][voiture->posx] == 3){

						if(voiture->madCar == 1 && voitMat[voiture->posy-1][voiture->posx] == 8){
							voiture->posy = voiture->posy-1;
							voiture->etat = 0;
						}

						else if(matDisplay[voiture->posy][(voiture->posx)-1] != 'R' && matDisplay[voiture->posy][(voiture->posx)-2] != 'R' && matDisplay[voiture->posy][(voiture->posx)-1] != '9'){
							voiture->posx = (voiture->posx)-1;
							}
					}
				else if(voitMat[voiture->posy][voiture->posx] == 4){
						if(matDisplay[voiture->posy][(voiture->posx)+1] != 'R' && matDisplay[voiture->posy][(voiture->posx)+1] != '9'){
							voiture->posx = (voiture->posx)+1;
							}
					}
				else if(voitMat[voiture->posy][voiture->posx] == 1){
						if(matDisplay[voiture->posy+1][voiture->posx] != 'R' && matDisplay[voiture->posy+1][voiture->posx] != '9'){
							voiture->posy = (voiture->posy)+1;
							}
					}
				else if(voitMat[voiture->posy][voiture->posx] == 7){
					if(voitMat[voiture->posy][voiture->posx-1] == 4 && matDisplay[voiture->posy+1][voiture->posx] != 'R' && voiture->parking == 1){
						voiture->posy = voiture->posy+1;
						voiture->etat = 0;
						voiture->parking = 0;
						insertPiet2(listePiet, voiture->posx+1, voiture->posy, 0, voiture->posx, voiture->posy);
						}
					else if(voitMat[voiture->posy][voiture->posx-1] == 4 && matDisplay[voiture->posy+1][voiture->posx] == 'R'){
						voiture->posx = voiture->posx+1;
						}
					else if(voitMat[voiture->posy][voiture->posx-1] == 4 && voiture->parking == 0){
						voiture->posx = voiture->posx+1;
						}
					}
				if(voiture->posx == 91 && voiture->posy == 21){
					voiture->parking = 0;
					}

				}
			if(voiture->direction == 'O'){
				if(voiture->crazy == 1){
					int isNotGoing = 1;
					int aleaGoing;
					while(isNotGoing == 1){
						aleaGoing = rand()%5;
						switch(aleaGoing){
							case 0 ://TryUp
								if(voiture->posy > 2 && matDisplay[voiture->posy-1][voiture->posx] != 'R' && voitMat[voiture->posy-1][voiture->posx] != 0){
									voiture->posy = voiture->posy-1;
									isNotGoing = 0;
									}
								break;
							case 1 ://TryDown
								if(matDisplay[voiture->posy+1][voiture->posx] != 'R' && voitMat[voiture->posy+1][voiture->posx] != 0){
									voiture->posy = voiture->posy+1;
									isNotGoing = 0;
									}
								break;
							case 2 ://TryLeft
								if(voiture->posx > 2 && matDisplay[voiture->posy][voiture->posx-1] != 'R' && matDisplay[voiture->posy][voiture->posx-1] != 'R'&& voitMat[voiture->posy][voiture->posx-1] != 0){
									voiture->posx = voiture->posx-1;
									isNotGoing = 0;
									}
								break;
							case 4 ://TryLeft
								if(voiture->posx > 2 && matDisplay[voiture->posy][voiture->posx-1] != 'R' && matDisplay[voiture->posy][voiture->posx-1] != 'R' && voitMat[voiture->posy][voiture->posx-1] != 0){
									voiture->posx = voiture->posx-1;
									isNotGoing = 0;
									}
								break;
							case 3 ://TryRight
								if(voiture->posx < 146 && matDisplay[voiture->posy][voiture->posx+1] != 'R' && voitMat[voiture->posy][voiture->posx+1] != 0 && matDisplay[voiture->posy][voiture->posx+2] != 'R'){
									voiture->posx = voiture->posx+1;
									isNotGoing = 0;
									}
								break;
							}
						}
					}

				else{
				
					if(voitMat[voiture->posy-2][(voiture->posx)+1] == 6 && theTime <= 30){
					}
					else if(voitMat[voiture->posy][voiture->posx] == 3 && voiture->posx != 0){
						if(matDisplay[voiture->posy][voiture->posx-1] != 'R' && matDisplay[voiture->posy][(voiture->posx)-2] != 'R'){
							if(voitMat[voiture->posy][(voiture->posx)-1] == 5 && voitMat[voiture->posy-1][(voiture->posx)-1] == 1 && matDisplay[(voiture->posy)-1][(voiture->posx)-1] == 'R'){ }
							else if(voitMat[voiture->posy][(voiture->posx)-1] == 5 && voitMat[voiture->posy-1][(voiture->posx)-1] == 1 && matDisplay[(voiture->posy)-2][(voiture->posx)-1] == 'R'){ }
						//	else if(voitMat[voiture->posy][(voiture->posx)-1] == 5 && voitMat[voiture->posy-1][(voiture->posx)-1] == 1 && matDisplay[(voiture->posy)-3][(voiture->posx)-1] == 'R'){ }
							else if(voitMat[voiture->posy][(voiture->posx)-1] == 3 && matDisplay[voiture->posy][(voiture->posx)-1] == 'R'){ }


							else{
								voiture->posx = (voiture->posx)-1;
								}
							}
						}
					else if(voitMat[voiture->posy][voiture->posx] == 3 && voiture->posx == 0){
						RemoveNode2(voiture, &voitPrem);	
						}
					else if(voitMat[voiture->posy][voiture->posx] == 2){
						if(matDisplay[voiture->posy-1][voiture->posx] == 'x' || matDisplay[voiture->posy-1][voiture->posx] == '+' || matDisplay[voiture->posy-1][voiture->posx] == '('){ }
						else if(matDisplay[(voiture->posy)-1][voiture->posx] != 'R'){
							voiture->posy = (voiture->posy)-1;
							}
						}
					else if(voitMat[voiture->posy][voiture->posx] == 5){
						if(voitMat[voiture->posy][(voiture->posx)-1] == 3){
							if(matDisplay[voiture->posy][(voiture->posx)-1] != 'R') {
								voiture->posx = (voiture->posx)-1;
								}
							}
						else if(voitMat[(voiture->posy)-1][voiture->posx] == 2){
							if(matDisplay[(voiture->posy)-1][voiture->posx] != 'R'){
								voiture->posy = (voiture->posy)-1;
								}
							}
						}
					}
				}
			if(voiture->direction == 'E'){
				
				if(voitMat[voiture->posy][(voiture->posx)+1] == 6 && theTime <= 30){
				}
				else if(voitMat[voiture->posy][voiture->posx] == 4 && voiture->posx != 147){
					if(matDisplay[(voiture->posy)+1][voiture->posx] != 'R'){
						if(voitMat[voiture->posy][(voiture->posx)+1] == 5 && voitMat[voiture->posy+1][(voiture->posx)+1] == 2 && matDisplay[(voiture->posy)+1][(voiture->posx)+1] == 'R'){ }
						else if(voitMat[voiture->posy][(voiture->posx)+1] == 5 && voitMat[voiture->posy+1][(voiture->posx)+1] == 2 && matDisplay[(voiture->posy)+2][(voiture->posx)+1] == 'R'){ }
						else if(voitMat[voiture->posy][(voiture->posx)+1] == 5 && voitMat[voiture->posy+1][(voiture->posx)+1] == 2 && matDisplay[(voiture->posy)+3][(voiture->posx)+1] == 'R'){ }
						else if(voitMat[voiture->posy][(voiture->posx)+1] == 5 && voitMat[voiture->posy+1][(voiture->posx)+1] == 2 && matDisplay[(voiture->posy)+4][(voiture->posx)+1] == 'R'){ }
						else if(voitMat[voiture->posy][(voiture->posx)+1] == 5 && voitMat[voiture->posy+1][(voiture->posx)+1] == 2 && matDisplay[(voiture->posy)+5][(voiture->posx)+1] == 'R'){ }

						else{
							voiture->posx = (voiture->posx)+1;
							}
						}
					}

				else if(voitMat[voiture->posy][voiture->posx] == 4 && voiture->posx != 147){
					if(matDisplay[voiture->posy][(voiture->posx)+1] != 'R'){
						voiture->posx = (voiture->posx)+1;
						}
					}

				else if(voitMat[voiture->posy][voiture->posx] == 4 && voiture->posx == 147){
					RemoveNode2(voiture, &voitPrem);	
					}

				else if(voitMat[voiture->posy][voiture->posx] == 2){
					if(matDisplay[voiture->posy-1][voiture->posx] == 'x' || matDisplay[voiture->posy-1][voiture->posx] == '+' || matDisplay[voiture->posy-1][voiture->posx] == '('){ }
					else if(matDisplay[(voiture->posy)-1][voiture->posx] != 'R'){
						voiture->posy = (voiture->posy)-1;
						}
					}
				else if(voitMat[voiture->posy][voiture->posx] == 5){
					if(voitMat[voiture->posy][(voiture->posx)+1] == 4){
						if(matDisplay[voiture->posy][(voiture->posx)+1] != 'R') {
							voiture->posx = (voiture->posx)+1;
							}
						}
					else if(voitMat[(voiture->posy)-1][voiture->posx] == 2){
						if(matDisplay[(voiture->posy)-1][voiture->posx] != 'R'){
							voiture->posy = (voiture->posy)-1;
							}
						}
					}
				}
			}
		if(voiture->etat == 0){
			pietons = pietPrem;
			while(pietons != NULL){
				if(pietons->posy == voiture->posy && pietons->posx == voiture->posx){
					if(voiture->posy == 30) {voiture->posy = voiture->posy+1; }
					if(voiture->posy == 28 && voiture->posy-1 != 'R') {voiture->posy = voiture->posy-1; }
					if(voiture->posy == 21) {voiture->posy = voiture->posy+1; }			
					pietons->posy = 43;
					pietons->posx = 144;
					RemovePiet2(pietons, &pietPrem);
					voiture->etat = 1;
					}
				pietons = pietons->NXT;
				}
			if(matDisplayVoit[voiture->posy+1][voiture->posx] == 'Y'){
				RemoveNode2(voiture, &voitPrem);
				}
			if(matDisplayVoit[voiture->posy][voiture->posx+2] == 'Y'){
				RemoveNode2(voiture, &voitPrem);
				}
			}
		voiture = voiture->NXT;
		}
	pietons = pietPrem;
	while(pietons != NULL){


		if(pietMat[pietons->posy][pietons->posx] == 3 && pietons->posx == pietons->spawnx && pietons->posy+2 == pietons->spawny){
			pietons->posx = pietons->spawnx;
			pietons->posy = pietons->spawny;
			}
		else if(pietMat[pietons->posy][pietons->posx] == 4 && pietons->posx == pietons->spawnx && pietons->posy+2 == pietons->spawny){
			pietons->posx = pietons->spawnx;
			pietons->posy = pietons->spawny;
			}

		else if(pietMat[pietons->posy][pietons->posx] == 1){
			if(matDisplay[pietons->posy+1][pietons->posx] != '9'){
				pietons->posy = pietons->posy+1;
		 		}
			}
		else if(pietMat[pietons->posy][pietons->posx] == 2){
			if(matDisplay[pietons->posy-1][pietons->posx] != '9'){
				pietons->posy = pietons->posy-1;
		 		}
			}
		else if(pietMat[pietons->posy][pietons->posx] == 3){
			if(matDisplay[pietons->posy][pietons->posx-1] != '9'){
				pietons->posx = pietons->posx-1;
		 		}
			}

		else if(pietMat[pietons->posy][pietons->posx] == 4){
			if(matDisplay[pietons->posy][pietons->posx+1] != '9'){
				pietons->posx = pietons->posx+1;
		 		}
			}
		else if(pietMat[pietons->posy][pietons->posx] == 7){
			if(matDisplay[pietons->posy][pietons->posx-2] != '9'){
				pietons->posx = pietons->posx-2;
		 		}
		 	}
		else if(pietMat[pietons->posy][pietons->posx] == 8){
			aleaMarket = rand()%2;
			if(aleaMarket == 0 && matDisplay[pietons->posy][pietons->posx-1] != '9'){
				pietons->posx = pietons->posx-1;
		 		}
		 	else if(aleaMarket == 1){
		 		pietons->posy = pietons->posy-1;
		 		}
		 	}

		else if(pietMat[pietons->posy][pietons->posx] == 9){
			aleaMarket = rand()%2;
			if(aleaMarket == 0 && matDisplay[pietons->posy][pietons->posx+1] != '9'){
				pietons->posx = pietons->posx+1;
		 		}
		 	else if(aleaMarket == 1){
		 		pietons->posy = pietons->posy+1;
		 		}
		 	}

		else if(pietMat[pietons->posy][pietons->posx] == 5){
			if(pietons->spawnx < 127){
				if(matDisplay[pietons->posy][pietons->posx-1] != '9'){
					pietons->posx = pietons->posx-1;
			 		}
			 	}
			else{
				if(matDisplay[pietons->posy][pietons->posx+1] != '9'){
					pietons->posx = pietons->posx+1;
			 		}
			 	}
			}
		else if(pietMat[pietons->posy][pietons->posx] == 6){
			RemovePiet2(pietons, &pietPrem);
		 	}
		 pietons = pietons->NXT;
		}
	
	}

void gameLoop2(){

	//Initialisation
	int i;
	int theTime = 0;
	int timeBoucle = 0;
	int game = 1;
	char ** matDisplay;
	char ** matDisplayVoit;
	char ** matDisplayBase;
	int ** voitMat;
	int ** pietMat;
	int * dirPos;
	int theMadCar = 1;
	int theMadCar2 = 1;
	int thePompier = 0;
	int thePompier2 = 0;
	int accident = 0;
	int crazy = 1;
	matDisplay = malloc(50 * sizeof(*matDisplay));
	matDisplayVoit = malloc(50 * sizeof(*matDisplayVoit));
	matDisplayBase = malloc(50 * sizeof(*matDisplayBase));
	voitMat = malloc(50 * sizeof(*voitMat));
	pietMat = malloc(50 * sizeof(*pietMat));
	for( i = 0 ; i < 50 ; i++) {
		matDisplay[i] = malloc(149*sizeof(*(matDisplay[i])));
		matDisplayVoit[i] = malloc(149*sizeof(*(matDisplayVoit[i])));
		matDisplayBase[i] = malloc(149*sizeof(*(matDisplayBase[i])));
		voitMat[i] = malloc(149*sizeof(*(voitMat[i])));
		pietMat[i] = malloc(149*sizeof(*(pietMat[i])));
		}
	dirPos = malloc(4 * sizeof(*dirPos));

	getDisplay2(matDisplayBase);
	display2(matDisplayBase);
	getVoitMat2(voitMat);
	getPietMat2(pietMat);
	//Fin initialisation

	usleep(80000);
	system("clear");
	Liste2 *maListe = initialisation2();
	ListePiet2 *maListePiet = initPiet2();

	nextPos2(matDisplay, voitMat, pietMat, maListe, maListePiet, theTime, matDisplayVoit);
	copy2(matDisplay, matDisplayBase);
	dispPietOnMat2(matDisplay, maListePiet);
	dispVoitOnMat2(matDisplay, maListe);	
	copy2(matDisplayVoit, matDisplay);

	display2(matDisplay);

	while(game){

		usleep(80000);
		system("clear");
		theTime++;
		if(theTime >= 60) { 
			theTime = 0; 
			timeBoucle++;
			if(timeBoucle == 4){
				timeBoucle = 0;
				}
			}
		setDirPos2(dirPos);
		if(matDisplay[20][53] == 'R' && thePompier == 0){
			system("play -q 'La-sirène-des-pompier-par-SDIS-59-mp3cut.net.mp3'&");
			system("play -q 'car-crashing-sound-effect.mp3'&");
			thePompier = 1;
			}
		if(matDisplay[20][53] == 'R'){
			accident = 1;
		}else{accident = 0;}

		if(matDisplay[44][49] == 'R' && thePompier2 == 0){
			system("play -q 'La-sirène-des-pompier-par-SDIS-59-mp3cut.net.mp3'&");
			system("play -q 'car-crashing-sound-effect.mp3'&");
			thePompier2 = 1;
		}
		if(matDisplayVoit[2][41] == 'Y'){
			matDisplay[20][53] = 'H';
			thePompier = 0;
			theMadCar = 1;
		}
		if(matDisplayVoit[48][144] == 'Y'){
			matDisplay[44][49] = 'V';
			thePompier2 = 0;
			theMadCar2 = 1;
		}

		if(crazy == 1){
			insertion2(maListe,dirPos, 3, 0);
			crazy = 0;		
		}
		if(theMadCar == 1){
			insertion2(maListe, dirPos, 1, 0);
			theMadCar = 0;
		}
		if(theMadCar2 == 1){
			insertion2(maListe, dirPos, 2, 0);
			theMadCar2 = 0;
		}
		if(thePompier == 1){
			insertion2(maListe, dirPos, 0, 1);
			thePompier = 2;
		}
		if(thePompier2 == 1){
			insertion2(maListe, dirPos, 0, 2);
			thePompier2 = 2;
		}
		else{
			insertion2(maListe, dirPos, 0, 0);
		}

		nextPos2(matDisplay, voitMat, pietMat, maListe, maListePiet, theTime, matDisplayVoit);
		copy2(matDisplay, matDisplayBase);
		setObjectTime2(matDisplay,theTime);
		if(accident == 1){
			printAccident(matDisplay);
			}
		printTram2(matDisplay, theTime, timeBoucle);
		dispPietOnMat2(matDisplay, maListePiet);	
		dispVoitOnMat2(matDisplay, maListe);	
		copy2(matDisplayVoit, matDisplay);
		dispVoitOnMatVoit2(matDisplayVoit, maListe);
		display2(matDisplayVoit);

		}
	}


/*int main(){
	srand (time(NULL));
	gameLoop2();
	return 0;
	}*/
