#include "CreateRegistration.h"
#include "Scoreboard.h"
void onCreateSelected(Group& group_create, Group& group_student)
{
    group_create.setVisible(true);
    group_student.setVisible(false);
}

void init_group_create(Group& group_create)
{
    group_create.loadWidgetsFromFile("CreateForm.txt");
}
void loadcreatewidget(Group& group_create)
{
    init_group_create(group_create);

}