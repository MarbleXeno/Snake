#pragma once
#include <Farfocel/Core/Runtime.hpp>
#include <Farfocel/Managers/AnimationManager.hpp>
#include <Farfocel/Managers/ResourcesManager.hpp>
#include <Farfocel/Managers/InputManager.hpp>
#include <Farfocel/Managers/ScenesManager.hpp>
#include <Farfocel/Utils/GUI/Widgets/Text.hpp>

#include "Scenes/Menu.hpp"

namespace gm{
    class SnakeGame : public fr::Runtime{
        public:
            SnakeGame();
            ~SnakeGame();

            void Start();
            void HandleEvents();
            void HandleInput();
            void Update();
            void Render();


        private:
            fr::ScenesManager mScenesManager;

            sf::Font mFont;
            
    };
} // namespace sb
