#ifndef DEVICE_H
#define DEVICE_H

#include "ui_DeviceSearcher.h"

#include <qbluetoothlocaldevice.h>
#include<QBluetoothServiceInfo>
#include <QDialog>

QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceDiscoveryAgent)
QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceInfo)

QT_USE_NAMESPACE


//-------------------------------------------------------------------------------------------------------------//
// CLASS: DeviceSearcher
//
//-------------------------------------------------------------------------------------------------------------//
class DeviceSearcher : public QDialog
{
    Q_OBJECT

public:
    DeviceSearcher(QWidget *parent = nullptr);
    ~DeviceSearcher();

public slots:
    void addDevice(const QBluetoothDeviceInfo&);
    void displayPairingMenu(const QPoint &pos);
    void pairingDone(const QBluetoothAddress&, QBluetoothLocalDevice::Pairing);

private slots:
    void startScan();
    void scanFinished();
    void itemActivated(QListWidgetItem *item);
    void startNewConnection(const QBluetoothServiceInfo&);


private:
    QBluetoothDeviceDiscoveryAgent *searcher;
    QBluetoothLocalDevice *localDevice;
    Ui_DeviceSearcher *ui;
};

#endif
