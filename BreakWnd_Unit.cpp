
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

#include <vcl.h>
#pragma hdrstop

#include "BreakWnd_Unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGAUGES"
#pragma resource "*.dfm"
TBreakWnd *BreakWnd;

//---------------------------------------------------------------------------
//Конструктор формы
__fastcall TBreakWnd::TBreakWnd(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------

//Действия при закрытии формы
void __fastcall TBreakWnd::FormClose(TObject *Sender, TCloseAction &Action)
{
 EGState.interruptBreak();
}
//---------------------------------------------------------------------------

//Перевод фокуса на форму перерыва, он не остался на предыдущем приложении

void __fastcall TBreakWnd::FormShow(TObject *Sender)
{
 SetFocus();
}
//---------------------------------------------------------------------------







