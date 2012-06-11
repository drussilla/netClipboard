#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    adialog = new AboutDialog;
    server = new Server;
    client = new Client;
    is_server_start = false;

    createActions();
    createTrayIcon();

    setWindowIcon(QIcon(":/img/net"));
    connect(ui->pushButton, SIGNAL(clicked()), SLOT(Start_Stop_Server()));
    connect(ui->pushButton_2, SIGNAL(clicked()), SLOT(SetClient()));
    connect(ui->pushButton_3, SIGNAL(clicked()), SLOT(close()));
    connect(ui->pushButton_4, SIGNAL(clicked()), adialog, SLOT(show()));
    connect(QApplication::clipboard(), SIGNAL(dataChanged()), SLOT(ClipboardChange()));

    trayIcon->show();

}

void MainWindow::Start_Stop_Server()
{
    if(!is_server_start)
    {
        if(server->start(ui->spinBox->value()))
        {
            is_server_start = true;
            ui->pushButton->setIcon(QIcon(":/img/ok"));
        }
    }
    else
    {
        if(server->stop())
        {
            ui->pushButton->setIcon(QIcon(":/img/cancel"));
            is_server_start = false;
        }
    }

}
void MainWindow::SetClient()
{
    if(!client->isSend())
    {
        client->setServer(ui->lineEdit->text(), ui->spinBox_2->value());
        client->setSend(true);
        ui->pushButton_2->setIcon(QIcon(":/img/ok"));
    }
    else
    {
        client->setSend(false);
        ui->pushButton_2->setIcon(QIcon(":/img/cancel"));
    }
}
void MainWindow::ClipboardChange()
{
    if(client->isSend() && !server->is_Read())
    {
        client->sendData();
    }
    else
    {
        server->setis_Read(false);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete server;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        QMessageBox::information(this, tr("Systray"),
                                 tr("The program will keep running in the "
                                    "system tray. To terminate the program, "
                                    "choose <b>Quit</b> in the context menu "
                                    "of the system tray entry."));
        hide();
        event->ignore();
    }
}

void MainWindow::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/img/net"));
    trayIcon->setContextMenu(trayIconMenu);
}
