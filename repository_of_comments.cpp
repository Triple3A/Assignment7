#include "repository_of_comments.hpp"

Repository_of_comments::Repository_of_comments()
{
	id_counter = 1;
}

void Repository_of_comments::add_comment(Comment* comment)
{
	comment->set_id(id_counter);
	id_counter++;
	comments.push_back(comment);
}