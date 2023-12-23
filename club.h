
typedef struct
{
    int j ;
    int m ;
    int a ;
} date ;


typedef struct
{
    int age ;
    char groupe[10] ;
}categorie ;

typedef struct
{
    int code ;
    char nom_prenom[30] ;
    date dn ;
    categorie type ;
    int telephone ;
} joueur ;

struct cellule
{
    joueur info ;
    struct cellule *suivant ;
};


struct liste
{
    struct cellule *premier ;
    struct cellule *dernier ;
};




void creer_liste(struct liste *);
unsigned liste_vide(struct liste );
int taille_liste(struct liste );
void insere_tete(joueur ,struct liste *);
void insere_queu(joueur , struct liste *) ;
void insere_pos(joueur,struct liste *,int);
void supprime_tete(struct liste *) ;
void supprime_queu(struct liste *) ;
void supprime_pos(struct liste *,int);
void affiche_liste(struct liste);
unsigned verife(int, struct liste);
date saisie_date() ;
categorie saisie_categorie() ;
joueur saisie(struct liste ) ;
void remplir_liste(struct liste *);
void supprime_code(struct liste *,int ) ;
void supprime_par_groupe(struct liste *,char [] );
void modifer_categorie(int,struct liste *);
void modifer_telephone(int,int ,struct liste *);
void affiche_cellule(struct cellule *) ;
void affiche_par_code(int, struct liste );
void affiche_par_nom(char [], struct liste);
void affiche_par_date(date, struct liste );
void affiche_par_categorie(categorie,struct liste ) ;
void affiche_type_junior(struct liste );
void tri(struct liste *) ;
int nb_jour(int );
unsigned verife_numero(int);
void enrregistrement(struct liste,FILE *) ;
void recuperation(FILE *,struct liste *);
unsigned verife_groupe(char [], struct liste ) ;
unsigned verife_chaine(char [20]) ;

