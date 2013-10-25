#include <stdio.h>
#include <stdlib.h>
#include <myconio.h>
#include <time.h>
#include <myconio.h>

int n=0,m=0,partie=0;


//==============================================================================//
// Procédure d'initialisation du tableau                                        //
// >procédure appelée dans le main                                              //
//==============================================================================//
void initTab(int tab[][n])
{
    int i,j;
    for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                if(i==0 || j==0 || i==n-1 || j==n-1)
                tab[i][j] = 10 ;
                else
                tab[i][j] = 0 ;
            }
        }
}

//==============================================================================//
// Procédure pour faire le choix                                                //
// >procédure appelée dans le main                                              //
//==============================================================================//
void choix()
{
    system("cls");
    textcolor(10);
    int t=0;
    gotoxy(10,1);
printf("_________________________________\n");
gotoxy(10,2);
printf("|                               |\n");
gotoxy(10,3);
printf("|  BIENVENUE DANS LE DEMINEUR   |\n");
gotoxy(10,4);
printf("|_______________________________|\n");


do //choix taille tableau
{
    gotoxy(5,6);
    printf("Quelle taille de tableau desirez-vous ?\n    1- 10\n    2- 15\n    3- 20\n");
    gotoxy(5,10);
    scanf("%d",&t);
    switch (t)
    {
    case 1 : n=12; break;
    case 2 : n=17; break;
    case 3 : n=22; break;
    default : printf("Choix errone, veuillez refaire votre choix.\n\n");break;
    }
}while (t<1 || t>3);

do //choix nombre de mines suivant la difficulté
{
    gotoxy(5,6);
    printf("Niveau de difficulte ?                         \n    1- Facile\n    2- Intermediaire\n    3- Avance\n");
    gotoxy(5,10);
    printf(" ");
    scanf(" %d",&t);
    switch (t)
    {
    case 1 : m=(n-2)*(n-2)*0.1; break; //10% de la surface en facile
    case 2 : m=(n-2)*(n-2)*0.2; break; //20% de la surface en intermédiaire
    case 3 : m=(n-2)*(n-2)*0.3; break; //30% de la surface en avancé
    default : printf("Choix errone, veuillez refaire votre choix.\n\n");
    }

}while (t<1 || t>3);
textcolor(7);
}

//==============================================================================//
// Procédure pour afficher le tableau, partie graphique                         //
// >procédure appelée dans le main                                              //
//==============================================================================//
void affichTab(int tab[][n])
{
    system("cls");
    int i,j;
    char a=197,b=219,c=32;

    for(i=1; i<2*n-2; i++)
    {
        for(j=1; j<2*n-2; j++)
        {
            if(i%2==1 && j%2==1)
            {
                gotoxy(i,j);
                printf("%c",a);

            }
            else if(i%2==0 && j%2==0)
            {
                gotoxy(i,j);
                printf("%c",b);
            }
            else {gotoxy(i,j);printf("%c",c);}
        }
        printf("\n");
    }

    gotoxy(2*n+1,2);
    textcolor(30);
    printf("> == LEGENDE == <");

    gotoxy(2*n+1,4);
    printf("** touche e : marquer une mine **");
    gotoxy(2*n+1,6);
    printf("** touche f : fouiller une case **");
    gotoxy(2*n+1,8);
    printf("** touche echap : quitter sans preavis **");
    gotoxy(2*n+1,10);
    printf("** touche directionnelles pour vous deplacer **");
    textbackground(0);

    textcolor(7);

}

//==============================================================================//
// Procédure pour afficher la solution si perdu                                 //
// >procédure appelée dans le main                                              //
//==============================================================================//
void affichSolu(int tab[][n])
{
    int i,j;
    char a=197,c=32;
    for(i=1; i<2*n+30; i++) // netoyage avant affichage solution
    {
        for(j=1; j<2*(n-1); j++)
        {
                gotoxy(i+2*n,j);
                printf("%c",32);
        }
        printf("\n");
    }

    for(i=1; i<2*(n-1); i++) //affichage de la solution
    {
        for(j=1; j<2*(n-1); j++)
        {
            if(i%2==1 && j%2==1) {gotoxy(i+2*n,j);printf("%c",a);}
            else if(i%2==0 && j%2==0)
            {
                gotoxy(i+2*n,j);
                if(tab[i/2][j/2]==99 || tab[i/2][j/2]==9)
                {
                    textcolor(12);
                    printf("%c",42); //affichage caractère étoile
                    textcolor(7); //couleur de base caractère
                }
            }
            else {gotoxy(i+2*n+1,j);printf("%c",c);}
        }
        printf("\n");
    }
    textbackground(0);
}

//==============================================================================//
// Procédure pour placer les mines et quantification                            //
// des cases pour les mines périphériques                                       //
// >procédure appelée dans le main                                              //
//==============================================================================//
void placeMines(int tab[][n])
{

    int a,mine=0; //compteur de base pour les boucles
    int i=0,j=0; //coordonnées du tableau

    for(a=0;a<m;a++)//placement des mines avec coordonnées aléatoires
    {
        i=rand()%(n-2)+1; //rand d'intervale n taille décalé de +1 pour i;
        j=rand()%(n-2)+1; //rand d'intervale n taille décalé de +1 pour j;
        tab[i][j]=9;  //9 signifie mine sur la case tableau
    }

    while (mine<m)//phase de vérification du nombre de mines et ajout si complément nécessaire
    {
        for(i=1; i<n-1; i++) //contrôle du nombre de mines avant ajout
        {
            for(j=1; j<n-1; j++)
            {
                if(tab[i][j] == 9) mine++;

            }
        }

        if(mine<m) //placement des mines manquantes, même principe
        {
            i=rand()%(n-2)+1;
            j=rand()%(n-2)+1;
            tab[i][j]=9;
        }
    }


    for(i=1; i<n-1; i++) //quantification des mines périphériques
    {
        for(j=1; j<n-1; j++)
        {
            if(tab[i][j] == 0) tab[i][j]=comptPerif(tab,i,j);
        }
    }
}

//==============================================================================//
// Fonction qui calcul le nombre de mines autour                                //
// >fonction qui est appelée par placeMines                                     //
//==============================================================================//
int comptPerif(int tab[][n],int colM, int ligneM)
{
    int i,j,comptM=0;
    for(i=colM-1; i<=colM+1; i++)
    {
        for(j=ligneM-1; j<=ligneM+1; j++)
        {
            if(tab[i][j] == 9) comptM++;
        }
    }
    return comptM;
}

//==============================================================================//
// Procédure de dégagement des cases vides                                      //
// >procédure qui est appelée par fouille                                       //
//==============================================================================//
void degagC(int tab[][n],int colD, int ligneD) //cas où la case = 0
{
    int i,j;

    for(i=colD-1; i<=colD+1; i++) //découverte des contours
    {
        for(j=ligneD-1; j<=ligneD+1; j++)
        {
            if(tab[i][j]>0 && tab[i][j]<9)
            {
                gotoxy(i*2,j*2);
                textcolor(10);
                printf("%d",tab[i][j]);
                textcolor(7);
            }
            if(tab[i][j]==0 || tab[i][j]>11)
            {
                gotoxy(i*2,j*2);
                textcolor(0);
                printf("%c",32);
                textcolor(7);

                tab[i][j]=11;

                degagC(tab,i,j);
            }
        }
    }
}

//==============================================================================//
// Procédure de dégagement des cases séléctionnées                              //
// >procédure qui est appelée par moove                                         //
//==============================================================================//
void fouille(int colF, int ligneF, int tab[][n])
{

    if(tab[colF][ligneF]==0)
    {
        degagC(tab,colF,ligneF);
    }
    if (tab[colF][ligneF]>0 && tab[colF][ligneF]<9)
    {
        gotoxy(colF*2,ligneF*2);
        textcolor(10);
        printf("%d",tab[colF][ligneF]);
        textcolor(7);
    }
    if(tab[colF][ligneF]==9)
    {
        gotoxy(colF*2,ligneF*2);
        textcolor(29);
        printf("%c",15);
        textcolor(7);
        partie=1;
        textbackground(0);
    }
}

//==============================================================================//
// Procédure de marquage des cases séléctionnées                                //
// >procédure qui est appelée par moove                                         //
//==============================================================================//
void target(int colT, int ligneT, int tab[][n])
{
    int cptM=0,i,j,cM=0;

    if(tab[colT][ligneT]==9 && cM<=m) //cas marquage sur mine qui existe
    {
        tab[colT][ligneT]=99;
        gotoxy(colT*2,ligneT*2);
        textcolor(12); //affichage couleur marrond
        printf("%c",15); //affichage caractère étoile
        textcolor(7); //couleur de base caractère

    }else

    if(tab[colT][ligneT]>=0 && tab[colT][ligneT]<9 && cM<=m) //cas marquage sur mine qui n'existe pas
    {
        gotoxy(colT*2,ligneT*2);
        textcolor(12);//affichage couleur marrond
        printf("%c",15);//affichage caractère étoile
        textcolor(7); //retour couleur de base caractère
        tab[colT][ligneT]+=20;
    }else

    if(tab[colT][ligneT]==99)  //cas marquage sur mine qui existe mais dèjà marquée
    {
        gotoxy(colT*2,ligneT*2);
        textcolor(7); //on revient sur la couleur jaune
        printf("%c",219); //réaffichage du caractère rectangle remplis
        textcolor(7); //retour couleur de base caractère
        tab[colT][ligneT]=9;
    }else

    if(tab[colT][ligneT]>20 && tab[colT][ligneT]<29) //cas marquage sur mine qui n'existe pas mais dèjà marquée
    {
        gotoxy(colT*2,ligneT*2);
        textcolor(7); //on revient sur la couleur jaune
        printf("%c",219); //réaffichage du caractère rectangle remplis
        textcolor(7); //retour couleur de base caractère
        tab[colT][ligneT]-=20;
    }

    for(i=1; i<n-1; i++) //comptage du nombre de mines pour marquage correcte
    {
        for(j=1; j<n-1; j++)
        {
            if(tab[i][j] == 99) cptM++;
        }
    }

    /*for(i=1; i<n-1; i++) //calcul du nombre de mines restants à trouver par rapport à celles marquées
    {
        for(j=1; j<n-1; j++)
        {
            if(tab[i][j] == 99 || (tab[i][j]>20 && tab[i][j]<29)) cM++;
        }
    }*/
    gotoxy(2*n+1,14);
    textcolor(5);
    printf("Il y a %d mines a trouver.",m);
    gotoxy(2*n+1,16);
    /*printf("%d mines ont ete marquees.",cM);
    textcolor(7);*/

    if(m==cptM)
    {
        partie=3;
    }

}

//==============================================================================//
// Procédure d'interprétation des touches appuyées                              //
// >procédure qui est appelée dans le main                                      //
//==============================================================================//
void moove (int tab[][n])
{
char touche;
int x=2,y=2;
gotoxy(2,2);

//x colonne et y ligne
    while (partie==0) //touche échap
    {
       gotoxy(x,y);
       touche = getch();
       switch(touche)
       {
           case 72 : //touche haut
           if(y>1)
           {
               y-=2; //on monte d'une ligne
               gotoxy(x,y);
               break;
           }
           case 77 : //touche droite
           if(x<2*(n-2))
           {
               x+=2;
               gotoxy(x,y);
               break;
           }
           case 80 : //touche bas
           if(y<2*(n-2))
           {
               y+=2;
               gotoxy(x,y);
               break;
           }
           case 75 : //touche gauche
           if(x>1)
           {
               x-=2;
               gotoxy(x,y);
               break;
           }
           case 27 : //touche échap
               system("cls");
               partie=2;
               break;

           case 102 : //touche f pour fouiller

           fouille(x/2,y/2,tab);
           gotoxy(x,y);
           break;

           case 101 : //touche e pour marquer les mines

           target(x/2,y/2,tab);
           break;
       }
    }
}


main()
{

    srand(time(NULL));
    int tab[n][n];
    int choixR=0;

    do
    {
        textbackground(0);
        choix(); //appel de la procédure choix

        int tab[n][n];

        initTab(tab); //appel de la procédure d'initialisation du tableau

        placeMines(tab); //appel de la procédure placement des mines

        affichTab(tab); //appel de la procédure pour afficher le tableau et la légende

        moove(tab); //appel de la procédure d'interprétation des touches


        if(partie==1)
        {
            affichSolu(tab); //appel de la procédure d'affichage de la solution si mine sélectionnée
            gotoxy(8,2*n+2);
            textcolor(13);
            printf("Navre, vous avez perdu... Voulez-vous recommencer une partie ?\n       1- Oui\n       2- Non\n");
            scanf("%d",&choixR);
            textcolor(7);
            if(choixR==1){
                partie=0;
                system("cls");
            }
            else
            {
            system("cls");
            gotoxy(8,2*n+2);
            printf("Au revoir !");
            }
        }
        if(partie==3 || partie==2)
        {
            gotoxy(8,2*n+2);
            if(partie==3)
            printf("Bravo, vous avez gagne ! Voulez-vous recommencer une partie ?\n    1- Oui\n    2- Non\n");
            else
            {
                gotoxy(5,6);
                printf("Vous avez quitte. Voulez-vous recommencer une partie ?\n    1- Oui\n    2- Non\n");
            }

            scanf("%d",&choixR);
            if(choixR==1)
            {
                partie=0;
            }
            else
            {
            system("cls");
            printf("\n\n\n          Au revoir !\n\n\n");
            system("pause");
            partie=1;
            }
        }
    }while (partie==0);
}


