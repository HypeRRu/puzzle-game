#ifndef BACKEND_GAME_H
#define BACKEND_GAME_H

#include <memory>
#include <string>

#include "include/backend/game_field.h"
#include "include/frontend/mainwindow.h"

namespace backend
{
    /**
     * @brief Класс игры
     */
    class Game
    {
    public:
        /**
         * @brief Конструктор класса игры
         */
        Game();
        /**
         * @brief Запуск игры
         */
        void                    run();
        /**
         * @brief Окончание игры
         */
        void                    game_over();
        /**
         * @brief Получение текущего количества шагов
         * @return Количество шагов (перемещений фишек)
         */
        uint32_t                steps_count() const;
        /**
         * @brief Увеличение счетчика шагов на 1
         */
        void                    inc_steps();
        /**
         * @brief Геттер игрового поля
         * @return Ссылка на игровое поле
         */
        GameField&              get_field() const;
        /**
         * @brief Геттер игрового окна
         * @return Ссылка на объект окна
         */
        frontend::MainWindow&   get_window() const;
    private:
        /**
         * @brief Окно с игрой
         */
        std::unique_ptr<frontend::MainWindow>   _window;
        /**
         * @brief Игровое поле
         */
        std::unique_ptr<GameField>              _field;
        /**
         * @brief Количество перемещений фишек
         */
        uint32_t                                _steps;
    };
}

#endif
