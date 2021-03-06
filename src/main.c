#include "lib.h"

#define DEBUG_WAIT 1  // Set to 0 to disable loading

//#if defined(__WIN32__)  // Needed to disable intellisense on macOS
void gotoligcol(int lig, int col) {
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
}

void Color(int couleurDuTexte, int couleurDeFond) {  // fonction d'affichage de couleurs
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}
void showCursor(bool show) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = show;
    SetConsoleCursorInfo(consoleHandle, &info);
}
//#endif

void clearScreen() {  // permet de clear la console
    system("cls");
}

int lancerDe() {
    // Retourne un nombre pseudo aléatoire en 1 et 6
    int nb;
    const int min = 1, max = 6;
    nb = (rand() % max) + min;
    return nb;
}

<<<<<<< Updated upstream
int creerPiocheCommu() // création de la pioche des cartes communauté
{
=======
int pioche() {
>>>>>>> Stashed changes
    srand(time(NULL));
    int nb = 0;
    int compteur = 0;
    int pioche[16];
<<<<<<< Updated upstream
    for (int i = 0; i< 16; i++)
    {
=======
    for (int i = 0; i <= 16; i++) {
>>>>>>> Stashed changes
        pioche[i] = 0;
    }
    FILE* pf = fopen("data/piocheCommu.txt", "w");
    if (pf == NULL)
    {
        printf("Erreur d'ouverture de fichier.");
    }
    else
    {
        for (int i = 0; i< 16; i++)
        {
            do
            {
                compteur = 0;
                nb = (rand() % 16) + 1;
                for(int j = 0; j <16; j++)
                {
                    if (pioche[j] == nb)
                    {
                        compteur += 1;
                    }
                }
                if (compteur == 0)
                {
                pioche[i]= nb;
                }
            }while (pioche[i] == 0);
            fprintf(pf, "%d ",pioche[i]);
        }
    }
    fclose(pf);
    pf = NULL;
    return 0;
}
int creerPiocheChance() // création de la pioche des cartes chance
{
    srand(time(NULL));
    int nb = 0;
    int compteur = 0;
<<<<<<< Updated upstream
    int pioche[16];
    for (int i = 0; i<= 16; i++)
    {
        pioche[i] = 0;

    }
    FILE* pf = fopen("data/piocheChance.txt", "w");
    if (pf == NULL)
    {
        printf("Erreur d'ouverture de fichier.");
    }
    else
    {
        for (int i = 0; i< 16; i++)
        {
            do
            {
                compteur = 0;
                nb = (rand() % 16) + 1;
                for (int j = 0; j <16; j++)
                {
                    if (pioche[j] == nb)
                    {
                        compteur += 1;
                    }
                }
                if (compteur == 0)
                {
                pioche[i]= nb;
                }
            }while (pioche[i] == 0);
        }
=======
    for (int i = 0; i < 16; i++) {
        do {
            compteur = 0;
            nb = (rand() % 16) + 1;
            for (int j = 0; j < 16; j++) {
                if (pioche[j] == nb) {
                    compteur += 1;
                }
            }
            if (compteur == 0) {
                pioche[i] = nb;
            }
        } while (pioche[i] == 0);
>>>>>>> Stashed changes
    }
    fclose(pf);
    pf = NULL;
    return 0;
}

<<<<<<< Updated upstream
void showLogo() { // affichage du logo monopoly
=======
void showLogo() {
>>>>>>> Stashed changes
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

void display() { // affichage du logo, avec un clearScreen avant
    clearScreen();
    showLogo();
}

void animation(int y, int x, int ms, int lenght) { // création d'une animation d'une barre de chargement
    int i;
    showCursor(false);
    gotoligcol(y, x);
    printf("|");
    for (i = 0; i < lenght; i++) {
        printf("-");
    }
    printf("|");
    gotoligcol(y, x + 1);
    for (int i = 0; i < lenght; i++) {
        printf("#");
        if (DEBUG_WAIT) {
            Sleep(ms);
        }
    }
    showCursor(true);
}

void clearCoords(int xA, int yA, int xB, int yB) {  // permet de clear une zone via ses coordonnées
    Color(0, 0);
    gotoligcol(yA, xA);
    for (int i = 0; i < yB - yA; i++) {
        gotoligcol(yA + i, xA);
        for (int j = 0; j < xB - xA; j++) {
            printf(" ");
        }
        printf("\n");
    }
    Color(15, 0);
}

void creationCase(char titre[15], int x, int y, int id, int couleur) {  // fonction de création des cases
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
    bord = (13 - longueur) / 2;
    Color(0, couleur);
    gotoligcol(x, y);
    if (id == 0) {
        for (int j = 0; j < 13; j++) {
            printf(" ");
        }
    } else {
        if (id < 10) {
            for (int i = 0; i < 6; i++) {
                printf(" ");
            }
            printf("%d", id);
            for (int a = 0; a < 6; a++) {
                printf(" ");
            }
        } else {
            for (int i = 0; i < 5; i++) {
                printf(" ");
            }
            printf("%d", id);
            for (int a = 0; a < 6; a++) {
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
    for (int z = y + bord + longueur; z < y + 13; z++) {
        printf(" ");
    }
    for (int n = 0; n < 3; n++) {
        gotoligcol(x + 2 + n, y);
        for (int j = 0; j < 13; j++) {
            printf(" ");
        }
        printf("\n");
    }
    Color(15, 0);
}

void batiments(terrain album) {  // fonction qui affiche les maisons/hôtels
    int nbBats = 0;
    nbBats = album.buildings;
    Color(0, album.couleur);
    if (album.hotel == true) {
        gotoligcol(album.x + 4, album.y + 9);
        printf("%c", 0xB2);
    } else {
        switch (nbBats) {
            case 1:
                gotoligcol(album.x + 4, album.y + 12);
                printf("%c", 0x7F);
                break;
            case 2:
                gotoligcol(album.x + 4, album.y + 10);
                printf("%c %c", 0x7F, 0x7F);
                break;
            case 3:
                gotoligcol(album.x + 4, album.y + 8);
                printf("%c %c %c", 0x7F, 0x7F, 0x7F);
                break;
            case 4:
                gotoligcol(album.x + 4, album.y + 6);
                printf("%c %c %c %c", 0x7F, 0x7F, 0x7F, 0x7F);
                break;
        }
    }
}

void terrainAchete(joueur *players, terrain album) {  // vérifie si un terrain est occupé pour afficher son proprio à la place de son prix de base
    int longueur = 0;
    Color(0, album.couleur);
    if (album.owned == true) {
        for (int i = 0; i < 4; i++) {
            if (album.ownedBy == players[i].id) {
                longueur = (13 - strlen(players[i].username)) / 2;
                gotoligcol(album.x + 3, album.y + longueur);
                printf("%s", players[i].username);
            }
        }
    } else {
        if (album.defaultPrice >= 100) {
            gotoligcol(album.x + 3, album.y + 4);
        } else {
            gotoligcol(album.x + 3, album.y + 5);
        }
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

void ifFaillite (joueur** listePlayers){  // fonction vérifiant si un joueur est en faillite
    for (int i = 0; i < 4; i++){
        if (listePlayers[i]->balance <= 0 && listePlayers[i]->ownedField[0] == 0){
            listePlayers[i]->bankruptcy = true;
        }
    }
}

bool finDuJeu(joueur* listePlayers, int nbJoueurs){ // fonction vérifiant si les joueurs sont en faillite ou non
    gotoligcol(25, 60);                             // on renvoie true si le jeu est fini, false si non
    switch(nbJoueurs){
        case 2 : 
        if (listePlayers[0].bankruptcy == true){
            printf("Le joueur 2 remporte la victoire !");
            animation(26, 65, 500, 15);
            return true;
        } else if (listePlayers[1].bankruptcy == true){
            printf("Le joueur 1 remporte la victoire !");
            animation(26, 65, 500, 15);
            return true;
        }
        break;

        case 3 : 
        if (listePlayers[0].bankruptcy == true && listePlayers[1].bankruptcy == true){
            printf("Le joueur 3 remporte la victoire !");
            animation(26, 65, 500, 15);
            return true;
        } else if (listePlayers[1].bankruptcy == true && listePlayers[2].bankruptcy == true){
            printf("Le joueur 1 remporte la victoire !");
            animation(26, 65, 500, 15);
            return true;
        } else if (listePlayers[0].bankruptcy == true && listePlayers[2].bankruptcy == true){
            printf("Le joueur 2 remporte la victoire !");
            animation(26, 65, 500, 15);
            return true;
        }
        break;

        case 4 :
        if (listePlayers[0].bankruptcy == true && listePlayers[1].bankruptcy == true && listePlayers[2].bankruptcy == true){
            printf("Le joueur 4 remporte la victoire !");
            animation(26, 65, 500, 15);
            return true;
        } else if (listePlayers[1].bankruptcy == true && listePlayers[2].bankruptcy == true && listePlayers[3].bankruptcy == true){
            printf("Le joueur 1 remporte la victoire !");
            animation(26, 65, 500, 15);
            return true;
        } else if (listePlayers[0].bankruptcy == true && listePlayers[1].bankruptcy == true && listePlayers[3].bankruptcy == true){
            printf("Le joueur 3 remporte la victoire !");
            animation(26, 65, 500, 15);
            return true;
        } else if (listePlayers[0].bankruptcy == true && listePlayers[2].bankruptcy == true && listePlayers[3].bankruptcy == true){
            printf("Le joueur 2 remporte la victoire !");
            animation(26, 65, 500, 15);
            return true;
        }
    }
    return false;
}

void acheterTerrainJ(joueur *currentplayer, terrain album) {  // fonction d'achat d'un terrain --> partie joueur
    int i = 0;
    (currentplayer)->balance -= album.defaultPrice;
    while ((currentplayer)->ownedField[i] != 0) {
        i++;
    }
    currentplayer->ownedField[i] = album.id;
    gotoligcol(32, 15);
    printf("Terrain achete : %s  -  %d", album.nom, album.id);
    Sleep(500);
}

void updateTour(terrain *listeTerrain, joueur **listePlayers, box *listeCases, int currentPlayer, int nbJoueurs) { // fonction qui affiche le terrain à nouveau, avec les changements
    joueur *player = listePlayers[currentPlayer];
    clearScreen();
    gotoligcol(6, 15);
    printf("Solde du joueur %s : %d%c", (player)->username, (player)->balance, 0x24);
    plateauGraphique(listeTerrain);
    afficherJoueurPlateau(listePlayers, listeTerrain, listeCases, nbJoueurs);
    for (int n = 0; n < 22; n++) {
        terrainAchete(*listePlayers, listeTerrain[n]);
        ifHypotheque(listeTerrain[n]);
        batiments(listeTerrain[n]);
    }
}

void acheterTerrainT(joueur *currentplayer, terrain *album) {  // fonction d'achat d'un terrain --> partie terrain
    album->owned = true;
    album->ownedBy = currentplayer->id;
}

void acheterMaisonT(joueur *currentplayer, terrain *album) {  // fonction d'achat d'une maison --> partie terrain
    if (album->buildings == 4){
        album->hotel = true;
    } else {
        album->buildings += 1;
    }
}

void acheterMaisonJ(joueur *currentplayer, terrain album) {  // fonction d'achat d'une maison --> partie joueur
    currentplayer->balance -= album.housePrice;
}

<<<<<<< Updated upstream
void vendreMaisonJ(joueur *currentplayer, terrain album, int nbMaisons) { // fonction de vente d'une maison -> partie joueur
    if (album.hotel == true){
        currentplayer->balance += (album.housePrice)/2;
    }
    currentplayer->balance += (album.housePrice)/2;
}

int vendreMaisonJ2(terrain album, int nbMaisons) { // fonction de vente d'une maison -> partie joueur / partie 2
    int argentFait = 0;
    if (album.hotel == true){
        argentFait += (album.housePrice/2);
    }
    argentFait += ((album.housePrice)/2)*nbMaisons;
    return argentFait;
}

void vendreMaisonT(joueur *currentplayer, terrain* album, int nbMaisons) { // vente maisons -> partie terrain
    if (album->hotel == true){
        album->hotel = false;
    }
    album->buildings -= nbMaisons;
}

void hypothequerTerrainT(joueur *currentplayer, terrain* listeAlbums, terrain album) { // hypothèque d'un terrain -> partie terrain
    int couleurAlbum = album.couleur;
    for (int i=0; i<22; i++){
        if (listeAlbums[i].couleur == couleurAlbum){
            if (listeAlbums[i].ownedBy == currentplayer->id && listeAlbums[i].buildings > 0){
                vendreMaisonT(currentplayer, &listeAlbums[i], listeAlbums[i].buildings);
                vendreMaisonJ(currentplayer, listeAlbums[i], listeAlbums[i].buildings);
            }
        }
    }
    album.hypotheque = true;
}

void hypothequerTerrainJ(joueur *currentplayer, terrain album){ // hypothèque d'un terrain -> partie joueur
    vendreMaisonJ(currentplayer, album, album.buildings);
    currentplayer->balance += album.val_hypoth;
}

int hypothequerTerrain2 (terrain album){ // hypothèque d'un terrain -> partie renvoi argent
    int argentFait = 0;
    argentFait += album.val_hypoth;
    return argentFait;
}

void leverHypotheque(joueur *currentplayer, terrain album){ // lever l'hypothèque
    if (album.hypotheque == true){
        currentplayer->balance -= album.val_hypoth+(album.val_hypoth*10/100);
    }
}

int compterArgent(joueur* currentPlayer, terrain* listeTerrain){ //fonction qui est censée compter l'argent total du joueur
    int argentTotal, compteur, idTerrain = 0;                    //en comptant l'argent que rapporte la vente 
    argentTotal += currentPlayer->balance;
    joueur pcurrentplayer = *currentPlayer;

    for (int i = 0; i < 26; i++){
        if (pcurrentplayer.ownedField[i] != 0){
            compteur += 1;
            printf("%d", compteur);
        }
    }
    for (int j=0; j<compteur; j++){
        idTerrain = pcurrentplayer.ownedField[j];
        argentTotal += vendreMaisonJ2(listeTerrain[idTerrain], listeTerrain[idTerrain].buildings);
        printf("%d", argentTotal);
        argentTotal += hypothequerTerrain2(listeTerrain[idTerrain]);
        printf("%d", argentTotal);
    }
    return argentTotal;
}

void faillite(joueur *currentplayer, terrain *listeTerrain, int sommeApayer){
    int argentRestant, i, venteTotale = 0;
    argentRestant = compterArgent(currentplayer, listeTerrain);
    printf("%d", argentRestant);
    printf("%d", argentRestant);
    printf("%d", argentRestant);
    printf("%d", argentRestant);
    printf("%d", argentRestant);
    Sleep(1000);
    if (argentRestant > sommeApayer){
        while (venteTotale < sommeApayer){
            venteTotale += vendreMaisonJ2(listeTerrain[i], listeTerrain[i].buildings);
            venteTotale += hypothequerTerrain2(listeTerrain[i]);
            hypothequerTerrainJ(currentplayer, listeTerrain[i]);
            hypothequerTerrainT(currentplayer, listeTerrain, listeTerrain[i]);
            i++;
        }
        currentplayer->balance += venteTotale;
    } else if (argentRestant < sommeApayer){
        currentplayer->balance = 0;
        printf("%s n'a pas assez d'argent, il est hors course !", currentplayer->username);
    }
}

void tourComplet(joueur* player){ // fonction qui repère si le joueur a fait un tour complet
    if (player->position >= 40){
=======
void tourComplet(joueur *player) {  // fonction qui repère si le joueur a fait un tour complet
    if (player->position >= 40) {
>>>>>>> Stashed changes
        player->position -= 40;
        player->balance += 200;
    }
}

void acheterCarteSortie(joueur* detenteur, joueur* enprison){
    int montant = 0;
    char choix[10];
    gotoligcol(20,15);
    do{printf("%s, saisissez le prix voulu pour la carte : ", detenteur->username);
    scanf("%d", &montant);}while(montant < 0);
    gotoligcol(21,15);
    do{printf("%s, acceptez-vous de payer ce prix ? Tapez 'Oui' ou 'Non' : ");
    scanf("%s", choix);}while(choix != "Oui" && choix != "Non");
    if (choix == "Oui"){
        enprison->balance -= montant;
        enprison->sortiePrison = true;
        detenteur->balance += montant;
        detenteur->sortiePrison = false;
    }
}

int argentPaye(joueur *currentplayer, terrain album) {  // fonction de paiement du loyer --> partie 1
    int loyerA, nbMaisons = 0;                          // on récupère le montant dû ici
    nbMaisons = album.buildings;
    switch (nbMaisons) {
        case 0:
            loyerA = album.loyer;
            break;
        case 1:
            loyerA = album.loyermaison1;
            break;
        case 2:
            loyerA = album.loyermaison2;
            break;
        case 3:
            loyerA = album.loyermaison3;
            break;
        case 4:
            if (album.hotel == true) {
                loyerA = album.loyerhotel;
            } else {
                loyerA = album.loyermaison4;
            }
    }
    return loyerA;
}

void payerLoyerJ1(joueur *currentplayer, int loyer) {  // fonction de paiement du loyer --> partie 2
    currentplayer->balance -= loyer;                   // le joueur tombé sur la case perd l'argent
}
void toucherLoyerJ2(joueur *currentplayer, int loyer) {  // fonction de paiement du loyer --> partie 3
    currentplayer->balance += loyer;                     // le propriétaire du terrain touche l'argent
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
    creationCase("Chance", 0, 26, 0, couleurCaseNeutre);
    creationCase("Zenith", 0, 65, 0, couleurCaseNeutre);
    creationCase("Sacem", 0, 104, 0, couleurCaseNeutre);
    creationCase("Drama", 0, 130, 0, couleurCaseNeutre);
    creationCase("Communaute", 15, 130, 0, couleurCaseNeutre);
    creationCase("Zenith", 25, 130, 0, couleurCaseNeutre);
    creationCase("Chance", 30, 130, 0, couleurCaseNeutre);
    creationCase("Sacem", 40, 130, 0, couleurCaseNeutre);

    creationCase("DEPART", 50, 130, 0, couleurCaseNeutre);
    creationCase("Chance", 50, 39, 0, couleurCaseNeutre);
    creationCase("Zenith", 50, 65, 0, couleurCaseNeutre);
    creationCase("Sacem", 50, 78, 0, couleurCaseNeutre);
    creationCase("Communaute", 50, 104, 0, couleurCaseNeutre);
}

box *creationBox() {
    box *listeCase = (box *)malloc(40 * sizeof(box));

    box tempBox;

    char *name[20];

    for (int i = 0; i < 40; i++) {
        FILE *texte = NULL;
        char ignore[1024];
        int donnee[3];

        listeCase[40];

        texte = fopen("data/board.txt", "r");
        if (texte == NULL) {
            printf("Error: Cannot open");
        }
        for (int j = 0; j < i; j++) {
            fgets(ignore, sizeof(ignore), texte);
        }
        fscanf(texte, "%d;%d;%d;%c", &donnee[0], &donnee[1], &donnee[2], &name);

        // tempBox = {donnee[0], donnee[1], donnee[2], (char)i};

        tempBox.id = donnee[0];
        tempBox.x = donnee[1];
        tempBox.y = donnee[2];

        listeCase[i] = tempBox;
    }

    return listeCase;
}

terrain *creationTerrain() {  // création d'une instance (un album)
    terrain *listeTerrain = (terrain *)malloc(23 * sizeof(terrain));

    terrain instance;

    char *listeNomTerrain[22] = {"Racine Carree", "Brol", "Absolution", "Plat.Collec", "Nevermind", "RAM", "One More Love",
                                 "Discovery", "MMLP", "NWTS", "Eminem Show", "Or Noir", "Ouest Side", "Civilisation", "Unorth.Juke",
                                 "After Hours", "Thriller", "DLL", "Trinity", "JVLIVS", "Ipseite", "Cyborg"};

    for (int i = 0; i < 22; i++) {
        char *nomCurrent = listeNomTerrain[i];

        FILE *texte = NULL;
        char ignore[1024];
        int donnee[15];
        char proprio[10];
        texte = fopen("data/fields.txt", "r");
        if (texte == NULL) {
            printf("Error: Cannot open");
        }
        for (int j = 0; j < i; j++) {
            fgets(ignore, sizeof(ignore), texte);
        }
        fscanf(texte, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &donnee[0], &donnee[1], &donnee[14],
               &donnee[2], &donnee[3], &donnee[4], &donnee[5], &donnee[6], &donnee[7],
               &donnee[8], &donnee[9], &donnee[10], &donnee[11], &donnee[12], &donnee[13], &donnee[15]);

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
        instance.val_hypoth = donnee[9];
        instance.buildings = donnee[10];
        instance.x = donnee[11];
        instance.y = donnee[12];
        instance.couleur = donnee[13];
        instance.ownedBy = donnee[15];
        instance.owned = false;
        instance.hotel = false;
        instance.hypotheque = false;

        listeTerrain[i] = instance;
    }

    return listeTerrain;
}

int choixAvatar(int nbJoueurs, int currentPlayer, int *numAvatar) {
    bool end = false;
    int av;
    int key, c;
    int avatar[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0B, 0x0C, 0x0E, 0x0F};
    int avatarUtilise[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int selection = 0;
    int useAvatar = 0;
    showCursor(false);
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
                    clearCoords(5,15,50,16);
                    useAvatar = 0;
                    break;

                case 77:
                    if (selection < 9) {
                        selection++;
                    }
                    printf("%c", avatar[selection]);
                    clearCoords(5,15,50,16);
                    useAvatar = 0;
                    break;
                case 13:
                        for (int j = 0; j < 4; j++) {
                            if (avatar[selection] == numAvatar[j]) {
                                useAvatar += 1;
                            }
                    }
                    if (useAvatar > 0) {
                        gotoligcol(15,5);
                        printf("Impossible, cet avatar est deja utilise.");
                        useAvatar = 0;
                    } else {end = true;}
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

    showCursor(true);

    return avatar[selection];
}

joueur *creationDesJoueurs(int nombreDeJoueurs) {
    int emptyCard[10];
    int emptyField[26];
    char pseudo[10];
    //int *avatarUtilise = (int *)calloc(4, sizeof(int));
    int avatarUtilise[4] = {0, 0, 0, 0};

    joueur *listeJoueurs = (joueur *)malloc(4 * sizeof(joueur));

    joueur tempJ1 = {1, 1500, "NULL", -1, {0}, false, false, false, false, 0, 0, 0};
    joueur tempJ2 = {2, 1500, "NULL", -1, {0}, false, false, false, false, 0, 0, 0};
    joueur tempJ3 = {3, 1500, "NULL", -1, {0}, false, false, false, false, 0, 0, 0};
    joueur tempJ4 = {4, 1500, "NULL", -1, {0}, false, false, false, false, 0, 0, 0};

    listeJoueurs[0] = tempJ1;
    listeJoueurs[1] = tempJ2;
    listeJoueurs[2] = tempJ3;
    listeJoueurs[3] = tempJ4;

    for (int i = 0; i < nombreDeJoueurs; i++) {
        display();
        printf("Entrez le nom du joueur %d (10 caracteres maximum): ", i + 1);
        scanf("%s", pseudo);
        while (strlen(pseudo) > 10) {
            printf("\nImpossible, le pseudo doit avoir moins de 10 caracteres :\n>> ");
            fflush(stdin);
            scanf("%s", pseudo);
        }
        strcpy(listeJoueurs[i].username, pseudo);
        listeJoueurs[i].avatar = choixAvatar(nombreDeJoueurs, 1, avatarUtilise);
        avatarUtilise[i] = listeJoueurs[i].avatar;
        listeJoueurs[i].position = 0;
    }

    display();
    gotoligcol(14, 0);

    for (int i = 0; i < nombreDeJoueurs; i++) {
        printf("Pseudo et avatar du joueur %d : %s  -  %c\n", i + 1, listeJoueurs[i].username, listeJoueurs[i].avatar);
    }

    printf("\nChargement de la partie en cours");

    animation(20, 0, 75, 50);

    //free(avatarUtilise);

    return listeJoueurs;
}

int demanderNbJoueurs() {  // fonction demandant et renvoyant le nombre de joueurs
    int nbJoueur = 0;
    display();
    printf("Veuillez entrer le nombre de joueurs (entre 2 et 4 inclus) : ");
    scanf("%d", &nbJoueur);
    while ((nbJoueur != 2) && (nbJoueur != 3) && (nbJoueur != 4)) {
        printf("\nLa valeur saisie est invalide (entre 2 et 4 inclus) :\n>> ");
        fflush(stdin);
        scanf("%d", &nbJoueur);
    }
    return nbJoueur;
}

void home() {  // menu principal du jeu
    int choice = 0;

    clearScreen();
    showLogo();

    gotoligcol(14, 23);
    Color(15, 2);
    printf("1-Lancer une nouvelle partie");
    gotoligcol(14, 60);
    Color(15, 3);
    printf("2-Sauvegarder la partie");
    gotoligcol(14, 93);
    Color(15, 4);
    printf("3-Charger une ancienne partie");
    gotoligcol(16, 33);
    Color(15, 9);
    printf("4-Consulter les regles");
    gotoligcol(16, 67);
    Color(15, 12);
    printf("5-Credits");
    gotoligcol(16, 89);
    Color(15, 8);
    printf("6-Quitter le jeu");

    gotoligcol(19, 0);
    Color(15, 0);

    printf("--> Que choisissez-vous de faire ? Tapez un chiffre : ");
    fflush(stdin);
    scanf("%d", &choice);

    while ((choice != 1) && (choice != 2) && (choice != 3) && (choice != 4) && (choice != 5) && (choice != 6)) {
        printf("\nVotre saisie (%d) n'est pas valide. Valeur attendue : 1, 2, 3, 4, 5 ou 6.\nVeuillez entrer un chiffre a nouveau >> ", choice);
        fflush(stdin);
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

void homeInGame(joueur **listePlayers, joueur *currentplayer, terrain *listeTerrain, int nbJoueurs, bool rejouer, int nbTours) {
    int choice = 0;  // 2e menu principal, celui auquel on accède via la partie (différence : sauvegarde)

    clearScreen();
    showLogo();

    gotoligcol(14, 23);
    Color(15, 2);
    printf("1-Lancer une nouvelle partie");
    gotoligcol(14, 60);
    Color(15, 3);
    printf("2-Sauvegarder la partie");
    gotoligcol(14, 93);
    Color(15, 4);
    printf("3-Charger une ancienne partie");
    gotoligcol(16, 33);
    Color(15, 9);
    printf("4-Consulter les regles");
    gotoligcol(16, 67);
    Color(15, 12);
    printf("5-Credits");
    gotoligcol(16, 89);
    Color(15, 8);
    printf("6-Quitter le jeu");

    gotoligcol(19, 0);
    Color(15, 0);
    printf("--> Que choisissez-vous de faire ? Tapez un chiffre : ");
    fflush(stdin);
    scanf("%d", &choice);

    while ((choice != 1) && (choice != 2) && (choice != 3) && (choice != 4) && (choice != 5) && (choice != 6)) {
        gotoligcol(20, 0);
        printf("Votre saisie (%d) n'est pas valide. Veuillez entrer un chiffre a nouveau : \n", choice);
        fflush(stdin);
        scanf("%d", &choice);
    }

    switch (choice) {
        case 1:
            clearScreen();
            newGame();
            break;
        case 2:
            faireSauvegarde(listePlayers, currentplayer, listeTerrain, nbJoueurs, rejouer, nbTours);
            gotoligcol(21, 0);
            printf("La partie a ete sauvegarde !");
            Sleep(2000);
            homeInGame(listePlayers, currentplayer, listeTerrain, nbJoueurs, rejouer, nbTours);
            break;
        case 3 :
            chargerSauvegarde();
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

void infoAlbum(terrain field) {  // fonction affichant toutes les infos d'un album
    int revenir = 0;
<<<<<<< Updated upstream
    clearCoords(15,22,90,33);
=======
    clearCoords(15, 22, 90, 32);
>>>>>>> Stashed changes
    gotoligcol(23, 20);
    printf("Album : %s", field.nom);
    gotoligcol(24, 20);
    if (field.owned == true) {
        printf("L'album appartient au joueur %d", field.ownedBy);
    } else {
        printf("L'album n'appartient a personne.");
    }
    gotoligcol(25, 20);
    printf("Prix de base de l'album : %d%c", field.defaultPrice, 0x24);
    gotoligcol(26, 20);
    printf("Prix d'une certification : %d%c", field.housePrice, 0x24);
    gotoligcol(27, 20);
    printf("Disque non certifie : %d%c / ", field.loyer, 0x24);
    gotoligcol(27, 47);
    printf("Disque d'argent : %d%c", field.loyermaison1, 0x24);
    gotoligcol(28, 20);
    printf("Disque d'or : %d%c / ", field.loyermaison2, 0x24);
    gotoligcol(28, 41);
    printf("Disque de platine: %d%c", field.loyermaison3, 0x24);
    gotoligcol(29, 20);
    printf("Disque de diamant : %d%c", field.loyermaison4, 0x24);
    gotoligcol(30, 20);
    printf("Disque certifie double diamant : %d%c", field.loyerhotel, 0x24);
    gotoligcol(31, 20);
    if (field.hotel == true) {
        printf("L'album est certifie double diamant.");
    } else if (field.buildings > 0) {
        printf("L'album possede %d certifications.", field.buildings);
    } else {
        printf("L'album n'est pas certifie.");
    }
    gotoligcol(32, 20);
    printf("La valeur de la revente est estimee a %d%c", field.val_hypoth, 0x24);
    do {
        gotoligcol(33, 20);
        printf("Pour revenir au tour, appuyez sur 1 : ");
        scanf("%d", &revenir);
    } while (revenir != 1);
}

void retourMenu() {  // fonction intermédiaire pour revenir dans le menu principal
    home();
}

void retourMenuInGame(joueur **listePlayers, joueur *currentplayer, terrain *listeTerrain, int nbJoueurs, bool rejouer, int nbTours) {  // fonction intermédiaire pour revenir dans le menu principal
    homeInGame(listePlayers, currentplayer, listeTerrain, nbJoueurs, rejouer, nbTours);
}

void regles() {  // affichage des règles du jeu : exit avec lettre 'a' ; accessible via le menu principal
    int sortie;
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
    printf("\n\n 1- Banque : \nAu depart, la banque verse 1500%c a chaque joueur.\nElle verse 200%c lorsqu'un joueur passe par la case depart.", 0x24, 0x24);
    printf("\nL'argent des cartes chance et des cartes communaute sont verses a la banque.\nLorsque qu'il tombe sur la case Sacem, le joueur doit verser 200%c a la banque.", 0x24);
    printf("\n\n 2 - Des : \nSi un joueur fait un double, il a le droit de rejouer.\nSi il fait trois doubles de suite le joueur doit aller en prison.");
    printf("\n\n 3 - Prison : \nLe joueur doit aller en prison s'il fait trois doubles de suite, s'il tire une carte chance lui disant d'aller en prison ou s'il tombe sur la case DRAMA.");
    printf("\nPour sortir de prison le joueur doit faire un double lors de son tour, avoir eu une carte chance lui permettant de sortir de prison ou bien payer 50%c. Au bout de 3 tours, il est oblige de payer 50%c pour sortir.", 0x24, 0x24);
    printf("\nLorsqu'il est envoye en prison, s'il passe par la case depart, le joueur ne recoit pas l'argent qui lui est du.");
    printf("\nLes cartes Sortie de Prison et Denonciation sont utilisables qu'une seule fois par partie");
    printf("\n\n 4 - Album : \nLorsqu'un joueur tombe sur une case 'album', il :\n    - peut l'acheter s'il a l'argent necessaire pour le faire et si elle n'appartient a personne.");
    printf("\n    - peut acheter des maisons si l'emplacement est deja a lui ou acheter un hotel s'il y a deja 4 maisons sur ce terrain.\n    - doit payer un loyer si l'emplacement appartient a un adversaire.");
    printf("\n    - n'a aucun loyer a payer si la propriete appartient a un adversaire mais est hypothequee.");
    printf("\nIl peut y avoir au maximum 32 maisons et 12 hotels en meme temps dans le jeu.");
    printf("\n\n 5 - Hypotheque :\nPour qu'un joueur hypotheque une propriete, il doit vendre toutes les certifications qu'il a sur cette case et , s'il en a, les certifications sur ses proprietes de la meme couleur.");
    printf("\nPour lever le montant de l'hypotheque, un joueur doit payer a la banque le cout de l'hypotheque ainsi qu'une majoration de 10%c du prix de l'hypotheque.", 0x25);
    printf("\nUn joueur peut vendre un terrain hypotheque a un autre a un prix convenu entre eux. L'acheteur peut faire le choix de lever l'hypotheque immediatemment en payant, a la banque, le prix de l'hypotheque + 10%c ou attendre et payer lors de l'achat 10%c, a la banque, du prix convenu entre les deux joueurs a la banque puis au moment de lever l'hypotheque payer le prix ainsi que les 10%c a la banque.", 0x25, 0x25, 0x25);
    printf("\n\n 6 - Faillite :\nS'il ne peut plus payer, a la banque ou a un autre joueur, la somme qu'il leur doit, le joueur est en faillite et est elimine.");
    printf("\nIl doit donner tout ce qu'il lui reste a la personne a qui il doit de l'argent.\nLorsqu'il legue des biens hypotheques, le creancier doit immediatemment payer une taxe de 10%c a la banque, et a ensuite le choix de lever l'hypotheque immediatemment ou bien d'attendre plusieurs tours mais il devra repayer les interets a la banque.", 0x25);
    printf("\nSi le joueur doit l'argent a la banque, tous ses biens sont donnes a cette derniere.");
    
    printf("\nTapez 1 pour revenir au menu >> ");
    scanf("%d",&sortie);
    while (sortie != 1) {
        printf("\nChoix invalide >> ");
        fflush(stdin);
        scanf("%d",&sortie);
    }
    printf("REVENIR A HOME IN GAME");
    Sleep(2500);
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
    for (int i = 0; i < 9; i++) {
        gotoligcol(15 + i, 61);
        printf("|");
        gotoligcol(15 + i, 81);
        printf("|");
    }
    for (int j = 0; j < 19; j++) {
        gotoligcol(14, 61 + j + 1);
        printf("%c", 0xC4);
        gotoligcol(24, 61 + j + 1);
        printf("%c", 0xC4);
    }
    Color(15, 2);
    gotoligcol(16, 65);
    printf("Kinan Lakhdar");
    Color(15, 5);
    gotoligcol(18, 65);
    printf("Corentin Gaude");
    Color(15, 4);
    gotoligcol(20, 64);
    printf("Matthieu Testard");
    Color(15, 9);
    gotoligcol(22, 64);
    printf("Augustin Mouton");
    Color(15, 0);
    printf("\nTapez 1 pour revenir au menu >> ");
    scanf("%d",&sortie);
    while (sortie != 1) {
        printf("\nChoix invalide >> ");
        fflush(stdin);
        scanf("%d",&sortie);
    }
    retourMenu();
}

joueur doubleStreakLimite(joueur player) {
    gotoligcol(25, 15);
    printf("Envoyer le joueur en prison");
    player.position = 10;
    player.streakDouble = 0;
    return player;
}

int cartePrisonEnJeu(joueur **listePlayers) {
    for (int i = 0; i < 4; i++) {
        if (listePlayers[i]->sortiePrison == true) {
            return listePlayers[i]->id;
        } else {
            return 0;
        }
    }
}

void deplacement(joueur *player, int sommeDe) {
    gotoligcol(21, 50);
    printf("Deplacer %s de la case %d a la case %d.", player->username, player->position, (player->position + sommeDe));
    Sleep(2000);
    (player)->position += sommeDe;
}

void tourPartie2(terrain *listeTerrain, joueur **listePlayers, box *listeCases, int currentPlayer, bool rejouer, int nbJoueurs, int nbTours) {
    updateTour(listeTerrain, listePlayers, listeCases, currentPlayer, nbJoueurs);
    Color(15, 0);
    int terrainactuel, choix, proprietaire, nbMaisons, idalbum, loyer, compteur, argentRestant = 0;
    joueur *player = listePlayers[currentPlayer];
    gotoligcol(6, 120);
    printf("Tour n%c%d", 0xF8, nbTours);
    gotoligcol(6, 15);
    printf("Solde du joueur %s : %d%c", (player)->username, (player)->balance, 0x24);
    if ((player)->position == 36 || (player)->position == 7 || (player)->position == 22) {  // cases chance
        gotoligcol(26, 15);
        *player = chance(*player);
    } else if ((player)->position == 2 || (player)->position == 17 || (player)->position == 33) {  // cases communauté
        gotoligcol(26, 15);
        *player = communaute(*player, listeTerrain);
    } else if ((player)->position == 4 || (player)->position == 12 || (player)->position == 28 || (player)->position == 38) {  // cases sacem
        player->balance -= 200;
        //argentRestant = compterArgent(player, listeTerrain);
        //printf("%d", argentRestant);
        //Sleep(2000);
        //faillite(player, listeTerrain, 200);
    } else if ((player)->position == 20 || (player)->position == 0) {  // case soundcloud (stationnement libre)
        gotoligcol(26, 15);
        printf("Reposez vous bien !");
    } else if ((player)->position == 30) {  // case drama
        gotoligcol(26, 15);
        printf("A cause d'une polemique, vous etes finito ...");
        (player)->position = 10;
        player->inJail = true;
    } else if ((player)->position == 10) {  // case prison
        gotoligcol(26, 15);
        printf("Vous rendez visite a un ami en prison.");
    } else if ((player)->position == 5 || (player)->position == 15 || (player)->position == 25 || (player)->position == 35) {  // cases Zéniths
        gotoligcol(26, 15);
        printf("Case de repos.");
    } else {
        for (int i = 0; i < 22; i++) {
            if (listeTerrain[i].idOnBoard == (player)->position) {
                terrainactuel = listeTerrain[i].id - 1;  // on récupère l'ID de l'album sur lequel le joueur est
            }
        }
        nbMaisons = listeTerrain[terrainactuel].buildings;
        if (listeTerrain[terrainactuel].owned == true && listeTerrain[terrainactuel].ownedBy != (player)->id) {
<<<<<<< Updated upstream
            if (listeTerrain[terrainactuel].hypotheque == true){
                gotoligcol(25,15);
                printf("Ce terrain est hypotheque, pas besoin de payer !");
            } else {
                proprietaire = listeTerrain[terrainactuel].ownedBy;
                loyer = argentPaye(player, listeTerrain[terrainactuel]);
                gotoligcol(25, 15);
                printf("%s est chez %s !", (player)->username, listePlayers[proprietaire-1]->username);
                gotoligcol(26, 15);
                printf("%s doit lui verser %d%c", (player)->username, loyer, 0x24);
                gotoligcol(27, 15);
                if (player->balance-loyer < 0){
                    //faillite(player, listeTerrain, loyer);
                    if (player->balance == 0){
                        printf("%s cede toute sa fortune a %s", (player)->username, listePlayers[proprietaire-1]->username);
                        loyer = player->balance;
                    }
                } else {
                    payerLoyerJ1(player, loyer);
                }
                animation(28, 15, 100, 15);
                toucherLoyerJ2(listePlayers[proprietaire-1], loyer);
            }
=======
            proprietaire = listeTerrain[terrainactuel].ownedBy;
            loyer = argentPaye(player, listeTerrain[terrainactuel]);
            gotoligcol(25, 15);
            printf("%s est chez %s !", (player)->username, listePlayers[proprietaire - 1]->username);
            gotoligcol(26, 15);
            printf("%s doit lui verser %d%c", (player)->username, loyer, 0x24);
            // gotoligcol(28, 15);
            // printf("Appuyez sur 'Entree' pour continuer.");
            payerLoyerJ1(player, loyer);
            toucherLoyerJ2(listePlayers[proprietaire - 1], loyer);
>>>>>>> Stashed changes
        } else {
            gotoligcol(25, 15);
            printf("%s peut maintenant :", (player)->username);
            gotoligcol(26, 15);
            printf("1- Acheter la propriete");
            gotoligcol(27, 15);
            printf("2- Acheter une maison ou un hotel");
            gotoligcol(28, 15);
            printf("3- Vendre une maison ou un hotel");
            gotoligcol(29, 15);
            printf("4- Obtenir des informations sur un terrain");
            gotoligcol(30, 15);
            printf("5- Finir le tour et passer au joueur suivant");
            gotoligcol(31,15);
            printf(">> ");
            fflush(stdin);
            scanf("%d", &choix);
            while ((choix != 1) && (choix != 2) && (choix != 3) && (choix != 4) && (choix != 5)) {
                printf("Saisie invalide (Valeur attendue : 1, 2, 3, 4 ou 5)\n>> ");
                fflush(stdin);
                scanf("%d", &choix);
            };
        }
        if (choix == 1) {
            terrainactuel = listeCases[terrainactuel].id;
            if (listeTerrain[terrainactuel].ownedBy == player->id){
                gotoligcol(32,15);
                printf("Vous possedez deja ce terrain.");
                Sleep(500);
                tourPartie2(listeTerrain, listePlayers, listeCases, currentPlayer, rejouer, nbJoueurs, nbTours);
            }
            if (player->balance-listeTerrain[terrainactuel].defaultPrice < 0){
                gotoligcol(32,15);
                printf("Vous n'avez pas assez d'argent. Revenez plus tard !");
                Sleep(500);
                tourPartie2(listeTerrain, listePlayers, listeCases, currentPlayer, rejouer, nbJoueurs, nbTours);
            } else {
                acheterTerrainJ(player, listeTerrain[terrainactuel]);
                acheterTerrainT(player, &listeTerrain[terrainactuel]);
            }
        } else if (choix == 2) {
            if (listeTerrain[terrainactuel].ownedBy != player->id) {
                gotoligcol(32, 15);
                printf("Vous n'etes pas proprietaire de ce terrain, veuillez choisir une autre option.");
                Sleep(500);
                tourPartie2(listeTerrain, listePlayers, listeCases, currentPlayer, rejouer, nbJoueurs, nbTours);
            } else if (player->balance-listeTerrain[terrainactuel].housePrice < 0) {
                gotoligcol(32, 15);
                printf("Vous n'avez pas assez d'argent. Revenez plus tard !");
                Sleep(500);
                tourPartie2(listeTerrain, listePlayers, listeCases, currentPlayer, rejouer, nbJoueurs, nbTours);
            } else {
                acheterMaisonJ(player, listeTerrain[terrainactuel]);
                acheterMaisonT(player, &listeTerrain[terrainactuel]);
            }
<<<<<<< Updated upstream
        } else if (choix == 4) {
            printf("Saisissez l'ID de l'album sur lequel vous souhaitez des informations :\n");
            do {
                printf("De 1 a 22 inclus >> ");
=======
        } else if (choix == 3) {
            do {
                gotoligcol(30, 15);
                printf("Saisissez l'ID de l'album sur lequel vous souhaitez des informations : ");
>>>>>>> Stashed changes
                scanf("%d", &idalbum);
            } while (idalbum < 1 || idalbum > 22);
            infoAlbum(listeTerrain[idalbum - 1]);
            tourPartie2(listeTerrain, listePlayers, listeCases, currentPlayer, rejouer, nbJoueurs, nbTours);
        } else if (choix == 5) {
            if (!rejouer) {
                gotoligcol(26, 30);
                printf("Passer au tour du joueur suivant");
            } else {
                gotoligcol(26, 30);
                printf("On fait rejouer le joueur");
            }
        } else if (choix == 3) {
            if (listeTerrain[terrainactuel].ownedBy != player->id) {
                gotoligcol(32, 15);
                printf("Vous n'etes pas proprietaire de ce terrain, veuillez choisir une autre option.");
                Sleep(500);
                tourPartie2(listeTerrain, listePlayers, listeCases, currentPlayer, rejouer, nbJoueurs, nbTours);
            } else if (listeTerrain[terrainactuel].buildings == 0){
                gotoligcol(32, 15);
                printf("Il n'y a pas de maisons a vendre, veuillez choisir une autre option.");
                Sleep(500);
                tourPartie2(listeTerrain, listePlayers, listeCases, currentPlayer, rejouer, nbJoueurs, nbTours);
            } else {
                vendreMaisonJ(player, listeTerrain[terrainactuel], 1);
                vendreMaisonT(player, &listeTerrain[terrainactuel], 1);
            }
        }
    }
}

void tourPrison(terrain *listeTerrain, joueur **listePlayers, box *listeCases, int currentPlayer, int nbJoueurs, bool rejouer, int nbTours) {
    updateTour(listeTerrain, listePlayers, listeCases, currentPlayer, nbJoueurs);
    Color(15, 0);
    int premierDe = 0;
    int deuxiemeDe = 0;
    int sommeDe = 0;
    int choix1, choix2 = 0;
    int idJPrison = 0;  // id du potentiel joueur possédant une carte sortiePrison
    idJPrison = cartePrisonEnJeu(listePlayers);
    joueur *player = listePlayers[currentPlayer];
    gotoligcol(6, 15);
    printf("Solde du joueur %s : %d%c", player->username, player->balance, 0x24);

    gotoligcol(25, 15);
    printf("C'est au tour de %s : il est en prison depuis %d tour(s).", (player)->username, (player)->timeInJail);
    gotoligcol(26, 15);
    printf("Il peut :");
    gotoligcol(27, 15);
    printf("1- Continuer le tour");
    gotoligcol(28, 15);
    printf("2- Retourner au menu");
    do {
        gotoligcol(29, 15);
        printf(">> ");
        scanf("%d", &choix1);
    } while (choix1 < 1 || choix1 > 2);
    if (choix1 == 1) {                    // Continuer le tour
        if ((player)->timeInJail == 3) {  // Si il est en prison depuis 3 tours
            (player)->timeInJail = 0;
            //faillite(player, listeTerrain, 50);
            (player)->balance -= 50;
            gotoligcol(28, 35);
            printf("%s perd donc 50%c et peut a nouveau jouer normalement.", (player)->username, 0x24);
            gotoligcol(25, 15);
            tourNormal(listeTerrain, listePlayers, listeCases, currentPlayer, false, nbJoueurs, nbTours);
        } else {  // Si il est en prison depuis moins de 3 tours
            gotoligcol(27, 15);
            printf("1- Payer 50%c a la banque", 0x24);
            gotoligcol(28, 15);
            printf("2- Tenter d'obtenir un double");
            gotoligcol(29, 15);
            if ((player)->sortiePrison == true) {
                printf("3- Utiliser votre carte 'Sortie de prison'");
                gotoligcol(30, 15);
                printf(">> ");
                scanf("%d", &choix2);
                while (choix2 != 1 && choix2 != 2 && choix2 != 3) {
                    gotoligcol(30, 15);
                    printf("Saisie invalide >> ");
                    fflush(stdin);
                    scanf("%d", &choix2);
                }
            } else if (player->sortiePrison != true && idJPrison != 0) {
                printf("3- Acheter la carte du joueur %d", idJPrison);
                gotoligcol(30, 15);
                printf(">> ");
                scanf("%d", &choix2);
                while (choix2 != 1 && choix2 != 2 && choix2 != 3) {
                    gotoligcol(30, 15);
                    printf("Saisie invalide >> ");
                    fflush(stdin);
                    scanf("%d", &choix2);
                }
            }
            do {
                gotoligcol(29,15);
                printf(">> ");
                scanf("%d", &choix2);
            } while (choix2 < 1 || choix2 > 2);
            (player)->timeInJail += 1;
            premierDe = lancerDe();
            deuxiemeDe = lancerDe();
            sommeDe = premierDe + deuxiemeDe;
            if (choix2 == 1) {
                (player)->timeInJail = 0;
               // faillite(player, listeTerrain, 50);
                (player)->balance -= 50;
                deplacement(player, sommeDe);
                if (premierDe == deuxiemeDe) {  // Si le joueur fait un double
                    (player)->streakDouble += 1;
                    gotoligcol(10, 50);
                    printf("%s a fait un double ! Il peut donc rejouer.", player->username);
                    tourPartie2(listeTerrain, listePlayers, listeCases, currentPlayer, true, nbJoueurs, nbTours);
                    tourJoueur(listeTerrain, listePlayers, listeCases, currentPlayer, true, nbJoueurs, nbTours);
                } else {
                    (player)->streakDouble = 0;
                    tourPartie2(listeTerrain, listePlayers, listeCases, currentPlayer, false, nbJoueurs, nbTours);
                }
            } else if (choix2 == 2) {
                if (premierDe == deuxiemeDe) {  // Si il fait un double
                    (player)->timeInJail = 0;
                    gotoligcol(31, 15);
                    printf("%s a fait un double ! Il sort de prison et avance de %d cases.", (player)->username, sommeDe);
                    deplacement(player, sommeDe);
                    tourPartie2(listeTerrain, listePlayers, listeCases, currentPlayer, false, nbJoueurs, nbTours);
                } else {
                    gotoligcol(31, 15);
                    printf("%s n'a pas fait de double et reste en prison...", (player)->username);
                }
            } else if (choix2 == 3 && (player)->sortiePrison == true) {
                (player)->timeInJail = 0;
                gotoligcol(28, 15);
                printf("%s a utilise sa carte et sort de prison");
                deplacement(player, sommeDe);
                if (premierDe == deuxiemeDe) {  // Si le joueur fait un double
                    (player)->streakDouble += 1;
                    gotoligcol(10, 50);
                    printf("%s a fait un double ! Il peut donc rejouer.", player->username);
                    tourPartie2(listeTerrain, listePlayers, listeCases, currentPlayer, true, nbJoueurs, nbTours);
                    tourJoueur(listeTerrain, listePlayers, listeCases, currentPlayer, true, nbJoueurs, nbTours);
                } else {
                    (player)->streakDouble = 0;
                    tourPartie2(listeTerrain, listePlayers, listeCases, currentPlayer, false, nbJoueurs, nbTours);
                }
            } else if (choix2 == 3 && (player)->sortiePrison != true && idJPrison != 0) {
                (player)->timeInJail = 0;
                acheterCarteSortie(listePlayers[idJPrison], player);
                deplacement(player, sommeDe);
                if (premierDe == deuxiemeDe) {  // Si le joueur fait un double
                    (player)->streakDouble += 1;
                    gotoligcol(10, 50);
                    printf("%s a fait un double ! Il peut donc rejouer.", (player)->username);
                    tourPartie2(listeTerrain, listePlayers, listeCases, currentPlayer, true, nbJoueurs, nbTours);
                    tourJoueur(listeTerrain, listePlayers, listeCases, currentPlayer, true, nbJoueurs, nbTours);
                } else {
                    (player)->streakDouble = 0;
                    tourPartie2(listeTerrain, listePlayers, listeCases, currentPlayer, false, nbJoueurs, nbTours);
                }
            }
        }
    } else if (choix1 == 2) {
        homeInGame(listePlayers, player, listeTerrain, nbJoueurs, rejouer, nbTours);
    }
}

<<<<<<< Updated upstream
=======
void acheterCarteSortie(joueur *detenteur, joueur *enprison) {
    gotoligcol(20, 15)
        printf("%s, saisissez une valeur")
}

>>>>>>> Stashed changes
void tourJoueur(terrain *listeTerrain, joueur **listePlayers, box *listeCases, int currentPlayer, bool rejouer, int nbJoueurs, int nbTours) {
    gotoligcol(6, 15);
    joueur *player = listePlayers[currentPlayer];
    printf("Solde du joueur %s : %d%c", (player)->username, (player)->balance, 0x24);
    if (player->inJail == true) {
        tourPrison(listeTerrain, listePlayers, listeCases, currentPlayer, nbJoueurs, rejouer, nbTours);
    } else {
        tourNormal(listeTerrain, listePlayers, listeCases, currentPlayer, rejouer, nbJoueurs, nbTours);
    }
}

void tourNormal(terrain *listeTerrain, joueur **listePlayers, box *listeCases, int currentPlayer, bool rejouer, int nbJoueurs, int nbTours) {
    int premierDe, deuxiemeDe, sommeDe, choix = 0;
    updateTour(listeTerrain, listePlayers, listeCases, currentPlayer, nbJoueurs);
    Color(15, 0);
    joueur *player = listePlayers[currentPlayer];
    gotoligcol(6, 120);
    printf("Tour n%c%d", 0xF8, nbTours);
    gotoligcol(6, 15);
    printf("Solde du joueur %s : %d%c", (player)->username, (player)->balance, 0x24);

    if (rejouer) {
        gotoligcol(25, 15);
        printf("%s rejoue, il a fait un double :", (player)->username);
    } else {
        gotoligcol(27, 15);
        printf("Tour de %s, options :", (player)->username);
    }

    gotoligcol(28, 15);
    printf("1- Lancer les des");
    gotoligcol(29, 15);
    printf("2- Retourner au menu");
    gotoligcol(30, 15);

    printf(">> ");
    fflush(stdin);
    scanf("%d", &choix);
    while (choix != 1 && choix != 2) {
        printf("\nSaisie invalide (1 ou 2) >> ");
        fflush(stdin);
        scanf("%d", &choix);
    }

    if (choix == 1) {
        premierDe = lancerDe();
        deuxiemeDe = lancerDe();
        sommeDe = premierDe + deuxiemeDe;
        gotoligcol(18, 50);
        printf("Premier de : %d", premierDe);
        gotoligcol(19, 50);
        printf("Deuxieme de : %d", deuxiemeDe);
        if (premierDe == deuxiemeDe && (player)->position != 10) {  // Si le joueur fait un double
            player->streakDouble += 1;
            gotoligcol(10, 50);
            printf("%s a fait un double !", (player)->username);
            if (player->streakDouble == 3) {  // Soit il en a fait 3 d'affilés alors il a des malus (prison etc)
                printf("Le joueur a fait 3 doubles d'affilee.");
                *player = doubleStreakLimite(*player);  // à vérifier
            } else {                                    // Soit il n'en est pas à 3 et peut donc jouer 2 fois
                gotoligcol(16, 50);
                printf("Le joueur a fait un double et peut donc rejouer");
                Sleep(2000);
                deplacement(player, sommeDe);
                tourComplet(player);
                tourPartie2(listeTerrain, listePlayers, listeCases, currentPlayer, true, nbJoueurs, nbTours);
                tourJoueur(listeTerrain, listePlayers, listeCases, currentPlayer, true, nbJoueurs, nbTours);
            }
            // !
        } else {  // Si le joueur ne fait pas de double
            (player)->streakDouble = 0;
            deplacement(player, sommeDe);
            tourComplet(player);
            tourPartie2(listeTerrain, listePlayers, listeCases, currentPlayer, false, nbJoueurs, nbTours);
        }
    } else if (choix == 2) {
        homeInGame(listePlayers, player, listeTerrain, nbJoueurs, rejouer, nbTours);
    }
}

void newGame() {  // menu de création des joueurs, affiche le plateau de base
    const int nbJoueurs = demanderNbJoueurs();
    int i = 0;
    int nbTours = 1;
    joueur *pJoueurs = creationDesJoueurs(nbJoueurs);
    terrain *pTerrains = creationTerrain();
    box *bList = creationBox();

    while (finDuJeu(pJoueurs, nbJoueurs) == false) {
        creerPiocheCommu();
        creerPiocheChance();
        clearScreen();
        plateauGraphique(pTerrains);
        Color(15, 0);
        joueur *joueuractuel = &pJoueurs[i];
        tourJoueur(pTerrains, &pJoueurs, bList, i, false, nbJoueurs, nbTours);
        Color(15, 0);
        gotoligcol(7, 15);
        printf("Position joueur : %d", (joueuractuel)->position);
        nbTours += 1;
        ifFaillite (&pJoueurs);
        i++;
        if (i >= nbJoueurs) {
            i = 0;
        }
        gotoligcol(22, 58);
        printf("C'est au tour de %s !", pJoueurs[i].username);
        animation(23, 53, 100, 30);
    }
    free(bList);
    free(pJoueurs);
    free(pTerrains);
}

int caseColorId(int id) {
    int color;
    if (id == 1 || id == 3) {
        return 13;
    } else if (id == 6 || id == 8 || id == 9) {
        return 11;
    } else if (id == 11 || id == 13 || id == 14) {
        return 7;
    } else if (id == 16 || id == 18 || id == 19) {
        return 4;
    } else if (id == 21 || id == 23 || id == 24) {
        return 12;
    } else if (id == 26 || id == 27 || id == 29) {
        return 14;
    } else if (id == 31 || id == 32 || id == 34) {
        return 2;
    } else if (id == 37 || id == 39) {
        return 10;
    } else {
        return 15;
    }
    return color;
}

void afficherJoueurPlateau(joueur **joueurs, terrain *terrains, box *cases, int nbJoueurs) {
    int posJoueur[4] = {-1, -1, -1, -1};

    FILE *pf = fopen("data/output.txt", "w");
    if (pf == NULL) {
        printf("Erreur d'ouverture de fichier.");
    } else {
        fprintf(pf, "Le dossier a été ouvert\n\n");
    }
    for (int i = 0; i < 4; i++) {
        posJoueur[i] = (joueurs[i])->position;
    }
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

    fprintf(pf, "|ID|Position|Nombre|\n");
    fprintf(pf, "| 1|      %d|    %d|\n", pos1, nbPos1);
    fprintf(pf, "| 2|      %d|    %d|\n", pos2, nbPos2);
    fprintf(pf, "| 3|      %d|    %d|\n", pos3, nbPos3);
    fprintf(pf, "| 4|      %d|    %d|\n\n", pos4, nbPos4);

    int posList[4] = {pos1, pos2, pos3, pos4};
    int nbPosList[4] = {nbPos1, nbPos2, nbPos3, nbPos4};

    for (int i = 0; i < 40; i++) {
        fprintf(pf, "ID : %d|X : %d|Y : %d\n", cases[i].id, cases[i].x, cases[i].y);
    }
    for (int i = 0; i < nbJoueurs; i++) {
        // printf("Jouer numero :  %d", i);
        if (nbPosList[i] == 1) {
            Color(0, caseColorId(cases[posList[i]].id));
            fprintf(pf, "\n%d - %d, joueur %d\n", cases[posList[i]].y + 2, cases[posList[i]].x + 6, i);
            gotoligcol(cases[posList[i]].x + 2, cases[posList[i]].y + 6);
            // printf("avant le pointeur");
            printf("%c", joueurs[i]->avatar);
            // printf("apres le pointeur ");
        } else if (nbPosList[i] == 2) {
            Color(0, caseColorId(cases[posList[i]].id));
            fprintf(pf, "\n%d - %d, joueur %d\n", cases[posList[i]].y + 2, cases[posList[i]].x + 4, i);
            gotoligcol(cases[posList[i]].x + 2, cases[posList[i]].y + 4);
            printf("%c", joueurs[i]->avatar);
            fprintf(pf, "%d - %d, joueur %d\n", cases[posList[i]].y + 2, cases[posList[i]].x + 8, i + 1);
            gotoligcol(cases[posList[i]].x + 2, cases[posList[i]].y + 8);
            printf("%c", joueurs[i + 1]->avatar);
            i++;
        } else if (nbPosList[i] == 3) {
            Color(0, caseColorId(cases[posList[i]].id));
            fprintf(pf, "\n%d - %d, joueur %d\n", cases[posList[i]].y + 2, cases[posList[i]].x + 3, i);
            gotoligcol(cases[posList[i]].x + 2, cases[posList[i]].y + 3);
            printf("%c", joueurs[i]->avatar);
            fprintf(pf, "%d - %d, joueur %d\n", cases[posList[i]].y + 2, cases[posList[i]].x + 6, i + 1);
            gotoligcol(cases[posList[i]].x + 2, cases[posList[i]].y + 6);
            printf("%c", joueurs[i + 1]->avatar);
            fprintf(pf, "%d - %d, joueur %d\n", cases[posList[i]].y + 2, cases[posList[i]].x + 9, i + 2);
            gotoligcol(cases[posList[i]].x + 2, cases[posList[i]].y + 9);
            printf("%c", joueurs[i + 2]->avatar);
            i++;
            i++;
        } else if (nbPosList[i] == 4) {
            Color(0, caseColorId(cases[posList[i]].id));
            fprintf(pf, "\n%d - %d, joueur %d\n", cases[posList[i]].y + 2, cases[posList[i]].x + 3, i);
            gotoligcol(cases[posList[i]].x + 2, cases[posList[i]].y + 3);
            printf("%c", joueurs[i]->avatar);
            fprintf(pf, "%d - %d, joueur %d\n", cases[posList[i]].y + 2, cases[posList[i]].x + 5, i + 1);
            gotoligcol(cases[posList[i]].x + 2, cases[posList[i]].y + 5);
            printf("%c", joueurs[i + 1]->avatar);
            fprintf(pf, "%d - %d, joueur %d\n", cases[posList[i]].y + 2, cases[posList[i]].x + 7, i + 2);
            gotoligcol(cases[posList[i]].x + 2, cases[posList[i]].y + 7);
            printf("%c", joueurs[i + 2]->avatar);
            fprintf(pf, "%d - %d, joueur %d\n", cases[posList[i]].y + 2, cases[posList[i]].x + 9, i + 3);
            gotoligcol(cases[posList[i]].x + 2, cases[posList[i]].y + 9);
            printf("%c", joueurs[i + 3]->avatar);
            i++;
            i++;
            i++;
        }
    }
    Color(15, 0);
    fclose(pf);
    pf = NULL;
    Sleep(2000);
}

void faireSauvegarde(joueur **listePlayers, joueur *currentplayer, terrain *listeTerrain, int nbJoueurs, bool rejouer, int nbTours) {
    FILE *pf = fopen("data/save1.txt", "w");
    if (pf == NULL) {
        printf("Erreur d'ouverture de fichier.");
    }

    for (int i = 0; i < 22; i++) {
        fprintf(pf, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", listeTerrain[i].id, listeTerrain[i].defaultPrice,
<<<<<<< Updated upstream
        listeTerrain[i].idOnBoard, listeTerrain[i].housePrice, listeTerrain[i].loyer, listeTerrain[i].loyermaison1, listeTerrain[i].loyermaison2,
        listeTerrain[i].loyermaison3, listeTerrain[i].loyermaison4, listeTerrain[i].loyerhotel, listeTerrain[i].val_hypoth, listeTerrain[i].buildings,
        listeTerrain[i].x, listeTerrain[i].y, listeTerrain[i].couleur, listeTerrain[i].ownedBy);
        fprintf(pf, " %d %d %d", listeTerrain[i].owned, listeTerrain[i].hotel, listeTerrain[i].hypotheque);
        fprintf(pf, "\n");
    }

    for (int j = 0; j<nbJoueurs; j++){
        fprintf(pf, "%d %d %d %d %d %d %d %d %d %d", listePlayers[j]->id, listePlayers[j]->balance, listePlayers[j]->position,
        listePlayers[j]->sortiePrison, listePlayers[j]->carteDenonciation, listePlayers[j]->inJail, listePlayers[j]->bankruptcy,
        listePlayers[j]->streakDouble, listePlayers[j]->timeInJail, listePlayers[j]->avatar);
        for (int k = 0; k<26; k++){
=======
                listeTerrain[i].idOnBoard, listeTerrain[i].housePrice, listeTerrain[i].loyer, listeTerrain[i].loyermaison1, listeTerrain[i].loyermaison2,
                listeTerrain[i].loyermaison3, listeTerrain[i].loyermaison4, listeTerrain[i].loyerhotel, listeTerrain[i].val_hypoth, listeTerrain[i].buildings,
                listeTerrain[i].x, listeTerrain[i].y, listeTerrain[i].couleur, listeTerrain[i].ownedBy);
        if (listeTerrain[i].owned == false) {
            fprintf(pf, " false");
        } else {
            fprintf(pf, " true");
        }
        if (listeTerrain[i].hotel == false) {
            fprintf(pf, " false");
        } else {
            fprintf(pf, " true");
        }
        if (listeTerrain[i].hypotheque == false) {
            fprintf(pf, " false");
        } else {
            fprintf(pf, " true");
        }
        fprintf(pf, "\n");
    }

    for (int j = 0; j < nbJoueurs; j++) {
        fprintf(pf, "%d %d %s %d", listePlayers[j]->id, listePlayers[j]->balance, listePlayers[j]->username, listePlayers[j]->position);
        if (listePlayers[j]->sortiePrison == false) {
            fprintf(pf, " false");
        } else {
            fprintf(pf, " true");
        }
        if (listePlayers[j]->carteDenonciation == false) {
            fprintf(pf, " false");
        } else {
            fprintf(pf, " true");
        }
        if (listePlayers[j]->inJail == false) {
            fprintf(pf, " false");
        } else {
            fprintf(pf, " true");
        }
        if (listePlayers[j]->bankruptcy == false) {
            fprintf(pf, " false");
        } else {
            fprintf(pf, " true");
        }
        fprintf(pf, " %d %d %d", listePlayers[j]->streakDouble, listePlayers[j]->timeInJail, listePlayers[j]->avatar);
        for (int k = 0; k < 26; k++) {
>>>>>>> Stashed changes
            fprintf(pf, " %d", listePlayers[j]->ownedField[k]);
        }
        fprintf(pf, " %s", listePlayers[j]->username);
        fprintf(pf, "\n");
    }

<<<<<<< Updated upstream
    if (nbJoueurs == 2){
        fprintf(pf, "\n\n\n\n\n%d %d %d", nbJoueurs, currentplayer->id, nbTours);
    } else if (nbJoueurs == 3){
        fprintf(pf, "\n\n\n\n%d %d %d", nbJoueurs, currentplayer->id, nbTours);
=======
    fprintf(pf, "%d %d", currentplayer->id, nbTours);
    if (rejouer == true) {
        fprintf(pf, " true");
>>>>>>> Stashed changes
    } else {
        fprintf(pf, "\n\n\n%d %d %d", nbJoueurs, currentplayer->id, nbTours);
    }
    fprintf(pf, " %d", rejouer);

    fclose(pf);
}

terrain *chargerTerrains() {  // chargement des terrains
    terrain *listeTerrain = (terrain *)malloc(23 * sizeof(terrain));

    terrain instance;

    char *listeNomTerrain[22] = {"Racine Carree", "Brol", "Absolution", "Plat.Collec", "Nevermind", "RAM", "One More Love",
                                 "Discovery", "MMLP", "NWTS", "Eminem Show", "Or Noir", "Ouest Side", "Civilisation", "Unorth.Juke",
                                 "After Hours", "Thriller", "DLL", "Trinity", "JVLIVS", "Ipseite", "Cyborg"};
    
    for (int i = 0; i < 22; i++) {
        char *nomCurrent = listeNomTerrain[i];
        FILE* texte = NULL;
        texte = fopen("data/save1.txt", "r");
        if (texte == NULL) {
            printf("Error: Cannot open");
        }
        char ignore[1024];
        int donnee[16];
        bool own, hot, hyp;
        int tempOwn, tempHot, tempHyp;
        for (int j = 0; j < i; j++) {
            fgets(ignore, sizeof(ignore), texte);
        }
        fscanf(texte, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &donnee[0], &donnee[1], &donnee[14],
               &donnee[2], &donnee[3], &donnee[4], &donnee[5], &donnee[6], &donnee[7], &donnee[8], &donnee[9],
               &donnee[10], &donnee[11], &donnee[12], &donnee[13], &donnee[15], &tempOwn, &tempHot, &tempHyp);

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
        instance.val_hypoth = donnee[9];
        instance.buildings = donnee[10];
        instance.x = donnee[11];
        instance.y = donnee[12];
        instance.couleur = donnee[13];
        instance.ownedBy = donnee[15];
        own = tempOwn;
        hot = tempHot;
        hyp = tempHyp;
        instance.owned = own;
        instance.hotel = hot;
        instance.hypotheque = hyp;

        listeTerrain[i] = instance;
    }

    return listeTerrain;
}

joueur* chargerJoueurs(int nbJoueurs){
    joueur *listeJoueurs = (joueur *)malloc(4 * sizeof(joueur));
    joueur player;

    for (int i = 0; i < nbJoueurs; i++) {
        FILE* pf = NULL;
        pf = fopen("data/save1.txt", "r");
        if (pf == NULL) {
            printf("Error: Cannot open");
        }
        //char* nomJ = malloc(12 * sizeof(char));
        int nbJoueurs;
        int donnee[40];
        char ignore[1024];
        bool sortie, prison, denoncer, faillite;
        int tempSortie, tempDenoncer, tempPrison, tempFaillite;
        for (int j = 0; j < 22+i; j++) {
            fgets(ignore, sizeof(ignore), pf);
        }

        fscanf(pf, "%d %d %d %d %d %d %d %d %d %d", &donnee[0], &donnee[1], &donnee[2], &donnee[3], &tempSortie, &tempDenoncer, 
        &tempPrison, &tempFaillite, &donnee[4], &donnee[5]);
        sortie = tempSortie;
        denoncer = tempDenoncer;
        prison = tempPrison;
        faillite = tempFaillite;
        player.id = donnee[0];
        player.balance = donnee[1];
        player.position = donnee[2];
        player.sortiePrison = sortie;
        if (player.sortiePrison == 0){
            player.sortiePrison = false;
        } else {
            player.sortiePrison = true;
        }
        player.carteDenonciation = denoncer;
        if (player.carteDenonciation == 0){
            player.carteDenonciation = false;
        } else {
            player.carteDenonciation = true;
        }
        player.inJail = prison;
        if (player.inJail == 0){
            player.inJail = false;
        } else {
            player.inJail = true;
        }
        player.bankruptcy = faillite;
        if (player.bankruptcy == 0){
            player.bankruptcy = false;
        } else {
            player.bankruptcy = true;
        }
        player.streakDouble = donnee[3];
        printf("%d ", player.streakDouble);
        player.timeInJail = donnee[4];
        printf("%d ", player.timeInJail);
        player.avatar = donnee[5];
        printf("avatar : %d ", player.avatar);
        for (int j=0; j<26; j++){
            fscanf(pf, "%d ", &donnee[j+6]);
            player.ownedField[j] = donnee[j+6];
            printf("indice %d liste : %d ", j, player.ownedField[j]);
        }
        /*
        for (int n=0; n<5; n++){
            fscanf(pf, "%c", &nomJ[n]);
        }
        printf("nom : %s ", nomJ);
        strcpy(player.username, nomJ);
        printf("nom 2 : %s",player.username);
        */
        Sleep(3000);

        listeJoueurs[i] = player;
    }

    /*
    if (nbJoueurs == 2){
        joueur tempJ3 = {3, 1500, "NULL", -1, {0}, false, false, false, false, 0, 0};
        joueur tempJ4 = {4, 1500, "NULL", -1, {0}, false, false, false, false, 0, 0};
        listeJoueurs[2] = tempJ3;
        listeJoueurs[3] = tempJ4;
    } else if (nbJoueurs == 3){
        joueur tempJ4 = {4, 1500, "NULL", -1, {0}, false, false, false, false, 0, 0};
        listeJoueurs[3] = tempJ4;
    } */

    for (int i = 0; i < nbJoueurs; i++) {
        display();
        printf("Entrez le nom du joueur %d : ", i + 1);
        scanf("%s", listeJoueurs[i].username);
        listeJoueurs[i].position = 0;
    }

    display();
    gotoligcol(14, 0);

    for (int i = 0; i < nbJoueurs; i++) {
        printf("Pseudo et avatar du joueur %d : %s  -  %c\n", i + 1, listeJoueurs[i].username, listeJoueurs[i].avatar);
    }

    printf("\nChargement de la partie en cours");

    animation(20, 0, 75, 50);

    return listeJoueurs;
}

void chargerSauvegarde(){
    FILE* pf = NULL;
    pf = fopen("data/save1.txt", "r");
    if (pf == NULL) {
        printf("Error: Cannot open");
    }

    const int nbJoueurs = 0;
    int i = 0;
    int nbTours = 1;
    char ignore[1024];
    bool rejouer;
    int tempRejouer;
    for (int j = 0; j < 29; j++) {
        fgets(ignore, sizeof(ignore), pf);
    }
    fscanf(pf, "%d %d %d %d", &nbJoueurs, &i, &nbTours, &tempRejouer);
    rejouer = tempRejouer;
    printf(" %d %d %d %d\n", nbJoueurs, i, nbTours, rejouer);
    Sleep(2000);
    i -= 1;
    printf("%d\n", i);
    rewind(pf);
    
    joueur *pJoueurs = chargerJoueurs(nbJoueurs);
    Sleep(2000);
    terrain *pTerrains = chargerTerrains();
    box *bList = creationBox();

    while (pJoueurs[0].balance > 0) {
        clearScreen();
        plateauGraphique(pTerrains);
        Color(15, 0);
        joueur *joueuractuel = &pJoueurs[i];
        tourJoueur(pTerrains, &pJoueurs, bList, i, rejouer, nbJoueurs, nbTours);
        printf("putoooo");
        Color(15, 0);
        gotoligcol(7, 15);
        printf("Position joueur : %d", (joueuractuel)->position);
        nbTours += 1;
        i++;
        if (i >= nbJoueurs) {
            i = 0;
        }
        gotoligcol(22, 58);
        printf("C'est au tour de %s !", pJoueurs[i].username);
        animation(23, 53, 100, 30);
    }
    free(bList);
    free(pJoueurs);
    free(pTerrains);
}

int main() {
    // Sleep(10000);    // Decommente pour voir les warnings
    Color(15, 0);
    srand(time(NULL));
    home();

    return 0;
}

<<<<<<< Updated upstream
joueur communaute(joueur currentplayer, terrain *listeTerrain){
    int nb;
    int donnee[16];
    int piocheTampon[16];
    FILE *pf = fopen("data/piocheCommu.txt", "w");
    if (pf == NULL)
    {
        printf("Erreur d'ouverture de fichier.");
    }
    else
    {
        fscanf(pf, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &donnee[0], &donnee[1],
               &donnee[2], &donnee[3], &donnee[4], &donnee[5], &donnee[6], &donnee[7],
               &donnee[8], &donnee[9], &donnee[10], &donnee[11], &donnee[12], &donnee[13], &donnee[14], &donnee[15]);
    }
    nb = donnee[0];
=======
/*void communaute(joueur currentplayer, terrain *listeTerrains, ){

>>>>>>> Stashed changes
    if (nb == 1){
        printf("Vous achetez des streams. Versez 50%c a la banque", 0x24);
        currentplayer.balance -= 50;
    }
    else if (nb == 2){
        printf("Vous faites un mauvais demarrage d'album. Versez 100%c a la banque", 0x24);
        currentplayer.balance -= 100;
    }
    else if (nb == 3){
        printf("Vous faites un exces de vitesse. Versez 10%c a la banque",0x24);
        currentplayer.balance -= 10;
    }
    else if (nb == 4){
        printf("Un fans vous donne 50%c", 0x24);
        currentplayer.balance += 50;
    }
    else if (nb == 5){
        printf("Vous faites un showcase. Recevez 100%c", 0x24);
        currentplayer.balance += 100;
    }
    else if (nb == 6){
        printf("Vous tournez un clip a Dubai. Versez 100%c a la banque", 0x24);
        currentplayer.balance -= 100;
    }
    else if (nb == 7){
        printf("Vous allez vous inspirer a New York. Versez 50%c a la banque", 0x24);
        currentplayer.balance -= 50;
    }
    else if (nb == 8){
        printf("Vous etes top1 spotify. Recevez 50%c de la banque", 0x24);
        currentplayer.balance += 50;
    }
    else if (nb == 9){
        printf("Vous signez un nouveau label. Recevez 200%c", 0x24);
        currentplayer.balance += 200;
    }
    else if (nb == 10)
    {
        printf("Payez 10%c d'impots pour chacun de vos terrain",0x24);
        int prix=0;
        for (int i  = 0; i<26; i++)
        {
            if (currentplayer.ownedField[i] != 0)
            {
                prix +=10;
            }
        printf("Vous avez payer %d$ taxes",prix);
        currentplayer.balance -= prix;
        }
    }
    else if (nb == 11)
    {
        int reparation = 0;
        printf("Payer 50%c de réparation sur chacun de vos hotels.",0x24 );
        for (int i = 0; i<22;i++)
        {
            if (listeTerrain[i].ownedBy == currentplayer.id)
            {
                if (listeTerrain[i].hotel == true)
                {
                    reparation += 50;
                }
            }
        }
        printf("Vous avez payez %d reparation",reparation);
        currentplayer.balance += reparation;
    }
    else if (nb == 12)
    {
        printf("Allez en prison" );
        currentplayer.position = 10;
        currentplayer.inJail = true;
    }
    else if (nb == 13)
    {
        printf("Allez vous reposer au Zenith d'apres");
        if (currentplayer.position > 35 )
        {
            currentplayer.balance += 200;
            currentplayer.position = 5;
        }
        else if ( 5 < currentplayer.position < 15)
        {
            currentplayer.position = 15;
        }
        else if ( 15 < currentplayer.position < 25)
        {
            currentplayer.position = 25 ;
        }
        else if ( 25 < currentplayer.position < 35)
        {
            currentplayer.position = 35;
        }
        else 
        {
            currentplayer.position = 5;
        }
    }
    else if (nb == 14)
    {
        printf("Vous aidez un fans dans le besoin et vous lui donnez 25%c", 0x24);
        currentplayer.balance -= 25;
    }
    else if (nb == 15)
    {
        printf("Allez à la case départ");
        currentplayer.position = 0;
        currentplayer.balance += 200;
    }
    else
    {
        printf("Vous aidez un jeune rappeur à commencer. Versez 50%c à la banque", 0x24);
        currentplayer.balance -= 50;
    }
    for (int i = 0; i< 16; i++)
    {
        piocheTampon[i] = donnee[i+1];
    }
    piocheTampon[15] = nb;
    for(int j = 0; j < 15; j++)
    {
        piocheTampon[j] = donnee[j+1];
    }
    piocheTampon[15] = nb;
    for(int j = 0; j < 16; j++)
    {
        fprintf(pf, "%d ",piocheTampon[j]);
    }
    fclose(pf);
    pf = NULL;
    return currentplayer;
}

joueur chance(joueur currentplayer){
    int nb;
    int donnee[16];
    int piocheTampon[16];
    FILE *pf = fopen("data/piocheChance.txt", "w");
    if (pf == NULL)
    {
        printf("Erreur d'ouverture de fichier.");
    }
    else
    {
        fscanf(pf, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &donnee[0], &donnee[1],
               &donnee[2], &donnee[3], &donnee[4], &donnee[5], &donnee[6], &donnee[7],
               &donnee[8], &donnee[9], &donnee[10], &donnee[11], &donnee[12], &donnee[13], &donnee[14], &donnee[15]);
    }
    nb = donnee[0];
    if (nb <15 )
    {
        if (nb == 1){
            printf("Allez a la case depart");
            currentplayer.balance += 200;
            currentplayer.position = 0;
        }
        else if (nb == 2){
            printf("Vous gagnez un pari PMU. Recevez 100%c.", 0x24);
            currentplayer.balance += 100;
        }
        else if (nb == 3){
            printf("Allez en prison");
            currentplayer.position = 10;
            currentplayer.inJail = true;
        }
        else if (nb == 4){
            printf("Vous recevez la recompensede revelation de l'annee. Recevez 50%c", 0x24);
            currentplayer.balance += 50;
        }
        else if (nb == 5){
            printf("Vous faites une pub. ReceveZ 50%c", 0x24);
            currentplayer.balance += 200;
        }
        else if (nb == 6){
            printf("Vous allez voir un amis en prison");
            if (currentplayer.position > 10)
            {
                currentplayer.balance += 200;
            }
            currentplayer.position = 10;
        }
        else if (nb == 7){
            printf("Vous avez bien travaillé. Allez vous reposé à Soundcloud");
            if (currentplayer.position > 20)
            {
                currentplayer.balance += 200;
            }
            currentplayer.position = 20;
        }
        else if (nb == 8){
            printf("Vos placements vous rapporte 200%c", 0x24);
            currentplayer.balance += 50;
        }
        else if (nb == 9)
        {
            printf("Allez vous reposer au Zenith d'apres");
            if (currentplayer.position > 35 )
            {
                currentplayer.balance += 200;
                currentplayer.position = 5;
            }
            else if ( 5 < currentplayer.position < 15)
            {
                currentplayer.position = 15;
            }
            else if ( 15 < currentplayer.position < 25)
            {
                currentplayer.position = 25 ;
            }
            else if ( 25 < currentplayer.position < 35)
            {
                currentplayer.position = 35;
            }
            else 
            {
                currentplayer.position = 5;
            }
        }
        else if (nb == 10)
        {
            printf("Payez 20%c d'impots", 0x24);
            currentplayer.balance -= 20;
        }
        else if (nb == 11)
        {
            printf("Vous achetez une nouvelle voiture. Payez 50%c", 0x24);
            currentplayer.balance -= 50;
        }
        else if (nb == 12)
        {
            printf("Vous etes top un Deezer. Recevez 25%c", 0x24);
            currentplayer.balance += 25;
        }
        else if (nb == 13)
        {
            printf("Vous gagnez 500%c au loto", 0x24);
            currentplayer.balance += 500;

        }
        else
        {
            printf("Vous prenez des cours de piano. Payez 50%c", 0x24);
            currentplayer.balance -= 50;
        }
        if (donnee[14] == 0 && donnee[15] == 0)
        {
                for (int i = 0; i< 16; i++)
            {
                piocheTampon[i] = donnee[i+1];
            }
            for(int j = 0; j < 15; j++)
            {
                piocheTampon[j] = donnee[j+1];
            }
            piocheTampon[13] = nb;
            piocheTampon[14] = 0;
            piocheTampon[15] = 0;
            for(int j = 0; j < 16; j++)
            {
                fprintf(pf, "%d ",piocheTampon[j]);
            }
        }
        else if (donnee[14] != 0 && donnee[15] == 0)
        {
            for (int i = 0; i< 16; i++)
            {
                piocheTampon[i] = donnee[i+1];
            }
            for(int j = 0; j < 15; j++)
            {
                piocheTampon[j] = donnee[j+1];
            }
            piocheTampon[14] = nb;
            piocheTampon[15] = 0;
            for(int j = 0; j < 16; j++)
            {
                fprintf(pf, "%d ",piocheTampon[j]);
            }
        }
        else
        {
            for (int i = 0; i< 16; i++)
            {
                piocheTampon[i] = donnee[i+1];
            }
            for(int j = 0; j < 15; j++)
            {
                piocheTampon[j] = donnee[j+1];
            }
            piocheTampon[15] = nb;
            for(int j = 0; j < 16; j++)
            {
                fprintf(pf, "%d ",piocheTampon[j]);
            }
        }
    }
    else
    {
        if (nb == 15)
        {
            printf("Vous denoncez une fraude du proprietaire, vous ne payez pas le loyer, carte a conserver ");
            currentplayer.carteDenonciation = true;
        }
        else
        {
            printf("Carte sortie de prison, a concerver");
            currentplayer.sortiePrison = true;
        }
        for (int i = 0; i< 16; i++)
        {
            piocheTampon[i] = donnee[i+1];
        }
        piocheTampon[15] = 0;
        for(int j = 0; j < 15; j++)
        {
            piocheTampon[j] = donnee[j+1];
        }
        for(int j = 0; j < 16; j++)
        {
            fprintf(pf, "%d ",piocheTampon[j]);
        }
    }
    fclose(pf);
    pf == NULL;
    return currentplayer;
}