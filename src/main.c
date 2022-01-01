#include <conio.h>
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

typedef struct t_joueur {
    int id;              // Player's ID from 1 to 4
    long balance;        // Balance of the player
    char username[MAX];  // Username of the player
    int position;        // ID of the player's current cell
    int cellType;        // Type of the player's current cell
    int ownedField[26];  // ID of each owned fields
    int luckCard[10];    // ID of possessed luck card
    int comCard[10];     // ID of possessed community card
    bool inJail;         // True if the player is in jail, false if not
    bool bankruptcy;     // True if the player is in bankruptcy, false if not
    char symbol;         // Le symbole du joueur
    int streakDouble;    // Active number of doubles
    int avatar;          // Hexadecimal code for the avatar selection
} joueur;

typedef struct t_terrain {
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
    int x;             // X position
    int y;             // Y position
    int couleur;       // Color of the cell
} terrain;

void clearScreen() { //permet de clear la console
    system("cls");
}

void gotoligcol(int lig, int col) {
    // ressources
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
}

int lancerDe() {
    // Retourne un nombre pseudo aléatoire en 1 et 6
    int nb;
    const int min = 1, max = 6;
    nb = (rand() % max) + min;
    printf("%d", nb);
    return nb;
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

void animation(int y, int x, int ms, int lenght) {
    int i;
    gotoligcol(y, x);
    printf("|");
    for (i = 0; i < lenght; i++) {
        printf("-");
    }
    printf("|");
    gotoligcol(y, x + 1);
    for (int i = 0; i < lenght; i++) {
        printf("#");
        Sleep(ms);
    }
}

void Color(int couleurDuTexte, int couleurDeFond) {  // fonction d'affichage de couleurs
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}

void creationCase(char titre[15], int x, int y, int couleur) {
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
    bord = (12 - longueur) / 2;
    Color(0, couleur);
    gotoligcol(x, y);
    for (int j = 0; j < 12; j++) {
        printf(" ");
    }
    printf("\n");
    gotoligcol(x + 1, y);
    for (int k = 0; k < bord; k++) {
        printf(" ");
    }
    gotoligcol(x + 1, y + bord);
    printf(titre);
    gotoligcol(x + 1, y + bord + longueur);
    for (int z = y + bord + longueur; z < y + 12; z++) {
        printf(" ");
    }
    for (int n=0; n<3; n++){
        gotoligcol(x+2+n, y);
        for (int j = 0; j < 12; j++) {
            printf(" ");
        }
        printf("\n");
    }
    Color(15, 0);
}

void caseOccupee(int position){

}

void positionJoueur(joueur player){

}

void terrainAchete(terrain album){ //vérifie si un terrain est occupé pour afficher son loyer à la place de son prix de base
    int nombreMaisons;
    nombreMaisons = album.buildings;
    if (album.owned == true){
        switch(nombreMaisons){
            case 0: gotoligcol(album.x+3, album.y+6); 
            printf("%d €", album.loyer);
            break;
            case 1: gotoligcol(album.x+3, album.y+6);
            printf("%d €", album.loyermaison1);
            break;
            case 2: gotoligcol(album.x+3, album.y+5); 
            printf("%d €", album.loyermaison2);
            break;
            case 3: gotoligcol(album.x+3, album.y+5); 
            printf("%d €", album.loyermaison3);
            break;
            case 4: gotoligcol(album.x+3, album.y+4); 
            printf("%d €", album.loyermaison4);
            break;
        }
    }
    if (album.hotel == true){
        gotoligcol(album.x+3, album.y+4);
        printf("%d €", album.loyerhotel);
    }
}

void plateauGraphique() {  // création du plateau de base, il reste inchangé après
    creationCase("Soundcloud", 0, 0, 15);
    creationCase("Eminem Show", 5, 0, 4);
    creationCase("NWTS", 10, 0, 4);
    creationCase("Communaute", 15, 0, 15);
    creationCase("MMLP", 20, 0, 4);
    creationCase("Zenith", 25, 0, 15);
    creationCase("Discovery", 30, 0, 7);
    creationCase("OneMoreLove", 35, 0, 7);
    creationCase("Sacem", 40, 0, 15);
    creationCase("RAM", 45, 0, 7);
    creationCase("Finito", 50, 0, 15);
    creationCase("Or Noir", 0, 12, 12);
    creationCase("Chance", 0, 24, 15);
    creationCase("Ouest Side", 0, 36, 12);
    creationCase("Civilisation", 0, 48, 12);
    creationCase("Zenith", 0, 60, 15);
    creationCase("Unorth.Juke", 0, 72, 14);
    creationCase("After Hours", 0, 84, 14);
    creationCase("Sacem", 0, 96, 15);
    creationCase("Thriller", 0, 108, 14);
    creationCase("Drama", 0, 120, 15);
    creationCase("DLL", 5, 120, 2);
    creationCase("Trinity", 10, 120, 2);
    creationCase("Communaute", 15, 120, 15);
    creationCase("Julius", 20, 120, 2);
    creationCase("Zenith", 25, 120, 15);
    creationCase("Chance", 30, 120, 15);
    creationCase("Ipseite", 35, 120, 10);
    creationCase("Sacem", 40, 120, 15);
    creationCase("Cyborg", 45, 120, 10);
    creationCase("DEPART", 50, 120, 15);
    creationCase("Nevermind", 50, 12, 11);
    creationCase("Plat.Collec", 50, 24, 11);
    creationCase("Chance", 50, 36, 15);
    creationCase("Absolution", 50, 48, 11);
    creationCase("Zenith", 50, 60, 15);
    creationCase("Sacem", 50, 72, 15);
    creationCase("Brol", 50, 84, 13);
    creationCase("Communaute", 50, 96, 15);
    creationCase("RacineCarree", 50, 108, 13);
}

terrain creationTerrain(terrain instance, int position) { //création d'une instance (un album)
    FILE *texte = NULL;
    char ignore[1024];
    int donnee[14];
    char proprio[10];
    texte = fopen("monopoly.txt", "r");
    if (texte == NULL) {
        printf("Error: Cannot open");
    }
    for (int i = 0; i < position; i++) {
        fgets(ignore, sizeof(ignore), texte);
    }
    fscanf(texte, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d", &donnee[0], &donnee[1],
           &donnee[2], &donnee[3], &donnee[4], &donnee[5], &donnee[6], &donnee[7],
           &donnee[8], &donnee[9], &donnee[10], &donnee[11], &donnee[12], donnee[13]);
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
    instance.x = donnee[11];
    instance.y = donnee[12];
    instance.couleur = donnee[13];
    instance.owned = false;
    instance.hotel = false;
    return instance;
}

terrain creationPlateau() {
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
    animation(20, 0, 50, 28);

    /*
    for (c = selection - 1; c < 10 - 1; c++)
        avatar[c] = avatar[c + 1];

    printf("Resultant array:\n");

    for (c = 0; c < 10 - 1; c++)
        printf("%c\n", avatar[c]);
    */

    return avatar[selection];
}

joueur *creationDesJoueurs(int nombreDeJoueurs) {
    int emptyCard[10];
    int emptyField[26];

    joueur *listeJoueurs = (joueur *)malloc(4 * sizeof(joueur));

    joueur tempJ1 = {1, 1500, "NULL", 0, 0, {0}, {0}, {0}, false, false};
    joueur tempJ2 = {2, 1500, "NULL", 0, 0, {0}, {0}, {0}, false, false};
    joueur tempJ3 = {3, 1500, "NULL", 0, 0, {0}, {0}, {0}, false, false};
    joueur tempJ4 = {4, 1500, "NULL", 0, 0, {0}, {0}, {0}, false, false};

    listeJoueurs[0] = tempJ1;
    listeJoueurs[1] = tempJ2;
    listeJoueurs[2] = tempJ3;
    listeJoueurs[3] = tempJ4;

    for (int i = 0; i < nombreDeJoueurs; i++) {
        display();
        printf("Entrez le nom du joueur %d : ", i+1);
        scanf("%s", listeJoueurs[i].username);
        listeJoueurs[i].avatar = choixAvatar(nombreDeJoueurs, 1);
    }

    display();
    gotoligcol(14, 0);

    for (int i = 0; i < nombreDeJoueurs; i++) {
        printf("Pseudo et avatar du joueur %d : %s  -  %c\n", i+1, listeJoueurs[i].username, listeJoueurs[i].avatar);
    }

    printf("\nChargement de la partie en cours");

    animation(20, 0, 75, 50);

    return listeJoueurs;
}

int demanderNbJoueurs() { //fonction demandant et renvoyant le nombre de joueurs
    int nb_joueurs = 0;
    display();
    do {
        printf("Veuillez entrer le nombre de joueurs (entre 2 et 4): ");
        scanf("%d", &nb_joueurs);
    } while (nb_joueurs < 2 || nb_joueurs > 4);
    return nb_joueurs;
}

void newGame() { // menu de création des joueurs, affiche le plateau de base
    int nb_joueurs = 0;
    nb_joueurs = demanderNbJoueurs();

    joueur *pJoueurs = creationDesJoueurs(nb_joueurs);

    joueur j1 = pJoueurs[0];
    joueur j2 = pJoueurs[1];
    joueur j3 = pJoueurs[2];
    joueur j4 = pJoueurs[3];

    printf("\n%d\n", j2.id);
    printf("%s\n", j2.username);

    free(pJoueurs);

    Sleep(5000);

    clearScreen();
    plateauGraphique();
    int i, de1, de2, sommeDe = 0;
    int plateauJeu[36]; // plateau = liste de 36 cases
    joueur players[nb_joueurs]; // players[nb_joueurs] est la liste des joueurs
    joueur* joueuractuel;
    //terrain plateauDeJeu[22];
    //plateauDeJeu[0] = creationTerrain(plateauDeJeu[0],0);
    //printf("%d", plateauDeJeu[0].defaultPrice);
    while(players[0].balance != 0 || players[1].balance != 0 || players[2].balance != 0){
         joueuractuel = &players[i];
         de1 = lancerDe();
         de2 = lancerDe();
         sommeDe = de1 + de2;
         deplacement(joueuractuel, plateauJeu, sommeDe);
         if (joueuractuel->position < 12){
             printf("%d", joueuractuel->position);
         }
         i++;
    }
}

void regles(){ // affichage des règles du jeu : exit avec lettre 'a' ; accessible via le menu principal
    char sortie;
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
    do{printf("\nPour revenir au menu principal, appuyez sur la touche 'a'. ");
    scanf("%c", &sortie);}while(sortie != 'a'); // à régler, ça print 2 fois pour x raison
    clearScreen();
    home();
}

void home() { // menu principal du jeu
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
    if (choice < 1 || choice > 6) {
        do {
            printf(
                "--> Votre saisie n'est pas valide. Veuillez entrer un chiffre a "
                "nouveau : ");
            scanf("%d", &choice);
        } while (choice < 1 || choice > 6);
    }
    switch (choice) {
        case 1:
            clearScreen();
            newGame();
            break;
        case 4:
            clearScreen();
            regles();
            break;
    }
}

void skip() {  // saute 50 lignes
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}

void deplacement(joueur* player, int plateau[36], int sommeDe) {
    player->position += sommeDe;
    printf("Deplacer %s de la case %d a la case %d.", player->username, plateau[36], sommeDe);
}

void checkIfOwned(int id) {
}

int main() {
    clearScreen();
    //choixAvatar();
    //  creationPlateau();

    // Initialisation
    // srand(time(NULL));
    home();

    return 0;
}