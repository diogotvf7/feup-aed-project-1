//
// Created by diogotvf7 on 04-11-2022.
//

#include <iostream>
#include <iomanip>

#include "Menu.h"

using namespace std;

bool isNumerical(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}
template<class T>
bool nameCmp(T *lhs, T *rhs) {
    return lhs->getName() < rhs->getName();
}
template<class T>
bool nameCmpReverse(T *lhs, T *rhs) {
    return lhs->getName() > rhs->getName();
}
template<class T>
bool attendanceCmp(T *lhs, T *rhs) {
    return lhs->countStudents() < rhs->countStudents();
}
template<class T>
bool attendanceCmpReverse(T *lhs, T *rhs) {
    return lhs->countStudents() > rhs->countStudents();
}
template<class T>
bool numberOfClassesCmp(T *lhs, T *rhs) {
    return lhs->countClasses() < rhs->countClasses();
}
template<class T>
bool numberOfClassesCmpReverse(T *lhs, T *rhs) {
    return lhs->countClasses() > rhs->countClasses();
}

Menu::Menu(ScheduleManager *sm) {
    this->sm = sm;
    this->status = "0";
    this->ucPrintConfig = {{"ORDER", "NAME"}, {"SHOW ATTENDANCE", "NO"}, {"REVERSE", "NO"}, {"YEAR", "ALL"}}; // ORDER->(NAME / ATTENDANCE)   SHOW ATTENDANCE->(YES / NO)   REVERSE->(YES / NO)   YEAR->(1 / 2 / 3 / ALL)
    this->classPrintConfig = {{"ORDER", "ATTENDANCE"}, {"SHOW ATTENDANCE", "YES"}, {"REVERSE", "NO"}, {"YEAR", "ALL"}}; // ORDER->(NAME / ATTENDANCE)   SHOW ATTENDANCE->(YES / NO)   REVERSE->(YES / NO)   YEAR->(1 / 2 / 3 / ALL)
    this->studentPrintConfig = {{"ORDER", "NAME"}, {"SHOW NUMBER OF CLASSES", "YES"}, {"REVERSE", "NO"}}; // ORDER->(NAME / NUMBER OF CLASSES / CODE)   SHOW NUMBER OF CLASSES->(YES / NO)   REVERSE->(YES / NO)
}

vector<UC*> Menu::getUcs() {
    vector<UC*> sortedUcs = sm->getUcVector();
    if (ucPrintConfig["ORDER"] == "NAME" && ucPrintConfig["REVERSE"] == "NO")
        sort(sortedUcs.begin(), sortedUcs.end(), nameCmp<UC>);

    else if (ucPrintConfig["ORDER"] == "NAME" && ucPrintConfig["REVERSE"] == "YES")
        sort(sortedUcs.begin(), sortedUcs.end(), nameCmpReverse<UC>);

    else if (ucPrintConfig["ORDER"] == "ATTENDANCE" && ucPrintConfig["REVERSE"] == "NO")
        sort(sortedUcs.begin(), sortedUcs.end(), attendanceCmp<UC>);

    else if (ucPrintConfig["ORDER"] == "ATTENDANCE" && ucPrintConfig["REVERSE"] == "YES")
        sort(sortedUcs.begin(), sortedUcs.end(), attendanceCmpReverse<UC>);

    return sortedUcs;
}

vector<Class*> Menu::getClasses(UC *uc, Student *s) {

    vector<Class*> sortedClasses;

    if (uc) sortedClasses = uc->getClasses();
    else if (s) sortedClasses = s->getClasses();
    else sortedClasses = sm->getClassesVector();

    if (classPrintConfig["ORDER"] == "NAME" && classPrintConfig["REVERSE"] == "NO")
        sort(sortedClasses.begin(), sortedClasses.end(), nameCmp<Class>);

    else if (classPrintConfig["ORDER"] == "NAME" && classPrintConfig["REVERSE"] == "YES")
        sort(sortedClasses.begin(), sortedClasses.end(), nameCmpReverse<Class>);

    else if (classPrintConfig["ORDER"] == "ATTENDANCE" && classPrintConfig["REVERSE"] == "NO")
        sort(sortedClasses.begin(), sortedClasses.end(), attendanceCmp<Class>);

    else if (classPrintConfig["ORDER"] == "ATTENDANCE" && classPrintConfig["REVERSE"] == "YES")
        sort(sortedClasses.begin(), sortedClasses.end(), attendanceCmpReverse<Class>);

    return sortedClasses;
}

vector<Student*> Menu::getStudents(Class *c) {

    vector<Student*> sortedClassStudents = c->getStudents();

    if (studentPrintConfig["ORDER"] == "NAME" && studentPrintConfig["REVERSE"] == "NO")
        sort(sortedClassStudents.begin(), sortedClassStudents.end(), nameCmp<Student>);

    else if (studentPrintConfig["ORDER"] == "NAME" && studentPrintConfig["REVERSE"] == "YES")
        sort(sortedClassStudents.begin(), sortedClassStudents.end(), nameCmpReverse<Student>);

    else if (studentPrintConfig["ORDER"] == "NUMBER OF CLASSES" && studentPrintConfig["REVERSE"] == "NO")
        sort(sortedClassStudents.begin(), sortedClassStudents.end(), numberOfClassesCmp<Student>);

    else if (studentPrintConfig["ORDER"] == "NUMBER OF CLASSES" && studentPrintConfig["REVERSE"] == "YES")
        sort(sortedClassStudents.begin(), sortedClassStudents.end(), numberOfClassesCmpReverse<Student>);

    return sortedClassStudents;
}

void Menu::run() {

    bool alive = true;
    while (alive) {
        switch (stoi(status)) {

            case 0: // Main menu
                mainMenu();
                break;
            case 1: //
                ucMenu(); // SHOWS UCS LIST MENU
                status = "0";
                break;
            case 2: //
                classMenu(); // SHOWS CLASS LIST MENU
                status = "0";
                break;
            case 3: //
                studentMenu();
                status = "0";
                break;
            case 4: //
                findMenu();
                status = "0";
                break;
            case 5: //
                requestMenu();
                status = "0";
                break;
            case 6:
                configMenu();
                status = "0";
                break;
            case 7: // EXIT
                close();
                cleanTerminal();
                alive = false;
                break;
        }
        cleanTerminal();
    }
}

void Menu::mainMenu() {
    cleanTerminal();
    cout << "__________________________________________________________________\n"
         << "|                            Main menu                           |\n"
         << "|                  Choose an option to continue                  |\n"
         << "|________________________________________________________________|\n"
         << "|                                                                |\n"
         << "|                  1. SEE CURRICULAR UNITS                       |\n"
         << "|                  2. SEE CLASSES                                |\n"
         << "|                  3. SEE STUDENTS                               |\n"
         << "|                  4. FIND STUDENT/CLASS/CURRICULAR UNIT         |\n"
         << "|                  5. MAKE REQUEST                               |\n"
         << "|                  6. CONFIGURATIONS                             |\n"
         << "|                  7. EXIT                                       |\n"
         << "|________________________________________________________________|\n\n";

    while (true) {
        cout << "   - OPTION: "; cin >> status;
        if (isNumerical(status) && 1 <= stoi(status) && stoi(status) <= 7) break;
        else cout << "   - INVALID OPTION" << endl;
    }
}

void Menu::ucMenu() {

    bool alive = true;
    vector<UC*> sortedUcs = getUcs();

    while (alive) {
        cleanTerminal();
        cout << "__________________________________________________________________\n"
             << "|                        CURRICULAR UNITS                        |\n"
             << "|                                                                |\n"
             << "|________________________________________________________________|\n";

        for (size_t i = 0; i < sortedUcs.size(); i++) {
            cout << right << setw(20) << to_string((i + 1)) + ".   " << sortedUcs[i]->getName();
            if (ucPrintConfig["SHOW ATTENDANCE"] == "YES") {
                cout << ": " << setw(12) <<  to_string((sortedUcs[i]->countStudents())) + " students";
            }
            cout << endl;
        }
        cout << "__________________________________________________________________\n"
             << "|           WRITE A NUMBER TO INSPECT A CURRICULAR UNIT          |\n"
             << "|                     WRITE 'back' TO GO BACK                    |\n"
             << "|________________________________________________________________|\n\n";

        while (true) {

            cout << "   - OPTION: "; cin >> status;
            if (isNumerical(status) && 1 <= stoi(status) && stoi(status) <= sortedUcs.size()) {
                alive = ucClassMenu(sortedUcs[stoi(status) - 1]);
                break;
            }
            else if (status == "back")
                return;
            else cout << "   - INVALID OPTION" << endl;
        }

    }
}

void Menu::classMenu() {

    bool alive = true;
    int page = 0;
    vector<Class*> sortedClasses = getClasses();

    while (alive) {
        cleanTerminal();
        cout << "__________________________________________________________________\n"
             << "|                            CLASSES                             |\n"
             << "|                                                                |\n"
             << "|________________________________________________________________|\n";

        for (int i = page * 20; i < min(page * 20 + 20, (int) sortedClasses.size()); i++) {
            cout << right << setw(20) << to_string(i + 1) + ".   " << sortedClasses[i]->getUc()->getName() << ' ' << sortedClasses[i]->getName();
            if (classPrintConfig["SHOW ATTENDANCE"] == "YES") {
                cout << ": " << (sortedClasses[i]->countStudents()) << " students";
            }
            cout << endl;
        }

        cout << "__________________________________________________________________\n"
             << "|                WRITE A NUMBER TO INSPECT A CLASS               |\n"
             << "|                      WRITE 'w' TO MOVE UP                      |\n"
             << "|                     WRITE 's' TO MOVE DOWN                     |\n"
             << "|                     WRITE 'back' TO GO BACK                    |\n"
             << "|________________________________________________________________|\n\n";

        while (true) {

            cout << "   - OPTION: "; cin >> status;
            if (isNumerical(status) && page * 20 + 1 <= stoi(status) && stoi(status) <= min(page * 20 + 21, (int) sortedClasses.size())) {
                alive = classStudentMenu(sortedClasses[stoi(status) - 1]);
                break;
            } else if (status == "w" && page * 20 - 20 >= 0) {
                page--;
                break;
            } else if (status == "s" && page * 20 + 20 < sortedClasses.size()) {
                page++;
                break;
            } else if (status == "back")
                return;
            else cout << "   - INVALID OPTION" << endl;
        }
    }
}

void Menu::studentMenu() {

    bool alive = true;

    cleanTerminal();
    cleanTerminal();

    cout << "__________________________________________________________________\n"
         << "|                           STUDENTS                             |\n"
         << "|                                                                |\n"
         << "|________________________________________________________________|\n";

    if (studentPrintConfig["ORDER"] == "NAME" && studentPrintConfig["REVERSE"] == "NO") {

        set<Student*,StudentNameCmp> sortedStudents = sm->getStudentsByNameSet();
        unsigned n = 0;

        for (Student *s : sortedStudents) {
            cout << right << setw(20) << to_string(++n) + ".   " << left << setw(20) << s->getName();
            if (studentPrintConfig["SHOW NUMBER OF CLASSES"] == "YES")
                cout <<  to_string(s->countClasses()) + " classes";
            cout << endl;
        }
    }
    if (studentPrintConfig["ORDER"] == "CODE" && studentPrintConfig["REVERSE"] == "NO") {

        set<Student*,StudentCodeCmp> sortedStudents = sm->getStudentsByCodeSet();
        unsigned n = 0;

        for (Student *s : sortedStudents) {
            cout << right << setw(20) << to_string(++n) + ".   " << left << setw(20) << s->getName();
            if (studentPrintConfig["SHOW NUMBER OF CLASSES"] == "YES")
                cout <<  to_string(s->countClasses()) + " classes";
            cout << endl;
        }
    }
    if (studentPrintConfig["ORDER"] == "NUMBER OF CLASSES" && studentPrintConfig["REVERSE"] == "NO") {

        set<Student*,StudentNumberOfClassesCmp> sortedStudents = sm->getStudentsByNumberOfClassesSet();
        unsigned n = 0;

        for (Student *s : sortedStudents) {
            cout << right << setw(20) << to_string(++n) + ".   " << left << setw(20) << s->getName();
            if (studentPrintConfig["SHOW NUMBER OF CLASSES"] == "YES")
                cout <<  to_string(s->countClasses()) + " classes";
            cout << endl;
        }
    }
    if (studentPrintConfig["ORDER"] == "NAME" && studentPrintConfig["REVERSE"] == "YES") {

        set<Student*,StudentNameCmp> sortedStudents = sm->getStudentsByNameSet();
        unsigned n = 0;

        for (auto itr = sortedStudents.rend(); itr != sortedStudents.rbegin(); itr++) {
            cout << right << setw(20) << to_string(++n) + ".   " << left << setw(20) << (*itr)->getName();
            if (studentPrintConfig["SHOW NUMBER OF CLASSES"] == "YES")
                cout <<  to_string((*itr)->countClasses()) + " classes";
            cout << endl;
        }
    }
    if (studentPrintConfig["ORDER"] == "CODE" && studentPrintConfig["REVERSE"] == "YES") {

        set<Student*,StudentCodeCmp> sortedStudents = sm->getStudentsByCodeSet();
        unsigned n = 0;

        for (auto itr = sortedStudents.rend(); itr != sortedStudents.rbegin(); itr++) {
            cout << right << setw(20) << to_string(++n) + ".   " << left << setw(20) << (*itr)->getName();
            if (studentPrintConfig["SHOW NUMBER OF CLASSES"] == "YES")
                cout <<  to_string((*itr)->countClasses()) + " classes";
            cout << endl;
        }
    }
    if (studentPrintConfig["ORDER"] == "NUMBER OF CLASSES" && studentPrintConfig["REVERSE"] == "YES") {

        set<Student*,StudentNumberOfClassesCmp> sortedStudents = sm->getStudentsByNumberOfClassesSet();
        unsigned n = 0;

        for (auto itr = sortedStudents.rend(); itr != sortedStudents.rbegin(); itr++) {
            cout << right << setw(20) << to_string(++n) + ".   " << left << setw(20) << (*itr)->getName();
            if (studentPrintConfig["SHOW NUMBER OF CLASSES"] == "YES")
                cout <<  to_string((*itr)->countClasses()) + " classes";
            cout << endl;
        }
    }


    cout << "__________________________________________________________________\n"
         << "|                     WRITE 'back' TO GO BACK                    |\n"
         << "|________________________________________________________________|\n\n";

    while (true) {
        cout << "   - OPTION: "; cin >> status;
        if (status == "back")
            return;
        else cout << "   - INVALID OPTION" << endl;
    }
}

bool Menu::ucClassMenu(UC *uc) {

    bool alive = true;
    vector<Class*> sortedUcClasses = getClasses(uc);

    while (alive) {
        cleanTerminal();
        cout << "__________________________________________________________________\n"
             << "|" << right << setw(32 + (int)(uc->getName().size() / 2)) << uc->getName() << setw(30) << "|\n"
             << "|                                                                |\n"
             << "|________________________________________________________________|\n";

        for (size_t i = 0; i < sortedUcClasses.size(); i++) {
            cout << right << setw(20) << to_string(i + 1) + ".    " << sortedUcClasses[i]->getName();
            if (classPrintConfig["SHOW ATTENDANCE"] == "YES") {
                cout << ": " << sortedUcClasses[i]->countStudents() << " students";
            }
            cout << endl;
        }

        cout << "__________________________________________________________________\n"
             << "|              WRITE A NUMBER TO INSPECT A CLASS UNIT            |\n"
             << "|                     WRITE 'back' TO GO BACK                    |\n"
             << "|________________________________________________________________|\n\n";

        while (true) {

            cout << "   - OPTION: "; cin >> status;
            if (isNumerical(status) && 1 <= stoi(status) && stoi(status) <= sortedUcClasses.size()) {
                alive = classStudentMenu(sortedUcClasses[stoi(status) - 1]);
                break;
            }
            else if (status == "back")
                return true;
            else cout << "   - INVALID OPTION" << endl;
        }
    }
    return false;
}

bool Menu::classStudentMenu(Class *c) {

    bool alive = true;
    vector<Student*> sortedClassStudents = getStudents(c);

    while (alive) {
        cleanTerminal();
        cout << "__________________________________________________________________\n"
             << "|" << right << setw(32 + (int)(c->getName().size() / 2)) << c->getUc()->getName() << setw(30) << "|\n"
             << "|" << right << setw(32 + (int)(c->getName().size() / 2)) << c->getName() << setw(30) << "|\n"
             << "|________________________________________________________________|\n";

        for (size_t i = 0; i < sortedClassStudents.size(); i++) {
            cout << right << setw(20) << to_string(i + 1) + ".    " << sortedClassStudents[i]->getName();
            if (studentPrintConfig["SHOW NUMBER OF CLASSES"] == "YES") {
                cout << ": " << (sortedClassStudents[i]->countClasses()) << " classes";
            }
            cout << endl;
        }

        cout << "__________________________________________________________________\n"
             << "|                WRITE A NUMBER TO INSPECT A STUDENT             |\n"
             << "|                     WRITE 'back' TO GO BACK                    |\n"
             << "|________________________________________________________________|\n\n";

        while (true) {

            cout << "   - OPTION: "; cin >> status;
            if (isNumerical(status) && 1 <= stoi(status) && stoi(status) <= sortedClassStudents.size()) {
                alive = studentMenu(sortedClassStudents[stoi(status) - 1]);
                break;
            }
            else if (status == "back")
                return true;
            else cout << "   - INVALID OPTION" << endl;
        }
    }
    return false;
}

bool Menu::studentMenu(Student *s) {

    bool alive = true;
    vector<Class*> sortedStudentClasses = getClasses(nullptr, s);

    while (alive) {
        cleanTerminal();
        cout << "__________________________________________________________________\n"
             << "|" << right << setw(32 + (int)(s->getName().size() / 2)) << s->getName() << setw(32) << "|\n"
             << "|" << right << setw(37) << s->getCode() << setw(29) << "|\n"
             << "|________________________________________________________________|\n";

        for (int i = 0; i < sortedStudentClasses.size(); i++) {
            cout << right << setw(20) << to_string(i + 1) + ".    " << sortedStudentClasses[i]->getName() << endl;
            for (Slot *slot : sortedStudentClasses[i]->getSlots())
                cout << right << setw(11) << " - " << *slot;
            cout << endl;
        }

        cout << "__________________________________________________________________\n";
        s->getStatus() ? cout << "|" << right << setw(46) << "WRITE 'd' TO DELETE STATUS" << setw(20) << "|\n" : cout << "|" << right << setw(44) << "WRITE 'a' TO ADD STATUS" << setw(22) << "|\n";
        cout << "|                     WRITE 'back' TO GO BACK                    |\n"
             << "|________________________________________________________________|\n\n";

        while (true) {

            cin >> status;

            if (status == "d" && s->getStatus()) {
                s->setStatus(false);
                break;
            }
            if (status == "a" && !s->getStatus()) {
                s->setStatus(true);
                break;
            }
            if (status == "back")
                return false;

            cout << "Invalid option";
        }
    }
    return false;
}

void Menu::addRequest() {

   string student, uc, intended; Student *s; Class *i;
    while (true) {
        cout << "\nStudent name or code: "; cin >> student;
        if (!isNumerical(student)) s = sm->findStudentByName(student);
        else s = sm->findStudentByCode(student);
        if (s) break;
        cout << "  - INVALID OPTION\n";
    }
    while (true) {
        cout << "UC Code: "; cin >> uc;
        cout << "Intended Class code: "; cin >> intended;
        i = sm->findClass(uc, intended);
        if (i) break;
        cout << "  - INVALID OPTION\n";
    }
    sm->createRequest(new AddRequest(s, i));
}

void Menu::removeRequest() {

    string student, uc, current; Student *s; Class *c;
    while (true) {
        cout << "\nStudent name or code: "; cin >> student;
        if (!isNumerical(student)) s = sm->findStudentByName(student);
        else s = sm->findStudentByCode(student);
        if (s) break;
        cout << "  - INVALID OPTION\n";
    }
    while (true) {
        cout << "UC Code: "; cin >> uc;
        cout << "Current Class code: "; cin >> current;
        c = sm->findClass(uc, current);
        if (c) break;
        cout << "  - INVALID OPTION\n";
    }
    sm->createRequest(new RemoveRequest(s, c));
}

void Menu::switchRequest() {
    string student, uc, current, intended; Student *s; Class *c, *i;
    while (true) {
        cout << "\nStudent name or code: "; cin >> student;
        if (!isNumerical(student)) s = sm->findStudentByName(student);
        else s = sm->findStudentByCode(student);
        if (s) break;
        cout << "  - INVALID OPTION\n";
    }
    while (true) {
        cout << "UC Code: "; cin >> uc;
        cout << "Current Class code: "; cin >> current;
        c = sm->findClass(uc, current);
        if (c) break;
        cout << "  - INVALID OPTION\n";
    }
    while (true) {
        cout << "Intended Class code: "; cin >> intended;
        i = sm->findClass(uc, intended);
        if (i) break;
        cout << "  - INVALID OPTION\n";
    }
    sm->createRequest(new SwitchRequest(s, c, i));

}
void Menu::swapRequest() {
    string tmp1, tmp2; Student *student, *colleague; Class *c, *i;
    while (true) {
        cout << "\nStudent name or code: "; cin >> tmp1;
        if (!isNumerical(tmp1)) student = sm->findStudentByName(tmp1);
        else student = sm->findStudentByCode(tmp1);
        if (student) break;
        cout << "  - INVALID OPTION\n";
    }
    while (true) {
        cout << "\nColleague name or code: "; cin >> tmp1;
        if (!isNumerical(tmp1)) colleague = sm->findStudentByName(tmp1);
        else colleague = sm->findStudentByCode(tmp1);
        if (colleague) break;
        cout << "  - INVALID OPTION\n";
    }
    while (true) {
        cout << "UC Code: "; cin >> tmp2;
        cout << "Current Class code: "; cin >> tmp1;
        c = sm->findClass(tmp2, tmp1);
        if (c) break;
        cout << "  - INVALID OPTION\n";
    }
    while (true) {
        cout << "Intended Class code: "; cin >> tmp1;
        i = sm->findClass(tmp2, tmp1);
        if (i) break;
        cout << "  - INVALID OPTION\n";
    }
    sm->createRequest(new SwapRequest(student, colleague, c, i));
}

void Menu::requestMenu() {
    cleanTerminal();
    cout << "__________________________________________________________________\n"
         << "|                          Request menu                          |\n"
         << "|                  Choose an option to continue                  |\n"
         << "|________________________________________________________________|\n"
         << "|                                                                |\n"
         << "|                  1. ADD REQUEST                                |\n"
         << "|                  2. REMOVE REQUEST                             |\n"
         << "|                  3. SWITCH REQUEST                             |\n"
         << "|                  4. SWAP REQUEST                               |\n"
         << "|                  5. EXIT                                       |\n"
         << "|________________________________________________________________|\n\n";

    while (true) {
        cout << "   - OPTION: "; cin >> status;
        if (isNumerical(status) && 1 <= stoi(status) && stoi(status) <= 4)
            break;
        if (status == "5")
            return;
        else cout << "   - INVALID OPTION" << endl;
    }
    switch (stoi(status)) {
      case 1:
            addRequest();
            break;
        case 2:
            removeRequest();
            break;
        case 3:
            switchRequest();
            break;
        case 4:
            swapRequest();
            break;
    }
}

void Menu::findMenu() {
    while (true) {
        cleanTerminal();
        cout << "__________________________________________________________________\n"
             << "|                           Find menu                            |\n"
             << "|                  Choose an option to continue                  |\n"
             << "|________________________________________________________________|\n"
             << "|                                                                |\n"
             << "|                  1. CURRICULAR UNIT                            |\n"
             << "|                  2. CLASS                                      |\n"
             << "|                  3. STUDENT                                    |\n"
             << "|                  4. EXIT                                       |\n"
             << "|________________________________________________________________|\n\n";

        while (true) {
            cout << "   - OPTION: "; cin >> status;
            if (isNumerical(status) && 1 <= stoi(status) && stoi(status) <= 3)
                break;
            if (status == "4")
                return;
            else cout << "   - INVALID OPTION" << endl;
        }

        string tmp1, tmp2; Student *s; Class *c; UC *uc;

        switch (stoi(status)) {
            case 1:
                while (true) {
                    cout << "UC Code: "; cin >> tmp1;
                    uc = sm->findUc(tmp1);
                    if (c) {
                        ucClassMenu(uc);
                        return;
                    }
                    cout << "  - INVALID OPTION\n";
                }
            case 2:
                while (true) {
                    cout << "UC Code: "; cin >> tmp1;
                    uc = sm->findUc(tmp1);
                    if (uc) break;
                    cout << "  - INVALID OPTION\n";
                }
                while (true) {
                    cout << "Current Class code: "; cin >> tmp2;
                    c = sm->findClass(tmp1, tmp2);
                    if (c) {
                        classStudentMenu(c);
                        return;
                    }
                    cout << "  - INVALID OPTION\n";
                }
            case 3:
                while (true) {
                    cout << "\nStudent name or code: "; cin >> tmp1;
                    if (!isNumerical(tmp1)) s = sm->findStudentByName(tmp1);
                    else s = sm->findStudentByCode(tmp1);
                    if (s) {
                        studentMenu(s);
                        return;
                    }
                    cout << "  - INVALID OPTION\n";
                }
        }
    }
}

void Menu::configUcMenu() {

    string tmp1;
    while (true) {
        cout << "   - ORDER->(NAME / ATTENDANCE): ";
        cin >> tmp1;
        if (tmp1 == "NAME" || tmp1 == "ATTENDANCE") {
            ucPrintConfig["ORDER"] = tmp1;
            break;
        }
        else cout << "   - INVALID OPTION" << endl;
    }
    while (true) {
        cout << "   - SHOW ATTENDANCE->(YES / NO): ";
        cin >> tmp1;
        if (tmp1 == "YES" || tmp1 == "NO") {
            ucPrintConfig["SHOW ATTENDANCE"] = tmp1;
            break;
        }
        else cout << "   - INVALID OPTION" << endl;
    }
    while (true) {
        cout << "   - REVERSE->(YES / NO): ";
        cin >> tmp1;
        if (tmp1 == "YES" || tmp1 == "NO") {
            ucPrintConfig["REVERSE"] = tmp1;
            break;
        }
        else cout << "   - INVALID OPTION" << endl;
    }
    while (true) {
        cout << "   - YEAR->(1 / 2 / 3 / ALL): ";
        cin >> tmp1;
        if (tmp1 == "1" || tmp1 == "2" || tmp1 == "3" || tmp1 == "ALL") {
            ucPrintConfig["YEAR"] = tmp1;
            break;
        }
        else cout << "   - INVALID OPTION" << endl;
    }
}

void Menu::configClassMenu() {

    string tmp1;
    while (true) {
        cout << "   - ORDER->(NAME / ATTENDANCE): ";
        cin >> tmp1;
        if (tmp1 == "NAME" || tmp1 == "ATTENDANCE") {
            classPrintConfig["ORDER"] = tmp1;
            break;
        }
        else cout << "   - INVALID OPTION" << endl;
    }
    while (true) {
        cout << "   - SHOW ATTENDANCE->(YES / NO): ";
        cin >> tmp1;
        if (tmp1 == "YES" || tmp1 == "NO") {
            classPrintConfig["SHOW ATTENDANCE"] = tmp1;
            break;
        }
        else cout << "   - INVALID OPTION" << endl;
    }
    while (true) {
        cout << "   - REVERSE->(YES / NO): ";
        cin >> tmp1;
        if (tmp1 == "YES" || tmp1 == "NO") {
            classPrintConfig["REVERSE"] = tmp1;
            break;
        }
        else cout << "   - INVALID OPTION" << endl;
    }
    while (true) {
        cout << "   - YEAR->(1 / 2 / 3 / ALL): ";
        cin >> tmp1;
        if (tmp1 == "1" || tmp1 == "2" || tmp1 == "3" || tmp1 == "ALL") {
            classPrintConfig["YEAR"] = tmp1;
            break;
        }
        else cout << "   - INVALID OPTION" << endl;
    }
}

void Menu::configStudentMenu() {
    string tmp1;
    while (true) {
        cout << "   - ORDER->(NAME / NUMBER_OF_CLASSES / CODE): ";
        cin >> tmp1;
        if (tmp1 == "NAME" || tmp1 == "NUMBER_OF_CLASSES" || tmp1 == "CODE") {
            studentPrintConfig["ORDER"] = tmp1;
            break;
        }
        else cout << "   - INVALID OPTION" << endl;
    }
    while (true) {
        cout << "   - SHOW NUMBER OF CLASSES->(YES / NO): ";
        cin >> tmp1;
        if (tmp1 == "YES" || tmp1 == "NO") {
            studentPrintConfig["SHOW NUMBER OF CLASSES"] = tmp1;
            break;
        }
        else cout << "   - INVALID OPTION" << endl;
    }
    while (true) {
        cout << "   - REVERSE->(YES / NO): ";
        cin >> tmp1;
        if (tmp1 == "YES" || tmp1 == "NO") {
            studentPrintConfig["REVERSE"] = tmp1;
            break;
        }
        else cout << "   - INVALID OPTION" << endl;
    }
}


void Menu::configMenu() {

    while (true) {
        cleanTerminal();
        cout << "__________________________________________________________________\n"
             << "|                      Configurations menu                       |\n"
             << "|                  Choose an option to continue                  |\n"
             << "|________________________________________________________________|\n"
             << "|                                                                |\n"
             << "|                  1. CURRICULAR UNITS                           |\n"
             << "|                  2. CLASSES                                    |\n"
             << "|                  3. STUDENTS                                   |\n"
             << "|                  4. EXIT                                       |\n"
             << "|________________________________________________________________|\n\n";

        while (true) {
            cout << "   - OPTION: "; cin >> status;
            if (isNumerical(status) && 1 <= stoi(status) && stoi(status) <= 3)
                break;
            if (status == "4")
                return;
            else cout << "   - INVALID OPTION" << endl;
        }

        switch (stoi(status)) {

            case 1:
                configUcMenu();
                break;
            case 2:
                configClassMenu();
                break;
            case 3:
                configStudentMenu();
                break;
        }
    }
}

void Menu::close() {
    cleanTerminal();
    cout << "__________________________________________________________________\n"
         << "|             Do you wish to save the requests made?             |\n"
         << "|                            yes / no                            |\n"
         << "|________________________________________________________________|\n";

    while (true) {
        cout << "   - OPTION: "; cin >> status;
        if (status == "yes") {
            sm->processRequests();
            sm->writeChanges();
            break;
        }
        if (status == "no")
            return;
        else cout << "   - INVALID OPTION" << endl;
    }
}

void Menu::cleanTerminal() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

