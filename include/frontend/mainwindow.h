#ifndef FRONTEND_MAINWINDOW_H
#define FRONTEND_MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include <vector>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace frontend
{
    /**
     * @brief Класс окна программы
     */
    class MainWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        /**
         * @brief Конструктор окна программы
         * @param parent Родительский объект
         */
        MainWindow(QWidget *parent = nullptr);
        /**
         * @brief Деструктор окна программы
         */
        ~MainWindow();
        /**
         * @brief Метод добавления объекта для отрисоки
         * @param sprite Отображаемый объект
         */
        void    add_sprite(std::shared_ptr<QGraphicsItem> sprite);
        /**
         * @brief Действие при окончании игры
         * @param steps Количество шагов, за которое была завершена игра
         */
        void    game_over(uint32_t steps);
    private:
        /**
         * @brief Метод начальной настройки отображения
         */
        void    setup_scene();


        /**
         * @brief Структура окна
         */
        Ui::MainWindow* _ui;
        /**
         * @brief Графическая сцена
         *
         * @details Служит для отрисовки различных объектов и взаимодействия с ними
         */
        QGraphicsScene* _scene;
    };
}

#endif
