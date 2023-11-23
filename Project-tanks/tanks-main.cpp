#include <iostream>
#include <chrono>
#include <conio.h>
#include <windows.h>
#include <string>

const int nScreenWidth = 90; // Console Screen Size X (columns)
const int nScreenHeight = 40; // Console Screen Size Y (rows)
const int fontSize = 16; // Font size for the console

// Function prototypes
void SetConsoleProperties(int width, int height, int fontSz);
void clearScreen(char* screen, int width, int height);
void WriteStringToBuffer(char* screen, const std::string& text, int x, int y, int width);

int main() {
    // Set console properties
    SetConsoleProperties(nScreenWidth, nScreenHeight, fontSize);

    // Create screen buffer
    char* screen = new char[nScreenWidth * nScreenHeight + 1];
    screen[nScreenWidth * nScreenHeight] = '\0';

    // Game loop
    while (true) {
        // Clear screen
        clearScreen(screen, nScreenWidth, nScreenHeight);

        // Check for key press
        if (_kbhit()) {
            int key = _getch(); // Get the keycode of the pressed key

            // Check if the key is the down arrow
            if (key == 224) { // Arrow keys are preceded by a 224 or 0xE0
                key = _getch(); // Get the actual key code
                if (key == 80) { // Down arrow keycode
                    // Write "Hello, World!" to the center of the screen
                    std::string text = "Hello, World!";
                    int x = nScreenWidth / 2 - text.length() / 2;
                    int y = nScreenHeight / 2;
                    WriteStringToBuffer(screen, text, x, y, nScreenWidth);
                }
            }
        }

        // Write buffer to console
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwBytesWritten = 0;
        WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);

        // Sleep for a short time
        Sleep(100);
    }

    // Clean up
    delete[] screen;
    return 0;
}

// Set properties for the console window, buffer size, and font size
void SetConsoleProperties(int width, int height, int fontSz) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set the font size first to ensure the console window does not exceed screen size
    CONSOLE_FONT_INFOEX cfi = { sizeof(cfi) };
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = fontSize;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(hStdOut, FALSE, &cfi);

    // Set the buffer size
    COORD coord = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
    SetConsoleScreenBufferSize(hStdOut, coord);

    // Set the size of the console window
    SMALL_RECT rectWindow = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };
    SetConsoleWindowInfo(hStdOut, TRUE, &rectWindow);
}

// Clear the screen buffer
void clearScreen(char* screen, int width, int height) {
    for (int i = 0; i < width * height; ++i) {
        screen[i] = ' ';
    }
}

// Write a string to the buffer at (x, y)
void WriteStringToBuffer(char* screen, const std::string& text, int x, int y, int width) {
    if (y >= 0 && y < nScreenHeight) {
        for (size_t i = 0; i < text.size(); ++i) {
            if (x + i >= 0 && x + i < width) {
                screen[y * width + x + i] = text[i];
            }
        }
    }
}
