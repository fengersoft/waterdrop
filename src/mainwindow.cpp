#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_selectCard = new SelectCard(ui->wgtSelectCard);
    QHBoxLayout* lay = new QHBoxLayout();
    ui->wgtSelectCard->setLayout(lay);
    lay->setMargin(0);
    lay->addWidget(m_selectCard);
    connect(m_selectCard, &SelectCard::onSelected, this, &MainWindow::onSelectCardSelected);
    loadLvSelData();
    showMaximized();
    showData(0);
    QStringList lvdataMenus;
    lvdataMenus << "修改主题名称";
    lvdataMenus << "删除主题";
    for (int i = 0; i < lvdataMenus.count(); i++)
    {
        QAction* act = new QAction(ui->lvData);
        act->setText(lvdataMenus[i]);
        connect(act, &QAction::triggered, this, &MainWindow::onlvDataTriggerd);
        ui->lvData->addAction(act);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadLvSelData()
{
    QStringList stl;
    stl << "全部";
    stl << "最近";
    stl << "常用";
    for (int i = 0; i < stl.count(); i++)
    {
        QListWidgetItem* item = new QListWidgetItem(ui->lvSel);
        item->setSizeHint(QSize(320, 32));
        item->setText(stl[i]);
        ui->lvSel->addItem(item);

    }
}

void MainWindow::showData(QString sql)
{
    ui->lvData->clear();
    QSqlQuery qry;
    sqliteDao()->sqliteWrapper()->select(sql, qry);
    while (qry.next())
    {
        QListWidgetItem* item = new QListWidgetItem(ui->lvData);
        item->setIcon(QIcon(":/res/subject.png"));
        item->setText(qry.value("name").toString());
        item->setData(Qt::UserRole, qry.value("id").toInt());
        item->setSizeHint(QSize(100, 48));
        item->setTextColor(QColor(97, 97, 97));
        ui->lvData->addItem(item);


    }
}

void MainWindow::showData(int i)
{
    if (i == 0)
    {
        showData("select name,id from subject");
    }
}


void MainWindow::on_btnAdd_clicked()
{
    QString s;
    bool ret = setValue("添加主题", "主题", s);
    if (ret == false)
    {
        return;
    }
    QString sql = "insert into subject (name) values ('" + s + "')";
    sqliteDao()->sqliteWrapper()->execute(sql);
    int id = sqliteDao()->sqliteWrapper()->getMaxId("subject");
    QListWidgetItem* item = new QListWidgetItem(ui->lvData);
    item->setIcon(QIcon(":/res/subject.png"));
    item->setText(s);
    item->setData(Qt::UserRole, id);
    item->setSizeHint(QSize(100, 48));
    item->setTextColor(QColor(97, 97, 97));
    ui->lvData->insertItem(0, item);
    emit ui->lvData->itemDoubleClicked(item);

}

void MainWindow::on_lvData_itemDoubleClicked(QListWidgetItem* item)
{
    if (item == nullptr)
    {
        return;
    }
    QString name = item->text();
    int id = item->data(Qt::UserRole).toInt();
    if (m_selectCard->hasItemId(id) == false)
    {
        m_selectCard->addItem(name, id);
        DataInfoPage* w = new DataInfoPage(ui->wgtPageInfos);
        w->setPid(id);
        ui->wgtPageInfos->addWidget(w);

    }

    m_selectCard->setSelected(id);

}

void MainWindow::onSelectCardSelected(SelectCardItem* item)
{
    ui->wgtPages->setCurrentIndex(1);
    for (int i = 0; i < ui->wgtPageInfos->count(); i++)
    {
        DataInfoPage* w = static_cast<DataInfoPage*>(ui->wgtPageInfos->widget(i));
        if (w->pid() == item->id)
        {
            ui->wgtPageInfos->setCurrentIndex(i);
            return;
        }
    }

}

void MainWindow::on_btnMainPage_clicked()
{
    ui->wgtPages->setCurrentIndex(0);
}

void MainWindow::onlvDataTriggerd()
{
    QAction* act = static_cast<QAction*>(sender());
    if (act->text() == "修改主题名称")
    {
        QListWidgetItem* item = ui->lvData->currentItem();
        if (item == nullptr)
        {
            return;
        }
        QString s = item->text();
        int id = item->data(Qt::UserRole).toInt();
        bool ret = setValue("修改主题名称", "主题名称", s);
        if (ret == true)
        {
            item->setText(s);
            QString sql = QString("update subject set name='%1' where id=%2").arg(s).arg(id);
            sqliteDao()->sqliteWrapper()->execute(sql);
            m_selectCard->updateItemText(id, s);
        }
    }
    else if (act->text() == "删除主题")
    {
        QListWidgetItem* item = ui->lvData->currentItem();
        if (item == nullptr)
        {
            return;
        }
        int id = item->data(Qt::UserRole).toInt();
        QString sql = QString("delete subject where id=%1").arg(id);
        sqliteDao()->sqliteWrapper()->execute(sql);
        sql = QString("delete from subjectitem where pid=%1").arg(id);
        sqliteDao()->sqliteWrapper()->execute(sql);
        ui->lvData->removeItemWidget(item);
        delete item;
        m_selectCard->deleteItemById(id);
    }
}
