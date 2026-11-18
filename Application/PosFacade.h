#ifndef GOF_DDD_ONION_HW2_POSFACADE_H
#define GOF_DDD_ONION_HW2_POSFACADE_H

#include "../Domain/Entities/Student.h"
#include "../Domain/Entities/Criterion.h"
#include "../Domain/Entities/Grade.h"
#include "../Domain/GradeFactory.h"
#include "../Domain_Services/IStudentRepository.h"
#include "../Domain_Services/ICriterionRepository.h"
#include "../Domain_Services/IGradeRepository.h"
#include "../Domain_Services/CalculateFinalScore.h"
#include "ReportExporter.h"
#include <memory>
#include <string>
#include <vector>

class PosFacade {
private:
    std::shared_ptr<IStudentRepository> studentRepo;
    std::shared_ptr<ICriterionRepository> criterionRepo;
    std::shared_ptr<IGradeRepository> gradeRepo;
    std::shared_ptr<GradeFactory> gradeFactory;
    std::shared_ptr<CalculateFinalScore> calculatorService;

    void validateWeight(double additionalWeight) const;

public:
    PosFacade(
        std::shared_ptr<IStudentRepository> sr,
        std::shared_ptr<ICriterionRepository> cr,
        std::shared_ptr<IGradeRepository> gr,
        std::shared_ptr<GradeFactory> gf,
        std::shared_ptr<CalculateFinalScore> cs
    );

    Student addStudent(const std::string& firstName, const std::string& lastName);
    std::vector<Student> getStudents() const;

    Criterion addCriterion(const std::string& title, double maxScore, double weight);
    bool removeCriterion(int criterionId);
    void addCriterionsList(const std::vector<Criterion>& criterions);
    std::vector<Criterion> getCriterionsList() const;

    Grade setGrade(int studentId, int criterionId, double scoreValue);
    bool removeGrade(int studentId, int criterionId);
    std::vector<Grade> getAllGrades() const;
    std::vector<Grade> getStudentGrades(int studentId) const;

    double getStudentFinalScore(int studentId) const;

    std::string generateReport(const ReportExporter& exporter) const;
    bool exportReportToFile(const std::string& filename, const ReportExporter& exporter) const;
};

#endif
