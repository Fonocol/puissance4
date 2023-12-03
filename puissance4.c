#include "header.h"


void init(int matrice[LINE][COLONNE]){
    for (int i = 0; i < LINE; i++){
        for (int j = 0; j < COLONNE; j++){
            matrice[i][j] = VIDE;
        } 
    }
}

void print(Partie partie){

    for (int i = -1; i < LINE; i++) {
        for (int j = -1; j < COLONNE; j++) {
            if (i==-1){
                if (j==-1)
                {
                    printf(" ",j);
                }else{
                    printf(" %d ",j);
                }   
            }
            else if (j==-1){
                printf("%d",i);
            }
            else
            {
                if ((i + j) % 2 == 0) {
                    if (partie.matrice[i][j]==vert){
                        printf("\033[47m\033[32m o ");
                    }else if (partie.matrice[i][j]==rouge){
                        printf("\033[47m\033[31m o ");
                    }else if (partie.matrice[i][j]==VIDE){
                        printf("\033[47m   ");
                    }   
                } else {
                    if (partie.matrice[i][j]==vert){
                        printf("\033[40m\033[32m o ");
                    }else if (partie.matrice[i][j]==rouge){
                        printf("\033[40m\033[31m o ");
                    }else if (partie.matrice[i][j]==VIDE){
                        printf("\033[40m   ");
                    }   
                }
            }
     

        }
        printf("\033[0m\n"); // Réinitialiser la couleur après chaque ligne
    }
}


bool insert(Partie *partie,int colone,int color){

    if (partie->matrice[VIDE][colone] != VIDE || colone< 0 || colone >= COLONNE ){
        return false;
    }
    else{
        for (int line = 1; line <= line; line++){
            if (partie->matrice[LINE - line][colone] == VIDE){
                partie->matrice[LINE - line][colone] = color;
                return true;
            }
        }
    } 
}

bool isfool(Partie game){
    for (int i = 0; i < COLONNE; i++){
        if (game.matrice[zero][i] == VIDE){
            return false;
        } 
    }
    return true; 
}

void print_generique(char bravo_message[],int index) {
    
    int message_length = strlen(bravo_message);
    
    for (int i = 0; i < message_length; i++) {
        printf("%c", bravo_message[i]);
        Sleep(30);
    }
    if (index==0)
    {
        Sleep(120);
        printf("loading ");
        for (int i = 0; i < 3; i++)
        {
            printf(".");
            Sleep(800);
        }
        printf("\n");
    }  
}

bool verifierAlignement(int matrice[LINE][COLONNE], int joueur) {
    // Vérification des lignes
    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j <= COLONNE - 4; j++) {
            if (j + 3 < COLONNE && matrice[i][j] == joueur && matrice[i][j + 1] == joueur &&
                matrice[i][j + 2] == joueur && matrice[i][j + 3] == joueur) {
                return true;
            }
        }
    }

    // Vérification des colonnes
    for (int i = 0; i <= LINE - 4; i++) {
        for (int j = 0; j < COLONNE; j++) {
            if (i + 3 < LINE && matrice[i][j] == joueur && matrice[i + 1][j] == joueur &&
                matrice[i + 2][j] == joueur && matrice[i + 3][j] == joueur) {
                return true;
            }
        }
    }

    // Vérification des diagonales descendantes
    for (int i = 0; i <= LINE - 4; i++) {
        for (int j = 0; j <= COLONNE - 4; j++) {
            if (i + 3 < LINE && j + 3 < COLONNE &&
                matrice[i][j] == joueur && matrice[i + 1][j + 1] == joueur &&
                matrice[i + 2][j + 2] == joueur && matrice[i + 3][j + 3] == joueur) {
                return true;
            }
        }
    }

    // Vérification des diagonales ascendantes
    for (int i = 3; i < LINE; i++) {
        for (int j = 0; j <= COLONNE - 4; j++) {
            if (i - 3 >= 0 && j + 3 < COLONNE &&
                matrice[i][j] == joueur && matrice[i - 1][j + 1] == joueur &&
                matrice[i - 2][j + 2] == joueur && matrice[i - 3][j + 3] == joueur) {
                return true;
            }
        }
    }

    return false;
}

bool winer(Partie *partie, int color) {
    return verifierAlignement(partie->matrice, color);
}



void create(char *folderName) {
    // Nom du dossier à créer ou vérifier
    char currentPath[1024];
    char folderPath[1024]; // Utilisez un tableau plutôt qu'un pointeur

    // Obtenir le chemin actuel du répertoire de travail
    if (_getcwd(currentPath, sizeof(currentPath)) != NULL) {
        // Concaténer le chemin actuel avec le nom du dossier
        snprintf(folderPath, sizeof(folderPath), "%s\\%s", currentPath, folderName);

        // Vérifier si le dossier existe
        if (_access(folderPath, 0) == -1) {
            // Le dossier n'existe pas, donc on le crée
            if (_mkdir(folderPath) == 0) {
                printf("Dossier créé avec succès : %s\n", folderPath);
            } else {
                printf("Échec de la création du dossier : %s\n", folderPath);
            }
        } else {
            printf("Le dossier existe déjà : %s\n", folderPath);
        }
    } else {
        printf("Erreur lors de l'obtention du répertoire de travail.\n");
    }
}


void savepartie(char *folderPath,const Partie *partie,int matrice[LINE][COLONNE]) {
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s/%s.txt", folderPath, partie->name);
    FILE *file = fopen(filePath, "w");
    
    if (file) {
        fprintf(file, "Nom : %s\n", partie->name);
        fprintf(file, "tour : %d\n", partie->tour);
        fprintf(file, "joueurCourant : %d\n", partie->joueurCourant);
        fprintf(file, "win_vert : %d\n", partie->win_vert);
        fprintf(file, "win_rouge : %d\n", partie->win_rouge);
        for (int i = 0; i < LINE; i++) {;
            for (int j = 0; j < COLONNE; j++) {
                fprintf(file, "[%d][%d] : %d\n",i,j, partie->matrice[i][j]);
            }
        }
        fclose(file);
    } else {
        printf("Erreur lors de l'ouverture du fichier pour enregistrement.\n");
    }
}


int loadpartie(const char *folderPath, const char *gameName, Partie *partie,int matrice[LINE][COLONNE]) {
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s/%s.txt", folderPath, gameName);
    FILE *file = fopen(filePath, "r");
    
    if (file) {
        fscanf(file, "Nom : %s\n", partie->name);
        fscanf(file, "tour : %d\n", &partie->tour);
        fscanf(file, "joueurCourant : %d\n", &partie->joueurCourant);
        fscanf(file, "win_vert : %d\n", &partie->win_vert);
        fscanf(file, "win_rouge : %d\n", &partie->win_rouge);
        for (int i = 0; i < LINE; i++) {;
            for (int j = 0; j < COLONNE; j++) {
                fscanf(file, "[%d][%d] : %d\n",&i,&j, &partie->matrice[i][j]);
            }
        }
        fclose(file);
        return 1;  // La lecture a réussi
    } else {
        printf("Erreur lors de l'ouverture du fichier pour chargement.\n");
        return 0;  // La lecture a échoué
    }
}


void jeux(Partie jeu,int matrice[LINE][COLONNE]){


    int col;
    while (!isfool(jeu) && !winer(&jeu,jeu.joueurCourant))
    {
        if (jeu.joueurCourant == rouge){
            jeu.joueurCourant = vert;
        }else if (jeu.joueurCourant == vert){
            jeu.joueurCourant = rouge;
        } 
        do
        {
            system("cls");//update
            print(jeu);
            print_generique("c'est le tour du joueur",1);
            printf("%d\n",jeu.joueurCourant);
            print_generique("enter la colone :",1);
            scanf("%d",&col);
        } while ( !insert(&jeu,col,jeu.joueurCourant ));
        savepartie("puissanc_4", &jeu,matrice);  
    }

    if (winer(&jeu,jeu.joueurCourant)){
        print_generique("Bravo la partie a ete gagner par le joueur ",1);
        printf("%d",jeu.joueurCourant);
        if (jeu.joueurCourant == rouge){
            jeu.win_rouge++;
        }else if (jeu.joueurCourant == vert){
            jeu.win_vert++;
        } 
    }
    else if (isfool(jeu)){
        print_generique("match null personne n'a gagner la partie :) ",1);
    }
    
    Sleep(2000);
    system("cls");
    init(matrice);
    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLONNE; j++) {
            jeu.matrice[i][j] = matrice[i][j];
        }
    }
    jeu.tour=jeu.tour+1;
    savepartie("puissanc_4", &jeu,matrice);
    jeux(jeu,matrice);

}





void run(int matrice[LINE][COLONNE],char *folderName) {
    int partie;
    //printf("Pour jouer une exhibition, entrez 0. Pour jouer une partie, entrez 1 : ");
    print_generique("0 pour continuer une partie, 1 pour créer une nouvelle partie : ",1);
    scanf("%d", &partie);

    if (partie == 0) {

        char gameName[50];
        print_generique("Entrez le nom de la partie que vous souhaitez continuer : ",1);
        scanf("%s", gameName);
        
        Partie game;
        if (loadpartie("puissanc_4", gameName, &game,matrice)) {
            printf("Chargement reussi : Nom : %s", game.name);
            //printMatrix(gameInfo.matrice);
            jeux(game,matrice);

            // Ajoutez le code pour continuer la partie ici
        } else {
            printf("Chargement de la partie échoué.\n");
        }
    } else {
        // Code pour créer une nouvelle partie
        Partie game;
        //printf("Entrez votre nom : ");
        print_generique("Entrez le nom de votre partie : ",1);
        scanf("%s", game.name);
        game.tour =1;
        game.joueurCourant = rouge;//le premier est vert
        game.win_vert = zero;
        game.win_rouge =zero;
        init(matrice);
        for (int i = 0; i < LINE; i++) {
            for (int j = 0; j < COLONNE; j++) {
                game.matrice[i][j] = matrice[i][j];
            }
        }
        
        
        savepartie("puissanc_4", &game,matrice);
        printf("Nouvelle partie creee : Nom : %s\n", game.name);
        jeux(game,matrice);
    }
}
