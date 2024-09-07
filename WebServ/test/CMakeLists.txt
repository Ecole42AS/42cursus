cmake_minimum_required(VERSION 3.13)
project(WebServ)

# Inclure le répertoire Google Test
add_subdirectory(/home/alex/Ecole42/42cursus/WebServ/googletest)

# Ajouter les fichiers sources pour la bibliothèque de parsing
set(PARSING_SOURCES
    parsing2.cpp
)

# Créer une bibliothèque à partir des sources de parsing
add_library(parsing_lib ${PARSING_SOURCES})
target_include_directories(parsing_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/parsing)

# Ajouter les fichiers de test
set(TEST_SOURCES
    test/parsing_tests.cpp
)

# Créer l'exécutable des tests
add_executable(parsing_tests ${TEST_SOURCES})

# Lier les bibliothèques nécessaires aux tests
target_link_libraries(parsing_tests gtest gtest_main pthread parsing_lib)

# Ajouter les tests
enable_testing()
add_test(NAME parsing_tests COMMAND parsing_tests)
