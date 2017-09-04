#include "dronecontroller.h"

DroneController::DroneController() {}

DroneController::DroneController(Drone *drone)
{
    m_control = new QLowEnergyController(drone->address);
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

DroneController::~DroneController() {

}

void DroneController::storeCmd(QString handle, QString value, bool response)
{
    commands.append(Cmd{handle, value, response});
}


/*
 * A VOIR !!!!!!!!!
 *
 *
 * A VOIR !!!!!!!!!
 */
void DroneController::send()
{
//    if (stop_event.is_set() and self.drone.q.empty()){
//        self.drone.q.join();
//        self.gatt.sendeof();
//        self.gatt.terminate(True);
//        self.t_reader.stop();
//        self.t_reader.join();
//    } else {
//        cmd = self.drone.q.get();
//        if ("connect" in cmd.handle) {
//                self.gatt.sendline(cmd.handle);
//                self.drone.q.task_done();
//                continue;
//        }
//        if (not cmd.response) {
//            self.gatt.sendline(" ".join(["char-write-cmd", cmd.handle, cmd.value]));
//        } else {
//            self.gatt.sendline(" ".join(["char-write-req", cmd.handle, cmd.value]));
//            self.drone.q.task_done();
//        }
//    }
}

/*
 * Commands
 *
 */
bool DroneController::takeoff()
{
    qDebug("Taking off!");
//    self.send(self.send_ref, Base.FlatTrim)
//    time.sleep(0.5)
//    self.send(self.send_ref, Base.TakeOff)
    qDebug("Airborne!");
}

/*
 * SLOTS
 *
 */
void DroneController::serviceDiscovered(const QBluetoothUuid &gatt)
{
    if (gatt == QBluetoothUuid(QBluetoothUuid::HeartRate)) {
        qDebug("Heart Rate service discovered. Waiting for service scan to be done...");
    }
}

void DroneController::deviceConnected()
{
    qWarning() << "Remote device disconnected";
    m_control->discoverServices();
}

void DroneController::deviceDisconnected()
{
    qWarning() << "Remote device disconnected";
}

void DroneController::controllerError(QLowEnergyController::Error error)
{
    qWarning() << "Controller Error:" << error;
}
