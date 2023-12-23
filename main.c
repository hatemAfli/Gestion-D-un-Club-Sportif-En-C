
#include <stdio.h>
#include <stdlib.h>
#include"club.h"
#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
struct liste lj ;

joueur j ;
FILE *fj ;
int pos ,i,code_j;
char num[8] ;
categorie c ;
date d ;
#include <tchar.h>


#include <windows.h>
#include<conio.h>


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
void addmenus(HWND);
void CreateBtt(HWND hwnd) ;

HWND hname ,hage,hout,hogo,Add,Finnish;
 HDC hdc;
HMENU hmenu ;

HBITMAP hlogoImage , hgenerateImage;
int intro=1 ;
char ch[30] ;
long p ;
/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("my projet");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND+6;


    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Club Sportif Realiséé par AfLi HaTem"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           1400,                 /* The programs width */
           1250,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{static HBITMAP  hBmp;


    /*if(intro)
    {
        system("start test.exe") ;
        intro=0;
    }*/

    switch (message)                  /* handle the messages */
    {

        case WM_COMMAND:
        switch(wParam)
        {
        case 1:
                system("color FC");
                ShowWindow(hwnd,SW_HIDE);
                fj=fopen("joueur.txt","r") ;
                if (feof(fj))
                {printf("    REMPLISSAGE DE LISTE : ");
                remplir_liste(&lj) ;
                }
                else
                MessageBox(0,"Le Fichier n'est pas vide !! Essayer De Recuperer Les Information ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
        case 2:
                system("color FC");
                ShowWindow(hwnd,SW_HIDE);
                printf("                               ****************************\n");
                printf("                               * AJOUT D'UN NOUVEL JOUEUR *\n");
                printf("                               **************************** \n");
                tableau(8,5,1,1,60,2) ;
                gotoxy(30,6);
                printf("AJOUT DE JOUEUR EN TETE");
                j=saisie(lj) ;
                insere_tete(j,&lj)  ;
                printf("\n\n" );
                printf("                               ****************************\n") ;
                printf("                               *      AJOUT REUSSI      *\n") ;
                printf("                               ****************************\n") ;
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
        case 3:
                system("color FC");
                ShowWindow(hwnd,SW_HIDE);
                printf("                               ****************************\n") ;
                printf("                               * AJOUT D'UN NOUVEL JOUEUR *\n") ;
                printf("                               **************************** \n");
                tableau(8,5,1,1,60,2) ;
                gotoxy(30,6);
                printf("AJOUT DE JOUEUR EN QUEUE");
                j=saisie(lj) ;
                insere_queu(j,&lj) ;
                printf("\n\n" );
                printf("                               ****************************\n") ;
                printf("                               *      AJOUT REUSSI      *\n") ;
                printf("                               ****************************\n") ;
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
        case 4:
                system("color FC");
                ShowWindow(hwnd,SW_HIDE);
                printf("                               ****************************\n") ;
                printf("                               * AJOUT D'UN NOUVEL JOUEUR *\n") ;
                printf("                               **************************** \n");
                tableau(8,5,1,1,60,2) ;
                gotoxy(30,6);
                printf("AJOUT DE JOUEUR EN POSITION");
                j=saisie(lj) ;
                 do
                {
                gotoxy(100,14);
                for(i=0;i<=20;i++)
                printf(" ");
                gotoxy(75,11) ;
                printf("Dans Quelle Position Voulez Vous ") ;
                gotoxy(75,14);
                printf("Ajouter (1 < position <= %d) :====> ",taille_liste(lj)) ;
                scanf("%d",&pos) ;
                fflush(stdin) ;
                }while((pos <=1) || (pos > taille_liste(lj) )) ;
                insere_pos(j,&lj,pos) ;
                gotoxy(75,16) ;
                printf("****************************\n") ;
                gotoxy(75,17);
                printf("*      AJOUT REUSSI      *\n") ;
                gotoxy(75,18);
                printf("****************************\n") ;
                gotoxy(5,30);
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
        case 5:
                system("color FC");
                ShowWindow(hwnd,SW_HIDE);
                if(liste_vide(lj))
                {
                MessageBox(0,"La Liste Est Vide ?? Essayer De Le Remplir !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else
                {
                if (MessageBox(hwnd,"       Vous Etes Entraine De Supprimer Un Joueur ?\n \n       Etes Vous Sûr ??", "Attention", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                {
                supprime_tete(&lj)  ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else
                {
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                }
        case 6:
                system("color FC");
                ShowWindow(hwnd,SW_HIDE);
                if(liste_vide(lj))
                {
                MessageBox(0,"La Liste Est Vide ?? Essayer De Le Remplir !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else
                {
                if (MessageBox(hwnd,"       Vous Etes Entraine De Supprimer Un Joueur ?\n \n       Etes Vous Sûr ??", "Attention", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                {
                supprime_queu(&lj)  ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else
                {
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                }
        case 7:
                system("color FC");
                ShowWindow(hwnd,SW_HIDE);
                //gotoxy(25,10);
                printf("                               ****************************\n");
                printf("                               *   SUPPRIMER UN JOUEUR    *\n");
                printf("                               **************************** \n");
                printf("                               *SUPPRESSION D'UNE POSITION*  \n") ;
                printf("                               ****************************  \n ");
                printf("\n\n") ;
                if(liste_vide(lj))
                {
                MessageBox(0,"La Liste Est Vide ?? Essayer De Le Remplir !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else
                {
                tableau(4,11,1,1,60,2) ;
                tableau(65,11,1,1,10,2);
                gotoxy(5,12);
                printf("Du quel position voulez-vous Supprimer ( 1< position < %d ):",taille_liste(lj));
                gotoxy(66,12) ;
                char p[taille_liste(lj)] ;
                int u=0;
                int ok=0 ;
                scanf("%s",&p)  ;
                do
                {
                u=0 ;
                ok=0;
                while(p[u] != '\0')
                {
                if(isdigit(p[u]) == 0)
                {
                ok=1 ;
                break ;
                }
                u++ ;
                }
                if(ok)
                {
                gotoxy(66,12) ;
                for(i=0;i<=5;i++)
                printf(" ") ;
                gotoxy(66,12) ;
                scanf("%s",&p)  ;
                }
                else if(atoi(p)<=1 || atoi(p)>=taille_liste(lj))
                {
                gotoxy(66,12) ;
                for(i=0;i<=5;i++)
                printf(" ") ;
                gotoxy(66,12) ;
                scanf("%s",&p)  ;
                }

                }while(ok || atoi(p)<=1 || atoi(p)>=taille_liste(lj)) ;

                if (MessageBox(hwnd,"       Vous Etes Entraine De Supprimer Un Joueur ?\n \n       Voulez-Vous Continuer ??", "Attention", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                {
                supprime_pos(&lj,atoi(p)) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else
                {
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                }

        case 8:
                system("color FC");
                ShowWindow(hwnd,SW_HIDE);
                if(liste_vide(lj))
                {
                MessageBox(0,"La Liste Est Vide ?? Essayer De Le Remplir !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else{
                printf("                               ****************************\n");
                printf("                               *   SUPPRIMER UN JOUEUR    *\n");
                printf("                               **************************** \n");
                printf("                               *   SUPPRESSION PAR CODE   *  \n") ;
                printf("                               ****************************  \n ");
                tableau(4,11,1,1,60,2) ;
                tableau(65,11,1,1,10,2);
                gotoxy(5,12);
                printf("Donner Le Code Du Joueur A Supprimer:",taille_liste(lj));
                char cd[10] ;
                int ok=0 ,i=0 ;
                gotoxy(66,12) ;
                scanf("%s",&cd) ;
                do
                {
                ok=0 ;
                i=0 ;
                while(cd[i] != '\0')
                {
                if(isdigit(cd[i]) == 0)
                {
                ok=1;
                break ;
                }
                i++ ;
                }
                if(ok)
                {
                gotoxy(66,12) ;
                for(i=0;i<=9;i++)
                printf(" ");
                gotoxy(66,12) ;
                scanf("%s",&cd) ;
                }
                } while(ok) ;
                if(!verife(atoi(cd),lj))
                {
                MessageBox(0,"La Code Saisie N'existe Pas Dans La Liste !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else
                {
                if (MessageBox(hwnd,"       Vous Etes Entraine De Supprimer Un Joueur ?\n \n       Voulez-Vous Continuer ??", "Attention", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                {
                supprime_code(&lj,atoi(cd)) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else
                {
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                }}
        case 9:
                system("color FC");
                ShowWindow(hwnd,SW_HIDE);
                if(liste_vide(lj))
                {
                MessageBox(0,"La Liste Est Vide ?? Essayer De Le Remplir !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else{

                printf("                               ****************************\n");
                printf("                               *   SUPPRIMER UN JOUEUR    *\n");
                printf("                               **************************** \n");
                printf("                               *SUPPRESSION PAR CATEGORIE *  \n") ;
                printf("                               ****************************  \n ");
                printf("\n\n") ;
                char a[10]  ;
                tableau(4,13,1,1,60,2) ;
                tableau(65,13,1,1,10,2);
                gotoxy(7,15) ;
                printf("Donner La Groupe  : ");
                gotoxy(66,15) ;
                scanf("%s",&a) ;
                do
                {
                if(strcmp(a,"mineur") && strcmp(a,"junior") && strcmp(a,"cadet"))
                {
                gotoxy(77,15) ;
                printf("La Groupe Saisi Est Incorrecte !!");
                gotoxy(66,15) ;
                for(i=0;i<=9;i++)
                printf(" ") ;
                gotoxy(66,15) ;
                scanf("%s",&a) ;

                }
                }
                while(strcmp(a,"mineur") && strcmp(a,"junior") && strcmp(a,"cadet")) ;
                gotoxy(77,15) ;
                for(i=0;i<=40;i++)
                printf(" ") ;
                if(verife_groupe(a,lj))
                {
                if (MessageBox(hwnd,"       Vous Etes Entraine De Supprimer Un Joueur ?\n \n       Voulez-Vous Continuer ??", "Attention", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                {
                supprime_par_groupe(&lj,a) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else
                {
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                }
                else
                {
                MessageBox(0,"IL N'existe Aucune Joueur De Cette Cathégorie !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }}
        case 11:
                system("color FC");
                ShowWindow(hwnd,SW_HIDE);

                if(liste_vide(lj))
                {
                MessageBox(0,"La Liste Est Vide ?? Essayer De Le Remplir !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else {
                printf("                               ****************************\n");
                printf("                               *   MODIFIER LE DONNEE     *\n");
                printf("                               **************************** \n");
                printf("                               *MODIFICATION DU CATEGORIE *  \n") ;
                printf("                               ****************************  \n ");
                printf("\n\n") ;
                char cd[10] ;
                int ok=0,i=0 ;
                printf("Donner le code du joueur : ");
                scanf("%s",&cd) ;
                ok=0 ;
                i=0 ;
                while(cd[i] != '\0')
                {
                if(isdigit(cd[i]) == 0)
                {
                ok=1;
                break ;
                }
                i++ ;
                }
                if(ok)
                {
                MessageBox(0,"La Code Saisie Est Invalide !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else if(!verife(atoi(cd),lj))
                {
                MessageBox(0,"La Code Saisie Est Inexistant Dans La Liste !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else
                {
                modifer_categorie(atoi(cd),&lj) ;
                MessageBox(0,"La Modification A Eté Effectuer Avec Succée !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }}
        case 12:
                system("color FC");
                ShowWindow(hwnd,SW_HIDE);
                if(liste_vide(lj))
                {
                MessageBox(0,"La Liste Est Vide ?? Essayer De Le Remplir !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else{
                printf("                               ****************************\n");
                printf("                               *   MODIFIER LE DONNEE     *\n");
                printf("                               **************************** \n");
                printf("                               *MODIFICATION DU TELEPHONE *  \n") ;
                printf("                               ****************************  \n ");
                printf("\n\n") ;
                tableau(4,11,1,2,60,2) ;
                tableau(65,11,1,2,10,2);
                gotoxy(7,12);
                printf("Donner Le Code De Joueur : ") ;
                gotoxy(7,15) ;
                printf("Donner Le Nouveau Numero  : ");
                gotoxy(66,12) ;
                char cd[10] ;
                int ok=0,i=0 ;
                scanf("%s",&cd) ;

                do{
                ok=0 ;
                i=0 ;
                while(cd[i] != '\0')
                {
                if(isdigit(cd[i]) == 0)
                {
                ok=1;
                break ;
                }
                i++ ;
                }
                if(ok)
                {
                gotoxy(66,12) ;
                for(i=0;i<=9;i++)
                printf(" ");
                gotoxy(66,12) ;
                scanf("%s",&cd) ;
                }

                }while( ok) ;
                if(!verife(atoi(cd),lj))
                {
                MessageBox(0,"La Code Saisie Est Inexistant Dans La Liste !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else
                {
                gotoxy(66,15);
                scanf("%s",&num) ;
                do
                {
                i=0;
                ok=0;
                while(num[i] != '\0')
                {
                if(isdigit(num[i]) == 0)
                {
                ok = 1 ;
                break ;
                }
                i++ ;
                }
                if(ok)
                {
                gotoxy(66,15) ;
                for(i=0;i<=9;i++)
                printf(" ") ;
                gotoxy(66,15) ;
                scanf("%s",&num) ;
                }
                else if(!verife_numero(atoi(num)))
                {
                gotoxy(66,15) ;
                for(i=0;i<=9;i++)
                printf(" ") ;
                gotoxy(66,15) ;
                scanf("%s",&num) ;
                }
                }while(!verife_numero(atoi(num)) || ok) ;
                if (MessageBox(hwnd,"       Vous Etes Entraine De Modifier Le Donnée D'Un Joueur ?\n \n       Voulez-Vous Continuer ??", "Attention", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                {
                modifer_telephone(code_j,atoi(num),&lj) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else
                {
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }}}
        case 13:
                system("color FC");
                ShowWindow(hwnd,SW_HIDE);
                printf("                                   ****************************\n");
                printf("                                   *  RECHERCHE ET AFFICHAGE  *\n");
                printf("                                   **************************** \n");
                printf("                                   *    CONTENU DU LISTE      *  \n") ;
                printf("                                   ****************************  \n ");
                printf("\n\n") ;
                if(liste_vide(lj))
                {
                MessageBox(0,"La Liste Est Vide ?? Essayer De Le Remplir !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else
                {affiche_liste(lj) ;
                printf("\n\n") ;
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;}
        case 14:
                system("color FC");
                ShowWindow(hwnd,SW_HIDE);
                if(liste_vide(lj))
                {
                MessageBox(0,"La Liste Est Vide ?? Essayer De Le Remplir !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else {
                printf("                                   ****************************\n");
                printf("                                   *  RECHERCHE ET AFFICHAGE  *\n");
                printf("                                   **************************** \n");
                printf("                                   *    RECHERCHE PAR CODE    *  \n") ;
                printf("                                   ****************************  \n ");
                printf("\n\n") ;
                gotoxy(2,7) ;
                char cd[10] ;
                int ok =0,i=0 ;
                printf("Donner le code du joueur a afficher : ");
                scanf("%s",&cd) ;
                ok=0 ;
                i=0 ;
                while(cd[i] != '\0')
                {
                if(isdigit(cd[i]) == 0)
                {
                ok=1;
                break ;
                }
                i++ ;
                }
                if(ok)
                {
                MessageBox(0,"La Code Saisie Est Invalide !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else if(!verife(atoi(cd),lj))
                {
                MessageBox(0,"La Code Saisie Est Inexistant Dans La Liste !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else
                {affiche_par_code(atoi(cd),lj) ;
                printf("\n\n\n\n") ;
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }}
        case 15:
                system("color FC");
                ShowWindow(hwnd,SW_HIDE);
                if(liste_vide(lj))
                {
                MessageBox(0,"La Liste Est Vide ?? Essayer De Le Remplir !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
               else {
                printf("                                   ****************************\n");
                printf("                                   *  RECHERCHE ET AFFICHAGE  *\n");
                printf("                                   **************************** \n");
                printf("                                   *  RECHERCHE PAR D-NAISS   *  \n") ;
                printf("                                   ****************************  \n ");
                printf("\n\n") ;
                d=saisie_date() ;
                system("cls") ;
                printf("                                   ****************************\n");
                printf("                                   *  RECHERCHE ET AFFICHAGE  *\n");
                printf("                                   **************************** \n");
                printf("                                   *  RECHERCHE PAR D-NAISS   *  \n") ;
                printf("                                   ****************************  \n ");
                printf("\n\n") ;
                affiche_par_date(d,lj) ;
                printf("\n\n\n\n") ;
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break; }
        case 16:
                system("color FC");
                ShowWindow(hwnd,SW_HIDE);
                if(liste_vide(lj))
                {
                MessageBox(0,"La Liste Est Vide ?? Essayer De Le Remplir !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else{
                printf("                                   ****************************\n");
                printf("                                   *  RECHERCHE ET AFFICHAGE  *\n");
                printf("                                   **************************** \n");
                printf("                                   *  RECHERCHE PAR CATEGORIE *  \n") ;
                printf("                                   ****************************  \n ");
                c=saisie_categorie() ;
                system("cls") ;
                printf("                                   ****************************\n");
                printf("                                   *  RECHERCHE ET AFFICHAGE  *\n");
                printf("                                   **************************** \n");
                printf("                                   *  RECHERCHE PAR CATEGORIE *  \n") ;
                printf("                                   ****************************  \n ");
                printf("\n\n") ;
                affiche_par_categorie(c,lj) ;
                printf("\n\n\n\n") ;
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
        case 17:
                system("color FC");
                ShowWindow(hwnd,SW_HIDE);
                if(liste_vide(lj))
                {
                MessageBox(0,"La Liste Est Vide ?? Essayer De Le Remplir !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else {
                printf("                                   ****************************\n");
                printf("                                   *  RECHERCHE ET AFFICHAGE  *\n");
                printf("                                   **************************** \n");
                printf("                                   *JOUEUR DE TYPE JUNIOR <=30*  \n") ;
                printf("                                   ****************************  \n ");
                printf("\n\n") ;
                affiche_type_junior(lj)  ;
                printf("\n\n\n\n") ;
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;}
        case 18:
                system("color FC");
                ShowWindow(hwnd,SW_HIDE);
                if(liste_vide(lj))
                {
                MessageBox(0,"La Liste Est Vide ?? Essayer De Le Remplir !! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
                }
                else{
                printf("                                   ****************************\n");
                printf("                                   *  RECHERCHE ET AFFICHAGE  *\n");
                printf("                                   **************************** \n");
                printf("                                   *            TRI           *  \n") ;
                printf("                                   ****************************  \n ");
                printf("\n\n") ;
                gotoxy(1,7) ;
                printf("LISTE TRIEE : \n\n") ;
                tri(&lj) ;
                printf("\n\n\n") ;
                system("pause");
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break; }
        case 19:
                system("color FC");
                ShowWindow(hwnd,SW_HIDE);

                printf("                               ******************************\n");
                printf("                               *  ENRREGIST ET RECUPERE     *\n");
                printf("                               ****************************** \n");
                printf("                               *ENRREGISTREMENT DANS FICHIER*  \n") ;
                printf("                               ******************************  \n ");

                printf("\n\n") ;
                fj=fopen("joueur.txt","w") ;
                enrregistrement(lj,fj) ;
                MessageBox(0,"L'Enrregistrement A Eté Effectuer Avec Succée !!  ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
        case 20:
                system("color FC");
                ShowWindow(hwnd,SW_HIDE);
                fj=fopen("joueur.txt","r") ;
                if(liste_vide(lj))
                {
                creer_liste(&lj);
                recuperation(fj,&lj) ;
                }
                else
                recuperation(fj,&lj) ;

                MessageBox(0,"Recupération Reussi!! ","Attention",0) ;
                ShowWindow(hwnd,SW_NORMAL);
                system("cls");
                break;
        case 21 :
                 ShellExecute(NULL,"open","joueur.txt",NULL,NULL,SW_SHOWNORMAL) ;
                 break ;

        case 10:
                if (MessageBox(hwnd,"       Vous voulez quitter ?", "QUITTER", MB_YESNO | MB_ICONQUESTION ) == IDYES)
                {
                DestroyWindow(hwnd);
                system("cls");
                }
                break;
        case 22 :
                ShellExecute(NULL,"open","Projet C Gestion du club sportif.pdf",NULL,NULL,SW_SHOWNORMAL) ;
                break ;



        }
    case WM_CREATE :
        addmenus(hwnd);
//        CreateBtt(hwnd) ;
            /*****************ajouter fond **********************/
            hBmp=LoadImage(NULL,"sport1.bmp",IMAGE_BITMAP,1370,700,LR_LOADFROMFILE);

            break;

        case WM_PAINT :
            {



         PAINTSTRUCT ps;
            hdc = BeginPaint(hwnd, &ps);

            DrawState(hdc,NULL,NULL,(long)hBmp,0,0,0,0,0,DST_BITMAP);

            EndPaint(hwnd, &ps);}
        break;
        case WM_DESTROY:
            PostQuitMessage (0);        /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

void addmenus(HWND hwnd)
{
    hmenu=CreateMenu();
    HMENU htp=CreateMenu();
    HMENU htp1=CreateMenu();
    HMENU hex1=CreateMenu();
    HMENU hex2=CreateMenu();
    HMENU hex3=CreateMenu();
    HMENU htp2=CreateMenu();
    HMENU htp3=CreateMenu();
    HMENU htp4=CreateMenu();



    /*******************************************************/
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)htp,"Création Des Joueurs");


    AppendMenu(htp,MF_STRING,1,"Remplissage");

/***************************************************************/

     AppendMenu(hmenu,MF_POPUP,(UINT_PTR)htp1,"Mise A Jour");

      AppendMenu(htp1,MF_POPUP,(UINT_PTR)hex3,"Ajouter Un Nouvel Joueur");
      AppendMenu(hex3,MF_STRING,2,"Ajout En Tête");
      AppendMenu(hex3,MF_STRING,3,"Ajout En Queu");
      AppendMenu(hex3,MF_STRING,4,"Ajout Dans Une Position");
      AppendMenu(htp1,MF_POPUP,(UINT_PTR)hex2,"Supprimer Un Joueur");
      AppendMenu(hex2,MF_STRING,5,"Suppression En Tête ");
      AppendMenu(hex2,MF_STRING,6,"Suppression En Queu");
      AppendMenu(hex2,MF_STRING,7,"Suppression A Partir D'une Position");
      AppendMenu(hex2,MF_STRING,8,"Suppression D'un Joueur Donné Par Code");
      AppendMenu(hex2,MF_STRING,9,"Suppression Des Joueurs D'une Categorie");
      AppendMenu(htp1,MF_POPUP,(UINT_PTR)hex1,"Modifier Les Donnée D'un Joueur");
      AppendMenu(hex1,MF_STRING,11,"Catègorie ");
      AppendMenu(hex1,MF_STRING,12,"Téléphone ");
/***************************************************************/
     AppendMenu(hmenu,MF_POPUP,(UINT_PTR)htp2,"Recherche,Affichage et Tri");

      AppendMenu(htp2,MF_STRING,13,"Contenu De La Liste Des Joueurs");
      AppendMenu(htp2,MF_STRING,14,"Recherche Par Code Joueur");
      AppendMenu(htp2,MF_STRING,15,"Recherche Par Date De Naissance");
      AppendMenu(htp2,MF_STRING,16,"Recherche Par Categorie");
      AppendMenu(htp2,MF_STRING,17,"Recherche Jouers De Type 'Junior'<=30 Ans");
      AppendMenu(htp2,MF_STRING,18,"Tri");
/***************************************************************/
     AppendMenu(hmenu,MF_POPUP,(UINT_PTR)htp3,"Enregistrement Et Récuperation");
     AppendMenu(htp3,MF_STRING,19,"Enregistrement Du Donnée");
     AppendMenu(htp3,MF_STRING,20,"Récupération Du Donnée");
     AppendMenu(htp3,MF_STRING,21,"Contenu Du Fichier");
/******************************************************************/
    //AppendMenu(hmenu,MF_POPUP,(UINT_PTR)htp4,"Enoncée Du Projet");
    AppendMenu(hmenu,MF_STRING,22,"Enoncée Du Projet");

/***************************************************************/
    AppendMenu(hmenu,MF_STRING,10,"Quitter");
    SetMenu(hwnd,hmenu);
}

