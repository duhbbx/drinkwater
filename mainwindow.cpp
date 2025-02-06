#include "mainwindow.h"

#include <QApplication>
#include <QScreen>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

#include <QMenu>

#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QApplication>


#include <QCloseEvent>

#include "customstyle.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {



    // 创建系统托盘图标
    createTrayIcon();




    // 创建 QTabWidget
    tabWidget = new QTabWidget(this);
    tabWidget->setTabPosition(QTabWidget::West);

    // 添加子页
    userInfoPage = new UserInfoPage(this);
    tabWidget->addTab(userInfoPage, "用户");

    // 连接 nameChanged 信号到 updateScrollUsername 槽函数
    connect(userInfoPage, &UserInfoPage::nameChanged, this, &MainWindow::updateScrollUsername);



    preferencesPage = new PreferencesPage(this);
    tabWidget->addTab(preferencesPage, "偏好");

    feedbackPage = new FeedbackPage(this);
    tabWidget->addTab(feedbackPage, "反馈");

    // 创建按钮用于获取表单数据
    QPushButton *submitButton = new QPushButton("Get Form Data", this);
    connect(submitButton, &QPushButton::clicked, this, &MainWindow::getFormData);

    // 创建一个按钮用于更新滚动显示的用户名
    QPushButton *updateButton = new QPushButton("Update Username", this);
    connect(updateButton, &QPushButton::clicked, this, &MainWindow::updateScrollUsername);

    // 设置布局
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(tabWidget);
    layout->addWidget(submitButton);
    layout->addWidget(updateButton);
    setCentralWidget(centralWidget);

    // 创建 ScrollWindow
    scrollWindow = new ScrollWindow();
    scrollWindow->show();



    // 连接信号和槽
    connect(userInfoPage, &UserInfoPage::scrollTimeReached, scrollWindow, &ScrollWindow::startScrollAnimation);

    // 设置自定义样式
    tabWidget->tabBar()->setStyle(new CustomTabStyle);

    // 设置窗口大小
    resize(800, 600);
    setFixedSize(size());

    // 禁用最大化按钮
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);

    // 获取屏幕的几何信息并居中显示
    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}



void MainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::DoubleClick) {
        // 双击托盘图标时显示窗口
        show();
        activateWindow();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon && trayIcon->isVisible()) {
        // 如果系统托盘支持，则隐藏窗口并显示托盘图标
        hide();
        event->ignore();
    } else {
        // 如果系统托盘不支持，则正常关闭程序
        event->accept();
    }
}

void MainWindow::createTrayIcon()
{
    // 创建系统托盘图标
    trayIcon = new QSystemTrayIcon(this);

    // 设置托盘图标
    trayIcon->setIcon(QIcon(":/icons/tray_icon.png")); // 请替换为你的图标路径

    // 创建托盘菜单
    QMenu *trayMenu = new QMenu(this);
    QAction *restoreAction = new QAction("Restore", this);
    QAction *quitAction = new QAction("Quit", this);

    connect(restoreAction, &QAction::triggered, this, &MainWindow::show);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);

    trayMenu->addAction(restoreAction);
    trayMenu->addAction(quitAction);

    trayIcon->setContextMenu(trayMenu);

    // 连接托盘图标激活信号
    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::onTrayIconActivated);

    // 显示托盘图标
    trayIcon->show();
}


void MainWindow::updateScrollUsername() {
    // 获取 UserInfoPage 中的用户名
    QString username = userInfoPage->getName();
    if (username.isEmpty()) {
        username = "Default User"; // 如果用户名为空，显示默认值
    }

    // 更新 ScrollWindow 的用户名
    scrollWindow->setUsername(username);
}

MainWindow::~MainWindow() {

     delete trayIcon;

}


void MainWindow::getFormData() {
    // 获取用户信息子页的数据
    qDebug() << "User Info:";
    qDebug() << "Name:" << userInfoPage->getName();
    qDebug() << "Date of Birth:" << userInfoPage->getDateOfBirth().toString("yyyy-MM-dd");
    qDebug() << "Subscribed:" << userInfoPage->isSubscribed();

    // 获取偏好设置子页的数据
    qDebug() << "Preferences:";
    qDebug() << "Theme:" << preferencesPage->getTheme();
    qDebug() << "Dark Mode:" << preferencesPage->isDarkModeEnabled();
    qDebug() << "Font Size:" << preferencesPage->getFontSize();

    // 获取反馈子页的数据
    qDebug() << "Feedback:";
    qDebug() << "Feedback:" << feedbackPage->getFeedback();
}
