//#include <TGUI/TGUI.hpp>
//#include <TGUI/Backend/SFML-Graphics.hpp>
//
//#include "AccountList.h"
//
//void login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password, Account*& accounts)
//{
//    //std::cout << "Username: " << username->getText() << std::endl;
//    //std::cout << "Password: " << password->getText() << std::endl;
//
//    tgui::String usrnme = username->getText();
//    tgui::String psswrd = password->getText();
//
//    bool check = findStudent(accounts, usrnme.toStdString(), psswrd.toStdString());
//    if (check) {
//        std::cout << "Chuan roi do\n";
//    }
//    else {
//        std::cout << "Sai roi man\n";
//    }
//}
//
//void updateTextSize(tgui::BackendGui& gui)
//{
//    // Update the text size of all widgets in the gui, based on the current window height
//    const float windowHeight = gui.getView().getRect().height;
//    gui.setTextSize(static_cast<unsigned int>(0.02f * windowHeight)); // 2% of height
//}
//
//void loadWidgets(tgui::BackendGui& gui, Account*& accounts)
//{
//    gui.loadWidgetsFromFile("form.txt");
//    // Specify an initial text size instead of using the default value
//    updateTextSize(gui);
//
//    // We want the text size to be updated when the window is resized
//    gui.onViewChange([&gui] { updateTextSize(gui); });
//    gui.get<tgui::Button>("Button1")->onPress(&login, gui.get<tgui::EditBox>("EditBox1"), gui.get<tgui::EditBox>("EditBox2"), std::ref(accounts));
//}
//
//bool runExample(tgui::BackendGui& gui, Account*& accounts)
//{
//    try
//    {
//        loadWidgets(gui, accounts);
//        return true;
//    }
//    catch (const tgui::Exception& e)
//    {
//        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
//        return false;
//    }
//}
//
//int main()
//{
//    sf::RenderWindow window{ {1300, 800}, "TGUI example - SFML_GRAPHICS backend" };
//
//    Account* accounts = nullptr;
//    loadAccount(accounts);
//
//    tgui::Gui gui{ window };
//    if (runExample(gui, accounts))
//        gui.mainLoop();
//}

#include "Core.h"
int main()
{
	run();
}
