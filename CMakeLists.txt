cmake_minimum_required(VERSION 3.10)
project(HeroRealms)

# Spécifier le standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Récupérer tous les fichiers sources
file(GLOB_RECURSE SOURCES 
    "src/Game/*.cpp"
    "src/Game/*/*.cpp"
    "main.cpp"
)

# Inclure les dossiers d'en-têtes
include_directories(${PROJECT_SOURCE_DIR}/include)

# Créer l'exécutable
add_executable(HeroRealms ${SOURCES})