#include "Scoreboard.h"

void onScoreboardSelected(Group& group_scoreboard , Group& group_student)
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
            tgui::String curSemesterStr = "Semester " + tgui::String(curSemester);
            string curDir = curDirectory.toStdString() + "/" + "Semester" + (char)(curSemester + '0') + "/Courses/";
            //group_course.get<tgui::TreeView>("TreeView1")->addItem({ curYears, curSemesterStr });
            for (Course* j = i->nowCourse; j; j = j->nextCourse) {


                if (j->findStudent(curDir, strID)) {
                    tgui::String item = j->courseName;
                    //group_course.get<tgui::TreeView>("TreeView1")->addItem({ curYears, curSemesterStr, item });
                }
            }

        }
	}
}