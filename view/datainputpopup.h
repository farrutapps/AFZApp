#ifndef DataInputPopup_H
#define DataInputPopup_H

#include <QWidget>
#include "model/dbmanager.h"
#include "QCalendarWidget"

namespace Ui {
class DataInputPopup;
}

class DataInputPopup : public QWidget
{
    Q_OBJECT

public:
    explicit DataInputPopup(QWidget *parent = 0, DbManager *databaseManager=NULL);
    ~DataInputPopup();

    void setupCombo();

    QString getDate();
    int getSurveyType();
    QString getLocation();

signals:
    void okClicked();

public slots:
    void on_OkButton_clicked();
    void on_CancelButton_clicked();
    void on_SurveyTypeBox_currentIndexChanged(int index);
    void on_LocationInput_textChanged();


private:
    Ui::DataInputPopup *ui;
    DbManager *dbMan;

    vector <QString> surveytypes;
};

#endif // DataInputPopup_H
