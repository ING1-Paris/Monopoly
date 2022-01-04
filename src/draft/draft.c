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

typedef struct t_case {
    int id;
    char nom[20];
    int x;
    int y;
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
        // display();
        printf("Entrez le nom du joueur %d : ", i + 1);
        scanf("%s", listeJoueurs[i].username);
        // listeJoueurs[i].avatar = choixAvatar(nombreDeJoueurs, 1);
    }

    // display();
    gotoligcol(14, 0);

    for (int i = 0; i < nombreDeJoueurs; i++) {
        printf("Pseudo et avatar du joueur %d : %s  -  %c\n", i + 1, listeJoueurs[i].username, listeJoueurs[i].avatar);
    }

    printf("\nChargement de la partie en cours");

    // animation(20, 0, 75, 50);

    return listeJoueurs;
}

void gotoligcol(int lig, int col) {
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
}

box *creationCase() {
    
    box *listeCase = (box *)malloc(40 * sizeof(box));


    for (int i = 0; i < 22; i++) {
        FILE *texte = NULL;
        char ignore[1024];
        int donnee[4];

        listeCase[40];

        texte = fopen("fields.txt", "r");
        if (texte == NULL) {
            printf("Error: Cannot open");
        }
        for (int j = 0; j < i; j++) {
            fgets(ignore, sizeof(ignore), texte);
        }
        fscanf(texte, "%d;%s;%d;%d", &donnee[0], &donnee[1], &donnee[2], &donnee[3]);

        box tempBox = {donnee[0], donnee[1], donnee[2], donnee[3]};

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
        char *nomCurrent = listeNomTerrain[i];

        FILE *texte = NULL;
        char ignore[1024];
        int donnee[14];
        char proprio[10];
        texte = fopen("data/fields.txt", "r");
        if (texte == NULL) {
            printf("Error: Cannot open");
        }
        for (int j = 0; j < i; j++) {
            fgets(ignore, sizeof(ignore), texte);
        }
        fscanf(texte, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &donnee[0], &donnee[1], &donnee[14],
               &donnee[2], &donnee[3], &donnee[4], &donnee[5], &donnee[6], &donnee[7],
               &donnee[8], &donnee[9], &donnee[10], &donnee[11], &donnee[12], &donnee[13]);

        instance.nom = nomCurrent;
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
    int posJoueur[4] = {5, 5, 12, 12};

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
    printf("|ID|Position|Nombre|\n");
    printf("| 1|      %d|    %d|\n", pos1, nbPos1);
    printf("| 2|      %d|    %d|\n", pos2, nbPos2);
    printf("| 3|      %d|    %d|\n", pos3, nbPos3);
    printf("| 4|      %d|    %d|\n\n", pos4, nbPos4);

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

    printf("|ID|Position|Nombre|\n");
    printf("| 1|      %d|    %d|\n", pos1, nbPos1);
    printf("| 2|      %d|    %d|\n", pos2, nbPos2);
    printf("| 3|      %d|    %d|\n", pos3, nbPos3);
    printf("| 4|      %d|    %d|\n\n", pos4, nbPos4);

    int posList[4] = {pos1, pos2, pos3, pos4};
    int nbPosList[4] = {nbPos1, nbPos2, nbPos3, nbPos4};

    for (int i = 0; i < 4; i++) {
        if (nbPosList[i] == 1) {
            gotoligcol(terrains[posList[i]].x + 5, terrains[posList[i]].y + 2);
            printf("%c", joueurs[i].avatar);
        } else if (nbPosList[i] == 2) {
            gotoligcol(terrains[posList[i]].x + 4, terrains[posList[i]].y + 2);
            printf("%c", joueurs[i].avatar);
            gotoligcol(terrains[posList[i]].x + 7, terrains[posList[i]].y + 2);
            printf("%c", joueurs[i + 1].avatar);
            i++;
        } else if (nbPosList[i] == 3) {
            gotoligcol(terrains[posList[i]].x + 3, terrains[posList[i]].y + 2);
            printf("%c", joueurs[i].avatar);
            gotoligcol(terrains[posList[i]].x + 5, terrains[posList[i]].y + 2);
            printf("%c", joueurs[i + 1].avatar);
            gotoligcol(terrains[posList[i]].x + 7, terrains[posList[i]].y + 2);
            printf("%c", joueurs[i + 2].avatar);
            i++;
            i++;
        } else if (nbPosList[i] == 4) {
            gotoligcol(terrains[posList[i]].x + 2, terrains[posList[i]].y + 2);
            printf("%c", joueurs[i].avatar);
            gotoligcol(terrains[posList[i]].x + 4, terrains[posList[i]].y + 2);
            printf("%c", joueurs[i + 1].avatar);
            gotoligcol(terrains[posList[i]].x + 6, terrains[posList[i]].y + 2);
            printf("%c", joueurs[i + 2].avatar);
            gotoligcol(terrains[posList[i]].x + 8, terrains[posList[i]].y + 2);
            printf("%c", joueurs[i + 3].avatar);
            i++;
            i++;
            i++;
        }
    }
}

int main() {
    joueur *pJoueurs = creationDesJoueurs(4);
    terrain *pTerrains = creationTerrain();

    box bList[40] = afficherJoueurPlateau(pJoueurs, pTerrains);
}