#include "mainwindow.h"
#include "qappwidget.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    QVBoxLayout* windowLayout = new QVBoxLayout;

    windowLayout->addWidget(new QAppWidget);

    QWidget* centralWidget = new QWidget();
    centralWidget->setLayout(windowLayout);
    setCentralWidget(centralWidget);
}
MainWindow::~MainWindow()
{

}
