#include <stdio.h>
#include "analyse_lexicale.h"
#include "lecture_caracteres.h"

int main (int argc, char *argv[]) {
    if (argc >= 1) {
        demarrer_car(argv[1]);
    } else {
        printf("Il faut donner un nom de fichier en argument !") ;
        return 1 ; 
    };
    while (!fin_de_sequence_car()){ 
	    analyser_lexem();
    };
    return 0;
}