#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

void login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password)
{
    std::cout << "Username: " << username->getText() << std::endl;
    std::cout << "Password: " << password->getText() << std::endl;
}

void updateTextSize(tgui::BackendGui& gui)
{
    // Update the text size of all widgets in the gui, based on the current window height
    const float windowHeight = gui.getView().getRect().height;
    gui.setTextSize(static_cast<unsigned int>(0.02f * windowHeight)); // 2% of height
}

void loadWidgets(tgui::BackendGui& gui)
{
    gui.loadWidgetsFromFile("form.txt");
    // Specify an initial text size instead of using the default value
    updateTextSize(gui);

    // We want the text size to be updated when the window is resized
    gui.onViewChange([&gui] { updateTextSize(gui); });
    gui.get<tgui::Button>("Button1")->onPress(&login, gui.get<tgui::EditBox>("EditBox1"), gui.get<tgui::EditBox>("EditBox2"));
 }

bool runExample(tgui::BackendGui& gui)
{
    try
    {
        loadWidgets(gui);
        return true;
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        return false;
    }
}

int main()
{
    sf::RenderWindow window{ {1300, 800}, "TGUI example - SFML_GRAPHICS backend" };

    tgui::Gui gui{ window };
    if (runExample(gui))
        gui.mainLoop();
}