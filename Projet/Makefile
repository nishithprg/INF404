
test_lexeme: analyse_lexicale.o  lecture_caracteres.o  test_lexeme.o
	gcc -g -Wall -o test_lexeme analyse_lexicale.o  lecture_caracteres.o  test_lexeme.o

interpreteur: analyse_syntaxique.o analyse_lexicale.o  lecture_caracteres.o  interpreteur.o
	gcc -g -Wall -o interpreteur analyse_lexicale.o  lecture_caracteres.o  interpreteur.o
	
analyse_syntaxique.o : analyse_syntaxique.c analyse_syntaxique.h analyse_lexicale.h lecture_caracteres.h
	gcc -g -Wall -c analyse_syntaxique.c

analyse_lexicale.o: analyse_lexicale.c analyse_lexicale.h lecture_caracteres.h
	gcc -g -Wall -c analyse_lexicale.c

lecture_caracteres.o: lecture_caracteres.c lecture_caracteres.h
	gcc -g -Wall -c lecture_caracteres.c

test_lexeme.o: analyse_lexicale.h lecture_caracteres.h
	gcc -g -Wall -c test_lexeme.c

interpreteur.o: interpreteur.c analyse_lexicale.h lecture_caracteres.h
	gcc -g -Wall -c interpreteur.c

clean:
	rm -f text_lexeme interpreteur *.o


