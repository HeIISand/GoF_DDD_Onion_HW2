#ifndef GOF_DDD_ONION_HW2_REPORTEXPORTER_H
#define GOF_DDD_ONION_HW2_REPORTEXPORTER_H

#include "../Domain/Entities/Student.h"
#include "../Domain/Entities/Criterion.h"
#include "../Domain/Entities/Grade.h"
#include "../Domain_Services/CalculateFinalScore.h"
#include <string>
#include <vector>
#include <memory>
#include <fstream>

class ReportExporter {
protected:
    virtual std::string formatHeader(const std::vector<Criterion>& criterionsList) const = 0;
    virtual std::string formatStudentRow(
        const Student& student,
        const std::vector<Criterion>& criterionsList,
        const std::vector<Grade>& studentGrades,
        double finalScore
    ) const = 0;
    virtual std::string formatFooter(size_t studentCount) const = 0;

public:
    virtual ~ReportExporter() = default;

    std::string buildReport(
        const std::vector<Student>& students,
        const std::vector<Criterion>& criterionsList,
        const std::vector<Grade>& allGrades,
        const std::shared_ptr<CalculateFinalScore>& calculator
    ) const {
        std::string report = formatHeader(criterionsList);

        for (const auto& student : students) {
            std::vector<Grade> studentGrades;
            for (const auto& grade : allGrades) {
                if (grade.getStudentId() == student.getId()) {
                    studentGrades.push_back(grade);
                }
            }

            double finalScore = calculator->calculate(criterionsList, studentGrades);
            report += formatStudentRow(student, criterionsList, studentGrades, finalScore);
        }

        report += formatFooter(students.size());
        return report;
    }

    bool exportToFile(
        const std::string& filename,
        const std::vector<Student>& students,
        const std::vector<Criterion>& criterionsList,
        const std::vector<Grade>& allGrades,
        const std::shared_ptr<CalculateFinalScore>& calculator
    ) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        file << buildReport(students, criterionsList, allGrades, calculator);
        return true;
    }
};

#endif
