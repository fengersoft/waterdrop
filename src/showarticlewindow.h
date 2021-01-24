#ifndef SHOWARTICLEWINDOW_H
#define SHOWARTICLEWINDOW_H

#include <QMainWindow>
#include "src/api/dialogs/setvaluedialog.h"
#include "src/api/sql/sqlitedao.h"
#include <QSqlQuery>
#include <QListWidgetItem>
namespace Ui
{
class ShowArticleWindow;
}

class ShowArticleWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowArticleWindow(QWidget* parent = nullptr);
    ~ShowArticleWindow();

    QString subject() const;
    void setSubject(const QString& subject);

    int id() const;
    void setId(int id);
    int getMaxId();
    void showData();

private slots:
    void on_btnAdd_clicked();

    void on_lvData_itemClicked(QListWidgetItem* item);

    void on_btnSave_clicked();

    void on_lvData_itemDoubleClicked(QListWidgetItem* item);

private:
    Ui::ShowArticleWindow* ui;
    QString m_subject;
    int m_id;
};

#endif // SHOWARTICLEWINDOW_H
