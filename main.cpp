#include <iostream>
#include <vector>
#include "my_server.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "handlers.hpp"

using namespace std;

int main(int argc, char **argv)
{
    MyServer* server = new MyServer(argc > 1 ? atoi(argv[1]) : 5000);
    Website_handler web(server);
    try
    {
        web.run();
    }
    catch (Server::Exception e)
    {
        cerr << e.getMessage() << endl;
    }
    catch(exception &ex)
    {
        cerr << ex.what() << endl;
    }
}
