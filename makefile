CC := g++ -std=c++11

all: netflix.out
	
netflix.out: main.o website_handler.o repository_of_users.o user.o repository_of_films.o film.o publisher.o repository_of_comments.o comment.o
	$(CC) main.o website_handler.o repository_of_users.o user.o repository_of_films.o film.o publisher.o repository_of_comments.o comment.o -o netflix.out
	
main.o: website_handler.hpp main.cpp
	$(CC) -c main.cpp -o main.o
	
website_handler.o: repository_of_users.hpp repository_of_films.hpp website_handler.cpp
	$(CC) -c website_handler.cpp -o website_handler.o
	
repository_of_users.o: user.hpp repository_of_users.cpp
	$(CC) -c repository_of_users.cpp -o repository_of_users.o
	
user.o: film.hpp user.cpp
	$(CC) -c user.cpp -o user.o
	
repository_of_films.o: film.hpp repository_of_films.cpp
	$(CC) -c repository_of_films.cpp -o repository_of_films.o
	
film.o: publisher.hpp film.cpp
	$(CC) -c film.cpp -o film.o
	
publisher.o: user.hpp film.hpp publisher.cpp
	$(CC) -c publisher.cpp -o publisher.o
	
repository_of_comments.o: comment.hpp repository_of_comments.cpp
	$(CC) -c repository_of_comments.cpp -o repository_of_comments.o
	
comment.o: comment.cpp
	$(CC) -c comment.cpp -o comment.o
	
.PHONY: clean
clean:
	rm -r *.o 