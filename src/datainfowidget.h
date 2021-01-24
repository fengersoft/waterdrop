#ifndef DATAINFOWIDGET_H
#define DATAINFOWIDGET_H

#include <QWidget>
#include <QPainter>
#include "datainfowidgetitem.h"
#include "src/api/dialogs/setvaluedialog.h"
#include <QMessageBox>
#include "src/api/color/colortable.h"
#include "src/api/sql/sqlitedao.h"
#include "src/api/audio/audiorecorderdialog.h"
#include  <QDesktopServices>
#include <QUrl>
#include <QClipboard>
#include <QBuffer>
#include <QWheelEvent>
#include <qdesktopwidget.h>
#include <QFileInfo>

namespace Ui
{
class DataInfoWidget;
}


class DataInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataInfoWidget(QWidget* parent = nullptr);
    ~DataInfoWidget();

    int pid() const;
    void setPid(int pid);
    void paintEvent(QPaintEvent* event);
    DataInfoWidgetCommand operateCmmand() const;
    void setOperateCmmand(const DataInfoWidgetCommand& operateCmmand);
    QList<DataInfoWidgetItem*> items;
    bool mousedownFlag() const;
    void setMousedownFlag(bool mousedownFlag);
    void loadData();
    void clearData();
    void deleteSelect();
    void searchData();
    void inverseSelect();
    void deSelect();
    void setSelectLeftAlign();
    void setSelectVerAvgAlign();
    void setSelectRightAlign();
    DataInfoWidgetItem* currentItem();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
private:
    Ui::DataInfoWidget* ui;
    int m_pid;
    DataInfoWidgetCommand m_operateCmmand;
    bool m_mousedownFlag;
    DataInfoWidgetItem* m_currentItem;
    QColor m_waitColor;
    int m_waitX;
    int m_waitY;
    bool m_showWait;
    QPoint m_mouseDownPoint;
    QPoint m_curMousePoint;
    int m_startX;
    int m_startY;


};

#endif // DATAINFOWIDGET_H
