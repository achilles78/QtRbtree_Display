#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include <QPoint>
#include <QStack>
#include <QPalette>
#include <random>
#include <vector>
#include "rbtree/include/head4rb.h"

// 构造函数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),Drawing_Widget(new DrawingWidget(this)) {
    ui->setupUi(this);
    My_Dialog = new MyDialog(this);
    My_Tree = nullptr;

    Drawing_Widget->setGeometry(0, 0, 3840, 2160);
    QPalette pal(Drawing_Widget->palette());
    pal.setColor(QPalette::Window, Qt::white); //设置背景黑色
    Drawing_Widget->setAutoFillBackground(true);
    Drawing_Widget->setPalette(pal);

    ScrollWidget = new QScrollArea(this);
    ScrollWidget->setWidget(Drawing_Widget);

    this->setCentralWidget(ScrollWidget);




    // 接受从子窗口发射过来的信号
    connect(My_Dialog, &MyDialog::strTransfer, [=](QString pre, QString in) {
        if (My_Tree != nullptr)
            My_Tree->clear();
        qDebug() << pre;
        qDebug() << in;
        if (pre.size() != in.size()) {
            QMessageBox::information(nullptr, "前序、中序构造",
                                     "前序、中序构造输入错误", QMessageBox::Yes);
        } else {
            My_Tree = new BinaryTree(pre, in);
            update();
        }
    });
}

// 析构函数
MainWindow::~MainWindow() {
    delete ui;
    delete My_Tree;
    delete My_Dialog;
    delete Drawing_Widget;
    delete ScrollWidget;
}

// 重构的绘图事件
void MainWindow::paintEvent(QPaintEvent *) {



        // 将前序、中序、后序、层次遍历依次输出
        // pen.setColor(Qt::darkCyan);
        // painter.setPen(pen);
        // painter.drawText(10,70,"前序：");
        // painter.drawText(10,100,My_Tree->getPreStr());
        // qDebug()<<My_Tree->getPreStr();
        // painter.drawText(10,150,"中序：");
        // painter.drawText(10,200,My_Tree->getInStr());
        // qDebug()<<My_Tree->getInStr();
        // painter.drawText(10,250,"后序：");
        // painter.drawText(10,300,My_Tree->getPostStr());
        // qDebug()<<My_Tree->getPostStr();
        // painter.drawText(10,350,"层次：");
        // painter.drawText(10,400,My_Tree->getLevelStr());
        // qDebug()<<My_Tree->getLevelStr();
        // //得到查找函数的各个父亲节点
        // if(!My_Tree->keyParent.isEmpty())
        // {
        //     painter.drawText(10,450,"父节点:");
        //     painter.drawText(10,500,My_Tree->keyParent);
        // }

}

// 前序构造
void MainWindow::on_actionCreat_triggered() {
    // 获得输入的字符串
    bool isOk;
    QString text =
        QInputDialog::getText(this, QString("构造树"), QString("输入字符串"),
                                         QLineEdit::Normal, QDir::home().dirName(), &isOk);

    if (isOk && !text.isEmpty()) {
        // ABC##DE#G##F###
        qDebug() << text;
        int i = text.count('#');

        // 错误判断
        if ((2 * i - text.size()) != 1) {
            QMessageBox::information(nullptr, "前序构造", "前序构造输入错误",
                                     QMessageBox::Yes);
            return;
        }

        if (My_Tree != nullptr)
            My_Tree->clear();
        My_Tree = new BinaryTree(text);
        // 如果生成树错误,则不刷新屏幕
        if (My_Tree->isright)
            update();
        else {
            QMessageBox::information(nullptr, "前序构造", "前序构造输入错误",
                                     QMessageBox::Yes);
        }
    }

    /*text.clear();
text=QString("ABC##DE#G##F###");
*/
}

// 层次构造
void MainWindow::on_actionLevel_triggered() {
    bool isOk;
    QString text =
        QInputDialog::getText(this, QString("构造树"), QString("输入字符串"),
                                         QLineEdit::Normal, QDir::home().dirName(), &isOk);
    if (isOk && !text.isEmpty()) {
        // AB#CD##EF#G####
        qDebug() << text;

        int i = text.count('#');

        // 错误判断
        if ((2 * i - text.size()) != 1) {
            QMessageBox::information(nullptr, "层次构造", "层次构造输入错误",
                                     QMessageBox::Yes);
            return;
        }

        if (My_Tree != nullptr)
            My_Tree->clear();
        My_Tree = new BinaryTree(text, 1);

        // 如果生成树错误,则不刷新屏幕
        if (My_Tree->isright)
            update();
        else {
            QMessageBox::information(nullptr, "层次构造", "层次构造输入错误",
                                     QMessageBox::Yes);
        }
    }
    /*
 * text.clear();
text=QString("AB#CD##EF#G####");
*/
}

void MainWindow::on_actionSwap_triggered() {
    My_Tree->swapTree();
    update();
}

// 查找函数
void MainWindow::on_actionFind_triggered() {
    My_Tree->keyParent.clear();
    bool isOk;
    QString text =
        QInputDialog::getText(this, QString("查找关键字"), QString("输入关键字"),
                                         QLineEdit::Normal, QDir::home().dirName(), &isOk);
    if (isOk && !text.isEmpty()) {

        QChar ch = text[0];
        if (text.size() == 1 && My_Tree->Find(ch)) {
            update();
        } else {
            QMessageBox::information(this, QString("失败"), QString("查找失败"));
        }
    }
}

void MainWindow::on_actionReCreat_triggered() { My_Dialog->show(); }

linktree gen_random_rbtree(int node_count)
{

    auto vec=std::vector<int>();
    for (int i=1;i<=node_count;i++)
       vec.push_back(i);


    std::random_device rd;
    std::mt19937 engine;
    //engine.seed(2);
    engine.seed(rd());
    std::shuffle(vec.begin(),vec.end(),engine);

    //std::vector<int> vec={6, 1, 4, 2, 16,13, 7,15,8,14,11,5,12,10,3,9};
    //std::vector<int> vec={6, 1, 4, 2, 16,13,7,15,8,14,11};
    //auto vec=std::vector<int>{6, 1, 4, 2, 16,13,7,15,8,14};
    linktree root=NULL;
    for(int& i : vec)
    {
        linktree pTreeNode = new_node(i);
        rb_insert(&root, pTreeNode);
    }
    return root;
}

void MainWindow::on_actionRandom_triggered()
{
    linktree rbtree=gen_random_rbtree(64);
    Drawing_Widget->setMy_Tree(new BinaryTree(rbtree));
    Drawing_Widget->update();


}

