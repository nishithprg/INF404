#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 

#include "type_ast.h"
#include "ast_construction.h"
#include "ast_parcours.h"
#include "analyse_lexicale.h"
#include "analyse_syntaxique.h"
#include "table_de_symbole.h"
#include "lecture_caracteres.h"


char nom[20];

void rec_eag(Ast *A1, Var_DB *tab_symb){
 		seq_terme(A1,tab_symb);
}
 	 
void seq_terme(Ast *A2,Var_DB *tab_symb){
	Ast A1;
 	terme(&A1,tab_symb);
 	suite_seq_terme(A1,A2,tab_symb);
}

void suite_seq_terme(Ast A1 , Ast *A2, Var_DB *tab_symb){
	Ast A3,A4;
	TypeOperateur op;
			
	if(op1(&op)){
		terme(&A3,tab_symb);
		A4 = creer_operation(op,A1,A3);
		suite_seq_terme(A4,A2,tab_symb);		
	} else {
		*A2=A1;		
	}
}
	
void terme(Ast *A1,Var_DB *tab_symb){
	seq_facteur(A1,tab_symb);
}
	
void seq_facteur(Ast *A2, Var_DB *tab_symb){
	Ast A1;
	facteur(&A1,tab_symb);
	suite_seq_facteur(A1,A2,tab_symb);
}
	
void suite_seq_facteur(Ast A1 , Ast *A2,Var_DB *tab_symb){
	Ast A3,A4;
	TypeOperateur op;
	int r = op2(&op);
	if(r==1){
		facteur(&A3,tab_symb);
		A4 = creer_operation(op,A1,A3);
		suite_seq_facteur(A4,A2,tab_symb);
	} else if (r==2){
		if(lexeme_courant().valeur==0){
			printf(" ERREUR : division par 0 impossible \n ");
			exit(3);
		}
		facteur(&A3,tab_symb);
		A4 = creer_operation(op,A1,A3);
		suite_seq_facteur(A4,A2,tab_symb);
	} else {
		*A2=A1;		
	}
}
	
void facteur(Ast *A1, Var_DB *tab_symb){
	switch(lexeme_courant().nature){
		case ENTIER:
			*A1 = creer_valeur(lexeme_courant().valeur);
			printf("Dans facteur ii, ENTIER : %d\n", lexeme_courant().valeur);
			avancer();
			break;
		// case PARO:
		// 	avancer();
		// 	rec_eag(A1, tab_symb);
		// 	if(lexeme_courant().nature == PARF){
		//   		avancer();
		//   	} else {
		//   		printf("ERREUR PARENTHESES");
		//   		exit(1);
		//   	}
		//   	break;
        case IDF: 
           	*A1 = creer_valeur(existe_val(*tab_symb, lexeme_courant().chaine));
			printf("Dans facteur ii, IDF : %s\n", lexeme_courant().chaine);
			avancer();
			break;
		
		default:
			printf("Erreur facteur ii\n");
			exit(0);
	}
}

void rec_affectation(Ast *A1, Var_DB *tab_symb){
	print_all_table(*tab_symb);
	strcpy(nom, lexeme_courant().chaine);
	printf("Var : %s\n", nom);
	afficher(lexeme_courant());
	printf("\n");
	avancer();
	afficher(lexeme_courant());
	printf("\n");
	switch(lexeme_courant().nature){
		case AFF:
			avancer();
			afficher(lexeme_courant());
			printf("\n");
			break;
		
		default:
			printf("Erreur affectation AFF\n");
			exit(0);
	};
	rec_eag(A1,tab_symb);
	afficherA(*A1);
	printf("\n");
	inserer_tab(tab_symb, nom, evaluation(*A1));
	afficher(lexeme_courant());
	printf("\n");
	switch(lexeme_courant().nature){
		case SEPINST:
			printf("Fin analyse synt d'expression.\n");
			avancer();
			break;

		default:
			printf("Erreur affectation SEPINST\n");
			exit(0);
	}
	print_all_table(*tab_symb);
};

void rec_seq_affectation(Ast *A1, Var_DB *tab_symb){
	Ast A2;
	switch(lexeme_courant().nature){
		case IDF:
			rec_affectation(A1, tab_symb);
			printf("**********************New Expression.********************\n");
			rec_seq_affectation(&A2, tab_symb);
			break;
		
		default:
			printf("Fin de sequence et fichier.\n");
	}
} 

int op1(TypeOperateur *Op){
	switch(lexeme_courant().nature){
		case PLUS:
		case MOINS:
			*Op = Operateur(lexeme_courant().nature);
			avancer(); 
			return 1;
		default:
			return 0;
	}
}
	
int op2(TypeOperateur *Op){ 
	switch(lexeme_courant().nature){
		case MUL: 
			*Op = Operateur(lexeme_courant().nature);
			avancer();
			return 1;
		case DIV: 
			*Op = Operateur(lexeme_courant().nature);
			avancer();
			return 2;
		default: 
			return 0;
	}
}
		 
TypeOperateur Operateur(Nature_Lexeme nature){
	switch(nature){
		case PLUS : return N_PLUS;
		case MOINS : return N_MOINS;
		case MUL: return N_MUL;
		case DIV : return N_DIV;
		default: 
			printf("Erreur operateur"); 
			exit(1) ; 
	}
}
	
/* ----------------------------------------------------------------------- */
void analyser(char* nomFichier){
	Ast A;
	Var_DB tab_symb;
	init_tab(&tab_symb);
	demarrer(nomFichier) ;
   	rec_seq_affectation(&A,&tab_symb);
}	 
 	 