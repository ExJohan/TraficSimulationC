#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>


typedef struct Voiture Voiture;
struct Voiture
{
	char direction;	/*N => Nord, S => Sud, E => EST, O => OUEST*/
	int posx;	/*Position courante x de la voiture*/
	int posy;	/*Position courante y de la voiture*/
	int ravitaillement; /*1=>ravitaillement 2=>carburant et 0=>sinon*/
	int parking;
	int etat;        /*État du véhicule => actif ou inactif*/
	char color;
	
	struct Voiture * NXT; /*Pointeur vers une prochaine voiture,necessaire pour la liste chainée*/
	};

typedef struct Liste Liste;
struct Liste {
	Voiture  * premier;
	};

typedef struct Pietons Pietons;
struct Pietons
{
	int direction;	//aller =  0 ou retour = 1
	int posx;	/*Position courante x du pieton*/
	int posy;	/*Position courante y du pieton*/	
	int spawnx; 
	int spawny;
	struct Pietons * NXT; /*Pointeur vers une prochaine voiture,necessaire pour la liste chainée*/
	};

typedef struct ListePiet ListePiet;
struct ListePiet {
	Pietons  * premier;
	};

Liste *initialisation(){

	Liste *liste = malloc(sizeof(*liste));
	Voiture * maVoiture = malloc(sizeof(*maVoiture));


	if (liste == NULL || maVoiture == NULL){
		exit(EXIT_FAILURE);
		}

	maVoiture -> direction = 'S';
	maVoiture -> posx = 10;
	maVoiture -> posy = 0;
	maVoiture -> ravitaillement = 0;
	maVoiture -> parking = 0;
	maVoiture -> etat = 1;
	maVoiture->NXT = NULL;
	maVoiture->color = 'R';
	liste->premier = maVoiture;
	return liste;

	}

ListePiet *initPiet(){

	ListePiet *listePiet = malloc(sizeof(*listePiet));
	Pietons * monPiet = malloc(sizeof(*monPiet));


	if (listePiet == NULL || monPiet == NULL){
		exit(EXIT_FAILURE);
		}

	monPiet -> direction = 0;
	monPiet -> posx = 97;
	monPiet -> posy = 33;
	monPiet->NXT = NULL;
	listePiet->premier = monPiet;
	return listePiet;

	}

void insertion(Liste *liste, int *dirPos){

	int aleaVoit = rand()%2; //Si fait spawn une voiture (actuellement une fois sur deux)
	int aleaColor = rand()%5;

	if (aleaVoit == 0){
		/* Création du nouvel élément */
		Voiture *nouveau = malloc(sizeof(*nouveau));
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

void insertPiet(ListePiet *liste, int posx, int posy, int direction, int spawnx, int spawny){

		/* Création du nouvel élément */
	Pietons *nouveau = malloc(sizeof(*nouveau));
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

void RemoveNode(Voiture * node, Voiture ** premier) {

	Voiture * current = (*premier)->NXT;
	Voiture * previous = *premier;
	while (current != NULL && previous != NULL) {
		if (current == node) {
			Voiture * temp = current;
			previous->NXT = current->NXT;
			free(temp);
			return;
			}
		previous = current;
		current = current->NXT;
		}
	return;
	}

void RemovePiet(Pietons * node, Pietons ** premier) {

	Pietons * current = (*premier)->NXT;
	Pietons * previous = *premier;
	while (current != NULL && previous != NULL) {
		if (current == node) {
			Pietons * temp = current;
			previous->NXT = current->NXT;
			free(temp);
			return;
			}
		previous = current;
		current = current->NXT;
		}
	return;
	}


void clearScreen(){
	const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
	write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
	}

void setDirPos(int *dirPos){
	
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

void dispVoitOnMat(char ** matDisplay, Liste * liste){
	if (liste == NULL){
        	exit(EXIT_FAILURE);
		}
	Voiture *actuel = liste->premier;
	while(actuel != NULL){
		matDisplay[actuel->posy][actuel->posx] = 'R';
		actuel = actuel->NXT;
		}
	}

void dispVoitOnMatVoit(char ** matDisplay, Liste * liste){
	if (liste == NULL){
        	exit(EXIT_FAILURE);
		}
	Voiture *actuel = liste->premier;
	while(actuel != NULL){
		matDisplay[actuel->posy][actuel->posx] = actuel->color;
		actuel = actuel->NXT;
		}
	}

void dispPietOnMat(char ** matDisplay, ListePiet * liste){
	if (liste == NULL){
        	exit(EXIT_FAILURE);
		}
	Pietons *actuel = liste->premier;
	while(actuel != NULL){
		matDisplay[actuel->posy][actuel->posx] = '9';
		actuel = actuel->NXT;
		}
	}


void getDisplay(char ** matDisplayBase){

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

void getVoitMat(int ** voitMat){
	int i,j;
	printf("\n\n");
	FILE * fichMat = NULL;
	fichMat = fopen("Matrice.txt","r+");
	for(i = 0; i<50 ; i++){
		for( j = 0; j<148 ; j++){
			fscanf(fichMat, "%d", &voitMat[i][j]);
			}
		}
	fclose(fichMat);
	}

void getPietMat(int ** pietMat){
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

void printMatTest(int ** voitMat){
	int i,j;
	printf("\n");
	for( i = 0; i<50 ; i++){
		for(j = 0; j<149 ; j++){
			printf("%d",voitMat[i][j]);
			}
		printf("\n");
		}
	}

void copy(char ** mat1, char ** mat2){

	int i;
	int j;
	for(i = 0; i < 50 ; i++){
		for(j = 0 ; j < 149; j++){
			mat1[i][j] = mat2[i][j];
			}
		}
	}


void display(char ** matDisplay){
	
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
					printf("\033[32m🚍");
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

void printTram(char ** matDisplay, int time, int timeBoucle){
	
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





void setObjectTime(char ** matDisplay, int theTime){
	
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

void nextPos(char ** matDisplay, int ** voitMat, int ** pietMat, Liste * liste, ListePiet * listePiet, int theTime){
		
	if (liste == NULL){
		exit(EXIT_FAILURE);
		}

	int aleaMarket;

	Voiture * voiture = liste->premier;
	Voiture * voitPrem = liste->premier;

	Pietons * pietons = listePiet->premier;
	Pietons * pietPrem = listePiet->premier;
	while(voiture != NULL){
//if pietons a coté de voiture etat se remet a 1
		if(voiture->etat == 1){

			if(voiture->direction == 'S'){

				if(voiture->posy <= 45 && voitMat[(voiture->posy)+2][(voiture->posx)-1] == 6 && theTime <= 30){
				}
				else if(voitMat[voiture->posy][voiture->posx] == 1){
					if(matDisplay[(voiture->posy)+1][voiture->posx] != 'R'){
						if(voitMat[voiture->posy+1][voiture->posx] == 5 && voitMat[voiture->posy+1][(voiture->posx)-1] == 4 && matDisplay[(voiture->posy)+1][(voiture->posx)-1] == 'R'){ }
						else if(voitMat[voiture->posy+1][voiture->posx] == 5 && voitMat[voiture->posy+1][(voiture->posx)-1] == 4 && matDisplay[(voiture->posy)+1][(voiture->posx)-2] == 'R'){ }
						else if(voitMat[voiture->posy+1][voiture->posx] == 5 && voitMat[voiture->posy+1][(voiture->posx)-1] == 4 && matDisplay[(voiture->posy)+1][(voiture->posx)-3] == 'R'){ }
						else if(voitMat[voiture->posy+1][voiture->posx] == 5 && voitMat[voiture->posy+1][(voiture->posx)-1] == 4 && matDisplay[(voiture->posy)+1][(voiture->posx)-4] == 'R'){ }
						else if(matDisplay[voiture->posy+1][voiture->posx] == 'x' || matDisplay[voiture->posy+1][voiture->posx] == '+' || matDisplay[voiture->posy+1][voiture->posx] == '('){ }
						else if(matDisplay[voiture->posy][voiture->posx+3] == '&') {
							voiture->etat = 0;
							insertPiet(listePiet, voiture->posx-1, voiture->posy, 0, 0, 0);
							}
						else if(matDisplay[voiture->posy][voiture->posx-3] == '&') {
							voiture->etat = 0;
							insertPiet(listePiet, voiture->posx+1, voiture->posy, 0, 0, 0);
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
					RemoveNode(voiture, &voitPrem);	
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
						RemoveNode(voiture, &voitPrem);	
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
						if(matDisplay[voiture->posy][(voiture->posx)-1] != 'R' && matDisplay[voiture->posy][(voiture->posx)-2] != 'R' && matDisplay[voiture->posy][(voiture->posx)-1] != '9'){
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
						insertPiet(listePiet, voiture->posx+1, voiture->posy, 0, voiture->posx, voiture->posy);
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
					RemoveNode(voiture, &voitPrem);	
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
					RemoveNode(voiture, &voitPrem);	
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
					RemovePiet(pietons, &pietPrem);
					voiture->etat = 1;
					}
				pietons = pietons->NXT;
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
			RemovePiet(pietons, &pietPrem);
		 	}
		 pietons = pietons->NXT;
		}
	
	}

void gameLoop(){

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

	getDisplay(matDisplayBase);
	display(matDisplayBase);
	getVoitMat(voitMat);
	getPietMat(pietMat);
	//Fin initialisation

	usleep(80000);
	system("clear");
	Liste *maListe = initialisation();
	ListePiet *maListePiet = initPiet();

	nextPos(matDisplay, voitMat, pietMat, maListe, maListePiet, theTime);
	copy(matDisplay, matDisplayBase);
	dispPietOnMat(matDisplay, maListePiet);
	dispVoitOnMat(matDisplay, maListe);	
	copy(matDisplayVoit, matDisplay);

	display(matDisplay);

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
		setDirPos(dirPos);
		insertion(maListe, dirPos);
		nextPos(matDisplay, voitMat, pietMat, maListe, maListePiet, theTime);
		copy(matDisplay, matDisplayBase);
		setObjectTime(matDisplay,theTime);
		printTram(matDisplay, theTime, timeBoucle);
		dispPietOnMat(matDisplay, maListePiet);	
		dispVoitOnMat(matDisplay, maListe);	
		copy(matDisplayVoit, matDisplay);
		dispVoitOnMatVoit(matDisplayVoit, maListe);
		display(matDisplayVoit);

		}
	}


/*int main(){
	srand (time(NULL));
	gameLoop();
	return 0;
	}*/
