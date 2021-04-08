#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QBluetoothServiceInfo>
#include <QBluetoothSocket>


//-------------------------------------------------------------------------------------------------------------//
// CONSTRUCTOR: Client
//
//-------------------------------------------------------------------------------------------------------------//
class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    void startClient(const QBluetoothServiceInfo &);
    void stopClient();

public slots:
    void sendMessage(const QString &);

signals:
    void messageReceived(const QString &, const float);
    void connected(const QString &);
    void disconnected();
    void socketErrorOccurred(const QString &);

private slots:
    void readSocket();


private:
    QBluetoothSocket *socket = nullptr;
};

#endif // CLIENT_H
