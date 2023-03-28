#include "Farfocel/Core/Runtime.hpp"

namespace fr{
    Runtime::Runtime()
        : mRenderWindow(nullptr), mEvent(nullptr), mDrawImgui(false), mInputManager(){

    }

    Runtime::~Runtime(){
        ImGui::SFML::Shutdown();
    }

    void Runtime::Init(){
        #ifdef _WIN32
	        system("cls");
        #endif

        renderer.CreateWindow();

        InitFarfocel();

        Start();
    }

    void Runtime::Init(const std::string& windowTitle, const uint16_t& windowWidth, const uint16_t& windowHeight, const uint16_t& maxFramerate, const fr_window::WindowDecorations& windowDecorations){
        #ifdef _WIN32
	        system("cls");
        #endif

        renderer.CreateWindow(windowTitle, windowWidth, windowHeight, maxFramerate, windowDecorations);

        InitFarfocel();
        Start();
    }

    void Runtime::InitFarfocel() {
        mRenderWindow = &renderer.GetRenderWindow();
        mEvent = &renderer.GetWindowEvent();

        // Event Manager setup
        eventManager = fr::EventManager(renderer.GetRenderWindow(), renderer.GetWindowEvent());
        mInputManager = fr::InputManager(renderer.GetRenderWindow());
        
        eventManager.AddBinding(sf::Event::Closed, true, [=]() { renderer.GetRenderWindow().close(); });
        eventManager.AddBinding(sf::Event::Resized, true, [=]() { renderer.ResizeView({ renderer.GetWindowEvent().size.width, renderer.GetWindowEvent().size.height }); });

        mInputManager.Bind(sf::Keyboard::Num0, false, [=]() {mDrawImgui = !mDrawImgui; });

        ImGui::SFML::Init(renderer.GetRenderWindow());
        
    }

    void Runtime::StartUpdateLoop(){
        while (renderer.GetRenderWindow().isOpen()){

            eventManager.Update();
            mInputManager.UpdateKeyboard();
            HandleEvents();

            HandleInput();

            ImGui::SFML::Update(renderer.GetRenderWindow(), renderer.GetDeltaTime());
            Update();

            renderer.GetRenderWindow().clear(sf::Color::Cyan);
            Render();

            if(mDrawImgui)
                ImGui::SFML::Render(renderer.GetRenderWindow());
            
            renderer.GetRenderWindow().display();
        }
    }
    
}