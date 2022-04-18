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
        if (getSelectedItem1 == "All Courses")
        {
            group_studentSB.get<tgui::ListView>("ListView1")->removeAllItems();
            int width = 0;
            for (auto t : mpa)
            {
                //cout << t.second.size() << endl;
                width += t.second.size();
                group_studentSB.get<tgui::ListView>("ListView1")->addMultipleItems(t.second);

            }
            group_studentSB.get<tgui::ListView>("ListView1")->setSize(1100, min(50 * width + 80LL, 600LL));

        }
        else {
            group_studentSB.get<tgui::ListView>("ListView1")->setSize(1100, 50);
            group_studentSB.get<tgui::ListView>("ListView1")->removeAllItems();
            group_studentSB.get<tgui::ListView>("ListView1")->addMultipleItems(mpa[getSelectedItem1]);
            group_studentSB.get<tgui::ListView>("ListView1")->setSize(1100, min(50LL * long long(mpa[getSelectedItem1].size()) + 80, 600LL));

        }

    }
    else {
        //cout << getSelectedItem1 + '/' + getSelectedItem << endl;
        group_studentSB.get<tgui::ListView>("ListView1")->removeAllItems();
        group_studentSB.get<tgui::ListView>("ListView1")->addMultipleItems(mpb[getSelectedItem1 + "/" + getSelectedItem]);
        group_studentSB.get<tgui::ListView>("ListView1")->setSize(1100, min(80LL * long long(mpb[getSelectedItem1 + getSelectedItem].size()) + 80, 600LL));

    }
}

void onComboBoxCoursesSelected(Group& group_studentSB, tgui::String getSelectedItem) {
    if (getSelectedItem == "All Courses")
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
        group_studentSB.get<tgui::ListView>("ListView1")->setSize(1100, min(50 * width + 80LL, 600LL));

    }
    else {
        group_studentSB.get<tgui::ComboBox>("ComboBox2")->setSelectedItem("All Classes");
        group_studentSB.get<tgui::ListView>("ListView1")->setSize(1100, 50);
        group_studentSB.get<tgui::ListView>("ListView1")->removeAllItems();
        group_studentSB.get<tgui::ListView>("ListView1")->addMultipleItems(mpa[getSelectedItem]);
        group_studentSB.get<tgui::ListView>("ListView1")->setSize(1100, min(50LL * long long(mpa[getSelectedItem].size()) + 80, 600LL));
    }
}

void loadSBWidgets(Group& group_studentSB, SchoolYear*& schoolYear) {
    init_groupSB(group_studentSB);

    group_studentSB.get<tgui::ListView>("ListView1")->addColumn("Courses", 210, tgui::ListView::ColumnAlignment::Center);
    group_studentSB.get<tgui::ListView>("ListView1")->addColumn("Class", 100, tgui::ListView::ColumnAlignment::Center);
    group_studentSB.get<tgui::ListView>("ListView1")->addColumn("StudentID", 110, tgui::ListView::ColumnAlignment::Center);
    group_studentSB.get<tgui::ListView>("ListView1")->addColumn("StudentName", 210, tgui::ListView::ColumnAlignment::Center);
    group_studentSB.get<tgui::ListView>("ListView1")->addColumn("GPA", 100, tgui::ListView::ColumnAlignment::Center);
    group_studentSB.get<tgui::ListView>("ListView1")->addColumn("10", 60, tgui::ListView::ColumnAlignment::Center);
    group_studentSB.get<tgui::ListView>("ListView1")->addColumn("ABC", 60, tgui::ListView::ColumnAlignment::Center);
    group_studentSB.get<tgui::ListView>("ListView1")->addColumn("4", 60, tgui::ListView::ColumnAlignment::Center);

    group_studentSB.get<tgui::ComboBox>("ComboBox1")->addItem("All Courses");
    group_studentSB.get<tgui::ComboBox>("ComboBox1")->setSelectedItem("All Courses");
    group_studentSB.get<tgui::ComboBox>("ComboBox2")->addItem("All Classes");
    group_studentSB.get<tgui::ComboBox>("ComboBox2")->setSelectedItem("All Classes");

    for (SchoolYear* i = schoolYear; i; i = i->nextSchoolYear) {
        tgui::String curYears = tgui::String(i->startYear) + '-' + tgui::String(i->endYear);

        int curSemester = 4;

        tgui::String curDirectory = "SchoolYears/" + tgui::String(i->startYear) + "-" + tgui::String(i->endYear);

        for (SpecificClass* j = i->nowClass; j; j = j->nextClass) {
            group_studentSB.get<tgui::ComboBox>("ComboBox2")->addItem(tgui::String(j->classCODE));
        }

        for (Semester* j = i->nowSemester; j; j = j->nextSemester) {
            curSemester--;
            //group_studentSB.get<tgui::ComboBox>("ComboBox1")->addItem("Semester " + tgui::String(curSemester) + "/" + tgui::String(i->startYear) + "-" + tgui::String(i->endYear));
            //group_studentSB.get<tgui::ComboBox>("ComboBox1")->setSelectedItem("Semester " + tgui::String(curSemester) + "/" + tgui::String(i->startYear) + "-" + tgui::String(i->endYear));
            tgui::String curSemesterStr = "Semester " + tgui::String(curSemester);
            string curDir = curDirectory.toStdString() + "/" + "Semester" + (char)(curSemester + '0') + "/Courses/";

            for (Course* k = j->nowCourse; k; k = k->nextCourse) {

                group_studentSB.get<tgui::ComboBox>("ComboBox1")->addItem(tgui::String(k->courseName));
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

                    tgui::String gpa = tgui::String(tMark);
                    tgui::String className;

                    string strID = "";
                    int tmpID = stdID;
                    while (tmpID) {
                        strID += (char)(tmpID % 10 + '0');
                        tmpID /= 10;
                    }
                    reverse(strID.begin(), strID.end());
                    //cerr << strID << '\n';

                    for (SpecificClass* sClass = i->nowClass; sClass; sClass = sClass->nextClass) {
                        Student tmpStudent;
                        string studentName;
                        if (sClass->findStudent(strID, studentName, tmpStudent)) {
                            className = tgui::String(sClass->classCODE);
                            //cerr << "I can find it\n";
                        }
                    }

                    vector<tgui::String> tmp;
                    tgui::String item = k->courseName;
                    for (Student* curStudent = k->nxtStudent; curStudent; curStudent = curStudent->nextStudent) {
                        if (curStudent->studentID == stdID) {
                            tgui::String curStudentName = curStudent->firstName;
                            curStudentName += ' ';
                            curStudentName += curStudent->lastName;
                            //cerr << curStudentName << '\n';
                            int on4 = 4 * tMark / 10;
                            //cerr << tgui::String(k->convertoABC(tMark));
                            //cerr << item << ' ' << className << ' ' << tgui::String(curStudent->studentID) << ' ' << curStudentName << ' ' << gpa << ' ' << tgui::String(k->convertoABC(tMark)) << ' ' << tgui::String(on4) << '\n';

                            tmp = { item, className, tgui::String(curStudent->studentID), curStudentName, gpa, gpa, tgui::String(k->convertoABC(tMark)), tgui::String(on4) };
                            mpa[item].push_back(tmp);
                            mpb[item + "/" + className].push_back(tmp);
                            group_studentSB.get<tgui::ListView>("ListView1")->addItem(tmp);
                        }
                    }
                }
            }
        }
    }
    //cout << mpc.size() << endl;

    group_studentSB.get<tgui::ComboBox>("ComboBox1")->onItemSelect(&onComboBoxCoursesSelected, ref(group_studentSB));
    group_studentSB.get<tgui::ComboBox>("ComboBox2")->onItemSelect(&onComboBoxClassSelected, ref(group_studentSB));
}
