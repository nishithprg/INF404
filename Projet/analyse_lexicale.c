/* ------------------------------------------------------------------------
-- paquetage analyse_lexicale
--
-- analyse lexicale d'une expression arithmetique
--
-- J-P. Peyrin, G. Serasset (version initiale) : janvier 1999
-- P.Habraken - 18/01/2010
--
-- 10 juin 2006 - PH :
-- remplacement record a champs variants par record "plat"
-- remplacement traitement iteratif par automate
--
-- Aout 2016 - LM : version C
------------------------------------------------------------------------ */

#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 

#include "lecture_caracteres.h"
#include "analyse_lexicale.h"

   /* --------------------------------------------------------------------- */


/* Les variables et fonctions locales au module */
   Lexeme lexeme_en_cours ;	/* le lexeme courant */

   void ajouter_caractere (char *s, char c);
   Nature_Caractere nature_caractere (char c);
   int est_separateur(char c);
   int est_chiffre(char c);
   int est_symbole(char c);
   int est_lettre(char c);
   int est_sep(char c);
   int est_aff(char c);
   void reconnaitre_lexeme();
   void analyser(char *fichier);
   void analyser_fin(char * fichier);
   void analyser_lexem();
   unsigned int col_prev = 1;

   /* --------------------------------------------------------------------- */

   void demarrer(char *nom_fichier) {
      demarrer_car(nom_fichier);
      avancer();
   }

   /* --------------------------------------------------------------------- */

   void avancer() {
      reconnaitre_lexeme();
   } 
/* --------------------------------------------------------------------- */

   void avancer_anlys() {
      analyser_lexem();
   } 
   /* --------------------------------------------------------------------- */

   Lexeme lexeme_courant() {
      return lexeme_en_cours;
   } 

   /* --------------------------------------------------------------------- */

   int fin_de_sequence() {
      return lexeme_en_cours.nature == FIN_SEQUENCE;
   }

   /* --------------------------------------------------------------------- */

   void arreter() {
      arreter_car() ;
   }

   /* --------------------------------------------------------------------- */


   // reconnaissance d'un nouveau lexeme
   // etat initial : le caractere courant est soit separateur 
   //                soit le 1er caractere d'un lexeme
   // etat final : 
   //       - un nouveau lexeme est reconnu dans lexeme_en_cours
   //       - le caractere courant est soit la fin de fichier, 
   //		soit un separateur,  soit le 1er caractere d'un lexeme

   void reconnaitre_lexeme() {
      typedef enum {E_INIT, E_ENTIER, E_FIN} Etat_Automate ;
      Etat_Automate etat=E_INIT;

     // on commence par lire et ignorer les separateurs
     while (est_separateur(caractere_courant())) {
        	avancer_car() ;
     } ;

     lexeme_en_cours.chaine[0] = '\0' ;

     // on utilise ensuite un automate pour reconnaitre et construire le prochain lexeme

    while (etat != E_FIN) {

	    switch (etat) {

		  case E_INIT: // etat initial
          
			switch(nature_caractere(caractere_courant())) {

				case C_FIN_SEQUENCE: 
             	lexeme_en_cours.nature = FIN_SEQUENCE;
               etat = E_FIN;
					break ;

				case CHIFFRE: 
		     		lexeme_en_cours.nature = ENTIER;
               lexeme_en_cours.ligne = numero_ligne();
               lexeme_en_cours.colonne = numero_colonne();
		     		ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
               lexeme_en_cours.valeur = caractere_courant() - '0';
               etat = E_ENTIER;
		   		avancer_car() ;
					break ;

				case SYMBOLE: 
		       		lexeme_en_cours.ligne = numero_ligne();
               	lexeme_en_cours.colonne = numero_colonne();
		       		ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
               	switch (caractere_courant()) {
               	   case '+':
               	      lexeme_en_cours.nature = PLUS;
               		   etat = E_FIN;
			   		      break;
               	  case '-':
               	   	lexeme_en_cours.nature = MOINS;
               			etat = E_FIN;
			   			   break;
               		case '*':
               			lexeme_en_cours.nature = MUL;
               			etat = E_FIN;
			   			   break;
                     case '/':
                        lexeme_en_cours.nature = DIV;
                        etat = E_FIN;
                        break;
		       		   default:
						      printf("Erreur_Lexicale") ;
				 		      exit(0) ;
				 	      } ;
		   			   avancer_car() ;
					   break ;

				default:
		           printf("Erreur_Lexicale\n") ;
		           exit(0) ;
		} ;
		break ;

		case E_ENTIER:  // reconnaissance d'un entier
			switch(nature_caractere(caractere_courant())) {
			   case CHIFFRE:
		  			ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
               lexeme_en_cours.valeur = lexeme_en_cours.valeur * 10 + caractere_courant() - '0';
               etat = E_ENTIER;
               avancer_car ();
					break ;

				default:
                 	etat = E_FIN;
          	} ;

	    case E_FIN:  // etat final
		break ;
	    
	  } ; // fin du switch(etat)
	} ; // fin du while (etat != fin)
   }

   /* --------------------------------------------------------------------- */

   // cette fonction ajoute le caractere c a la fin de la chaine s 
   // (la chaine s est donc modifiee)
 
   void ajouter_caractere (char *s, char c) {
	   int l;
	   l = strlen(s) ;
      s[l] = c;
      s[l+1] = '\0';
   };

   /* --------------------------------------------------------------------- */

   Nature_Caractere nature_caractere (char c) {
	   if (fin_de_sequence_car(c)) return C_FIN_SEQUENCE;
	   if (est_chiffre(c)) return CHIFFRE;
	   if (est_symbole(c)) return SYMBOLE;
      if (est_lettre(c)) return LETTRE;
      if (est_aff(c)) return AFFC;
      if (est_sep(c)) return SEPC;
	   return ERREUR_CAR;
   }
   /* --------------------------------------------------------------------- */

   void analyser(char *fichier){
      FILE *file;
      char expr[10];
      int fin_seq;
      // int test;
      // int ligne = 1;
      
      typedef enum {E_INIT, E_INTER, E_FIN, E_ERR} Automata_state ;
      Automata_state state=E_INIT;
      
      file = fopen(fichier, "r");
      if(file == NULL){
         printf("Fichier fourni n'existe pas.\n");
      }

      fin_seq = fscanf(file,"%s", expr);
      // printf("%s, return type : %d\n", expr, fin_seq);
      while (!feof(file)){
         while(fin_seq == 1){
            // if(est_separateur(expr[i])){
            //    continue;
            // }
            switch (state){
               case E_INIT:
                  printf("Current state : E_INIT\n");
                  if(est_entier(expr)){
                     state = E_FIN;
                  } else {
                     state = E_ERR;
                  }
                  break;
               case E_FIN:
                  printf("Current state : E_FIN\n");
                  // test = est_symbol_car(expr);
                  // printf("est_symbol_car return : %d\n", test);
                  // exit(1);
                  if(est_entier(expr)){
                     state = E_FIN;
                  } else if(est_symbol_car(expr)) {
                     state = E_INTER;
                  } else {
                     state = E_ERR;
                  }
                  break;
               case E_INTER:
                  printf("Current state : E_INTER\n");
                  if(est_entier(expr)){
                     state = E_FIN;
                  } else {
                     state = E_ERR;
                  }
                  break;
               
               default:
                  printf("Current state : E_ERR\n");
                  break;
            }
            fin_seq = fscanf(file,"%s", expr);
         }
         if(state == E_FIN){
            printf("Expression est valide.\n");
         } else {
            printf("Erreur de syntax d'expression\n");
         }
         // ligne++;
         // state = E_INIT;
      }
      fclose(file);
   }
   /* --------------------------------------------------------------------- */
   // Fonction analyse avec lexeme
   void analyser_fin(char * fichier){
      // Initialisation pour l'automate
      demarrer_car(fichier);
      avancer_anlys();
      
      while (! fin_de_sequence()) { 
        // afficher (lexeme_courant()) ;
         printf("%c ",caractere_courant());
         avancer_anlys() ;
      };
   }
   /* --------------------------------------------------------------------- */
   // Fonction analyse avec lexeme
   void afficher_etat(Etat_Automate etat){
      switch(etat){
         case E_INIT: 
            printf("E_INIT");
            break;
         case E_AFF:
            printf("E_AFF");
            break; 
         case E_ENTIER: 
            printf("E_ENTIER");
            break;
         case E_IDF:
            printf("E_IDF");
            break;
         case E_SYMB: 
            printf("E_SYMB");
            break;
         case E_ERR: 
            printf("E_ERR");
            break;
         case E_FIN: 
            printf("E_FIN");
            break;
         case E_FIN_ERR:
            printf("E_FIN_ERR");  
            break;       
      }
   }
   void analyser_lexem(){
      Etat_Automate etat=E_INIT;

      lexeme_en_cours.chaine[0] = '\0' ;

      while(etat != E_FIN && etat != E_FIN_ERR){
         
         // on oublie les espaces vide inclus ceux entre des chiffre ex : 12 65 meme chose que 1256
         while (est_separateur(caractere_courant())) {
            avancer_car() ;
         };

         printf("Caractere courant : %c\tL'etat debut cycle : ", caractere_courant());
         afficher_etat(etat);
         printf(" -> ");

         switch (etat){

            case E_INIT:
               switch (nature_caractere(caractere_courant())){      

                  case LETTRE:
                     lexeme_en_cours.nature = NOMV;
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                     etat = E_INIT;
                     avancer_car();
                     break;

                  case C_FIN_SEQUENCE: 
                     lexeme_en_cours.nature = E_FIN_ERR;
                     etat = E_FIN_ERR;
                     break ;

                  case AFFC:
                     lexeme_en_cours.nature = AFF;
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                     etat = E_AFF;
                     lexeme_en_cours.chaine[0] = '\0';
                     avancer_car();
                     break;

                  default:
                     etat = E_ERR;
                     avancer_car();
                     break;
               };
               break;   
            
            case E_AFF:
               switch (nature_caractere(caractere_courant())){
                   
                  case LETTRE:
                     lexeme_en_cours.nature = NOMV;
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                     etat = E_IDF;
                     lexeme_en_cours.chaine[0] = '\0';
                     avancer_car();
                     break;
                     
                  case CHIFFRE:
                     lexeme_en_cours.nature = ENTIER;
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                     lexeme_en_cours.valeur = (lexeme_en_cours.valeur * 10) + (caractere_courant() - '0');
                     etat = E_ENTIER;
                     lexeme_en_cours.chaine[0] = '\0';
                     avancer_car();
                     break;
                  
                  case C_FIN_SEQUENCE: 
                     lexeme_en_cours.nature = E_FIN_ERR;
                     etat = E_FIN_ERR;
                     avancer_car();
                     break ;

                  default:
                     printf(" Ca se plante ici ");
                     etat = E_ERR;
                     break;
				   };
               break;
            
            case E_ENTIER:
               switch (nature_caractere(caractere_courant())){
                  case CHIFFRE:
                     lexeme_en_cours.nature = ENTIER;
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     lexeme_en_cours.valeur = (lexeme_en_cours.valeur * 10) + (caractere_courant() - '0');
                     etat = E_ENTIER;
                     avancer_car();
                     break; 
                  
                  case SYMBOLE:
                     switch(caractere_courant()){
                        case '+':
                           lexeme_en_cours.nature = PLUS;
                           break;
                        case '-':
                           lexeme_en_cours.nature = MOINS;
                           break;
                        case '*':
                           lexeme_en_cours.nature = MUL;
                           break;
                        case '/':
                           lexeme_en_cours.nature = DIV;
                           break;
                        default:
                           etat = E_ERR;
                           break;
                     };
                     lexeme_en_cours.valeur = 0;
                     etat = E_SYMB;
                     lexeme_en_cours.chaine[0] = '\0';
                     avancer_car();
                     break;

                  case SEPC:
                     lexeme_en_cours.chaine[0] = '\0';
                     lexeme_en_cours.nature = SEP;
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                     etat = E_FIN;
                     avancer_car();
                     break;

                  case C_FIN_SEQUENCE: 
                     lexeme_en_cours.nature = E_FIN_ERR;
                     etat = E_FIN_ERR;
                     avancer_car();
                     break ;

                  default:
                     etat = E_ERR;
                     avancer_car();
               };
               break;

            case E_IDF:
               switch (nature_caractere(caractere_courant())){      

                  case LETTRE:
                     lexeme_en_cours.nature = NOMV;
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                     etat = E_IDF;
                     avancer_car();
                     break;

                  case C_FIN_SEQUENCE: 
                     lexeme_en_cours.nature = E_FIN_ERR;
                     etat = E_FIN_ERR;
                     avancer_car();
                     break ;

                  case SYMBOLE:
                     lexeme_en_cours.chaine[0] = '\0';
                     switch(caractere_courant()){
                        case '+':
                           lexeme_en_cours.nature = PLUS;
                           break;
                        case '-':
                           lexeme_en_cours.nature = MOINS;
                           break;
                        case '*':
                           lexeme_en_cours.nature = MUL;
                           break;
                        case '/':
                           lexeme_en_cours.nature = DIV;
                           break;
                        default:
                           etat = E_ERR;
                           break;
                     };
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                     etat = E_SYMB;
                     avancer_car();
                     break;

                  case SEPC:
                     lexeme_en_cours.chaine[0] = '\0';
                     lexeme_en_cours.nature = SEP;
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                     etat = E_FIN;
                     avancer_car();
                     break;

                  default:
                     lexeme_en_cours.nature = ERREUR_CAR;
                     etat = E_ERR;
                     avancer_car();
                     break;
               };
               break;  

            case E_SYMB:
               lexeme_en_cours.chaine[0] = '\0';
               switch(nature_caractere(caractere_courant())){
                  case CHIFFRE:
                     lexeme_en_cours.nature = ENTIER;
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     lexeme_en_cours.valeur = (lexeme_en_cours.valeur * 10) + (caractere_courant() - '0');
                     etat = E_ENTIER;
                     lexeme_en_cours.chaine[0] = '\0';
                     avancer_car();
                     break; 

                  case LETTRE:
                     lexeme_en_cours.nature = NOMV;
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     etat = E_IDF;
                     avancer_car();
                     break;

                  case C_FIN_SEQUENCE: 
                     lexeme_en_cours.nature = E_FIN_ERR;
                     etat = E_FIN_ERR;
                     avancer_car();
                     break ;

                  default:
                     etat = E_ERR;
                     avancer_car();
                     break;
               };
               break;

            case E_ERR:
               switch(nature_caractere(caractere_courant())){
                  case SEPC:
                     lexeme_en_cours.nature = SEP;
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     lexeme_en_cours.chaine[0] = '\0';
                     etat = E_FIN_ERR;
                     avancer_car();
                     break;

                  default:
                     etat = E_ERR;
                     avancer_car();
                     break;
               };
               break;

            case E_FIN:
               printf("Fin de l'expression.\n");
               break;

            case E_FIN_ERR:
               printf("Fin de sequence inattendu\n");
         }      
         
         printf("L'etat fin cycle : ");
         afficher_etat(etat);
         printf("\n");
      }
   }
   /* --------------------------------------------------------------------- */
   // vaut vrai ssi c designe un caractere separateur
   int est_separateur(char c) { 
      return c == ' ' || c == '\t' || c == '\n' ;
   }
/* --------------------------------------------------------------------- */
   // vaut vrai ssi c designe une lettre
   int est_lettre(char c){
      return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
   };
/* --------------------------------------------------------------------- */
   // vaut vrai ssi c designe "=", ":=" , "<-"
   int est_aff(char c){
      return c == '='; 
   };
/* --------------------------------------------------------------------- */
   // vaut vrai ssi c designe ':'
   int est_sep(char c){
      return c == ';';
   };
/* --------------------------------------------------------------------- */
   // vaut vrai ssi c designe un entier
   int est_entier(char * str) {
      int len = strlen(str);
      for(int i = 0; i < len; i++){
         if(!est_chiffre(str[i])){
            return 0;
         }
      }
      return 1;
   }

   /* --------------------------------------------------------------------- */

   // vaut vrai ssi c designe un caractere chiffre
   int est_chiffre(char c) {
      return c >= '0' && c <= '9' ;
   }

   /* --------------------------------------------------------------------- */

   // vaut vrai ssi c designe un caractere correspondant a un symbole arithmetique
   int est_symbole(char c)  {
      switch (c) {
         case '+':  
	 	   case '-':  
	 	   case '*':
	 	   case '/':
            return 1;

      default:
         return 0;
      } 
   }
/* --------------------------------------------------------------------- */
   // vaut vrai ssi c designe un caractere chiffre
   int est_symbol_car(char * str) {
      int len = strlen(str);
      if(est_symbole(str[0]) && len ==1){
         return 1;
      } else {
         return 0;
      }
   
   }

   /* --------------------------------------------------------------------- */

   // renvoie la chaine de caracteres correspondant a la nature du lexeme
   char *Nature_vers_Chaine (Nature_Lexeme nature) {
	switch (nature) {
		case ENTIER: return "ENTIER" ;
		case PLUS: return "PLUS" ;
      case MOINS: return "MOINS" ;            
      case MUL: return "MUL" ;              
      case DIV : return "DIV";
      case FIN_SEQUENCE: return "FIN_SEQUENCE" ;     
      default: return "ERREUR" ;            
	} ;
   } 

   /* --------------------------------------------------------------------- */

   // affiche a l'ecran le lexeme l
   void afficher(Lexeme l) {

      switch (l.nature) {
         case FIN_SEQUENCE: 
            break;
         default: 
            printf("(ligne %d, ", l.ligne);
            printf("colonne %d) : ",l.colonne);
	    printf("[") ;
            printf("nature = %s", Nature_vers_Chaine(l.nature)) ;
            printf(", chaine = %s, ", l.chaine) ;
            switch(l.nature) {
                 case ENTIER:
                      printf("valeur = %d", l.valeur);
                 default:
                      break;
            } ;
	    printf("]") ;
	} ;
   }

   /* --------------------------------------------------------------------- */

