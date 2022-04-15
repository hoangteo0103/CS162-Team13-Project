#include "Scoreboard.h"
map <tgui::String, vector<vector<tgui::String>>> mp; 

void onComboBoxSelected(Group& group_scoreboard, tgui::String getSelectedItem)
{
    if (getSelectedItem == "All Semesters")
    {
        group_scoreboard.get<tgui::ListView>("ListView1")->removeAllItems();
        int width = 0;
        for (auto t : mp)
        {
            cout << t.second.size() << endl;
            width += t.second.size();
            group_scoreboard.get<tgui::ListView>("ListView1")->addMultipleItems(t.second);

        }
        group_scoreboard.get<tgui::ListView>("ListView1")->setSize(1020, min(50 * width + 80LL , 600LL));

    }
    else {
        group_scoreboard.get<tgui::ListView>("ListView1")->setSize(1020, 50);
        group_scoreboard.get<tgui::ListView>("ListView1")->removeAllItems();
        group_scoreboard.get<tgui::ListView>("ListView1")->addMultipleItems(mp[getSelectedItem]);
        group_scoreboard.get<tgui::ListView>("ListView1")->setSize(1020, min(50LL * long long (mp[getSelectedItem].size()) + 80 , 600LL));

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
void loadwidget(Group& group_scoreboard, queue<pair<SchoolYear*, int>> curSchoolYear, string& studentName)
{
    init_group(group_scoreboard);
    
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("Semester", 200);
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("Course ID", 100);
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("Course", 270);
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("Credit", 70);
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("Midterm", 90);
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("Final", 70);
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("Other", 60);
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("10", 30);
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("ABC", 40);
    group_scoreboard.get<tgui::ListView>("ListView1")->addColumn("4", 50);

    while (!curSchoolYear.empty())
    {
        SchoolYear* cSYear = curSchoolYear.front().first;
        int sID = curSchoolYear.front().second;
        curSchoolYear.pop();


        /*string strID = "";
        while (sID) {
            strID += (char)((sID % 10) + '0');
            sID /= 10;
        }
        reverse(strID.begin(), strID.end());
        */
        tgui::String curYears = tgui::String(cSYear->startYear) + '-' + tgui::String(cSYear->endYear);

        int curSemester = 4;

        tgui::String curDirectory = "SchoolYears/" + tgui::String(cSYear->startYear) + "-" + tgui::String(cSYear->endYear);

        for (Semester* i = cSYear->nowSemester; i; i = i->nextSemester) {
            curSemester--;
            group_scoreboard.get<tgui::ComboBox>("ComboBox1")->addItem("Semester " + tgui::String(curSemester) + "/" + tgui::String(cSYear->startYear) + "-" + tgui::String(cSYear->endYear));
            group_scoreboard.get<tgui::ComboBox>("ComboBox1")->setSelectedItem("Semester " + tgui::String(curSemester) + "/" + tgui::String(cSYear->startYear) + "-" + tgui::String(cSYear->endYear));
            tgui::String curSemesterStr = "Semester " + tgui::String(curSemester);
            string curDir = curDirectory.toStdString() + "/" + "Semester" + (char)(curSemester + '0') + "/Courses/";
            /*for (Course* j = i->nowCourse; j; j = j->nextCourse) {

                vector<tgui::String> tmp;
                if (j->findStudent(curDir, strID)) {
                    tgui::String item = j->courseName;
                    tmp = { curSemesterStr + "/" + curYears, tgui::String(j->courseID) , item , tgui::String(j->credits) ,"A" , tgui::String(j->score) , "4" };
                    mp[curSemesterStr + "/" + curYears].push_back(tmp);
                    group_scoreboard.get<tgui::ListView>("ListView1")->addItem(tmp);
                }
            }*/

            for (Course* j = i->nowCourse; j; j = j->nextCourse) {
                string cName = curDir + j->courseName;
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
                    
                    //cerr << no << ' ' << stdID << ' ' << mTerm << ' ' << fMark << ' ' << oMark << ' ' << tMark << '\n';
                    //cerr << stdName << '\n';
                    vector<tgui::String> tmp;
                    if (!studentName.compare(stdName)) {
                        tgui::String item = j->courseName;
                        tmp = { curSemesterStr + "/" + curYears, tgui::String(j->courseID) , item ,tgui::String(j->credits) ,tgui::String(mTerm), tgui::String(fMark), tgui::String(oMark), tgui::String(tMark) ,tgui::String(j->score) ,   "4" ,  "A" };
                        mp[curSemesterStr + "/" + curYears].push_back(tmp);
                        group_scoreboard.get<tgui::ListView>("ListView1")->addItem(tmp);
                    }
                }

            }
        }
    }
    group_scoreboard.get<tgui::ComboBox>("ComboBox1")->addItem("All Semesters"); 
    group_scoreboard.get<tgui::ComboBox>("ComboBox1")->setSelectedItem("All Semesters"); 
    group_scoreboard.get<tgui::ComboBox>("ComboBox1")->onItemSelect(&onComboBoxSelected , ref(group_scoreboard));

}