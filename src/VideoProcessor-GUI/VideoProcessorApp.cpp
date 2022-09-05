/*
 * Copyright(C) 2021 Dennis Fleurbaaij <mail@dennisfleurbaaij.com>
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 3.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program. If not, see < https://www.gnu.org/licenses/>.
 */

#include <pch.h>

#include <winnt.h>
extern "C" {
#include <libavutil/log.h>
}

#include <VideoProcessorDlg.h>

#include "VideoProcessorApp.h"


BEGIN_MESSAGE_MAP(CVideoProcessorApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


CVideoProcessorApp videoProcessorApp;


void av_log_callback(void* ptr, int level, const char* fmt, va_list vargs)
{
	vprintf(fmt, vargs);
}


BOOL CVideoProcessorApp::InitInstance()
{
	// Setup ffmpeg logging
	av_log_set_callback(av_log_callback);
#ifdef _DEBUG
	av_log_set_level(AV_LOG_TRACE);
#endif

	CVideoProcessorDlg dlg;
	m_pMainWnd = &dlg;

	try
	{
		bool start = true;
		if (!CWinAppEx::InitInstance())
			throw std::runtime_error("Failed to initialize VideoProcessorApp");

		// COINIT_MULTITHREADED was used in the Blackmagic SDK examples,
		// using that without further investigation
		if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
			throw std::runtime_error("Failed to initialize com objects");

		// Parse command line
		// https://docs.microsoft.com/en-us/cpp/c-runtime-library/argc-argv-wargv
		int iNumOfArgs;
		LPWSTR* pArgs = CommandLineToArgvW(GetCommandLine(), &iNumOfArgs);
		for (int i = 1; i < iNumOfArgs; i++)
		{
			// /fullscreen
			if (wcscmp(pArgs[i], L"/fullscreen") == 0)
			{
				dlg.StartFullScreen();
			}

<<<<<<< Updated upstream
			// /renderer "name"
			if (wcscmp(pArgs[i], L"/renderer") == 0 && (i + 1) < iNumOfArgs)
			{
				dlg.DefaultRendererName(pArgs[i + 1]);
			}
=======
			
			// /renderer "name"
			if (wcscmp(pArgs[i], L"-r") == 0 && (i + 1) < iNumOfArgs)
			{
				dlg.DefaultRendererName(pArgs[i + 1]);
			}

			// /frame_offset [-value|"auto"]
			if (wcscmp(pArgs[i], L"-fo") == 0 && (i + 1) < iNumOfArgs)
			{
				if (wcscmp(pArgs[i + 1], L"auto") == 0)
				{
					dlg.StartFrameOffsetAuto();
				}
				else
				{
					dlg.StartFrameOffset(pArgs[i + 1]);
				}
			}

			//Set conversion overide
			if (wcscmp(pArgs[i], L"-o") == 0)
			{
				dlg.setConversionOveride();
			}

			//Color Space
			if (wcscmp(pArgs[i], L"-cs") == 0 && (i + 1) < iNumOfArgs)
			{
				if (wcscmp(pArgs[i + 1], L"BT.2020") == 0)
				{
					dlg.setColorSpace(1);
				}else if (wcscmp(pArgs[i + 1], L"P3-D65") == 0)
				{
					dlg.setColorSpace(2);
				}
				else if (wcscmp(pArgs[i + 1], L"P3-DCI") == 0)
				{
					dlg.setColorSpace(3);
				}
				else if (wcscmp(pArgs[i + 1], L"P3-D60") == 0)
				{
					dlg.setColorSpace(4);
				}
				else if (wcscmp(pArgs[i + 1], L"REC.709") == 0)
				{
					dlg.setColorSpace(5);
				}
				else if (wcscmp(pArgs[i + 1], L"REC.601 (NTSC)") == 0)
				{
					dlg.setColorSpace(6);
				}
				else if (wcscmp(pArgs[i + 1], L"REC.601 (PAL/SECAM)") == 0)
				{
					dlg.setColorSpace(7);
				}
				else {
					start = false;
					printf("Error: Color Space not found\nOnly these color spaces are allowed:\nBT.2020, P3-D65, P3-D60, REC.709, REC.601 (NTSC), REC.601 (PAL/SECAM)");
				}

				

			}

			//HDR Colorspace
			if (wcscmp(pArgs[i], L"-HDR_cs") == 0 && (i + 1) < iNumOfArgs)
			{
				if (wcscmp(pArgs[i + 1], L"LLDV") == 0)
				{
					dlg.setHDRColorSpace(1);
				}
				else if (wcscmp(pArgs[i + 1], L"follow container") == 0)
				{
					dlg.setHDRColorSpace(2);
				}
				else if (wcscmp(pArgs[i + 1], L"BT.2020") == 0)
				{
					dlg.setHDRColorSpace(3);
				}
				else if (wcscmp(pArgs[i + 1], L"P3") == 0)
				{
					dlg.setHDRColorSpace(4);
				}
				else if (wcscmp(pArgs[i + 1], L"REC709") == 0)
				{
					dlg.setHDRColorSpace(5);
				}
				else 
				{
					start = false;
					printf("Error: HDR Color Space not found\nOnly these HDR color spaces are allowed:\nLLDV, follow container, BT.2020, P3, REC709");
				}

			}

			//HDR Luminace
			if (wcscmp(pArgs[i], L"-HDR_l") == 0 && (i + 1) < iNumOfArgs)
			{
				if (wcscmp(pArgs[i + 1], L"LLDV") == 0){
					dlg.setHDRLuminance(1);
				}
				else if (wcscmp(pArgs[i + 1], L"user") == 0)
				{
					dlg.setHDRLuminance(2);
				}
				else 
				{
					start = false;
					printf("Error: HDR Color Space not found\nOnly these HDR color spaces are allowed:\nLLDV, user");
				}

			}

			//Queue
			if (wcscmp(pArgs[i], L"-q") == 0)
			{

			}

			//Start Stop
			if (wcscmp(pArgs[i], L"-ss") == 0 && (i + 1) < iNumOfArgs)
			{
				if (wcscmp(pArgs[i + 1], L"Clock-Theo") == 0)
				{
					dlg.setStartStop(1);
				}
				else if (wcscmp(pArgs[i + 1], L"Clock-Clock") == 0)
				{
					dlg.setStartStop(2);

				}
				else if (wcscmp(pArgs[i + 1], L"Theo-Theo") == 0)
				{
					dlg.setStartStop(3);

				}
				else if (wcscmp(pArgs[i + 1], L"Clock-None") == 0)
				{
					dlg.setStartStop(4);

				}
				else if (wcscmp(pArgs[i + 1], L"Theo-None") == 0)
				{
					dlg.setStartStop(5);

				}
				else if (wcscmp(pArgs[i + 1], L"None") == 0)
				{
					dlg.setStartStop(6);

				}
				else {
					start = false;
					printf("Error: Start Stop type not found\nOnly these Start Stop types are allowed:\Clock-Theo, Clock-Clock, Theo-Theo, Theo-None, None");
				}
>>>>>>> Stashed changes

			// /frame_offset [-value|"auto"]
			if (wcscmp(pArgs[i], L"/frame_offset") == 0 && (i + 1) < iNumOfArgs)
			{
				if (wcscmp(pArgs[i + 1], L"auto") == 0)
				{
					dlg.StartFrameOffsetAuto();
				}
				else
				{
					dlg.StartFrameOffset(pArgs[i + 1]);
				}
			}

			//Nominal Range
			if (wcscmp(pArgs[i], L"-nr") == 0 && (i + 1) < iNumOfArgs)
			{
				if (wcscmp(pArgs[i + 1], L"Full") == 0)
				{
					dlg.setRange(1);
				}
				else if (wcscmp(pArgs[i + 1], L"Limited") == 0)
				{
					dlg.setRange(2);
				}
				else if (wcscmp(pArgs[i + 1], L"Small") == 0)
				{
					dlg.setRange(3);
				}
				else {
					start = false;
					printf("Error: Nominal Range not found\nOnly these nominal ranges are allowed:\Full, Limited, Small");
				}

			}

			//Transfer Function
			if (wcscmp(pArgs[i], L"-tf") == 0 && (i + 1) < iNumOfArgs)
			{
				if (wcscmp(pArgs[i + 1], L"PQ") == 0)
				{
					dlg.setTransferFunction(1);
				}
				else if (wcscmp(pArgs[i + 1], L"REC709(y2.2)") == 0)
				{
					dlg.setTransferFunction(2);
				}
				else if (wcscmp(pArgs[i + 1], L"BT.2020 constant") == 0)
				{
					dlg.setTransferFunction(3);
				}
				else if (wcscmp(pArgs[i + 1], L"True gamma 1.8") == 0)
				{
					dlg.setTransferFunction(4);
				}
				else if (wcscmp(pArgs[i + 1], L"True gamma 2.0") == 0)
				{
					dlg.setTransferFunction(5);
				}
				else if (wcscmp(pArgs[i + 1], L"True gamma 2.2") == 0)
				{
					dlg.setTransferFunction(6);
				}
				else if (wcscmp(pArgs[i + 1], L"True gamma 2.4") == 0)
				{
					dlg.setTransferFunction(7);
				}
				else if (wcscmp(pArgs[i + 1], L"True gamma 2.6") == 0)
				{
					dlg.setTransferFunction(8);
				}
				else if (wcscmp(pArgs[i + 1], L"True gamma 2.8") == 0)
				{
					dlg.setTransferFunction(9);
				}
				else if (wcscmp(pArgs[i + 1], L"Liner RGB (y1)") == 0)
				{
					dlg.setTransferFunction(10);
				}
				else if (wcscmp(pArgs[i + 1], L"204M(y2.2)") == 0)
				{
					dlg.setTransferFunction(11);
				}
				else if (wcscmp(pArgs[i + 1], L"8-bit gamma 2.2") == 0)
				{
					dlg.setTransferFunction(12);
				}
				else if (wcscmp(pArgs[i + 1], L"Log 100:1 H.264") == 0)
				{
					dlg.setTransferFunction(13);
				}
				else if (wcscmp(pArgs[i + 1], L"Log 316:1 H.264") == 0)
				{
					dlg.setTransferFunction(14);
				}
				else if (wcscmp(pArgs[i + 1], L"REC709(y2.2) symmetric") == 0)
				{
					dlg.setTransferFunction(15);
				}
				else if (wcscmp(pArgs[i + 1], L"BT.2020 non-const") == 0)
				{
					dlg.setTransferFunction(16);
				}
				else if (wcscmp(pArgs[i + 1], L"Hybrid Log") == 0)
				{
					dlg.setTransferFunction(17);
				}
				else {
					start = false;
					printf("Error: Transfer Function not found\nOnly these Transfer Functions are allowed:\n");
					printf("PQ, REC709(y2.2), BT.2020 constant, True gamma 1.8, True gamma 2.0, True gamma 2.2,\n");
					printf("True gamma 2.4, True gamma 2.6, True gamma 2.8,Liner RGB (y1), 204M(y2.2), 204M(y2.2),\n");
					printf("8-bit gamma 2.2, Log 100:1 H.264, Log 316:1 H.264, REC709(y2.2) symmetric,BT.2020 non-const, Hybrid Log\n");
				}

			}

			//Transfer Matrix
			if (wcscmp(pArgs[i], L"-tm") == 0 && (i + 1) < iNumOfArgs)
			{
				if (wcscmp(pArgs[i + 1], L"BT.2020 10") == 0)
				{
					dlg.setTransferMatrix(1);
				}
				else if (wcscmp(pArgs[i + 1], L"BT.2020 12") == 0)
				{
					dlg.setTransferMatrix(2);
				}
				else if (wcscmp(pArgs[i + 1], L"BT.709") == 0)
				{
					dlg.setTransferMatrix(3);

				}
				else if (wcscmp(pArgs[i + 1], L"BT.601") == 0)
				{
					dlg.setTransferMatrix(4);

				}
				else if (wcscmp(pArgs[i + 1], L"240M") == 0)
				{
					dlg.setTransferMatrix(5);

				}
				else if (wcscmp(pArgs[i + 1], L"FCC") == 0)
				{
					dlg.setTransferMatrix(6);

				}
				else if (wcscmp(pArgs[i + 1], L"YCgCo") == 0)
				{
					dlg.setTransferMatrix(7);

				}
				else {
					start = false;
					printf("Error: Transfer Matrix not found\nOnly these Transfer Matrices are allowed:\n");
					printf("BT.2020 10, BT.2020 12, BT.601, 240M, FCC, YCgCo\n");

				}
			}

			//Primaries
			if (wcscmp(pArgs[i], L"-p") == 0 && (i + 1) < iNumOfArgs)
			{
				if (wcscmp(pArgs[i + 1], L"BT.2020") == 0)
				{
					dlg.setPrimaries(1);
				}
				else if (wcscmp(pArgs[i + 1], L"DCI-P3") == 0)
				{
					dlg.setPrimaries(2);
				}
				else if (wcscmp(pArgs[i + 1], L"BT.709") == 0)
				{
					dlg.setPrimaries(3);
				}
				else if (wcscmp(pArgs[i + 1], L"NTSC SySm") == 0)
				{
					dlg.setPrimaries(4);
				}
				else if (wcscmp(pArgs[i + 1], L"NTSC SyBG") == 0)
				{
					dlg.setPrimaries(5);
				}
				else if (wcscmp(pArgs[i + 1], L"CIE 1931 XYZ") == 0)
				{
					dlg.setPrimaries(6);
				}
				else if (wcscmp(pArgs[i + 1], L"ACES") == 0)
				{
					dlg.setPrimaries(7);
				}
				else {
					start = false;
					printf("Error: Transfer Matrix not found\nOnly these Transfer Matrices are allowed:\n");
					printf("BT.2020, DCI-P3, BT.709, NTSC SySm, NTSC SyBG, CIE 1931 XYZ, ACES\n");

				}

			}

			//Help
			if (wcscmp(pArgs[i], L"-h") == 0)
			{	
				//Set Window not to start
				start = false;

				//Print help message
				printf("Video Processor\n");
				printf("Ussage:\n");
				printf("-f                          |	Open to fullscreen\n");
				printf("-r [renderer name]          |	sets renderer\n");
				printf("-fo Auto | number           |	Sets Frame offset\n");
				printf("-o                          |	Sets Video conversion to v210 to p010\n");
				printf("-cs [color sapce]           |	Configures colospace overide\n");
				printf("-HDR_cs [HDR Color Space]   |	Configures HDR Color Space overide\n");
				printf("-HDR_l [HDR Luminace]       |	Configures HDR Luminence overide\n");
				//printf("-MaxCLL [value]             |	Sets User MaxCLL\n");
				//printf("-MaxFALL [value]            |	Sets User MaxFall\n");	
				//printf("-Disp_MSTR_L [value]        |	Sets User Display Master Low\n");
				//printf("-Disp_MSTR_H [value]        |	Sets User Display Master High\n");
				//printf("-q use | number | auto      |	Configures the Queue\n");
				printf("-ss [value]                 |	Configures start stop\n");
				printf("-nr [value]                 |	Configures Nominal Range\n");
				printf("-tf [value]                 |	Configures Transfer Fucntion\n");
				printf("-tm [value]                 |	Configures Transfer Matrix\n");
				printf("-p [value]                  |	Configures Primaries\n");
				printf("-h                          |	Displays this message\n");

			}



		}

		// Set set ourselves to high prio.
		if (!SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS))
			throw std::runtime_error("Failed to set process priority");
		if (start) {
			dlg.DoModal();
		}
	}
	catch (std::runtime_error& e)
	{
		dlg.EndDialog(IDABORT);

		size_t size = strlen(e.what()) + 1;
		wchar_t* wtext = new wchar_t[size];
		size_t outSize;
		mbstowcs_s(&outSize, wtext, size, e.what(), size - 1);

		MessageBox(nullptr, wtext, TEXT("Fatal error"), MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

		delete[] wtext;
	}

	CoUninitialize();

	return FALSE;
}


// Only here for debugging purposes where the application is compiled as a console application.
int main() {
	return _tWinMain(GetModuleHandle(NULL), NULL, GetCommandLine(), SW_SHOW);
}
