#include "include/frontend/cell_sprite.h"

#include <map>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

using namespace frontend;

CellSprite::CellSprite(backend::Cell& object):
    _width{64}, _height{64},
    _x_off{0}, _y_off{0},
    _object{object}
{
    /* Задание текстуры исходя из типа клетки */
    switch (object.get_type())
    {
        case backend::Cell::Type::Free:
            this->_texture = "free-cell";
            break;
        case backend::Cell::Type::Blocked:
            this->_texture = "blocked-cell";
            break;
        case backend::Cell::Type::Yellow:
            this->_texture = "yellow-cell";
            this->setFlags(QGraphicsItem::ItemIsMovable);
            break;
        case backend::Cell::Type::Orange:
            this->_texture = "orange-cell";
            this->setFlags(QGraphicsItem::ItemIsMovable);
            break;
        case backend::Cell::Type::Red:
            this->_texture = "red-cell";
            this->setFlags(QGraphicsItem::ItemIsMovable);
            break;
        default:
            this->_texture = "free-cell";
            break;
    }
    this->move();
}


void CellSprite::set_offset(int8_t x_off, int8_t y_off)
{
    this->_x_off = x_off;
    this->_y_off = y_off;
    this->move();
}


void CellSprite::move()
{
    this->setPos(
        this->_width    * this->_object.get_x() + this->_x_off,
        this->_height   * this->_object.get_y() + this->_y_off
    );
}


QRectF CellSprite::boundingRect() const
{
    return QRectF(
        -this->_width / 2, -this->_height / 2,
        this->_width, this->_height
    );
}


void CellSprite::paint(
    QPainter *painter,
    const QStyleOptionGraphicsItem *,
    QWidget *
)
{
    /* TODO: textures drawing */

    /* TEMP */
    std::map<std::string, QColor> colors;
    colors.emplace(std::make_pair(
        "yellow-cell", QColor(246, 236, 25)
    ));
    colors.emplace(std::make_pair(
        "orange-cell", QColor(230, 112, 7)
    ));
    colors.emplace(std::make_pair(
        "red-cell", QColor(242, 37, 17)
    ));
    colors.emplace(std::make_pair(
        "free-cell", QColor(230, 230, 230)
    ));
    colors.emplace(std::make_pair(
        "blocked-cell", QColor(121, 121, 121)
    ));

    painter->setPen(Qt::black);
    painter->setBrush(colors.at(this->_texture));

    QPolygon polygon;
    polygon << QPoint(-this->_width / 2, -this->_height / 2)
            << QPoint(-this->_width / 2,  this->_height / 2)
            << QPoint( this->_width / 2,  this->_height / 2)
            << QPoint( this->_width / 2, -this->_height / 2);
    /* Отрисовка текстуры */
    painter->drawPolygon(polygon);
}


void CellSprite::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
}


void CellSprite::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Текущее положение клетки */
    uint16_t cx = this->_object.get_x() * this->_width;
    uint16_t cy = this->_object.get_y() * this->_height;
    /* Положение мыши */
    int16_t dx = (event->scenePos().x() - cx) / this->_width;
    int16_t dy = (event->scenePos().y() - cy) / this->_height;
    /* Если смещение происходит
    по вертикали или горизонтали на 1 клетку, оно разрешено */
    if (std::abs(dx) + std::abs(dy) == 1)
        this->_object.move(dx, dy);
}


void CellSprite::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
}
