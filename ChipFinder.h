#ifndef SERVICE_H
#define SERVICE_H

#include "ui_ChipFinder.h"

#include <QDialog>
#include <QMap>

QT_FORWARD_DECLARE_CLASS(QBluetoothAddress)
QT_FORWARD_DECLARE_CLASS(QBluetoothServiceInfo)
QT_FORWARD_DECLARE_CLASS(QBluetoothServiceDiscoveryAgent)

QT_USE_NAMESPACE

class ChipFinder : public QDialog
{
    Q_OBJECT

public:
    ChipFinder(const QString &name, const QBluetoothAddress &address, QWidget *parent = nullptr);
    ~ChipFinder();

public slots:
    void addChip(const QBluetoothServiceInfo&);
    void tryToConnect(QListWidgetItem*);

private:

    QBluetoothServiceDiscoveryAgent *chipDiscoverer;

    Ui_ChipFinder *ui;
};

#endif
