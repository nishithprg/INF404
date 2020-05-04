#ifndef __ANAL_SYNTX__
#define __ANAL_SYNTX__

#include "table_de_symbole.h"
#include "ast_construction.h"
#include "type_ast.h"


void rec_eag(Ast *A1, Var_DB *tab_symb);

void seq_terme(Ast *A2, Var_DB *tab_symb);

void suite_seq_terme(Ast A1 , Ast *A2, Var_DB *tab_symb);

void terme(Ast *A1, Var_DB *tab_symb);

void seq_facteur(Ast *A2, Var_DB *tab_symb);

void suite_seq_facteur(Ast A1 , Ast *A2, Var_DB *tab_symb);

void facteur(Ast *A1, Var_DB *tab_symb);

void rec_affectation(Ast *A1,Var_DB *tab_symb);

void rec_seq_affectation(Ast *A1, Var_DB *tab_symb);

int condition(Ast *A_cond, Var_DB *tab_symb);

void seq_inst(Ast *A1, Var_DB *tab_symb);

void inst(Ast *A1, Var_DB *tab_symb);

void seq_inst(Ast *A1, Var_DB *tab_symb);

void suite_seq_inst(Ast *A1, Var_DB *tab_symb);

void pgm(Ast *A1, Var_DB *tab_symb);

int op1(TypeOperateur *Op);

int op2(TypeOperateur *Op);

TypeComparitors recon_comparitor(Nature_Lexeme nature);

TypeOperateur Operateur(Nature_Lexeme nature);

void analyser(char* nomFichier);

#endif