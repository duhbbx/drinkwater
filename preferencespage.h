#ifndef PREFERENCESPAGE_H
#define PREFERENCESPAGE_H

#include <QWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>

class PreferencesPage : public QWidget {
    Q_OBJECT

public:
    explicit PreferencesPage(QWidget *parent = nullptr);

    QString getTheme() const;
    bool isDarkModeEnabled() const;
    int getFontSize() const;

private:
    QComboBox *themeComboBox;
    QCheckBox *darkModeCheckBox;
    QSpinBox *fontSizeSpinBox;
};

#endif // PREFERENCESPAGE_H
