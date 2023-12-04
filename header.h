#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <windows.h> 
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

//le répertoire de travail actuel.
#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir(buffer, drive, length) getcwd(buffer, length)
#else
#include <unistd.h>
#define GetCurrentDir getdcwd
#endif

#define LINE 6
#define COLONNE 7
#define PIONS 21
#define VIDE 0

enum{
    zero,
    vert,
    rouge
};

typedef struct Partie {
    int matrice[LINE][COLONNE];
    char name[50];
    int tour;
    int joueurCourant;
    int win_vert;
    int win_rouge;
}Partie;

void init(int matrice[LINE][COLONNE]);
void print(Partie partie);
bool insert(Partie *partie,int colone,int color);
void run(int matrice[LINE][COLONNE],char *folderName);
void jeux(Partie jeu,int matrice[LINE][COLONNE]);
int loadpartie(const char *folderPath, const char *gameName, Partie *partie,int matrice[LINE][COLONNE]);
void savepartie(char *folderPath, const Partie *partie,int matrice[LINE][COLONNE]);
void create(char *folderName);
void print_generique(char bravo_message[],int index);