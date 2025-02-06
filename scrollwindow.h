#ifndef SCROLLWINDOW_H
#define SCROLLWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>

class ScrollWindow : public QWidget {
    Q_OBJECT

public:
    explicit ScrollWindow(QWidget *parent = nullptr);
    void setUsername(const QString &username); // 设置用户名
    void startScrollAnimation(); // 启动滚动动画

private slots:
    void handleScrollFinished(); // 处理滚动动画完成事件

private:
    void startSingleScrollAnimation(); // 启动单次滚动动画

    QLabel *usernameLabel; // 显示用户名的标签
    QPropertyAnimation *scrollAnimation; // 滚动动画
    int scrollCount; // 当前滚动次数
};

#endif // SCROLLWINDOW_H
