// Copyright (C) 2003-2009 Dolphin Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official SVN repository and contact information can be found at
// http://code.google.com/p/dolphin-emu/

#ifndef __PADCONFIGDIALOG_h__
#define __PADCONFIGDIALOG_h__

#include <iostream>
#include <vector>

#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/gbsizer.h>
#include "Config.h"

#if defined(HAVE_X11) && HAVE_X11
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/keysym.h>
	#include <X11/XKBlib.h>
	#include "X11InputBase.h"
#endif

class WiimotePadConfigDialog : public wxDialog
{
	public:
		WiimotePadConfigDialog(wxWindow *parent,
			wxWindowID id = 1,
			const wxString &title = wxT("Wii Remote Plugin Configuration"),
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = wxDEFAULT_DIALOG_STYLE | wxWANTS_CHARS);
		virtual ~WiimotePadConfigDialog(){;}

		void CloseClick(wxCommandEvent& event);
		void UpdateGUI(int Slot = 0);
		void UpdateGUIButtonMapping(int controller);
		void UpdateControls();
		void OnKeyDown(wxKeyEvent& event);
		void Convert2Box(int &x);
		void ConvertToString();
		void OnButtonTimer(wxTimerEvent& WXUNUSED(event)) { DoGetButtons(GetButtonWaitingID); }
		void UpdatePad(wxTimerEvent& WXUNUSED(event));

		wxTimer *m_UpdatePad,
				*m_ButtonMappingTimer;

		wxStaticBitmap  *m_bmpDotLeftIn[4],
						*m_bmpDotLeftOut[4],
						*m_bmpDotRightIn[4],
						*m_bmpDotRightOut[4],
						*m_bmpDeadZoneLeftIn[4],
						*m_bmpDeadZoneRightIn[4];
	private:
		DECLARE_EVENT_TABLE();

		bool ControlsCreated;
		int Page, BoxW, BoxH, g_Pressed;

		wxNotebook *m_Notebook;
		wxPanel *m_Controller[4];
		wxButton *m_Close,
				 *m_Apply;
		wxBoxSizer  *m_MainSizer,
					*m_sMain[4],
					*m_SizeParent[4];

		wxCheckBox  *m_CheckC2S[4],
					*m_TiltInvertRoll[4],
					*m_TiltInvertPitch[4];

		// Emulated Wiimote key settings		
		wxBoxSizer  *m_HorizControllers[4],
					*m_gC2SDeadZone[4],
					*m_gCircle2Square[4],
					*m_gCircle2SquareVert[4],
					*m_gDeadZone[4],
					*m_gDeadZoneHoriz[4],
					*m_HorizControllerTiltParent[4],
					*m_HorizControllerTilt[4],
					*m_TiltHoriz[4],
					*m_SizeAnalogLeft[4],
					*m_SizeAnalogLeftHorizX[4],
					*m_SizeAnalogLeftHorizY[4],
					*m_SizeAnalogRight[4],
					*m_SizeAnalogRightHorizX[4],
					*m_SizeAnalogRightHorizY[4],
					*m_SizeAnalogTriggerVertLeft[4],
					*m_SizeAnalogTriggerVertRight[4],
					*m_SizeAnalogTriggerHorizInput[4],

					*m_HorizControllerMapping[4],
					*m_Sizer_Wiimote[WM_CONTROLS][4],
					*m_SWmVertLeft[4],
					*m_SWmVertRight[4],
					*m_Sizer_NunChuck[NC_CONTROLS][4],
					*m_NunchuckStick[4],
					*m_Sizer_Classic[CC_CONTROLS][4],
					*m_SCcVertLeft[4],
					*m_SCcVertMiddle[4],
					*m_SCcVertRight[4],
					*m_SCcLeftStick[4],
					*m_SCcRightStick[4],
					*m_SCcTriggers[4],
					*m_sizer_GH3[GH3_CONTROLS][4],
					*m_sGH3_Analog[4],
					*m_SGH3VertLeft[4],
					*m_SGH3VertMiddle[4],
					*m_SGH3VertRight[4];

		wxGridBagSizer *m_SizeAnalogTriggerHorizConfig[4], *m_SizeAnalogTriggerStatusBox[4], *m_TiltGrid[4],
			*m_GridLeftStick[4], *m_GridRightStick[4];
		wxStaticBoxSizer *m_SizeBasic[4], *m_SizeEmu[4], *m_SizeReal[4], *m_SizeExtensions[4], *m_SizerIRPointer[4], *m_gTilt[4], *m_gJoyname[4];
		wxTextCtrl *m_AnalogLeftX[4], *m_AnalogLeftY[4], *m_AnalogRightX[4], *m_AnalogRightY[4],
			*m_AnalogTriggerL[4], *m_AnalogTriggerR[4];
		wxButton *m_bAnalogLeftX[4], *m_bAnalogLeftY[4], *m_bAnalogRightX[4], *m_bAnalogRightY[4],
			*m_bAnalogTriggerL[4], *m_bAnalogTriggerR[4],
			// Nunchuck

			*m_Button_Wiimote[WM_CONTROLS][4],
			*m_Button_NunChuck[NC_CONTROLS][4],
			*m_Button_Classic[CC_CONTROLS][4],
			*m_Button_GH3[GH3_CONTROLS][4],
			*m_bGH3_Analog[4];

		wxStaticText *m_TextScreenWidth[4], *m_TextScreenHeight[4], *m_TextScreenLeft[4], *m_TextScreenTop[4], *m_TextAR[4],
			*m_tAnalogX[8], *m_tAnalogY[8], *m_TiltTextRoll[4], *m_TiltTextPitch[4],
			*m_CheckC2SLabel[4], *m_ComboDeadZoneLabel[4], *m_TStatusLeftIn[4], *m_TStatusLeftOut[4], *m_TStatusRightIn[4], *m_TStatusRightOut[4],
			*m_TriggerStatusL[4], *m_TriggerStatusR[4], *m_TriggerStatusLx[4], *m_TriggerStatusRx[4],
			*m_tAnalogTriggerInput[4], *m_tAnalogTriggerL[4], *m_tAnalogTriggerR[4],

			*m_statictext_Wiimote[WM_CONTROLS][4],
			*m_statictext_NunChuck[NC_CONTROLS][4],
			*m_statictext_Classic[CC_CONTROLS][4],
			*m_statictext_GH3[GH3_CONTROLS][4],
			*m_NunchuckTextStick[5],
			*m_CcTextLeftStick[4],
			*m_CcTextRightStick[4],
			*m_CcTextTriggers[4],
			*m_tGH3_Analog[4];

		wxButton *ClickedButton;
		wxString OldLabel;

		wxComboBox *m_TiltComboInput[4], *m_TiltComboRangeRoll[4], *m_TiltComboRangePitch[4], *m_Joyname[4], *m_ComboDiagonal[4], *m_ComboDeadZoneLeft[4], *m_ComboDeadZoneRight[4], *m_TriggerType[4],
			*m_NunchuckComboStick[4], *m_CcComboLeftStick[4], *m_CcComboRightStick[4], *m_CcComboTriggers[4], *m_GH3ComboAnalog[4];

		wxPanel *m_pLeftInStatus[4], *m_pLeftOutStatus[4], *m_pRightInStatus[4], *m_pRightOutStatus[4];
		wxStaticBitmap *m_bmpSquareLeftIn[4], *m_bmpSquareLeftOut[4], *m_bmpSquareRightIn[4], *m_bmpSquareRightOut[4];
		wxStaticBoxSizer *m_gAnalogLeft[4], *m_gAnalogRight[4], *m_gTrigger[4],
			*m_gWiimote[4], *m_gNunchuck[4], *m_gClassicController[4], *m_gGuitarHero3Controller[4];

		wxBitmap CreateBitmapDot();
		wxBitmap CreateBitmap();
		wxBitmap CreateBitmapDeadZone(int Radius);
		wxBitmap CreateBitmapClear();

		enum
		{
			ID_CLOSE = 1000,
			ID_APPLY,
			IDTM_EXIT,
			IDTM_BUTTON,
			IDTM_UPDATE_PAD, // Timer

			ID_NOTEBOOK,
			ID_CONTROLLERPAGE1,
			ID_CONTROLLERPAGE2,
			ID_CONTROLLERPAGE3,
			ID_CONTROLLERPAGE4,

			// Gamepad <It's important that the internal ordering of these are unchanged>
			IDB_ANALOG_LEFT_X, IDB_ANALOG_LEFT_Y,
			IDB_ANALOG_RIGHT_X, IDB_ANALOG_RIGHT_Y,
			IDB_TRIGGER_L, IDB_TRIGGER_R,

			ID_ANALOG_LEFT_X, ID_ANALOG_LEFT_Y,
			ID_ANALOG_RIGHT_X, ID_ANALOG_RIGHT_Y,
			ID_TRIGGER_L, ID_TRIGGER_R,

			// Wiimote
			IDS_WIDTH, IDS_HEIGHT, IDS_LEFT, IDS_TOP,
			IDB_WM_A, IDB_WM_B,
			IDB_WM_1, IDB_WM_2,
			IDB_WM_P, IDB_WM_M, IDB_WM_H,
			IDB_WM_L, IDB_WM_R, IDB_WM_U, IDB_WM_D,
			IDB_WM_SHAKE, IDB_WM_PITCH_L, IDB_WM_PITCH_R,

			// Nunchuck
			IDB_NC_Z,
			IDB_NC_C,
			IDB_NC_L,
			IDB_NC_R,
			IDB_NC_U,
			IDB_NC_D,
			IDB_NC_SHAKE,

			// Classic Controller
			IDB_CC_A, IDB_CC_B,
			IDB_CC_X, IDB_CC_Y,
			IDB_CC_P, IDB_CC_M, IDB_CC_H,
			IDB_CC_TL, IDB_CC_ZL, IDB_CC_ZR, IDB_CC_TR,
			IDB_CC_DL, IDB_CC_DU, IDB_CC_DR, IDB_CC_DD, // Digital pad
			IDB_CC_LL, IDB_CC_LU, IDB_CC_LR, IDB_CC_LD, // Left analog stick
			IDB_CC_RL, IDB_CC_RU, IDB_CC_RR, IDB_CC_RD, // Right analog stick

			// Guitar Hero 3 Controller
			IDB_GH3_GREEN,
			IDB_GH3_RED,
			IDB_GH3_YELLOW,
			IDB_GH3_BLUE,
			IDB_GH3_ORANGE,
			IDB_GH3_PLUS,
			IDB_GH3_MINUS,
			IDB_GH3_WHAMMY,
			IDB_GH3_ANALOG_LEFT,
			IDB_GH3_ANALOG_UP,
			IDB_GH3_ANALOG_RIGHT,
			IDB_GH3_ANALOG_DOWN,
			IDB_GH3_STRUM_UP,
			IDB_GH3_STRUM_DOWN,

			// Gamepad settings
			IDC_JOYNAME, IDC_LEFT_C2S, IDCB_LEFT_DIAGONAL, IDCB_DEAD_ZONE_LEFT, IDCB_DEAD_ZONE_RIGHT,
			ID_TRIGGER_TYPE, ID_TILT_INPUT, ID_TILT_RANGE_ROLL, ID_TILT_RANGE_PITCH, ID_TILT_INVERT_ROLL, ID_TILT_INVERT_PITCH,
			IDCB_NUNCHUCK_STICK, IDCB_CC_LEFT_STICK, IDCB_CC_RIGHT_STICK, IDCB_CC_TRIGGERS, IDCB_GH3_ANALOG,
		};

		void OnClose(wxCloseEvent& event);
		void CreatePadGUIControls();
		void GeneralSettingsChanged(wxCommandEvent& event);

		// Gamepad configuration
		void SetButtonText(int id, char text[128], int _Page = -1); void SetButtonTextAll(int id, char text[128]);
		wxString GetButtonText(int id, int Page = -1);
		void GetButtons(wxCommandEvent& event); void DoGetButtons(int);
		void SaveButtonMapping(int controller, bool DontChangeId = false, int FromSlot = -1); void SaveButtonMappingAll(int Slot);
		void SaveKeyboardMapping(int Controller, int Id, int Key);
		void ToBlank(bool ToBlank = true);
		void PadGetStatus();
		void DoSave(bool ChangePad = false, int Slot = -1);
		void DoChangeJoystick(); void PadOpen(int Open); void PadClose(int Close); void DoChangeDeadZone(bool Left);
		void OnButtonClick(wxCommandEvent& event);

		// Configure buttons
		int GetButtonWaitingID, GetButtonWaitingTimer;
};
extern WiimotePadConfigDialog *m_PadConfigFrame;
#endif
