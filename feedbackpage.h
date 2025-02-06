#ifndef FEEDBACKPAGE_H
#define FEEDBACKPAGE_H

#include <QWidget>
#include <QTextEdit>

class FeedbackPage : public QWidget {
    Q_OBJECT

public:
    explicit FeedbackPage(QWidget *parent = nullptr);

    QString getFeedback() const;

private:
    QTextEdit *feedbackEdit;
};

#endif // FEEDBACKPAGE_H
