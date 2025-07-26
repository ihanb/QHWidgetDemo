//
// Created by 69431 on 2023/9/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWidget.h" resolved

#include <QHBoxLayout>
#include "MainWidget.h"
#include "ui_MainWidget.h"
#include "HTableView.h"

MainWidget::MainWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWidget) {
    ui->setupUi(this);
    imageWidget = new ImageWidget;

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(imageWidget);
    this->setLayout(layout);
}

MainWidget::~MainWidget() {
    delete ui;
}
