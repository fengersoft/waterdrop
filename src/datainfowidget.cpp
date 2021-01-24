#include "datainfowidget.h"
#include "ui_datainfowidget.h"

DataInfoWidget::DataInfoWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::DataInfoWidget)
{
    ui->setupUi(this);
    m_operateCmmand = dwNone;
    m_mousedownFlag = false;
    setMouseTracking(true);
    m_showWait = false;
    m_startX = 0;
    m_startY = 0;

}

DataInfoWidget::~DataInfoWidget()
{
    clearData();
    delete ui;
}

int DataInfoWidget::pid() const
{
    return m_pid;
}

void DataInfoWidget::setPid(int pid)
{
    m_pid = pid;
    loadData();
}

void DataInfoWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing);
    painter.fillRect(rect(), QBrush(Qt::white));
    for (int i = 0; i < items.count(); i++)
    {
        DataInfoWidgetItem* item = items.at(i);
        if (item->itemType() == dwText)
        {
            QRect rc = item->calRect(painter, m_startX, m_startY);
            if (item->isSelected())
            {
                painter.setBrush(Qt::NoBrush);
                painter.setPen(item->backgroundColor());
                QRect selRc = QRect(rc.x() - 2, rc.y() - 2, rc.width() + 4, rc.height() + 4);
                painter.drawRect(selRc);
                qDebug() << selRc;
            }
            painter.setBrush(QBrush(item->backgroundColor()));
            painter.setPen(Qt::NoPen);
            painter.drawRect(rc);
            painter.setPen(Qt::white);
            painter.drawText(rc, Qt::AlignCenter, item->text());
        }
        else if (item->itemType() == dwVoice)
        {
            QRect rc = item->calRect(painter, m_startX, m_startY);
            rc.setRight(rc.left() + 128);
            if (item->isSelected())
            {
                painter.setBrush(Qt::NoBrush);
                painter.setPen(item->backgroundColor());
                QRect selRc = QRect(rc.x() - 2, rc.y() - 2, rc.width() + 4, rc.height() + 4);
                painter.drawRect(selRc);
                qDebug() << selRc;
            }
            painter.setBrush(QBrush(item->backgroundColor()));
            painter.setPen(Qt::NoPen);
            painter.drawRect(rc);
            QPixmap pix = QPixmap(":/res/voicewave.png");
            QRect pixRc = QRect(rc.left() + 4, rc.top() + 4, rc.height() - 8, rc.height() - 8);
            painter.drawPixmap(pixRc, pix, pix.rect());
            painter.setPen(Qt::white);
            painter.drawText(rc, Qt::AlignCenter, "录音");
        }
        else if (item->itemType() == dwNote)
        {
            QRect rc = item->calRect(painter, m_startX, m_startY);
            rc.setHeight(rc.height() * 2);
            if (item->isSelected())
            {
                painter.setBrush(Qt::NoBrush);
                painter.setPen(item->backgroundColor());
                QRect selRc = QRect(rc.x() - 2, rc.y() - 2, rc.width() + 4, rc.height() + 4);
                painter.drawRect(selRc);
                qDebug() << selRc;
            }
            QRect createDateTimeRc = QRect(rc.left(), rc.top(), rc.width(), rc.height() / 2);
            QRect textRc = QRect(rc.left(), rc.top() + rc.height() / 2, rc.width(), rc.height() / 2);
            painter.setBrush(QBrush(item->backgroundColor()));
            painter.setPen(Qt::NoPen);
            painter.drawRect(textRc);
            painter.setPen(QColor(197, 197, 197));

            painter.drawText(createDateTimeRc, Qt::AlignCenter, item->createDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            painter.setPen(Qt::white);
            textRc.setLeft(textRc.left() + 8);
            painter.drawText(textRc, Qt::AlignVCenter | Qt::AlignLeft, item->text());
        }
        else if (item->itemType() == dwRect)
        {
            painter.setPen(Qt::black);
            QPoint pt1 = QPoint(item->x(), item->y());
            QPoint pt2 = QPoint(item->x2(), item->y2());;

            pt1.setX(pt1.x() + m_startX);
            pt1.setY(pt1.y() + m_startY);

            pt2.setX(pt2.x() + m_startX);
            pt2.setY(pt2.y() + m_startY);
            painter.drawLine(pt1.x(), pt1.y(), pt2.x(), pt1.y());
            painter.drawLine(pt1.x(), pt1.y(), pt1.x(), pt2.y());
            painter.drawLine(pt1.x(), pt2.y(), pt2.x(), pt2.y());
            painter.drawLine(pt2.x(), pt1.y(), pt2.x(), pt2.y());

            int x = pt1.x() < pt2.x() ? pt1.x() : pt2.x();
            int y = pt1.y() < pt2.y() ? pt1.y() : pt2.y();
            item->rect = QRect(x, y, abs(pt2.x() - pt1.x()), abs(pt2.y() - pt1.y()));
        }
        else if (item->itemType() == dwLine)
        {
            painter.setPen(Qt::black);
            QPoint pt1 = QPoint(item->x(), item->y());
            QPoint pt2 = QPoint(item->x2(), item->y2());

            pt1.setX(pt1.x() + m_startX);
            pt1.setY(pt1.y() + m_startY);

            pt2.setX(pt2.x() + m_startX);
            pt2.setY(pt2.y() + m_startY);
            painter.drawLine(pt1, pt2);
            int x = pt1.x() < pt2.x() ? pt1.x() : pt2.x();
            int y = pt1.y() < pt2.y() ? pt1.y() : pt2.y();
            item->rect = QRect(x, y, abs(pt2.x() - pt1.x()), abs(pt2.y() - pt1.y()));


        }
        else if (item->itemType() == dwImage)
        {
            painter.setPen(Qt::black);
            QPoint pt1 = QPoint(item->x(), item->y());
            QPoint pt2;

            pt1.setX(pt1.x() + m_startX);
            pt1.setY(pt1.y() + m_startY);
            qreal n = qApp->devicePixelRatio();
            pt2.setX(pt1.x() + item->pix().width() / n);
            pt2.setY(pt1.y() + item->pix().height() / n);

            item->rect = QRect(pt1.x(), pt1.y(), abs(pt2.x() - pt1.x()), abs(pt2.y() - pt1.y()));
            painter.drawPixmap(item->rect, item->pix(), item->pix().rect());

        }
        else if (item->itemType() == dwCurve)
        {
            QPen pen;
            pen.setColor(item->backgroundColor());
            pen.setWidth(1);
            painter.setPen(pen);
            if (item->pts.count() < 2)
            {
                return;
            }
            for (int j = 0; j < item->pts.count() - 1; j++)
            {
                QPoint pt1 = item->pts.at(j);
                QPoint pt2 = item->pts.at(j + 1);

                pt1.setX(pt1.x() + m_startX);
                pt1.setY(pt1.y() + m_startY);

                pt2.setX(pt2.x() + m_startX);
                pt2.setY(pt2.y() + m_startY);

                painter.drawLine(pt1, pt2);
            }


        }

    }
    if (m_showWait == true)
    {
        QFontMetrics fm = painter.fontMetrics();
        int w = fm.width("待插入字符");
        int h = fm.height();
        QRect rc = QRect(m_waitX, m_waitY, w + 16, h + 16);
        painter.setBrush(QBrush(m_waitColor));
        painter.setPen(Qt::NoPen);
        painter.drawRect(rc);
        painter.setPen(Qt::white);

    }
    if ((m_operateCmmand == dwRect) || (m_operateCmmand == dwRectSelect))
    {
        painter.setPen(Qt::black);
        QPoint pt1 = m_mouseDownPoint;
        QPoint pt2 = m_curMousePoint;

        pt1.setX(pt1.x() + m_startX);
        pt1.setY(pt1.y() + m_startY);

        pt2.setX(pt2.x() + m_startX);
        pt2.setY(pt2.y() + m_startY);
        painter.drawLine(pt1.x(), pt1.y(), pt2.x(), pt1.y());
        painter.drawLine(pt1.x(), pt1.y(), pt1.x(), pt2.y());
        painter.drawLine(pt1.x(), pt2.y(), pt2.x(), pt2.y());
        painter.drawLine(pt2.x(), pt1.y(), pt2.x(), pt2.y());
    }
    if (m_operateCmmand == dwLine)
    {
        QPoint pt1 = m_mouseDownPoint;
        QPoint pt2 = m_curMousePoint;

        pt1.setX(pt1.x() + m_startX);
        pt1.setY(pt1.y() + m_startY);

        pt2.setX(pt2.x() + m_startX);
        pt2.setY(pt2.y() + m_startY);
        painter.drawLine(pt1, pt2);
    }
    painter.end();
}

DataInfoWidgetCommand DataInfoWidget::operateCmmand() const
{
    return m_operateCmmand;
}

void DataInfoWidget::setOperateCmmand(const DataInfoWidgetCommand& operateCmmand)
{
    m_operateCmmand = operateCmmand;
}

void DataInfoWidget::mousePressEvent(QMouseEvent* event)
{
    QPoint pt = mapFromGlobal(cursor().pos());
    if ((m_operateCmmand == dwText) || (m_operateCmmand == dwNote))
    {
        m_waitColor = ColorTable::getRandomColor();
        m_waitX = pt.x();
        m_waitY = pt.y();
        m_showWait = true;
        update();
        QString s;
        bool ret = setValue("添加文本", "文本", s);
        if (ret == true)
        {
            DataInfoWidgetItem* item = new DataInfoWidgetItem(this);
            item->setPid(m_pid);
            item->setText(s);
            item->setItemType(m_operateCmmand);
            item->setX(pt.x() - m_startX);
            item->setY(pt.y() - m_startY);
            item->setBackgroundColor(m_waitColor);
            int r, g, b;
            m_waitColor.getRgb(&r, &g, &b);
            QString itemType = m_operateCmmand == dwText ? "dwText" : "dwNote";
            QString sql = QString("insert into subjectitem (pid,item,itemtype,x,y,r,g,b,createDateTime) values "
                                  " (%1,'%2','%3',%4,%5,%6,%7,%8,'%9')")
                          .arg(m_pid).arg(s).arg(itemType).arg(m_waitX - m_startX).arg(m_waitY - m_startY)
                          .arg(r).arg(g).arg(b).arg(item->createDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            qDebug() << m_waitX;
            qDebug() << m_startX;
            qDebug() << m_startY;
            sqliteDao()->sqliteWrapper()->execute(sql);
            item->setId(item->getMaxId());
            items << item;
            m_mousedownFlag = false;

            m_operateCmmand = dwNone;
            update();
        }
        m_showWait = false;

    }
    else if (m_operateCmmand == dwVoice)
    {
        m_waitColor = ColorTable::getRandomColor();
        m_waitX = pt.x();
        m_waitY = pt.y();
        m_showWait = true;
        update();
        QString s;
        QString srcPath;
        bool ret = showAudioRecorderDialog(srcPath);
        if (ret == true)
        {
            QFileInfo info(srcPath);
            QString srcFileName = info.fileName();
            DataInfoWidgetItem* item = new DataInfoWidgetItem(this);
            item->setPid(m_pid);
            item->setText(s);
            item->setItemType(m_operateCmmand);
            item->setX(pt.x() - m_startX);
            item->setY(pt.y() - m_startY);
            item->setBackgroundColor(m_waitColor);
            item->setSrcFileName(srcFileName);
            int r, g, b;
            m_waitColor.getRgb(&r, &g, &b);
            QString itemType = "dwVoice";
            QString sql = QString("insert into subjectitem (pid,srcFileName,itemtype,x,y,r,g,b,createDateTime) values "
                                  " (%1,'%2','%3',%4,%5,%6,%7,%8,'%9')")
                          .arg(m_pid).arg(srcFileName).arg(itemType).arg(m_waitX - m_startX).arg(m_waitY - m_startY)
                          .arg(r).arg(g).arg(b).arg(item->createDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            sqliteDao()->sqliteWrapper()->execute(sql);
            item->setId(item->getMaxId());
            items << item;
            update();
            m_operateCmmand = dwNone;
        }
        m_showWait = false;

    }
    else if (m_operateCmmand == dwImage)
    {
        QPixmap pix = qApp->clipboard()->pixmap();
        if (pix.isNull())
        {
            update();
            return;
        }
        DataInfoWidgetItem* item = new DataInfoWidgetItem(this);
        item->setPid(m_pid);
        item->setPix(pix);
        item->setItemType(dwImage);
        item->setX(pt.x() - m_startX);
        item->setY(pt.y() - m_startY);
        item->setBackgroundColor(m_waitColor);
        int r, g, b;
        m_waitColor.getRgb(&r, &g, &b);
        QString sql = QString("insert into subjectitem (pid,data,itemtype,x,y,r,g,b) values "
                              " (%1,?,'%2','%3',%4,%5,%6,%7)")
                      .arg(m_pid).arg("dwImage").arg(pt.x() - m_startX).arg(pt.y() - m_startY).arg(r).arg(g).arg(b);
        QSqlQuery qry;
        sqliteDao()->sqliteWrapper()->prepare(sql, qry);
        QByteArray data;
        QBuffer buf(&data);
        pix.save(&buf, "png");
        qry.bindValue(0, data);
        qry.exec();
        item->setId(item->getMaxId());
        items << item;
        update();
        m_operateCmmand = dwNone;
    }

    else if (m_operateCmmand == dwCurve)
    {
        m_mousedownFlag = true;
        DataInfoWidgetItem* item = new DataInfoWidgetItem(this);


        pt.setX(pt.x() - m_startX);
        pt.setY(pt.y() - m_startY);
        item->pts << pt;
        item->setItemType(dwCurve);
        item->setBackgroundColor(ColorTable::getRandomColor());
        items << item;
        m_currentItem = item;
        update();
    }
    else if ((m_operateCmmand == dwRect) || (m_operateCmmand == dwRectSelect)
             || (m_operateCmmand == dwLine))
    {
        m_mousedownFlag = true;



        pt.setX(pt.x() - m_startX);
        pt.setY(pt.y() - m_startY);
        m_mouseDownPoint = pt;
        m_curMousePoint = pt;
        update();
    }
    else if (m_operateCmmand == dwNone)
    {
        m_mouseDownPoint = pt;
        m_mousedownFlag = true;
        QList<DataInfoWidgetItem*> selItems;
        for (int i = 0; i < items.count(); i++)
        {
            DataInfoWidgetItem* item = items.at(i);
            if (item->rect.contains(pt))
            {
                selItems << item;
            }
        }
        qSort(selItems.begin(), selItems.end(), [](DataInfoWidgetItem * item1, DataInfoWidgetItem * item2)
        {
            if (item1->area() < item2->area())
            {
                return true;
            }
            else
            {
                return false;
            }
        });
        if (selItems.count() > 0)
        {
            m_currentItem = selItems.at(0);
            m_currentItem->setIsSelected(true);
            int i = items.indexOf(m_currentItem);
            items.takeAt(i);
            items.append(m_currentItem);

        }
        else
        {
            m_currentItem = nullptr;
        }
        update();


    }
}

void DataInfoWidget::mouseMoveEvent(QMouseEvent* event)
{
    QPoint pt = mapFromGlobal(cursor().pos());
    if (m_operateCmmand == dwCurve)
    {
        if (m_mousedownFlag == true)
        {
            pt.setX(pt.x() - m_startX);
            pt.setY(pt.y() - m_startY);
            m_currentItem->pts << pt;
            update();
        }
    }
    if ((m_operateCmmand == dwRect) || (m_operateCmmand == dwRectSelect) ||
        (m_operateCmmand == dwLine))
    {
        if (m_mousedownFlag == true)
        {
            pt.setX(pt.x() - m_startX);
            pt.setY(pt.y() - m_startY);
            m_curMousePoint = pt;
            update();
        }
    }
    else if (m_operateCmmand == dwNone)
    {
        if (m_mousedownFlag == true)
        {
            int x = pt.x() - m_mouseDownPoint.x();
            int y = pt.y() - m_mouseDownPoint.y();
            if (m_currentItem != nullptr)
            {
                m_currentItem->setX(m_currentItem->x() + x);
                m_currentItem->setY(m_currentItem->y() + y);
                m_currentItem->setX2(m_currentItem->x2() + x);
                m_currentItem->setY2(m_currentItem->y2() + y);
            }
            else
            {
                m_startX += x;
                m_startY += y;
            }


            m_mouseDownPoint = pt;
            update();
            qDebug() << "move";
        }
    }
}

void DataInfoWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    QPoint pt = mapFromGlobal(cursor().pos());
    for (int i = 0; i < items.count(); i++)
    {
        DataInfoWidgetItem* item = items.at(i);
        if ((item->itemType() == dwText) || (item->itemType() == dwNote))
        {
            if (item->rect.contains(pt))
            {
                QString s = item->text();
                bool ret = setValue("修改文本", "文本", s);
                if (ret == true)
                {
                    item->setText(s);
                    QString sql = QString("update subjectitem set item='%1' where id=%2").arg(s).arg(item->id());
                    sqliteDao()->sqliteWrapper()->execute(sql);
                    update();
                }

                return;
            }
        }
        else if (item->itemType() == dwVoice)
        {
            if (item->rect.contains(pt))
            {
                item->playSound();
            }

        }

    }
}

void DataInfoWidget::wheelEvent(QWheelEvent* event)
{
    if (m_operateCmmand == dwNone)
    {
        if (event->modifiers() == Qt::ControlModifier)
        {
            m_startX += event->delta();
            update();
        }
        else
        {
            m_startY += event->delta();
            update();
        }

    }
}

bool DataInfoWidget::mousedownFlag() const
{
    return m_mousedownFlag;
}

void DataInfoWidget::setMousedownFlag(bool mousedownFlag)
{
    m_mousedownFlag = mousedownFlag;
}

void DataInfoWidget::loadData()
{
    clearData();
    QString sql = "select * from subjectitem where pid=" + QString("%1").arg(m_pid) + " order by id";
    QSqlQuery qry;
    sqliteDao()->sqliteWrapper()->select(sql, qry);
    while (qry.next())
    {

        DataInfoWidgetItem* item = new DataInfoWidgetItem(this);
        item->setPid(m_pid);
        item->setText(qry.value("item").toString());
        item->setItemType(item->DataInfoWidgetTypeName(qry.value("itemType").toString()));
        item->setX(qry.value("x").toInt());
        item->setY(qry.value("y").toInt());
        item->setBackgroundColor(QColor(qry.value("r").toInt(), qry.value("g").toInt(), qry.value("b").toInt()));
        item->setId(qry.value("id").toInt());
        item->setX2(qry.value("x2").toInt());
        item->setY2(qry.value("y2").toInt());
        item->setSrcFileName(qry.value("srcFileName").toString());
        if (item->itemType() == dwImage)
        {
            QByteArray data = qry.value("data").toByteArray();
            item->pix().loadFromData(data, "png");
        }
        else if (item->itemType() == dwNote)
        {
            item->setCreateDateTime(qry.value("createDateTime").toDateTime());
        }

        items << item;
    }
    update();
}

void DataInfoWidget::clearData()
{
    qDeleteAll(items);
    items.clear();
}

void DataInfoWidget::deleteSelect()
{
    for (int i = items.count() - 1; i >= 0; i--)
    {

        DataInfoWidgetItem* item = items.at(i);
        if (!item->isSelected())
        {
            continue;
        }

        QString sql = QString("delete from subjectitem where id=%1").arg(item->id());
        sqliteDao()->sqliteWrapper()->execute(sql);
        items.removeOne(item);
        delete item;


    }
    m_currentItem = nullptr;
    update();
}

void DataInfoWidget::searchData()
{
    if (m_currentItem != nullptr)
    {
        QDesktopServices::openUrl(QUrl("https://www.baidu.com/s?wd=" + m_currentItem->text()));
    }
}

void DataInfoWidget::inverseSelect()
{
    for (int i = 0; i < items.count(); i++)
    {
        DataInfoWidgetItem* item = items.at(i);
        item->setIsSelected(!item->isSelected());
    }
    update();
}

void DataInfoWidget::deSelect()
{
    for (int i = 0; i < items.count(); i++)
    {
        DataInfoWidgetItem* item = items.at(i);
        item->setIsSelected(false);
    }
    update();
}

void DataInfoWidget::setSelectLeftAlign()
{
    int l = 65535;
    for (int i = 0; i < items.count(); i++)
    {
        DataInfoWidgetItem* item = items.at(i);
        if (!item->isSelected())
        {
            continue;
        }
        if (item->x() < l)
        {
            l = item->x();
        }

    }
    for (int i = 0; i < items.count(); i++)
    {
        DataInfoWidgetItem* item = items.at(i);
        if (!item->isSelected())
        {
            continue;
        }
        item->setX(l);
        QString sql = QString("update subjectitem set x=%1 where id=%2").arg(l).arg(item->id());
        sqliteDao()->sqliteWrapper()->execute(sql);

    }
    update();
}

void DataInfoWidget::setSelectVerAvgAlign()
{
    QList<DataInfoWidgetItem*> selItems;
    for (int i = 0; i < items.count(); i++)
    {
        DataInfoWidgetItem* item = items.at(i);
        if (!item->isSelected())
        {
            continue;
        }
        selItems << item;

    }
    if (selItems.count() < 2)
    {
        return;
    }
    qSort(selItems.begin(), selItems.end(), [](DataInfoWidgetItem * item1, DataInfoWidgetItem * item2)
    {
        if (item1->y() < item2->y())
        {
            return true;
        }
        return  false;

    });
    int h0 = 0;
    int h1 = items.at(items.count() - 1)->rect.bottom() - items.at(0)->rect.top();
    for (int i = 0; i < selItems.count(); i++)
    {
        DataInfoWidgetItem* item = selItems.at(i);
        h0 += item->rect.height();

    }
    int v = (h1 - h0) / (items.count() - 1);
    for (int i = 1; i < selItems.count(); i++)
    {
        DataInfoWidgetItem* item = selItems.at(i);
        DataInfoWidgetItem* preItem = selItems.at(i - 1);
        item->setY(preItem->y() + preItem->rect.height() + v);


    }
    update();

}

void DataInfoWidget::setSelectRightAlign()
{
    int l = -65535;
    for (int i = 0; i < items.count(); i++)
    {
        DataInfoWidgetItem* item = items.at(i);
        if (!item->isSelected())
        {
            continue;
        }
        if ((item->x() + item->rect.width()) > l)
        {
            l = item->x() + item->rect.width();
        }

    }
    for (int i = 0; i < items.count(); i++)
    {
        DataInfoWidgetItem* item = items.at(i);
        if (!item->isSelected())
        {
            continue;
        }
        item->setX(l - item->rect.width());
        QString sql = QString("update subjectitem set x=%1 where id=%2").arg(l).arg(item->id());
        sqliteDao()->sqliteWrapper()->execute(sql);

    }
    update();
}

DataInfoWidgetItem* DataInfoWidget::currentItem()
{
    return m_currentItem;
}

void DataInfoWidget::mouseReleaseEvent(QMouseEvent* event)
{
    QPoint pt = mapFromGlobal(cursor().pos());
    if (m_operateCmmand == dwCurve)
    {
        m_mousedownFlag = false;


        pt.setX(pt.x() - m_startX);
        pt.setY(pt.y() - m_startY);
        m_currentItem->pts << pt;



        update();
        m_currentItem = nullptr;

    }
    else if (m_operateCmmand == dwRect)
    {
        m_currentItem = nullptr;
        m_operateCmmand = dwNone;
        m_mousedownFlag = false;
        DataInfoWidgetItem* item = new DataInfoWidgetItem();
        item->setItemType(dwRect);
        item->setPid(m_pid);
        item->setX(m_mouseDownPoint.x());
        item->setY(m_mouseDownPoint.y());
        item->setX2(m_curMousePoint.x());
        item->setY2(m_curMousePoint.y());
        QString sql = QString("insert into subjectItem (pid,x,y,x2,y2,r,g,b,itemType) values "
                              "(%1,%2,%3,%4,%5,%6,%7,%8,'%9')")
                      .arg(m_pid).arg(item->x()).arg(item->y()).arg(item->x2()).arg(item->y2())
                      .arg(0).arg(0).arg(0).arg("dwRect");
        sqliteDao()->sqliteWrapper()->execute(sql);
        item->setId(item->getMaxId());
        items << item;
        update();
    }
    else if (m_operateCmmand == dwLine)
    {
        m_currentItem = nullptr;
        m_operateCmmand = dwNone;
        m_mousedownFlag = false;
        DataInfoWidgetItem* item = new DataInfoWidgetItem();
        item->setItemType(dwLine);
        item->setPid(m_pid);
        item->setX(m_mouseDownPoint.x());
        item->setY(m_mouseDownPoint.y());
        item->setX2(m_curMousePoint.x());
        item->setY2(m_curMousePoint.y());
        QString sql = QString("insert into subjectItem (pid,x,y,x2,y2,r,g,b,itemType) values "
                              "(%1,%2,%3,%4,%5,%6,%7,%8,'%9')")
                      .arg(m_pid).arg(item->x()).arg(item->y()).arg(item->x2()).arg(item->y2())
                      .arg(0).arg(0).arg(0).arg("dwLine");
        sqliteDao()->sqliteWrapper()->execute(sql);
        item->setId(item->getMaxId());
        items << item;
        update();
    }
    else if (m_operateCmmand == dwRectSelect)
    {
        m_currentItem = nullptr;
        m_operateCmmand = dwNone;
        m_mousedownFlag = false;

        QPoint pt1 = m_mouseDownPoint;
        QPoint pt2 = m_curMousePoint;

        pt1.setX(pt1.x() + m_startX);
        pt1.setY(pt1.y() + m_startY);

        pt2.setX(pt2.x() + m_startX);
        pt2.setY(pt2.y() + m_startY);

        int x = pt1.x() < pt2.x() ? pt1.x() : pt2.x();
        int y = pt1.y() < pt2.y() ? pt1.y() : pt2.y();
        QRect rc = QRect(x, y, abs(pt1.x() - pt2.x()), abs(pt1.y() - pt2.y()));
        for (int i = 0; i < items.count(); i++)
        {
            DataInfoWidgetItem* item = items.at(i);
            item->setIsSelected(rc.contains(item->rect));
        }
        update();
    }
    else if (m_operateCmmand == dwNone)
    {
        if ((m_mousedownFlag == true) && (m_currentItem != nullptr))
        {
            QString sql = QString("update subjectitem set x=%1,y=%2 where id=%3").arg(m_currentItem->x())
                          .arg(m_currentItem->y()).arg(m_currentItem->id());
            sqliteDao()->sqliteWrapper()->execute(sql);

        }
        m_mousedownFlag = false;
    }
}
