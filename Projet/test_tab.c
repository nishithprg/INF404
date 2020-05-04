#include <stdio.h>
#include <stdlib.h>

#include "table_de_symbole.h"

int main(){
    char nom[256] = "nishith";
    int age = 19;

    Var_DB tab_symb;
    init_tab(&tab_symb);

    inserer_tab(&tab_symb,nom,age);
    print_all_table(tab_symb);
    printf("******************************\n");
    age = 20;
    // int res = existe_val(tab_symb,nom);
    // if(existe_val(tab_symb,nom)){
    //     printf("nishith exists\n");
    // } else {
    //     printf("nishiht doesn't exist\n");
    // }
    
    inserer_tab(&tab_symb,nom,age);
    print_all_table(tab_symb);

    return 0;
}