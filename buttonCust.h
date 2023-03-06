#ifndef BUTTONCUST_H
#define BUTTONCUST_H


#include <QApplication>
#include <QtGui>
#include <QPushButton>
#include <QDebug>

/*
 *Run button simple logic
 */
class ButtonCust : public QObject{
    Q_OBJECT
public:
    static bool pressed;

    /*
     * Returns true if was pressed and reverts
     */
    bool wasPressed() {
        if(pressed) {
            pressed = false;
            return true;
        }
        return false;
    }


public slots:


    static void insert()
    {
        pressed = true;
        qDebug() << "pressed";
    }
};



#endif // BUTTONCUST_H
