#include <QSignalMapper>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CImageButton.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_signalMapper = new QSignalMapper(this);
    InitUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchLayout(int id)
{
    qDebug() << "---------switch layout----------" << id;
    ClearLayout();

    switch (id) {
    case 1:
        ui->gridLayout->addWidget(GenQLabel(), 0, 0);
        break;
    case 4:
        for (int row = 0; row < 2; ++row) {
            for (int col = 0; col < 2; ++col) {
                ui->gridLayout->addWidget(GenQLabel(), row, col);
            }
        }
        break;
    case 6:
        ui->gridLayout->addWidget(GenQLabel(), 0, 0, 2, 2);
        ui->gridLayout->addWidget(GenQLabel(), 0, 2);
        ui->gridLayout->addWidget(GenQLabel(), 1, 2);
        ui->gridLayout->addWidget(GenQLabel(), 2, 0);
        ui->gridLayout->addWidget(GenQLabel(), 2, 1);
        ui->gridLayout->addWidget(GenQLabel(), 2, 2);
        break;
    case 8:
        ui->gridLayout->addWidget(GenQLabel(), 0, 0, 3, 3);
        ui->gridLayout->addWidget(GenQLabel(), 0, 3);
        ui->gridLayout->addWidget(GenQLabel(), 1, 3);
        ui->gridLayout->addWidget(GenQLabel(), 2, 3);
        ui->gridLayout->addWidget(GenQLabel(), 3, 0);
        ui->gridLayout->addWidget(GenQLabel(), 3, 1);
        ui->gridLayout->addWidget(GenQLabel(), 3, 2);
        ui->gridLayout->addWidget(GenQLabel(), 3, 3);
        break;
    case 9:
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                ui->gridLayout->addWidget(GenQLabel(), row, col);
            }
        }
        break;
    case 13:
        ui->gridLayout->addWidget(GenQLabel(), 0, 0);
        ui->gridLayout->addWidget(GenQLabel(), 0, 1);
        ui->gridLayout->addWidget(GenQLabel(), 0, 2);
        ui->gridLayout->addWidget(GenQLabel(), 0, 3);

        ui->gridLayout->addWidget(GenQLabel(), 1, 0);
        ui->gridLayout->addWidget(GenQLabel(), 1, 1, 2, 2);
        ui->gridLayout->addWidget(GenQLabel(), 1, 3);
        ui->gridLayout->addWidget(GenQLabel(), 2, 0);
        ui->gridLayout->addWidget(GenQLabel(), 2, 3);

        ui->gridLayout->addWidget(GenQLabel(), 3, 0);
        ui->gridLayout->addWidget(GenQLabel(), 3, 1);
        ui->gridLayout->addWidget(GenQLabel(), 3, 2);
        ui->gridLayout->addWidget(GenQLabel(), 3, 3);
        break;
    case 16:
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                ui->gridLayout->addWidget(GenQLabel(), row, col);
            }
        }
        break;
    default:
        break;
    }
}

void MainWindow::play(int index)
{
    // itemAt 获取给定索引的对象
    ClickableLabel *label = static_cast<ClickableLabel*>(ui->gridLayout->itemAt(index)->widget());
    assert(index == label->index);
    qDebug() << "click index:" << index;
}

void MainWindow::InitUI()
{
    setWindowTitle(tr("this is play windows"));
    // 一、四、六、八、九、十三、十六分屏
    const char* iconArr[] = {":/image/window_1.png", ":/image/window_2.png",":/image/window_3.png", ":/image/window_14.png", ":/image/window_4.png", ":/image/window_15.png",":/image/window_16.png"};
    const char* tipArr[] = {"一分屏", "四分屏", "六分屏", "八分屏", "九分屏", "十三分屏", "十六分屏"};
    const int styleArr[] = {1, 4, 6, 8, 9, 13, 16};
    for (int i = 0; i < 7; ++i) {
        CImageButton *btn = new CImageButton(this);
        QPixmap *img = new QPixmap(iconArr[i]);
        btn->SetPixmap(img, true, img, false, img, false);
        btn->setToolTip(tipArr[i]);
        btn->setFlat(true);
        btn->setFixedSize(24, 24);
        m_signalMapper->setMapping(btn, styleArr[i]);
        connect(btn, SIGNAL(clicked(bool)), m_signalMapper, SLOT(map()));
        ui->horizontalLayout->addWidget(btn);
    }
    // 统一映射
    connect(m_signalMapper, SIGNAL(mapped(int)), this, SLOT(switchLayout(int)));

    ui->horizontalLayout->addStretch();
    ui->gridLayout->setSpacing(3);
    ui->gridLayout->addWidget(GenQLabel(), 0, 0);
}

void MainWindow::ClearLayout()
{
    //清空horizontalLayout布局内的所有元素
    QLayoutItem *child;
    while ((child = ui->gridLayout->takeAt(0)) != 0) // takeAt 弹出容器中的对象
    {
        //setParent为NULL，防止删除之后界面不消失
        if(child->widget())
        {
            child->widget()->setParent(NULL);
            child->widget()->deleteLater(); // parent 设置为 NULL 后必须手动释放
        }
        delete child;
    }
    m_labelIndex = 0; // 切换分屏后重新索引
}

ClickableLabel *MainWindow::GenQLabel()
{
    ClickableLabel *label = new ClickableLabel(this);
    label->index = m_labelIndex++; // 给一个索引以区分点击的是哪个label
    connect(label, &ClickableLabel::clicked, this, &MainWindow::play);
    return label;
}

