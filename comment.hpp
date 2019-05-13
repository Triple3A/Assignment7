#ifndef COMMENT_H
#define COMMENT_H

class Comment
{
public:
	Comment(int _id, std::string _content);
	void add_reply(std::string);
private:
	int id;
	std::string content;
	std::vector<std::string> replies;
};
#endif