#include "HSMClient.h"

#include <iostream>
#include <ostream>

#include "ISO8583InputManager.h"
#include "ISO8583Message.h"
#include "ISO8583Request.h"
#include "Utils.h"


void HSMClient::verifyCVV2() {

    // get inputs
    ISO8583Request request = inputManager.getVerifyCVV2Input();

    // build ISO8583 message
    ISO8583Message message = builder.buildVerifyCVV2(request);

    // get the message packed string
    // TODO: fix bugs in packing message
    std::string packedMessage = message.pack();

    // send to HSM server
	if (!socket.isConnected()) {
		socket.connectToServer();
	}

	socket.sendMessage(packedMessage);

	// receive server response
	std::string response = socket.receiveMessage();

	// show server response
	hsmResponse.showResponse(response);
}

void HSMClient::verifyPVV() {

    // get inputs
    ISO8583Request request = inputManager.getVerifyPVVInput();

    // build ISO8583 message
    ISO8583Message message = builder.buildVerifyPVV(request);

    // get the message packed string
    // TODO: fix bugs in packing message
    std::string packedMessage = message.pack();

    // send to HSM server
	if (!socket.isConnected()) {
		socket.connectToServer();
	}

	socket.sendMessage(packedMessage);

	// receive server response
	std::string response = socket.receiveMessage();

	// show server response
	hsmResponse.showResponse(response);

}

void HSMClient::encryptData() {

    // get inputs
    ISO8583Request request = inputManager.getEncryptDataInput();

    // build ISO8583 message
    ISO8583Message message = builder.buildEncryptُData(request);

    // get the message packed string
    // TODO: fix bugs in packing message
    std::string packedMessage = message.pack();

    // send to HSM server
	if (!socket.isConnected()) {
		socket.connectToServer();
	}

	socket.sendMessage(packedMessage);

	// receive server response
	std::string response = socket.receiveMessage();

	// show server response
	hsmResponse.showResponse(response);

}

void HSMClient::generateMAC() {

    // get inputs
    ISO8583Request request = inputManager.getGenerateMACInput();

    // build ISO8583 message
    ISO8583Message message = builder.buildGenerateMAC(request);

    // get the message packed string
    // TODO: fix bugs in packing message
    std::string packedMessage = message.pack();

    // send to HSM server
	if (!socket.isConnected()) {
		socket.connectToServer();
	}

	socket.sendMessage(packedMessage);

	// receive server response
	std::string response = socket.receiveMessage();

	// show server response
	hsmResponse.showResponse(response);
}

void HSMClient::verifyMAC() {

    // get inputs
    ISO8583Request request = inputManager.getVerifyMACInput();

    // build ISO8583 message
    ISO8583Message message = builder.buildVerifyMAC(request);

    // get the message packed string
    // TODO: fix bugs in packing message
    std::string packedMessage = message.pack();

    // send to HSM server
	if (!socket.isConnected()) {
		socket.connectToServer();
	}

	socket.sendMessage(packedMessage);

	// receive server response
	std::string response = socket.receiveMessage();

	// show server response
	hsmResponse.showResponse(response);
}
