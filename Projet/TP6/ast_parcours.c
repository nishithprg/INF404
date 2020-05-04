
#include <stdio.h>
#include <stdlib.h>

#include "type_ast.h"
#include "ast_parcours.h"
#include "table_de_symbole.h"

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
		case N_DIV:
			printf("/");
			break;
	} 
}

void afficherA(Ast expr) {
	switch (expr->nature) {
        case OPERATION:
            aff_operateur(expr->operateur) ;
            printf("(");
            afficherA(expr->gauche);
            printf(", ");
            afficherA(expr->droite);
            printf(")");
			break;
               
		case VALEUR:
           	printf("%d", expr->valeur);
			break ;
	}
}

int evaluation(Ast expr) {
	switch(expr->nature){
		case OPERATION:
			switch (expr->operateur){
				case N_PLUS:
					return evaluation(expr->gauche) + evaluation(expr->droite);
				
				case N_MOINS:
					return evaluation(expr->gauche) - evaluation(expr->droite);
				
				case N_MUL:
					return evaluation(expr->gauche) * evaluation(expr->droite);
				
				case N_DIV:
					return evaluation(expr->gauche) / evaluation(expr->droite);
				
				default:
					printf("Erreur evaluation d'expression.\n");
					exit(1);
			}
			break;
		
		case VALEUR:
			return expr->valeur;

		default:
			exit(2);
	}
      return -1 ;
}


