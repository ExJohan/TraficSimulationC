#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>




typedef struct Voiture2 Voiture2;
struct Voiture2;
typedef struct Liste2 Liste2;
struct Liste2;
typedef struct Pietons2 Pietons2;
struct Pietons2;
typedef struct ListePiet2 ListePiet2;
struct ListePiet2;
Liste2 *initialisation2();
ListePiet2 *initPiet2();
void insertion2(Liste2 *Liste2, int *dirPos);
void insertPiet2(ListePiet2 *liste, int posx, int posy, int direction, int spawnx, int spawny);
void RemoveNode2(Voiture2 * node, Voiture2 ** premier);
void RemovePiet2(Pietons2 * node, Pietons2 ** premier);
void clearScreen2();
void setDirPos2(int *dirPos);
void printAccident2(char ** matDisplay);
void dispVoitOnMat2(char ** matDisplay, Liste2 * liste);
void dispVoitOnMatVoit2(char ** matDisplay, Liste2 * liste);
void dispPietOnMat2(char ** matDisplay, ListePiet2 * liste);
void getDisplay2(char ** matDisplayBase);
void getVoitMat2(int ** voitMat);
void getPietMat2(int ** pietMat);
void printMatTest2(int ** voitMat);
void copy2(char ** mat1, char ** mat2);
void display2(char ** matDisplay);
void printTram2(char ** matDisplay, int time, int timeBoucle);
void setObjectTime2(char ** matDisplay, int theTime);
void nextPos2(char ** matDisplay, int ** voitMat, int ** pietMat, Liste2 * liste, ListePiet2 * listePiet, int theTime);
void gameLoop2();
