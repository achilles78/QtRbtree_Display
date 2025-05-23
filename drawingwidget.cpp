#include "drawingwidget.h"

#include <QPainter>

DrawingWidget::DrawingWidget(QWidget *parent)
    : QWidget{parent}
{
    My_Tree=nullptr;
}

DrawingWidget::~DrawingWidget()
{
    if (nullptr==My_Tree)
        delete My_Tree;
}

BinaryTree *DrawingWidget::getMy_Tree() const
{
    return My_Tree;
}

void DrawingWidget::setMy_Tree(BinaryTree *newMy_Tree)
{
    My_Tree = newMy_Tree;
}



void DrawingWidget::paintEvent(QPaintEvent *event)
{
    if (nullptr != My_Tree)
    {
        QPainter painter(this);
        // QPainter painter(this->centralWidget());
        QPen pen(Qt::SolidLine);
        pen.setWidth(5);
        pen.setColor(Qt::blue);
        painter.setPen(pen);

        QPen wpen(Qt::SolidLine);
        wpen.setWidth(5);
        wpen.setColor(Qt::white);


        QColor bgBlack = QColorConstants::Black;
        QColor bgRed = QColorConstants::Red;
        QBrush blackBrush(bgBlack),redBrush(bgRed);
        painter.setBrush(blackBrush);
        // 只有当树部位空的时候才画图
        if (My_Tree != nullptr && My_Tree->isright == true) {

            for (int i = 0; i < My_Tree->size(); i++) {
                QPoint p = My_Tree->getPoints()[i]; // 得到各个节点的坐标
                if (My_Tree->getLevelStr()[i]->color)
                    painter.setBrush(blackBrush);
                else
                    painter.setBrush(redBrush);
                painter.drawEllipse(p, 25, 25);     // 圆的半径为25
                painter.setPen(wpen);
                painter.drawText(p, My_Tree->getLevelStr()[i]->data.toString());
                painter.setPen(pen);
                if (i != 0)
                    painter.drawLine(My_Tree->getLines()[i - 1]); // 得到线段的坐标
            }
        }
    }
}
