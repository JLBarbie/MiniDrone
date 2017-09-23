#include "drone.h"

/*!
 * \brief Drone::Drone
 * Constructeur par defaut
 */
Drone::Drone()
{

}

/*!
 * \brief Drone::Drone
 * \param address
 */
Drone::Drone(QBluetoothAddress address)
{
    this->address = address;

    m_control = new QLowEnergyController(address);
    connect(m_control, SIGNAL(serviceDiscovered(QBluetoothUuid)),
            this, SLOT(serviceDiscovered(QBluetoothUuid)));
    connect(m_control, SIGNAL(discoveryFinished()),
            this, SLOT(serviceScanDone()));
    connect(m_control, SIGNAL(error(QLowEnergyController::Error)),
            this, SLOT(controllerError(QLowEnergyController::Error)));
    connect(m_control, SIGNAL(connected()),
            this, SLOT(deviceConnected()));
    connect(m_control, SIGNAL(disconnected()),
            this, SLOT(deviceDisconnected()));
    m_control->discoverServices();
    m_control->connectToDevice();
}

/*!
 * \brief Drone::~Drone
 */
Drone::~Drone() {

}

/*!
 * \brief Drone::getInfo
 * \return
 */
bool Drone::getInfo() {
    return true;
}

/*!
 * \brief Drone::storeCmd
 * \param handle
 * \param value
 * \param response
 */
void Drone::storeCmd(QString handle, QString value, bool response)
{
    commands.append(Cmd{handle, value, response});
}

/*!
 * \brief Drone::send
 *
 * Send command to drone
 */
void Drone::send(char currentValue)
{
    QByteArray value;
    value.append(char(0)); // Flags that specify the format of the value.
    value.append(char(currentValue)); // Actual value.

    QLowEnergyService *service	= m_control->createServiceObject(
                QBluetoothUuid::ClientCharacteristicConfiguration
                );

    //PreCondition: service details already discovered
    QLowEnergyCharacteristic batteryLevel = service->characteristic(
               QBluetoothUuid::BatteryLevel);
    if (!batteryLevel.isValid())
       return;

    QLowEnergyDescriptor notification = batteryLevel.descriptor(
               QBluetoothUuid::ClientCharacteristicConfiguration);
    if (!notification.isValid())
       return;

    service->writeDescriptor(notification, QByteArray::fromHex("0100"));
}

QString Drone::sendRef(Base type) {
    if (emerge) {
        unsigned int handle = '0x0043';
        seq_ref += 1;
    } else {
        unsigned int handle = '0x0046';
    }
    unsigned int value = '04' + ('%02x' % seq_ref);
    if (type == Base::FlatTrim) {
        value += '02000000';
    } else if (type == Base::TakeOff) {
        value += '02000100';
    } else if (type == Base::Land) {
        value += '02000300';
    } else if (emerge) {
        value += '02000400';
    } else {
        value += type;
    }
//    low_level(handle, value);
}

bool Drone::forward() {
    return true;
}

bool Drone::backward() {
    return true;
}

bool Drone::right() {
    return true;
}

bool Drone::left() {
    return true;
}

bool Drone::up() {
    return true;
}

bool Drone::down() {
    return true;
}

bool Drone::clock() {
    return true;
}

bool Drone::reverse_clock() {
    return true;
}

bool Drone::landing() {
    return true;
}

bool Drone::emergency() {
    return true;
}

/*!
 * \brief Drone::takeoff
 * \return
 *
 * Decollage
 */
bool Drone::takeoff()
{
    qDebug("Taking off!");
    sendRef(Base::TakeOff);
//    time.sleep(0.5)
//    self.send(self.send_ref, Base.TakeOff)
    qDebug("Airborne!");
    return true;
}

/**********
 * SLOTS
 **********/
void Drone::serviceDiscovered(const QBluetoothUuid &gatt)
{
    qDebug() << gatt;
    if (gatt == QBluetoothUuid(QBluetoothUuid::HeartRate)) {
        qDebug("Heart Rate service discovered. Waiting for service scan to be done...");
    }
}

void Drone::deviceConnected()
{
    qWarning() << "Remote device disconnected";
    m_control->discoverServices();
}

void Drone::deviceDisconnected()
{
    qWarning() << "Remote device disconnected";
}

void Drone::controllerError(QLowEnergyController::Error error)
{
    qWarning() << "Controller Error:" << error;
}
