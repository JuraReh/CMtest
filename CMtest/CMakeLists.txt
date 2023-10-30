# CMakeList.txt: Projekt CMake pro CMtest, sem přidejte logiku zdrojového
# kódu a definic specifickou pro projekt.
#
cmake_minimum_required (VERSION 3.8)

# Přidejte zdrojový kód ke spustitelnému souboru tohoto projektu.
add_executable (CMtest "CMtest.cpp" "CMtest.h")

# TODO: V případě potřeby přidejte testy a cíle instalace.
