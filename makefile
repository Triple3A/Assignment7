CC := g++ -std=c++11

all: netflix.out
	
netflix.out: main.o website_handler.o repository_of_users.o user.o
	$(CC) main.o website_handler.o repository_of_users.o user.o -o netflix.out
	
main.o: website_handler.hpp main.cpp
	$(CC) -c main.cpp -o main.o
	
website_handler.o: repository_of_users.hpp website_handler.cpp
	$(CC) -c website_handler.cpp -o website_handler.o
	
repository_of_users.o: user.hpp repository_of_users.cpp
	$(CC) -c repository_of_users.cpp -o repository_of_users.o
	
user.o: user.cpp
	$(CC) -c user.cpp -o user.o
	
.PHONY: clean
clean:
	rm -r *.o 