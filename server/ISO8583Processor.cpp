#include "ISO8583Processor.h"

#include "HSMCommandHandler.h"
#include "Utils.h"


ISO8583Processor::ISO8583Processor(const std::string &rawMessage) : rawMessage(rawMessage) {}

std::string ISO8583Processor::process() {
    ISO8583Message iso8583Message = buildISO8583Message();
    std::string result = handleISO8583Message(iso8583Message);
    return result;
}

ISO8583Message ISO8583Processor::buildISO8583Message() {
    // create ISO8583 message
    ISO8583Message iso8583Message;
    // unpack raw message into ISO8583 message fields
    iso8583Message.unpack(rawMessage);
    // return ISO8583 message
    return iso8583Message;
}

std::string ISO8583Processor::handleISO8583Message(ISO8583Message iso8583Message) {
    std::string processingCode = iso8583Message.getField(3);

    if (processingCode == "900000") return HSMCommandHandler::handleVerifyCVV2(iso8583Message);
    if (processingCode == "920000") return HSMCommandHandler::handleVerifyPVV(iso8583Message);
    if (processingCode == "950000") return HSMCommandHandler::handleEncryptData(iso8583Message);
    if (processingCode == "980000") return HSMCommandHandler::handleGenerateMAC(iso8583Message);
    if (processingCode == "981000") return HSMCommandHandler::handleVerifyMAC(iso8583Message);

    Utils::showError("invalid processing code: " + processingCode);
    exit(1);
}
