#include "Domain/GradeFactory.h"
#include "Domain_Services/IStudentRepository.h"
#include "Domain_Services/ICriterionRepository.h"
#include "Domain_Services/IGradeRepository.h"
#include "Domain_Services/CalculateFinalScore.h"
#include "Application/PosFacade.h"
#include "Infrastructure/StudentRepository.h"
#include "Infrastructure/CriterionRepository.h"
#include "Infrastructure/GradeRepository.h"
#include "Infrastructure/IView.h"
#include "Infrastructure/ConsoleView.h"
#include "Infrastructure/App.h"
#include "include/di.h"

namespace di = boost::di;

int main() {
    const auto injector = di::make_injector(
        di::bind<IStudentRepository>.to<StudentRepository>(),
        di::bind<ICriterionRepository>.to<CriterionRepository>(),
        di::bind<IGradeRepository>.to<GradeRepository>(),
        di::bind<IView>.to<StandardConsoleView>()
    );

    auto app = injector.create<App>();
    app.run();

    return 0;
}
