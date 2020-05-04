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
   Lexeme lexeme_en_cours;	/* le lexeme courant */

   void reconnaitre_lexeme();

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
      if (est_sep(c)) return SEP;
	   return ERREUR_CAR;
   }
  
   /* --------------------------------------------------------------------- */
   // Fonction analyse avec lexeme
   void afficher_etat(Etat_Automate etat){
      switch(etat){
         case E_INIT: 
            printf("E_INIT");
            break;
         case E_ENTIER: 
            printf("E_ENTIER");
            break;
         case E_IDF:
            printf("E_IDF");
            break;
         case E_SYMB:
            printf("E_SYMB");
         case E_FIN: 
            printf("E_FIN");
            break;     
      }
   }
   
   void reconnaitre_lexeme() {
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
                  ajouter_caractere (lexeme_en_cours.chaine, caractere_courant());
                  lexeme_en_cours.valeur = caractere_courant() - '0';
                  etat = E_ENTIER;
                  avancer_car() ;
                  break ;

				   case SYMBOLE: 
		       		lexeme_en_cours.ligne = numero_ligne();
               	lexeme_en_cours.colonne = numero_colonne();
		       		ajouter_caractere (lexeme_en_cours.chaine, caractere_courant());
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
                     case '!':
               			lexeme_en_cours.nature = DIFF;
               			etat = E_SYMB;
			   			   break;
                     case '<':
               			lexeme_en_cours.nature = LT;
               			etat = E_SYMB;
			   			   break;
                     case '>':
               			lexeme_en_cours.nature = GT;
               			etat = E_SYMB;
			   			   break;
		       		   default:
						      printf("Erreur_Lexicale\n") ;
				 		      exit(0) ;
				 	      } ;
		   			   avancer_car() ;
					   break ;
            
               case LETTRE:
                  lexeme_en_cours.nature = IDF;
                  lexeme_en_cours.ligne = numero_ligne();
                  lexeme_en_cours.colonne = numero_colonne();
                  ajouter_caractere (lexeme_en_cours.chaine, caractere_courant());
                  etat = E_IDF;
                  avancer_car();
                  break;

               case AFFC:
                  lexeme_en_cours.nature = AFF;
                  lexeme_en_cours.ligne = numero_ligne();
                  lexeme_en_cours.colonne = numero_colonne();
                  ajouter_caractere (lexeme_en_cours.chaine, caractere_courant());
                  etat = E_SYMB;
                  avancer_car();
                  break;

               case SEP:
                  lexeme_en_cours.nature = SEPINST;
                  lexeme_en_cours.ligne = numero_ligne();
                  lexeme_en_cours.colonne = numero_colonne();
                  ajouter_caractere (lexeme_en_cours.chaine, caractere_courant());
                  etat = E_FIN;
                  avancer_car();
                  break;

               default:
                  printf("Erreur_Lexicale\n") ;
                  exit(0) ;
		      } ;
		      break;

		      case E_ENTIER:  // reconnaissance d'un entier
               switch(nature_caractere(caractere_courant())) {
                  case CHIFFRE:
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant()) ;
                     lexeme_en_cours.valeur = lexeme_en_cours.valeur * 10 + caractere_courant() - '0';
                     etat = E_ENTIER;
                     avancer_car();
                     break ;

                  default:
                        etat = E_FIN;
               };
               break;

            case E_IDF:
               switch(nature_caractere(caractere_courant())) {
                  case LETTRE:
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant()) ;
                     etat = E_IDF;
                     if(!strcmp(lexeme_en_cours.chaine, "if")){
                        lexeme_en_cours.nature = IF;
                     } else if(!strcmp(lexeme_en_cours.chaine, "then")){
                        lexeme_en_cours.nature = THEN;
                     } else if(!strcmp(lexeme_en_cours.chaine, "else")){
                        lexeme_en_cours.nature = ELSE;
                     } else if(!strcmp(lexeme_en_cours.chaine, "fi")){
                        lexeme_en_cours.nature = FI;
                     }
                     avancer_car();
                     break ;

                  default:
                        etat = E_FIN;
               };
               break;

            case E_SYMB:
               lexeme_en_cours.ligne = numero_ligne();
               lexeme_en_cours.colonne = numero_colonne();
               if(!strcmp(lexeme_en_cours.chaine, "=")){
                  switch(caractere_courant()){
                     case '=':
                        ajouter_caractere(lexeme_en_cours.chaine, caractere_courant()) ;
                        lexeme_en_cours.nature = EQL;
                        etat = E_FIN;
                        break;
                     default:
                        switch(nature_caractere(caractere_courant())){
                           case SYMBOLE:
                              printf("Erreur_Lexicale\n");
				 		            exit(0);
                           default:
                              break;
                        }
                        etat = E_FIN;
                  }
               } else if(!strcmp(lexeme_en_cours.chaine, "!")){
                  switch(caractere_courant()){
                     case '=':
                        ajouter_caractere(lexeme_en_cours.chaine, caractere_courant()) ;
                        lexeme_en_cours.nature = DIFF;
                        etat = E_FIN;
                        break;
                     default:
                        switch(nature_caractere(caractere_courant())){
                           case SYMBOLE:
                              printf("Erreur_Lexicale\n");
				 		            exit(0);
                           default:
                              break;
                        }
                        etat = E_FIN;
                  } 
               } else if(!strcmp(lexeme_en_cours.chaine, "<")){
                  switch(caractere_courant()){
                     case '=':
                        ajouter_caractere(lexeme_en_cours.chaine, caractere_courant()) ;
                        lexeme_en_cours.nature = LE;
                        etat = E_FIN;
                        break;
                     default:
                        switch(nature_caractere(caractere_courant())){
                           case SYMBOLE:
                              printf("Erreur_Lexicale\n");
				 		            exit(0);
                           default:
                              break;
                        }
                        etat = E_FIN;
                  }   
               } else if(!strcmp(lexeme_en_cours.chaine, ">")){
                  switch(caractere_courant()){
                     case '=':
                        ajouter_caractere(lexeme_en_cours.chaine, caractere_courant()) ;
                        lexeme_en_cours.nature = GE;
                        etat = E_FIN;
                        break;
                     default:
                        switch(nature_caractere(caractere_courant())){
                           case SYMBOLE:
                              printf("Erreur_Lexicale\n");
				 		            exit(0);
                           default:
                              break;
                        }
                        etat = E_FIN;
                  }
               }
               avancer_car();
               break;

	         case E_FIN:  // etat final
		         break ;
	    
	      } ; // fin du switch(etat)
	   } ; // fin du while (etat != fin)
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
         case '!':
         case '<':
         case '>':

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
      case IDF: return "IDF" ;
      case SEPINST: return "SEPINST";
      case AFF: return "AFF";
		case PLUS: return "PLUS" ;
      case MOINS: return "MOINS" ;            
      case MUL: return "MUL" ;              
      case DIV : return "DIV";
      case FIN_SEQUENCE: return "FIN_SEQUENCE" ;     
      default: return "ERREUR" ;  
      case IF: return "IF";      
      case THEN: return "THEN";
      case ELSE: return "ELSE";
      case FI: return "FI";
      case EQL: return "EQL";
      case DIFF: return "DIFF";
      case LE: return "LE";
      case GE: return "GE";
      case LT: return "LT";
      case GT: return "GT";
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
	    printf("[");
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

