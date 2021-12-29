#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#if defined(__WIN32__)
    #include <windows.h>
#endif*

struct Joueur {
    int id;             // Player's ID from 1 to 4
    long balance;       // Balance of the player
    char username[10];  // Username of the player
    int position;       // ID of the player's current cell
    int cellType;       // Type of the player's current cell
    int ownedField[26]; // ID of each owned fields
    int luckCard[10];   // ID of possessed luck card
    int comCard[10];    // ID of possessed community card
    bool inJail;        // True if the player is in jail, false if not
    bool bankruptcy;    // True if the player is in bankruptcy, false if not
};

struct Terrain {
    int id;             // Field's ID from 0 to 25
    long defaultPrice;  // Field's initial price
    long currentPrice;  // Field's current price after mark-up
    int buildings;      // Amount of buildings in the field
    bool owned;         // True if owned, False if not
    int ownedBy;        // 0 if not owned

};


int lancerDe() {
    //Retourne un nombre pseudo aléatoire en 1 et 6
    int nb;
    const int min = 1, max = 6;
    nb = (rand()%max) + min;
    printf("%d", nb);
    return nb;
}

int completeType() {
    return 0;
}

void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void gotoligcol( int lig, int col ) {
    // ressources
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

void creationCase (char titre[15], int x, int y, int couleur, char mode){
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
    bord = (12-longueur)/2;
    Color(0,couleur);
    if (mode == 'h'){
        limite = 2;
    }
    else if (mode == 'v'){
        limite = 1;
    }
    for (int i = 0; i<limite; i++){
        gotoligcol(i+x, y);
        for (int j = 0; j<12; j++){
            printf(" ");
        }
        printf("\n");
    }
    gotoligcol(x+limite,y);
    for (int k = 0; k<bord; k++){
        printf(" ");
    }
    gotoligcol(x+limite,y+bord);
    printf(titre);
    gotoligcol(x+limite,y+bord+longueur);
    for(int z=y+bord+longueur; z<y+12; z++){
        printf(" ");
    }
    for (int i = 0; i<limite; i++){
        gotoligcol(i+x+limite+1, y);
        for (int j = 0; j<12; j++){
            printf(" ");
        }
        printf("\n");
    }
    Color(15,0);
}

void plateau(){
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

int creationDesJoueurs(int nombreDeJoueurs) {

    int emptyCard[10];
    int emptyField[26];

    char pseudoJ1[10];
    char pseudoJ2[10];

    fgets(pseudoJ1, 10, stdin);
    printf("\n");
    fgets(pseudoJ2, 10, stdin);
    printf("\n");

    struct Joueur j1 = {1, 1500, pseudoJ1, 0, 0, emptyField, emptyCard, emptyCard, false, false};
    struct Joueur j2 = {1, 1500, pseudoJ2, 0, 0, emptyField, emptyCard, emptyCard, false, false};

    printf("\n");

    printf("Pseudo joeur 1 : %s", j1.username);
    printf("Pseudo joeur 2 : %s", j2.username);

    return 0;
}

void home(){
    gotoligcol(0,0);
    printf("MONO            POLY  	     MONOPOLY	      MONO	  PO   	     MONOPOLY         MONOPOLYMONO           MONOPOLY         MO          MO        NO");
    printf("\nPOLYMONO    MONOPOLY	    NO      MO        NOPO        NO        NO      MO        NO         PO         NO      MO        NO           NO      MO");
    printf("\nMONOPOLY    POLYMONO	   PO	     NO       PO  MO      MO       PO        NO       PO          LY       PO        NO       PO            PO    LY");
    printf("\nPOLY	MONO	POLY	  LY	      PO      LY  NO      LY      LY          PO      LY          MO      LY          PO      LY             LY  PO");
    printf("\nMONO	POLY	MONO     MO            LY     MO    PO    PO     MO            LY     MO         NO      MO            LY     MO              MONO");
    printf("\nPOLY		POLY	NO		MO    NO    LY	  NO    NO              MO    NOPONOMOLYPO      NO              MO    NO               NO");
    printf("\nMONO		MONO	 PO	       NO     PO      MO  MO     PO            NO     PO                 PO            NO     PO               PO");
    printf("\nPOLY		POLY	  LY	      PO      LY      NO  LY      LY          PO      LY                  LY          PO      LY               LY");
    printf("\nMONO		MONO	   MO	     LY       MO        POPO       MO        LY       MO                   MO        LY       MO               MO");
    printf("\nPOLY		POLY 	    NO      MO        NO        LYNO        NO      MO        NO                    NO      MO        NO               NO");
    printf("\nMONO		POLY	     POLYMONO         PO          MO         POLYMONO         PO                     POLYMONO         POLYMONOPOLY     LY");
    gotoligcol(10, 5);
    printf("1-Lancer une nouvelle partie");
    gotoligcol(10, 35);
    printf("2-Sauvegarder la partie");
    gotoligcol(10, 65);
    printf("3-Charger une ancienne partie");
    gotoligcol(14, 25);
    printf("4-Consulter les regles");
    gotoligcol(14, 61);
    printf("5-Credits");
    gotoligcol(14, 84);
    printf("6-Quitter la partie");
}

int main() {
    for (int i = 0; i < 50; i++)
    {
        printf("\n");
    }
    plateau();
    //Initialisation
    //srand(time(NULL));
    //home();
    //Tests
    lancerDe();
    creationDesJoueurs(2);

    printf("\n");
    return 0;
}