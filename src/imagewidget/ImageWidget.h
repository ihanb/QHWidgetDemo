//
// Created by 69431 on 2024/8/7.
//

#ifndef HWIDGETDEMO_IMAGEWIDGET_H
#define HWIDGETDEMO_IMAGEWIDGET_H
#include <QWidget>
#include "ImageWatch.hpp"

class ImageWidget : public QWidget{
Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = nullptr);
    ~ImageWidget() override;

private:
    ImageWatch* imageWatch;
};


#endif //HWIDGETDEMO_IMAGEWIDGET_H
