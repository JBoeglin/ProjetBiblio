
#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QtCore>
#include <QtWidgets/QGraphicsPixmapItem>


class ImageItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    enum { Type = UserType + 1 };

    ImageItem(int id, const QPixmap &pixmap, QGraphicsItem *parent = nullptr);

    int type() const override { return Type; }
    void adjust();
    int id() const;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private slots:
    void setFrame(int frame);
    void updateItemPosition();

private:
    QTimeLine timeLine;
    int recordId;
    double z;
};


#endif
