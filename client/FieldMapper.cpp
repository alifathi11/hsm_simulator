#include "FieldMapper.h"

int FieldMapper::getFieldNumber(const std::string& fieldName) {
    static const std::unordered_map<std::string, int> fieldMap = {
        {"pan", 2},               // DE2 - Primary Account Number
        {"exp", 14},              // DE14 - Expiry Date (YYMM)
        {"cvv2", 48},             // DE48 - Additional Data (Private Use)
        {"pvv", 48},              // DE48 too (you could separate it by subfields)
        {"data", 48},             // General-purpose private data
        {"mac", 64}               // DE64 - Message Authentication Code
    };

    auto it = fieldMap.find(fieldName);
    if (it != fieldMap.end()) {
        return it->second;
    }

    return -1;  // Not found
}