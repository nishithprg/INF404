
#ifndef __TYPE_AST__
#define __TYPE_AST__ 

typedef enum {OPERATION, VALEUR, VARIABLE} TypeAst ;
typedef enum {N_PLUS, N_MUL, N_MOINS, N_DIV} TypeOperateur ;

typedef struct noeud { 
	TypeAst nature ;
	TypeOperateur operateur ;
	struct noeud *gauche, *droite ;
    int valeur;
	char var;
} NoeudAst ;

typedef NoeudAst *Ast ;

#endif  
