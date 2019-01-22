#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>


typedef struct Voiture Voiture;
struct Voiture;
typedef struct Liste Liste;
struct Liste;
typedef struct Pietons Pietons;
struct Pietons;
typedef struct ListePiet ListePiet;
struct ListePiet;
Liste *initialisation();
ListePiet *initPiet();
void insertion(Liste *liste, int *dirPos);
void insertPiet(ListePiet *liste, int posx, int posy, int direction, int spawnx, int spawny);
void RemoveNode(Voiture * node, Voiture ** premier);
void RemovePiet(Pietons * node, Pietons ** premier);
void clearScreen();
void setDirPos(int *dirPos);
void dispVoitOnMat(char ** matDisplay, Liste * liste);
void dispVoitOnMatVoit(char ** matDisplay, Liste * liste);
void dispPietOnMat(char ** matDisplay, ListePiet * liste);
void getDisplay(char ** matDisplayBase);
void getVoitMat(int ** voitMat);
void getPietMat(int ** pietMat);
void printMatTest(int ** voitMat);
void copy(char ** mat1, char ** mat2);
void display(char ** matDisplay);
void printTram(char ** matDisplay, int time, int timeBoucle);
void setObjectTime(char ** matDisplay, int theTime);
void nextPos(char ** matDisplay, int ** voitMat, int ** pietMat, Liste * liste, ListePiet * listePiet, int theTime);
void gameLoop();
