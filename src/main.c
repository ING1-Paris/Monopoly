#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>
#if defined(__WIN32__)
    #include <windows.h>
#endif
#define MAX 100

typedef struct {
    int id;              // Player's ID from 1 to 4
    long balance;        // Balance of the player
    char *username[MAX];  // Username of the player
    int position;        // ID of the player's current cell
    int cellType;        // Type of the player's current cell
    int ownedField[26];  // ID of each owned fields
    int luckCard[10];    // ID of possessed luck card
    int comCard[10];     // ID of possessed community card
    bool inJail;         // True if the player is in jail, false if not
    bool bankruptcy;     // True if the player is in bankruptcy, false if not
    char symbol;         // Le symbole du joueur
} joueur;

typedef struct {
    int id;            // Field's ID from 0 to 25
    int defaultPrice;  // Field's initial price
    int housePrice;    // Field's house price
    int loyer;         // Loyer de base
    int loyermaison1;  // Loyer avec une maison
    int loyermaison2;  // Loyer avec 2 maisons
    int loyermaison3;  // Loyer avec 3 maisons
    int loyermaison4;  // Loyer avec 4 maisons
    int loyerhotel;    // Loyer avec un hotel
    int hypotheque;    // Valeur hypothécaire
    int buildings;     // Amount of buildings in the field
    bool owned;        // True if owned, False if not
    bool hotel;        // True if there is a hotel
    char ownedBy[10];  // Name of the player who owns this field
} terrain;


int lancerDe() {
    // Retourne un nombre pseudo aléatoire en 1 et 6
    int nb;
    const int min = 1, max = 6;
    nb = (rand() % max) + min;
    printf("%d", nb);
    return nb;
}

int completeType() { return 0; }

void Color(int couleurDuTexte, int couleurDeFond) {  // fonction d'affichage de couleurs
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}

void gotoligcol(int lig, int col) {
    // ressources
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
}

void creationCase(char titre[15], int x, int y, int couleur, char mode) {
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
    int limite = 0;
    longueur = strlen(titre);
    bord = (12 - longueur) / 2;
    Color(0, couleur);
    if (mode == 'h') {
        limite = 2;
    } else if (mode == 'v') {
        limite = 1;
    }
    for (int i = 0; i < limite; i++) {
        gotoligcol(i + x, y);
        for (int j = 0; j < 12; j++) {
            printf(" ");
        }
        printf("\n");
    }
    gotoligcol(x + limite, y);
    for (int k = 0; k < bord; k++) {
        printf(" ");
    }
    gotoligcol(x + limite, y + bord);
    printf(titre);
    gotoligcol(x + limite, y + bord + longueur);
    for (int z = y + bord + longueur; z < y + 12; z++) {
        printf(" ");
    }
    for (int i = 0; i < limite; i++) {
        gotoligcol(i + x + limite + 1, y);
        for (int j = 0; j < 12; j++) {
            printf(" ");
        }
        printf("\n");
    }
    Color(15, 0);
}

void plateauGraphique() {
    creationCase("Soundcloud", 0, 0, 15, 'h');
    creationCase("Eminem Show", 5, 0, 4, 'v');
    creationCase("NWTS", 8, 0, 4, 'v');
    creationCase("Communaute", 11, 0, 15, 'v');
    creationCase("MMLP", 14, 0, 4, 'v');
    creationCase("Zenith", 17, 0, 15, 'v');
    creationCase("Discovery", 20, 0, 5, 'v');
    creationCase("OneMoreLove", 23, 0, 5, 'v');
    creationCase("Sacem", 26, 0, 15, 'v');
    creationCase("RAM", 29, 0, 5, 'v');
    creationCase("Finito", 32, 0, 15, 'h');
    creationCase("Or Noir", 0, 12, 12, 'h');
    creationCase("Chance", 0, 24, 15, 'h');
    creationCase("Ouest Side", 0, 36, 12, 'h');
    creationCase("Civilisation", 0, 48, 12, 'h');
    creationCase("Zenith", 0, 60, 15, 'h');
    creationCase("Unorth.Juke", 0, 72, 14, 'h');
    creationCase("After Hours", 0, 84, 14, 'h');
    creationCase("Sacem", 0, 96, 15, 'h');
    creationCase("Thriller", 0, 108, 14, 'h');
    creationCase("Drama", 0, 120, 15, 'h');
    creationCase("DLL", 5, 120, 2, 'v');
    creationCase("Trinity", 8, 120, 2, 'v');
    creationCase("Communaute", 11, 120, 15, 'v');
    creationCase("Julius", 14, 120, 2, 'v');
    creationCase("Zenith", 17, 120, 15, 'v');
    creationCase("Chance", 20, 120, 15, 'v');
    creationCase("Ipseite", 23, 120, 1, 'v');
    creationCase("Sacem", 26, 120, 15, 'v');
    creationCase("Cyborg", 29, 120, 1, 'v');
    creationCase("DEPART", 32, 120, 15, 'h');
    creationCase("Nevermind", 32, 12, 11, 'h');
    creationCase("Plat.Collec", 32, 24, 11, 'h');
    creationCase("Chance", 32, 36, 15, 'h');
    creationCase("Absolution", 32, 48, 11, 'h');
    creationCase("Zenith", 32, 60, 15, 'h');
    creationCase("Sacem", 32, 72, 15, 'h');
    creationCase("Brol", 32, 84, 13, 'h');
    creationCase("Communaute", 32, 96, 15, 'h');
    creationCase("RacineCarree", 32, 108, 13, 'h');
}

terrain creationTerrain(terrain instance, int position) {
    FILE *texte = NULL;
    char ignore[1024];
    int donnee[11];
    char proprio[10];
    texte = fopen("monopoly.txt", "r");
    if (texte == NULL) {
        printf("Error: Cannot open");
    }
    for (int i = 0; i < position; i++) {
        fgets(ignore, sizeof(ignore), texte);
    }
    fscanf(texte, "%d %d %d %d %d %d %d %d %d %d %d", &donnee[0], &donnee[1],
           &donnee[2], &donnee[3], &donnee[4], &donnee[5], &donnee[6], &donnee[7],
           &donnee[8], &donnee[9], &donnee[10]);
    instance.id = donnee[0];
    instance.defaultPrice = donnee[1];
    instance.housePrice = donnee[2];
    instance.loyer = donnee[3];
    instance.loyermaison1 = donnee[4];
    instance.loyermaison2 = donnee[5];
    instance.loyermaison3 = donnee[6];
    instance.loyermaison4 = donnee[7];
    instance.loyerhotel = donnee[8];
    instance.hypotheque = donnee[9];
    instance.buildings = donnee[10];
    instance.owned = false;
    instance.hotel = false;
    return instance;
}

void creationPlateau() {
    terrain racine;
    terrain brol;
    terrain absolution;
    terrain platinium;
    terrain nevermind;
    terrain ram;
    terrain onemore;
    terrain discovery;
    terrain mmlp;
    terrain nwts;
    terrain eminemshow;
    terrain ornoir;
    terrain ouestside;
    terrain civilisation;
    terrain jukebox;
    terrain after;
    terrain thriller;
    terrain dll;
    terrain trinity;
    terrain julius;
    terrain ipseite;
    terrain cyborg;
    racine = creationTerrain(racine, 0);
    brol = creationTerrain(brol, 1);
    absolution = creationTerrain(absolution, 2);
    platinium = creationTerrain(platinium, 3);
    nevermind = creationTerrain(nevermind, 4);
    ram = creationTerrain(ram, 5);
    onemore = creationTerrain(onemore, 6);
    discovery = creationTerrain(discovery, 7);
    mmlp = creationTerrain(mmlp, 8);
    nwts = creationTerrain(nwts, 9);
    eminemshow = creationTerrain(eminemshow, 10);
    ornoir = creationTerrain(ornoir, 11);
    ouestside = creationTerrain(ouestside, 12);
    civilisation = creationTerrain(civilisation, 13);
    jukebox = creationTerrain(jukebox, 14);
    after = creationTerrain(after, 15);
    thriller = creationTerrain(thriller, 16);
    dll = creationTerrain(dll, 17);
    trinity = creationTerrain(trinity, 18);
    julius = creationTerrain(julius, 19);
    ipseite = creationTerrain(ipseite, 20);
    cyborg = creationTerrain(cyborg, 21);
}

int creationDesJoueurs(int nombreDeJoueurs) {
    int emptyCard[10];
    int emptyField[26];

    joueur j1 = {1, 1500, "NULL", 0, 0, "test", "test", "test", false, false};
    joueur j2 = {1, 1500, "NULL", 0, 0, "test", "test", "test", false, false};

    scanf("%s", j1.username);
    printf("\n");
    scanf("%s", j2.username);
    printf("\n");

    printf("\n");
    printf("Pseudo joueur 1 : %s", j1.username);
    printf("Pseudo joueur 2 : %s", j2.username);
}

void clearScreen(){
    printf("\e[1;1H\e[2J");
}

int demanderNbJoueurs() {
    int nb_joueurs = 0;
    do {
        printf("Veuillez entrer le nombre de joueurs (entre 2 et 4): ");
        scanf("%d", &nb_joueurs);
    } while (nb_joueurs < 2 || nb_joueurs > 4);
    return nb_joueurs;
}

void newGame() {
    int nb_joueurs = 0;
    nb_joueurs = demanderNbJoueurs();
    plateauGraphique();
}

void regles(){
    printf("REGLESREGLELGERESLRE       SELGERSELGERSELGERSEL          REGLESREGLESERGE     REG	       SELGERSELGERSELGERSEL          REGLESREGLES");
    printf("\nSEL              REG       REL    	               REGLES		       SER	       REG                         REGLES");
    printf("\nREG               REG      SEL                      REGLES    		       REG	       SEL                     REGLES");
    printf("\nSEL                REG     REG			   REGLES                      SER             REG                    REGL");
    printf("\nREG                SEL	   SEL		          REGLES	               REG             SEL                   REG");
    printf("\nSEL               REG      REG		         REGLES                        SER             REG                    REGL");
    printf("\nREG		  SEL      SEL		         REGLE                         REG             SEL                     REGLES");
    printf("\nSEL		REG        REGLESREGRELESR	EGLE	                       SER             REGLESREGRELESR           REGL");
    printf("\nREGLESEGLESREGLES          SEL			 REG              SERGLES      REG             SEL                         REGLE");
    printf("\nREG            SEL         SEL			 REGLE                EGLES    SER             REG                           REGLE");
    printf("\nSEL             REG        SEL			 REGLES                 ERGEL  REG             SEL                              REGLE");
    printf("\nREG               SEL      REG			   SERLG                REGLE  SER             REG                                REGLE");
    printf("\nSEL                REG     SEL                      REGLE            SERLG     REG             SEL                               REGLE");
    printf("\nREG                 SEL    REG                        SERGLER      REGLES      SER             REG                           REGLES");
    printf("\nSEL                   REG  SELGERSELGERSELGERSEL          REGLESSERGLE         REGLESREGLESREG SELGERSELGERSELGERSEL  REGREGLESREG");
    printf("\n\nPour revenir au menu principal, appuyez sur une touche.");
    
}

void home() {
    int choice = 0;
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
    if (choice < 1 || choice > 6) {
        do {
            printf(
                "--> Votre saisie n'est pas valide. Veuillez entrer un chiffre a "
                "nouveau : ");
            scanf("%d", &choice);
        } while (choice < 1 || choice > 6);
    }
    switch(choice){
        case 1 : clearScreen(); // permet de clear la console !!!
        newGame();
        break;
        case 4 : clearScreen(); 
        regles();
        break;
    }
}

void skip() {  // saute 50 lignes
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}

void deplacement(joueur* player, int plateau[36], int de1, int de2){
    int somme = de1+de2;
    player->position += somme;
}

int main() {
    //int nb_joueurs, i, de1, de2 = 0;
    //int plateauJeu[36]; // plateau = liste de 36 cases
    //nb_joueurs = demanderNbJoueurs();
    //joueur players[nb_joueurs], *joueuractuel; // players[nb_joueurs] est la liste des joueurs
    //while("pas la fin"){
        //joueuractuel = &players[i];
        //de1 = lancerDe();
        //de2 = lancerDe();
        //deplacement(joueuractuel, plateauJeu, de1, de2);
        //if (joueuractuel->position > 12)
        //i++;
    //}
    skip();
    //creationPlateau();
    //plateauGraphique();

    //Initialisation
    //srand(time(NULL));
    home();

    //Tests
    //creationDesJoueurs(2);
    //printf("\n");
    return 0;
}