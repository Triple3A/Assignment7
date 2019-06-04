CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) netflix.out
	
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

netflix.out: $(BUILD_DIR)/website_handler.o $(BUILD_DIR)/repository_of_users.o $(BUILD_DIR)/user.o $(BUILD_DIR)/repository_of_films.o $(BUILD_DIR)/film.o $(BUILD_DIR)/publisher.o $(BUILD_DIR)/repository_of_comments.o $(BUILD_DIR)/comment.o $(BUILD_DIR)/exceptions.o $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o
	$(CC)  $(CF)  $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/website_handler.o $(BUILD_DIR)/repository_of_users.o $(BUILD_DIR)/user.o $(BUILD_DIR)/repository_of_films.o $(BUILD_DIR)/film.o $(BUILD_DIR)/publisher.o $(BUILD_DIR)/repository_of_comments.o $(BUILD_DIR)/comment.o $(BUILD_DIR)/exceptions.o -o netflix.out
	
$(BUILD_DIR)/website_handler.o: repository_of_users.hpp repository_of_films.hpp website_handler.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp handlers.hpp
	$(CC)  $(CF)  -c website_handler.cpp -o $(BUILD_DIR)/website_handler.o
	
$(BUILD_DIR)/repository_of_users.o: user.hpp repository_of_users.cpp
	$(CC)  $(CF)  -c repository_of_users.cpp -o $(BUILD_DIR)/repository_of_users.o
	
$(BUILD_DIR)/user.o: film.hpp exceptions.hpp user.cpp
	$(CC)  $(CF)  -c user.cpp -o $(BUILD_DIR)/user.o
	
$(BUILD_DIR)/repository_of_films.o: film.hpp repository_of_films.cpp
	$(CC)  $(CF)  -c repository_of_films.cpp -o $(BUILD_DIR)/repository_of_films.o
	
$(BUILD_DIR)/film.o: publisher.hpp film.cpp
	$(CC)  $(CF)  -c film.cpp -o $(BUILD_DIR)/film.o
	
$(BUILD_DIR)/publisher.o: user.hpp film.hpp publisher.cpp
	$(CC)  $(CF)  -c publisher.cpp -o $(BUILD_DIR)/publisher.o
	
$(BUILD_DIR)/repository_of_comments.o: comment.hpp repository_of_comments.cpp
	$(CC)  $(CF)  -c repository_of_comments.cpp -o $(BUILD_DIR)/repository_of_comments.o
	
$(BUILD_DIR)/comment.o: exceptions.hpp comment.cpp
	$(CC)  $(CF)  -c comment.cpp -o $(BUILD_DIR)/comment.o
	
$(BUILD_DIR)/exceptions.o: exceptions.cpp exceptions.hpp
	$(CC)  $(CF)  -c exceptions.cpp -o $(BUILD_DIR)/exceptions.o


$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC)  $(CF)  -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC)  $(CF)  -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC)  $(CF)  -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC)  $(CF)  -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC)  $(CF)  -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC)  $(CF)  -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp website_handler.hpp
	$(CC)  $(CF)  -c handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC)  $(CF)  -c my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC)  $(CF)  -c main.cpp -o $(BUILD_DIR)/main.o


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null

