#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table_de_symbole.h"

Var_DB tab_symb;

void inserer_tab(Var_DB *tab, char * var, int val){
    // Modification de val si var sexiste deja
    for(int i = 0; i < tab->buffer_count; i++){
        if(tab->tab_elem[i].variable == var){
            strcpy(tab->tab_elem[i].variable, val);
            return;
        }
    }
    // Insertion de var et val
    tab->buffer_count++;
    strcpy(tab->tab_elem[tab->buffer_count].variable, var);
    strcpy(tab->tab_elem[tab->buffer_count].valeur, val);
};

void afficher_val(Var_DB *tab, int var){
    for(int i = 0; i < tab->buffer_count; i++){
        if(tab->tab_elem[i].variable == var){
            printf("%d",tab->tab_elem[i].valeur);
            break;
        }
    }
};

void print_all_table(Var_DB *tab){
    int i=0;
    while (i < tab->buffer_count){
        printf("%c : ",tab->tab_elem[i].variable);
        printf("%d\n",tab->tab_elem[i].valeur);
        i++;
    }
}

int main(){

}
