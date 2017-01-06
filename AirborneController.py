from PySide import QtCore,QtGui
from PySide import QtUiTools
import minidrone
import dronedict
import threading
import os, sys
import time

S_DISCONNECTED = 0
S_CONNECTING = 1
S_CONNECTED = 2

DRONEMAC = 'E0:14:D6:A9:3D:28'
CB_MSG = 0
CB_BATTERY = 1
CB_DATA_UPDATE = 2
CB_SPEED = 3
CB_STATE = 4

def logger(type, msg):
    if type == 0:
        print("[\033[34mINFO\033[0m] " +msg)
    elif type == 1:
        print("[\033[36mBATT\033[0m] " +msg)
    elif type == 2:
        print("[\033[35mDATA\033[0m] " +str(msg))
    elif type == 3:
        print("[\033[34mSPEED\033[0m] " +msg)
    elif type == 4:
        print("[\033[32mSTAT\033[0m] " +msg)
    elif type == 5:
        print("[\033[31mERROR\033[0m] " +msg)


def load_ui(file_name, where=None):
    """
    Loads a .UI file into the corresponding Qt Python object
    :param file_name: UI file path
    :param where: Use this parameter to load the UI into an existing class (i.e. to override methods)
    :return: loaded UI
    """
    # Create a QtLoader
    loader = QtUiTools.QUiLoader()

    # Open the UI file
    ui_file = QtCore.QFile(file_name)
    ui_file.open(QtCore.QFile.ReadOnly)

    # Load the contents of the file
    ui = loader.load(ui_file, where)

    # Close the file
    ui_file.close()

    return ui

class AirborneCreator(QtGui.QWidget):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        self.mutex = threading.Lock()
        self.setupUI()
        self.setWindowTitle('Airborne Controller')


    def setupUI(self):
        # Load UI and set it as main layout
        ui_file_path = os.path.join(os.path.realpath(os.path.dirname(__file__)), 'airborne.ui')
        main_widget = load_ui(ui_file_path, self)

        layout = QtGui.QVBoxLayout()
        layout.addWidget(main_widget)
        self.setLayout(layout)
        self.initCourse()

        self.logo = self.findChild(QtGui.QGraphicsView, 'logo');
        self.scene = QtGui.QGraphicsScene()
        self.logo.setScene(self.scene)
        self.img = QtGui.QImage('./ressources/logo.png')
        self.item = QtGui.QGraphicsPixmapItem(QtGui.QPixmap.fromImage(self.img));
        self.scene.addItem(self.item);

        # Get a reference to all required widgets
        self.connectButton = self.findChild(QtGui.QToolButton, 'connectButton')
        self.macAddressInput = self.findChild(QtGui.QLineEdit, 'macAddress')

        self.forwardButton = self.findChild(QtGui.QPushButton, 'forward')
        self.backwardButton = self.findChild(QtGui.QPushButton, 'backward')
        self.rightButton = self.findChild(QtGui.QPushButton, 'right')
        self.leftButton = self.findChild(QtGui.QPushButton, 'left')

        self.landingButton = self.findChild(QtGui.QPushButton, 'landing')
        # self.lengthSpinBox = self.findChild(QtGui.QDoubleSpinBox, 'lengthSpinBox')
        # self.widthSpinBox = self.findChild(QtGui.QDoubleSpinBox, 'widthSpinBox')
        # self.lineWidthSpinBox = self.findChild(QtGui.QDoubleSpinBox, 'lineWidthSpinBox')
        # self.cornersSpinBox = self.findChild(QtGui.QDoubleSpinBox, 'cornersSpinBox')
        # self.cornersCheckBox = self.findChild(QtGui.QCheckBox, 'cornersCheckBox')
        # self.xSpinBox = self.findChild(QtGui.QDoubleSpinBox, 'xSpinBox')
        # self.ySpinBox = self.findChild(QtGui.QDoubleSpinBox, 'ySpinBox')

        # Configure widget ranges:
        # max_float = sys.float_info.max
        # self.lengthSpinBox.setMinimum(0)
        # self.lengthSpinBox.setMaximum(max_float)
        # self.widthSpinBox.setMinimum(0)
        # self.widthSpinBox.setMaximum(max_float)
        # self.lineWidthSpinBox.setMinimum(0)
        # self.lineWidthSpinBox.setMaximum(max_float)
        # self.lineWidthSpinBox.setSingleStep(0.1)
        # self.cornersSpinBox.setMinimum(0)
        # self.cornersSpinBox.setMaximum(max_float)
        # self.xSpinBox.setMinimum(-max_float)
        # self.xSpinBox.setMaximum(max_float)
        # self.ySpinBox.setMinimum(-max_float)
        # self.ySpinBox.setMaximum(max_float)

        # Connect slots/callbacks and signals
        self.connectButton.clicked.connect(self.initializationDrone)
        # self.cornersSpinBox.setEnabled(False)
        # self.cornersCheckBox.stateChanged.connect(self.onCornersCheckBoxChangedState)

    def initCourse(self):
        self.courseAction = self.findChild(QtGui.QComboBox, 'courseAction')
        self.courseAction.addItem("Avant")
        self.courseAction.addItem("Arriere")
        self.courseAction.addItem("Gauche")
        self.courseAction.addItem("Droite")
        self.courseAction.addItem("Rotation")
        self.courseAction.addItem("R-Rotation")

    # def resetValues(self):
        # self.lengthSpinBox.setValue(50)
        # self.widthSpinBox.setValue(50)
        # self.lineWidthSpinBox.setValue(0.2)
        # self.cornersCheckBox.setChecked(False)
        # self.cornersSpinBox.setValue(5)
        # self.xSpinBox.setValue(0)
        # self.ySpinBox.setValue(0)

    def onCornersCheckBoxChangedState(self, checked):
        self.cornersSpinBox.setEnabled(bool(checked))

    def initializationDrone(self):
        self.droneMAC = self.macAddressInput.text()
        self.drone = minidrone.MiniDrone(mac=self.droneMAC, callback=logger)
        state = S_CONNECTING
        self.drone.connect()
        time.sleep(2)
        dronedict.process_notification(self.drone, dronedict.P_NAME)
        dronedict.process_notification(self.drone, dronedict.P_FW_HW)
        state = S_CONNECTED
        print(state)
        print ("Drone found and pairing: ")
        print ("MAC Address: %s" % self.droneMAC)

    def keyPressEvent(self, event):
        key = event.key()
        if key == QtCore.Qt.Key_W:
            self.forwardButton.setEnabled(True)
            self.drone.move_fw()
        elif key == QtCore.Qt.Key_S:
            self.backButton.setEnabled(True)
            self.drone.move_bw()
        elif key == QtCore.Qt.Key_A:
            self.leftButton.setEnabled(True)
            self.drone.move_left()
        elif key == QtCore.Qt.Key_D:
            self.rightButton.setEnabled(True)
            self.drone.move_right()

        elif key == QtCore.Qt.Key_Up:
            self.drone.ascend()
        elif key == QtCore.Qt.Key_Down:
            self.drone.descend()
        elif key == QtCore.Qt.Key_Right:
            self.drone.turn_right()
        elif key == QtCore.Qt.Key_Left:
            self.drone.turn_left()

        elif key == QtCore.Qt.Key_E:
            self.landingButton.setEnabled(True)
            self.drone.land()
            print("Landing")
        elif key == QtCore.Qt.Key_Escape:
            self.drone.emergency()
            print("Emergency")
        elif key == QtCore.Qt.Key_Space:
            self.drone.takeoff()
            print("Take Off")

        elif key == QtCore.Qt.Key_O:
            self.drone.cutout(not config['cutout'])
        elif key == QtCore.Qt.Key_I:
            self.drone.wheels(not config['wheels'])
        # elif event == ord('+'):
        #     drone.incr_speed()
        # elif event == ord('-'):
        #     drone.decr_speed()
        # elif event == ord('x'):
        #     drone.disconnect()

    def keyReleaseEvent(self, event):
        key = event.key()
        if key == QtCore.Qt.Key_W:
            self.forwardButton.setEnabled(False)
        elif key == QtCore.Qt.Key_S:
            self.backButton.setEnabled(False)
        elif key == QtCore.Qt.Key_A:
            self.leftButton.setEnabled(False)
        elif key == QtCore.Qt.Key_D:
            self.rightButton.setEnabled(False)

        elif key == QtCore.Qt.Key_Up:
            self.drone.ascend()
        elif key == QtCore.Qt.Key_Down:
            self.drone.descend()
        elif key == QtCore.Qt.Key_Right:
            self.drone.turn_right()
        elif key == QtCore.Qt.Key_Left:
            self.drone.turn_left()

    def __exit__(self, exc_type, exc_value, traceback):
        self.drone.die()
        self.package_obj.cleanup()

if __name__ == '__main__':
    global state, message, config, speed, battery
    # Init basic configuration
    state = S_DISCONNECTED
    message = speed = battery = ''
    config = dict()

    # Create Qt app
    app = QtGui.QApplication(sys.argv)

    # Create the widget and show it
    gui = AirborneCreator()
    gui.show()

    # Run the app
    sys.exit(app.exec_())
