#include "showarticlewindow.h"
#include "ui_showarticlewindow.h"

ShowArticleWindow::ShowArticleWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::ShowArticleWindow)
{
    ui->setupUi(this);
}

ShowArticleWindow::~ShowArticleWindow()
{
    delete ui;
}

void ShowArticleWindow::on_btnAdd_clicked()
{
    QString s = m_subject;
    bool ret = setValue("请输入标题", "标题", s);
    if (ret == false)
    {
        return;
    }
    QString sql = QString("insert into article (subject,title) values ('%1','%2')").arg(m_subject).arg(s);
    sqliteDao()->sqliteWrapper()->execute(sql);
    m_id = getMaxId();
    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(QSize(300, 32));
    item->setText(s);
    item->setData(Qt::UserRole, m_id);
    ui->lvData->insertItem(0, item);
    ui->lvData->setCurrentItem(item);

}

int ShowArticleWindow::id() const
{
    return m_id;
}

void ShowArticleWindow::setId(int id)
{
    m_id = id;
}

int ShowArticleWindow::getMaxId()
{

    return  sqliteDao()->sqliteWrapper()->getMaxId("article");
}

void ShowArticleWindow::showData()
{
    QSqlQuery qry;
    QString sql = QString("select * from article where subject='%1'").arg(m_subject);
    sqliteDao()->sqliteWrapper()->select(sql, qry);
    while (qry.next())
    {
        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(QSize(300, 32));
        item->setText(qry.value("title").toString());
        item->setData(Qt::UserRole, qry.value("id").toInt());
        ui->lvData->addItem(item);
    }

}

QString ShowArticleWindow::subject() const
{
    return m_subject;
}

void ShowArticleWindow::setSubject(const QString& subject)
{
    m_subject = subject;
    showData();
}

void ShowArticleWindow::on_lvData_itemClicked(QListWidgetItem* item)
{
    m_id = item->data(Qt::UserRole).toInt();
    ui->edtInfo->clear();
    QSqlQuery qry;
    QString sql = QString("select * from article where id=%1").arg(m_id);
    sqliteDao()->sqliteWrapper()->select(sql, qry);
    if (qry.next())
    {
        QByteArray b = qry.value("artText").toByteArray();
        QString s = QString::fromLocal8Bit(b);
        ui->edtInfo->append(s);
    }

}

void ShowArticleWindow::on_btnSave_clicked()
{
    QString html = ui->edtInfo->toHtml();
    QSqlQuery qry;
    QString sql = QString("update article set artText=? where id=%1").arg(m_id);
    sqliteDao()->sqliteWrapper()->prepare(sql, qry);
    qry.bindValue(0, html.toLocal8Bit());
    qry.exec();
}

void ShowArticleWindow::on_lvData_itemDoubleClicked(QListWidgetItem* item)
{
    QString s = item->text();
    bool ret = setValue("请输入标题", "标题", s);
    if (ret == false)
    {
        return;
    }
    QString sql = QString("update article set title='%1' where id=%2").arg(s).arg(item->data(Qt::UserRole).toInt());
    sqliteDao()->sqliteWrapper()->execute(sql);
    item->setText(s);
}
