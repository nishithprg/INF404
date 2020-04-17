#include "type_ast.h"
#include "analyse_lexicale.h"

void rec_eag(Ast *A1);

void seq_terme(Ast *A2);

void suite_seq_terme(Ast A1 , Ast *A2);

void terme(Ast *A1);

void seq_facteur(Ast *A2);

void suite_seq_facteur(Ast A1 , Ast *A2);

void facteur(Ast *A1);

void affectation(Ast *A1);

int op1(TypeOperateur *Op);

int op2(TypeOperateur *Op);

TypeOperateur Operateur(Nature_Lexeme nature);