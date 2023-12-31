﻿#include "CMtest.h"
#include <iostream>
//#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <conio.h>
using namespace std;

#include <stdio.h>
#include <Windows.h>

const int  nScreenWidth = 240;			// Console Screen Size X (columns)
const int nScreenHeight = 63;			// Console Screen Size Y (rows)

int state = 0;
float fPlayerX = 14.7f;			// Player Start Position
float fPlayerY = 5.09f;
float fPlayerA = 0.0f;			// Player Start Rotation
float fFOV = 3.14159f / 4.0f;	// Field of View
float fDepth = 16.0f;			// Maximum rendering distance
float fSpeed = 5.0f;			// Walking Speed



char* screen = new char[(nScreenWidth * nScreenHeight)+1];
char screen2D[nScreenHeight][nScreenWidth];



typedef struct {
	const char* text;
	bool togled;
	int x;
	int y;
} tlacitko;
typedef struct {
	float uhelHlavne;
	int x;
	int y;
} tank;
void vykresliTank(tank tank, int floorHeight);
void zapissloubeczeme(int vyskaSloupce);
void clearScreen();
void clearScreen(char vypln);
void nakresliBod(int x, int y, char vypln);
int zjistiBodZSouradnic(int x, int y);
void nakresliObdelnik(int x, int y, int vyska, int delka, char vypln);
void nakresliPeknyObdelnik(int x, int y, int vyska, int delka, char vypln, int okraj);
void zapisText(int x, int y, const char text[100]);
void vypisTlacitko(tlacitko t);


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
	int playerCount = 0;
	int curentButon = 0;
	tlacitko tlacitka[3] = { {"pp1",false,10,15}, {"pp2",false,20,15}, {"pp3",false,30,15} };
	
	while (1)
	{
		if (state != 0)
			break;
		//ukradl cas jsem a necha jsem to tady 
		//mby bude potreba na tu balistickou vec
		tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();
		//cispa ruznych potrebnych znaku ktere se budou hodit a jsou jinak než v normalnim ascii protože cmako je stupid   //176:░ ,177:▒ ,178:▓   219:█   220:▄ 223:▀  179:│, 180:┤, 191:┐,192:└, 193:┴, 194:┬, 195:├, 196:─, 197:┼ 217:┘, 218:┌, 185:╣ 186:║ 187:╗ 188:╝  200:╚, 201:╔, 202:╩, 203:╦, 204:╠, 205:═, 206:╬, 
		    clearScreen();
			
			nakresliBod(5, 4,'.');
			nakresliBod(10, 15,'.');
			nakresliObdelnik(12, 20, 5, 53, 176);
			nakresliPeknyObdelnik(30, 8, 42, 13, 177,1);			
			//zapisText(20, 30, "Testovaci kus textu.");

			//tlacitka
			/*vypisTlacitko(tlacitka[0]);
			vypisTlacitko(tlacitka[1]);
			vypisTlacitko(tlacitka[2]);*/
			


			//slider pocet hracu
			char pp = ' ';
			screen2D[10][10] = '0' + playerCount;
			if (_kbhit())
			{
				pp = _getch();

			}
			switch (pp)
			{
			case 72:
				playerCount++;
				break;
			case 80:
				playerCount--;
				break;
			case 75:
				for (size_t i = 0; i < sizeof(tlacitka)/sizeof(tlacitka[0]); i++)
				{
					tlacitka[i].togled = false;
				}
				if (curentButon < (sizeof(tlacitka) / sizeof(tlacitka[0])))
				{
					curentButon--;
					
				}
				else
				{
					curentButon = 0;
				}
				tlacitka[curentButon].togled = true;
				break;
			case 77:
				for (size_t i = 0; i < sizeof(tlacitka) / sizeof(tlacitka[0]); i++)
				{
					tlacitka[i].togled = false;
				}
				if (curentButon < (sizeof(tlacitka) / sizeof(tlacitka[0])))
				{
					curentButon++;

				}
				else
				{
					curentButon = 0;
				}
				tlacitka[curentButon].togled = true;
				break;
			case 'm':
				state = 1;
			break;
			default:
				break;
			}

			

				





		// Display Stats
		//sprintf(screen, "FPS=%3.0f", 1.0f / fElapsedTime);
		// Display Frame




		//for (int y = 0; y < nScreenHeight; y++) {
		//	for (int x = 0; x < nScreenWidth; x++) {
		//		screen[(x * nScreenWidth) + y] = screen2D[x][y];
		//	}
		//}
		




		//preved2dNaOutput();
		screen[nScreenWidth * nScreenHeight] = '\0';
		WriteConsoleOutputCharacter(hConsole, (LPCSTR)screen2D, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);

	}
	if (state == 1) {
		int floorHeight = 20; //potom bude pole cisel
		clearScreen();
		zapissloubeczeme(floorHeight);
		
		tank* poleTanku = (tank*)malloc(playerCount * sizeof(tank));
		poleTanku[0].uhelHlavne = 0;
		poleTanku[0].x = rand() % nScreenWidth;
		poleTanku[1].uhelHlavne = 0;
		poleTanku[1].x = rand() % nScreenWidth;
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
			vykresliTank(poleTanku[0], floorHeight);
			vykresliTank(poleTanku[1], floorHeight);




			// Display Stats
			sprintf(screen, "FPS=%3.0f", 1.0f / fElapsedTime);

			screen[nScreenWidth * nScreenHeight] = '\0';
			WriteConsoleOutputCharacter(hConsole, (LPCSTR)screen2D, nScreenWidth* nScreenHeight, { 0,0 }, & dwBytesWritten);
		}
		
	}
	return 0;
}
void vykresliTank(tank tank,int vyskaSloupce) {
	nakresliBod(tank.x, nScreenHeight - vyskaSloupce, 220);
	nakresliBod(tank.x+1, nScreenHeight - vyskaSloupce, 220);
	nakresliBod(tank.x-1, nScreenHeight - vyskaSloupce, 219);
	nakresliBod(tank.x, nScreenHeight - vyskaSloupce -1, '_');
	nakresliBod(tank.x-1, nScreenHeight - vyskaSloupce - 1, '_');
}
void zapissloubeczeme(int vyskaSloupce) { // zatim jen vypisuje jednu vysku
	for (size_t x = 0; x < nScreenWidth; x++)
	{
		for (size_t y = 0; y <nScreenHeight; y++)
		{
			if (y>(nScreenHeight - vyskaSloupce)) {
				nakresliBod(x, y, 176);
			}
		}
	}
}
void clearScreen() {
	for (int x = 0; x < nScreenWidth; x++)
	{
		for (int y = 0; y < nScreenHeight; y++)
		{
			screen2D[y][x] = ' ';
		}
	}
}
void clearScreen(char vypln) {
	for (int x = 0; x < nScreenWidth; x++)
	{
		for (int y = 0; y < nScreenHeight; y++)
		{
			screen2D[y][x] = vypln;
		}
	}
}
void nakresliBod(int x, int y, char vypln) {
	screen2D[y][x] = vypln;
}
int zjistiBodZSouradnic(int x, int y) {
	return (y * nScreenWidth) + x;
}
void nakresliObdelnik(int x, int y, int vyska, int delka, char vypln) {
	for (int pomX = 0; pomX < delka; pomX++)
	{
		for (int pomY = 0; pomY < vyska; pomY++)
		{
			screen2D[(y + pomY)][(pomX + x)] = vypln;
		}
	}
}
void nakresliPeknyObdelnik(int x, int y, int vyska, int delka, char vypln, int okraj) {
	for (int pomX = 0; pomX < delka; pomX++)
	{
		for (int pomY = 0; pomY < vyska; pomY++)
		{
			screen2D[(y + pomY)][(pomX + x)] = vypln;



			switch (okraj)
			{
			case 1:
				if (pomX == 0 && pomY == 0)
				{
					screen2D[(y + pomY)][(pomX + x)] = 218;
				}
				else if (pomX == delka - 1 && pomY == 0)
				{
					screen2D[(y + pomY)][(pomX + x)] = 191;
				}
				else if (pomX == 0 && pomY == vyska - 1)
				{
					screen2D[(y + pomY)][(pomX + x)] = 192;
				}
				else if (pomX == delka - 1 && pomY == vyska - 1)
				{
					screen2D[(y + pomY)][(pomX + x)] = 217;
				}
				else if (pomX == 0 || pomX == delka - 1)
				{
					screen2D[(y + pomY)][(pomX + x)] = 179;
				}
				else if (pomY == 0 || pomY == vyska - 1)
				{
					screen2D[(y + pomY)][(pomX + x)] = 196;
				}
				break;
			case 2:
				if (pomX == 0 && pomY == 0)
				{
					screen2D[(y + pomY)][(pomX + x)] = 201;
				}
				else if (pomX == delka - 1 && pomY == 0)
				{
					screen2D[(y + pomY)][(pomX + x)] = 187;
				}
				else if (pomX == 0 && pomY == vyska - 1)
				{
					screen2D[(y + pomY)][(pomX + x)] = 200;
				}
				else if (pomX == delka - 1 && pomY == vyska - 1)
				{
					screen2D[(y + pomY)][(pomX + x)] = 188;
				}
				else if (pomX == 0 || pomX == delka - 1)
				{
					screen2D[(y + pomY)][(pomX + x)] = 186;
				}
				else if (pomY == 0 || pomY == vyska - 1)
				{
					screen2D[(y + pomY)][(pomX + x)] = 205;
				}
				break;
			default:
				break;
			}
			
		}
	}
}
void zapisText(int x, int y,const char text[100]) {
	//sprintf(screen2D[x][y], text);
}
void vypisTlacitko(tlacitko t) {
	
	if (t.togled)
	{
		nakresliPeknyObdelnik(t.x, t.y, 3, strlen(t.text) + 3, ' ', 2);
	}
	else
	{
		nakresliPeknyObdelnik(t.x, t.y, 3, strlen(t.text) + 3, ' ', 1);
	}
	zapisText(t.x + 1, t.y + 1, t.text);
}