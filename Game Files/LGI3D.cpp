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

#include "LGI3D.h"

static VOID CALLBACK OutputsAreGo(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	imageBase = (uintptr_t)GetModuleHandleA(0);
	BYTE outputBase = *(BYTE *)(imageBase + 0x65DA20);
	BYTE outputData = *(BYTE *)(outputBase + 0x44);
	BYTE outputData2 = *(BYTE *)(outputBase + 0x45);

	Outputs->SetValue(OutputLampStart, !!(outputData & 0x80));
	Outputs->SetValue(Output1pKnock, !!(outputData & 0x20));
	Outputs->SetValue(Output1pMotor, !!(outputData & 0x40));
	Outputs->SetValue(Output2pKnock, !!(outputData & 0x04));
	Outputs->SetValue(Output2pMotor, !!(outputData & 0x08));
	Outputs->SetValue(Output2pLampStart, !!(outputData & 0x10));
	Outputs->SetValue(OutputVisualChange3D, !!(outputData & 0x02));
	Outputs->SetValue(Output1pAirFront, !!(outputData2 & 0x80));
	Outputs->SetValue(Output1pAirRear, !!(outputData2 & 0x20));
	Outputs->SetValue(Output2pAirFront, !!(outputData2 & 0x40));
	Outputs->SetValue(Output2pAirRear, !!(outputData2 & 0x10));
	Outputs->SetValue(OutputRawLamps, outputData & outputData2);
}

void LGI3D::OutputsGameLoop()
{
	if (!init)
	{
		Outputs = new CWinOutputs();
		m_game.name = "Let's Go Island 3D";
		Outputs->SetGame(m_game);
		Outputs->Initialize();
		Outputs->Attached();
		SetTimer(0, 0, Output_Time, (TIMERPROC)OutputsAreGo);
		while (GetMessage(&Msg1, NULL, NULL, 0))
		{
			TranslateMessage(&Msg1);
			DispatchMessage(&Msg1);
		}
		init = true;
	}
}