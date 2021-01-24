#include "datainfopage.h"
#include "ui_datainfopage.h"

DataInfoPage::DataInfoPage(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::DataInfoPage)
{
    ui->setupUi(this);
    m_dataInfoWidget = new DataInfoWidget(ui->wgtClient);
    QHBoxLayout* lay = new QHBoxLayout();
    lay->setMargin(0);
    ui->wgtClient->setLayout(lay);
    lay->addWidget(m_dataInfoWidget);
    m_showArticleWindow = nullptr;

}

DataInfoPage::~DataInfoPage()
{
    delete ui;
}

int DataInfoPage::pid() const
{
    return m_pid;
}

void DataInfoPage::setPid(int pid)
{
    m_pid = pid;
    m_dataInfoWidget->setPid(m_pid);
}

void DataInfoPage::on_btnAddText_clicked()
{
    m_dataInfoWidget->setOperateCmmand(DataInfoWidgetCommand::dwText);
}



void DataInfoPage::on_btnCancel_clicked()
{
    m_dataInfoWidget->setOperateCmmand(DataInfoWidgetCommand::dwNone);
}



void DataInfoPage::on_btnAdddwCurve_clicked()
{
    m_dataInfoWidget->setOperateCmmand(DataInfoWidgetCommand::dwCurve);
}

void DataInfoPage::on_toolButton_clicked()
{
    m_dataInfoWidget->deleteSelect();
}

void DataInfoPage::on_btnSearch_clicked()
{
    m_dataInfoWidget->searchData();
}

void DataInfoPage::on_btnAddRect_clicked()
{

    m_dataInfoWidget->setOperateCmmand(dwRect);
}

void DataInfoPage::on_btnSelect_clicked()
{
    m_dataInfoWidget->setOperateCmmand(dwRectSelect);
}

void DataInfoPage::on_btnInverseSelect_clicked()
{
    m_dataInfoWidget->inverseSelect();
}

void DataInfoPage::on_btnDeSelect_clicked()
{
    m_dataInfoWidget->deSelect();
}

void DataInfoPage::on_btnLeftAlign_clicked()
{
    m_dataInfoWidget->setSelectLeftAlign();
}

void DataInfoPage::on_btnRightAlign_clicked()
{
    m_dataInfoWidget->setSelectRightAlign();
}

void DataInfoPage::on_btnArticle_clicked()
{
    DataInfoWidgetItem* item = m_dataInfoWidget->currentItem();
    if (item == nullptr)
    {
        return;
    }
    if (item->itemType() != dwText)
    {
        return;
    }
    if (m_showArticleWindow != nullptr)
    {
        delete m_showArticleWindow;
    }
    m_showArticleWindow = new ShowArticleWindow(this);
    m_showArticleWindow->setWindowTitle("关于\"" + item->text() + "\"的内容");
    m_showArticleWindow->setSubject(item->text());
    m_showArticleWindow->showMaximized();
}

void DataInfoPage::on_btnAddLine_clicked()
{
    m_dataInfoWidget->setOperateCmmand(dwLine);
}

void DataInfoPage::on_btnAvg_clicked()
{
    m_dataInfoWidget->setSelectVerAvgAlign();
}

void DataInfoPage::on_btnAddImg_clicked()
{
    m_dataInfoWidget->setOperateCmmand(dwImage);
    if (QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        startShootScreen();
    }

}

void DataInfoPage::on_btnSnap_clicked()
{
    QPoint pt = QPoint(0, 36);
    pt = ui->btnSnap->mapToGlobal(pt);
    QMenu* menu = new QMenu(this);
    QStringList items;
    items << "截图时隐藏本窗口";
    items << "截图时不隐藏本窗口";
    for (int i = 0; i < items.count(); i++)
    {
        QAction* act = new QAction(menu);
        act->setText(items[i]);
        connect(act, &QAction::triggered, this, &DataInfoPage::onBtnSnapMenuClick);
        menu->addAction(act);
    }
    menu->exec(pt);
    delete menu;

}

void DataInfoPage::onBtnSnapMenuClick()
{
    QAction* act = static_cast<QAction*>(sender());
    if (act->text() == "截图时隐藏本窗口")
    {
        startShootScreen(true);

    }
    else
    {
        startShootScreen(false);
    }
}

void DataInfoPage::on_btnAddNote_clicked()
{
    m_dataInfoWidget->setOperateCmmand(dwNote);
}

void DataInfoPage::on_btnAddVoice_clicked()
{
    m_dataInfoWidget->setOperateCmmand(dwVoice);

}
