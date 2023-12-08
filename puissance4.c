#include "header.h"


void init(int matrice[LINE][COLONNE]){
    for (int i = 0; i < LINE; i++){
        for (int j = 0; j < COLONNE; j++){
            matrice[i][j] = VIDE;
        } 
    }
    matrice[0][0] = 2;
    matrice[0][1] = 3;
    matrice[0][2] = 4;
    matrice[0][3] = 5;
    matrice[0][4] = 4;
    matrice[0][5] = 3;
    matrice[0][6] = 2;


    matrice[1][0] = 3;
    matrice[1][1] = 4;
    matrice[1][2] = 5;
    matrice[1][3] = 6;
    matrice[1][4] = 5;
    matrice[1][5] = 4;
    matrice[1][6] = 3;


    matrice[2][0] = 4;
    matrice[2][1] = 5;
    matrice[2][2] = 6;
    matrice[2][3] = 7;
    matrice[2][4] = 6;
    matrice[2][5] = 5;
    matrice[2][6] = 4;

    matrice[3][0] = 4;
    matrice[3][1] = 5;
    matrice[3][2] = 6;
    matrice[3][3] = 7;
    matrice[3][4] = 6;
    matrice[3][5] = 5;
    matrice[3][6] = 4;

    matrice[4][0] = 3;
    matrice[4][1] = 4;
    matrice[4][2] = 5;
    matrice[4][3] = 6;
    matrice[4][4] = 5;
    matrice[4][5] = 4;
    matrice[4][6] = 3;
    //les poids
    matrice[5][0] = 2;
    matrice[5][1] = 3;
    matrice[5][2] = 4;
    matrice[5][3] = 5;
    matrice[5][4] = 4;
    matrice[5][5] = 3;
    matrice[5][6] = 2;

}

void print(Partie partie){
    char nomcurrent[3][5] = {"Vert ","","Rouge"};
    printf("\033[47m\033[31m      PUISSANCE 4      \033[0m\n");

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
                    }else{
                        printf("\033[47m %d ",partie.matrice[i][j]);
                    }   
                } else {
                    if (partie.matrice[i][j]==vert){
                        printf("\033[40m\033[32m o ");
                    }else if (partie.matrice[i][j]==rouge){
                        printf("\033[40m\033[31m o ");
                    }else{
                        printf("\033[40m %d ",partie.matrice[i][j]);
                    }   
                }
            }
     

        }
        printf("\033[0m\n"); // Réinitialiser la couleur après chaque ligne
    }
    printf("\033[47m\033[31m      PUISSANCE 4      \033[0m\n");
    printf("Active| Vert   | Rouge|\n");
    printf("______|________|______|\n");
    printf("%s | %d      | %d    |\n",nomcurrent[partie.joueurCourant+1],partie.win_vert,partie.win_rouge);
    printf("______|________|______|\n");
    printf("Nom :   %s\n",partie.name);
}

int machine_cherche(Partie partie){
    int max = partie.matrice[0][0];
    int col=0;
    for (int i = 0; i < LINE; i++){
        for (int j = 0; j < COLONNE; j++){
            if (partie.matrice[i][j]>max)
            {
                max = partie.matrice[i][j];
                col = j;
            }
            
        }
        
    }
    return col;
    
}

bool insert(Partie *partie,int colone,int color){

    if (partie->matrice[VIDE][colone] == vert || partie->matrice[VIDE][colone] == rouge || colone< 0 || colone >= COLONNE ){
        return false;
    }
    else{
        for (int line = 1; line <= LINE; line++){
            if ((partie->matrice[LINE - line][colone] != vert) && (partie->matrice[LINE - line][colone] != rouge) ){
                partie->matrice[LINE - line][colone] = color;
                for (int i = 0; i < 3; i++){
                    for (int j = 0; j < 3; j++){
                        if (i !=(LINE - line) &&  j!=colone && (((LINE - line)-1)+i)<LINE && (((LINE - line)-1)+i)>=0 && ((colone-1)+j)<COLONNE &&((colone-1)+j)>=0){
                            if ((partie->matrice[((LINE - line)-1)+i][(colone-1)+j] != vert) && (partie->matrice[((LINE - line)-1)+i][(colone-1)+j] != rouge))
                            {
                                if(partie->joueurCourant ==vert ){
                                    partie->matrice[((LINE - line)-1)+i][(colone-1)+j] =partie->matrice[((LINE - line)-1)+i][(colone-1)+j]+upper;
                                }else
                                {
                                    partie->matrice[((LINE - line)-1)+i][(colone-1)+j] =partie->matrice[((LINE - line)-1)+i][(colone-1)+j]+lower;
                                }
                                
                                
                            }   
                        } 
                    }
                    
                }

                return true;
            }
        }
    } 
}

bool isfool(Partie game){
    for (int i = 0; i < COLONNE; i++){
        if (game.matrice[zero][i] != vert && game.matrice[zero][i] != rouge){
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
        printf("loading pour ");
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
        fprintf(file, "choix : %d\n", partie->choix);
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
        fscanf(file, "choix : %d\n", &partie->choix);
        for (int i = 0; i < LINE; i++) {;
            for (int j = 0; j < COLONNE; j++) {
                fscanf(file, "[%d][%d] : %d\n",&i,&j, &partie->matrice[i][j]);
            }
        }
        for (int i = 0; i < LINE; i++) {;
            for (int j = 0; j < COLONNE; j++) {
                matrice[i][j] = partie->matrice[i][j];
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
        do
        {
            system("cls");//update
            print(jeu);
            //print_generique("c'est le tour du joueur",1);
            //printf("%d\n",jeu.joueurCourant);
            print_generique("colone :",1);
            if (jeu.choix == machine && jeu.joueurCourant == rouge){
                col = machine_cherche(jeu);
                Sleep(1000);
            }else
            {
                scanf("%d",&col);
            }
                
        } while ( !insert(&jeu,col,jeu.joueurCourant ));
        if (!winer(&jeu,jeu.joueurCourant)){
            if (jeu.joueurCourant == rouge){
                jeu.joueurCourant = vert;
            }else if (jeu.joueurCourant == vert){
                jeu.joueurCourant = rouge;
            } 
        }
        savepartie("puissanc_doc", &jeu,matrice);
        
    }
    system("cls");//update
    print(jeu);

    if (winer(&jeu,jeu.joueurCourant)){
        if (jeu.joueurCourant==vert){
            print_generique("Bravo la partie a ete gagner par le joueur Vert ",1);
        }else
        {
            print_generique("Bravo la partie a ete gagner par le joueur Rouge ",1);
        }
        
        //bonus++ et changement de player c'est a dire c'est au perdant de jouer le second tour
        if (jeu.joueurCourant == rouge){
            jeu.win_rouge++;
            jeu.joueurCourant = vert;
        }else if (jeu.joueurCourant == vert){
            jeu.win_vert++;
            jeu.joueurCourant = rouge;
        }
        Sleep(2000); 
    }
    else if (isfool(jeu)){
        print_generique("match null personne n'a gagner la partie :) ",1);
        Sleep(2000);
    }
    
    Sleep(2000);
    system("cls");
    print_generique("nouvelle partie en cour ",0);
    init(matrice);
    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLONNE; j++) {
            jeu.matrice[i][j] = matrice[i][j];
        }
    }
    jeu.tour=jeu.tour+1;
    savepartie("puissanc_doc", &jeu,matrice);
    jeux(jeu,matrice);   

}





void run(int matrice[LINE][COLONNE],char *folderName) {
    int partie;
    //printf("Pour jouer une exhibition, entrez 0. Pour jouer une partie, entrez 1 : ");
    print_generique("0 pour continuer une partie, 1 pour creer une nouvelle partie : ",1);
    scanf("%d", &partie);

    if (partie == 0) {

        char gameName[50];
        print_generique("Entrez le nom de la partie que vous souhaitez continuer : ",1);
        scanf("%s", gameName);
        
        Partie game;
        if (loadpartie("puissanc_doc", gameName, &game,matrice)) {
            printf("Chargement reussi : Nom : %s", game.name);
            //printMatrix(gameInfo.matrice);
            jeux(game,matrice);

            // Ajoutez le code pour continuer la partie ici
        } else {
            printf("Chargement de la partie échoué.\n");
        }
    } else {
        // Code pour créer une nouvelle partie
        int choix;
        Partie game;
        print_generique("vous voulez jouer contre la machine(1) ou un humain(0)",1);
        scanf("%d",&choix);
        if (choix == humain){
            game.choix=humain;
        }else{
            game.choix=machine;
        }
        //printf("Entrez votre nom : ");
        print_generique("Entrez le nom de votre partie : ",1);
        scanf("%s", game.name);
        game.tour =1;
        game.joueurCourant = vert;//le premier est vert
        game.win_vert = zero;
        game.win_rouge =zero;
        init(matrice);
        for (int i = 0; i < LINE; i++) {
            for (int j = 0; j < COLONNE; j++) {
                game.matrice[i][j] = matrice[i][j];
            }
        }
        
    
        savepartie("puissanc_doc", &game,matrice);
        printf("Nouvelle partie creee : Nom : %s\n", game.name);
        jeux(game,matrice);
    }
}
