//
// Created by 69431 on 2023/9/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWidget.h" resolved

#include <QHBoxLayout>
#include "MainWidget.h"
#include "ui_MainWidget.h"
#include "HTableView.h"
#include "FramelessWidget.h"

MainWidget::MainWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWidget) {
    ui->setupUi(this);

    initConnet();
}

MainWidget::~MainWidget() {
    delete ui;
}
void MainWidget::initConnet(){
    QObject::connect(ui->btn_ImageWatch, &QPushButton::clicked,
                     this, &MainWidget::slot_ImageWatch);

    QObject::connect(ui->btn_FramelessWidget, &QPushButton::clicked,
                     this, &MainWidget::slot_FramelessWidget);
}
void MainWidget::slot_ImageWatch(){
    QWidget* w = new QWidget();
    w->setLayout(new QHBoxLayout);
    ImageWidget* imageWidget = new ImageWidget;
    w->layout()->addWidget(imageWidget);
    w->show();
}

void MainWidget::slot_FramelessWidget(){
    FramelessWidget* fw = new FramelessWidget();
    fw->show();
}
