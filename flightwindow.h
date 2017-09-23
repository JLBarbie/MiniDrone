#ifndef FLIGHTWINDOW_H
#define FLIGHTWINDOW_H

#include <QMainWindow>

namespace Ui {
class FlightWindow;
}

class FlightWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FlightWindow(QWidget *parent = 0);
    ~FlightWindow();

private:
    Ui::FlightWindow *ui;
};

#endif // FLIGHTWINDOW_H
