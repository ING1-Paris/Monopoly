#include <stdio.h>
#include <conio.h>


int main() {
    while (1) {
        if (kbhit()) {
            printf("%d\n",getch());
        }
    }
}