#ifndef COMMENT_H
#define COMMENT_H

#include <iostream>
#include <vector>

class Comment
{
public:
	Comment(std::string _content);
	void set_id(int _id);
	int get_id();
	void add_reply(std::string);
private:
	int id;
	std::string content;
	std::vector<std::string> replies;
};
#endif