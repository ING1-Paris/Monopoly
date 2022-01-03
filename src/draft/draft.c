#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void afficherJoueurPlateau() {
    int posJoueur[4] = {5, 5, 12, 12};

    // joueur joueurs[], terrain terrains[]

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

    
}

int main() {
    afficherJoueurPlateau();
}