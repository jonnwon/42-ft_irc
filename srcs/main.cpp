#include "Server.hpp"
#include "Util.hpp"
#include <cstdlib>

int main(int argc, char **argv)
{
  try
  {
    Check::checkArg(argc, argv);
    Server server(std::atoi(argv[1]), argv[2]);

    server.runServer();
    server.serverLoop();
  }
  catch (std::exception &e)
  {
    std::cout << "Error : " <<  e.what() << std::endl;
  }

  return 0;
}
