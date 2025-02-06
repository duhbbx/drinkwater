#include "preferencespage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

PreferencesPage::PreferencesPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 设置布局的对齐方式为顶端对齐
    mainLayout->setAlignment(Qt::AlignTop);

    // 第一行：Theme
    QHBoxLayout *themeLayout = new QHBoxLayout();
    themeLayout->addWidget(new QLabel("Theme:"));
    themeComboBox = new QComboBox(this);
    themeComboBox->addItems({"Light", "Dark", "System"});
    themeLayout->addWidget(themeComboBox);
    mainLayout->addLayout(themeLayout);

    // 第二行：Dark Mode
    QHBoxLayout *darkModeLayout = new QHBoxLayout();
    darkModeCheckBox = new QCheckBox("Enable dark mode", this);
    darkModeLayout->addWidget(darkModeCheckBox);
    mainLayout->addLayout(darkModeLayout);

    // 第三行：Font Size
    QHBoxLayout *fontSizeLayout = new QHBoxLayout();
    fontSizeLayout->addWidget(new QLabel("Font Size:"));
    fontSizeSpinBox = new QSpinBox(this);
    fontSizeSpinBox->setRange(10, 24);
    fontSizeLayout->addWidget(fontSizeSpinBox);
    mainLayout->addLayout(fontSizeLayout);
}

QString PreferencesPage::getTheme() const {
    return themeComboBox->currentText();
}

bool PreferencesPage::isDarkModeEnabled() const {
    return darkModeCheckBox->isChecked();
}

int PreferencesPage::getFontSize() const {
    return fontSizeSpinBox->value();
}
