#ifndef LIB
#define LIB
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

#define MAX 100

// Déclaration des structures
typedef struct t_joueur {
    int id;                  // Player's ID from 1 to 4
    long balance;            // Balance of the player
    char username[MAX];      // Username of the player
    int position;            // ID of the player's current cell
    int cellType;            // Type of the player's current cell
    int ownedField[26];      // ID of each owned fields
    bool cartePrison;        // Carte sortie de prison
    bool carteDenonciation;  // carte chance pour payer moins chere
    bool inJail;             // True if the player is in jail, false if not
    bool bankruptcy;         // True if the player is in bankruptcy, false if not
    char symbol;             // Le symbole du joueur
    int streakDouble;        // Active number of doubles
    int timeInJail;          // Times in prison
    int avatar;              // Hexadecimal code for the avatar selection
} joueur;

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

typedef struct t_box {
    int id;
    int x;
    int y;
    char nom[20];
} box;

// Déclarations des prototypes
#if defined(__WIN32__)  // Needed to disable intellisense on macOS
void gotoligcol(int lig, int col);
void Color(int couleurDuTexte, int couleurDeFond);
void showCursor(bool show);
#endif

int lancerDe();
void clearScreen();
void showLogo();
void display();
void animation(int y, int x, int ms, int lenght);
void creationCase(char titre[15], int x, int y, int id, int couleur);
void terrainAchete(joueur players[], terrain album);
void ifHypotheque(terrain album);
joueur acheterTerrainJ(joueur currentplayer, terrain album);
terrain acheterTerrainT(joueur currentplayer, terrain album);
terrain acheterMaisonT(joueur currentplayer, terrain album);
joueur acheterMaisonJ(joueur currentplayer, terrain album);
int argentPaye(joueur currentplayer, terrain album);
joueur payerLoyerJ1(joueur currentplayer, int loyer);
joueur toucherLoyerJ2(joueur currentplayer, int loyer);
void plateauGraphique(terrain *listeTerrains);
terrain *creationTerrain();
int choixAvatar(int nbJoueurs, int currentPlayer);
joueur *creationDesJoueurs(int nombreDeJoueurs);
int demanderNbJoueurs();
void infoAlbum(terrain field);
void retourMenu();
void regles();
void credits();
void home();
joueur doubleStreakLimite(joueur player);
int cartePrisonEnJeu(joueur *listePlayers);
joueur deplacement(joueur player, int sommeDe);
void tourPartie2(terrain *listeTerrain, joueur *listePlayers, int currentPlayer, bool rejouer);
void tourNormal(terrain *listeTerrain, joueur *listePlayers, int currentPlayer, bool rejouer);
void tourPrison(terrain *listeTerrain, joueur *listePlayers, int currentPlayer);
void tourJoueur(terrain *listeTerrain, joueur *listePlayers, int currentPlayer, bool rejouer);
void newGame();

void afficherJoueurPlateau(joueur *joueurs, terrain *terrains, box *cases, int i, int j, int k, int l);
int caseColorId(int id);

#endif