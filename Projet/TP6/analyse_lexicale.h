#ifndef __ANAL_LEC__
#define __ANAL_LEC__
/* ;------------------------------------------------------------------------
-- paquetage machine_lexemes
--
-- analyse lexicale d'une expression arithmetique
--
-- P.Habraken - 18/01/2010
--
-- 2 aout 2006 - PH :
-- remplacement record a champs variants par record "plat"
------------------------------------------------------------------------ */

   typedef enum {
	   ERREUR_CAR,       // caractere incorrect
	   CHIFFRE,			   // chiffre 
	   SYMBOLE,          // symboles operators (arith and comp)
      LETTRE,           // alphabets
      SEP,              // ;
      AFFC,			      // =
      C_FIN_SEQUENCE    // caractere de fin de sequence     
   } Nature_Caractere ;

   typedef enum { 
      ENTIER,           // sequence de chiffres
      IDF,           // sequence d'alphabet
      SEPINST,              // ;
      IF,
      THEN,
      ELSE,
      FI,
      EQL,              // ==
      DIFF,             // !=
      LE,               // <=
      GE,               // >=
      LT,               // <
      GT,               // >
      AFF,              // =
      PLUS,             // +
      MOINS,            // -
      MUL,              // *
      DIV,              // /
      // PARO,             // (
      // PARF,             // )
      FIN_SEQUENCE     // pseudo lexeme ajoute en fin de sequence
   } Nature_Lexeme ;

   typedef enum {
      E_INIT, 
      E_ENTIER, 
      E_IDF, 
      E_SYMB,
      E_FIN
   } Etat_Automate;

   typedef struct { 
      Nature_Lexeme nature;    // nature du lexeme
      unsigned int ligne;           // numero de ligne
      unsigned int colonne;         // numero de colonne
      char chaine[256];           // chaine de caracteres
      int valeur;          // valeur d'un entier
   } Lexeme ; 

   void afficher(Lexeme l);

   void demarrer(char *nom_fichier);
   // e.i. : indifferent
   // e.f. : la sequence de lexemes est lue dans le fichier designe par
   //        nom_fichier
   //        fin_de_sequence <=> lexeme_courant.nature = FIN_SEQUENCE
   //        (non fin_de_sequence) => lexeme courant est le premier
   //        lexeme de la sequence
   //        l'exception Erreur_Lexicale est levee en cas d'erreur

   void analyser(char *fichier); // Fonction analyse sans lexeme
   
   void analyser_fin(char * fichier); // Fonction initialisation de analyser

   void analyser_lexem(); // Fonction analyse avec lexeme

   void avancer();
   // pre-condition : la machine sequentielle est demarree
   // e.i. : on pose i = rang du lexeme_courant :
   //        (non fin_de_sequence)
   //        et (non lexeme_courant.nature = FIN_SEQUENCE)
   // e.f. : fin_de_sequence <=> lexeme_courant.nature = FIN_SEQUENCE
   //        (non fin_de_sequence) => lexeme_courant est le lexeme i+1
   //        l'exception Erreur_Lexicale est levee en cas d'erreur

   Lexeme lexeme_courant();
   // pre-condition : la machine sequentielle est demarree
   // lexeme_courant est :
   // . le pseudo lexeme FIN_SEQUENCE si fin_de_sequence
   // . le pseudo lexeme ERREUR si une erreur a ete detectee
   // . le lexeme de rang i sinon

   int fin_de_sequence();
   // pre-condition : la machine sequentielle est demarree
   // fin_de_sequence vaut :
   // . vrai si tous les lexemes de la sequence ont ete reconnus
   // . faux sinon

   void arreter();
   // e.i. : la machine sequentielle est demarree
   // e.f. : la machine sequentielle est arretee

   int est_entier(char * str);

   int est_symbol_car(char * str);

   void ajouter_caractere (char *s, char c);
   Nature_Caractere nature_caractere (char c);
   int est_separateur(char c);
   int est_chiffre(char c);
   int est_symbole(char c);
   int est_lettre(char c);
   int est_sep(char c);
   int est_aff(char c);

   void afficher_etat(Etat_Automate etat);

#endif 
