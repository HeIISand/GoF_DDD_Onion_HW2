#include "App.h"
#include "CsvReportExporter.h"
#include "TxtReportExporter.h"
#include "../Domain/CriterionsListBuilder.h"
#include <string>
#include <utility>
#include <exception>

App::App(std::shared_ptr<PosFacade> pf, std::shared_ptr<IView> cv)
    : posFacade(std::move(pf)), view(std::move(cv)) {}

void App::addStudent() {
    view->print("\n--- Добавление студента ---");
    view->print("Введите имя:");
    std::string firstName = view->readString();
    view->print("Введите фамилию:");
    std::string lastName = view->readString();

    try {
        Student s = posFacade->addStudent(firstName, lastName);
        view->print("Студент добавлен! ID: " + std::to_string(s.getId()) + ", " + s.getName().getFullName());
    } catch (const std::exception& e) {
        view->print(std::string("Ошибка: ") + e.what());
    }
}

void App::addCriterion() {
    view->print("\n--- Добавление критерия ---");
    view->print("Введите название критерия:");
    std::string title = view->readString();
    view->print("Введите максимальный балл:");
    double maxScore = view->readDouble();
    view->print("Введите вес критерия (от 0 до 1):");
    double weight = view->readDouble();

    try {
        Criterion c = posFacade->addCriterion(title, maxScore, weight);
        view->print("Критерий добавлен! ID: " + std::to_string(c.getId()) + ", " + c.getTitle());
    } catch (const std::exception& e) {
        view->print(std::string("Ошибка: ") + e.what());
    }
}

void App::removeCriterion() {
    view->print("\n--- Удаление критерия ---");
    view->print("Введите ID критерия:");
    int criterionId = view->readInt();

    if (posFacade->removeCriterion(criterionId)) {
        view->print("Критерий и связанные с ним оценки удалены.");
    } else {
        view->print("Критерий не найден.");
    }
}

void App::showStudents() {
    auto students = posFacade->getStudents();
    if (students.empty()) {
        view->print("Список студентов пуст.");
        return;
    }
    view->print("\n--- Список студентов ---");
    for (const auto& s : students) {
        view->print("[" + std::to_string(s.getId()) + "] " + s.getName().getFullName());
    }
}

void App::showCriterionsList() {
    auto criterions = posFacade->getCriterionsList();
    if (criterions.empty()) {
        view->print("Список критериев пуст.");
        return;
    }
    view->print("\n--- Список критериев курса ---");
    for (const auto& c : criterions) {
        view->print("[" + std::to_string(c.getId()) + "] " + c.getTitle() +
                    " (макс: " + std::to_string(c.getMaxScore().getValue()) +
                    ", вес: " + std::to_string(c.getWeight().getValue()) + ")");
    }
}

void App::setGrade() {
    view->print("\n--- Выставление / изменение оценки ---");
    view->print("Введите ID студента:");
    int studentId = view->readInt();
    view->print("Введите ID критерия:");
    int criterionId = view->readInt();
    view->print("Введите балл:");
    double score = view->readDouble();

    try {
        Grade g = posFacade->setGrade(studentId, criterionId, score);
        view->print("Оценка сохранена! Балл: " + std::to_string(g.getScore().getValue()));
    } catch (const std::exception& e) {
        view->print(std::string("Ошибка: ") + e.what());
    }
}

void App::removeGrade() {
    view->print("\n--- Отмена оценки ---");
    view->print("Введите ID студента:");
    int studentId = view->readInt();
    view->print("Введите ID критерия:");
    int criterionId = view->readInt();

    if (posFacade->removeGrade(studentId, criterionId)) {
        view->print("Оценка успешно удалена.");
    } else {
        view->print("Оценка не найдена.");
    }
}

void App::showGrades() {
    auto grades = posFacade->getAllGrades();
    if (grades.empty()) {
        view->print("Оценок пока нет.");
        return;
    }
    view->print("\n--- Выставленные оценки ---");
    for (const auto& g : grades) {
        view->print("Студент ID " + std::to_string(g.getStudentId()) +
                    " | Критерий ID " + std::to_string(g.getCriterionId()) +
                    " | Балл: " + std::to_string(g.getScore().getValue()));
    }
}

void App::showStudentGrades() {
    view->print("\n--- Оценки студента ---");
    view->print("Введите ID студента:");
    int studentId = view->readInt();

    try {
        auto grades = posFacade->getStudentGrades(studentId);
        if (grades.empty()) {
            view->print("У студента пока нет оценок.");
            return;
        }
        for (const auto& g : grades) {
            view->print("Критерий ID " + std::to_string(g.getCriterionId()) +
                        " | Балл: " + std::to_string(g.getScore().getValue()));
        }
    } catch (const std::exception& e) {
        view->print(std::string("Ошибка: ") + e.what());
    }
}

void App::showStudentFinalScore() {
    view->print("\n--- Итоговый балл студента ---");
    view->print("Введите ID студента:");
    int studentId = view->readInt();

    try {
        double finalScore = posFacade->getStudentFinalScore(studentId);
        view->print("Итоговый балл: " + std::to_string(finalScore));
    } catch (const std::exception& e) {
        view->print(std::string("Ошибка: ") + e.what());
    }
}

void App::exportReport() {
    view->print("\n--- Экспорт ведомости ---");
    view->print("1. Экспорт в CSV (report.csv)");
    view->print("2. Экспорт в TXT (report.txt)");
    view->print("0. Назад в главное меню");

    int choice = view->readInt();
    if (choice == 1) {
        CsvReportExporter exporter;
        view->print("\n" + posFacade->generateReport(exporter));
        if (posFacade->exportReportToFile("report.csv", exporter)) {
            view->print("Ведомость сохранена в файл report.csv");
        } else {
            view->print("Ошибка при сохранении файла report.csv");
        }
    } else if (choice == 2) {
        TxtReportExporter exporter;
        view->print("\n" + posFacade->generateReport(exporter));
        if (posFacade->exportReportToFile("report.txt", exporter)) {
            view->print("Ведомость сохранена в файл report.txt");
        } else {
            view->print("Ошибка при сохранении файла report.txt");
        }
    } else if (choice == 0) {
        return;
    } else {
        view->print("Неизвестный формат.");
    }
}

void App::runDemo() {
    view->print("\n--- Демонстрационный сценарий ---");
    try {
        Student s1 = posFacade->addStudent("Иван", "Иванов");
        Student s2 = posFacade->addStudent("Анна", "Петрова");

        CriterionsListBuilder builder;
        auto demoCriterions = builder
            .addCriterion("Ходил на лекции,", 10.0, 0.1)
            .addCriterion("Ходил на семинары,", 10.0, 0.1)
            .addCriterion("Вдумчиво использовал ИИ", 10.0, 0.1)
            .addCriterion("не пропускал дедлайны", 10.0, 0.1)
            .addCriterion("Помнил ФИО лектора", 10.0, 0.6)
            .build();

        posFacade->addCriterionsList(demoCriterions);

        int c1 = demoCriterions[0].getId();
        int c2 = demoCriterions[1].getId();
        int c3 = demoCriterions[2].getId();
        int c4 = demoCriterions[3].getId();
        int c5 = demoCriterions[4].getId();

        posFacade->setGrade(s1.getId(), c1, 8.0);
        posFacade->setGrade(s1.getId(), c2, 9.0);
        posFacade->setGrade(s1.getId(), c3, 7.0);
        posFacade->setGrade(s1.getId(), c4, 7.0);
        posFacade->setGrade(s1.getId(), c5, 7.0);

        posFacade->setGrade(s2.getId(), c1, 10.0);
        posFacade->setGrade(s2.getId(), c2, 10.0);
        posFacade->setGrade(s2.getId(), c3, 9.0);
        posFacade->setGrade(s2.getId(), c4, 9.0);
        posFacade->setGrade(s2.getId(), c5, 9.0);

        TxtReportExporter txtExporter;
        CsvReportExporter csvExporter;

        view->print(posFacade->generateReport(txtExporter));
        bool csv = posFacade->exportReportToFile("report.csv", csvExporter);
        bool txt = posFacade->exportReportToFile("report.txt", txtExporter);
        if (csv && txt) {
            view->print("Экспорт выполнен в файлы report.csv и report.txt");
        } else {
            view->print("Ошибка при сохранении файлов отчета.");
        }
    } catch (const std::exception& e) {
        view->print(std::string("Ошибка в демо-сценарии: ") + e.what());
    }
}

void App::run() {
    bool isRunning = true;
    while (isRunning) {
        view->print("\nМеню ПОС:");
        view->print("1. Добавить студента");
        view->print("2. Добавить критерий");
        view->print("3. Удалить критерий");
        view->print("4. Показать студентов");
        view->print("5. Показать список критериев");
        view->print("6. Выставить или изменить оценку");
        view->print("7. Отменить оценку");
        view->print("8. Показать все оценки");
        view->print("9. Показать оценки студента");
        view->print("10. Рассчитать итог студента");
        view->print("11. Экспортировать ведомость");
        view->print("12. Запустить сквозной демо-сценарий");
        view->print("0. Выход");

        int choice = view->readInt();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: addCriterion(); break;
            case 3: removeCriterion(); break;
            case 4: showStudents(); break;
            case 5: showCriterionsList(); break;
            case 6: setGrade(); break;
            case 7: removeGrade(); break;
            case 8: showGrades(); break;
            case 9: showStudentGrades(); break;
            case 10: showStudentFinalScore(); break;
            case 11: exportReport(); break;
            case 12: runDemo(); break;
            case 0: isRunning = false; break;
            default: view->print("Неизвестная команда.");
        }
    }
}
