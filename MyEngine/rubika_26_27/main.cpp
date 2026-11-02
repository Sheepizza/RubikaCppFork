#include <Entity.h>

#include <SFML/Graphics.hpp>
#include <Imgui/imgui.h>
#include <Imgui/imgui-SFML.h>

#include <Globals.h>
#include <Profiler.h>
#include <Logger.h>
#include <DebugMgr.h>
#include <Scene.h>
#include <SceneMgr.h>
#include <TextureMgr.h>
#include <InputMgr.h>
#include <RenderComponent.h>
#include <TransformComponent.h>
#include <Sprite.h>
#include <Rectangle.h>

void CreateInputs(Entity* e)
{
    TransformComponent* t = e->AddComponent<TransformComponent>();

    gData.InputMgr->CreateInputAction("Up");
    gData.InputMgr->BindAction("Up", sf::Keyboard::Key::Z);
    auto up = [e](float input) {e->Move(0, -0.2f * input); };
    std::function<void(float)> MoveUp = up;
    gData.InputMgr->RegisterCallback("Up", "Move Up", MoveUp, e);

    gData.InputMgr->CreateInputAction("Down");
    gData.InputMgr->BindAction("Down", sf::Keyboard::Key::S);
    auto down = [e](float input) {e->Move(0, 0.2f * input); };
    std::function<void(float)> MoveDown = down;
    gData.InputMgr->RegisterCallback("Down", "Move Down", MoveDown, e);

    gData.InputMgr->CreateInputAction("Right");
    gData.InputMgr->BindAction("Right", sf::Keyboard::Key::D);
    auto right = [e](float input) {e->Move(0.2f * input, 0); };
    std::function<void(float)> MoveRight = right;
    gData.InputMgr->RegisterCallback("Right", "Move Right", MoveRight, e);

    gData.InputMgr->CreateInputAction("Left");
    gData.InputMgr->BindAction("Left", sf::Keyboard::Key::Q);
    auto left = [e](float input) {e->Move(-0.2f * input, 0); };
    std::function<void(float)> MoveLeft = left;
    gData.InputMgr->RegisterCallback("Left", "Move Left", MoveLeft, e);
}

void CreateScene()
{
    Scene mainScene = Scene("MainScene");

    Entity* e = new Entity("Isaac");

    mainScene.AddEntity(e);

    gData.SceneMgr->AddNewScene(mainScene);

    gData.SceneMgr->SetActiveScene("MainScene");

    RenderComponent* r = e->AddComponent<RenderComponent>();

    Sprite* sprite = r->AddDrawable<Sprite>();

    sprite->SetTextureAndSprite("IsaacSprite", "Body_Vertical");

    /*StaticTile* staticTile = r->AddDrawable<StaticTile>();

    staticTile->SetTextureAndStaticTile("Basement", "Corner_Top_Left");*/

    CreateInputs(e);
}

int main()
{
    gData.Init();

    CreateScene();

    sf::RenderWindow window(sf::VideoMode({ 1080, 720 }), "SFML works!", sf::State::Windowed);

    ImGui::SFML::Init(window);

    /*Logger::Info("This is an info message. That is useful");
    Logger::Warning("This is a warning message. Should I worry?");
    Logger::Error("This is an error message. Oh sh*t!!");*/

    sf::Clock clock;
    clock.restart();

    while (window.isOpen())
    {
        gData.IncrementFrameCount();

        PROFILER_EVENT_BEGIN(PROFILER_COLOR_BLACK, "Frame %llu", gData.FrameCount);

        int deltaTimeMicroS = clock.getElapsedTime().asMicroseconds();
        float fDeltaTimeMS = (float)deltaTimeMicroS / 1000.f;
        float fDeltaTimeS = fDeltaTimeMS / 1000.f;
        sf::Time imGuiTime = clock.restart();

        PROFILER_EVENT_BEGIN(PROFILER_COLOR_BLUE, "Event & Input");

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

#ifdef _USE_IMGUI
            ImGui::SFML::ProcessEvent(window, event.value());
#endif
        }

        PROFILER_EVENT_END();

        PROFILER_EVENT_BEGIN(PROFILER_COLOR_RED, "Update");
#ifdef _USE_IMGUI
        ImGui::SFML::Update(window, imGuiTime);
#endif
        // sample
        //ImGui::ShowDemoWindow();
        //Logger::DrawLogger();
        gData.DebugMgr->Draw();

        PROFILER_EVENT_END();

        PROFILER_EVENT_BEGIN(PROFILER_COLOR_GREEN, "Draw");
        window.clear();

#ifdef _USE_IMGUI
        ImGui::SFML::Render(window);
#endif

        float deltaT = clock.getElapsedTime().asSeconds();

        gData.InputMgr->Update(deltaT);

        if (gData.SceneMgr->ActiveScene != nullptr)
        {
            gData.SceneMgr->ActiveScene->Update(deltaT);
            gData.SceneMgr->ActiveScene->Draw(window);
        }

        window.display();

        PROFILER_EVENT_END();

        PROFILER_EVENT_END();

    }

    ImGui::SFML::Shutdown();

    gData.Shut();
    gData.Destroy();

    return 0;
}