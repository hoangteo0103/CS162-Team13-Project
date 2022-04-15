#include "CreateRegistration.h"
#include "Scoreboard.h"
void onCreateSelected(Group& group_create, Group& group_student)
{
    group_create.setVisible(true);
    group_student.setVisible(false);
}

void onLoad(Group& group_create)
{
    string file_path = Get_path(); 
    int pos = 0 ; 
    for (int i = file_path.size() - 1; i >= 0; i--)
    {
        if (file_path[i] == ':')
            pos = i;
    }
    file_path = file_path.substr(pos + 2);
    group_create.get<Label>("File")->setText(file_path);
}

void init_group_create(Group& group_create)
{
    group_create.loadWidgetsFromFile("CreateForm.txt");
}
void loadcreatewidget(Group& group_create)
{
    init_group_create(group_create);
    group_create.get<tgui::Button>("Load")->onClick(&onLoad , ref(group_create));

}