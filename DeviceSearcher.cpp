#include "DeviceSearcher.h"
#include "ChipFinder.h"

#include <qbluetoothaddress.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothlocaldevice.h>
#include <QMenu>
#include <QDebug>
#include <Client.h>
#include <Plotter.h>

//-------------------------------------------------------------------------------------------------------------//
// CONSTRUCTOR: DeviceSearcher
//
//-------------------------------------------------------------------------------------------------------------//
DeviceSearcher::DeviceSearcher(QWidget *parent)
:   QDialog(parent), localDevice(new QBluetoothLocalDevice),
    ui(new Ui_DeviceSearcher)
{
    ui->setupUi(this);

    searcher = new QBluetoothDeviceDiscoveryAgent();

    connect(ui->scan, SIGNAL(clicked()), this, SLOT(startScan()));

    connect(searcher, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SLOT(addDevice(QBluetoothDeviceInfo)));
    connect(searcher, SIGNAL(finished()), this, SLOT(scanFinished()));

    connect(ui->list, SIGNAL(itemActivated(QListWidgetItem*)),
            this, SLOT(itemActivated(QListWidgetItem*)));

    // add context menu for devices to be able to pair device
    ui->list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->list, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(displayPairingMenu(QPoint)));
    connect(localDevice, SIGNAL(pairingFinished(QBluetoothAddress,QBluetoothLocalDevice::Pairing))
        , this, SLOT(pairingDone(QBluetoothAddress,QBluetoothLocalDevice::Pairing)));

}


//-------------------------------------------------------------------------------------------------------------//
// DESTRUCTOR: ~DeviceSearcher
//
//-------------------------------------------------------------------------------------------------------------//
DeviceSearcher::~DeviceSearcher()
{
    delete searcher;
}


//-------------------------------------------------------------------------------------------------------------//
// METHOD: addDevice
//
//-------------------------------------------------------------------------------------------------------------//
void DeviceSearcher::addDevice(const QBluetoothDeviceInfo &info)
{
    // add bluetooth device to list
    QString label = QString("%1 %2").arg(info.address().toString()).arg(info.name());
    QList<QListWidgetItem *> items = ui->list->findItems(label, Qt::MatchExactly);


    if (items.empty()) {

        QListWidgetItem *item = new QListWidgetItem(label);

        // check if we are paired to the device
        QBluetoothLocalDevice::Pairing pairingStatus = localDevice->pairingStatus(info.address());


        // notify user we are paired by highlighting the foreground as green
        if (pairingStatus == QBluetoothLocalDevice::Paired || pairingStatus == QBluetoothLocalDevice::AuthorizedPaired )
            item->setForeground(QColor(Qt::green));
        else
            item->setForeground(QColor(Qt::black));

        ui->list->addItem(item);
    }

}


//-------------------------------------------------------------------------------------------------------------//
// METHOD: startScan
//
//-------------------------------------------------------------------------------------------------------------//
void DeviceSearcher::startScan()
{
    searcher->start();
    ui->scan->setEnabled(false);
}


//-------------------------------------------------------------------------------------------------------------//
// METHOD: scanFinished
//
//-------------------------------------------------------------------------------------------------------------//
void DeviceSearcher::scanFinished()
{
    ui->scan->setEnabled(true);
}


//-------------------------------------------------------------------------------------------------------------//
// METHOD: itemActivated
//
//-------------------------------------------------------------------------------------------------------------//
void DeviceSearcher::itemActivated(QListWidgetItem *item)
{
    QString text = item->text();

    int index = text.indexOf(' ');

    if (index == -1)
        return;

    QBluetoothAddress address(text.left(index));
    QString name(text.mid(index + 1));

    ChipFinder d(name, address);
    d.exec();
}

//-------------------------------------------------------------------------------------------------------------//
// METHOD: startNewConnection
//
//
//
//-------------------------------------------------------------------------------------------------------------//
void DeviceSearcher::startNewConnection(const QBluetoothServiceInfo& info)
{
    Client * newClient = new Client();
    Plotter p(info.serviceName());

    newClient->startClient(info);
    connect(newClient, SIGNAL(messageReceived(const QString &, const float)), &p, SLOT(addToPlot(const QString &, const float)));
    connect(&p, &QDialog::finished, [newClient]{newClient->stopClient(); delete newClient;});
    p.exec();
}


//-------------------------------------------------------------------------------------------------------------//
// METHOD: displayPairingMenu
//
//-------------------------------------------------------------------------------------------------------------//
void DeviceSearcher::displayPairingMenu(const QPoint &pos)
{
    if (ui->list->count() == 0)
        return;

    // create context menu to allow adding/removing pairing
    QMenu menu(this);
    QAction *pairAction = menu.addAction("Pair");
    QAction *removePairAction = menu.addAction("Remove Pairing");
    QAction *chosenAction = menu.exec(ui->list->viewport()->mapToGlobal(pos));
    QListWidgetItem *currentItem = ui->list->currentItem();

    QString text = currentItem->text();
    int index = text.indexOf(' ');
    if (index == -1)
        return;

    // determine if the user wants use to pair or remove pairing
    QBluetoothAddress address (text.left(index));
    if (chosenAction == pairAction) {
        localDevice->requestPairing(address, QBluetoothLocalDevice::Paired);
    } else if (chosenAction == removePairAction) {
        localDevice->requestPairing(address, QBluetoothLocalDevice::Unpaired);
    }
}


//-------------------------------------------------------------------------------------------------------------//
// METHOD: pairingDone
//
//-------------------------------------------------------------------------------------------------------------//
void DeviceSearcher::pairingDone(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing)
{
    QList<QListWidgetItem *> items = ui->list->findItems(address.toString(), Qt::MatchContains);

    // notify user whether or not we've successfully paired 
    if (pairing == QBluetoothLocalDevice::Paired || pairing == QBluetoothLocalDevice::AuthorizedPaired ) {
        for (int var = 0; var < items.count(); ++var) {
            QListWidgetItem *item = items.at(var);
            item->setForeground(QColor(Qt::green));
        }
    } else {
        for (int var = 0; var < items.count(); ++var) {
            QListWidgetItem *item = items.at(var);
            item->setForeground(QColor(Qt::red));
        }
    }
}
