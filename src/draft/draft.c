#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#if defined(__WIN32__)
#include <conio.h>
#include <windows.h>
#endif

typedef struct t_joueur {
    int id;              // Player's ID from 1 to 4
    long balance;        // Balance of the player
    char username[100];  // Username of the player
    int position;        // ID of the player's current cell
    int cellType;        // Type of the player's current cell
    int ownedField[26];  // ID of each owned fields
    bool sortiePrison;   // ID of possessed luck card
    bool loyerDivise;    // ID of possessed community card
    bool inJail;         // True if the player is in jail, false if not
    bool bankruptcy;     // True if the player is in bankruptcy, false if not
    char symbol;         // Le symbole du joueur
    int streakDouble;    // Active number of doubles
    int timeInJail;      // Times in prison
    int avatar;          // Hexadecimal code for the avatar selection
} joueur;

typedef struct t_box {
    int id;
    int x;
    int y;
    char nom[20];
} box;

typedef struct t_terrain {
    char *nom;         // Field's name
    int id;            // Field's ID from 0 to 25
    int idOnBoard;     // Field's ID from 0 to 39 (board reference)
    int defaultPrice;  // Field's initial price
    int housePrice;    // Field's house price
    int loyer;         // Loyer de base
    int loyermaison1;  // Loyer avec une maison
    int loyermaison2;  // Loyer avec 2 maisons
    int loyermaison3;  // Loyer avec 3 maisons
    int loyermaison4;  // Loyer avec 4 maisons
    int loyerhotel;    // Loyer avec un hotel
    int val_hypoth;    // Valeur hypothécaire
    int buildings;     // Amount of buildings in the field
    bool owned;        // True if owned, False if not
    bool hotel;        // True if there is a hotel
    int ownedBy;       // ID of the player who owns this field
    int x;             // X position
    int y;             // Y position
    int couleur;       // Color of the cell
    bool hypotheque;   // True si la case est hypothéquée
} terrain;

void clearScreen() {  // permet de clear la console
    system("cls");
}

void Color(int couleurDuTexte, int couleurDeFond) {  // fonction d'affichage de couleurs
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}

void gotoligcol(int lig, int col) {
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
}

void showLogo() {
    gotoligcol(0, 0);
    printf(
        "MONO            POLY  	     MONOPOLY	      MONO	  PO   	     "
        "MONOPOLY         MONOPOLYMONO           MONOPOLY         MO          MO "
        "       NO");
    printf(
        "\nPOLYMONO    MONOPOLY	    NO      MO        NOPO        NO        NO "
        "     MO        NO         PO         NO      MO        NO           NO  "
        "    MO");
    printf(
        "\nMONOPOLY    POLYMONO	   PO	     NO       PO  MO      MO       PO  "
        "      NO       PO          LY       PO        NO       PO            PO "
        "   LY");
    printf(
        "\nPOLY	MONO	POLY	  LY	      PO      LY  NO      LY      LY   "
        "       PO      LY          MO      LY          PO      LY             "
        "LY  PO");
    printf(
        "\nMONO	POLY	MONO     MO            LY     MO    PO    PO     MO    "
        "        LY     MO         NO      MO            LY     MO              "
        "MONO");
    printf(
        "\nPOLY		POLY	NO		MO    NO    LY	  NO    NO     "
        "         MO    NOPONOMOLYPO      NO              MO    NO               "
        "NO");
    printf(
        "\nMONO		MONO	 PO	       NO     PO      MO  MO     PO    "
        "        NO     PO                 PO            NO     PO               "
        "PO");
    printf(
        "\nPOLY		POLY	  LY	      PO      LY      NO  LY      LY   "
        "       PO      LY                  LY          PO      LY               "
        "LY");
    printf(
        "\nMONO		MONO	   MO	     LY       MO        POPO       MO  "
        "      LY       MO                   MO        LY       MO               "
        "MO");
    printf(
        "\nPOLY		POLY 	    NO      MO        NO        LYNO        NO "
        "     MO        NO                    NO      MO        NO               "
        "NO");
    printf(
        "\nMONO		POLY	     POLYMONO         PO          MO         "
        "POLYMONO         PO                     POLYMONO         POLYMONOPOLY   "
        "  LY");
    gotoligcol(14, 5);
}

void display() {
    clearScreen();
    showLogo();
}



int choixAvatar(int nbJoueurs, int currentPlayer) {
    bool end = false;
    int av;
    int key, c;
    int avatar[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0B, 0x0C, 0x0E, 0x0F};
    int selection = 0;
    display();
    printf("Veuillez choisir votre avatar");
    gotoligcol(17, 7);
    printf("<---     --->");
    gotoligcol(17, 13);
    printf("%c", avatar[selection]);
    while (!end) {
        gotoligcol(17, 13);
        if (kbhit()) {
            key = getch();
            switch (key) {
                case 75:
                    if (selection > 0) {
                        selection = selection - 1;
                    }
                    printf("%c", avatar[selection]);
                    break;

                case 77:
                    if (selection < 9) {
                        selection++;
                    }
                    printf("%c", avatar[selection]);
                    break;
                case 13:
                    end = true;
                    break;
                    /* Pour vérifier si l'avat est déjà pris
                    av = avatar[selection];
                    switch (currentPlayer) {
                        case 1:
                            if ((av == j2.avatar) || (av == j3.avatar) || (av == j4.avatar)) {
                                printf("Avatar deja choisi !");
                            } else {
                                end = true;
                            }
                            break;
                        case 2:
                            if ((av == j1.avatar) || (av == j3.avatar) || (av == j4.avatar)) {
                                printf("Avatar deja choisi !");
                            } else {
                                end = true;
                            }
                            break;
                        case 3:
                            if ((av == j1.avatar) || (av == j2.avatar) || (av == j4.avatar)) {
                                printf("Avatar deja choisi !");
                            } else {
                                end = true;
                            }
                            break;
                        case 4:
                            if ((av == j1.avatar) || (av == j2.avatar) || (av == j3.avatar)) {
                                printf("Avatar deja choisi !");
                            } else {
                                end = true;
                            }
                            break;
                        {*/
            }
        }
    }

    gotoligcol(18, 5);
    printf("Selection enregistree");
    //animation(20, 0, 50, 28);

    /*
    for (c = selection - 1; c < 10 - 1; c++)
        avatar[c] = avatar[c + 1];

    printf("Resultant array:\n");

    for (c = 0; c < 10 - 1; c++)
        printf("%c\n", avatar[c]);
    */

    return avatar[selection];
}

void home() {  // menu principal du jeu
    int choice = 0;

    showLogo();

    gotoligcol(14, 23);
    Color(15, 2);
    printf("1-Lancer une nouvelle partie");
    gotoligcol(14, 60);
    Color(15, 5);
    printf("2-Sauvegarder la partie");
    gotoligcol(14, 93);
    Color(15, 4);
    printf("3-Charger une ancienne partie");
    gotoligcol(16, 33);
    Color(15, 9);
    printf("4-Consulter les regles");
    gotoligcol(16, 67);
    Color(15, 11);
    printf("5-Credits");
    gotoligcol(16, 89);
    Color(15, 8);
    printf("6-Quitter la partie");

    gotoligcol(19, 0);
    Color(15, 0);
    printf("--> Que choisissez-vous de faire ? Tapez un chiffre : ");
    scanf("%d", &choice);

    while (choice < 1 || choice > 6) {
        printf("Votre saisie (%d) n'est pas valide. Veuillez entrer un chiffre a nouveau : \n", choice);
        scanf("%d", &choice);
    }
    switch (choice) {
        case 1:
            clearScreen();
            //newGame();
            break;
        case 4:
            clearScreen();
            //regles();
            break;
        case 5:
            clearScreen();
            //credits();
            break;
    }
}

joueur *creationDesJoueurs(int nombreDeJoueurs) {
    int emptyCard[10];
    int emptyField[26];

    joueur *listeJoueurs = (joueur *)malloc(4 * sizeof(joueur));

    joueur tempJ1 = {1, 1500, "NULL", 0, 0, {0}, false, false, false, false};
    joueur tempJ2 = {2, 1500, "NULL", 0, 0, {0}, false, false, false, false};
    joueur tempJ3 = {3, 1500, "NULL", 0, 0, {0}, false, false, false, false};
    joueur tempJ4 = {4, 1500, "NULL", 0, 0, {0}, false, false, false, false};

    listeJoueurs[0] = tempJ1;
    listeJoueurs[1] = tempJ2;
    listeJoueurs[2] = tempJ3;
    listeJoueurs[3] = tempJ4;

    for (int i = 0; i < nombreDeJoueurs; i++) {
        display();
        printf("Entrez le nom du joueur %d : ", i + 1);
        scanf("%s", listeJoueurs[i].username);
        listeJoueurs[i].avatar = choixAvatar(nombreDeJoueurs, 1);
    }

    display();
    gotoligcol(14, 0);

    for (int i = 0; i < nombreDeJoueurs; i++) {
        printf("Pseudo et avatar du joueur %d : %s  -  %c\n", i + 1, listeJoueurs[i].username, listeJoueurs[i].avatar);
    }

    printf("\nChargement de la partie en cours");

    //animation(20, 0, 75, 50);

    return listeJoueurs;
}



box *creationBox() {
    
    box *listeCase = (box *)malloc(40 * sizeof(box));

    char *name[20];


    for (int i = 0; i < 22; i++) {
        FILE *texte = NULL;
        char ignore[1024];
        int donnee[3];

        listeCase[40];

        texte = fopen("board.txt", "r");
        if (texte == NULL) {
            printf("Error: Cannot open");
        }
        for (int j = 0; j < i; j++) {
            fgets(ignore, sizeof(ignore), texte);
        }
        fscanf(texte, "%d;%s;%d;%d", &donnee[0], &name, &donnee[1], &donnee[2]);

        box tempBox = {donnee[0], donnee[1], donnee[2], (char) i};

        //box tempBox.id = donnee[0];

        listeCase[i] = tempBox;
    }

    return listeCase;
}



terrain *creationTerrain() {  // création d'une instance (un album)
    terrain *listeTerrain = (terrain *)malloc(23 * sizeof(terrain));

    terrain instance;

    char *listeNomTerrain[22] = {"RacineCarree", "Brol", "Absolution", "Plat.Collec", "Nevermind", "RAM", "OneMoreLove",
                                 "Discovery", "MMLP", "NWTS", "Eminem Show", "Or Noir", "Ouest Side", "Civilisation", "Unorth.Juke",
                                 "After Hours", "Thriller", "DLL", "Trinity", "JVLIVS", "Ipseite", "Cyborg"};

    for (int i = 0; i < 22; i++) {
        //char *nomCurrent = listeNomTerrain[i];

        FILE *texte = NULL;
        char ignore[1024];
        int donnee[14];
        char proprio[10];
        texte = fopen("fields.txt", "r");
        if (texte == NULL) {
            printf("Error: Cannot open");
        }
        for (int j = 0; j < i; j++) {
            fgets(ignore, sizeof(ignore), texte);
        }
        fscanf(texte, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &donnee[0], &donnee[1], &donnee[14],
               &donnee[2], &donnee[3], &donnee[4], &donnee[5], &donnee[6], &donnee[7],
               &donnee[8], &donnee[9], &donnee[10], &donnee[11], &donnee[12], &donnee[13]);

        instance.nom = listeNomTerrain[i];
        instance.id = donnee[0];
        instance.defaultPrice = donnee[1];
        instance.idOnBoard = donnee[14];
        instance.housePrice = donnee[2];
        instance.loyer = donnee[3];
        instance.loyermaison1 = donnee[4];
        instance.loyermaison2 = donnee[5];
        instance.loyermaison3 = donnee[6];
        instance.loyermaison4 = donnee[7];
        instance.loyerhotel = donnee[8];
        instance.hypotheque = donnee[9];
        instance.buildings = donnee[10];
        instance.x = donnee[11];
        instance.y = donnee[12];
        instance.couleur = donnee[13];
        instance.owned = false;
        instance.hotel = false;
        instance.hypotheque = false;

        listeTerrain[i] = instance;
    }

    return listeTerrain;
}



void afficherJoueurPlateau(joueur *joueurs, terrain *terrains) {
    int posJoueur[4] = {0};

    /*for (int i = 0; i < 4; i++) {
        posJoueur[i] = joueurs[i].position;
    }*/

    int pos1 = posJoueur[0], pos2 = posJoueur[1], pos3 = posJoueur[2], pos4 = posJoueur[3];

    int nbPos1 = 0, nbPos2 = 0, nbPos3 = 0, nbPos4 = 0;

    int currentPos;

    for (int i = 0; i < 4; i++) {
        currentPos = posJoueur[i];

        if (currentPos != -1) {
            if (currentPos == pos1) {
                nbPos1++;
            } else if (currentPos == pos2) {
                nbPos2++;
            } else if (currentPos == pos3) {
                nbPos3++;
            } else if (currentPos == pos4) {
                nbPos4++;
            }
        }
    }
    /*
    printf("|ID|Position|Nombre|\n");
    printf("| 1|      %d|    %d|\n", pos1, nbPos1);
    printf("| 2|      %d|    %d|\n", pos2, nbPos2);
    printf("| 3|      %d|    %d|\n", pos3, nbPos3);
    printf("| 4|      %d|    %d|\n\n", pos4, nbPos4);
    */

    if (pos1 == pos2) {
        nbPos2 = nbPos1;
    }
    if (pos1 == pos3) {
        nbPos3 = nbPos1;
    }
    if (pos1 == pos4) {
        nbPos4 = nbPos1;
    }
    if (pos2 == pos3) {
        nbPos3 = nbPos2;
    }
    if (pos2 == pos4) {
        nbPos4 = nbPos2;
    }
    if (pos3 == pos4) {
        nbPos4 = nbPos3;
    }

    /*
    printf("|ID|Position|Nombre|\n");
    printf("| 1|      %d|    %d|\n", pos1, nbPos1);
    printf("| 2|      %d|    %d|\n", pos2, nbPos2);
    printf("| 3|      %d|    %d|\n", pos3, nbPos3);
    printf("| 4|      %d|    %d|\n\n", pos4, nbPos4);
    */
    int posList[4] = {pos1, pos2, pos3, pos4};
    int nbPosList[4] = {nbPos1, nbPos2, nbPos3, nbPos4};
    
    for (int i = 0; i < 4; i++) {
        if (nbPosList[i] == 1) {
            //printf("ouodauo");
            gotoligcol(terrains[posList[i]].y + 2,terrains [posList[i]].x + 5);
            printf("%c", joueurs[i].avatar);
        } else if (nbPosList[i] == 2) {
            //printf("dazed");
            gotoligcol(terrains[posList[i]].y + 2, terrains [posList[i]].x + 4);
            printf("%c", joueurs[i].avatar);
            gotoligcol(terrains[posList[i]].y + 2, terrains[posList[i]].x + 7);
            printf("%c", joueurs[i + 1].avatar);
            i++;
        } else if (nbPosList[i] == 3) {
            //printf("fesfs");
            gotoligcol(terrains[posList[i]].y + 2, terrains[posList[i]].x + 3);
            printf("%c", joueurs[i].avatar);
            gotoligcol(terrains[posList[i]].y + 2, terrains[posList[i]].x + 5);
            printf("%c", joueurs[i + 1].avatar);
            gotoligcol(terrains[posList[i]].y + 2, terrains[posList[i]].x + 7);
            printf("%c", joueurs[i + 2].avatar);
            i++;
            i++;
        } else if (nbPosList[i] == 4) {
            //printf("fsedf");
            gotoligcol(terrains[posList[i]].y + 2, terrains[posList[i]].x + 2);
            printf("%c", joueurs[i].avatar);
            gotoligcol(terrains[posList[i]].y + 2, terrains[posList[i]].x + 4);
            printf("%c", joueurs[i + 1].avatar);
            gotoligcol(terrains[posList[i]].y + 2, terrains[posList[i]].x + 6);
            printf("%c", joueurs[i + 2].avatar);
            gotoligcol(terrains[posList[i]].y + 2, terrains[posList[i]].x + 8);
            printf("%c", joueurs[i + 3].avatar);
            i++;
            i++;
            i++;
        }
    }
}

void creationCase(char titre[15], int x, int y, int id, int couleur) {
    /*
    0 : Noir
    1 : Bleu foncé
    2 : Vert foncé
    3 : Turquoise
    4 : Rouge foncé
    5 : Violet
    6 : Vert caca d'oie
    7 : Gris clair
    8 : Gris foncé
    9 : Bleu fluo
    10 : Vert fluo
    11 : Turquoise
    12 : Rouge fluo
    13 : Violet 2
    14 : Jaune
    15 : Blanc
    */

    int longueur = 0;
    int bord = 0;
    longueur = strlen(titre);
    bord = (13 - longueur) / 2;
    Color(0, couleur);
    gotoligcol(x, y);
    if (id == 0) {
        for (int j = 0; j < 13; j++) {
            printf(" ");
        }
    } else {
        if (id < 10) {
            for (int i = 0; i < 6; i++) {
                printf(" ");
            }
            printf("%d", id);
            for (int a = 0; a < 6; a++) {
                printf(" ");
            }
        } else {
            for (int i = 0; i < 5; i++) {
                printf(" ");
            }
            printf("%d", id);
            for (int a = 0; a < 6; a++) {
                printf(" ");
            }
        }
    }
    printf("\n");
    gotoligcol(x + 1, y);
    for (int k = 0; k < bord; k++) {
        printf(" ");
    }
    gotoligcol(x + 1, y + bord);
    printf(titre);
    gotoligcol(x + 1, y + bord + longueur);
    for (int z = y + bord + longueur; z < y + 13; z++) {
        printf(" ");
    }
    for (int n = 0; n < 3; n++) {
        gotoligcol(x + 2 + n, y);
        for (int j = 0; j < 13; j++) {
            printf(" ");
        }
        printf("\n");
    }
    Color(15, 0);
}

void plateauGraphique(terrain *listeTerrains) {  // création du plateau de base, il reste inchangé après

    int couleurCaseNeutre = 15;

    for (int i = 0; i < 22; i++) {
        terrain currentTerrain = listeTerrains[i];
        char *nomCurrent = currentTerrain.nom;
        creationCase(nomCurrent, currentTerrain.x, currentTerrain.y, currentTerrain.id, currentTerrain.couleur);
    }
    creationCase("Soundcloud", 0, 0, 0, couleurCaseNeutre);
    creationCase("Communaute", 15, 0, 0, couleurCaseNeutre);
    creationCase("Zenith", 25, 0, 0, couleurCaseNeutre);
    creationCase("Sacem", 40, 0, 0, couleurCaseNeutre);
    creationCase("Finito", 50, 0, 0, couleurCaseNeutre);
    creationCase("Chance", 0, 26, 0, couleurCaseNeutre);
    creationCase("Zenith", 0, 65, 0, couleurCaseNeutre);
    creationCase("Sacem", 0, 104, 0, couleurCaseNeutre);
    creationCase("Drama", 0, 130, 0, couleurCaseNeutre);
    creationCase("Communaute", 15, 130, 0, couleurCaseNeutre);
    creationCase("Zenith", 25, 130, 0, couleurCaseNeutre);
    creationCase("Chance", 30, 130, 0, couleurCaseNeutre);
    creationCase("Sacem", 40, 130, 0, couleurCaseNeutre);
    creationCase("DEPART", 50, 130, 0, couleurCaseNeutre);
    creationCase("Chance", 50, 39, 0, couleurCaseNeutre);
    creationCase("Zenith", 50, 65, 0, couleurCaseNeutre);
    creationCase("Sacem", 50, 78, 0, couleurCaseNeutre);
    creationCase("Communaute", 50, 104, 0, couleurCaseNeutre);
}


int main() {
    system("cls");



    joueur *pJoueurs = creationDesJoueurs(4);
    terrain *pTerrains = creationTerrain();
    box *bList = creationBox();

    plateauGraphique(pTerrains);
    afficherJoueurPlateau(pJoueurs, pTerrains);

    
    free(bList);
    free(pJoueurs);
    free(pTerrains);
    gotoligcol(60, 0);
}