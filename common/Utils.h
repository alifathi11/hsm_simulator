#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <ostream>
#include <string>


class Utils {
public:
    static void showMessage(const std::string& message);
    static void showError(const std::string& errorMessage);
    static void printHEX(const std::string& data);
    static std::string prompt(const std::string& message);
};



#endif //UTILS_H
