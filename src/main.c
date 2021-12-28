#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#if defined(__WIN32__)
    #include <windows.h>
#endif

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

int creationDesJoueurs(int nombreDeJoueurs) {

    int emptyCard[10];
    int emptyField[26];

    char pseudoJ1[10];
    char pseudoJ2[10];

    fgets(pseudoJ1, 10, stdin);
    fgets(pseudoJ2, 10, stdin);

    struct Joueur j1 = {1, 1500, pseudoJ1, 0, 0, emptyField, emptyCard, emptyCard, false, false};
    struct Joueur j2 = {1, 1500, pseudoJ2, 0, 0, emptyField, emptyCard, emptyCard, false, false};

    return 0;
}

int main() {
    //Initialisation
        srand(time(NULL));

    //Tests
        lancerDe();
        creationDesJoueurs(2);

        printf("\n");
        return 0;
}