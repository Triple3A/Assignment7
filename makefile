CC := g++ -std=c++11
BUILD_DIR=build
TEMPLATE_DIR=.template

$(BUILD_DIR):
mkdir -p $(BUILD_DIR)

all: netflix.out
	
netflix.out: main.o website_handler.o repository_of_users.o user.o repository_of_films.o film.o publisher.o repository_of_comments.o comment.o exceptions.o $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o
	$(CC) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o website_handler.o repository_of_users.o user.o repository_of_films.o film.o publisher.o repository_of_comments.o comment.o exceptions.o -o netflix.out
	
website_handler.o: repository_of_users.hpp repository_of_films.hpp website_handler.cpp
	$(CC) -c website_handler.cpp -o website_handler.o
	
repository_of_users.o: user.hpp repository_of_users.cpp
	$(CC) -c repository_of_users.cpp -o repository_of_users.o
	
user.o: film.hpp exceptions.hpp user.cpp
	$(CC) -c user.cpp -o user.o
	
repository_of_films.o: film.hpp repository_of_films.cpp
	$(CC) -c repository_of_films.cpp -o repository_of_films.o
	
film.o: publisher.hpp film.cpp
	$(CC) -c film.cpp -o film.o
	
publisher.o: user.hpp film.hpp publisher.cpp
	$(CC) -c publisher.cpp -o publisher.o
	
repository_of_comments.o: comment.hpp repository_of_comments.cpp
	$(CC) -c repository_of_comments.cpp -o repository_of_comments.o
	
comment.o: exceptions.hpp comment.cpp
	$(CC) -c comment.cpp -o comment.o
	
exception.o: exceptions.cpp
	$(CC) -c exceptions.cpp -o exceptions.o


$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
    $(CC) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
    $(CC) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
    $(CC) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
    $(CC) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
    $(CC) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
    $(CC) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp website_handler.hpp
    $(CC) -c handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
    $(CC) -c my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
    $(CC) -c main.cpp -o $(BUILD_DIR)/main.o


.PHONY: clean
clean:
    rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null

