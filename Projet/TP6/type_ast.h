
#ifndef __TYPE_AST__
#define __TYPE_AST__ 

typedef enum {OPERATION, VALEUR} TypeAst ;
typedef enum {N_PLUS, N_MUL, N_MOINS, N_DIV} TypeOperateur;
typedef enum {N_EQL, N_DIFF, N_LE, N_GE, N_LT, N_GT} TypeComparitors;

typedef struct noeud { 
	TypeAst nature ;
	TypeOperateur operateur ;
	struct noeud *gauche, *droite ;
    int valeur;
} NoeudAst ;

typedef NoeudAst *Ast ;

#endif  
