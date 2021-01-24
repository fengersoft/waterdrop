#include "datainfowidgetitem.h"

DataInfoWidgetItem::DataInfoWidgetItem(QObject* parent) : QObject(parent)
{
    m_isSelected = false;
    m_createDateTime = QDateTime::currentDateTime();

}

QString DataInfoWidgetItem::text() const
{
    return m_text;
}

void DataInfoWidgetItem::setText(const QString& text)
{
    m_text = text;
}

DataInfoWidgetType DataInfoWidgetItem::itemType() const
{
    return m_itemType;
}

void DataInfoWidgetItem::setItemType(const DataInfoWidgetType& itemType)
{
    m_itemType = itemType;
}

int DataInfoWidgetItem::x() const
{
    return m_x;
}

void DataInfoWidgetItem::setX(int x)
{
    m_x = x;
}

int DataInfoWidgetItem::y() const
{
    return m_y;
}

void DataInfoWidgetItem::setY(int y)
{
    m_y = y;
}

QRect& DataInfoWidgetItem::calRect(QPainter& painter, int startX, int startY)
{
    rect.setX(startX + m_x);
    rect.setY(startY + m_y);
    QFontMetrics fm = painter.fontMetrics();
    QString s;
    if (m_itemType == dwNote)
    {
        s = m_createDateTime.toString("yyyy-MM-dd hh:mm:ss");
        s = s.length() > m_text.length() ? s : m_text;
    }
    else
    {
        s = m_text;

    }
    rect.setWidth(fm.width(s) + 16);

    rect.setHeight(fm.height() + 16);
    if (m_itemType == dwVoice)
    {
        rect.setWidth(128);
    }
    return rect;
}

QColor DataInfoWidgetItem::backgroundColor() const
{
    return m_backgroundColor;
}

void DataInfoWidgetItem::setBackgroundColor(const QColor& backgroundColor)
{
    m_backgroundColor = backgroundColor;
}

bool DataInfoWidgetItem::isSelected() const
{
    return m_isSelected;
}

void DataInfoWidgetItem::setIsSelected(bool isSelected)
{
    m_isSelected = isSelected;
}

int DataInfoWidgetItem::pid() const
{
    return m_pid;
}

void DataInfoWidgetItem::setPid(int pid)
{
    m_pid = pid;
}

DataInfoWidgetType DataInfoWidgetItem::DataInfoWidgetTypeName(QString name)
{
    if (name == "dwText")
    {
        return dwText;
    }
    if (name == "dwRect")
    {
        return dwRect;
    }
    if (name == "dwLine")
    {
        return dwLine;
    }
    else if (name == "dwImage")
    {
        return dwImage;
    }
    else if (name == "dwNote")
    {
        return dwNote;
    }
    else if (name == "dwVoice")
    {
        return dwVoice;
    }
    else
    {
        return dwNone;
    }
}

int DataInfoWidgetItem::getMaxId()
{
    QString sql = "select max(id) from subjectitem";
    QSqlQuery qry;
    sqliteDao()->sqliteWrapper()->select(sql, qry);
    qry.next();
    return qry.value(0).toInt();

}

int DataInfoWidgetItem::id() const
{
    return m_id;
}

void DataInfoWidgetItem::setId(int id)
{
    m_id = id;
}

int DataInfoWidgetItem::x2() const
{
    return m_x2;
}

void DataInfoWidgetItem::setX2(int x2)
{
    m_x2 = x2;
}

int DataInfoWidgetItem::y2() const
{
    return m_y2;
}

void DataInfoWidgetItem::setY2(int y2)
{
    m_y2 = y2;
}

int DataInfoWidgetItem::area()
{
    return rect.width() * rect.height();
}

QPixmap& DataInfoWidgetItem::pix()
{
    return m_pix;
}

void DataInfoWidgetItem::setPix(const QPixmap& pix)
{
    m_pix = pix;
}

QDateTime DataInfoWidgetItem::createDateTime() const
{
    return m_createDateTime;
}

void DataInfoWidgetItem::setCreateDateTime(const QDateTime& createDateTime)
{
    m_createDateTime = createDateTime;
}

QString DataInfoWidgetItem::srcFileName() const
{
    return m_srcFileName;
}

void DataInfoWidgetItem::setSrcFileName(const QString& srcFileName)
{
    m_srcFileName = srcFileName;
}

void DataInfoWidgetItem::playSound()
{
    if (m_sound != nullptr)
    {
        delete m_sound;
    }
    m_sound = new QSound(QApplication::applicationDirPath() + "/data/audios/" + m_srcFileName, this);
    m_sound->setLoops(1);
    m_sound->play();
}
