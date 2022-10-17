#ifndef BACKEND_GAME_FIELD_H
#define BACKEND_GAME_FIELD_H

#include <vector>
#include <memory>
#include <random>

#include "include/backend/cell.h"

namespace backend
{
    class Game;
    /**
     * @brief Класс игрового поля
     *
     * @details Содержит информацию обо всех клетках игрового поля
     */
    class GameField
    {
    public:
        /**
         * @brief Конструктор класса игрового поля
         * @param game Ссылка на объект игры
         * @param width Ширина игрового поля
         * @param height Высота игрового поля
         */
        GameField(Game& game, uint8_t width = 5, uint8_t height = 5);
        /**
         * @brief Метод проверки правильности расстоновки фишек
         * @return Правильность расстановки фишек
         */
        bool        check_arrangement() const;
        /**
         * @brief Метод получения объекта игры
         * @return Объект игры
         */
        Game&       get_game() const;
        /**
         * @brief Метод перемещения фишки в клетку
         * @param from_x координата x фишки
         * @param from_y координата y фишки
         * @param dx смещение фишки по оси x
         * @param dy смещение фишки по оси y
         * @return Возможно ли перемещение
         */
        bool        move_cell(
            int8_t from_x, int8_t from_y,
            int8_t dx, int8_t dy
        );
    private:
        /**
         * @brief Метод инициализации генератора поля
         *
         * @details Инициализирует массив неразмещенных клеток
         */
        void        init_generator();
        /**
         * @brief Метод инициализации игрового поля
         *
         * @details Осуществляет начальную расстановку фишек и блоков на поле
         */
        void        init_field();
        /**
         * @brief Метод генерации фишки случайного цвета
         * @return Цвет фишки
         */
        Cell::Type  generate_cell_color();
        /**
         * @brief Настройка цветов колонок поля
         */
        void        setup_columns();


        /**
         * @brief Игровое поле
         */
        std::vector<
            std::unique_ptr<Cell>
        >                               _field;
        /**
         * @brief Ширина игрового поля
         */
        const uint8_t                   _width;
        /**
         * @brief Высота игрового поля
         */
        const uint8_t                   _height;
        /**
         * @brief Фишки, отвечающие за цвет колонок
         */
        std::vector<
            std::unique_ptr<Cell>
        >                               _columns_colors;
        /**
         * @brief Количество неразмещенных клеток (по типам)
         */
        std::vector<
            std::pair<Cell::Type, uint8_t>
        >                               _unplaced_cells;
        /**
         * @brief Количество неразмещенных клеток (суммарно)
         */
        uint16_t                        _unplaced_count;
        /**
         * @brief Ссылка на объект игры
         */
        std::reference_wrapper<Game>    _game;
        /**
         * Генератор случайных чисел
         */
        std::random_device              _random_device;
        std::default_random_engine      _random_engine;
    };
}

#endif
