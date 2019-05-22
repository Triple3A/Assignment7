#include "comment.hpp"

Comment::Comment(std::string _content, User* _owner)
	:content(_content), owner(_owner) {};

int Comment::get_id()
{
	return id;
}

void Comment::set_id(int _id)
{
	id = _id;
}

void Comment::add_reply(std::string content)
{
	replies.push_back(content);
}

User* Comment::get_owner()
{
	return owner;
}
