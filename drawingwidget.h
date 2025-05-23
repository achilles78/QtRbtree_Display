#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>
#include "binarytree.h"
class DrawingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingWidget(QWidget *parent = nullptr);
    ~DrawingWidget();
    BinaryTree *getMy_Tree() const;
    void setMy_Tree(BinaryTree *newMy_Tree);

private:
    BinaryTree* My_Tree;
signals:


    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // DRAWINGWIDGET_H
