#include "scrollwindow.h"
#include <QScreen>
#include <QGuiApplication>
#include <QFontMetrics>

ScrollWindow::ScrollWindow(QWidget *parent)
    : QWidget(parent), scrollCount(0) { // 初始化滚动次数为 0
    // 设置窗口无边框、透明背景且置顶
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::ToolTip | Qt::WindowTransparentForInput);
    setAttribute(Qt::WA_TranslucentBackground);

    // 禁用焦点
    setFocusPolicy(Qt::NoFocus);

    // 获取屏幕尺寸并设置窗口为全屏
    QScreen *screen = QGuiApplication::primaryScreen();
    setGeometry(screen->geometry());

    // 创建 QLabel 用于显示用户名
    usernameLabel = new QLabel(this);
    usernameLabel->setAlignment(Qt::AlignCenter);
    usernameLabel->setStyleSheet("font-size: 48px; color: red; background-color: rgba(0, 0, 0, 0);"); // 完全透明背景
    usernameLabel->hide(); // 初始隐藏

    usernameLabel->setText("这里是提示语句...................");

    // 创建滚动动画
    scrollAnimation = new QPropertyAnimation(usernameLabel, "geometry", this);
    scrollAnimation->setDuration(10000); // 10 秒钟
    connect(scrollAnimation, &QPropertyAnimation::finished, this, &ScrollWindow::handleScrollFinished);
}

void ScrollWindow::setUsername(const QString &username) {
    // 更新 QLabel 的文本
    usernameLabel->setText("Username: " + username);
}

void ScrollWindow::startScrollAnimation() {
    // 重置滚动次数
    scrollCount = 0;

    // 显示 QLabel
    usernameLabel->show();

    // 启动第一次滚动
    startSingleScrollAnimation();
}

void ScrollWindow::startSingleScrollAnimation() {
    // 获取 QLabel 的内容宽度
    QFontMetrics metrics(usernameLabel->font());
    int textWidth = metrics.horizontalAdvance(usernameLabel->text());

    // 设置 QLabel 的宽度为内容宽度
    usernameLabel->setFixedWidth(textWidth);

    // 设置滚动动画的起始和结束位置
    scrollAnimation->setStartValue(QRect(-textWidth, height() / 2 - 50, textWidth, 100)); // 从左侧开始
    scrollAnimation->setEndValue(QRect(width(), height() / 2 - 50, textWidth, 100)); // 滚动到右侧

    // 启动滚动动画
    scrollAnimation->start();
}

void ScrollWindow::handleScrollFinished() {
    // 增加滚动次数
    scrollCount++;

    // 如果滚动次数小于 3，继续滚动
    if (scrollCount < 3) {
        startSingleScrollAnimation();
    } else {
        // 滚动完成，隐藏 QLabel
        usernameLabel->hide();
    }
}
