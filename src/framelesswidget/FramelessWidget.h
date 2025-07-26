#pragma once
#include <QWidget>

class QPushButton;
class QLabel;

class FramelessWidget : public QWidget {
    Q_OBJECT
public:
    explicit FramelessWidget(QWidget* parent = nullptr);
protected:
    void initUI();
    void initSubControl();
    void initConnect();
    void paintEvent(QPaintEvent* event) override;
private:
    QWidget* contentWidget;
    QPushButton* m_btn_close;
    QPushButton* m_btn_sendfoce;
    QPushButton* m_btn_reenter;
    QLabel* m_label_title;
    QLabel* m_label_content;
};
