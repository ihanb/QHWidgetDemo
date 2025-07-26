#include "FramelessWidget.h"
#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPainter>

# pragma execution_character_set("utf-8")

FramelessWidget::FramelessWidget(QWidget* parent): QWidget(parent) {
    initUI();
    initSubControl();
    initConnect();
}

void FramelessWidget::initUI() {
    // 设置无边框和透明背景
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // 主内容区域
    contentWidget = new QWidget(this);
    contentWidget->setObjectName("contentWidget");
    contentWidget->setStyleSheet(
        "#contentWidget{"
        "background: qlineargradient("
        "x1:0, y1:0, x2:0, y2:1," 
        "stop:0 rgb(255,233,244)," 
        "stop:1 rgb(255,255,255));"
        " border-radius: 8px;"
        "}"
    );

    // 创建阴影效果
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect;
    shadowEffect->setBlurRadius(20);         // 阴影模糊半径
    shadowEffect->setColor(QColor(0, 0, 0, 160)); // 阴影颜色
    shadowEffect->setOffset(0, 0);           // 阴影偏移
    contentWidget->setGraphicsEffect(shadowEffect);

    // 主内容布局
    QVBoxLayout* mainLayout = new QVBoxLayout(contentWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // 窗口布局（添加边距以显示阴影）
    QVBoxLayout* windowLayout = new QVBoxLayout(this);
    windowLayout->addWidget(contentWidget);
    windowLayout->setContentsMargins(15, 15, 15, 15); // 阴影显示区域
    windowLayout->setSpacing(20);
    // 初始大小
    resize(400, 300);
}

void FramelessWidget::initConnect() {
    QObject::connect(m_btn_close, &QPushButton::clicked, this, &FramelessWidget::close);
}

void FramelessWidget::initSubControl() {
    m_btn_close = new QPushButton(this);
    m_btn_close->setFixedSize(30, 30);
    m_btn_close->setGeometry(width() - 30, 15, 30, 30);
    m_btn_close->setText("X");
    m_btn_close->raise();

    m_label_title = new QLabel(this);
    m_label_content = new QLabel(this);

    contentWidget->layout()->addWidget(m_label_title);
    contentWidget->layout()->addWidget(m_label_content);

    m_label_title->setText("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    m_label_content->setText("abbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");

    m_btn_sendfoce = new QPushButton(this);
    m_btn_sendfoce->setFixedSize(100, 35);
    m_btn_sendfoce->setText("强制发送");

    m_btn_reenter = new QPushButton(this);
    m_btn_reenter->setFixedSize(100, 35);
    m_btn_reenter->setText("重新输入");

    QHBoxLayout* btn_layout = new QHBoxLayout(this);
    btn_layout->setSpacing(15);
    btn_layout->addItem(new QSpacerItem(451, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    btn_layout->addWidget(m_btn_sendfoce);
    btn_layout->addWidget(m_btn_reenter);
    contentWidget->layout()->addItem(btn_layout);
}
void FramelessWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    //QPainter painter(this);

    //// 1. 创建线性渐变对象（从左上到右下）
    //QLinearGradient gradient(0, 0, 0, height());

    //// 2. 设置颜色停止点
    //gradient.setColorAt(0.0, QColor(255, 233, 244));
    //gradient.setColorAt(1.0, QColor(255, 255, 255));  

    //// 3. 填充背景
    //painter.fillRect(rect(), gradient);
}