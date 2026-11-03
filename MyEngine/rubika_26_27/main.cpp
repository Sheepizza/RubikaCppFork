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
#include <DynamicColliderComponent.h>
#include <Sprite.h>
#include <Rectangle.h>
#include <Player.h>
#include <Obstacle.h>

void CreateInputs(Player* player)
{
    gData.InputMgr->RegisterCallback("Up", "Move Up", [player](float input) {player->Move(0, -0.1f * input); }, player);

    gData.InputMgr->RegisterCallback("Down", "Move Down", [player](float input) {player->Move(0, 0.1f * input); }, player);

    gData.InputMgr->RegisterCallback("Right", "Move Right", [player](float input) {player->Move(0.1f * input, 0); }, player);

    gData.InputMgr->RegisterCallback("Left", "Move Left", [player](float input) {player->Move(-0.1f * input, 0); }, player);

    gData.InputMgr->RegisterCallback("DisplayColliders", "DisplayColliders", [](float) {gData.SceneMgr->DisplayColliders(true); }, player);

    gData.InputMgr->RegisterCallback("HideColliders", "HideColliders", [](float) {gData.SceneMgr->DisplayColliders(false); }, player);
}

void CreateScene()
{
    Scene mainScene = Scene("MainScene");

    int length = 11;
	int height = 6;

#pragma region Enviro

    Entity* enviro = new Entity("Basement");

    mainScene.AddEntity(enviro);

	enviro->AddComponent<TransformComponent>();
    RenderComponent* enviroR = enviro->AddComponent<RenderComponent>();

	StaticTile* corner_top_left = enviroR->AddDrawable<StaticTile>(0, 0);
	corner_top_left->SetTextureAndStaticTile("Basement", "Corner_Top_Left");

    for (size_t i = 0; i < length; i++)
    {
        StaticTile* wall_up = enviroR->AddDrawable<StaticTile>(52 * (i+ 1), 0);
        wall_up->SetTextureAndStaticTile("Basement", "Wall_Classic_Up");

        StaticTile* wall_down = enviroR->AddDrawable<StaticTile>(52 * (i + 1), 52 * (height + 1));
        wall_down->SetTextureAndStaticTile("Basement", "Wall_Classic_Down");
    }

    StaticTile* corner_top_right = enviroR->AddDrawable<StaticTile>(52 * (length + 1), 0);
    corner_top_right->SetTextureAndStaticTile("Basement", "Corner_Top_Right");

    for (size_t i = 0; i < height; i++)
    {
        StaticTile* wall_left = enviroR->AddDrawable<StaticTile>(0, 52 * (i + 1));
        wall_left->SetTextureAndStaticTile("Basement", "Wall_Classic_Left");

        StaticTile* wall_right = enviroR->AddDrawable<StaticTile>(52 * (length + 1), 52 * (i + 1));
        wall_right->SetTextureAndStaticTile("Basement", "Wall_Classic_Right");
    }

    StaticTile* corner_bot_left = enviroR->AddDrawable<StaticTile>(0, 52 * (height + 1));
    corner_bot_left->SetTextureAndStaticTile("Basement", "Corner_Bottom_Left");

    StaticTile* corner_bot_Right = enviroR->AddDrawable<StaticTile>(52 * (length + 1), 52 * (height + 1));
    corner_bot_Right->SetTextureAndStaticTile("Basement", "Corner_Bottom_Right");

    StaticTile* ground1 = enviroR->AddDrawable<StaticTile>(52, 52);
    ground1->SetTextureAndStaticTile("Basement", "Ground_Line_Up");

    for (size_t i = 0; i < height - 4; i++)
    {
        StaticTile* ground2 = enviroR->AddDrawable<StaticTile>(52, 104 + (52 * i * 2));
        ground2->SetTextureAndStaticTile("Basement", "Ground_Line_Mid_1");

        StaticTile* ground3 = enviroR->AddDrawable<StaticTile>(52, 156 + (52 * i * 2));
        ground3->SetTextureAndStaticTile("Basement", "Ground_Line_Mid_2");
    }

    StaticTile* ground2 = enviroR->AddDrawable<StaticTile>(52, 52 * (height - 1));
    ground2->SetTextureAndStaticTile("Basement", "Ground_Line_Mid_1");

    StaticTile* ground = enviroR->AddDrawable<StaticTile>(52, 52 * height);
    ground->SetTextureAndStaticTile("Basement", "Ground_Line_Down");

#pragma endregion

    Player* player = new Player("Isaac");

    mainScene.AddEntity(player);

    mainScene.AddEntity(new Obstacle({ 407, 73 }, "Obstacle1"));

    mainScene.AddEntity(new Obstacle({ 62, 201 }, "Obstacle2"));

    mainScene.AddEntity(new Obstacle({ 553, 150 }, "Obstacle2"));

    gData.SceneMgr->AddNewScene(mainScene);

    gData.SceneMgr->SetActiveScene("MainScene");

    CreateInputs(player);
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
        gData.Update(fDeltaTimeS);


        PROFILER_EVENT_END();

        PROFILER_EVENT_BEGIN(PROFILER_COLOR_GREEN, "Draw");
        window.clear();

        gData.SceneMgr->Draw(window);
        gData.DebugMgr->Draw();

#ifdef _USE_IMGUI
        ImGui::SFML::Render(window);
#endif

        window.display();

        PROFILER_EVENT_END();

        PROFILER_EVENT_END();

    }

    ImGui::SFML::Shutdown();

    gData.Shut();
    gData.Destroy();

    return 0;
}