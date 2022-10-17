#include "include/backend/game_field.h"

#include "include/backend/game.h"
#include "include/frontend/mainwindow.h"
#include "include/frontend/cell_sprite.h"

using namespace backend;

GameField::GameField(Game& game, uint8_t width, uint8_t height):
    _width{width}, _height{height},
    _game{std::ref(game)},
    _random_device{},
    _random_engine{_random_device()}
{
    /* Настройка количества необходимых фишек различных цветов */
    this->init_generator();
    /* Задание расстановки фишек и блоков */
    this->init_field();
}


void GameField::init_generator()
{
    /* Цвета и количество фишек, которые необходимо разместить */
    this->_unplaced_cells.emplace_back(
        std::make_pair(Cell::Type::Yellow, this->_height)
    );
    this->_unplaced_cells.emplace_back(
        std::make_pair(Cell::Type::Orange, this->_height)
    );
    this->_unplaced_cells.emplace_back(
        std::make_pair(Cell::Type::Red, this->_height)
    );
    /* Общее количество фишек */
    this->_unplaced_count = -1 + this->_height *
        static_cast<uint8_t>(this->_unplaced_cells.size());
}


void GameField::init_field()
{
    /* Добавление информации о цветах колонок */
    this->setup_columns();
    /* Задание размеров поля */
    this->_field.reserve(this->_width * this->_height);
    /* Генерация конфигурации */
    for (uint8_t y = 0; y < this->_height; ++y)
    {
        for (uint8_t x = 0; x < this->_width; ++x)
        {
            Cell::Type type = Cell::Type::Free;
            if (x % 2)
            {
                /* Нечетные ряды изначально содержат
                пустые либо заблокированные клетки */
                if (y % 2) // y нечетный
                    type = Cell::Type::Free; // клетка свободна
                else // y четный
                    type = Cell::Type::Blocked; // клетка заблокирована
            } else // x четный
            {
                /* Генерируется случайный цвет фишки */
                type = this->generate_cell_color();
            }
            /* Добавление клетки */
            this->_field.emplace_back(
               std::make_unique<Cell>(*this, x, y, type)
            );
            this->get_game().get_window().add_sprite(
                this->_field.back()->get_sprite()
            );
        }
    }
}


Cell::Type GameField::generate_cell_color()
{
    /* Генератор случайного числа */
    std::uniform_int_distribution<uint16_t> distribution(
        0, this->_unplaced_count--
    );
    /* Случайное число */
    uint16_t result = distribution(this->_random_engine);
    /* Получение цвета фишки */
    for (auto& unplaced: this->_unplaced_cells)
    {
        if (result < unplaced.second)
        {
            --unplaced.second;
            return unplaced.first;
        }
        result -= unplaced.second;
    }
    return Cell::Type::Free;
}


bool GameField::move_cell(
    int8_t from_x, int8_t from_y,
    int8_t dx, int8_t dy
)
{
    /* Клетка, в которую перемещается фишка */
    int8_t dest_x = from_x + dx;
    int8_t dest_y = from_y + dy;
    /* Проверка выхода за границы поля */
    if (
        dest_x < 0 || dest_x >= this->_width  ||
        dest_y < 0 || dest_y >= this->_height
    )
        return false;
    /* Индексы в массиве клеток */
    uint16_t from   = from_y * this->_width + from_x;
    uint16_t to     = dest_y * this->_width + dest_x;
    /* Проверка возможности перемещения фишки */
    if (
        /* Клетка должна быть свободна */
        this->_field.at(to)->get_type()     == Cell::Type::Free &&
        /* Перемещаемый объект не может быть блоком */
        this->_field.at(from)->get_type()   != Cell::Type::Blocked
    )
    {
        /* Изменение координат клеток */
        this->_field.at(from)->set_x(dest_x);
        this->_field.at(from)->set_y(dest_y);
        this->_field.at(to)->set_x(from_x);
        this->_field.at(to)->set_y(from_y);
        /* Изменение позиций клеток на поле */
        std::swap(this->_field.at(from), this->_field.at(to));
        /* Увеличение счетчика шагов */
        this->get_game().inc_steps();
        /* Проверка расстановки */
        if (this->check_arrangement())
            this->get_game().game_over();
        return true;
    }
    return false;
}


bool GameField::check_arrangement() const
{
    /* Проход по всем колонкам с цветами */
    for (uint8_t column = 0; column < this->_width; column += 2)
    {
        /* Получение цвета колонки */
        const Cell::Type check_type =
            this->_unplaced_cells.at(column / 2).first;
        for (uint8_t row = 0; row < this->_height; ++row)
        {
            /* Проверка элементов колонки */
            uint16_t index = row * this->_width + column;
            if (this->_field.at(index)->get_type() != check_type)
                return false;
        }
    }
    return true;
}


Game& GameField::get_game() const
{
    return this->_game.get();
}


void GameField::setup_columns()
{
    /* Задание количества цветных колонок */
    this->_columns_colors.reserve(this->_unplaced_cells.size());
    /* Проход по всем цветам */
    for (uint8_t i = 0; i < this->_unplaced_cells.size(); ++i)
    {
        /* Добавление клетки с цветом колонки */
        this->_columns_colors.emplace_back(
            std::make_unique<Cell>(
                *this,
                2 * i, -1,
                this->_unplaced_cells.at(i).first
            )
        );
        /* Данная клетка не может перемещаться */
        auto sprite = this->_columns_colors.back()->get_sprite();
        sprite->setFlags(sprite->flags() & ~QGraphicsItem::ItemIsMovable);
        /* Задание отступа снизу */
        sprite->set_offset(0, -16);
        this->get_game().get_window().add_sprite(
            this->_columns_colors.back()->get_sprite()
        );
    }
}
