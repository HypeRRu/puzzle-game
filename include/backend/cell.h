#ifndef BACKEND_CELL_H
#define BACKEND_CELL_H

#include <string>
#include <memory>

namespace frontend
{
    class CellSprite;
}

namespace backend
{
    class GameField;
    /**
     * @brief Класс клетки
     *
     * @details Содержит информацию о клетке игрового поля
     */
    class Cell
    {
    public:
        /**
         * @brief Тип клетки
         */
        enum class Type
        {
            Free,
            Blocked,
            Yellow,
            Orange,
            Red
        };
        /**
         * @brief Конструктор класс клетки
         * @param x Координата x расположения клетки на поле
         * @param y Координата y расположения клетки на поле
         * @param type Тип клетки
         */
        Cell(GameField& owner, int8_t x, int8_t y, Type type);
        /**
         * @brief Сеттер координаты x клетки
         * @param x Координата x расположения клетки на поле
         */
        void        set_x(int8_t x);
        /**
         * @brief Геттер координаты x клетки
         * @return Координата x расположения клетки
         */
        int8_t      get_x() const;
        /**
         * @brief Сеттер координаты y клетки
         * @param y Координата y расположения клетки на поле
         */
        void        set_y(int8_t y);
        /**
         * @brief Геттер координаты y клетки
         * @return Координата y расположения клетки
         */
        int8_t      get_y() const;
        /**
         * @brief Геттер типа клетки
         * @return Тип клетки
         */
        Cell::Type  get_type() const;
        /**
         * @brief Геттер графического отображения клетки
         * @return Графическое отображение клетки
         */
        std::shared_ptr<frontend::CellSprite> get_sprite() const;
        /**
         * @brief Функция смены позиции клетки
         * @param dx сдвиг позиции по оси X
         * @param dy сдвиг позиции по оси Y
         * @return Возможно ли движение
         */
        bool move(int8_t dx, int8_t dy);
    protected:
        /**
         * @brief Расположение клетки по x
         */
        int8_t                                  _pos_x;
        /**
         * @brief Расположение клетки по y
         */
        int8_t                                  _pos_y;
        /**
         * @brief Тип клетки
         */
        Type                                    _type;
        /**
         * @brief Графическое отображение клетки
         */
        std::shared_ptr<frontend::CellSprite>   _sprite;
        /**
         * @brief Объект поля, которому принадлежит клетка
         */
        GameField&                              _owner;
    };
}

#endif
