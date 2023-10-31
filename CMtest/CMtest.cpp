// CMtest.cpp: Definuje vstupní bod pro aplikaci.
//

#include "CMtest.h"
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
using namespace std;

#include <stdio.h>
#include <Windows.h>

int  nScreenWidth = 240;			// Console Screen Size X (columns)
int nScreenHeight = 63;			// Console Screen Size Y (rows)

byte	state = 0;
float fPlayerX = 14.7f;			// Player Start Position
float fPlayerY = 5.09f;
float fPlayerA = 0.0f;			// Player Start Rotation
float fFOV = 3.14159f / 4.0f;	// Field of View
float fDepth = 16.0f;			// Maximum rendering distance
float fSpeed = 5.0f;			// Walking Speed



char* screen = new char[(nScreenWidth * nScreenHeight)+1];
void nakresliBod(int x, int y);
void nakresliObdelnik(int x, int y, int vyska, int delka, char vypln);
int main()
{
	// Create Screen Buffer
	
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);



	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now();

	while (1)
	{
		//ukradl cas jsem a necha jsem to tady 
		//mby bude potreba na tu balistickou vec
		tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

		//switch (state) // switch je tu aby se menilo menu a gameplay ale asi bych to resil jinkak jako switch a pak while a ne naopak
		//{
		//case 0: // menu
			//nakresli obdelnik
			
			for (int i = 0; i < nScreenHeight*nScreenWidth; i++)
			{
				screen[i] = ' ';               //cispa ruznych potrebnych znaku ktere se budou hodit a jsou jinak než v normalnim ascii protože cmako je stupid   //176:░ ,177:▒ ,178:▓   219:█   220:▄ 223:▀  179:│, 180:┤, 191:┐,192:└, 193:┴, 194:┬, 195:├, 196:─, 197:┼ 217:┘, 218:┌, 185:╣ 186:║ 187:╗ 188:╝  200:╚, 201:╔, 202:╩, 203:╦, 204:╠, 205:═, 206:╬, 
			}
			nakresliBod(5, 4);
			nakresliBod(10, 15);
			
			//nakresliObdelnik(2, 6, 13, 8, 'd');        //shit dont work
			
			//napis text
			//tlacitka
			//slider pocet hracu
		//break;
		//case 1:
			//hra
		//break;
		//default:
		//break;
		//}
		//menu





		// Display Stats
		//sprintf_s(screen, 40, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f ", fPlayerX, fPlayerY, fPlayerA, 1.0f / fElapsedTime);

		// Display Map
		/*for (int nx = 0; nx < 5; nx++)
			for (int ny = 0; ny < 5; ny++)
			{
				screen[(ny + 1) * nScreenWidth + nx] = '´';
			}
		screen[((int)fPlayerX + 1) * nScreenWidth + (int)fPlayerY] = 'P';*/

		// Display Frame
		screen[nScreenWidth * nScreenHeight] = '\0';
		WriteConsoleOutputCharacter(hConsole, (LPCSTR)screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);

	}

	return 0;
}
void nakresliBod(int x, int y) {
	int bod = (y * nScreenWidth) + x;
	screen[bod] = '.';
}
void nakresliObdelnik(int x, int y, int vyska, int delka, char vypln){
	int bod = (y * nScreenWidth) + x;
	char * radek = new char[delka];
	for (int i = 0; i < delka; i++)
	{
		radek[i] = vypln;
	}

	for (int px = 0; px < vyska; px++)
	{
		
		//sprintf_s(*screen,delka,radek);
	}
}