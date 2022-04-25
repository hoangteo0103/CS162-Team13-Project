#include "ClassScoreboard.h"

map <tgui::String, vector<vector<tgui::String>>> mpa;
map <tgui::String, vector<vector<tgui::String>> > mpb;

void init_groupSB(Group& group_studentSB) {
    group_studentSB.loadWidgetsFromFile("ClassScoreboardForm.txt");
}

void onStudentSBSelected(Group& group_studentSB, Group& group_student) {
    group_studentSB.setVisible(true);
    group_student.setVisible(false);
}

void onComboBoxClassSelected(Group& group_studentSB, tgui::String getSelectedItem)
{
    //cerr << getSelectedItem << '\n';
    tgui::String getSelectedItem1 = group_studentSB.get<ComboBox>("ComboBox1")->getSelectedItem();
    if (getSelectedItem == "All Classes")
    {
        if (getSelectedItem1 == "All Semesters")
        {
            group_studentSB.get<tgui::ListView>("ListView1")->removeAllItems();
            int width = 0;
            for (auto t : mpa)
            {
                //cout << t.second.size() << endl;
                width += t.second.size();
                group_studentSB.get<tgui::ListView>("ListView1")->addMultipleItems(t.second);

            }
            group_studentSB.get<tgui::ListView>("ListView1")->setSize(1100, min(50 * width + 80LL, 550LL));

        }
        else {
            group_studentSB.get<tgui::ListView>("ListView1")->setSize(1100, 50);
            group_studentSB.get<tgui::ListView>("ListView1")->removeAllItems();
            group_studentSB.get<tgui::ListView>("ListView1")->addMultipleItems(mpa[getSelectedItem1]);
            group_studentSB.get<tgui::ListView>("ListView1")->setSize(1100, min(20LL * long long(mpa[getSelectedItem1].size()) + 40, 550LL));

        }

    }
    else {
        //cout << getSelectedItem1 + '/' + getSelectedItem << endl;
        group_studentSB.get<tgui::ListView>("ListView1")->removeAllItems();
        group_studentSB.get<tgui::ListView>("ListView1")->addMultipleItems(mpb[getSelectedItem1 + "/" + getSelectedItem]);
        group_studentSB.get<tgui::ListView>("ListView1")->setSize(1100, min(20LL * long long(mpb[getSelectedItem1 + '/' + getSelectedItem].size()) + 40, 550LL));

    }
}

void onComboBoxSemestersSelected(Group& group_studentSB, tgui::String getSelectedItem) {
    if (getSelectedItem == "All Semesters")
    {
        group_studentSB.get<tgui::ListView>("ListView1")->removeAllItems();
        group_studentSB.get<tgui::ComboBox>("ComboBox2")->setSelectedItem("All Classes");
        int width = 0;
        for (auto t : mpa)
        {
            //cout << t.second.size() << endl;
            width += t.second.size();
            group_studentSB.get<tgui::ListView>("ListView1")->addMultipleItems(t.second);

        }
        group_studentSB.get<tgui::ListView>("ListView1")->setSize(1100, min(50 * width + 80LL, 550LL));

    }
    else {
        group_studentSB.get<tgui::ComboBox>("ComboBox2")->setSelectedItem("All Classes");
        group_studentSB.get<tgui::ListView>("ListView1")->setSize(1100, 50);
        group_studentSB.get<tgui::ListView>("ListView1")->removeAllItems();
        group_studentSB.get<tgui::ListView>("ListView1")->addMultipleItems(mpa[getSelectedItem]);
        group_studentSB.get<tgui::ListView>("ListView1")->setSize(1100, min(20LL * long long(mpa[getSelectedItem].size()) + 40, 550LL));
    }
}

void loadSBWidgets(Group& group_studentSB, SchoolYear*& schoolYear) {
    init_groupSB(group_studentSB);

    group_studentSB.get<tgui::ListView>("ListView1")->addColumn("Semester", 220, tgui::ListView::ColumnAlignment::Center);
    //group_studentSB.get<tgui::ListView>("ListView1")->addColumn("Courses", 210, tgui::ListView::ColumnAlignment::Center);
    group_studentSB.get<tgui::ListView>("ListView1")->addColumn("StudentID", 130, tgui::ListView::ColumnAlignment::Center);
    group_studentSB.get<tgui::ListView>("ListView1")->addColumn("Student Name", 270, tgui::ListView::ColumnAlignment::Center);
    group_studentSB.get<tgui::ListView>("ListView1")->addColumn("Class", 110, tgui::ListView::ColumnAlignment::Center);
    group_studentSB.get<tgui::ListView>("ListView1")->addColumn("GPA", 100, tgui::ListView::ColumnAlignment::Center);
    group_studentSB.get<tgui::ListView>("ListView1")->addColumn("ABC", 80, tgui::ListView::ColumnAlignment::Center);
    group_studentSB.get<tgui::ListView>("ListView1")->addColumn("4", 80, tgui::ListView::ColumnAlignment::Center);

    group_studentSB.get<tgui::ComboBox>("ComboBox1")->addItem("All Semesters");
    group_studentSB.get<tgui::ComboBox>("ComboBox1")->setSelectedItem("All Semesters");
    group_studentSB.get<tgui::ComboBox>("ComboBox2")->addItem("All Classes");
    group_studentSB.get<tgui::ComboBox>("ComboBox2")->setSelectedItem("All Classes");

    for (SchoolYear* i = schoolYear; i; i = i->nextSchoolYear) {
        tgui::String curYears = tgui::String(i->startYear) + '-' + tgui::String(i->endYear);

        int curSemester = 4;

        tgui::String curDirectory = "SchoolYears/" + tgui::String(i->startYear) + "-" + tgui::String(i->endYear);

        for (SpecificClass* k = i->nowClass; k; k = k->nextClass) {
            group_studentSB.get<tgui::ComboBox>("ComboBox2")->addItem(tgui::String(k->classCODE));
        }

        for (Semester* j = i->nowSemester; j; j = j->nextSemester) {
            curSemester--;

            group_studentSB.get<tgui::ComboBox>("ComboBox1")->addItem("Semester " + tgui::String(curSemester) + "/" + tgui::String(i->startYear) + "-" + tgui::String(i->endYear));
            //group_studentSB.get<tgui::ComboBox>("ComboBox1")->setSelectedItem("Semester " + tgui::String(curSemester) + "/" + tgui::String(i->startYear) + "-" + tgui::String(i->endYear));
            tgui::String curSemesterStr = "Semester " + tgui::String(curSemester);
            string curDir = curDirectory.toStdString() + "/" + "Semester" + (char)(curSemester + '0') + "/Courses/";

            for (SpecificClass* k = i->nowClass; k; k = k->nextClass) {
                //group_studentSB.get<tgui::ComboBox>("ComboBox2")->addItem(tgui::String(k->classCODE));

                for (Student* curStudent = k->classStudent; curStudent; curStudent = curStudent->nextStudent) {

                    //string strID = "";
                    float GPA = 0;
                    float cnt = 0, tmpID;

                    for (Course* curCourse = j->nowCourse; curCourse; curCourse = curCourse->nextCourse) {
                        cnt++;
                        //group_studentSB.get<tgui::ComboBox>("ComboBox1")->addItem(tgui::String(k->courseName));
                        string cName = curDir + curCourse->courseName;
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

                            if (stdID == curStudent->studentID) GPA += tMark;
                        }
                    }

                    GPA /= cnt;

                    vector<tgui::String> tmp;

                    tgui::String name = curStudent->firstName;
                    name += ' ';
                    name += curStudent->lastName;

                    tmp = { tgui::String(curSemesterStr + "/" + curYears), tgui::String(curStudent->studentID), name, tgui::String(k->classCODE), tgui::String(j->nowCourse->round(GPA)), tgui::String(j->nowCourse->convertoABC(GPA)), tgui::String(j->nowCourse->converto4(GPA))};
                    mpa[curSemesterStr + "/" + curYears].push_back(tmp);
                    mpb[curSemesterStr + "/" + curYears + "/" + tgui::String(k->classCODE)].push_back(tmp);
                    mpb[tgui::String("All Semesters/") + tgui::String(k->classCODE)].push_back(tmp);
                    group_studentSB.get<tgui::ListView>("ListView1")->addItem(tmp);
                    //tgui::String item = k->courseName;
                }
            }
        }
    }
    //cout << mpc.size() << endl;

    group_studentSB.get<tgui::ComboBox>("ComboBox1")->onItemSelect(&onComboBoxSemestersSelected, ref(group_studentSB));
    group_studentSB.get<tgui::ComboBox>("ComboBox2")->onItemSelect(&onComboBoxClassSelected, ref(group_studentSB));
}
