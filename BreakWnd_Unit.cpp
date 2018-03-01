
/*********************************************************************
*                                                                    *
* EyesGuard - ��������� ��� ���, ��� ����� ��������� ���� ������,    *
*             ������� �� ����������.                                 *
* ���� ���������                                                     *
*    � �������� ������� (eyesguard@yandex.ru), 2011,                 *
*    � ������� ������   (mihail.buryakov@gmail.com), 2012,           *
*    � �������� ������� (eyesguard@yandex.ru), 2018.                 *
*    ������ ��������� �������� ��������� ����������� ������������.   *
* �� ������ �������������� �� �/��� �������������� � ������������    *
* � ��������� ����������� ������������ �������� GNU � ��� ����,      *
* ��� ��� ���� ������������ ������ ���������� ��                     *
* (Free Software Foundation); ���� ������                            *
* 2 �������� ���� (�� ������ �������) ����� ����� ������� ������.    *
*                                                                    *
* ��������� ���������������� � �������, ��� ��� ����� ��������,      *
* �� ��� ����� �� �� �� ���� ����������� ������������; ���� ���      *
* ��������� ����������� ������������, ��������� � ����������������   *
* ���������� � ������������ ��� ������������ �����. ��� ���������    *
* ����� ��������� ���������� ������������ � �����������              *
* ������������ ��������� GNU (http://www.gnu.org/licenses/gpl.html). *
*                                                                    *
*********************************************************************/

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BreakWnd_Unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TBreakWnd *BreakWnd;

//---------------------------------------------------------------------------
//����������� �����
__fastcall TBreakWnd::TBreakWnd(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------
//�������� ��� �������� �����

void __fastcall TBreakWnd::FormClose(TObject *Sender, TCloseAction &Action)
{
 MainWnd->IsBreakNow = true;
 MainWnd->IsWarningNow = true;
 MainWnd->MainTimerTimer(this);
}
//---------------------------------------------------------------------------
//��������� �������� ��� �������� ����, ���� �� ��� ��������

void __fastcall TBreakWnd::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
 if ((MainWnd->EnMonOff) && (MainWnd->IsBreakNow))
        SendMessage(Handle,WM_SYSCOMMAND,SC_MONITORPOWER,-1);
}
//---------------------------------------------------------------------------
//������� ������ �� ����� ��������, �� �� ������� �� ���������� ����������

void __fastcall TBreakWnd::FormShow(TObject *Sender)
{
 SetFocus();        
}
//---------------------------------------------------------------------------


