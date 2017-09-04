#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLCDNumber>

/*!
 * \brief MainWindow::MainWindow
 * \param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    startDeviceDiscovery();
}

/*!
 * \brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * \brief MainWindow::startDeviceDiscovery
 */
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

/*!
 * \brief MainWindow::deviceDiscovered
 * \param device
 */
void MainWindow::deviceDiscovered(QBluetoothDeviceInfo device)
{
    qDebug() << "Found new device:" << device.name() << '(' << device.address().toString() << ')';
    devices.insert(device.name(), device.address());
    ui->ListMAC->addItem(device.name());
}

/*!
 * \brief MainWindow::keyPressEvent
 * \param event
 */
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
            controller->takeoff();
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

/*!
 * \brief MainWindow::keyReleaseEvent
 * \param event
 */
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

/*!
 * \brief MainWindow::on_tabWidget_currentChanged
 * \param index
 */
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

/*!
 * \brief MainWindow::leapLoop
 */
void MainWindow::leapLoop()
{
    coord pos;
    pos = leap->getPos();
}

/*!
 * \brief MainWindow::connectLeap
 */
void MainWindow::connectLeap()
{
    leap = new LeapDevice();
}

/*!
 * \brief MainWindow::on_pushButton_clicked
 */
void MainWindow::on_pushButton_clicked()
{
    startDeviceDiscovery();
}

/*!
 * \brief MainWindow::on_connectButton_clicked
 */
void MainWindow::on_connectButton_clicked()
{
    Drone *drone = new Drone(devices.value(ui->ListMAC->currentText()));
    controller = new DroneController(drone);
}

/*!
 * \brief MainWindow::on_horizontalSlider_valueChanged
 * \param value
 */
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->actionTime->display(value);
}

void MainWindow::on_addButton_clicked()
{
    QTreeWidgetItem *row = new QTreeWidgetItem();
    row->setText(0, ui->listAction->currentText());
    row->setText(1, QString::number(ui->horizontalSlider->value()));
    ui->parcours->addTopLevelItem(row);
}
