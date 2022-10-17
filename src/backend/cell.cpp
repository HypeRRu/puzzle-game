#include "include/backend/cell.h"

#include "include/backend/game_field.h"
#include "include/frontend/cell_sprite.h"

using namespace backend;

Cell::Cell(GameField& owner, int8_t x, int8_t y, Type type):
    _type{type},
    _sprite{std::make_shared<frontend::CellSprite>(*this)},
    _owner{owner}
{
    this->set_x(x);
    this->set_y(y);
}


void Cell::set_x(int8_t x)
{
    this->_pos_x = x;
    this->get_sprite()->move();
}


int8_t Cell::get_x() const
{
    return this->_pos_x;
}


void Cell::set_y(int8_t y)
{
    this->_pos_y = y;
    this->get_sprite()->move();
}


int8_t Cell::get_y() const
{
    return this->_pos_y;
}


Cell::Type Cell::get_type() const
{
    return this->_type;
}


std::shared_ptr<frontend::CellSprite> Cell::get_sprite() const
{
    return this->_sprite;
}


bool Cell::move(int8_t dx, int8_t dy)
{
    return this->_owner.move_cell(this->_pos_x, this->_pos_y, dx, dy);
}
