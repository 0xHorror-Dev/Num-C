cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("Num-C")

add_executable(Num-C WIN32 "src/main.cpp" 
"src/Application/App.h" "src/Application/App.cpp"
"src/Application/WndProc.cpp" "src/Application/Events.cpp"

"src/GFX/GFX.h" "src/GFX/GFX.cpp"

"src/Converter/Converter.h" "src/Converter/Converter.cpp"
)

target_link_libraries(Num-C d2d1 dwrite dwmapi)