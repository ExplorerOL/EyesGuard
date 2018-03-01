
/*********************************************************************
*                                                                    *
* EyesGuard - программа для тех, кто хочет сохранить свое зрение,    *
*             работая на компьютере.                                 *
* Сайт программы www.eyesguard.org                                   *
*    © Воробьев Дмитрий (eyesguard@yandex.ru), 2011,                 *
*    © Буряков Михаил   (mihail.buryakov@gmail.com), 2012.           *
*    Данная программа является свободным программным обеспечением.   *
* Вы вправе распространять ее и/или модифицировать в соответствии    *
* с условиями Генеральной Общественной Лицензии GNU в том виде,      *
* как она была опубликована Фондом Свободного ПО                     *
* (Free Software Foundation); либо версии                            *
* 2 Лицензии либо (по вашему желанию) любой более поздней версии.    *
*                                                                    *
* Программа распространяется в надежде, что она будет полезной,      *
* но БЕЗ КАКИХ БЫ ТО НИ БЫЛО ГАРАНТИЙНЫХ ОБЯЗАТЕЛЬСТВ; даже без      *
* косвенных гарантийных обязательств, связанных с ПОТРЕБИТЕЛЬСКИМИ   *
* СВОЙСТВАМИ и ПРИГОДНОСТЬЮ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Для получения    *
* более подробной информации ознакомьтесь с Генеральной              *
* Общественной Лицензией GNU (http://www.gnu.org/licenses/gpl.html). *
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
//extern PACKAGE TBreakWnd *BreakWnd;
//---------------------------------------------------------------------------
#endif
