#include "Client.h"
#include <iostream>

//-------------------------------------------------------------------------------------------------------------//
// METHOD: startClient
//
//
//
//-------------------------------------------------------------------------------------------------------------//
Client::Client(QObject *parent)
    :   QObject(parent)
{
}


//-------------------------------------------------------------------------------------------------------------//
// METHOD: startClient
//
//
//
//-------------------------------------------------------------------------------------------------------------//
Client::~Client()
{
    stopClient();
}

//-------------------------------------------------------------------------------------------------------------//
// METHOD: startClient
//
//
//
//-------------------------------------------------------------------------------------------------------------//
void Client::startClient(const QBluetoothServiceInfo &remoteService)
{
    if (socket)
        return;

    // Connect to service
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    qDebug() << "Create socket";
    socket->connectToService(remoteService);
    qDebug() << "ConnectToService done";

    connect(socket, &QBluetoothSocket::readyRead, this, &Client::readSocket);
    //connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, &QBluetoothSocket::disconnected, this, &Client::disconnected);


}


//-------------------------------------------------------------------------------------------------------------//
// METHOD: readSocket
//
//
//
//-------------------------------------------------------------------------------------------------------------//
void Client::readSocket()
{
    if (!socket)
        return;

    while (socket->canReadLine()) {
        float num = socket->readLine().toFloat();
        emit messageReceived(socket->peerName(),num);
    }
}


//-------------------------------------------------------------------------------------------------------------//
// METHOD: sendMessage
//
//
//
//-------------------------------------------------------------------------------------------------------------//
void Client::sendMessage(const QString &message)
{
    QByteArray text = message.toUtf8() + '\n';
    socket->write(text);
}


//-------------------------------------------------------------------------------------------------------------//
// METHOD: stopClient
//
//
//
//-------------------------------------------------------------------------------------------------------------//
void Client::stopClient()
{
    //sendMessage("FIN");
    delete socket;
    socket = nullptr;
}
