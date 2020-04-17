
#include <stdio.h>
#include "type_ast.h"
#include "ast_parcours.h"

void aff_operateur(TypeOperateur op){
	switch (op) {
		case N_PLUS:
			printf("+") ;
			break;
		case N_MOINS:
			printf("-") ;
			break;
		case N_MUL:
			printf("*") ;
			break;
	} 
}

void afficherA(Ast expr) {
	switch (expr->nature) {
               case OPERATION:
                        aff_operateur(expr->operateur) ;
                        printf("(");
                        afficher(expr->gauche);
                        printf(", ");
                        afficher(expr->droite);
                        printf(")");
			break ;
               case VALEUR:
                  	printf("%d", expr->valeur);
			break ;
	}
}

int evaluation(Ast expr) {
      // A COMPLETER !
      return -1 ;
}

