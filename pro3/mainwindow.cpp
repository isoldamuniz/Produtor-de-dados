#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDateTime>
#include <QString>

/**
 * @brief MainWindow::MainWindow é a função construtora da janela e do soquete de rede.
 * Nela, os sinais e slots de cada objeto dessa classe são conectados.
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    connect(ui->pushButtonConnect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpConnect()));

    connect(ui->pushButtonDisconnect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpDisconnect()));

    connect(ui->horizontalSliderMin,
            SIGNAL(valueChanged(int)),
            ui->lcdNumberMin,
            SLOT(display(int)));

    connect(ui->horizontalSliderMax,
            SIGNAL(valueChanged(int)),
            ui->lcdNumberMax,
            SLOT(display(int)));

    connect(ui->horizontalSliderTime,
            SIGNAL(valueChanged(int)),
            ui->lcdNumberTime,
            SLOT(display(int)));

    connect(ui->pushButtonStart,
            SIGNAL(clicked(bool)),
            this,
            SLOT(iniciaTimer()));

    connect(ui->pushButtonStop,
            SIGNAL(clicked(bool)),
            this,
            SLOT(stop()));
}

/**
 * @brief MainWindow::tcpConnect é a função que faz a conexão a uma máquina
 * por meio de um IP informado na porta 1234.
 */

void MainWindow::tcpConnect(){
    socket->connectToHost(ui->lineEditIP->text(),1234);
    if(socket->waitForConnected(3000)){
      qDebug() << "Connected";
    }
    else{
      qDebug() << "Disconnected";
    }
}

/**
 * @brief MainWindow::tcpDisconnect é a função que encerra a conexão do IP informado.
 */

void MainWindow::tcpDisconnect(){
    socket->disconnectFromHost();
    if(socket->waitForDisconnected(3000) || socket->state() == QAbstractSocket::UnconnectedState){
        qDebug() << "Disconnected";
    }
}

/**
 * @brief MainWindow::timerEvent é a função manipuladora de eventos de tempo.
 * */

void MainWindow::timerEvent(QTimerEvent *e){
    putData();
}

/**
 * @brief MainWindow::iniciaTimer é a função que inicia o temporizador escolhido pelo usuário.
 * Esse temporizador é usado para enviar dados a cada timeout.
 */

void MainWindow::iniciaTimer(){
    tempo = startTimer(ui->lcdNumberTime->intValue()*1000);
}

/**
 * @brief MainWindow::putData é a função que gerencia os dados que são enviados.
 */

void MainWindow::putData(){
    QDateTime datetime;
      QString str;
      int upper = ui->lcdNumberMax->value();
      int lower = ui->lcdNumberMin->value();
      if(upper != 0 && lower != 0 && ui->lcdNumberTime->intValue() != 0){
          if(socket->state()== QAbstractSocket::ConnectedState){
             datetime = QDateTime::currentDateTime();
             str = "set "+
                     datetime.toString(Qt::ISODate)+
                     " "+
                     QString::number(qrand() % ((upper - lower)) + lower)
                     + "\n";

             ui->plainTextEditData->appendPlainText(str);
             qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
                if(socket->waitForBytesWritten(3000)){
                     qDebug() << "wrote";
                }
            }
      }
}

/**
 * @brief MainWindow::stop é a função que deleta o temporizador escolhido pelo usuário.
 */

void MainWindow::stop(){
    killTimer(tempo);
}

/**
 * @brief MainWindow::~MainWindow é a função destrutora da janela e do soquete de rede TCP
 */

MainWindow::~MainWindow()
{
    delete socket;
    delete ui;
}
