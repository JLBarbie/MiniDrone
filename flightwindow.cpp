#include "flightwindow.h"
#include "ui_flightwindow.h"

FlightWindow::FlightWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FlightWindow)
{
    ui->setupUi(this);
}

FlightWindow::~FlightWindow()
{
    delete ui;
}
