#include "HSMClient.h"

#include <iostream>
#include "ISO8583Message.h"
#include "ISO8583Request.h"


// TODO: fix bugs in packing message
// TODO: check connection, send and receive messages


void HSMClient::verifyCVV2() {

    // get inputs
    ISO8583Request request = ISO8583InputManager::getVerifyCVV2Input();

    // build ISO8583 message
    ISO8583Message message = ISO8583Builder::buildVerifyCVV2(request);

    // get the message packed string
    std::string packedMessage = message.pack();

	// send message
	socket->sendMessage(packedMessage);

	// receive server response
	std::string response = socket->receiveMessage();

	// show server response
	HSMResponse::showResponse(response);
}

void HSMClient::verifyPVV() {

    // get inputs
    ISO8583Request request = ISO8583InputManager::getVerifyPVVInput();

    // build ISO8583 message
    ISO8583Message message = ISO8583Builder::buildVerifyPVV(request);

    // get the message packed string
    std::string packedMessage = message.pack();

	// send message
	socket->sendMessage(packedMessage);

	// receive server response
	std::string response = socket->receiveMessage();

	// show server response
	HSMResponse::showResponse(response);

}

void HSMClient::encryptData() {

    // get inputs
    ISO8583Request request = ISO8583InputManager::getEncryptDataInput();

    // build ISO8583 message
    ISO8583Message message = ISO8583Builder::buildEncryptُData(request);

    // get the message packed string
    std::string packedMessage = message.pack();

	// send message
	socket->sendMessage(packedMessage);

	// receive server response
	std::string response = socket->receiveMessage();

	// show server response
	HSMResponse::showResponse(response);

}

void HSMClient::generateMAC() {

    // get inputs
    ISO8583Request request = ISO8583InputManager::getGenerateMACInput();

    // build ISO8583 message
    ISO8583Message message = ISO8583Builder::buildGenerateMAC(request);

    // get the message packed string
    std::string packedMessage = message.pack();

	// send message
	socket->sendMessage(packedMessage);

	// receive server response
	std::string response = socket->receiveMessage();

	// show server response
	HSMResponse::showResponse(response);
}

void HSMClient::verifyMAC() {

    // get inputs
    ISO8583Request request = ISO8583InputManager::getVerifyMACInput();

    // build ISO8583 message
    ISO8583Message message = ISO8583Builder::buildVerifyMAC(request);

    // get the message packed string
    std::string packedMessage = message.pack();

	// send message
	socket->sendMessage(packedMessage);

	// receive server response
	std::string response = socket->receiveMessage();

	// show server response
	HSMResponse::showResponse(response);
}

void HSMClient::setSocket(HSMClientSocket* socket) {
	this->socket = socket;
}

