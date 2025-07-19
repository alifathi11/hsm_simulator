#ifndef FIELDMAPPER_H
#define FIELDMAPPER_H

#include <string>
#include <unordered_map>

class FieldMapper {
public:
    static int getFieldNumber(const std::string& fieldName);
};

#endif // FIELDMAPPER_H