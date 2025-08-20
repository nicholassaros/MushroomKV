#include "Server.h"
#include <spdlog/spdlog.h>


int main() {

    Server myServer = Server(8000);

    myServer.Start();
    return 0;
}