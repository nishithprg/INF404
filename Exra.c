#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 

#include "/home/nishith/INF404/Projet/lecture_caracteres.h"
#include "/home/nishith/INF404/Projet/analyse_lexicale.h"

 void reconnaitre_lexeme123(){
      Etat_Automate etat=E_INIT;

      lexeme_en_cours.chaine[0] = '\0';
      lexeme_en_cours.valeur = 0;

      while(etat != E_FIN){
         
         // on oublie les espaces vide inclus ceux entre des chiffre ex : 12 65 meme chose que 1256
         while (est_separateur(caractere_courant())) {
            avancer_car() ;
         };

         // Affichage d'etat au debut d'iteration. Affichage d'etat a la fin d'iteration dispo apres le grand switch
         // printf("Caractere courant : %c\tL'etat debut cycle : ", caractere_courant());
         // afficher_etat(etat);
         // printf(" -> ");

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
                     lexeme_en_cours.nature = FIN_SEQUENCE;
                     etat = E_FIN;
                     break;

                  case AFFC:
                     lexeme_en_cours.chaine[0] = '\0';
                     lexeme_en_cours.nature = AFF;
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                     etat = E_AFF;
                     avancer_car();
                     break;

                  default:
                     printf("Erreur_Lexicale\n") ;
                     exit(0) ;
               };
               break;   
            
            case E_AFF:
               switch (nature_caractere(caractere_courant())){
                   
                  case LETTRE:
                     lexeme_en_cours.chaine[0] = '\0';
                     lexeme_en_cours.nature = NOMV;
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                     etat = E_IDF;
                     avancer_car();
                     break;
                     
                  case CHIFFRE:
                     lexeme_en_cours.valeur = 0;
                     lexeme_en_cours.chaine[0] = '\0';
                     lexeme_en_cours.nature = ENTIER;
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                     lexeme_en_cours.valeur = (lexeme_en_cours.valeur * 10) + (caractere_courant() - '0');
                     etat = E_ENTIER;
                     avancer_car();
                     break;
                  
                  case C_FIN_SEQUENCE: 
                     lexeme_en_cours.nature = FIN_SEQUENCE;
                     etat = E_FIN;
                     break;

                  default:
                     printf("Erreur_Lexicale\n") ;
                     exit(0) ;
                     
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
                           printf("Erreur_Lexicale\n") ;
                           exit(0) ;
                     };
                     lexeme_en_cours.valeur = 0;
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                     etat = E_SYMB;
                     avancer_car();
                     break;

                  case SEPC:
                     lexeme_en_cours.valeur = 0;
                     lexeme_en_cours.chaine[0] = '\0';
                     lexeme_en_cours.nature = SEP;
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                     etat = E_FIN;
                     avancer_car();
                     break;

                  case C_FIN_SEQUENCE: 
                     lexeme_en_cours.nature = FIN_SEQUENCE;
                     etat = E_FIN;
                     break;

                  default:
                     printf("Erreur_Lexicale\n") ;
                     exit(0) ;
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
                     lexeme_en_cours.nature = FIN_SEQUENCE;
                     etat = E_FIN;
                     break;

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
                           printf("Erreur_Lexicale\n") ;
                           exit(0) ;
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
                     printf("Erreur_Lexicale\n") ;
                     exit(0) ;
               };
               break;  

            case E_SYMB:
               
               switch(nature_caractere(caractere_courant())){
                  case CHIFFRE:
                     lexeme_en_cours.valeur = 0;
                     lexeme_en_cours.chaine[0] = '\0';
                     lexeme_en_cours.nature = ENTIER;
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     lexeme_en_cours.valeur = (lexeme_en_cours.valeur * 10) + (caractere_courant() - '0');
                     etat = E_ENTIER;
                     avancer_car();
                     break; 

                  case LETTRE:
                     lexeme_en_cours.chaine[0] = '\0';
                     lexeme_en_cours.nature = NOMV;
                     ajouter_caractere(lexeme_en_cours.chaine, caractere_courant());
                     lexeme_en_cours.ligne = numero_ligne();
                     lexeme_en_cours.colonne = numero_colonne();
                     etat = E_IDF;
                     avancer_car();
                     break;

                  case C_FIN_SEQUENCE: 
                     lexeme_en_cours.nature = FIN_SEQUENCE;
                     etat = E_FIN;
                     break;

                  default:
                     printf("Erreur_Lexicale\n") ;
                     exit(0) ;
               };
               break;

            case E_FIN:
               printf("Fin de l'expression.\n");
               break;
               
            
         } // End switch Automata states
         afficher(lexeme_courant());
         printf("\n");
         
         // Affichage d'etat a la fin d'iteration
         // printf("L'etat fin cycle : ");
         // afficher_etat(etat);
         // printf("\n");
      } // End while
   } // End analyse_lexeme()