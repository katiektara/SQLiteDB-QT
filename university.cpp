#include "university.h"
#include "ui_university.h"
#include <QDir>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtWidgets>

University::University(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::University)
{
    ui->setupUi(this);
    QString path ;
        path="C:/Projects/Universities";
        QDir file;
        //QString filepath=QDir::path();
        QString filename = file.path() + QDir::separator() + "universites.db";

        if(!createDB(filename))
        {
            QMessageBox::critical(this,
                                  tr("Database not found"),
                                  tr("Database not found. The application will be closed."),
                                  QMessageBox::Ok);
            qApp->exit();
        }

}

University::~University()
{
    delete ui;
}

void University::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

bool University::createDB(QString dbname)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbname);

        if(db.open())
        {

            bool found = false;
            foreach (QString table, db.tables())
            {
                if(table == "university")
                {
                    found = true;
                    break;
                }
            }
            if(!found)
            {
                QSqlQuery query(db);
                query.exec("CREATE TABLE university (name VARCHAR(32), ranking VARCHAR(16))");
            }

            model = new QSqlTableModel(this,db);
            model->setTable("university");

            model->setEditStrategy(QSqlTableModel::OnFieldChange);
            model->select();


        }
        else
            return false;

        return true;



}

void University::on_textEdit_destroyed() {}
void University::on_pushButtonAdd_clicked()
{
    QString Name=ui->textName->toPlainText();
        QString Ranking=ui->textRanking->toPlainText();

        AddNewUniversity(Name,Ranking);
}
void University::AddNewUniversity(QString Name, QString Ranking)
{
    QSqlRecord rec = model->record();
        rec.setValue("Name",Name);
        rec.setValue("Ranking",Ranking);


        // insert a new record (-1)
        model->insertRecord(-1,rec);
        ui->textName->setText("");
        ui->textRanking->setText("");

}

void University::on_pushButtonDelete_clicked()
{
    QModelIndex sample = ui->treeView->currentIndex();
        if( sample.row() >= 0 )
        {
            QMessageBox::StandardButton dlg;
            dlg = QMessageBox::question(this, tr("Remove University"),
                                        QString(tr("Do you want to remove University?")),
                                        QMessageBox::Yes | QMessageBox::No);

            if(dlg == QMessageBox::Yes)
            {
                // remove the current index
                model->removeRow(sample.row());
            }
        }
}


void University::on_pushButtonView_clicked()
{
    QTreeView  *view;
        view=ui->treeView;

         ViewDetails();

}


void University::ViewDetails()
{
    QTreeView *view=ui->treeView;
       view->setModel(model);

}


