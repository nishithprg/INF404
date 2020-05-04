#ifndef __TAB_SYMB__
#define __TAB_SYMB__

typedef struct element{
    char variable[256];
    int valeur;
} Element_table;

typedef struct tableau{
    Element_table tab_elem[256];
    int buffer_count;
} Var_DB;

void init_tab(Var_DB *tab);

void inserer_tab(Var_DB *tab, char * var, int val);

int existe_val(Var_DB stab, char * var);

void print_all_table(Var_DB tab);

#endif


