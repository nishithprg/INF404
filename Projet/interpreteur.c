#include <stdio.h>

#include "lecture_caracteres.h"
#include "analyse_lexicale.h"
#include "type_ast.h"
#include "ast_construction.h"
#include "ast_parcours.h"
#include "analyse_syntaxique.h"
#include "table_de_symbole.h"

int main (int argc, char *argv[]) {
    if (argc >= 1) {
        demarrer(argv[1]);
    } else {
        printf("Il faut donner un nom de fichier en argument !") ;
        return 1 ; 
    };
    analyser(argv[1]);

    return 0;
}