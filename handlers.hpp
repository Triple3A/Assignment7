#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "server/server.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "website_handler.hpp"

class RandomNumberHandler : public RequestHandler
{
public:
    Response *callback(Request *);
private:
    Website_handler* web;
};

class LoginHandler : public RequestHandler
{
public:
    LoginHandler(Website_handler* _web) :web(_web) {};
    Response *callback(Request *);
private:
    Website_handler* web;
};

class SignupHandler : public RequestHandler
{
public:
    SignupHandler(Website_handler* _web) :web(_web) {};
    Response *callback(Request *);
private:
    Website_handler* web;
};

class UploadHandler : public RequestHandler
{
public:
    Response *callback(Request *);
private:
    Website_handler* web;
};

class ColorHandler : public TemplateHandler
{
public:
  ColorHandler(std::string filePath);
  std::map<std::string, std::string> handle(Request *req);
};

#endif
