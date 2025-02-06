#include "feedbackpage.h"
#include <QVBoxLayout>
#include <QLabel>

FeedbackPage::FeedbackPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    feedbackEdit = new QTextEdit(this);
    feedbackEdit->setPlaceholderText("Enter your feedback here");
    layout->addWidget(new QLabel("Feedback:"));
    layout->addWidget(feedbackEdit);
}

QString FeedbackPage::getFeedback() const {
    return feedbackEdit->toPlainText();
}
