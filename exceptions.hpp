#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>
#include <string>

class Bad_request : public std::exception
{
public:
	virtual const char* what() const throw();
};

class Not_found : public std::exception
{
public:
	virtual const char* what() const throw();
};

class Permission_denied : public std::exception
{
public:
	virtual const char* what() const throw();
};
#endif