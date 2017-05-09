#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    startDeviceDiscovery();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startDeviceDiscovery()
{

    // Create a discovery agent and connect to its signals
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));

    // Start a discovery
    discoveryAgent->start();

    //...
}

void MainWindow::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    qDebug() << "Found new device:" << device.name() << '(' << device.address().toString() << ')';
    ui->ListMAC->addItem(device.address().toString());
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    switch (key) {
        case Qt::Key_W:
            ui->forward->setEnabled(true);
            //drone.move_fw()
            break;
        case Qt::Key_S:
            ui->backward->setEnabled(true);
            //drone->move_bw()
            break;
        case Qt::Key_A:
            ui->left->setEnabled(true);
            //drone.move_left()
            break;
        case Qt::Key_D:
            ui->right->setEnabled(true);
            //drone.move_right()
            break;
        case Qt::Key_Up:
            ui->up->setEnabled(true);
            //self.drone.ascend()
            break;
        case Qt::Key_Down:
            ui->down->setEnabled(true);
            //self.drone.descend()
            break;
        case Qt::Key_Right:
            ui->clock->setEnabled(true);
            //self.drone.turn_right()
            break;
        case Qt::Key_Left:
            ui->rev_clock->setEnabled(true);
            //self.drone.turn_left()
            break;
        case Qt::Key_E:
            ui->landing->setEnabled(true);
            //self.drone.land()
            qDebug("Landing");
            break;
        case Qt::Key_Escape:
            //drone.emergency()
            qDebug("Emergency");
            break;
        case Qt::Key_Space:
            //self.drone.takeoff()
            qDebug("Take Off");
            break;
        case Qt::Key_O:
            break;
            //self.drone.cutout(not config['cutout'])
        case Qt::Key_I:
            break;
            //self.drone.wheels(not config['wheels'])

        default:
            break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    int key = event->key();
    switch (key) {
        case Qt::Key_W:
            ui->forward->setEnabled(false);
        case Qt::Key_S:
            ui->backward->setEnabled(false);
        case Qt::Key_A:
            ui->left->setEnabled(false);
        case Qt::Key_D:
            ui->right->setEnabled(false);
        case Qt::Key_Up:
            ui->up->setEnabled(false);
        case Qt::Key_Down:
            ui->down->setEnabled(false);
        case Qt::Key_Right:
            ui->clock->setEnabled(false);
        case Qt::Key_Left:
            ui->rev_clock->setEnabled(false);
        default:
            break;
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch (index) {
    case 0:

        break;
    case 2:
        qDebug("Leap Motion");
        connectLeap();
        leapLoop();
        break;
    default:
        break;
    }
}


void MainWindow::leapLoop()
{
    coord pos;
    pos = leap->getPos();
}

void MainWindow::connectLeap()
{
    leap = new LeapDevice();
}
