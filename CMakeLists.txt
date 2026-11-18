cmake_minimum_required(VERSION 4.1)
project(GoF_DDD_Onion_HW2)

set(CMAKE_CXX_STANDARD 23)

add_executable(GoF_DDD_Onion_HW2
        main.cpp
        Domain/Value_Objects/Name.h
        Domain/Value_Objects/Score.h
        Domain/Value_Objects/Weight.h
        Domain/Entities/Student.h
        Domain/Entities/Criterion.h
        Domain/Entities/Grade.h
        Domain/GradeFactory.h
        Domain/CriterionsListBuilder.h
        Domain_Services/IStudentRepository.h
        Domain_Services/ICriterionRepository.h
        Domain_Services/IGradeRepository.h
        Domain_Services/CalculateFinalScore.h
        Application/ReportExporter.h
        Application/PosFacade.h
        Application/PosFacade.cpp
        Infrastructure/StudentRepository.h
        Infrastructure/CriterionRepository.h
        Infrastructure/GradeRepository.h
        Infrastructure/CsvReportExporter.h
        Infrastructure/TxtReportExporter.h
        Infrastructure/IView.h
        Infrastructure/ConsoleView.h
        Infrastructure/App.h
        Infrastructure/App.cpp
        include/di.h
)

enable_testing()

add_executable(GoF_DDD_Onion_HW2_Tests
        Tests/tests.cpp
        Application/PosFacade.cpp
        Infrastructure/App.cpp
)

add_test(NAME PosDomainTests COMMAND GoF_DDD_Onion_HW2_Tests)
