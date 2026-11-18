#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "../include/di.h"
#include "../Domain/Value_Objects/Name.h"
#include "../Domain/Value_Objects/Score.h"
#include "../Domain/Value_Objects/Weight.h"
#include "../Domain/Entities/Student.h"
#include "../Domain/Entities/Criterion.h"
#include "../Domain/Entities/Grade.h"
#include "../Domain/GradeFactory.h"
#include "../Domain/CriterionsListBuilder.h"
#include "../Domain_Services/IStudentRepository.h"
#include "../Domain_Services/ICriterionRepository.h"
#include "../Domain_Services/IGradeRepository.h"
#include "../Domain_Services/CalculateFinalScore.h"
#include "../Application/PosFacade.h"
#include "../Infrastructure/StudentRepository.h"
#include "../Infrastructure/CriterionRepository.h"
#include "../Infrastructure/GradeRepository.h"
#include "../Infrastructure/CsvReportExporter.h"
#include "../Infrastructure/TxtReportExporter.h"
#include "../Infrastructure/IView.h"
#include "../Infrastructure/App.h"

namespace di = boost::di;

class FakeView : public IView {
public:
    mutable std::vector<int> intInputs;
    mutable size_t intIndex = 0;
    mutable std::vector<double> doubleInputs;
    mutable size_t doubleIndex = 0;
    mutable std::vector<std::string> stringInputs;
    mutable size_t stringIndex = 0;
    mutable std::vector<std::string> outputs;

    void print(const std::string& message) const override {
        outputs.push_back(message);
    }

    int readInt() const override {
        if (intIndex < intInputs.size()) {
            return intInputs[intIndex++];
        }
        return 0;
    }

    double readDouble() const override {
        if (doubleIndex < doubleInputs.size()) {
            return doubleInputs[doubleIndex++];
        }
        return 0.0;
    }

    std::string readString() const override {
        if (stringIndex < stringInputs.size()) {
            return stringInputs[stringIndex++];
        }
        return "";
    }
};

void testValueObjectsInvariants() {
    Name validName("Иван", "Иванов");
    assert(validName.getFirstName() == "Иван");
    assert(validName.getLastName() == "Иванов");
    assert(validName.getFullName() == "Иван Иванов");

    bool emptyNameThrown = false;
    try {
        Name invalidName("", "Иванов");
    } catch (const std::invalid_argument&) {
        emptyNameThrown = true;
    }
    assert(emptyNameThrown);

    bool negativeScoreThrown = false;
    try {
        Score invalidScore(-1.0);
    } catch (const std::invalid_argument&) {
        negativeScoreThrown = true;
    }
    assert(negativeScoreThrown);

    bool invalidWeightThrown = false;
    try {
        Weight invalidWeight(1.5);
    } catch (const std::invalid_argument&) {
        invalidWeightThrown = true;
    }
    assert(invalidWeightThrown);
}

void testGradeFactoryAndCriterionsListBuilder() {
    CriterionsListBuilder builder;
    auto criterionsList = builder
        .addCriterion("лекции", 10.0, 0.4)
        .addCriterion("семы", 10.0, 0.6)
        .build();

    assert(criterionsList.size() == 2);

    GradeFactory factory;
    Grade validGrade = factory.createGrade(1, 1, criterionsList[0].getId(), 8.5, criterionsList);
    assert(validGrade.getScore().getValue() == 8.5);

    bool scoreExceedsMaxThrown = false;
    try {
        factory.createGrade(2, 1, criterionsList[0].getId(), 12.0, criterionsList);
    } catch (const std::invalid_argument&) {
        scoreExceedsMaxThrown = true;
    }
    assert(scoreExceedsMaxThrown);

    bool unknownCriterionThrown = false;
    try {
        factory.createGrade(3, 1, 999, 5.0, criterionsList);
    } catch (const std::invalid_argument&) {
        unknownCriterionThrown = true;
    }
    assert(unknownCriterionThrown);
}

void testDomainServiceCalculation() {
    CriterionsListBuilder builder;
    auto criterionsList = builder
        .addCriterion("лекции", 10.0, 0.3)
        .addCriterion("семы", 10.0, 0.3)
        .addCriterion("ии", 10.0, 0.4)
        .build();

    GradeFactory factory;
    std::vector<Grade> grades = {
        factory.createGrade(1, 1, 1, 8.0, criterionsList),
        factory.createGrade(2, 1, 2, 9.0, criterionsList),
        factory.createGrade(3, 1, 3, 7.0, criterionsList)
    };

    CalculateFinalScore calculator;

    double finalScore = calculator.calculate(criterionsList, grades);
    assert(std::abs(finalScore - 7.9) < 1e-9);
}

void testFacadeAndAppThroughDiContainer() {
    auto fakeView = std::make_shared<FakeView>();
    fakeView->intInputs = {12, 0};

    const auto injector = di::make_injector(
        di::bind<IStudentRepository>.to<StudentRepository>().in(di::unique),
        di::bind<ICriterionRepository>.to<CriterionRepository>().in(di::unique),
        di::bind<IGradeRepository>.to<GradeRepository>().in(di::unique),
        di::bind<IView>.to(fakeView)
    );

    auto facade = injector.create<std::shared_ptr<PosFacade>>();
    Student s = facade->addStudent("Петр", "Сидоров");
    Criterion c = facade->addCriterion("лекции", 10.0, 0.5);
    facade->setGrade(s.getId(), c.getId(), 9.0);
    assert(facade->getStudentGrades(s.getId()).size() == 1);
    assert(facade->removeCriterion(c.getId()));
    assert(facade->getCriterionsList().empty());
    assert(facade->getAllGrades().empty());

    auto app = injector.create<App>();
    app.run();

    assert(!fakeView->outputs.empty());
}

int main() {
    testValueObjectsInvariants();
    testGradeFactoryAndCriterionsListBuilder();
    testDomainServiceCalculation();
    testFacadeAndAppThroughDiContainer();

    std::cout << "Все тесты успешно пройдены!" << std::endl;
    return 0;
}
