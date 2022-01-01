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

void test1() {
    while (1) {
        int key;
        if (kbhit()) {
            key = getch();
            do {
                key = getch();
            } while (key == 224);
            switch (key) {
                case 113:
                    printf("quit");
                    exit(0);
                    break;
                case 72:
                    printf("up");
                    break;
                case 75:
                    printf("left");
                    break;
                case 77:
                    printf("right");
                    break;
                case 80:
                    printf("down");
                    break;
            }
            printf("%d\n", key);
        }
    }
}

void test2() {
    char c;
    printf(
        "Ce programme indique les codes des touches du clavier "
        "generes par la commande getch()\n"
        "Un appui sur la touche 'Q' termine le programme\n");

    do {
        printf("Appuyez sur une touche du clavier: ");

        /* On récupère le code de la touche genere par getch() */
        c = getch();

        /* Si c'est une touche "classique" */
        if (c != 0 && c != -32)
            printf("code : %i\n", c);

        /* Dans le cas d'une touche spéciale */
        else {
            printf("Touche speciale : %i\t", c);
            /* On rappelle getch() pour récupérer le code de la touche */
            c = getch();
            printf("code : %i\n", c);
        }
    } while (c != 'Q');

}

int main() {
    test2();
    return 0;
}