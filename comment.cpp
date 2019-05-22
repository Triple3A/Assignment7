#include "comment.hpp"

Comment::Comment(std::string _content)
	:content(_content) {};

int Comment::get_id()
{
	return id;
}

void Comment::set_id(int _id)
{
	id = _id;
}
