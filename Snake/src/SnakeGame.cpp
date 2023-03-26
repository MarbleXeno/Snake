
#include "SnakeGame.hpp"

namespace gm{
    SnakeGame::SnakeGame()
    {
        Init("Snake", 600, 700, 60, fr_window::WindowDecorations::NoResize);
        StartUpdateLoop();
    }

    SnakeGame::~SnakeGame(){

    }

    void SnakeGame::Start(){
        mFont.loadFromFile("res/font.ttf");


        mScenesManager.Add(new gm::Menu("menu", renderer, mScenesManager, mFont, eventManager));
    }

    void SnakeGame::HandleEvents(){
        
    }

    void SnakeGame::HandleInput(){
        
    }

    void SnakeGame::Update(){
        mScenesManager.Update();
    }

    void SnakeGame::Render(){
        mScenesManager.Render();
    }
}