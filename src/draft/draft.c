// Taille physique du tableau
#define NOMBRE_MAXI_ETUDIANTS 100

typedef struct {
    int numeroEtudiant;
    float maths, phys, physApp, info;
} Etudiant;

float saisirNote() {
    float note;
    do {
        scanf(" %f", &note);
        if(note < 0 || note > 20) {
            printf("La note n'est pas correcte, recommencez.\n");
        }
    } while(note < 0 || note > 20);
    return note;
}

Etudiant saisirEtudiant() {
    Etudiant nouvelEtudiant;
    printf("Numero etudiant :\n");
    scanf("%d", &nouvelEtudiant.numeroEtudiant);
    printf("Moyenne en maths :\n");
    nouvelEtudiant.maths = saisirNote(); // scanf("%f", &nouvelEtudiant.maths);
    printf("Moyenne en physique :\n");
    nouvelEtudiant.phys = saisirNote();
    printf("Moyenne en physique appliquee :\n");
    nouvelEtudiant.physApp = saisirNote();
    printf("Moyenne en informatique :\n");
    nouvelEtudiant.info = saisirNote();
    return nouvelEtudiant;
}

void afficherEtudiant(Etudiant e) {
    printf("Etudiant %d : maths (%.2f/20), physique (%.2f/20), electronique (%.2f/20), informatique (%.2f/20).\n",
           e.numeroEtudiant, e.maths, e.phys, e.physApp, e.info);
}

float moyenneMaths(Etudiant promotion[], int nbEtudiants) {
    if(nbEtudiants == 0) {
        return 0; // pour ne pas faire une division par 0
    }
    int i = 0;
    float somme = 0;
    for (i = 0; i < nbEtudiants; ++i) {
        somme += promotion[i].maths;
    }
    return somme / nbEtudiants;
}

void afficherEtudiants(Etudiant etudiants[], int taille) {
    int i = 0;
    for (i = 0; i < taille; ++i) {
        afficherEtudiant(etudiants[i]);
    }
}

int main() {
    int i = 0;
    int nbEtudiants = 0; // taille logique du tableau
    Etudiant promotion[NOMBRE_MAXI_ETUDIANTS];

    do {
        printf("Combien d'etudiants avez-vous ?\n");
        scanf(" %d", &nbEtudiants);
    } while (nbEtudiants < 0 || nbEtudiants > NOMBRE_MAXI_ETUDIANTS);

    for (i = 0; i < nbEtudiants; ++i) {
        promotion[i] = saisirEtudiant();
    }

    afficherEtudiants(promotion, nbEtudiants);

    printf("Moyenne en mathematiques : %.2f.\n", moyenneMaths(promotion, nbEtudiants));

    return 0;
}