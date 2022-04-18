#include "TeacherScoreboard.h"
map <tgui::String, vector<vector<tgui::String>>> mpx;    
map <tgui::String, vector<vector<tgui::String>> > mpc;
void init_scoreboard_group(Group& group_scoreboard)
{
    group_scoreboard.loadWidgetsFromFile("TeacherScoreboardForm.txt");
}

void onComboBoxSemesterSelected(Group& group_scoreboard, tgui::String getSelectedItem)
{
    if (getSelectedItem == "All Semesters")
    {
        group_scoreboard.get<tgui::ListView>("ListView1")->removeAllItems();
        group_scoreboard.get<tgui::ComboBox>("ComboBox2")->setSelectedItem("All Courses");
        int width = 0;
        for (auto t : mpx)
        {
            cout << t.second.size() << endl;
            width += t.second.size();
            group_scoreboard.get<tgui::ListView>("ListView1")->addMultipleItems(t.second);

        }
        group_scoreboard.get<tgui::ListView>("ListView1")->setSize(1100, min(50 * width + 80LL, 600LL));

    }
    else {
        group_scoreboard.get<tgui::ComboBox>("ComboBox2")->setSelectedItem("All Courses");
        group_scoreboard.get<tgui::ListView>("ListView1")->setSize(1100, 50);
        group_scoreboard.get<tgui::ListView>("ListView1")->removeAllItems();
        group_scoreboard.get<tgui::ListView>("ListView1")->addMultipleItems(mpx[getSelectedItem]);
        group_scoreboard.get<tgui::ListView>("ListView1")->setSize(1100, min(50LL * long long(mpx[getSelectedItem].size()) + 80, 600LL));

    }
}

void onComboBoxCourseSelected(Group& group_scoreboard, tgui::String getSelectedItem)
{
    tgui::String getSelectedItem1 = group_scoreboard.get<ComboBox>("ComboBox1")->getSelectedItem();
    if (getSelectedItem == "All Courses")
    {
        if (getSelectedItem1 == "All Semesters")
        {
            group_scoreboard.get<tgui::ListView>("ListView1")->removeAllItems();
            int width = 0;
            for (auto t : mpx)
            {
                cout << t.second.size() << endl;
                width += t.second.size();
                group_scoreboard.get<tgui::ListView>("ListView1")->addMultipleItems(t.second);

            }
            group_scoreboard.get<tgui::ListView>("ListView1")->setSize(1100, min(50 * width + 80LL, 600LL));

        }
        else {
            group_scoreboard.get<tgui::ListView>("ListView1")->setSize(1100, 50);
            group_scoreboard.get<tgui::ListView>("ListView1")->removeAllItems();
            group_scoreboard.get<tgui::ListView>("ListView1")->addMultipleItems(mpx[getSelectedItem1]);
            group_scoreboard.get<tgui::ListView>("ListView1")->setSize(1100, min(50LL * long long(mpx[getSelectedItem1].size()) + 80, 600LL));

        }

    }
    else {
        cout << getSelectedItem1 + '/' + getSelectedItem << endl;
        group_scoreboard.get<tgui::ListView>("ListView1")->removeAllItems();
        group_scoreboard.get<tgui::ListView>("ListView1")->addMultipleItems(mpc[getSelectedItem1 + "/" + getSelectedItem]);
        group_scoreboard.get<tgui::ListView>("ListView1")->setSize(1100, min(50LL * long long(mpc[getSelectedItem1 + getSelectedItem].size()) + 80, 600LL));

    }
}
void onTeacherScoreboardSelected(Group& group_scoreboard, Group& group_student) {
    group_scoreboard.setVisible(true);
    group_student.setVisible(false);
}

void loadScoreBoardWidget(Group& group_scoreboard, SchoolYear*& schoolYear) {
    init_scoreboard_group(group_scoreboard);

    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("Semester", 210, tgui::ListView::ColumnAlignment::Center);
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("Course", 270);
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("StudentID", 110, tgui::ListView::ColumnAlignment::Center);
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("Credit", 70, tgui::ListView::ColumnAlignment::Center);
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("Midterm", 90, tgui::ListView::ColumnAlignment::Center);
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("Final", 70, tgui::ListView::ColumnAlignment::Center);
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("Other", 60, tgui::ListView::ColumnAlignment::Center);
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("10", 60, tgui::ListView::ColumnAlignment::Center);
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("ABC", 60, tgui::ListView::ColumnAlignment::Center);
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("4", 60, tgui::ListView::ColumnAlignment::Center);

    group_scoreboard.get<tgui::ComboBox>("ComboBox1")->addItem("All Semesters");
    group_scoreboard.get<tgui::ComboBox>("ComboBox1")->setSelectedItem("All Semesters");
    group_scoreboard.get<tgui::ComboBox>("ComboBox2")->addItem("All Courses");
    group_scoreboard.get<tgui::ComboBox>("ComboBox2")->setSelectedItem("All Courses");

    for (SchoolYear* i = schoolYear; i; i = i->nextSchoolYear) {
        tgui::String curYears = tgui::String(i->startYear) + '-' + tgui::String(i->endYear);

        int curSemester = 4;

        tgui::String curDirectory = "SchoolYears/" + tgui::String(i->startYear) + "-" + tgui::String(i->endYear);

        for (Semester* j = i->nowSemester; j; j = j->nextSemester) {
            curSemester--;
            group_scoreboard.get<tgui::ComboBox>("ComboBox1")->addItem("Semester " + tgui::String(curSemester) + "/" + tgui::String(i->startYear) + "-" + tgui::String(i->endYear));
            group_scoreboard.get<tgui::ComboBox>("ComboBox1")->setSelectedItem("Semester " + tgui::String(curSemester) + "/" + tgui::String(i->startYear) + "-" + tgui::String(i->endYear));
            tgui::String curSemesterStr = "Semester " + tgui::String(curSemester);
            string curDir = curDirectory.toStdString() + "/" + "Semester" + (char)(curSemester + '0') + "/Courses/";

            for (Course* k = j->nowCourse; k; k = k->nextCourse) {
                group_scoreboard.get<tgui::ComboBox>("ComboBox2")->addItem(tgui::String(k->courseName));
                string cName = curDir + k->courseName;
                ifstream fin;
                fin.open(cName + ".csv");

                //cerr << cName + ".csv\n";

                string line, word;
                int num = 0;

                while (getline(fin, line)) {
                    num++;
                    if (num == 1) {
                        //cerr << "Lmao\n";
                        continue;
                    }

                    stringstream str(line);
                    int cnt = 0;

                    int no = 0, stdID = 0, mTerm = 0, fMark = 0, oMark = 0, tMark = 0;
                    char stdName[FULLNAMELENGTH];

                    while (getline(str, word, ',')) {
                        cnt++;
                        stringstream stoint(word);
                        switch (cnt) {
                        case 1:
                            stoint >> no;
                            break;
                        case 2:
                            stoint >> stdID;
                            break;
                        case 3:
                            for (int i = 0; i < word.length(); i++) {
                                stdName[i] = word[i];
                            }
                            stdName[word.length()] = '\0';
                            break;
                        case 4:
                            stoint >> mTerm;
                            break;
                        case 5:
                            stoint >> fMark;
                            break;
                        case 6:
                            stoint >> oMark;
                            break;
                        case 7:
                            stoint >> tMark;
                            break;
                        default:
                            break;
                        }
                    }
                    vector<tgui::String> tmp;
                    tgui::String item = k->courseName;
                    for (Student* curStudent = k->nxtStudent; curStudent; curStudent = curStudent->nextStudent) {
                        if (curStudent->studentID == stdID) {
                            tmp = { curSemesterStr + "/" + curYears, item, tgui::String(curStudent->studentID),tgui::String(k->credits) ,tgui::String(mTerm), tgui::String(fMark), tgui::String(oMark), tgui::String(tMark) ,tgui::String(k->score) , "4" ,  "A" };
                            mpx[curSemesterStr + "/" + curYears].push_back(tmp);
                            mpc[curSemesterStr + "/" + curYears + k->courseName].push_back(tmp);
                            mpc[tgui::String("All Semesters/") + k->courseName].push_back(tmp);
                            group_scoreboard.get<tgui::ListView>("ListView1")->addItem(tmp);
                            break;
                        }
                    }
                }
            }
        }
    }
    //cout << mpc.size() << endl;
    
    group_scoreboard.get<tgui::ComboBox>("ComboBox1")->onItemSelect(&onComboBoxSemesterSelected, ref(group_scoreboard));
    group_scoreboard.get<tgui::ComboBox>("ComboBox2")->onItemSelect(&onComboBoxCourseSelected, ref(group_scoreboard));
}