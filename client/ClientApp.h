#ifndef CLIENTAPP_H
#define CLIENTAPP_H
#include <string>


class ClientApp {

public:
    void run();

private:
    void showMenu();
    void handleOption(const std::string&);
    void showMessage(std::string);
    void endProgram();
};


#endif //CLIENTAPP_H
