#include "header.h"

int main(){
    
    char *folderName = "puissanc_doc";
    create(folderName);

    
    
    int matrice[LINE][COLONNE]={VIDE};

    //lance le jeu
    system("cls");//update
    print_generique("Bienvenue dans le jeu de Puissance 4 developpe dans le cadre du projet tutore Ing1 Info!\n",0);
    Sleep(1500);
    system("cls");

    run(matrice,folderName);

    
    
    return 0 ;
}
