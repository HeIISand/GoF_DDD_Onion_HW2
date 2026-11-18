#ifndef GOF_DDD_ONION_HW2_CSVREPORTEXPORTER_H
#define GOF_DDD_ONION_HW2_CSVREPORTEXPORTER_H

#include "../Application/ReportExporter.h"
#include <sstream>
#include <iomanip>

class CsvReportExporter : public ReportExporter {
protected:
    std::string formatHeader(const std::vector<Criterion>& criterionsList) const override {
        std::ostringstream ss;
        ss << "StudentId;FullName";
        for (const auto& c : criterionsList) {
            ss << ";" << c.getTitle();
        }
        ss << ";FinalScore\n";
        return ss.str();
    }

    std::string formatStudentRow(
        const Student& student,
        const std::vector<Criterion>& criterionsList,
        const std::vector<Grade>& studentGrades,
        double finalScore
    ) const override {
        std::ostringstream ss;
        ss << student.getId() << ";" << student.getName().getFullName();

        for (const auto& c : criterionsList) {
            double val = 0.0;
            for (const auto& g : studentGrades) {
                if (g.getCriterionId() == c.getId()) {
                    val = g.getScore().getValue();
                    break;
                }
            }
            ss << ";" << std::fixed << std::setprecision(2) << val;
        }

        ss << ";" << std::fixed << std::setprecision(2) << finalScore << "\n";
        return ss.str();
    }

    std::string formatFooter(size_t studentCount) const override {
        std::ostringstream ss;
        ss << "TotalStudents;" << studentCount << "\n";
        return ss.str();
    }
};

#endif
