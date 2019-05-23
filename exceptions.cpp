#include "exceptions.hpp"

const char* Bad_request::what() const throw()
{
	return "Bad Request";
}

const char* Not_found::what() const throw()
{
	return "Not Found";
}

const char* Permission_denied::what() const throw()
{
	return "Permission Denied";
}