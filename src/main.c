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
    bool sortiePrison;   // ID of possessed luck card
    bool loyerDivise;    // ID of possessed community card
    bool inJail;         // True if the player is in jail, false if not
    bool bankruptcy;     // True if the player is in bankruptcy, false if not
    char symbol;         // Le symbole du joueur
    int streakDouble;    // Active number of doubles
    int timeInJail;      // Times in prison
    int avatar;          // Hexadecimal code for the avatar selection
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

void clearScreen() {  // permet de clear la console
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
    bord = (12 - longueur) / 2;
    Color(0, couleur);
    gotoligcol(x, y);
    if (id == 0) {
        for (int j = 0; j < 12; j++) {
            printf(" ");
        }
    } else {
        for (int i = 0; i < 5; i++) {
            printf(" ");
        }
        printf("%d", id);
        if (id < 10) {
            for (int a = 0; a < 6; a++) {
                printf(" ");
            }
        } else {
            for (int a = 0; a < 5; a++) {
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
    for (int z = y + bord + longueur; z < y + 12; z++) {
        printf(" ");
    }
    for (int n = 0; n < 3; n++) {
        gotoligcol(x + 2 + n, y);
        for (int j = 0; j < 12; j++) {
            printf(" ");
        }
        printf("\n");
    }
    Color(15, 0);
}

void terrainAchete(joueur players[], terrain album) {  // vérifie si un terrain est occupé pour afficher son proprio à la place de son prix de base
    int longueur = 0;
    Color(0, album.couleur);
    if (album.owned == true) {
        for (int i = 0; i < 4; i++) {
            if (album.ownedBy == players[i].id) {
                longueur = (12 - strlen(players[i].username)) / 2;
                gotoligcol(album.x + 3, album.y + longueur);
                printf("%s", players[i].username);
            }
        }
    } else {
        gotoligcol(album.x + 3, album.y + 5);
        printf("%d %c", album.defaultPrice, 0x24);  // essayer de print le symbole € avec
    }
    Color(15, 0);
}

void ifHypotheque(terrain album) {  // fonction vérifiant si une case est hypothéquée
    Color(0, album.couleur);
    if (album.hypotheque == true) {
        gotoligcol(album.x + 4, album.y + 1);
        printf("H");
    }
    Color(15, 0);
}

joueur updateJoueur(joueur currentplayer, terrain album) {  // fonction d'achat d'un terrain --> partie joueur
    int i = 0;
    currentplayer.balance -= album.defaultPrice;
    while (currentplayer.ownedField[i] != 0) {
        i++;
    }
    currentplayer.ownedField[i] = album.id;
    return currentplayer;
}

terrain updateTerrain(joueur currentplayer, terrain album) {  // fonction d'achat d'un terrain --> partie terrain
    album.owned = true;
    album.ownedBy = currentplayer.id;
    return album;
}

terrain acheterMaisonT(joueur currentplayer, terrain album) {  // fonction d'achat d'une maison --> partie terrain
    album.buildings += 1;
    return album;
}

joueur acheterMaisonJ(joueur currentplayer, terrain album) {  // fonction d'achat d'une maison --> partie joueur
    currentplayer.balance -= album.housePrice;
    return currentplayer;
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
    creationCase("Chance", 0, 24, 0, couleurCaseNeutre);
    creationCase("Zenith", 0, 60, 0, couleurCaseNeutre);
    creationCase("Sacem", 0, 96, 0, couleurCaseNeutre);
    creationCase("Drama", 0, 120, 0, couleurCaseNeutre);
    creationCase("Communaute", 15, 120, 0, couleurCaseNeutre);
    creationCase("Zenith", 25, 120, 0, couleurCaseNeutre);
    creationCase("Chance", 30, 120, 0, couleurCaseNeutre);
    creationCase("Sacem", 40, 120, 0, couleurCaseNeutre);
    creationCase("DEPART", 50, 120, 0, couleurCaseNeutre);
    creationCase("Chance", 50, 36, 0, couleurCaseNeutre);
    creationCase("Zenith", 50, 60, 0, couleurCaseNeutre);
    creationCase("Sacem", 50, 72, 0, couleurCaseNeutre);
    creationCase("Communaute", 50, 96, 0, couleurCaseNeutre);
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

    animation(20, 0, 75, 50);

    return listeJoueurs;
}

int demanderNbJoueurs() {  // fonction demandant et renvoyant le nombre de joueurs
    int nb_joueurs = 0;
    display();
    do {
        printf("Veuillez entrer le nombre de joueurs (entre 2 et 4): ");
        scanf("%d", &nb_joueurs);
    } while (nb_joueurs < 2 || nb_joueurs > 4);
    return nb_joueurs;
}

void infoAlbum(terrain field) {  // fonction affichant toutes les infos d'un album
    gotoligcol(23, 20);
    printf("Album : %s", field.nom);
    gotoligcol(24, 20);
    if (field.owned == true) {
        printf("L'album appartient a %s", field.ownedBy);
    } else {
        printf("L'album n'appartient a personne.");
    }
    gotoligcol(25, 20);
    printf("Prix de base de l'album : %d%c", field.defaultPrice, 0x24);
    gotoligcol(26, 20);
    printf("Prix d'une certification : %d%c", field.housePrice, 0x24);
    gotoligcol(27, 20);
    printf("Disque non certifie : %d%c", field.loyer, 0x24);
    gotoligcol(27, 35);
    printf("Disque d'argent : %d%c", field.loyermaison1, 0x24);
    gotoligcol(27, 60);
    printf("Disque d'or : %d%c", field.loyermaison2, 0x24);
    gotoligcol(28, 28);
    printf("Disque de platine: %d%c", field.loyermaison3, 0x24);
    gotoligcol(28, 51);
    printf("Disque de diamant : %d%c", field.loyermaison1, 0x24);
    gotoligcol(29, 20);
    if (field.hotel == true) {
        printf("L'album est certifie double diamant.");
    } else {
        printf("L'album possède %d certifications.", field.buildings);
    }
    gotoligcol(30, 20);
    printf("La valeur de la revente est estimee a %d%c", field.val_hypoth, 0x24);
}

void newGame() {  // menu de création des joueurs, affiche le plateau de base
    const int nb_joueurs = demanderNbJoueurs();

    joueur *pJoueurs = creationDesJoueurs(nb_joueurs);
    terrain *pTerrains = creationTerrain();

    /*joueur j1 = pJoueurs[0];
    joueur j2 = pJoueurs[1];
    joueur j3 = pJoueurs[2];
    joueur j4 = pJoueurs[3];*/

    Sleep(2000);

    free(pJoueurs);
    free(pTerrains);

    clearScreen();
    plateauGraphique(pTerrains);

    joueur joueuractuel = pJoueurs[0];
    tourJoueur(pTerrains, joueuractuel, false);
}

void retourMenu() {  // fonction intermédiaire pour revenir dans le menu principal
    clearScreen();
    home();
}

void regles() {  // affichage des règles du jeu : exit avec lettre 'a' ; accessible via le menu principal
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
    do {
        printf("\n\nPour revenir au menu principal, appuyez sur la touche 'a'. ");
        scanf("%c", &sortie);
    } while (sortie != 'a');  // à régler, ça print 2 fois pour x raison
    retourMenu();
}

void credits() {  // affichage des crédits du jeu : exit avec lettre 'a' ; accessible via le menu principal
    char sortie;
    printf("        CERDTSCREDITSCER     CREDITSCREDITSCRE	      CREDITSCREDITSCRE  CREDITSCR	 CREDITSCREDITSCRE   CREDITSCREDITSCRE     CREDITSCREDITSC");
    printf("\n     STIDERCCR      CREDITS  CRE	     CRE      CRE		 DIT     CRE		CRE		    CRE         CREDITS");
    printf("\n   CREDITSC		     DIT              DIT     DIT		 CRE      CRE		DIT		    DIT       CREDITS");
    printf("\n STERDIC		     SCR   	       SCR    CRE		 DIT        STI         CRE                 CRE       CREDITS");
    printf("\nCREDIT			     EDI     	      CRE     DIT		 CRE         CRE        DIT                 DIT        CREDITS");
    printf("\nSERDTE			     TSC             DIT      CRE		 DIT          STI	CRE		    CRE          CREDITS");
    printf("\nCREDIT                       RED            SCR       DITCREDITR	 CRE          CRE	DIT                 DIT             CREDITS");
    printf("\nSERDIC                       CREDITSCREDITSCR         CRE		 DIT          STI	CRE                 CRE               CREDITS");
    printf("\nCREDIT                       SCR	    CRE       DIT		 CRE          CRE	DIT                 DIT                CREDITS");
    printf("\n STERDIC                     EDI	     DIT      CRE		 DIT         STI	CRE                 CRE                  CREDITS");
    printf("\n   CREDITSC                  TSC	      CRE     DIT		 CRE       CRE		DIT                 DIT                  CREDITS");
    printf("\n     STIDERCCR      CREDITS  RED	       DIT    CRE		 DIT      CRE		CRE                 CRE               CREDITS");
    printf("\n        CERDIDCREDITSCER     ITS		SCR   DITCREDITCREDITC   CREDITSCR	 CREDITSCRDITSCRE           DIT       CREDITSCREDI");
    do {
        printf("\n\nPour revenir au menu principal, appuyez sur la touche 'a'. ");
        scanf("%c", &sortie);
    } while (sortie != 'a');  // à régler, ça print 2 fois pour x raison
    retourMenu();
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
            newGame();
            break;
        case 4:
            clearScreen();
            regles();
            break;
        case 5:
            clearScreen();
            credits();
            break;
    }
}

joueur doubleStreakLimite(joueur player) {
    gotoligcol(25, 15);
    printf("Envoyer le joueur en prison");
    player.position = 10;
    player.streakDouble = 0;
    return player;
}

joueur deplacement(joueur player, int sommeDe) {
    gotoligcol(21, 50);
    printf("Deplacer %s de la case %d a la case %d.", player.username, player.position, player.position + sommeDe);
    player.position += sommeDe;
    return player;
}

void tourPartie2(terrain *listeTerrain, joueur player, bool rejouer) {
    int terrainactuel, choix, proprietaire, nbMaisons, idalbum = 0;
    terrainactuel = player.position;
    if (player.position == 36 || player.position == 7 || player.position == 22) {  // cases chance
        gotoligcol(29, 15);
        printf("APPELER LA FONCTION caseChance()");
    } else if (player.position == 2 || player.position == 17 || player.position == 32) {  // cases communauté
        gotoligcol(29, 15);
        printf("APPELER LA FONCTION caseCommunaute()");
    } else if (player.position == 4 || player.position == 12 || player.position == 28 || player.position == 38) {  // cases sacem
        player.balance -= 200;
    } else if (player.position == 20) {  // case soundcloud (stationnement libre)
        gotoligcol(29, 15);
        printf("Reposez vous bien !");
    } else if (player.position == 30) {
        gotoligcol(29, 15);
        printf("A cause d'une polemique, vous etes finito ...");
        player.position = 10;
    } else if (player.position = 10) {
        gotoligcol(29, 15);
        printf("%s est finito !", player.username);
    } else {
        nbMaisons = listeTerrain[terrainactuel].buildings;
        if (listeTerrain[terrainactuel].owned == true && listeTerrain[terrainactuel].ownedBy != player.id) {
            gotoligcol(25, 15);
            printf("%s est chez %d !", player.username, listeTerrain[terrainactuel].ownedBy);
            gotoligcol(26, 15);
            printf("Le joueur doit payer un montant de :");
            gotoligcol(27, 15);
            switch (nbMaisons) {
                case 0:
                    printf("%d%c", listeTerrain[terrainactuel].loyer, 0x24);
                    break;
                case 1:
                    printf("%d%c", listeTerrain[terrainactuel].loyermaison1, 0x24);
                    break;
                case 2:
                    printf("%d%c", listeTerrain[terrainactuel].loyermaison2, 0x24);
                    break;
                case 3:
                    printf("%d%c", listeTerrain[terrainactuel].loyermaison3, 0x24);
                    break;
                case 4:
                    printf("%d%c", listeTerrain[terrainactuel].loyermaison4, 0x24);
                    break;
            }
            if (listeTerrain[terrainactuel].hotel == true) {
                printf("%d%c", listeTerrain[terrainactuel].loyerhotel, 0x24);
            }
            gotoligcol(28, 15);
            printf("Appuyez sur 'Entree' pour continuer.");
            gotoligcol(29, 15);
            printf("APPELER LA FONCTION terrainOccupe()");
            gotoligcol(30, 15);
        } else {
            gotoligcol(25, 15);
            printf("%s peut maintenant :", player.username);
            gotoligcol(26, 15);
            printf("1- Acheter la propriete");
            gotoligcol(27, 15);
            printf("2- Acheter une maison ou un hotel");  // ajouter fonction acheter maison, vérifier si c'est possible
            gotoligcol(28, 15);
            printf("3- Obtenir des informations sur un terrain");
            gotoligcol(29, 15);
            printf("4- Finir le tour et passer au joueur suivant");
            gotoligcol(30, 15);
            printf(">> ");
            fflush(stdin);
            do {
                scanf("%d", &choix);
            } while (choix < 1 || choix > 4);
        }

        if (choix == 1) {
            player = updateJoueur(player, listeTerrain[terrainactuel]);
            listeTerrain[terrainactuel] = updateTerrain(player, listeTerrain[terrainactuel]);
        } else if (choix == 2) {
            if (listeTerrain[terrainactuel].ownedBy != player.id) {
                gotoligcol(30, 15);
                printf("Vous n'etes pas proprietaire de ce terrain, veuillez choisir une autre option : ");
                do {
                    scanf("%d", choix);
                } while (choix < 1 || choix > 4);
            } else {
                player = acheterMaisonJ(player, listeTerrain[terrainactuel]);
                listeTerrain[terrainactuel] = acheterMaisonT(player, listeTerrain[terrainactuel]);
            }
        } else if (choix == 3) {
            gotoligcol(30, 15);
            printf("Saisissez l'ID de l'album sur lequel vous souhaitez des informations : ");
            scanf("%d", &idalbum);
            infoAlbum(listeTerrain[idalbum + 1]);
            fflush(stdin);
            gotoligcol(25, 15);
            printf("%s peut maintenant :", player.username);
            gotoligcol(26, 15);
            printf("1- Acheter la propriete");
            gotoligcol(27, 15);
            printf("2- Acheter une maison ou un hotel");
            gotoligcol(28, 15);
            printf("3- Obtenir des informations sur un terrain");
            gotoligcol(29, 15);
            printf("4- Finir le tour et passer au joueur suivant");
            gotoligcol(30, 15);
            printf(">> ");
            fflush(stdin);
            do {
                scanf("%d", &choix);
            } while (choix < 1 || choix > 4);
        } else {
            if (!rejouer) {
                gotoligcol(26, 30);
                printf("Passer au tour du joueur suivant");
            } else {
                gotoligcol(26, 30);
                printf("On fait rejouer le joueur");
            }
        }
    }
}

void tourNormal(terrain *listeTerrain, joueur player, bool rejouer) {
    int premierDe = 0;
    int deuxiemeDe = 0;
    int sommeDe = 0;
    int choix = 0;
    clearScreen();
    plateauGraphique(listeTerrain);

    if (rejouer) {
        gotoligcol(25, 15);
        printf("%s rejoue, il a fait un double :", player.username);
    } else {
        gotoligcol(27, 15);
        printf("Tour de %s, options :", player.username);
    }

    gotoligcol(28, 15);
    printf("1- Lancer les des");
    gotoligcol(29, 15);
    printf("2- Retourner au menu");
    gotoligcol(30, 15);
    printf(">> ");
    fflush(stdin);
    do {
        scanf("%d", &choix);
    } while (choix < 1 || choix > 2);

    if (choix == 1) {
        premierDe = lancerDe();
        deuxiemeDe = lancerDe();
        sommeDe = premierDe + deuxiemeDe;
        gotoligcol(18, 50);
        printf("Premier de : %d", premierDe);
        gotoligcol(19, 50);
        printf("Deuxieme de : %d", deuxiemeDe);
        if (premierDe == deuxiemeDe) {  // Si le joueur fait un double
            player.streakDouble += 1;
            gotoligcol(10, 50);
            printf("%s a fait un double !", player.username);
            if (player.streakDouble == 3) {  // Soit il en a fait 3 d'affilés alors il a des malus (prison etc)
                printf("Le joueur a fait 3 doubles d'affilee.");
                player = doubleStreakLimite(player);

            } else {  // Soit il n'en est pas à 3 et peut donc jouer 2 fois
                gotoligcol(16, 50);
                printf("Le joueur a fait un double et peut donc rejouer");
                player = deplacement(player, sommeDe);
                tourPartie2(listeTerrain, player, true);
                tourJoueur(listeTerrain, player, true);
            }
            // !
        } else {  // Si le joueur ne fait pas de double
            tourPartie2(listeTerrain, player, false);
        }

    } else if (choix == 2) {
        clearScreen();
        home();
    }
}

void tourPrison(terrain *listeTerrain, joueur player) {
    int premierDe = 0;
    int deuxiemeDe = 0;
    int sommeDe = 0;
    int choix1, choix2 = 0;

    gotoligcol(25, 15);
    printf("C'est au tour de %s : il est en prison depuis %d tour(s).", player.username, player.timeInJail);
    gotoligcol(26, 15);
    printf("Il peut :");
    gotoligcol(27, 15);
    printf("1- Continuer le tour");
    gotoligcol(28, 15);
    printf("2- Retourner au menu");
    gotoligcol(29, 15);
    printf(">> ");
    do {
        scanf("%d", &choix1);
    } while (choix1 < 1 || choix1 > 2);
    if (choix1 == 1) {                 // Continuer le tour
        if (player.timeInJail == 3) {  // Si il est en prison depuis 3 tours
            player.timeInJail = 0;
            player.balance -= 50;
            gotoligcol(28, 15);
            printf("%s perd donc 50€ et peut a nouveau jouer normalement.", player.username);
            gotoligcol(25, 15);
            tourNormal(listeTerrain, player, false);

        } else {  // Si il est en prison depuis moins de 3 tours
            gotoligcol(27, 15);
            printf("1- Payer 50 %c à la banque", 0x24);
            gotoligcol(28, 15);
            printf("2- Tenter d'obtenir un double");
            gotoligcol(29, 15);
            if (player.sortiePrison == true) {
                printf("3- Utiliser votre carte 'Sortie de prison'");
            }  // faire un else avec la possibilité d'acheter la carte à un autre joueur
            do {
                scanf("%d", &choix2);
            } while (choix2 < 1 || choix2 > 2);
            player.timeInJail += 1;
            premierDe = lancerDe();
            deuxiemeDe = lancerDe();
            sommeDe = premierDe + deuxiemeDe;
            if (choix2 == 1) {
                player.balance -= 50;
                player = deplacement(player, sommeDe);
                if (premierDe == deuxiemeDe) {  // Si le joueur fait un double
                    player.streakDouble += 1;
                    gotoligcol(10, 50);
                    printf("%s a fait un double ! Il peut donc rejouer.", player.username);
                    tourPartie2(listeTerrain, player, true);
                    tourJoueur(listeTerrain, player, true);
                } else {
                    tourPartie2(listeTerrain, player, false);
                }
            } else if (choix2 == 2) {
                if (premierDe == deuxiemeDe) {  // Si il fait un double
                    gotoligcol(28, 15);
                    printf("%s a fait un double ! Il sort de prison et avance de %d cases.", player.username, sommeDe);
                    player = deplacement(player, sommeDe);
                    tourPartie2(listeTerrain, player, false);
                }
            } else if (choix2 == 3) {  // Si il ne fait pas un double
                player = deplacement(player, sommeDe);
                tourPartie2(listeTerrain, player, false);
            } else {
                gotoligcol(28, 15);
                printf("%s n'a pas fait de double et reste en prison...", player.username);
                gotoligcol(29, 15);
                printf("LANCER TOUR JOUEUR SUIVANT");
            }
        }

    } else if (choix1 == 2) {
        home();
    }
}

void tourJoueur(terrain *listeTerrain, joueur player, bool rejouer) {
    int choix = 0;
    if (player.position == 10) {
        tourPrison(listeTerrain, player);
    } else {
        tourNormal(listeTerrain, player, rejouer);
    }
}

void afficherJoueurPlateau(joueur joueurs[], terrain terrains[]) {
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
            printf("%c", joueurs[i+1].avatar);
            i++;
        } else if (nbPosList[i] == 3) {
            gotoligcol(terrains[posList[i]].x + 3, terrains[posList[i]].y + 2);
            printf("%c", joueurs[i].avatar);
            gotoligcol(terrains[posList[i]].x + 5, terrains[posList[i]].y + 2);
            printf("%c", joueurs[i+1].avatar);
            gotoligcol(terrains[posList[i]].x + 7, terrains[posList[i]].y + 2);
            printf("%c", joueurs[i + 2].avatar);
            i++;
            i++;
        } else if (nbPosList[i] == 4) {
            gotoligcol(terrains[posList[i]].x + 2, terrains[posList[i]].y + 2);
            printf("%c", joueurs[i].avatar);
            gotoligcol(terrains[posList[i]].x + 4, terrains[posList[i]].y + 2);
            printf("%c", joueurs[i+1].avatar);
            gotoligcol(terrains[posList[i]].x + 6, terrains[posList[i]].y + 2);
            printf("%c", joueurs[i+2].avatar);
            gotoligcol(terrains[posList[i]].x + 8, terrains[posList[i]].y + 2);
            printf("%c", joueurs[i + 3].avatar);
            i++;
            i++;
            i++;
        }
    }
}

int main() {
    srand(time(NULL));  // initialise aléatoire selon une seed
    clearScreen();
    home();
    // choixAvatar();
    //   creationPlateau();

    // Initialisation
    // home();
    return 0;
}