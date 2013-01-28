
/***************************************************************************
 *   Copyright (C) 2008 by Vorobyov Dmitry                                 *
 *   eyesguard@yandex.ru                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   The official publication of the license GNU GPL you can find here:    *
 *   http://www.gnu.org/licenses/gpl.html                                  *
 ***************************************************************************/

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BreakForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBreakWnd *BreakWnd;

//---------------------------------------------------------------------------
__fastcall TBreakWnd::TBreakWnd(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TBreakWnd::FormClose(TObject *Sender, TCloseAction &Action)
{
 MainWnd->IsBreakNow = true;
 MainWnd->IsWarningNow = true;
 MainWnd->TimerTimer(BreakWnd);
}
//---------------------------------------------------------------------------

void __fastcall TBreakWnd::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
 if ((MainWnd->EnMonOff) && (MainWnd->IsBreakNow))
        SendMessage(Handle,WM_SYSCOMMAND,SC_MONITORPOWER,1);
}
//---------------------------------------------------------------------------

void __fastcall TBreakWnd::FormShow(TObject *Sender)
{
 SetFocus();        
}
//---------------------------------------------------------------------------


