#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtcpSocket>
#include <QDebug>


namespace Ui {
class MainWindow;
}

/**
 * A classe MainWindow é usada para desenvolver a prática de programação orientada a objetos
 * por meio de um sistema de aquisição e supervisão de dados utilizando a comunicação TCP/IP.
 * Nessa classe, foi criado um produtor de dados que se conecta a uma máquina e envia dados a serem gravados.
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
   void putData();
   void timerEvent(QTimerEvent *e);
   void tcpConnect();
   void tcpDisconnect();
   void stop();
   void iniciaTimer();
private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    int tempo;
};

#endif // MAINWINDOW_H
