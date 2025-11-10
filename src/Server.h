#ifndef SERVER_H
#define SERVER_H

class Server {
private:
    int port;

public:
    Server();
    void parseCommandLine(int argc, char** argv);
    void start();
};

#endif