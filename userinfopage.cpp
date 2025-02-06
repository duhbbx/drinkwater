#include "userinfopage.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QTime>
#include <QDebug>

UserInfoPage::UserInfoPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this); // 主布局仍然是垂直布局

    // 设置布局的对齐方式为顶端对齐
    mainLayout->setAlignment(Qt::AlignTop);

    // 第一行：Name
    QHBoxLayout *nameLayout = new QHBoxLayout();
    nameLayout->addWidget(new QLabel("Name:"));
    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Enter your name");
    nameEdit->setText("请输入提醒的问题");  // 设置默认值
    nameLayout->addWidget(nameEdit);
    mainLayout->addLayout(nameLayout);

    // 第二行：Date of Birth
    QHBoxLayout *dateLayout = new QHBoxLayout();
    dateLayout->addWidget(new QLabel("Date of Birth:"));
    dateEdit = new QDateEdit(QDate::currentDate(), this);
    dateLayout->addWidget(dateEdit);
    mainLayout->addLayout(dateLayout);

    // 第三行：Subscribe Checkbox
    subscribeCheckBox = new QCheckBox("Subscribe to newsletter", this);
    mainLayout->addWidget(subscribeCheckBox);

    // 第四行：Scroll Time
    QHBoxLayout *scrollTimeLayout = new QHBoxLayout();
    scrollTimeLayout->addWidget(new QLabel("Scroll Time (HH:mm):"));
    scrollTimeEdit = new QTextEdit(this);
    scrollTimeEdit->setMaximumHeight(100); // 设置合适的高度
    scrollTimeEdit->setPlaceholderText("Enter time in HH:mm format (one per line)");
    scrollTimeLayout->addWidget(scrollTimeEdit);
    mainLayout->addLayout(scrollTimeLayout);

    // 初始化定时器
    scrollTimer = new QTimer(this);
    connect(scrollTimer, &QTimer::timeout, this, &UserInfoPage::checkScrollTime);
    scrollTimer->start(1000); // 每秒检查一次

    // 连接信号和槽
    connect(nameEdit, &QLineEdit::editingFinished, this, &UserInfoPage::onNameEditingFinished);

    this->setFocusPolicy(Qt::StrongFocus); // 允许父窗口接收焦点
}

QString UserInfoPage::getName() const {
    return nameEdit->text();
}

QDate UserInfoPage::getDateOfBirth() const {
    return dateEdit->date();
}

bool UserInfoPage::isSubscribed() const {
    return subscribeCheckBox->isChecked();
}

void UserInfoPage::onNameEditingFinished() {
    QString name = nameEdit->text();
    qDebug() << "Name set to:" << name;
    emit nameChanged(name); // 发射信号
}

void UserInfoPage::checkScrollTime() {
    QString scrollTimeText = scrollTimeEdit->toPlainText().trimmed(); // 获取滚动时间并去除空白字符
    QTime currentTime = QTime::currentTime(); // 获取当前时间

    // 按行分割输入的时间
    QStringList timeList = scrollTimeText.split('\n', Qt::SkipEmptyParts);

    for (const QString &timeStr : timeList) {
        // 解析用户输入的时间
        QTime scrollTime = QTime::fromString(timeStr.trimmed(), "HH:mm");
        if (!scrollTime.isValid()) {
            continue; // 如果时间格式无效，跳过
        }

        // 检查是否到达滚动时间
        if (currentTime.hour() == scrollTime.hour() && currentTime.minute() == scrollTime.minute()) {
            // 如果该时间点未触发过
            if (!triggeredTimes.contains(timeStr)) {
                qDebug() << "Scroll time reached:" << timeStr;
                emit scrollTimeReached(); // 发射信号
                triggeredTimes.insert(timeStr); // 标记为已触发
            }
        } else {
            // 如果时间点已过，移除标记
            triggeredTimes.remove(timeStr);
        }
    }
}
