#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H
#include <string>

#include "ServerConfig.h"


class ConfigLoader {
public:
    static ServerConfig load(const std::string& filePath);
};



#endif //CONFIGLOADER_H
