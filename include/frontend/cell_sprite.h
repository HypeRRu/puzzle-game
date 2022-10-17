#ifndef FRONTEND_CELL_SPRITE_H
#define FRONTEND_CELL_SPRITE_H

#include <string>
#include <QGraphicsItem>

#include "include/backend/cell.h"

namespace frontend
{
    /**
     * @brief Класс отображения объекта клетки
     *
     * @details Отвечает за отрисовку определенной клетки на экране
     */
    class CellSprite: public QGraphicsItem
    {
    public:
        /**
         * @brief Конструктор отображения клетки
         * @param Отрисовываемая клетка
         */
        CellSprite(backend::Cell& object);
        /**
         * @brief Отрисовка объекта на новой позиции
         */
        void move();
        /**
         * @brief Установка смещения клетки при отрисовке
         * @param x_off Смешение по оси x (вправо) в пикселях
         * @param y_off Смещение по оси y (вниз) в пикселях
         */
        void set_offset(int8_t x_off, int8_t y_off);
        /**
         * @brief Получение границ объекта в виде прямоугольника
         * @return Прямоугольник - граница объекта
         */
        QRectF boundingRect() const;
        /**
         * @brief Метод отрисовки объекта на экране
         * @param painter Отрисовщик
         */
        void paint(
            QPainter *painter,
            const QStyleOptionGraphicsItem *,
            QWidget *
        );
        /**
         * @brief Действие при нажатии мышью на данном объекте
         */
        void mousePressEvent(QGraphicsSceneMouseEvent *);
        /**
         * @brief Действие при перемещении объекта мышью
         * @param event Событие перемещения объекта
         */
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        /**
         * @brief Действие при отпускании мыши
         */
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    protected:
        /**
         * @brief Имя текстуры объекта
         */
        std::string     _texture;
        /**
         * @brief Ширина текстуры
         */
        uint8_t         _width;
        /**
         * @brief Высота текстуры
         */
        uint8_t         _height;
        /**
         * @brief Горизонтальный отступ для отрисовки
         */
        int8_t          _x_off;
        /**
         * @brief Вертикальный отступ для отрисовки
         */
        int8_t          _y_off;
        /**
         * @brief Отрисовываемый объект
         */
        backend::Cell&  _object;
    };
}

#endif
