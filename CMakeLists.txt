﻿# CMakeList.txt: Soubor projektu CMake na nejvyšší úrovni, proveďte na tomto
# místě globální konfiguraci a zahrňte podprojekty.
#
cmake_minimum_required (VERSION 3.8)

project ("CMtest")

# Zahrňte podprojekty.
add_subdirectory ("CMtest" "Project-tanks")
