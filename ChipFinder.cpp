#include "ChipFinder.h"

#include <qbluetoothaddress.h>
#include <qbluetoothservicediscoveryagent.h>
#include <qbluetoothserviceinfo.h>
#include <qbluetoothlocaldevice.h>
#include <qbluetoothuuid.h>
#include <iostream>
#include <QAction>
#include "Client.h"
#include "Plotter.h"

//-------------------------------------------------------------------------------------------------------------//
// CONSTRUCTOR: ChipFinder
//
//-------------------------------------------------------------------------------------------------------------//
ChipFinder::ChipFinder(const QString &name,
                                               const QBluetoothAddress &address, QWidget *parent)
:   QDialog(parent), ui(new Ui_ChipFinder)
{
    ui->setupUi(this);

    // Using default Bluetooth adapter
    QBluetoothLocalDevice localDevice;
    QBluetoothAddress adapterAddress = localDevice.address();


    // Start discovery
    std::cout << "device name: " << name.toStdString() << std::endl;
    chipDiscoverer = new QBluetoothServiceDiscoveryAgent(adapterAddress);

    chipDiscoverer->setRemoteAddress(address);

    setWindowTitle(name);

    connect(chipDiscoverer, SIGNAL(serviceDiscovered(QBluetoothServiceInfo)),
            this, SLOT(addChip(QBluetoothServiceInfo)));

    connect(ui->list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(tryToConnect(QListWidgetItem *)));
    chipDiscoverer->start();
}


//-------------------------------------------------------------------------------------------------------------//
// DESTRUCTOR: ~ChipFinder
//
//-------------------------------------------------------------------------------------------------------------//
ChipFinder::~ChipFinder()
{
    delete chipDiscoverer;
    delete ui;
}


//-------------------------------------------------------------------------------------------------------------//
// METHOD: addChip
//
//-------------------------------------------------------------------------------------------------------------//
void ChipFinder::addChip(const QBluetoothServiceInfo &info)
{
    std::cout << "service discovered: " << info.serviceName().toStdString() << std::endl;
    if (info.serviceName().isEmpty())
        return;

    // add discovered bluetooth device to list
    QString line = info.serviceName();
    if (!info.serviceDescription().isEmpty())
        line.append("\n\t" + info.serviceDescription());
    if (!info.serviceProvider().isEmpty())
        line.append("\n\t" + info.serviceProvider());

    ui->list->addItem(line);
}



//-------------------------------------------------------------------------------------------------------------//
// METHOD: tryToConnect
//
//-------------------------------------------------------------------------------------------------------------//
void ChipFinder::tryToConnect(QListWidgetItem* item)
{
    QString serviceName = item->text();
    QBluetoothServiceInfo desiredService, currentService;
    QList<QBluetoothServiceInfo> services = chipDiscoverer->discoveredServices();
    QList<QBluetoothServiceInfo>::iterator it;

    // find bluetooth device we want to connect to
    for(it = services.begin(); it < services.end(); it++)
    {
        currentService = *it;
        if(currentService.serviceName() == serviceName)
        {
            desiredService = currentService;
            break;
        }
    }

    // start up a client which will feed the graph with data
    if(!desiredService.serviceName().isEmpty())
    {
        Client * newClient = new Client();
        Plotter p(desiredService.serviceName());
        newClient->startClient(desiredService);
        connect(newClient, SIGNAL(messageReceived(const QString &, const float)), &p, SLOT(addToPlot(const QString &, const float)));
        connect(&p, &QDialog::finished, [newClient]{newClient->stopClient(); delete newClient;});
        p.exec();
    }
}
