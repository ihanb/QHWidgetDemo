//
// Created by 69431 on 2023/9/24.
//

#ifndef HWIDGETDEMO_HTABLEVIEW_H
#define HWIDGETDEMO_HTABLEVIEW_H

#include <QWidget>
#include <QTableView>


class HTableView : public QTableView {
Q_OBJECT

public:
    explicit HTableView(QWidget *parent = nullptr);

    ~HTableView() override;

private:

};


#endif //HWIDGETDEMO_HTABLEVIEW_H
