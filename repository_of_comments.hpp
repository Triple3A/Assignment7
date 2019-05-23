#ifndef REPOSITORY_OF_COMMENTS_H
#define REPOSITORY_OF_COMMENTS_H

#include "comment.hpp"

class Repository_of_comments
{
public:
	Repository_of_comments();
	void add_comment(Comment*);
	Comment* search_comment(int comment_id);
	int get_position_of_element(int comment_id);
	void delete_comment(int comment_id);
	std::vector<Comment*> get_comments();
private:
	std::vector<Comment*> comments;
	int id_counter;
};
#endif