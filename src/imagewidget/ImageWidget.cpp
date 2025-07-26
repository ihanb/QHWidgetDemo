//
// Created by 69431 on 2024/8/7.
//

#include "ImageWidget.h"
#include <QHBoxLayout>
#include <QLabel>
ImageWidget::ImageWidget(QWidget *parent) :
        QWidget(parent){
    imageWatch = new ImageWatch;
    QImage image("D:\\File\\pic\\a.png");
    imageWatch->setPixmap(QPixmap::fromImage(image));
    QLabel* label = new QLabel;
    label->setPixmap(QPixmap::fromImage(image));
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(imageWatch);
    //layout->addWidget(label);
    this->setLayout(layout);

}

ImageWidget::~ImageWidget() {

}
