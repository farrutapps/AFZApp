#ifndef DataInputPopup_H
#define DataInputPopup_H

#include <QWidget>
#include "classes/dbmanager.h"
#include "QCalendarWidget"

namespace Ui {
class DataInputPopup;
}

class DataInputPopup : public QWidget
{
    Q_OBJECT

public:
    explicit DataInputPopup(QWidget *parent = 0, DbManager *database_manager=NULL);
    ~DataInputPopup();

    void SetupCombo();

    QString GetDate();
    int GetSurveyType();
    QString GetLocation();

signals:
    void ok_clicked();

public slots:
    void on_OkButton_clicked();
    void on_CancelButton_clicked();
    void on_SurveyTypeBox_currentIndexChanged(int index);
    void on_LocationInput_textChanged();


private:
    Ui::DataInputPopup *ui;
    DbManager *db_man;

    vector <QString> Surveytypes;
};

#endif // DataInputPopup_H
