#ifndef SRC_UI_IMAGEWATCH_HPP
#define SRC_UI_IMAGEWATCH_HPP
// :/icons/bgcolor.png
#include <QtGlobal>
#include <QBrush>
#include <QColor>
#include <QFont>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QImage>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QOpenGLWidget>//Qt6 error
#include <QPainter>
#include <QPen>
#include <QRectF>
#include <QStyleOptionGraphicsItem>
#include <QToolTip>
#include <QWidget>

class MyGraphicsPixmapItem : public QGraphicsPixmapItem
{
public:
  explicit MyGraphicsPixmapItem(QGraphicsItem *parent = nullptr) : QGraphicsPixmapItem(parent)
  {
    setAcceptHoverEvents(true);
  }
  explicit MyGraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr)
    : QGraphicsPixmapItem(pixmap, parent)
  {
    setAcceptHoverEvents(true);
  }

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
  {
    auto   transform        = painter->transform();
    double zoom             = transform.m11();
    auto   oldItemTransMode = transformationMode();
    if (zoom >= ZOOM_THRESHOLD_LINE) { setTransformationMode(Qt::FastTransformation); }
    QGraphicsPixmapItem::paint(painter, option, widget);
    if (zoom >= ZOOM_THRESHOLD_LINE) { setTransformationMode(oldItemTransMode); }
    bool dealed = false;
    if (zoom >= ZOOM_THRESHOLD_LINE)
    {
      auto itemRect = boundingRect();
      painter->save();
      painter->setPen(QPen(QColor(128, 128, 128), 2.0 / zoom));

      auto   view              = dynamic_cast<QGraphicsView *>(widget->parent());
      auto   viewportTransform = view->viewportTransform();
      QRectF viewRect          = view->viewport()->rect();
      auto   viewRectInScene   = viewportTransform.inverted().mapRect(viewRect);
      auto   itemRectInScene   = mapRectToScene(itemRect);

      auto itemRectDisped = viewRectInScene.intersected(itemRectInScene);
      for (int iy = itemRectDisped.top(); iy <= itemRectDisped.bottom(); iy++)
      {
        painter->drawLine(0, iy, itemRect.width(), iy);
      }
      for (int ix = itemRectDisped.left(); ix <= itemRectDisped.right(); ix++)
      {
        painter->drawLine(ix, 0, ix, itemRect.height());
      }
      if (zoom >= ZOOM_THRESHOLD_VALUE)
      {
          painter->setRenderHint(QPainter::Antialiasing, true);
        // 设置灰色刷，黑色笔
        QBrush brush(QColor(128, 128, 128));
        painter->setBrush(brush);
        QPen pen(QColor(0, 0, 0));
        //pen.setWidth(1/zoom);
        painter->setPen(pen);
        QFont font = painter->font();
        font.setPointSizeF(8 * zoom / 64);
        font.setWeight(QFont::Weight(qBound(0, int(QFont::Normal * zoom / 64), 99)));
        painter->scale(1.0 / zoom, 1.0 / zoom);
        painter->setFont(font);
        // 给显示出来的每一个像素写上像素值
        QImage image = pixmap().toImage();
        for (int iy = itemRectDisped.top(); iy < itemRectDisped.bottom(); iy++)
        {
          for (int ix = itemRectDisped.left(); ix < itemRectDisped.right(); ix++)
          {
            QRgb pixel = image.pixel(ix, iy);
            QString text;
            //text = QString("%1\n%2\n%3").arg(qRed(pixel)).arg(qGreen(pixel)).arg(qBlue(pixel));
            text = QString("%1").arg((qRed(pixel)+qGreen(pixel)+qBlue(pixel)) / 3);
            QRectF rect((ix + 0.1) * zoom, (iy + 0.1) * zoom, 0.8 * zoom, 0.8 * zoom);
            QRectF bkGround = painter->boundingRect(rect, Qt::AlignCenter, text);
            bkGround.adjust(-0.1 * zoom, 0, 0.1 * zoom, 0);
            bkGround = bkGround.intersected(rect);
            //painter->drawRect(bkGround);
            //painter->drawText(rect, Qt::AlignCenter, text);

              QPainterPath textPath;
              QRectF painterRect = rect;
              QLinearGradient linearGrad;
              linearGrad.setColorAt(0, Qt::white);// 字体利用特定颜色来填充
              QFontMetrics metrics(font);
              int pixelsWide = metrics.horizontalAdvance(text);
              int pixelsHigh = metrics.height();
              textPath.addText(painterRect.x() + painterRect.width()/2 - pixelsWide/2,
                               painterRect.y() + painterRect.height()/2 + pixelsHigh/2,
                               font, text);
              painter->setBrush(linearGrad);
              painter->drawPath(textPath);
              /*painter->strokePath(textPath, pen);
              painter->drawPath(textPath);
              painter->fillPath(textPath, QBrush(Qt::blue));*/

          }
        }
      }
      painter->restore();
    }
  }

protected:
  void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override
  {
    // 获取当前的水平缩放值（X轴缩放值）
    double zoom = scene()->views().first()->transform().m11();
    if (zoom >= ZOOM_THRESHOLD_LINE)
    {
      QPointF scenePos = event->scenePos();
      QPointF itemPos  = mapFromScene(scenePos);
      int     x        = static_cast<int>(itemPos.x());
      int     y        = static_cast<int>(itemPos.y());

      QToolTip::showText(event->screenPos(), QString("Pixel: (%1, %2)").arg(x).arg(y));
    }
    else { QToolTip::hideText(); }
  }

private:
  const static int ZOOM_THRESHOLD_LINE  = 35;
  const static int ZOOM_THRESHOLD_VALUE = 80;
};

class ImageWatch : public QGraphicsView
{
public:
  ImageWatch(QWidget *parent = nullptr) : QGraphicsView(parent)
  {
    scene = new QGraphicsScene(this);
    setScene(scene);
    setViewport(new QOpenGLWidget);
    setBackgroundBrush(Qt::white);
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setInteractive(true);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAlignment(Qt::AlignCenter);

    pixmapItem = new MyGraphicsPixmapItem;
    scene->addItem(pixmapItem);

    fitInView(pixmapItem, Qt::KeepAspectRatio);
  }

  void setPixmap(const QPixmap &pixmap) { pixmapItem->setPixmap(pixmap); }

protected:
  void wheelEvent(QWheelEvent *event) override
  {
    int    numDegrees = event->delta() / 8;
    double numSteps   = numDegrees / 15.0;

    double scaleFactor = 1.15;
    if (numSteps > 0) { scale(scaleFactor, scaleFactor); }
    else
    {
      scale(1.0 / scaleFactor, 1.0 / scaleFactor);

      // 保证图片缩小到最小时, 仍能占满整个窗口
      QRectF pixmapRect         = pixmapItem->boundingRect();
      QRectF pixmapViewportRect = mapToScene(viewport()->rect()).boundingRect();
      if (pixmapViewportRect.width() > pixmapRect.width()
          && pixmapViewportRect.height() > pixmapRect.height())
      {
        fitInView(pixmapItem, Qt::KeepAspectRatio);
      }
    }
  }
  void resizeEvent(QResizeEvent *event) override
  {
    fitInView(pixmapItem, Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
  }
  void mouseDoubleClickEvent(QMouseEvent *event) override
  {
    resetTransform();
    centerOn(sceneRect().center());
    fitInView(pixmapItem, Qt::KeepAspectRatio);
    QGraphicsView::mouseDoubleClickEvent(event);
  }

private:
  QGraphicsScene       *scene;
  MyGraphicsPixmapItem *pixmapItem;
};

#endif  // SRC_UI_IMAGEWATCH_HPP
