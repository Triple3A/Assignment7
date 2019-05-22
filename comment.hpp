#ifndef COMMENT_H
#define COMMENT_H

#include <iostream>
#include <vector>

// class Not_found {};
class User;

class Comment
{
public:
	Comment(std::string _content, User* _owner);
	void set_id(int _id);
	int get_id();
	void add_reply(std::string);
	User* get_owner();
private:
	int id;
	std::string content;
	User* owner;
	std::vector<std::string> replies;
};
#endif