#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include <QTabWidget>

#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>

#include <QSystemTrayIcon>


#include "userinfopage.h"
#include "preferencespage.h"
#include "feedbackpage.h"

#include "scrollwindow.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void getFormData();

private slots:
    void updateScrollUsername();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);


private:

    QSystemTrayIcon *trayIcon;

    QTabWidget *tabWidget;
    UserInfoPage *userInfoPage;
    PreferencesPage *preferencesPage;
    FeedbackPage *feedbackPage;
    ScrollWindow *scrollWindow;

    void createTrayIcon();
};
#endif // MAINWINDOW_H
