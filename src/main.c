#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

struct Player {
    int id;             // Player's ID from 1 to 4
    long balance;       // Balance of the player
    char username[10];  // Username of the player
    int position;       // ID of the player's current cell
    int ownedField[26]; // ID of each owned fields
    int luckCard[10];   // ID of possessed luck card
    int comCard[10];    // ID of possessed community card
    bool inJail;        // True if the player is in jail, false if not
    bool bankruptcy;    // True if the player is in bankruptcy, false if not
};

struct Field {
    int id;             // Field's ID from 1 to 26
    long defaultPrice;  // Field's initial price
    long currentPrice;  // Field's current price after mark-up
    int buildings;      // Amount of buildings in the field
    bool owned;         // True if owned, False if not
    int ownedBy;        // 0 if not owned

};

int main() {
    printf("Numero 1");

    testFunction();

    printf("\n");
    return 0;
}