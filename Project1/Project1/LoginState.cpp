#include "LoginState.h"

void login(BackendGui& gui, tgui::EditBox::Ptr username, tgui::EditBox::Ptr password, Account* accounts_student, Account* accounts_teacher)
{
    //cerr << accounts << '\n';
    //std::cout << "Username: " << username->getText() << std::endl;
    //std::cout << "Password: " << password->getText() << std::endl;
    tgui::String usrnme = username->getText();
    tgui::String psswrd = password->getText();
    //cout << usrnme.toStdString();
    bool checkStudent = findStudent(accounts_student, usrnme.toStdString(), psswrd.toStdString());
    bool checkTeacher = findTeacher(accounts_teacher, usrnme.toStdString(), psswrd.toStdString());
    if (checkStudent) {
        //std::cout << "Chuan roi do\n";
        run_mainmenu(gui, usrnme);
    }
    else if (checkTeacher) {
        cout << "Chuan rui\n";
        run_mainmenu_teacher(gui , usrnme);
    }
    else {
        gui.get<tgui::TextArea>("TextArea1")->showWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
    }
}

void updateTextSize(tgui::BackendGui& gui)
{
    // Update the text size of all widgets in the gui, based on the current window height
    const float windowHeight = gui.getView().getRect().height;
    gui.setTextSize(static_cast<unsigned int>(0.02f * windowHeight)); // 2% of height
}

void loadWidgets(tgui::BackendGui& gui, Account*& accounts_student, Account*& accounts_teacher)
{
    gui.loadWidgetsFromFile("LoginForm.txt");
    // Specify an initial text size instead of using the default value
    updateTextSize(gui);

    // We want the text size to be updated when the window is resized
    gui.onViewChange([&gui] { updateTextSize(gui); });
    bool ok = false;
    //cerr << accounts << '\n';
    gui.get<tgui::TextArea>("TextArea1")->hideWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
    gui.get<tgui::Button>("Button1")->onPress(&login, ref(gui), gui.get<tgui::EditBox>("EditBox1"), gui.get<tgui::EditBox>("EditBox2"), accounts_student, accounts_teacher);
}

bool run_login(BackendGui& gui)
{
    try
    {
        Account* accounts_student = nullptr;
        Account* accounts_teacher = nullptr;
        loadAccountStudent(accounts_student);
        loadAccountTeacher(accounts_teacher);

        loadWidgets(gui, accounts_student , accounts_teacher);
        //auto tview = tgui::TreeView::create();
        //tview->setSize("&.size");
        //tview->addItem({ "This", "Is", "Similar", "To", "MenuBars" });
        //tview->addItem({ "Optional", "Parameter", "createParents" }, true);
        //gui.add(tview);
        return true;
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        return false;
    }
}
