//Name: Gilles Kepnang

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <errno.h>
#include <cmath>
void *start_thread(void *args); //Thread function
void exit_thread(void *args);   //Cancel function

//Struct which passes class object pointer and other necessary variables
struct thread_args
{
    qint64 start;
    qint64 limit;
    MainWindow *ptr;
    qint64 sumofNums;
};
thread_args t_args; //instance of struct
pthread_t tid; /* the thread identifier */


//THREAD FUNCTION FOR GENERATING PRIME NUMBERS
void* start_thread(void *arg)
{
    struct thread_args *struct_ptr = (struct thread_args*) arg;
    QList <qint64> listOfNonPrimes;

    /* set the cancellation parameters --
      - Enable thread cancellation
      - Defer the action of the cancellation
    */
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    pthread_cleanup_push(exit_thread, arg);
    while (1)
    {
        //Generate non-prime numbers (or composites)
        qint64 i, j, limit(struct_ptr->limit), start(struct_ptr->start);
        qint64 sqrt_of_limit = sqrt(limit);
        for (i = 2; i <= sqrt_of_limit; i++)    //Use square root as upper limit to lower iterations...
        {
            for (j = 2; j <= limit/i; j++)
            {
                if (start <= (i*j) && limit >= (i*j) && !listOfNonPrimes.contains(i*j))
                {
                    listOfNonPrimes.append(i*j);
                    pthread_testcancel();
                }
                pthread_testcancel();
            }
        }

        //Iterate through all numbers in defined interval and display the
        //non primes (a.k.a numbers that are not in the list)
        //Update progress as well after every iteration
        qint64 progress = 0;
        struct_ptr->sumofNums = 0;
        for(i=start; i<=limit; i++)
        {
            if (!listOfNonPrimes.contains(i))
            {
                struct_ptr->ptr->signal_init(i,1);
                struct_ptr->sumofNums++;
                pthread_testcancel();
            }
            progress++;
            struct_ptr->ptr->signal_init(progress,2);
            pthread_testcancel();
        }
        struct_ptr->ptr->end_init(true);
        break;
    }
    pthread_cleanup_pop(0);
    pthread_exit(0);
}

//FUNCTION FOR CANCELLING THREAD (Clear all variables within the struct
//                                and deassign object pointer)
void exit_thread(void *arg)
{
    struct thread_args *struct_ptr = (struct thread_args*) arg;
    struct_ptr->sumofNums = 0;
    struct_ptr->start = 0;  struct_ptr->limit = 0;
    struct_ptr->ptr->end_init(false);
    struct_ptr->ptr = NULL;
}

////////////////////////////////////////////////////////////////////
//////////////////////MAINWINDOW MAIN FUNCTIONS/////////////////////
//Default constructor which initializes all values
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusLine->setText("Waiting for answer...");
    ui->actionStop->setEnabled(false);
    ui->stopButton->setEnabled(false);
    processing = false;
    to = 0;    from = 0;
    count = 0;  totalcount = 0;
    numList.clear();
    numStrList.clear();
    //Connect appropriate signals and slots
    connect(this,SIGNAL(updateDisplay(qint64)),this,SLOT(updateDisplaySlot(qint64)));
    connect(this,SIGNAL(updateProgress(qint64)),this,SLOT(updateProgressSlot(qint64)));
    connect(this, SIGNAL(endThread(bool)), this, SLOT(threadEndSlot(bool)));

    //Set QListView Model
    model = new QStringListModel(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

//FUNCTION TO INITIALIZE THREAD FUNCTION AND GENERATING
//OF PRIME NUMBERS
void MainWindow::thread_init(qint64 start, qint64 limit)
{
    numStrList.clear();
    updateModelView();
    processing = true;
    count = 0;
    ui->statusLine->setText("Waiting for answer...");
    /* create the thread */
    t_args.ptr = this;
    t_args.start = start;   t_args.limit = limit;
    pthread_create(&tid,NULL,start_thread,(void*) &t_args);

    //Set minimum and maximum for the progress bar
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(limit-start);
}

//FUNCTIONS FOR INITIALIZING SIGNAL EMISSION
void MainWindow::signal_init(qint64 sigval, int type)
{
    //Emit signals to update display and update progress bar
    if (type == 1)    emit updateDisplay(sigval);
    if (type == 2)    emit updateProgress(sigval);
}

void MainWindow::end_init(bool flag)
{   //Emit signal to let object know that thread has ended
    emit endThread(flag);
}

//Function for updating the QListView values
void MainWindow::updateModelView()
{
    model->setStringList(numStrList);
    ui->numberList->setModel(model);
}
//Function all initial events before prime numbers are generated
void MainWindow::startEvents()
{
    //updates GUI on when it is ready to process data
    ui->statusLine->setText("Waiting for answer...");
    ui->progressBar->setValue(0);
    ui->counterLine->setText(" ");
    ui->actionStart->setEnabled(false); ui->actionStop->setEnabled(true);
    ui->startButton->setEnabled(false); ui->stopButton->setEnabled(true);
    thread_init(from,to);
}

//////////////////MAINWINDOW SLOTS//////////////////////////////////////

//////////Slots for starting to generate prime numbers///////////////////
void MainWindow::on_actionStart_triggered()
{
    if (!processing && (from < to)) startEvents();
}
void MainWindow::on_startButton_clicked()
{
    if (!processing && (from < to)) startEvents();
}

//////////////////Slots for changing text on each line///////////////////
void MainWindow::on_fromLine_textChanged(QString fromStr)
{
    bool ok;
    fromStr.toLongLong(&ok, 10);
    //Assigns number values for valid values and when ready to process data
    if (ok && !processing) from = fromStr.toLongLong(&ok, 10);
}

void MainWindow::on_toLine_textChanged(QString toStr)
{
    bool ok;
    toStr.toLongLong(&ok, 10);
    //Assigns number values for valid values and when ready to process data
    if (ok && !processing) to = toStr.toLongLong(&ok, 10);
}

//////////////////Slots for exiting the application//////////////////////
void MainWindow::on_actionExit_triggered()
{
    exit(1);
}
void MainWindow::on_exitButton_clicked()
{
    exit(1);
}

///////////////Slots for stop generating prime numbers///////////////////
void MainWindow::on_actionStop_triggered()
{
    qDebug() << "Process for generating prime numbers has been cancelled...";
    pthread_cancel(tid);
}
void MainWindow::on_stopButton_clicked()
{
    qDebug() << "Process for generating prime numbers has been cancelled...";
    pthread_cancel(tid);
}

//Update StringList model
void MainWindow::updateDisplaySlot(qint64 curNum)
{
    count++;    totalcount++;
    ui->counterLine->setText(QString::number(count,10));
    numStrList.append(QString::number(curNum,10));
    updateModelView();
    pthread_testcancel();
}

//Update Progress Bar and StringList model
void MainWindow::updateProgressSlot(qint64 curNum)
{
    ui->progressBar->setValue(curNum);
    pthread_testcancel();
}

//Updates GUI at the end of the thread
void MainWindow::threadEndSlot(bool flag)
{
    //Flag variable determines whether thread was completed and
    //and all prime numbers were generated

    if (flag)   //Successful thread completion
    {
        ui->statusLine->setText(QString::number(totalcount,10));
    }
    else    //Incomplete thread
    {
        numStrList.clear();
        updateModelView();
        ui->counterLine->setText(" ");
        ui->progressBar->setValue(0);
    }
    processing = false;
    ui->actionStart->setEnabled(true); ui->actionStop->setEnabled(false);
    ui->startButton->setEnabled(true); ui->stopButton->setEnabled(false);
}
////////////////////////////////////////////////////////////////////////////
