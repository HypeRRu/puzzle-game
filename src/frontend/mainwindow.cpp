#include "include/frontend/mainwindow.h"

#include <QMessageBox>

#include "ui_mainwindow.h"
#include "include/frontend/cell_sprite.h"

using namespace frontend;

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    this->_ui->setupUi(this);
    this->setWindowTitle("Puzzle game");
    this->setup_scene();
}


MainWindow::~MainWindow()
{
    delete this->_ui;
    delete this->_scene;
}


void MainWindow::setup_scene()
{
    /* Конфигурация сцены */
    this->_scene = new QGraphicsScene(this);

    this->_ui->graphicsView->setAlignment(Qt::AlignCenter);
    this->_ui->graphicsView->setMinimumSize(200, 200);
    this->_ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    this->_ui->graphicsView->setScene(this->_scene);
    this->_ui->graphicsView->show();
}


void MainWindow::add_sprite(std::shared_ptr<QGraphicsItem> sprite)
{
    this->_scene->addItem(sprite.get());
}


void MainWindow::game_over(uint32_t steps)
{
    /* Сообщение об окончании игры */
    QMessageBox box;
    box.setText(QString("Игра окончена! Произведено ходов: ") + QString::number(steps));
    box.exec();
    /* Закрытие окна */
    this->close();
}

