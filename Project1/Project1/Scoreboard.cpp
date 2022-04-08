#include "Scoreboard.h"
map <tgui::String, vector<vector<tgui::String>>> mp; 

void onComboBoxSelected(Group& group_scoreboard , tgui::String getSelectedItem)
{
    if (getSelectedItem == "All Semesters")
    {
        group_scoreboard.get<tgui::ListView>("ListView1")->removeAllItems();
        for (auto t : mp)
        {
            group_scoreboard.get<tgui::ListView>("ListView1")->addMultipleItems(t.second);

        }
    }
    else {
        group_scoreboard.get<tgui::ListView>("ListView1")->removeAllItems();
        group_scoreboard.get<tgui::ListView>("ListView1")->addMultipleItems(mp[getSelectedItem]);
    }
}

void onScoreboardSelected(Group& group_scoreboard, Group& group_student)
{
    group_scoreboard.setVisible(true);
    group_student.setVisible(false);    
}

void init_group(Group& group_scoreboard)
{
    group_scoreboard.loadWidgetsFromFile("ScoreBoardForm.txt");
}
void loadwidget(Group& group_scoreboard, queue<pair<SchoolYear*, int>> curSchoolYear)
{
    init_group(group_scoreboard);
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("Semester" ,200); 
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("Course ID" ,100 ); 
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("Course" ,300 ); 
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("Credit" ,90 ); 
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("ABC" ,50 ); 
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("10" ,50 ); 
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("4" ,50 ); 
    while (!curSchoolYear.empty())
    {
        SchoolYear* cSYear = curSchoolYear.front().first;
        int sID = curSchoolYear.front().second;
        curSchoolYear.pop();


        string strID = "";
        while (sID) {
            strID += (char)((sID % 10) + '0');
            sID /= 10;
        }
        reverse(strID.begin(), strID.end());
        tgui::String curYears = tgui::String(cSYear->startYear) + '-' + tgui::String(cSYear->endYear);

        int curSemester = 4;

        tgui::String curDirectory = "SchoolYears/" + tgui::String(cSYear->startYear) + "-" + tgui::String(cSYear->endYear);

        for (Semester* i = cSYear->nowSemester; i; i = i->nextSemester) {
            curSemester--;
            group_scoreboard.get<tgui::ComboBox>("ComboBox1")->addItem("Semester " + tgui::String(curSemester) + "/" + tgui::String(cSYear->startYear) + "-" + tgui::String(cSYear->endYear));
            group_scoreboard.get<tgui::ComboBox>("ComboBox1")->setSelectedItem("Semester " + tgui::String(curSemester) + "/" + tgui::String(cSYear->startYear) + "-" + tgui::String(cSYear->endYear));
            tgui::String curSemesterStr = "Semester " + tgui::String(curSemester);
            string curDir = curDirectory.toStdString() + "/" + "Semester" + (char)(curSemester + '0') + "/Courses/";
            for (Course* j = i->nowCourse; j; j = j->nextCourse) {

                vector<tgui::String> tmp;
                if (j->findStudent(curDir, strID)) {
                    tgui::String item = j->courseName;
                    tmp = { curSemesterStr + "/" + curYears, tgui::String(j->courseID) , item , tgui::String(j->credits) ,"A" , tgui::String(j->score) , "4" };
                    mp[curSemesterStr + "/" + curYears].push_back(tmp);
                    group_scoreboard.get<tgui::ListView>("ListView1")->addItem(tmp);
                }
            }
        }
    }
    group_scoreboard.get<tgui::ComboBox>("ComboBox1")->addItem("All Semesters"); 
    group_scoreboard.get<tgui::ComboBox>("ComboBox1")->setSelectedItem("All Semesters"); 
    group_scoreboard.get<tgui::ComboBox>("ComboBox1")->onItemSelect(&onComboBoxSelected , ref(group_scoreboard));

}