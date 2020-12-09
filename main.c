#include <stdio.h>
#include <stdlib.h>

#define MAX_LIGNE 100

int** f_scanPGM(char nomfichier[], int* ptr_n, int* ptr_p, int* ptr_nb_magique, int* ptr_max);
void f_printPGM(int** tab,int n,int p, int nb_magique, int max);
void afficheTab2D(int** tab,int n,int p);

int main()
{
    int** tab;
    int hauteur, largeur;
    int nb_magique, max;

    tab=f_scanPGM("feep.pgm", &hauteur, &largeur, &nb_magique, &max);

    afficheTab2D(tab,hauteur,largeur);

    f_printPGM(tab,hauteur,largeur, nb_magique, max);

    free(tab);
    return 0;
}

int** f_scanPGM(char nomfichier[], int* ptr_n, int* ptr_p, int* ptr_nb_magique, int* ptr_max)
{
    FILE *f; //pointeur vers le fichier cible
    int** tab; //tableau en 2D alloué dynamiquement
    int i,j;
    char etat_lecture = 0; //etat_lecture=3 --> les 3 parametres d'entete ont ete lus
    char ligne[MAX_LIGNE]; //On utilisera fgets pour effectuer une lecture ligne par ligne pour l'entete



    f=fopen(nomfichier,"r"); //ouverture du fichier en lecture seule
    if (f==NULL) printf("erreur ouverture fichier\n");
    else
    {
        while (etat_lecture != 3) {
            fgets(ligne, MAX_LIGNE, f);
                //lecture ligne par ligne tant que les 3 parametres ne sont pas "set"
            if (ligne[0] == '#') continue;//si on tombe sur un commentaire, on repart pour un autre tour de boucle

            //Et ensuite on cherche les infos en fonction de l'etat de lecture actuel
            if (etat_lecture == 0) {
                sscanf(ligne, "P%d", ptr_nb_magique);
                etat_lecture+=1;
            }
            else if (etat_lecture == 1) {
                sscanf(ligne, "%d %d", ptr_p, ptr_n);
                etat_lecture+=1;
            }
            else if (etat_lecture == 2) {
                sscanf(ligne, "%d", ptr_max);
                etat_lecture+=1;
            }

        }
        printf("informations trouvees dans l'entete :\n");
        printf("'''''''''''''''''''''''''''''''''''\n");
        printf("nb_magique : %d\n", *ptr_nb_magique);
        printf("largeur/hauteur : %d/%d\n", *ptr_p, *ptr_n);
        printf("max : %d\n\n", *ptr_max);

        /* Allocation de tableau 2D en 2 etapes */
        tab = malloc(*ptr_n * sizeof(int*));
        //ici on fait la demande pour l'allocation d'un tableau de n pointeurs
        for(i = 0; i < *ptr_n; i++) tab[i] = malloc(sizeof(int) * *ptr_p);
        //puis pour chaque case du premier tableau on alloue un tableau d'entiers

        //remplissage du tableau :
        for(i = 0; i < *ptr_n; i++)
        {
            for(j = 0; j < *ptr_p; j++)
            {
                fscanf(f,"%d",&tab[i][j]);
            }
        }

    }
    fclose(f);
    return tab;
}

void f_printPGM(int** tab,int n,int p, int nb_magique, int max)
{
    FILE *f;//pointeur vers le fichier cible
    char filename[]="output.pgm"; //nom du fichier de sortie
    int i,j;

    f=fopen(filename,"w");//On ouvre en écriture, cela va créer directement le fichier
    if (f==NULL) printf("erreur ouverture fichier\n");
    else
    {
        //ecriture de l'entete dans l'output
        fprintf(f,"P%d\n",nb_magique);
        fprintf(f,"%d %d\n",p,n);
        fprintf(f,"%d\n",max);

        //Remplissage du fichier à partir du tableau 2D
        for(i=0; i < n; i++)
        {
            for(j = 0; j < p; j++)
            {
                fprintf(f,"%4d",tab[i][j]);
            }
            fprintf(f,"\n");
            }
    }
}

void afficheTab2D(int** tab,int n,int p)
{
    int i,j;
    printf("Voici le tableau associe au fichier PGM : \n");
    printf("'''''''''''''''''''''''''''''''''''''''\n");

    //Affichage case par case du tableau 2D
    for(i=0; i < n; i++)
    {
        for(j = 0; j < p; j++)

        {
            printf("%4d",tab[i][j]);
        }
    printf("\n");
    }
}
