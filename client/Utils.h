#ifndef UTILS_H
#define UTILS_H
#include <string>


class Utils {
public:
    static std::string prompt(const std::string& message);
    static void showMessage(const std::string& message);
    static void printHex(const std::string& data);
};



#endif //UTILS_H
