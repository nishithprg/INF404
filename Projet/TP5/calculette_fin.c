#include <stdio.h>
#include "analyse_lexicale.h"
#include "lecture_caracteres.h"

int main (int argc, char *argv[]) {
    if (argc >= 1) {
        demarrer_car(argv[1]);
        avancer_anlys();
    } else {
        printf("Il faut donner un nom de fichier en argument !") ;
        return 1 ; 
    } ; 
   while (! fin_de_sequence()) { 
        afficher (lexeme_courant()) ;
        printf("\n") ;
        avancer_anlys() ;
    } ;
    return 0 ;
}