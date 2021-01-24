#ifndef DATAINFOPAGE_H
#define DATAINFOPAGE_H

#include <QWidget>
#include "datainfowidget.h"
#include "showarticlewindow.h"
#include <QMenu>
#include "src/api/capture/capturewindow.h"

namespace Ui
{
class DataInfoPage;
}

class DataInfoPage : public QWidget
{
    Q_OBJECT

public:
    explicit DataInfoPage(QWidget* parent = nullptr);
    ~DataInfoPage();

    int pid() const;
    void setPid(int pid);

private slots:
    void on_btnAddText_clicked();



    void on_btnCancel_clicked();


    void on_btnAdddwCurve_clicked();

    void on_toolButton_clicked();

    void on_btnSearch_clicked();

    void on_btnAddRect_clicked();

    void on_btnSelect_clicked();

    void on_btnInverseSelect_clicked();

    void on_btnDeSelect_clicked();

    void on_btnLeftAlign_clicked();

    void on_btnRightAlign_clicked();

    void on_btnArticle_clicked();

    void on_btnAddLine_clicked();

    void on_btnAvg_clicked();

    void on_btnAddImg_clicked();

    void on_btnSnap_clicked();
    void onBtnSnapMenuClick();

    void on_btnAddNote_clicked();

    void on_btnAddVoice_clicked();

private:
    Ui::DataInfoPage* ui;
    DataInfoWidget* m_dataInfoWidget;
    int m_pid;
    ShowArticleWindow* m_showArticleWindow;
};

#endif // DATAINFOPAGE_H
