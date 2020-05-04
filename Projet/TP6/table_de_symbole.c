#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table_de_symbole.h"

void init_tab(Var_DB *tab){
    tab->buffer_count = 0;
};

void inserer_tab(Var_DB *tab, char * var, int val){
    // Modification de val si var sexiste deja
    for(int i = 0; i < tab->buffer_count; i++){
        if(!strcmp(tab->tab_elem[i].variable, var)){
            tab->tab_elem[i].valeur = val;
            return;
        }
    }
    // Insertion de var et val
    strcpy(tab->tab_elem[tab->buffer_count].variable, var);
    tab->tab_elem[tab->buffer_count].valeur = val;
    tab->buffer_count++;
};

int existe_val(Var_DB tab, char * var){
    for(int i = 0; i < tab.buffer_count; i++){
        if(!strcmp(tab.tab_elem[i].variable, var)){
            return tab.tab_elem[i].valeur;
        }
    }
    return 0;
};

void print_all_table(Var_DB tab){
    int i=0;
    while (i < tab.buffer_count){
        printf("%s : ",tab.tab_elem[i].variable);
        printf("%d\n",tab.tab_elem[i].valeur);
        i++;
    }
}

