#ifndef USERINFOPAGE_H
#define USERINFOPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QDateEdit>
#include <QCheckBox>
#include <QTextEdit>
#include <QTimer>

class UserInfoPage : public QWidget {
    Q_OBJECT

public:
    explicit UserInfoPage(QWidget *parent = nullptr);

    QString getName() const;
    QDate getDateOfBirth() const;
    bool isSubscribed() const;

signals:
    void nameChanged(const QString &name); // 信号：名称变化
    void scrollTimeReached(); // 信号：滚动时间到达

private slots:
    void onNameEditingFinished();
    void checkScrollTime(); // 检查是否到达滚动时间

private:
    QLineEdit *nameEdit;
    QDateEdit *dateEdit;
    QCheckBox *subscribeCheckBox;
    QTextEdit *scrollTimeEdit; // 用于输入滚动时间
    QTimer *scrollTimer; // 定时器，用于检查滚动时间
    QSet<QString> triggeredTimes; // 记录已经触发过的时间
};

#endif // USERINFOPAGE_H
