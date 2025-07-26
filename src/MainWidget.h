//
// Created by 69431 on 2023/9/24.
//

#ifndef HWIDGETDEMO_MAINWIDGET_H
#define HWIDGETDEMO_MAINWIDGET_H

#include <QWidget>
#include "HTableView.h"
#include "ImageWidget.h"
#include "FramelessWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget {
Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);

    ~MainWidget() override;
protected slots:
    void slot_ImageWatch();
    void slot_FramelessWidget();
protected:
    void initConnet();
private:
    Ui::MainWidget *ui;
};


#endif //HWIDGETDEMO_MAINWIDGET_H
