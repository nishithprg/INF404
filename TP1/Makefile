
# test_lexeme: analyse_lexicale.o  lecture_caracteres.o  test_lexeme.o
	# gcc -g -Wall -o test_lexeme analyse_lexicale.o  lecture_caracteres.o  test_lexeme.o
calculette: analyse_lexicale.o  lecture_caracteres.o  calculette.o
	gcc -g -Wall -o calculette analyse_lexicale.o  lecture_caracteres.o  calculette.o
	
analyse_lexicale.o: analyse_lexicale.c analyse_lexicale.h lecture_caracteres.h
	gcc -g -Wall -c analyse_lexicale.c

lecture_caracteres.o: lecture_caracteres.h lecture_caracteres.c
	gcc -g -Wall -c lecture_caracteres.c

# test_lexeme.c: analyse_lexicale.h
# 	gcc -g -Wall -c test_lexeme.c

calculette.o: analyse_lexicale.h lecture_caracteres.h
	gcc -g -Wall -c calculette.c

clean:
	rm -f text_lexeme calculette *.o


