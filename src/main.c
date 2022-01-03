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

void plateauGraphique(terrain *listeTerrains) {  // création du plateau de base, il reste inchangé après

    int couleurCaseNeutre = 15;

    for (int i = 0; i < 22; i++) {
        terrain currentTerrain = listeTerrains[i];
        char *nomCurrent = currentTerrain.nom;
        creationCase(nomCurrent, currentTerrain.x, currentTerrain.y, currentTerrain.couleur);
    }
    creationCase("Soundcloud", 0, 0, couleurCaseNeutre);
    creationCase("Communaute", 15, 0, couleurCaseNeutre);
    creationCase("Zenith", 25, 0, couleurCaseNeutre);
    creationCase("Sacem", 40, 0, couleurCaseNeutre);
    creationCase("Finito", 50, 0, couleurCaseNeutre);
    creationCase("Chance", 0, 24, couleurCaseNeutre);
    creationCase("Zenith", 0, 60, couleurCaseNeutre);
    creationCase("Sacem", 0, 96, couleurCaseNeutre);
    creationCase("Drama", 0, 120, couleurCaseNeutre);
    creationCase("Communaute", 15, 120, couleurCaseNeutre);
    creationCase("Zenith", 25, 120, couleurCaseNeutre);
    creationCase("Chance", 30, 120, couleurCaseNeutre);
    creationCase("Sacem", 40, 120, couleurCaseNeutre);
    creationCase("DEPART", 50, 120, couleurCaseNeutre);
    creationCase("Chance", 50, 36, couleurCaseNeutre);
    creationCase("Zenith", 50, 60, couleurCaseNeutre);
    creationCase("Sacem", 50, 72, couleurCaseNeutre);
    creationCase("Communaute", 50, 96, couleurCaseNeutre);
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

void newGame() {  // menu de création des joueurs, affiche le plateau de base
    const int nb_joueurs = demanderNbJoueurs();

    joueur *pJoueurs = creationDesJoueurs(nb_joueurs);
    terrain *pTerrains = creationTerrain();

    /*joueur j1 = pJoueurs[0];
    joueur j2 = pJoueurs[1];
    joueur j3 = pJoueurs[2];
    joueur j4 = pJoueurs[3];*/

    pJoueurs[1] = updateJoueur(pJoueurs[1], pTerrains[0]);
    pTerrains[0] = updateTerrain(pJoueurs[1], pTerrains[0]);
    pJoueurs[0] = updateJoueur(pJoueurs[0], pTerrains[2]);
    pTerrains[2] = updateTerrain(pJoueurs[0], pTerrains[2]);
    terrainAchete(pJoueurs, pTerrains[0]);
    terrainAchete(pJoueurs, pTerrains[2]);
    gotoligcol(0, 140);
    printf("%d %d", pJoueurs[0].balance, pJoueurs[1].balance);
    printf("%d %d", pTerrains[0].ownedBy, pTerrains[2].ownedBy);

    Sleep(2000);

    free(pJoueurs);
    free(pTerrains);

    clearScreen();
    plateauGraphique(pTerrains);

    int i, de1, de2, sommeDe = 0;
    int plateauJeu[36];  // plateau = liste de 36 cases

    joueur *joueuractuel;
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
        printf("\nPour revenir au menu principal, appuyez sur la touche 'a'. ");
        scanf("%c", &sortie);
    } while (sortie != 'a');  // à régler, ça print 2 fois pour x raison
    clearScreen();
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
    }
}

void doubleStreakLimite(joueur player) {
    printf("Envoyer le joueur en prison + toutes les conditions si y'a double");
    player.position = 30;
}

void deplacement(joueur player, int sommeDe) {
    gotoligcol(25, 50);
    printf("Deplacer %s de la case %d a la case %d.", *player.username, player.position, sommeDe);
    player.position += sommeDe;
}

void tourPartie2(joueur player, bool rejouer) {
    int choix = 0;
    int proprietaire = 0;
    int loyer = 333;
    int type = 1;
    if (proprietaire != 0) {
        gotoligcol(25, 15);
        printf("%s est chez %d !", *player.username, proprietaire);
        gotoligcol(26, 15);
        printf("Le joueur doit payer un montant de :");
        gotoligcol(27, 15);
        printf("%f €", loyer);
        gotoligcol(28, 15);
        printf("Appuyez sur 'Entree' pour continuer.");
        gotoligcol(29, 15);
        printf("APPELER LA FONCTION terrainOccupe()");
        gotoligcol(30, 15);
        scanf("%d", &choix);
    } else if (type == 2) {
        gotoligcol(29, 15);
        printf("APPELER LA FONCTION caseChance()");
    } else if (type == 3) {
        gotoligcol(29, 15);
        printf("APPELER LA FONCTION caseCommunaute()");
    } else if (type == 4) {
        gotoligcol(29, 15);
        printf("APPELER LA FONCTION caseTaxe()");
    } else if (type == 4) {
        gotoligcol(29, 15);
        printf("APPELER LA FONCTION caseParcGratuit()");
    } else {
        gotoligcol(25, 15);
        printf("%s peut maintenant :", *player.username);
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
        scanf("%d", &choix);
        clearScreen();
        terrain *pTerrains = creationTerrain();
        plateauGraphique(pTerrains);
        if (choix == 1) {
            gotoligcol(26, 30);
            printf("Lancer la fonction ACHAT DE PROPRIETE");
        } else if (choix == 2) {
            gotoligcol(26, 30);
            printf("Lancer la fonction INFORMATION SUR UNE PROPRIETE");
        } else if (choix == 3) {
            if (!rejouer) {
                gotoligcol(26, 30);
                printf("Passer au tour du joueur suivant");
            } else {
                gotoligcol(26, 30);
                printf("On fait rejouer le joueur");
            }
        } else {
            gotoligcol(26, 30);
            printf("Le choix ne correspond a aucune des options");
        }
    }
}

void tourNormal(joueur player, bool rejouer) {
    int premierDe = 0;
    int deuxiemeDe = 0;
    int sommeDe = 0;
    int choix = 0;
    clearScreen();
    terrain *pTerrains = creationTerrain();
    plateauGraphique(pTerrains);

    if (rejouer) {
        gotoligcol(27, 15);
        printf("%s rejoue, il a fait un double :", *player.username);
    } else {
        gotoligcol(27, 15);
        printf("Tour de %s, options :", *player.username);
    }

    gotoligcol(28, 15);
    printf("1- Lancer les des");
    gotoligcol(29, 15);
    printf("2- Retourner au menu");
    gotoligcol(30, 15);
    printf(">> ");
    fflush(stdin);
    scanf("%d", &choix);

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
            printf("%s a fait un double !", *player.username);

            if (player.streakDouble == 3) {  // Soit il en a fait 3 d'affilés alors il a des malus (prison etc)
                printf("Le joueur a fait 3 doubles d'affiles.");
                doubleStreakLimite(player);

            } else {  // Soit il n'en est pas à 3 et peut donc jouer 2 fois
                gotoligcol(16, 50);
                printf("Le joueur a fait un double et peut donc rejouer");
                deplacement(player, sommeDe);
                tourPartie2(player, true);
                tourNormal(player, true);
            }
            // !
        } else {  // Si le joueur ne fait pas de double
            tourPartie2(player, false);
        }

    } else if (choix == 2) {
        home();
    }
}

void tourPrison(joueur player) {
    int premierDe = 0;
    int deuxiemeDe = 0;
    int sommeDe = 0;
    int choix = 0;

    gotoligcol(25, 15);
    printf("C'est au tour de %s : il est en prison depuis %d tours.", *player.username, player.timeInJail);
    gotoligcol(26, 15);
    printf("Il peut :");
    gotoligcol(27, 15);
    printf("1- Continuer le tour");
    gotoligcol(28, 15);
    printf("2- Retourner au menu");
    gotoligcol(29, 15);
    printf(">> ");
    scanf("%d", &choix);
    if (choix == 1) {                  // Continuer le tour
        if (player.timeInJail == 3) {  // Si il est en prison depuis 3 tours
            player.timeInJail = 0;
            player.balance -= 50;
            gotoligcol(28, 15);
            printf("%s perd donc 50€ et peut a nouveau jouer normalement.", *player.username);
            gotoligcol(25, 15);
            tourNormal(player, false);

        } else {  // Si il est en prison depuis moins de 3 tours
            player.timeInJail += 1;
            premierDe = lancerDe();
            deuxiemeDe = lancerDe();
            sommeDe = premierDe + deuxiemeDe;
            if (premierDe == deuxiemeDe) {  // Si il fait un double
                gotoligcol(28, 15);
                printf("%s a fait un double ! Il sort de prison et avance de %d cases.", *player.username, sommeDe);
                deplacement(player, sommeDe);
                tourPartie2(player, false);
            } else {  // Si il ne fait pas un double
                gotoligcol(28, 15);
                printf("%s n'a pas fait de double et reste en prison...", *player.username);
                gotoligcol(29, 15);
                printf("LANCER TOUR JOUEUR SUIVANT");
            }
        }
    } else if (choix == 2) {
        home();
    }
}

void tourJoueur(joueur player) {
    int choix = 0;
    if (player.position == 30) {
        tourPrison(player);
    } else {
        tourNormal(player, false);

        gotoligcol(27, 15);
        Color(15, 2);
        printf("%s rejoue, il a fait un double :", *player.username);
        scanf("%d", &choix);
    }
}

void skip() {  // saute 50 lignes
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}

void afficherJoueurPlateau() {
    int posJoueur[4] = {5, 12, 28, 12};

    // joueur joueurs[], terrain terrains[]

    /*for (int i = 0; i < 4; i++) {
        posJoueur[i] = joueurs[i].position;
    }*/

    int pos1 = posJoueur[0], pos2 = posJoueur[1], pos3 = posJoueur[2], pos4 = posJoueur[3];

    int nbPos1 = 0, nbPos2 = 0, nbPos3 = 0, nbPos4 = 0;

    int currentPos;

    for (int i = 0; i < 4; i++) {
        currentPos = posJoueur[i];

        if (currentPos = pos1) {
            nbPos1++;
        } else if (currentPos = pos2) {
            nbPos2++;
        } else if (currentPos = pos3) {
            nbPos3++;
        } else if (currentPos = pos4) {
            nbPos4++;
        }
    }

    printf("%d - %d - %d - %d", nbPos1, nbPos2, nbPos3, nbPos4);
}

int main() {
    clearScreen();
    home();
    // choixAvatar();
    //   creationPlateau();

    // Initialisation
    // srand(time(NULL));
    // home();
    return 0;
}