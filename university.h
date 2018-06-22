#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>

namespace Ui {
class University;
}

class University : public QMainWindow
{
    Q_OBJECT

public:
    University(QWidget *parent = 0);
    ~University();
    QSqlTableModel *model;
        QSqlDatabase db;
         bool createDB(QString dbname);
         void setName(const QString n);
         void setRanking(const QString p);
         void AddNewUniversity(QString Name,QString Ranking);
         void ViewDetails();
protected:
    void changeEvent(QEvent *e);
private:
    Ui::University *ui;
private slots:
    void on_pushButtonView_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonAdd_clicked();
    void on_textEdit_destroyed();
};

#endif // UNIVERSITY_H







