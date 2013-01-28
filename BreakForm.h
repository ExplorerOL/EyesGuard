
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

#ifndef BreakFormH
#define BreakFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MainForm.h"
//---------------------------------------------------------------------------
class TBreakWnd : public TForm
{
__published:	// IDE-managed Components
        TLabel *BreakLabel1;
        TLabel *BreakLabel2;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TBreakWnd(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TBreakWnd *BreakWnd;
//---------------------------------------------------------------------------
#endif
