#include "PosFacade.h"
#include <stdexcept>
#include <utility>

PosFacade::PosFacade(
    std::shared_ptr<IStudentRepository> sr,
    std::shared_ptr<ICriterionRepository> cr,
    std::shared_ptr<IGradeRepository> gr,
    std::shared_ptr<GradeFactory> gf,
    std::shared_ptr<CalculateFinalScore> cs
)
    : studentRepo(std::move(sr)),
      criterionRepo(std::move(cr)),
      gradeRepo(std::move(gr)),
      gradeFactory(std::move(gf)),
      calculatorService(std::move(cs)) {}

void PosFacade::validateWeight(double additionalWeight) const {
    if (criterionRepo->getTotalWeight() + additionalWeight > 1.0) {
        throw std::invalid_argument("Сумма весов всех критериев не может превышать 1.0.");
    }
}

Student PosFacade::addStudent(const std::string& firstName, const std::string& lastName) {
    Name name(firstName, lastName);
    Student student(studentRepo->getNextId(), name);
    studentRepo->add(student);
    return student;
}

std::vector<Student> PosFacade::getStudents() const {
    return studentRepo->getAll();
}

Criterion PosFacade::addCriterion(const std::string& title, double maxScore, double weight) {
    Weight weightVo(weight);
    validateWeight(weightVo.getValue());
    Criterion criterion(criterionRepo->getNextId(), title, Score(maxScore), weightVo);
    criterionRepo->add(criterion);
    return criterion;
}

bool PosFacade::removeCriterion(int criterionId) {
    if (criterionRepo->remove(criterionId)) {
        gradeRepo->removeByCriterionId(criterionId);
        return true;
    }
    return false;
}

void PosFacade::addCriterionsList(const std::vector<Criterion>& criterions) {
    double addedWeight = 0.0;
    for (const auto& c : criterions) {
        addedWeight += c.getWeight().getValue();
    }
    validateWeight(addedWeight);
    for (const auto& c : criterions) {
        criterionRepo->add(c);
    }
}

std::vector<Criterion> PosFacade::getCriterionsList() const {
    return criterionRepo->getAll();
}

Grade PosFacade::setGrade(int studentId, int criterionId, double scoreValue) {
    auto student = studentRepo->getById(studentId);
    if (!student.has_value()) {
        throw std::invalid_argument("Студент с таким ID не найден.");
    }

    auto existingGrade = gradeRepo->getByStudentAndCriterion(studentId, criterionId);
    if (existingGrade.has_value()) {
        auto criterion = criterionRepo->getById(criterionId);
        if (!criterion.has_value()) {
            throw std::invalid_argument("Критерий отсутствует в списке критериев курса.");
        }
        Grade updated = existingGrade.value();
        updated.updateScore(Score(scoreValue), criterion.value());
        gradeRepo->save(updated);
        return updated;
    }

    auto criterionsList = criterionRepo->getAll();
    Grade newGrade = gradeFactory->createGrade(
        gradeRepo->getNextId(),
        studentId,
        criterionId,
        scoreValue,
        criterionsList
    );
    gradeRepo->save(newGrade);
    return newGrade;
}

bool PosFacade::removeGrade(int studentId, int criterionId) {
    return gradeRepo->remove(studentId, criterionId);
}

std::vector<Grade> PosFacade::getAllGrades() const {
    return gradeRepo->getAll();
}

std::vector<Grade> PosFacade::getStudentGrades(int studentId) const {
    if (!studentRepo->getById(studentId).has_value()) {
        throw std::invalid_argument("Студент с таким ID не найден.");
    }
    return gradeRepo->getByStudentId(studentId);
}

double PosFacade::getStudentFinalScore(int studentId) const {
    if (!studentRepo->getById(studentId).has_value()) {
        throw std::invalid_argument("Студент с таким ID не найден.");
    }
    return calculatorService->calculate(
        criterionRepo->getAll(),
        gradeRepo->getByStudentId(studentId)
    );
}

std::string PosFacade::generateReport(const ReportExporter& exporter) const {
    return exporter.buildReport(
        studentRepo->getAll(),
        criterionRepo->getAll(),
        gradeRepo->getAll(),
        calculatorService
    );
}

bool PosFacade::exportReportToFile(const std::string& filename, const ReportExporter& exporter) const {
    return exporter.exportToFile(
        filename,
        studentRepo->getAll(),
        criterionRepo->getAll(),
        gradeRepo->getAll(),
        calculatorService
    );
}
