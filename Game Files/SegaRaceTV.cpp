/*This file is part of Output Blaster.

Output Blaster is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Output Blaster is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Output Blaster.If not, see < https://www.gnu.org/licenses/>.*/

#include "SegaRaceTV.h"

static int WindowsLoop()
{
	imageBase = (uintptr_t)GetModuleHandleA(0);
	INT_PTR outputdataBase1 = *(INT_PTR*)(imageBase + 0x62B78);
	INT_PTR outputdataBase2 = *(INT_PTR*)(outputdataBase1 + 0x7F0);
	INT_PTR outputdataBase3 = *(INT_PTR*)(outputdataBase2 + 0xD4);
	BYTE outputdataBase4 = *(BYTE*)(outputdataBase3 + 0xC);
	BYTE outputdataBase5 = *(BYTE*)(outputdataBase3 + 0xD);

	if (outputdataBase4 == 0x80)
	{
		Outputs->SetValue(OutputLampStart, 0x01);
	}
	else
	{
		Outputs->SetValue(OutputLampStart, 0x00);
	}
	Outputs->SetValue(OutputLampView1, !!(outputdataBase4 & 0x8));
	Outputs->SetValue(OutputBoost, !!(outputdataBase4 & 0x10));
	Outputs->SetValue(OutputLampRed, !!(outputdataBase4 & 0x1));
	Outputs->SetValue(OutputLampRed2, !!(outputdataBase5 & 0x40));
	Outputs->SetValue(OutputLampBlue, !!(outputdataBase4 & 0x2));
	Outputs->SetValue(OutputLampBlue2, !!(outputdataBase5 & 0x80));
	return 0;
}

static DWORD WINAPI OutputsAreGo(LPVOID lpParam)
{
	while (true)
	{
		WindowsLoop();
		Sleep(16);
	}
}

void SRTV::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = new CWinOutputs();
		m_game.name = "Sega Race TV";
		Outputs->SetGame(m_game);
		Outputs->Initialize();
		Outputs->Attached();
		CreateThread(NULL, 0, OutputsAreGo, NULL, 0, NULL);
		while (GetMessage(&Msg1, NULL, NULL, 0))
		{
			TranslateMessage(&Msg1);
			DispatchMessage(&Msg1);
		}
		init = true;
	}
}