#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <ostream>
#include <string>


class Utils {
public:
    static void showMessage(const std::string& message);
    static void showError(const std::string& errorMessage);
};



#endif //UTILS_H
