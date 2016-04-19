#ifndef PREFERENCESWINDOW_H
#define PREFERENCESWINDOW_H

#include <QWidget>

namespace Ui {
class PreferencesWindow;
}

class PreferencesWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PreferencesWindow(QWidget *parent = 0);
    ~PreferencesWindow();

private:
    Ui::PreferencesWindow *ui;
};

#endif // PREFERENCESWINDOW_H
