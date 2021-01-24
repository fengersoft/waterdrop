#ifndef DATAINFOWIDGETITEM_H
#define DATAINFOWIDGETITEM_H

#include <QObject>
#include <QRect>
#include <QPainter>
#include "src/api/sql/sqlitedao.h"
#include <QSqlQuery>
#include <QDate>
#include <QSound>
enum DataInfoWidgetCommand
{
    dwNone,
    dwText,
    dwCurve,
    dwRect,
    dwRectSelect,
    dwLine,
    dwImage,
    dwVoice,
    dwNote

};
typedef   DataInfoWidgetCommand DataInfoWidgetType;
class DataInfoWidgetItem : public QObject
{
    Q_OBJECT
public:
    explicit DataInfoWidgetItem(QObject* parent = nullptr);

    QString text() const;
    void setText(const QString& text);

    DataInfoWidgetType itemType() const;
    void setItemType(const DataInfoWidgetType& itemType);
    QRect rect;

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);
    QRect& calRect(QPainter& painter, int startX, int startY);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor& backgroundColor);
    QVector<QPoint> pts;
    bool isSelected() const;
    void setIsSelected(bool isSelected);

    int pid() const;
    void setPid(int pid);
    DataInfoWidgetType DataInfoWidgetTypeName(QString name);
    int getMaxId();

    int id() const;
    void setId(int id);

    int x2() const;
    void setX2(int x2);

    int y2() const;
    void setY2(int y2);
    int area();

    QPixmap& pix();
    void setPix(const QPixmap& pix);

    QDateTime createDateTime() const;
    void setCreateDateTime(const QDateTime& createDateTime);

    QString srcFileName() const;
    void setSrcFileName(const QString& srcFileName);
    void playSound();

signals:

private:
    QString m_text;
    DataInfoWidgetType m_itemType;
    int m_x;
    int m_y;
    int m_x2;
    int m_y2;
    QColor m_backgroundColor;
    bool m_isSelected;
    int m_id;
    int m_pid;
    QPixmap m_pix;
    QDateTime m_createDateTime;
    QString m_srcFileName;
    QSound* m_sound = nullptr;
};

#endif // DATAINFOWIDGETITEM_H
