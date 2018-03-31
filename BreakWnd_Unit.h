
/*********************************************************************
*                                                                    *
* EyesGuard - cares about youe vision during working on PC!                               *
* Site of program http://eyesguard.ru                                *
*                              					     *
*    © Dmitry Vorobjev (eyesguard@yandex.ru), 2011,                  *
*    © Mihail Buryakov   (mihail.buryakov@gmail.com), 2012,          *
*    © Dmitry Vorobjev (eyesguard@yandex.ru), 2018.                  *
*   This program is free software; you can redistribute it and/or    *
*   modify it under the terms of the GNU General Public License as   *
*   published by the Free Software Foundation; either version 2 of   *
*   the License, or at your option) any later version.               *
*                                                                    *
*   This program is distributed in the hope that it will be useful,  *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of   *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    *
*   GNU General Public License for more details.                     *
*                                                                    *
*   The official publication of the license GNU GPL you can          *
*   find here: http://www.gnu.org/licenses/gpl.html                  *
*                                                                    *
*********************************************************************/

//---------------------------------------------------------------------------

#ifndef BreakWnd_UnitH
#define BreakWnd_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MainWnd_Unit.h"
#include "CGAUGES.h"
//---------------------------------------------------------------------------
class TBreakWnd : public TForm
{
__published:	// IDE-managed Components
        TLabel *BreakLabel1;
        TLabel *BreakLabel2;
	TLabel *LabelTimeBreakLeft;
	TCGauge *GaugeBreakProgress;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TBreakWnd(TComponent* Owner);

};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#endif
