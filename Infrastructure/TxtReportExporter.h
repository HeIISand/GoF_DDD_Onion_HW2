#ifndef GOF_DDD_ONION_HW2_TXTREPORTEXPORTER_H
#define GOF_DDD_ONION_HW2_TXTREPORTEXPORTER_H

#include "../Application/ReportExporter.h"
#include <sstream>
#include <iomanip>

class TxtReportExporter : public ReportExporter {
protected:
    std::string formatHeader(const std::vector<Criterion>& criterionsList) const override {
        std::ostringstream ss;
        ss << "=== ВЕДОМОСТЬ ПОС ===\n";
        ss << "Критериев в курсе: " << criterionsList.size() << "\n";
        ss << "---------------------\n";
        return ss.str();
    }

    std::string formatStudentRow(
        const Student& student,
        const std::vector<Criterion>& criterionsList,
        const std::vector<Grade>& studentGrades,
        double finalScore
    ) const override {
        std::ostringstream ss;
        ss << "[" << student.getId() << "] " << student.getName().getFullName() << ":\n";

        for (const auto& c : criterionsList) {
            double val = 0.0;
            for (const auto& g : studentGrades) {
                if (g.getCriterionId() == c.getId()) {
                    val = g.getScore().getValue();
                    break;
                }
            }
            ss << "  - " << c.getTitle() << ": "
               << std::fixed << std::setprecision(2) << val
               << " / " << c.getMaxScore().getValue() << "\n";
        }

        ss << "  Итог: " << std::fixed << std::setprecision(2) << finalScore << "\n";
        return ss.str();
    }

    std::string formatFooter(size_t studentCount) const override {
        std::ostringstream ss;
        ss << "---------------------\n";
        ss << "Всего студентов: " << studentCount << "\n";
        return ss.str();
    }
};

#endif
