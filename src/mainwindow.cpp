#include "mainwindow.h"
#include "graphicsview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("mouse wheel to zoom");
    setCentralWidget(new GraphicsView());
}

MainWindow::~MainWindow()
{}

QSize MainWindow::sizeHint() const
{
    return QSize(800, 600);
}

