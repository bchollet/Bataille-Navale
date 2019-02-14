#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
#include <time.h>
#define NBTIR_MAX 2
#define DEFAULT_VALUE -1
#define DEFAULT_CHAR ' '

//Ceci est un test de versionning !

char DemanderLettre();
char RetourMenu();
void AideDuJeu();
void ScoresDuJeu();
void AfficherGrille();
void EcritureScores();
void EcritureLog();
int Jeu();
char Login();

int nbtir = 0, numGrille = DEFAULT_VALUE;

char login[20];

int main()
{
    char lettre = DEFAULT_CHAR;

    do
    {
        system("cls");
        printf("========== Bonjour moussaillon ! Bienvenu dans la bataille navale ! ==========\n");
        printf("\t\t\tQue souhaitez-vous faire ?\n\n");
        printf("\t\t  - Jouer - Aide - Scores - Quitter -\n\n");
        printf("Entrez la premiere lettre de l'action que vous souhaitez effectuer: ");

        switch(DemanderLettre())
        {
            case 'j':
            case 'J':
                nbtir = Jeu();  //Le nombre de tir de la partie est enregistr‚ dans la variable nbtir. Elle sera utilis‚e pour d‚terminer les scores
                RetourMenu();
                break;

            case 'a':
            case 'A':
                AideDuJeu();
                break;

            case 's':
            case 'S':
                ScoresDuJeu();
                break;
            case 'q':
            case 'Q':
                printf("\nAu revoir moussaillon ! A bientot !\n");
                lettre = 'q'; //Permet de fermer la boucle
                break;

            default:
                printf("\nCommande pas valide");
                RetourMenu();
                break;
        }
    } while (lettre != 'q');

    return EXIT_SUCCESS;
}

char DemanderLettre()
{
    char lettre = DEFAULT_CHAR;
    fflush(stdin);
    scanf("%c", &lettre);
    return lettre;
}

char RetourMenu()
{
    char retour_menu = DEFAULT_CHAR;
    printf("\n\n\nAppuyez sur \"Enter\" pour revenir au menu\n");
    fflush(stdin);
    scanf("%c", &retour_menu);
    system("cls");
    return retour_menu;
}

char Login()
{
    system("cls");
    do
    {
        printf("Veuillez entrer un login (20 caractŠres max): ");
        fflush(stdin);
        scanf("%20s", login);
        fflush(stdin);
        printf("Votre login est-il bien: %s ? <o/n>: ", login);

    } while (DemanderLettre() != 'o');

    return login;

}

void AfficherGrille()
{
    int ligne = DEFAULT_VALUE, col = DEFAULT_VALUE;

    printf("      0   1   2   3   4   5   6   7   8   9\n");
    printf("    -----------------------------------------\n");
    for (col = 0; col < 10; col++)
    {
        printf("%2d  ",col);
        for (ligne = 0; ligne < 10; ligne++)
        {
            printf("|   ");
        }
        printf("|");
        AfficherInfo(col, 0, DEFAULT_VALUE);
        printf("\n");
        printf("    -----------------------------------------\n");
    }
    printf("A l'attaque moussaillon !\n\n");
}

int DemanderPosition(char question[],int lowerBound, int upperBound)
{
    int val = DEFAULT_VALUE;

    do
    {
        fflush(stdin);
        printf("%s",question);
    } while((scanf("%i", &val) == 0) || (val > upperBound) || (val < lowerBound));

    return val;
}

int VerifCoule(int numBateau, int boat[10][10])
{
    int i = DEFAULT_VALUE, j = DEFAULT_VALUE, down = DEFAULT_VALUE, boatDown = DEFAULT_VALUE;

    down = 0;
    boatDown = 0;

    for (i = 0; i < 10; i++)
        {
            for (j = 0; j < 10; j++)
            {
                if (boat[i][j] == numBateau)
                {
                    down++;
                }
            }
        }
    if (down == 0)
    {
        switch (numBateau)
        {
            case 1:
                printf("Bravo ! Vous avez coul‚ le torpilleur !\n");
                boatDown = 1;
                break;

            case 2:
                printf("Bravo ! Vous avez coul‚ le sous-marin !\n");
                boatDown = 1;
                break;

            case 3:
                printf("Bravo ! Vous avez coul‚ le contre-torpilleur !\n");
                boatDown = 1;
                break;

            case 4:
                printf("Bravo ! Vous avez coul‚ le croiseur !\n");
                boatDown = 1;
                break;

            case 5:
                printf("Bravo ! Vous avez coul‚ le porte-avion !\n");
                boatDown = 1;
                break;

            default:
                break;
        }
    }
    return boatDown;
}

void AfficherInfo(int ligne, int nbtir, int erreur)
{
    switch (ligne)
    {
        case 8:
            printf("\t\t\t Capitaine: %s", login);
            break;

        case 9:
            if (erreur == 1)
            {
                nbtir--;
            }
            printf("\t\t\t Nombre de tir effectu‚s: %2i", nbtir);
            break;

        default:
            break;
    }
}

void PositionBateau(int boat[10][10])
{
    int x = DEFAULT_VALUE, y = DEFAULT_VALUE, numBoat = DEFAULT_VALUE, verifFin = DEFAULT_VALUE;
    char charGrille[2];
    charGrille[1]='\0'; //\0 indique la fin de la chaŒne de caractŠre.

    srand(time(NULL));
    numGrille = 0;
    numGrille = (rand() % 2 + 1);

    switch(numGrille)   //Conversion du chiffre al‚atoire en string pour l'ouverture du fichier. le nombre … deux chiffres correspondt au code ASCII (49 = 1 en code ASCII)
    {
        case 1:
            charGrille[0] = 49;
            break;

        case 2:
            charGrille[0] = 50;
            break;

        default:
            break;
    }

    FILE *grilleboat = NULL;    //Ouverture du fichier contenant les coordonn‚es de la position des bateaux

    grilleboat = fopen(charGrille, "r");

    if (grilleboat == NULL)
    {
        printf("\nErreur ! Le fichier n'existe pas. Veuillez relancer le programme.\n");
        Sleep(60000);
    }
    else
    {
        verifFin = 0;

        while(verifFin != EOF)
        {
            verifFin = fscanf(grilleboat, "%i %i %i", &x, &y, &numBoat);     //Inscritption des coordonn‚es du fichier dans la grille bateau
            boat[x][y] = numBoat;
        }

        fclose(grilleboat);
    }

}

void EcritureLog()
{
    time_t rawtime; //Initialisation de la date
    time (&rawtime);

    FILE *LogPartie = NULL;
    LogPartie = fopen("LogPartie.txt", "a+");

    if (LogPartie != NULL)
    {
        fprintf(LogPartie,"%s\nA joue sur la grille: %i\nDate: %s\n\n", login, numGrille, ctime (&rawtime));
    }

    fclose(LogPartie);
}

int Jeu()
{
    int ligne = DEFAULT_VALUE, col = DEFAULT_VALUE, x = DEFAULT_VALUE, y = DEFAULT_VALUE, i = DEFAULT_VALUE, j = DEFAULT_VALUE, erreur = DEFAULT_VALUE, nbtir = DEFAULT_VALUE;
    int numBateau = DEFAULT_VALUE, down = DEFAULT_VALUE, nbBoat = 5;
    char retour_menu = DEFAULT_CHAR;
    char tab[10][10];
    int boat[10][10];

    //Initialisation de la grille
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            tab[i][j] = ' ';
        }
    }

    //Initialisation de la position des bateaux
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            boat[i][j] = 0;
        }
    }

    PositionBateau(boat);

    //L'utilisateur s'authentifie, confirme et le programme affiche la grille
    Login();
    EcritureLog();
    system("cls");
    AfficherGrille();

    //L'utilisateur a le droit … 50 tirs
    for (nbtir = 1; nbtir <= NBTIR_MAX; nbtir++)
    {
        //L'utilisateur entre les coordonn‚es
        x = DemanderPosition("Entrez un num‚ro de ligne (de 0 … 9): ", 0, 9);
        y = DemanderPosition("Entrez un num‚ro de colonne (de 0 … 9): ", 0, 9);
        numBateau = boat[x][y];

        system("cls");

        //V‚rification si le tir a ‚t‚ effectu‚ sur une case d‚j… s‚lectionn‚e
        if ((tab[x][y] == 'X') && (boat[x][y] == -1) || (tab[x][y] == '1'))
        {
            erreur = 1;
        }

        //Affichage de la grille avec les coordonn‚es entr‚es
        printf("      0   1   2   3   4   5   6   7   8   9\n");
        printf("    -----------------------------------------\n");
        for (col = 0; col < 10; col++)
        {
            printf("%2d  ",col);
            for (ligne = 0; ligne < 10; ligne++)
            {
                //v‚rification si les coordon‚es entr‚es correspondent … un emplacement de bateau
                if (boat[x][y] != 0)
                {
                    tab[x][y] = 'X';
                    boat[x][y] = -1;
                }
                else
                {
                    tab[x][y] = '1';
                }
                printf("| %c ",tab[col][ligne]);
            }
            printf("|");

            //Affichage des information de la partie
            AfficherInfo(col, nbtir, erreur);
            printf("\n");
            printf("    -----------------------------------------\n");
        }

        //Commentaire de l'action de l'utilisateur
        if (erreur == 1)
        {
            printf("Vous avez d‚j… tir‚ sur cette case !\n");
            nbtir--;
            erreur = 0;
        }
        else if (tab[x][y] == 'X')
        {
            printf("Touch‚ !\n");
        }
        else if (tab[x][y] == '1')
        {
            printf("Rat‚ !\n");
        }

        if ((VerifCoule(numBateau, boat)) == 1)
        {
            nbBoat--;
        }

        if (nbBoat == 0)
        {
            break;
        }
    }
    if (nbtir < (NBTIR_MAX + 1))
        {
            printf("VICTOIRE !");
        }
    else if (nbtir == (NBTIR_MAX + 1))
        {
            printf("Zut ! Vous avez perdu !");
        }

    EcritureScores(nbtir);

    return nbtir;
}

void AideDuJeu()
{
    system("cls");
    printf("RŠgles:\n\tVous aurez devant vous une grille sur laquelle sont dispos‚s plusieurs bateaux de diff‚rentes tailles.\n");
    printf("\tVous devrez entrer les coordonnees d'une case afin d'y envoyer un missile.\n");
    printf("\tLe but du jeu est de couler tous les bateaux pr‚sent sur la grille en touchant chacune des cases\n\tqu'il occupe a l'aide d'un missile\n");
    printf("\tMoins vous effectuerez de coups, meilleur sera votre score !");
    printf("\n\n");
    printf("La grille contient:\n");
    printf("\t1 porte-avions (5 cases)\n");
    printf("\t1 croiseur (4 cases)\n");
    printf("\t1 contre-torpilleur (3 cases)\n");
    printf("\t1 sous-marin (3 cases)\n");
    printf("\t1 torpilleur (2 cases)\n");
    printf("\n\n");
    printf("Commandes du programme au menu:\n");
    printf("\t\"j\": Commencer … jouer\n");
    printf("\t\"a\": Afficher l'aide\n");
    printf("\t\"s\": Afficher les scores\n");
    printf("\t\"q\": Quitter le programme\n");

    RetourMenu();
}

void EcritureScores(int score)
{
    FILE *scores = NULL;    //Ouverture du fichier contenant les scores
    scores = fopen("scores", "a+");

    score--;

    if (scores != NULL)
    {
        fprintf(scores,"  %20s \t\t%i\n", login, score);
    }
    fclose(scores);
}

void LireScores()
{
    char lettre = DEFAULT_CHAR;

    FILE *scores = NULL;
    scores = fopen("scores", "r");

    if (scores != NULL);
    {
        do
        {
            lettre = fgetc(scores);

            if (lettre != EOF)
            {
                printf("%c", lettre);
            }
        }while (lettre != EOF);

        fclose(scores);
    }

}

void ScoresDuJeu()
{
    system("cls");
    printf("\n\t      Joueur \t   Nombre de tir\n\n");
    LireScores();
    RetourMenu();
}

