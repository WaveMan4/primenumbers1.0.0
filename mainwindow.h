//Name: Gilles Kepnang


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QStringListModel>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QList <qint64> numList;
    QStringListModel *model;
    QStringList numStrList;
    //Functions which initialize signal emission
    //and connect to appropriate slots
    void thread_init(qint64 start, qint64 limit);
    void signal_init(qint64 sigval, int type);
    void end_init(bool flag);

    void updateModelView(); //Function to update QListView
    void startEvents();     //Function to show initial GUI display before processing values

//Signals that are emitted within _init functions
signals:
    void updateDisplay(qint64 number);
    void updateProgress(qint64 number);
    void endThread(bool flag);
protected:
    void changeEvent(QEvent *e);

//Private variables
private:
    Ui::MainWindow *ui;
    qint64 to;
    qint64 from;
    qint64 count;
    qint64 totalcount;
    bool processing;

//Slots that correspond to actions
private slots:
    void on_stopButton_clicked();
    void on_actionStop_triggered();
    void on_startButton_clicked();
    void on_exitButton_clicked();
    void on_actionExit_triggered();
    void on_toLine_textChanged(QString );
    void on_fromLine_textChanged(QString );
    void on_actionStart_triggered();
//Slots used which update GUI objects appropriately
    void updateDisplaySlot(qint64);
    void updateProgressSlot(qint64);
    void threadEndSlot(bool);

};

#endif // MAINWINDOW_H
