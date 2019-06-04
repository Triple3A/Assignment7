#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "server/server.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "website_handler.hpp"

class PublisherHomeHandler : public RequestHandler
{
public:
    PublisherHomeHandler(Website_handler* _web) :web(_web) {};
    Response *callback(Request *);
private:
    Website_handler* web;
};

class CustomerHomeHandler : public RequestHandler
{
public:
    CustomerHomeHandler(Website_handler* _web) :web(_web) {};
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

class PostFilmHandler : public RequestHandler
{
public:
    PostFilmHandler(Website_handler* _web) :web(_web) {};
    Response *callback(Request *);
private:
    Website_handler* web;
};

class DeleteFilmHandler : public RequestHandler
{
public:
    DeleteFilmHandler(Website_handler* _web) :web(_web) {};
    Response *callback(Request *);
private:
    Website_handler* web;
};

class ProfileHandler : public RequestHandler
{
public:
    ProfileHandler(Website_handler* _web) :web(_web) {};
    Response *callback(Request *);
private:
    Website_handler* web;
};

class LogoutHandler : public RequestHandler
{
public:
    LogoutHandler(Website_handler* _web) :web(_web) {};
    Response *callback(Request *);
private:
    Website_handler* web;
};

class DetailFilmHandler : public RequestHandler
{
public:
    DetailFilmHandler(Website_handler* _web) :web(_web) {};
    Response *callback(Request *);
private:
    Website_handler* web;
};

class BuyFilmHandler : public RequestHandler
{
public:
    BuyFilmHandler(Website_handler* _web) :web(_web) {};
    Response *callback(Request *);
private:
    Website_handler* web;
};

class RateFilmHandler : public RequestHandler
{
public:
    RateFilmHandler(Website_handler* _web) :web(_web) {};
    Response *callback(Request *);
private:
    Website_handler* web;
};

class CommentFilmHandler : public RequestHandler
{
public:
    CommentFilmHandler(Website_handler* _web) :web(_web) {};
    Response *callback(Request *);
private:
    Website_handler* web;
};



#endif
