#ifndef __AST_PARCOURS__
#define __AST_PARCOURS__

#include "table_de_symbole.h"

void afficherA(Ast expr) ;
// affiche l'arbre abstrait de l'expression arithmetique expr

int evaluation(Ast expr) ;
// calcule la valeur de l'expression arithmetique expr
// FONCTION A COMPLETER !

int eval_condition(Ast A_left, Ast A_right,TypeComparitors op);

void free_ast(NoeudAst *A);

#endif

