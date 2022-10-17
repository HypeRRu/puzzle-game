#include <QApplication>

#include "include/backend/game.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    /* Запуск игры */
    backend::Game game;
    game.run();
    return app.exec();
}
