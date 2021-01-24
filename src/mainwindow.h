#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "src/api/dialogs/setvaluedialog.h"
#include "src/api/sql/sqlitedao.h"
#include "src/api/controls/card/selectcard.h"
#include "datainfopage.h"
#include <QHBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void loadLvSelData();
    void showData(QString sql);
    void showData(int i);

private slots:
    void on_btnAdd_clicked();

    void on_lvData_itemDoubleClicked(QListWidgetItem* item);
    void onSelectCardSelected(SelectCardItem* item);
    void on_btnMainPage_clicked();
    void onlvDataTriggerd();
private:
    Ui::MainWindow* ui;
    SelectCard* m_selectCard;
};
#endif // MAINWINDOW_H
