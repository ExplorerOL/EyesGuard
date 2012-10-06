unit MainWnd_Unit;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, StdCtrls,
  ExtCtrls, Menus,
  BreakWnd_Unit;

type

  { TMainWnd }

  TMainWnd = class(TForm)
    OptionsLabel: TLabel;
    TimeWorkEdit: TEdit;
    TimeBreakEdit: TEdit;
    TimeWorkLabel: TLabel;
    TimeBreakLabel: TLabel;
    ButCancel: TButton;
    ButApply: TButton;
    ButExit: TButton;
    TrayIcon: TTrayIcon;
    TrayImageList: TImageList;
    MainPopupMenu: TPopupMenu;
    PopupExit: TMenuItem;
    Timer: TTimer;
    CheckSound: TCheckBox;
    CheckOff: TCheckBox;
    PopupSet: TMenuItem;
    PopupOff: TMenuItem;
    PopupMakeBr: TMenuItem;
    CheckEnMonOff: TCheckBox;
    InfoLabel: TLabel;
    PopupBreakLine: TMenuItem;
    PopupTimerReset: TMenuItem;
    PopupImageList: TImageList;
    Image1: TImage;
    ButOK: TButton;
    HintTimer: TTimer;
    procedure FormShow(Sender: TObject);
  private
    { private declarations }
  public
    { public declarations }
  end;

implementation

{$R *.lfm}

{ TMainWnd }

procedure TMainWnd.FormShow(Sender: TObject);
begin
  Left := Screen.Width - Width - 100;
  Top := Screen.Height - Height - 100;
end;

end.
