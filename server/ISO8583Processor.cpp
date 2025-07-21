#include "ISO8583Processor.h"


ISO8583Processor::ISO8583Processor(const std::string &messageStr) : messageStr(messageStr) {}

std::string ISO8583Processor::process() {
    ISO8583Message iso8583Message = buildISO8583Message();
    std::string result = handleISO8583Message(iso8583Message);
    return result;
}

ISO8583Message ISO8583Processor::buildISO8583Message() {
    ISO8583Message iso8583Message;
    // TODO: build ISO8583Message out of string message
    return iso8583Message;
}

std::string ISO8583Processor::handleISO8583Message(const ISO8583Message& iso8583Message) {
    // TODO: build ISO8583 response
    std::string result = "OK";
    return result;
}
