
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<malloc.h>
#include"club.h"
#include<string.h>
#include<myconio.h>


void creer_liste(struct liste *lj)
{
    lj->premier = NULL ;
    lj->dernier = NULL ;
}

unsigned liste_vide(struct liste lj)
{
    return(lj.premier == NULL && lj.dernier == NULL) ;
}
int taille_liste(struct liste lj)
{
    struct cellule *p ;
    int n=0  ;
    p=lj.premier ;
    while(p)
    {
        n++ ;
        p=p->suivant ;
    }
    return n ;
}

void insere_tete(joueur j,struct liste *lj)
{
    struct cellule *p ;
    p=(struct cellule *)malloc(sizeof(struct cellule )) ;
    p->info = j ;
    p->suivant = lj->premier ;
    if(lj->premier == NULL)
       lj->dernier = p ;
    lj->premier = p ;
}


void insere_queu(joueur j , struct liste *lj)
{
    struct cellule *p ;
    p=(struct cellule *)malloc(sizeof(struct cellule )) ;
    p->info = j ;
    p->suivant = NULL ;
    if(lj->premier == NULL)
        lj->premier = p ;
    else
        lj->dernier->suivant = p ;
    lj->dernier = p ;

}

void insere_pos(joueur j , struct liste *lj, int pos )
{
    struct cellule *p , *q ;
    int n =1 ;
    p=lj->premier ;
    while(n!=pos)
    {
        n++ ;
        p=p->suivant ;
    }
    q=(struct cellule *)malloc(sizeof(struct cellule ));
    q->info = p->info ;
    q->suivant = p->suivant ;
    p->info = j ;
    p->suivant = q ;
}


void supprime_tete(struct liste *lj)
{
  struct cellule *p ;
  p=lj->premier ;
  lj->premier = p->suivant ;
  if(p->suivant == NULL)
        lj->dernier = NULL ;
}


void supprime_queu(struct liste *lj)
{
    struct cellule *p , *q ;
    p=lj->premier ;
    if(p->suivant ==  NULL)
    {
        lj->premier = NULL ;
        lj->dernier = NULL ;
    }
    else
    {
        q=p->suivant ;
        while(q->suivant)
        {
            q=q->suivant ;
            p=p->suivant ;
        }
        p->suivant = NULL ;
        lj -> dernier = p ;
    }
}

void supprime_pos(struct liste *lj,int pos)
{
    int n=1 ;
    struct cellule *p , *q ;
    p=lj->premier ;
    while(n!=pos-1)
    {
        n++ ;
        p=p->suivant ;
    }
    q=p->suivant ;
    p->suivant  =q->suivant ;
    free(q) ;
}

void affiche_liste(struct liste lj)
{
    struct cellule *p ;
    int i = 11 , j=11;
    p=lj.premier ;
    tableau(8,8,6,taille_liste(lj)+1,15,1) ;
    gotoxy(9,9) ;
    printf("CODE DU JOUEUR:");
    gotoxy(25,9) ;
    printf("NOM_PRENOM :") ;
    gotoxy(41,9);
    printf("DATE NAISSANCE:");
    gotoxy(57,9);
    printf("AGE DU JOUEUR :");
    gotoxy(73,9);
    printf("GROUPE :");
    gotoxy(89,9);
    printf("NUM TELEPHONE :");
    while(j<=9 + 2*taille_liste(lj))
    {
        gotoxy(9,j) ;
        printf("%d",p->info.code) ;
        gotoxy(25,j) ;
        printf("%s",p->info.nom_prenom) ;
        gotoxy(41,j) ;
        printf("%d/%d/%d",p->info.dn.j,p->info.dn.m,p->info.dn.a);
        gotoxy(57,j) ;
        printf("%d",p->info.type.age) ;
        gotoxy(73,j) ;
        printf("%s",p->info.type.groupe);
        gotoxy(89,j) ;
        printf("%d",p->info.telephone) ;
        p=p->suivant ;
        j=j+2 ;
    }

}

unsigned verife(int code_j, struct liste lj)
{
    struct cellule *p ;
    p=lj.premier ;
    while(p)
    {
        if(p->info.code == code_j)
            return 1 ;
        p=p->suivant ;
    }
    return 0 ;
}
int nb_jour(int m)
{
    switch(m)
    {
        case (1 || 3 || 5|| 7 || 8 || 10 || 12) :
             return 31 ;
             break ;
        case 2 :
            return 28 ;
            break;
        default :
            return 30 ;
            break;

    }
}


date saisie_date()
{
    date d ;
    int i ;
    tableau(4,11,1,1,60,2) ;
    tableau(65,11,1,1,11,2);
    gotoxy(5,12);
    printf("Donner La Date DE Naissance Sous Forme JJ/MM/AAAA:") ;
    gotoxy(66,12);
    scanf("%d/%d/%d",&d.j,&d.m,&d.a) ;
    do
    {
    if(d.m<=12 && d.m>0)
    {if(d.j>nb_jour(d.m) )
    {

    gotoxy(78,12) ;
    printf("ERREUR !!Le %d ieme Mois Contient %d Jours!!",d.m,nb_jour(d.m));
    gotoxy(66,12) ;
    for(i=0;i<=10;i++)
        printf(" ") ;
    gotoxy(66,12) ;
    scanf("%d/%d/%d",&d.j,&d.m,&d.a) ;
    }
    else if(d.j <= 0)
    {
     gotoxy(78,12) ;
    printf("ERREUR!! Le Jours Doit Etre > 0 !!") ;
    gotoxy(66,12) ;
    for(i=0;i<=10;i++)
        printf(" ") ;
    gotoxy(66,12) ;
    scanf("%d/%d/%d",&d.j,&d.m,&d.a) ;
    }
    }
    else {
            gotoxy(78,12) ;
    printf("La Mois Doit Etre Compris Entre 1 Et 12 !!");
    gotoxy(66,12) ;
    for(i=0;i<=10;i++)
        printf(" ") ;
    gotoxy(66,12) ;
    scanf("%d/%d/%d",&d.j,&d.m,&d.a) ;

    }
    if(d.a<=1999)
    {
        gotoxy(78,12) ;
        for(i=0;i<=50;i++)
            printf(" ") ;
        gotoxy(78,12) ;
    printf("L'annee Doit Etre Superieur  A 1999 !!") ;
    gotoxy(66,12) ;
    for(i=0;i<=10;i++)
        printf(" ") ;
    gotoxy(66,12) ;
    scanf("%d/%d/%d",&d.j,&d.m,&d.a) ;


    }
    gotoxy(78,12) ;
        for(i=0;i<=50;i++)
            printf(" ") ;
    } while(d.j>nb_jour(d.m) || d.m>12 || d.m<=0 || d.j<=0 || d.a<=1999) ;



    return d ;
}



categorie saisie_categorie()
{
    categorie c ;
    int i ;
    char a[10] ;
    tableau(4,11,1,2,60,2) ;
    tableau(65,11,1,2,10,2);
    gotoxy(7,12);
    printf("Donner l'age  : ") ;
    gotoxy(7,15) ;
    printf("Donner La Groupe  : ");
    gotoxy(66,12) ;
    scanf("%s",&a) ;
    int u,ok ;
    do
    {
        u=0;
        ok=0;
        while(a[u] != '\0')
        {
            if(isdigit(a[u]) == 0)
            {
                ok = 1 ;
                break ;
            }
            u++ ;
        }
        if(ok)
        {
            gotoxy(77,12) ;
            printf("Age Invalide !! Ressayer") ;
            gotoxy(66,12) ;
            for(i=0;i<=9;i++)
                printf(" ");
            gotoxy(66,12) ;
            scanf("%s",&a) ;
        }
        else if(atoi(a)==0)
    {gotoxy(77,12) ;
    printf("L'age doit etre different a 0 !!");
    gotoxy(66,12) ;
    for(i=0;i<=9;i++)
        printf(" ");
    gotoxy(66,12) ;
    scanf("%s",&a) ;

    }}while(atoi(a) == 0 || ok) ;
    gotoxy(77,12) ;
    for(i=0;i<=40;i++)
        printf(" ") ;
    c.age=atoi(a) ;
    gotoxy(66,15) ;
    scanf("%s",&c.groupe) ;
    do
    {
        ok=0;
    if(strcmp(c.groupe,"mineur") && strcmp(c.groupe,"junior") && strcmp(c.groupe,"cadet"))
    {
        gotoxy(77,15) ;
        printf("La Groupe Saisi Est Incorrecte !!");
        gotoxy(66,15) ;
        for(i=0;i<=9;i++)
        printf(" ") ;
        gotoxy(66,15) ;
        ok=1 ;
        scanf("%s",&c.groupe) ;

    }
    else
    {
        if(c.age > 18)
        {
        if(strcmp(c.groupe,"junior"))
        {
        gotoxy(77,15) ;
        printf("Groupe Ne Correspond Pas A L'Age !!");
        gotoxy(66,15) ;
        for(i=0;i<=9;i++)
        printf(" ") ;
        gotoxy(66,15) ;
        ok=1 ;
        scanf("%s",&c.groupe) ;

            }
        }
        else if (c.age <= 10)
        {
            if(strcmp(c.groupe,"mineur"))
            {
        gotoxy(77,15) ;
        printf("Groupe Ne Correspond Pas A L'Age !!");
        gotoxy(66,15) ;
        for(i=0;i<=9;i++)
        printf(" ") ;
        gotoxy(66,15) ;
        ok=1 ;
        scanf("%s",&c.groupe) ;
            }

        }
        else
        {
            if(strcmp(c.groupe,"cadet"))
            {
                gotoxy(77,15) ;
        printf("Groupe Ne Correspond Pas A L'Age !!");
        gotoxy(66,15) ;
        for(i=0;i<=9;i++)
        printf(" ") ;
        gotoxy(66,15) ;
        ok=1 ;
        scanf("%s",&c.groupe) ;
            }
        }
    }
    }
    while((strcmp(c.groupe,"mineur") && strcmp(c.groupe,"junior") && strcmp(c.groupe,"cadet"))|| ok) ;
    gotoxy(77,15) ;
    for(i=0;i<=40;i++)
        printf(" ") ;
    return c ;
}





unsigned verife_chaine(char ch[20])
{
    int i=0 ,x,ok=0   ;
    while(ch[i] != '\0')
    {
        x=ch[i]  ;
        if((x>=97 && x<=122) || (x>=65 && x<=90) || x==95)
        {
           i++ ;
        }
        else
        {
            ok=1 ;
            break ;
        }
    }
    return ok ;
}
unsigned verife_numero(int n)
{
    int m=n , nb=0 ;
    while(m)
    {
        nb++;
        m=m/10 ;
    }
    if (nb==8)
        return 1 ;
    else return 0 ;
}


void supprime_code(struct liste *lj,int code_j )
{
    struct cellule *p , *q;
    p=lj->premier ;
    if(p->info.code == code_j)
        supprime_tete(lj) ;
    else
    {
            q=p->suivant ;
            while(q)
            {
                if(q->info.code == code_j)
                {
                    if(q->suivant == NULL)
                        supprime_queu(lj) ;
                    else
                    {
                        p->suivant = q->suivant ;
                    }
                break ;
                }
                else
                {
                    q=q->suivant ;
                    p=p->suivant ;
                }
            }
            if(!q)
                printf("ce code n'existe pas ") ;
    }
}

void supprime_par_groupe(struct liste *lj,char groupe[10])
{
    struct cellule *f,*p ,*q ;
    f=lj->premier ;
    while(f)
    {
        p=lj->premier ;
        if( strcmp(p->info.type.groupe,groupe)==0)
            supprime_tete(lj) ;
        else
        {
            q=p->suivant ;
            while(q)
            {
             if(strcmp(q->info.type.groupe,groupe)==0)
             {
                 if(q->suivant == NULL)
                    supprime_queu(lj) ;
                 else
                    p->suivant = q->suivant ;
                 break;
             }
             else
             {
                 q=q->suivant ;
                 p=p->suivant ;
             }
            }
        }
        f=f->suivant ;
    }
}


void modifer_categorie(int code_j,struct liste *lj)
{
    categorie c  ;
    printf("\n") ;
    c=saisie_categorie() ;
    struct cellule *p ;
    p=lj->premier ;
    while(p)
    {
        if(p->info.code == code_j)
        {
            p->info.type = c ;
        }
        p=p->suivant ;
    }
}

void modifer_telephone(int code_j,int num ,struct liste *lj)
{


    struct cellule *p ;
    p=lj->premier ;
    while(p)
    {
        if(p->info.code == code_j)
        {
            p->info.telephone = num ;
        }
        p=p->suivant ;
    }
}

void affiche_cellule(struct cellule *p)
{

    printf("%d | %s | %d/%d/%d | %d | %s | %d|\n",p->info.code,p->info.nom_prenom,p->info.dn.j,p->info.dn.m,p->info.dn.a,p->info.type.age,p->info.type.groupe,p->info.telephone) ;

}
void affiche_par_code(int code_j, struct liste lj)
{
    struct cellule *p ;
    p=lj.premier ;
    tableau(8,8,6,2,15,1) ;
    gotoxy(9,9) ;
    printf("CODE DU JOUEUR:");
    gotoxy(25,9) ;
    printf("NOM_PRENOM :") ;
    gotoxy(41,9);
    printf("DATE NAISSANCE:");
    gotoxy(57,9);
    printf("AGE DU JOUEUR :");
    gotoxy(73,9);
    printf("GROUPE :");
    gotoxy(89,9);
    printf("NUM TELEPHONE :");
    while(p)
    {
        if(p->info.code == code_j)
            {
        gotoxy(9,11) ;
        printf("%d",p->info.code) ;
        gotoxy(25,11) ;
        printf("%s",p->info.nom_prenom) ;
        gotoxy(41,11) ;
        printf("%d/%d/%d",p->info.dn.j,p->info.dn.m,p->info.dn.a);
        gotoxy(57,11) ;
        printf("%d",p->info.type.age) ;
        gotoxy(73,11) ;
        printf("%s",p->info.type.groupe);
        gotoxy(89,11) ;
        printf("%d",p->info.telephone) ;

            }
        p=p->suivant ;
    }
}


void affiche_par_nom(char nom[20], struct liste lj)
{
    struct cellule *p ;
    p=lj.premier ;
    while(p)
    {
        if(strcmp(p->info.nom_prenom,nom)==0)
            affiche_cellule(p) ;
        p=p->suivant ;
    }
}


void affiche_par_date(date d , struct liste lj)
{
    struct cellule *p ;
    int ok=0 ;
    struct liste l ;
    creer_liste(&l) ;
    p=lj.premier ;
    while(p)
    {
        if(p->info.dn.a==d.a && p->info.dn.j==d.j && p->info.dn.m==d.m)
            {
                insere_queu(p->info,&l);
                ok=1 ;
            }
        p=p->suivant ;
    }

    if(!ok)
        printf("IL N'EXISTE PAS DES JOUEURS NEE A CETTE DATE !!\n\n") ;
    else
        affiche_liste(l) ;
}

void affiche_par_categorie(categorie c,struct liste lj)
{
    struct cellule *p ;
    int ok=0 ;
    struct liste l ;
    creer_liste(&l) ;
    p=lj.premier ;
    while(p)
    {
        if(p->info.type.age == c.age && strcmp(p->info.type.groupe,c.groupe)==0)
            {
                insere_queu(p->info,&l) ;
                ok=1;
            }
        p=p->suivant ;
    }
    if(!ok)
        printf("IL N'EXISTE AUCUN JOUEUR DU CETTE CATEGORIE !!\n\n");
    else
        affiche_liste(l) ;

}

void affiche_type_junior(struct liste lj)
{
    struct cellule *p ,*q;
    joueur aux ;
    struct liste l ;
    int ok=0 ;
    p=lj.premier ;
    creer_liste(&l) ;
    while(p)
    {
        if(strcmp(p->info.type.groupe,"junior")==0 && p->info.type.age<=30)
            {
                insere_queu(p->info,&l);
                ok=1 ;
            }
        p=p->suivant ;
    }
    p=l.premier ;
    while(p)
    {
        q=p->suivant ;
        while(q)
        {
            if(p->info.type.age < q->info.type.age)
            {
                aux=q->info ;
                q->info=p->info ;
                p->info=aux ;
            }
            q=q->suivant ;
        }
        p=p->suivant ;
    }

    if(!ok)
        printf("IL N'EXISTE ANCUN JOUEUR DE TYPE JUNIOR ET D'AGE INFERIEUR A 30 !!\n\n") ;
    else
        affiche_liste(l) ;
}


void tri(struct liste *lj)
{
    struct liste l ;
    creer_liste(&l) ;
    struct cellule *p ;
    p=lj->premier ;
    while(p)
    {
        if(strcmp(p->info.type.groupe,"mineur")==0)
            insere_queu(p->info,&l) ;
        p=p->suivant ;
    }
    p=lj->premier ;
    while(p)
    {
        if(strcmp(p->info.type.groupe,"cadet")==0)
            insere_queu(p->info,&l) ;
        p=p->suivant ;
    }
    p=lj->premier ;
    while(p)
    {
        if(strcmp(p->info.type.groupe,"junior")==0)
            insere_queu(p->info,&l) ;
        p=p->suivant ;
    }
    creer_liste(lj) ;
    p=l.premier ;
    while(p)
    {
        insere_queu(p->info,lj);
        p=p->suivant ;
    }
    affiche_liste(*lj) ;

}
void enrregistrement(struct liste lj,FILE *fj)
{

    struct cellule *p ;
    p=lj.premier ;
    while(p)
    {
        fprintf(fj," %d ",p->info.code) ;
        fprintf(fj,"%s ",p->info.nom_prenom);
        fprintf(fj,"%d ",p->info.dn.j) ;
        fprintf(fj,"%d ",p->info.dn.m) ;
        fprintf(fj,"%d ",p->info.dn.a) ;
        fprintf(fj,"%d ",p->info.type.age) ;
        fprintf(fj,"%s ",p->info.type.groupe) ;
        fprintf(fj,"%d ",p->info.telephone) ;
        p=p->suivant ;
        fprintf(fj,"\n") ;
    }
    fclose(fj)  ;
}
void recuperation(FILE *fj,struct liste *lj)
{
    joueur j ;

    while(!feof(fj))
    {
        fscanf(fj," %d ",&j.code) ;
        fscanf(fj,"%s ",&j.nom_prenom);
        fscanf(fj,"%d ",&j.dn.j) ;
        fscanf(fj,"%d ",&j.dn.m) ;
        fscanf(fj,"%d ",&j.dn.a) ;
        fscanf(fj,"%d ",&j.type.age) ;
        fscanf(fj,"%s ",&j.type.groupe) ;
        fscanf(fj,"%d ",&j.telephone) ;
        insere_queu(j,lj) ;
    }
}


unsigned verife_groupe(char c[10], struct liste lj)
{
    struct cellule *p = lj.premier ;
    while(p)
    {
        if( strcmp(c,p->info.type.groupe)==0)
        {
            return 1 ;
            break ;
        }
        p=p->suivant ;
    }
    return 0;
}

/*
unsigned verife_categori(categorie c , struct liste lj)
{
    struct cellule *p = lj.premier ;
    while(p)
    {
        if(c.age == p->info.type.age && strcmp(c.groupe,p->info.type.groupe)==0)
        {
            return 1 ;
            break ;
        }
        p=p->suivant ;
    }
    return 0;
}
*/
joueur saisie(struct liste lj)
{

    int   i ,ok;
    joueur j ;
char cd[20] ;

    tableau(4,7,1,1,67,2) ;
    tableau(4,9,2,6,33,2) ;
    gotoxy(14,8) ;
    printf("Remplissage Du Tableau : ") ;
    gotoxy(5,11) ;
    printf("Code  Du Joueur: ") ;
    gotoxy(5,14) ;
    printf("Nom_Prenon De Joueur : ");
    gotoxy(5,17) ;
    printf("Date_Naissance (JJ/MM/AAAA) : ");
    gotoxy(5,20);
    printf("La Groupe : ");
    gotoxy(5,23);
    printf("L'age Du Joueur :");
    gotoxy(5,26) ;
    printf("Le Numero De Telepone : ");
    gotoxy(40,11) ;
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
        gotoxy(75,11);
        printf("Code Invalide !!");
        gotoxy(40,11) ;
        for(i=0;i<=30;i++)
            printf(" ");
        gotoxy(40,11) ;
        scanf("%s",&cd) ;
    }

    else if(verife(atoi(cd),lj))
    {
        gotoxy(75,11);
        printf("Ce Code Existe Deja !! ");
        gotoxy(40,11) ;
        for(i=0;i<=30;i++)
            printf(" ");
        gotoxy(40,11) ;
        scanf("%s",&cd) ;
    }


    }while(verife(atoi(cd),lj) || ok) ;
    gotoxy(75,11);
    for(i=0;i<=45;i++)
            printf(" ");
    gotoxy(40,14) ;
    j.code=atoi(cd) ;
    scanf("%s",&j.nom_prenom) ;
    do
    {
        if(verife_chaine(j.nom_prenom))
        {
            gotoxy(75,14) ;
            printf("Chaine Invalide !! ");
            gotoxy(40,14);
            for(i=0;i<=30;i++)
            {printf(" ") ;}
            gotoxy(40,14) ;
            scanf("%s",&j.nom_prenom) ;
        }
    }while(verife_chaine(j.nom_prenom)) ;

    gotoxy(75,14);
    for(i=0;i<=45;i++)
            printf(" ");

    gotoxy(40,17) ;
    scanf("%d/%d/%d",&j.dn.j,&j.dn.m,&j.dn.a) ;
     do
    {
    if(j.dn.m<=12 && j.dn.m>0)
    {if(j.dn.j>nb_jour(j.dn.m) )
    {
        gotoxy(75,17);
    printf("ERREUR !!Le %d ieme Mois Contient %d Jours !! ",j.dn.m,nb_jour(j.dn.m));
    gotoxy(40,17) ;
    for(i=0;i<=30;i++)
        printf(" ") ;
    gotoxy(40,17) ;
    scanf("%d/%d/%d",&j.dn.j,&j.dn.m,&j.dn.a) ;
    }
    else if(j.dn.j <= 0)
    {
    gotoxy(75,17);
    printf("ERREUR!!Le Jours Doit Etre Superieur Strictement a 0 !!") ;
    gotoxy(40,17) ;
    for(i=0;i<=30;i++)
        printf(" ") ;
    gotoxy(40,17) ;
    scanf("%d/%d/%d",&j.dn.j,&j.dn.m,&j.dn.a) ;
    }
    }
    else {
    gotoxy(75,17) ;
    printf("La Mois Doit Etre Compris Entre 1 Et 12 !!");
    gotoxy(40,17) ;
    for(i=0;i<=30;i++)
        printf(" ") ;
    gotoxy(40,17) ;
    scanf("%d/%d/%d",&j.dn.j,&j.dn.m,&j.dn.a) ;
    }
    if(j.dn.a<=1999)
    {
    gotoxy(75,17);
    for(i=0;i<=45;i++)
        printf(" ");
    gotoxy(75,17) ;
    printf("L'annee Doit Etre < 1999 !!") ;
    gotoxy(40,17) ;
    for(i=0;i<=30;i++)
        printf(" ") ;
    gotoxy(40,17) ;
    scanf("%d/%d/%d",&j.dn.j,&j.dn.m,&j.dn.a) ;
    }

    gotoxy(75,17);
    for(i=0;i<=45;i++)
        printf(" ");
    } while(j.dn.j>nb_jour(j.dn.m) || j.dn.m>12 || j.dn.m<=0 || j.dn.j<=0 || j.dn.a<=1999) ;

    gotoxy(75,17);
    for(i=0;i<=45;i++)
            printf(" ");

    gotoxy(40,20) ;
    scanf("%s",&j.type.groupe) ;
    do
    {
    if(strcmp(j.type.groupe,"mineur") && strcmp(j.type.groupe,"junior") && strcmp(j.type.groupe,"cadet"))
    {
    gotoxy(75,20) ;
    printf("ERREUR!! la groupe saisie est incorrecte !!");
    gotoxy(40,20);
    for(i=0;i<=30;i++)
        printf(" ") ;
    gotoxy(40,20);
    scanf("%s",&j.type.groupe) ;
    }
    }
    while(strcmp(j.type.groupe,"mineur") && strcmp(j.type.groupe,"junior") && strcmp(j.type.groupe,"cadet")) ;

    gotoxy(75,20);
    for(i=0;i<=45;i++)
            printf(" ");

    gotoxy(40,23) ;


    char a[10] ;
    scanf("%s",&a);
    do
    {
        ok=0 ;
        i=0;
        while(a[i] != '\0')
        {
            if(isdigit(a[i]) == 0)
            {
              ok=1 ;
              break ;
            }
            i++ ;
        }

        if(ok)
        {
            gotoxy(75,23);
            printf("Age Invalide !! Ressayer");
            gotoxy(40,23);
            for(i=0;i<=30;i++)
                printf(" ");
            gotoxy(40,23);
            scanf("%s",&a);
        }
        else if(atoi(a)==0)
        {
            gotoxy(75,23);
            printf("ERREUR !! L'age Doit different de 0 !!");
            gotoxy(40,23);
            for(i=0;i<=30;i++)
                printf(" ") ;
            gotoxy(40,23);
            ok=1 ;
            scanf("%s",&a) ;
        }
        else
        {
            if(strcmp(j.type.groupe,"mineur")==0 )
            {
                if(atoi(a)>10)
                {
                gotoxy(75,23);
                printf("Age Ne Correspond Pas A La Groupe !!") ;
                gotoxy(40,23);
                for(i=0;i<=30;i++)
                printf(" ") ;
                gotoxy(40,23);
                ok=1 ;
                scanf("%s",&a) ;
                }
            }
            else if(strcmp(j.type.groupe,"cadet")==0 )
            {
                if(atoi(a)<=10 || atoi(a) > 18)
                {
                gotoxy(75,23);
                printf("Age Ne Correspond Pas A La Groupe !!") ;
                gotoxy(40,23);
                for(i=0;i<=30;i++)
                printf(" ") ;
                gotoxy(40,23);
                ok=1 ;
                scanf("%s",&a) ;
                }
            }
            else
            {
                if(atoi(a) <= 18)
                {
                gotoxy(75,23);
                printf("Age Ne Correspond Pas A La Groupe !!") ;
                gotoxy(40,23);
                for(i=0;i<=30;i++)
                printf(" ") ;
                gotoxy(40,23);
                ok =1 ;
                scanf("%s",&a) ;

                }
            }
        }
    }while(atoi(a)== 0 || ok);
    j.type.age=atoi(a) ;
    gotoxy(75,23);
    for(i=0;i<=45;i++)
            printf(" ");

    gotoxy(40,26) ;


    char tel[10] ;
    scanf("%s",&tel) ;
    do{
    i=0;
    ok=0;
    while(tel[i] != '\0')
    {
        if(isdigit(tel[i]) == 0)
        {
            ok = 1 ;
            break ;
        }
        i++ ;
    }
    if(ok)
    {
        gotoxy(75,26);
        printf("ERREUR !! Le Numero Doit Etre De 8 Chiffre !!");
        gotoxy(40,26) ;
        for(i=0;i<=30;i++)
            printf(" ") ;
        gotoxy(40,26) ;
        scanf("%s",&tel) ;
    }
    else if(!verife_numero(atoi(tel)))
    {
        gotoxy(75,26);
        printf("ERREUR !! Le Numero Doit Etre De 8 Chiffre !!");
        gotoxy(40,26) ;
        for(i=0;i<=30;i++)
            printf(" ") ;
        gotoxy(40,26) ;
        scanf("%s",&tel) ;
    }
    }while(!verife_numero(atoi(tel)) || ok) ;

    gotoxy(75,26);
    for(i=0;i<=45;i++)
            printf(" ");
    j.telephone=atoi(tel) ;

    return j ;
}




void remplir_liste(struct liste *lj)
{

    int pos ,r , i,n=0 ,ok=0;
    joueur j ;
    char cd[20] ;
    do{n++ ;
    tableau(8,5,1,1,60,2) ;
    gotoxy(30,6);
    printf("AJOUT DE %dieme JOUEUR",n);
    tableau(4,7,1,1,67,2) ;
    tableau(4,9,2,6,33,2) ;
    gotoxy(14,8) ;
    printf("Remplissage Du Tableau : ") ;
    gotoxy(5,11) ;
    printf("Le Code Du Joueur : ") ;
    gotoxy(5,14) ;
    printf("Nom_Prenon De Joueur : ");
    gotoxy(5,17) ;
    printf("Date_Naissance (JJ/MM/AAAA) : ");
    gotoxy(5,20);
    printf("La Groupe : ");
    gotoxy(5,23);
    printf("L'age Du Joueur :");
    gotoxy(5,26) ;
    printf("Le Numero De Telepone : ");
    gotoxy(40,11) ;
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
        gotoxy(75,11);
        printf("Code Invalide !!");
        gotoxy(40,11) ;
        for(i=0;i<=30;i++)
            printf(" ");
        gotoxy(40,11) ;
        scanf("%s",&cd) ;
    }

    else if(verife(atoi(cd),*lj))
    {
        gotoxy(75,11);
        printf("Ce Code Existe Deja !! ");
        gotoxy(40,11) ;
        for(i=0;i<=30;i++)
            printf(" ");
        gotoxy(40,11) ;
        scanf("%s",&cd) ;
    }


    }while(verife(atoi(cd),*lj) || ok) ;
    gotoxy(75,11);
    for(i=0;i<=45;i++)
            printf(" ");
    gotoxy(40,14) ;
    j.code=atoi(cd) ;
    scanf("%s",&j.nom_prenom) ;
    do
    {
        if(verife_chaine(j.nom_prenom))
        {
            gotoxy(75,14) ;
            printf("Chaine Invalide !! ");
            gotoxy(40,14);
            for(i=0;i<=30;i++)
            {printf(" ") ;}
            gotoxy(40,14) ;
            scanf("%s",&j.nom_prenom) ;
        }
    }while(verife_chaine(j.nom_prenom)) ;

    gotoxy(75,14);
    for(i=0;i<=45;i++)
            printf(" ");

    gotoxy(40,17) ;
    scanf("%d/%d/%d",&j.dn.j,&j.dn.m,&j.dn.a) ;
     do
    {
    if(j.dn.m<=12 && j.dn.m>0)
    {if(j.dn.j>nb_jour(j.dn.m) )
    {
        gotoxy(75,17);
    printf("ERREUR !!Le %d ieme Mois Contient %d Jours !! ",j.dn.m,nb_jour(j.dn.m));
    gotoxy(40,17) ;
    for(i=0;i<=30;i++)
        printf(" ") ;
    gotoxy(40,17) ;
    scanf("%d/%d/%d",&j.dn.j,&j.dn.m,&j.dn.a) ;
    }
    else if(j.dn.j <= 0)
    {
    gotoxy(75,17);
    printf("ERREUR!!Le Jours Doit Etre Superieur Strictement a 0 !!") ;
    gotoxy(40,17) ;
    for(i=0;i<=30;i++)
        printf(" ") ;
    gotoxy(40,17) ;
    scanf("%d/%d/%d",&j.dn.j,&j.dn.m,&j.dn.a) ;
    }
    }
    else {
    gotoxy(75,17) ;
    printf("La Mois Doit Etre Compris Entre 1 Et 12 !!");
    gotoxy(40,17) ;
    for(i=0;i<=30;i++)
        printf(" ") ;
    gotoxy(40,17) ;
    scanf("%d/%d/%d",&j.dn.j,&j.dn.m,&j.dn.a) ;
    }
    if(j.dn.a<=1999)
    {
    gotoxy(75,17);
    for(i=0;i<=45;i++)
        printf(" ");
    gotoxy(75,17) ;
    printf("L'annee Doit Etre < 1999 !!") ;
    gotoxy(40,17) ;
    for(i=0;i<=30;i++)
        printf(" ") ;
    gotoxy(40,17) ;
    scanf("%d/%d/%d",&j.dn.j,&j.dn.m,&j.dn.a) ;
    }

    gotoxy(75,17);
    for(i=0;i<=45;i++)
        printf(" ");
    } while(j.dn.j>nb_jour(j.dn.m) || j.dn.m>12 || j.dn.m<=0 || j.dn.j<=0 || j.dn.a<=1999) ;

    gotoxy(75,17);
    for(i=0;i<=45;i++)
            printf(" ");

    gotoxy(40,20) ;
    scanf("%s",&j.type.groupe) ;
    do
    {
    if(strcmp(j.type.groupe,"mineur") && strcmp(j.type.groupe,"junior") && strcmp(j.type.groupe,"cadet"))
    {
    gotoxy(75,20) ;
    printf("ERREUR!! la groupe saisie est incorrecte !!");
    gotoxy(40,20);
    for(i=0;i<=30;i++)
        printf(" ") ;
    gotoxy(40,20);
    scanf("%s",&j.type.groupe) ;
    }
    }
    while(strcmp(j.type.groupe,"mineur") && strcmp(j.type.groupe,"junior") && strcmp(j.type.groupe,"cadet")) ;

    gotoxy(75,20);
    for(i=0;i<=45;i++)
            printf(" ");

    gotoxy(40,23) ;
    char a[10] ;
    scanf("%s",&a);
    do
    {
        ok=0 ;
        i=0;
        while(a[i] != '\0')
        {
            if(isdigit(a[i]) == 0)
            {
              ok=1 ;
              break ;
            }
            i++ ;
        }

        if(ok)
        {
            gotoxy(75,23);
            printf("Age Invalide !! Ressayer");
            gotoxy(40,23);
            for(i=0;i<=30;i++)
                printf(" ");
            gotoxy(40,23);
            scanf("%s",&a);
        }
        else if(atoi(a)==0)
        {
            gotoxy(75,23);
            printf("ERREUR !! L'age Doit different de 0 !!");
            gotoxy(40,23);
            for(i=0;i<=30;i++)
                printf(" ") ;
            gotoxy(40,23);
            scanf("%s",&a) ;
        }
        else
        {
            if(strcmp(j.type.groupe,"mineur")==0 )
            {
                if(atoi(a)>10)
                {
                gotoxy(75,23);
                printf("Age Ne Correspond Pas A La Groupe !!") ;
                gotoxy(40,23);
                for(i=0;i<=30;i++)
                printf(" ") ;
                gotoxy(40,23);
                ok=1 ;
                scanf("%s",&a) ;
                }
            }
            else if(strcmp(j.type.groupe,"cadet")==0 )
            {
                if(atoi(a)<=10 || atoi(a) > 18)
                {
                gotoxy(75,23);
                printf("Age Ne Correspond Pas A La Groupe !!") ;
                gotoxy(40,23);
                for(i=0;i<=30;i++)
                printf(" ") ;
                gotoxy(40,23);
                ok=1 ;
                scanf("%s",&a) ;
                }
            }
            else
            {
                if(atoi(a) <= 18)
                {
                gotoxy(75,23);
                printf("Age Ne Correspond Pas A La Groupe !!") ;
                gotoxy(40,23);
                for(i=0;i<=30;i++)
                printf(" ") ;
                gotoxy(40,23);
                ok =1 ;
                scanf("%s",&a) ;

                }
            }
        }
    }while(atoi(a) == 0 || ok);
    j.type.age=atoi(a) ;
    gotoxy(75,23);
    for(i=0;i<=45;i++)
            printf(" ");

    gotoxy(40,26) ;
    char tel[10] ;
    scanf("%s",&tel) ;
    do{
    i=0;
    ok=0;
    while(tel[i] != '\0')
    {
        if(isdigit(tel[i]) == 0)
        {
            ok = 1 ;
            break ;
        }
        i++ ;
    }
    if(ok)
    {
        gotoxy(75,26);
        printf("ERREUR !! Le Numero Doit Etre De 8 Chiffre !!");
        gotoxy(40,26) ;
        for(i=0;i<=30;i++)
            printf(" ") ;
        gotoxy(40,26) ;
        scanf("%s",&tel) ;
    }
    else if(!verife_numero(atoi(tel)))
    {
        gotoxy(75,26);
        printf("ERREUR !! Le Numero Doit Etre De 8 Chiffre !!");
        gotoxy(40,26) ;
        for(i=0;i<=30;i++)
            printf(" ") ;
        gotoxy(40,26) ;
        scanf("%s",&tel) ;
    }
    }while(!verife_numero(atoi(tel)) || ok) ;

    gotoxy(75,26);
    for(i=0;i<=45;i++)
            printf(" ");
    j.telephone=atoi(tel) ;
    do
    {
        gotoxy(100,14);
        for(i=0;i<=20;i++)
            printf(" ");
        gotoxy(75,11) ;
        printf("Dans Quelle Position Voulez Vous ") ;
        gotoxy(75,14);
        printf("Ajouter (1 <= position <= %d) :====> ",taille_liste(*lj)+1) ;
        scanf("%d",&pos) ;
        fflush(stdin) ;
        if(pos == 1)
            insere_tete(j,lj) ;
        else if(pos == taille_liste(*lj) +1)
            insere_queu(j,lj) ;
        else if(pos >=1 && pos<=taille_liste(*lj) +1)
            insere_pos(j,lj,pos) ;
        }while((pos <1) || (pos > taille_liste(*lj) +1)) ;
    do
    {
        gotoxy(85,23);
        for(i=0;i<=20;i++)
            printf(" ");
        gotoxy(75,20) ;
        printf("Voulez Vous Ajouter Un Autre ");
        gotoxy(75,23);
        printf("Joueur 1/Oui 0/Nom : ");
        scanf("%d",&r);
        }
        while(r!=0 && r!=1) ;
    system("cls") ;
    printf("\n") ;
    }while(r)  ;
}


