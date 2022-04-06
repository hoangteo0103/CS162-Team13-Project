#include "LoginState.h"

void saveToFile(tgui::String usrnme, tgui::String psswrd)
{
    ofstream fout;
    fout.open("Remember Username.txt"); 
    fout << usrnme.toStdString() << endl;
    fout << psswrd.toStdString();
}

bool loadFromFile(tgui::String& usrnme, tgui::String& psswrd)
{
    ifstream fin;
    fin.open("Remember Username.txt");
    cout << 1;

    if (fin.eof()) return false;
    string user, pass; 
    fin >> user >> pass;
    usrnme = tgui::String(user); 
    psswrd = tgui::String(pass); 
    return true;
}

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
    if (checkStudent ) {
        //std::cout << "Chuan roi do\n";
        if (gui.get<tgui::CheckBox>("CheckBox_RememberUser")->isChecked())
            saveToFile(usrnme, psswrd);
        run_mainmenu(gui, usrnme);
    }
    else if (checkTeacher) {
        //cout << "Chuan rui\n";
        run_mainmenu_teacher(gui , usrnme);
    }
    else {
        gui.get<tgui::TextArea>("TextArea_WrongLogin")->showWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
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
    tgui::String user, pass;
    if (loadFromFile(user, pass))
    {
        gui.get<tgui::CheckBox>("CheckBox_RememberUser")->setChecked(true);
        gui.get<tgui::EditBox>("EditBox_Usename")->setText(user);
        gui.get<tgui::EditBox>("EditBox_Password")->setText(pass);
    }
    // We want the text size to be updated when the window is resized
    gui.onViewChange([&gui] { updateTextSize(gui); });
    bool ok = false;
    //cerr << accounts << '\n';
    gui.get<tgui::TextArea>("TextArea_WrongLogin")->hideWithEffect(tgui::ShowEffectType::Fade, sf::milliseconds(0));
    gui.get<tgui::Button>("Button_Login")->onPress(&login, ref(gui), gui.get<tgui::EditBox>("EditBox_Usename"), gui.get<tgui::EditBox>("EditBox_Password"), accounts_student, accounts_teacher);
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
