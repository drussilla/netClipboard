#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QtGui/QMainWindow>
#include <QSystemTrayIcon>
#include <QDialog>
#include <QEvent>
#include <QMenu>
#include <QCloseEvent>

#include "server.h"
#include "client.h"
#include "aboutdialog.h"
namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    Server *server;
    Client *client;
    AboutDialog *adialog;
    bool is_server_start;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    void createActions();
    void createTrayIcon();

public slots:
    void Start_Stop_Server();
    void ClipboardChange();
    void SetClient();
};

#endif // MAINWINDOW_H
