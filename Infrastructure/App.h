#ifndef GOF_DDD_ONION_HW2_APP_H
#define GOF_DDD_ONION_HW2_APP_H

#include "../Application/PosFacade.h"
#include "IView.h"
#include <memory>

class App {
private:
    std::shared_ptr<PosFacade> posFacade;
    std::shared_ptr<IView> view;

    void addStudent();
    void addCriterion();
    void removeCriterion();
    void showStudents();
    void showCriterionsList();
    void setGrade();
    void removeGrade();
    void showGrades();
    void showStudentGrades();
    void showStudentFinalScore();
    void exportReport();
    void runDemo();

public:
    App(std::shared_ptr<PosFacade> pf, std::shared_ptr<IView> cv);
    void run();
};

#endif
