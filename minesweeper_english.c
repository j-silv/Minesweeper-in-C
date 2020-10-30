#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int TAILLE=5;      //marche jusqu'a TAILLE = 10! apres, dus aux numeros (2 chiffres) les espaces sont un peu decales
int NB_MINES=3;    //change comme tu veux. le # de drapeau changera automatiquement




int i,j,k;      //vu que ces variables "compteurs" sont utilises par beaucoup de fonctions, je l'ai mis comme variables globales
typedef enum {VRAI=1,FAUX=0}Bouleen;
typedef enum {BOMBE=1,RIEN=0}PossibleSousTerre;
typedef enum {DRAPEAU = 1, FOUILLE = 2, INCONNU = 0}PossibleEnSurface;
typedef struct {
    PossibleSousTerre sousTerre;
    PossibleEnSurface surface;
    int nbAutour;
} CaseTerrain;


//Initialiser toutes les cases
void creerChampDeMines(CaseTerrain champ[TAILLE][TAILLE]){

    int xDep=0;
    int yDep=0;

    for (i = 0; i<TAILLE;i++){
        for (j=0; j<TAILLE;j++){
            champ[i][j].sousTerre=RIEN;
            champ[i][j].surface=INCONNU;
            champ[i][j].nbAutour=0;
        }
    }

    //mets les bombes dans les cases d'une maniere aleatoire
    for (i=1;i<=NB_MINES;i++){
        xDep=rand()%TAILLE;
        yDep=rand()%TAILLE;

        while (champ[xDep][yDep].sousTerre==BOMBE){     //verifie qu'il n'y a pas de bombe deja mise
                xDep=rand()%TAILLE;                     //si c'est le cas, continue a chercher d'autres cases
                yDep=rand()%TAILLE;
        }
    champ[xDep][yDep].sousTerre=BOMBE;
    }

return;
}



void afficheChamp(CaseTerrain champ[TAILLE][TAILLE], int nbDrapeauRestants, Bouleen modeDebug){

    printf("You have %d flags left!\n\n",nbDrapeauRestants);
    printf("     ");

    //IMPRIME LES COLONNES NUMERES
    for (i=0;i<TAILLE;i++){
        printf("%d ",i);
    }

    //*MODE DEBUG* IMPRIME LES COLONNES NUMERES
    if (modeDebug == VRAI){
        printf("                      ",i);
        for (i=0;i<TAILLE;i++){
            printf("%d ",i);
        }
    }

    printf("\n    ");

    //IMPRIME LES LIMITES HORIZ.
    for (i=0;i<(2*TAILLE);i++){    //Algorithme simple pour qu'un champ de taille +5 s'imprime correctement
    printf("_");
    }


    //*MODE DEBUG* IMPRIME LES LIMITES HORIZ.
    if (modeDebug == VRAI){
        printf("                      ");

        for (i=0;i<(2*TAILLE);i++){
            printf("_");
        }
    }

    printf("\n");

    //IMPRIME LES LIMITES VERT.
    for (i = 0; i<TAILLE;i++){
        printf(" %d | ",i);

        //IMPRIME SURFACE
        for (j=0; j<TAILLE;j++) {
            switch (champ[i][j].surface){
                case DRAPEAU: printf("%c ",'^');
                    break;

                case FOUILLE: printf("%d ",champ[i][j].nbAutour);
                    break;

                case INCONNU: printf("%c ",'.');
                    break;
            }
        }

    //*MODE DEBUG* IMPRIME SURFACE
    if (modeDebug == VRAI){
        printf("                     ");
        for (j=0; j<TAILLE;j++){
            printf("%d",champ[i][j].surface);
            printf("%d",champ[i][j].sousTerre);
        }
    }


        printf("\n");
    }

return;
}


int compterMinesAutour(CaseTerrain champ[TAILLE][TAILLE], int x, int y){
    //initialise a zero chaque fois la fonction est appele pour eviter de resultats faux
    int nbM=0;

    //cherche les 8 cases (sauf si on est aux limites) autour d'une case fouille
    //les conditions supplementaires evitent des cases qui ne sont pas initalises. Autrement dit, elles evitent les limites
    if (champ[x-1][y-1].sousTerre==BOMBE && x!=0 && y!=0){
        nbM++;
    }

    if (champ[x-1][y].sousTerre==BOMBE && x!=0){
        nbM++;
    }

    if (champ[x-1][y+1].sousTerre==BOMBE && x!=0 && y!=(TAILLE-1)){
        nbM++;
    }

    if (champ[x][y-1].sousTerre==BOMBE && y!=0){
        nbM++;
    }

    if (champ[x][y+1].sousTerre==BOMBE && y!=(TAILLE-1)){
        nbM++;
    }

    if (champ[x+1][y-1].sousTerre==BOMBE && x!=(TAILLE-1) && y!=0){
        nbM++;
    }

    if (champ[x+1][y].sousTerre==BOMBE && x!=(TAILLE-1)){
        nbM++;
    }

    if (champ[x+1][y+1].sousTerre==BOMBE && x!=(TAILLE-1) && y!=(TAILLE-1)){
        nbM++;
    }

return (nbM);
}

Bouleen partieGagnee(CaseTerrain champ[TAILLE][TAILLE]){

    //Cherche chaque case et augmente k chaque fois un drapeau est mis au-dessus d'une bombe
    for (i=0,k=0; i<TAILLE;i++){
        for (j=0; j<TAILLE;j++){
            if (champ[i][j].surface==DRAPEAU && champ[i][j].sousTerre==BOMBE){
                k++;
            }
        }
    }

    if (k==NB_MINES){  //GAGNE
        return (VRAI);
    }

    else{
        return (FAUX);
    }
}


//fonction qui affiche la solution du champ quand tu gagnes/perds, etc.
void afficheFin(CaseTerrain champ[TAILLE][TAILLE]){
    printf("The solution of the mine field : \n\n");
    printf("     ");

     //IMPRIME LES COLONNES NUMERES
    for (i=0;i<TAILLE;i++){
        printf("%d ",i);
    }

    //IMPRIME LES LIMITES HORIZ.
    printf("\n    ");
    for (i=0;i<(2*TAILLE);i++){    //Algorithme simple pour qu'un champ de taille +5 s'imprime correctement
        printf("_");
    }

    printf("\n");

    //IMPRIME LES FRONTIERES VERT.
    for (i = 0; i<TAILLE;i++){
        printf(" %d | ",i);

        //IMPRIME SOUSTERRE
        for (j=0; j<TAILLE;j++){
            switch (champ[i][j].sousTerre){

                case BOMBE: printf("%c ",'X');
                    break;

                case RIEN: printf("%c ",'.');
                    break;
            }
        }

        printf("\n");
    }

printf("\n");

return;

}


//j'ai code la fonction suivante en copiant l'algorithime de compterMinesAutour-
//en evitant de manipuler les cases qui ne sont pas initialise
void explorer(CaseTerrain champ[TAILLE][TAILLE], int x, int y, int nbM){


    if (champ[x][y].nbAutour==0) {

    //la derniere condition verifie que la case n'est pas deja fouille. cela evite une boucle infini

        //   [<^]     -->     REGARDE CASE EN HAUT GAUCHE DIAGONALE
        if (x!=0 && y!=0 && champ[x-1][y-1].surface!=FOUILLE ){

            champ[x-1][y-1].surface=FOUILLE;
            nbM=compterMinesAutour(champ,x-1,y-1);
            champ[x-1][y-1].nbAutour=nbM;
            explorer(champ,x-1,y-1,nbM);       //FONCTION RECURSIVE
        }
        //    [^]
        if (x!=0 && champ[x-1][y].surface!=FOUILLE){

            champ[x-1][y].surface=FOUILLE;
            nbM=compterMinesAutour(champ,x-1,y);
            champ[x-1][y].nbAutour=nbM;
            explorer(champ,x-1,y,nbM);
        }
        //    [^>]
        if (x!=0 && y!=(TAILLE-1) && champ[x-1][y+1].surface!=FOUILLE){    //

            champ[x-1][y+1].surface=FOUILLE;
            nbM=compterMinesAutour(champ,x-1,y+1);
            champ[x-1][y+1].nbAutour=nbM;
            explorer(champ,x-1,y+1,nbM);
        }
        //    [>]
        if (y!=(TAILLE-1) && champ[x][y+1].surface!=FOUILLE){

            champ[x][y+1].surface=FOUILLE;
            nbM=compterMinesAutour(champ,x,y+1);
            champ[x][y+1].nbAutour=nbM;
            explorer(champ,x,y+1,nbM);
        }
        //    [v>]
        if (x!=(TAILLE-1) && y!=(TAILLE-1) && champ[x+1][y+1].surface!=FOUILLE){

            champ[x+1][y+1].surface=FOUILLE;
            nbM=compterMinesAutour(champ,x+1,y+1);
            champ[x+1][y+1].nbAutour=nbM;
            explorer(champ,x+1,y+1,nbM);
        }
        //    [v]
        if (x!=(TAILLE-1) && champ[x+1][y].surface!=FOUILLE){

            champ[x+1][y].surface=FOUILLE;
            nbM=compterMinesAutour(champ,x+1,y);
            champ[x+1][y].nbAutour=nbM;
            explorer(champ,x+1,y,nbM);
        }
        //     [<v]
        if (x!=(TAILLE-1) && y!=0 && champ[x+1][y-1].surface!=FOUILLE){

            champ[x+1][y-1].surface=FOUILLE;
            nbM=compterMinesAutour(champ,x+1,y-1);
            champ[x+1][y-1].nbAutour=nbM;
            explorer(champ,x+1,y-1,nbM);
        }
        //     [<]
        if (y!=0 && champ[x][y-1].surface!=FOUILLE){

            champ[x][y-1].surface=FOUILLE;
            nbM=compterMinesAutour(champ,x,y-1);
            champ[x][y-1].nbAutour=nbM;
            explorer(champ,x,y-1,nbM);
        }
    }

    return;
}



int main(int nbM){

    printf("What size mine field would you like (1-10)? : ");
    scanf("%d",&TAILLE);
    printf("How many mines? : ");
    scanf("%d",&NB_MINES);

    CaseTerrain champMines[TAILLE][TAILLE];
    int nbDrapeauRestants = NB_MINES,x,y;
    char action;

    //Change a VRAI pour voir si le programme fonctionne comme il faut
    Bouleen modeDebug = FAUX;

    //quand fini == VRAI le programme se termine
    Bouleen fini = FAUX;

    srand(time(NULL));
    creerChampDeMines(champMines);



    printf("\n\nHello! Welcome to the game: *MINESWEEPER*\n\n");
    printf("The rules are simple... Avoid the mines. (There are %d of them!)\n\n",NB_MINES);
    printf("To win, you have to place your flags on the squares that you think house the mines.\n\n");
    printf("GOOD LUCK!!!\n");
    printf("----------------------------------------------------------------------\n\n\n");


    //boucle principale
    do{

        afficheChamp(champMines, nbDrapeauRestants,modeDebug);
        printf("\n[S] to select a square, [F] to place a flag, [Q] to quit ? : ");
        scanf(" %c", &action);


        //JOUEUR CHOISIT DE MARCHER
        if (action == 's' || action == 'S'){

            printf("Where do you want to go ?\n\n");
            printf("Row : ");
            scanf("%d",&x);
            printf("Column : ");
            scanf("%d",&y);
            printf("\n");
            printf("You selected %d, %d -->\n",x,y);

            //AFFICHE CONSEQUENCE D'ACTION
            switch (champMines[x][y].sousTerre){

            case RIEN: printf("WHEW.... No mine here!\n\n");

                    if (champMines[x][y].surface==DRAPEAU){  //**au cas ou le joueur marche dans une case avec un drapeau
                    printf("You picked up a flag at %d, %d\n",x,y);
                    nbDrapeauRestants++;
                    }

                    champMines[x][y].surface=FOUILLE;
                    nbM=compterMinesAutour(champMines,x,y);
                    printf("\nOK, there are %d mine(s) around this square!\n\n",nbM);
                    champMines[x][y].nbAutour=nbM;
                    explorer(champMines,x,y,nbM);

                break;

            case BOMBE: printf("****BOOM!!!!****\n");

                    printf("Darn! You stepped on a mine...\n\n");
                    afficheFin(champMines);
                    fini=VRAI;

                break;
            }

        }


        //JOUEUR CHOISIT DE POSER UN DRAPEAU
        if (action == 'f' || action == 'F'){

            if (nbDrapeauRestants!=0){

                printf("Where do you want to place a flag ?\n\n");
                printf("Row : ");
                scanf("%d",&x);
                printf("Column : ");
                scanf("%d",&y);
                printf("\n");

                //OPTION DE RECUPERER LE DRAPEAU
                if (champMines[x][y].surface==DRAPEAU){
                    printf("You picked up a flag at %d, %d\n\n",x,y);
                    nbDrapeauRestants++;
                    champMines[x][y].surface=INCONNU;
                }

                else{
                    printf("You placed a flag at %d, %d -->\n\n",x,y);
                    champMines[x][y].surface=DRAPEAU;
                    nbDrapeauRestants--;
                }
            }

            else{
                printf("You don't have any more flags! Sorry...\n\n");
            }
        }


        //OPTION D'ABANDONNER SI LE JOUEUR A TROP PEUR
        if (action == 'Q' || action == 'q'){

            printf("Aww... you quit! What a shame.\n\n");
            afficheFin(champMines);
            fini=VRAI;
        }

        //apres chaque tour voir si le joueur a gagne
        if (partieGagnee(champMines)==VRAI){
            printf("BRAVO, YOU WON!!! All the mines were found!\n\n");
            afficheFin(champMines);
            fini=VRAI;
        }

    }while (fini==FAUX);

printf("Thanks for playing! Restart the program to play again\n");

system("pause");

return 0;
}
