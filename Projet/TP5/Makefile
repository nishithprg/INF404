PROGRAMS= test_lexeme interpreteur

all:$(PROGRAMS)

lecture_caracteres.o: lecture_caracteres.c lecture_caracteres.h
	gcc -g -Wall -c lecture_caracteres.c

analyse_lexicale.o: analyse_lexicale.c analyse_lexicale.h lecture_caracteres.h
	gcc -g -Wall -c analyse_lexicale.c

table_de_symbole.o: table_de_symbole.c table_de_symbole.h
	gcc -c table_de_symbole.c

ast_construction.o: ast_construction.c ast_construction.h type_ast.h
	gcc -c ast_construction.c

ast_parcours.o: ast_parcours.c ast_parcours.h type_ast.h table_de_symbole.h
	gcc -c ast_parcours.c

analyse_syntaxique.o : analyse_syntaxique.c analyse_syntaxique.h lecture_caracteres.h analyse_lexicale.h ast_construction.h ast_parcours.h type_ast.h table_de_symbole.h
	gcc -g -Wall -c analyse_syntaxique.c

test_lexeme.o: analyse_lexicale.h lecture_caracteres.h
	gcc -g -Wall -c test_lexeme.c

interpreteur.o: interpreteur.c analyse_syntaxique.h analyse_lexicale.h lecture_caracteres.h ast_construction.h ast_parcours.h type_ast.h table_de_symbole.h
	gcc -g -Wall -c interpreteur.c

test_lexeme: analyse_lexicale.o  lecture_caracteres.o  test_lexeme.o
	gcc -g -Wall -o test_lexeme analyse_lexicale.o  lecture_caracteres.o  test_lexeme.o

interpreteur: analyse_syntaxique.o analyse_lexicale.o lecture_caracteres.o interpreteur.o ast_construction.o ast_parcours.o table_de_symbole.o
	gcc -g -Wall -o interpreteur analyse_syntaxique.o analyse_lexicale.o lecture_caracteres.o interpreteur.o ast_construction.o ast_parcours.o table_de_symbole.o

clean:
	rm -f text_lexeme interpreteur *.o


