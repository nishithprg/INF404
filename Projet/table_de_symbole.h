#ifndef __TAB_SYMB__
#define TAB_SYMB__

typedef struct element{
    char variable[256];
    char valeur[];
} Element_table;

typedef struct tableau{
    Element_table tab_elem[256];
    int buffer_count;
} Var_DB;

void inserer_tab(Var_DB *tab, char * var, int val);

void afficher_val(Var_DB *tab, int var);

#endif


