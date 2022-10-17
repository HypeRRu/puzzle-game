#include "include/backend/game.h"

#include "include/frontend/mainwindow.h"

using namespace backend;

Game::Game():
    _window{std::make_unique<frontend::MainWindow>()},
    _field{std::make_unique<GameField>(*this, 5, 5)},
    _steps{0}
{}


void Game::run()
{
    this->_window->show();
}


void Game::game_over()
{
    this->_window->game_over(this->_steps);
}


GameField& Game::get_field() const
{
    return *this->_field.get();
}


frontend::MainWindow& Game::get_window() const
{
    return *this->_window.get();
}


uint32_t Game::steps_count() const
{
    return this->_steps;
}


void Game::inc_steps()
{
    ++this->_steps;
}
