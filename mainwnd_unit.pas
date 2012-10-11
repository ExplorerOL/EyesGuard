unit MainWnd_Unit;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, StdCtrls,
  ExtCtrls, Menus,
  EventHandler,
  Settings;

const
  NumCoeff = 3;
  TimeCoeffs: array[1..NumCoeff] of integer = (1, 1000, 60000);
  TimeNames: array[1..NumCoeff] of string = ('мс', 'сек', 'мин');
  TimeMaxLength = 3;

type

  { TMainWnd }

  TMainWnd = class(TForm)
    TimeRemindSelect: TComboBox;
    TimeRemindLabel1: TLabel;
    TimeRemindNoComboBox: TComboBox;
    OptionsLabel: TLabel;
    TimeRemindLabel: TLabel;
    TimeBreakEdit: TEdit;
    TimeRemindEdit: TEdit;
    TimeUpdateSelect: TComboBox;
    TimeWorkSelect: TComboBox;
    TimeUpdateEdit: TEdit;
    TimeBreakLabel: TLabel;
    TimeUpdateLabel: TLabel;
    TimeWorkEdit: TEdit;
    TimeWorkLabel: TLabel;
    ButCancel: TButton;
    ButApply: TButton;
    ButExit: TButton;
    TimeBreakSelect: TComboBox;
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

    procedure FormClose(Sender: TObject; var CloseAction: TCloseAction);
    procedure FormCreate(Sender: TObject);
    procedure setIcon(num: Integer);
    procedure setSettings(s: TBreakSettings);
    function getSettings(): TBreakSettings;
    procedure setChanged();
    function calcMeasurement(time: Cardinal): Integer;
    procedure TimeRemindNoComboBoxChange(Sender: TObject);
    procedure TimeWorkEditChange(Sender: TObject);
    procedure TrayIconClick(Sender: TObject);
  private
    Settings: TBreakSettings;
    SettingsChanged: Boolean;
  public
    ActionsOnSave: TSimpleEventList;
    ActionsOnShow: TSimpleEventList;
  end;

implementation

{$R *.lfm}

{ TMainWnd }

procedure TMainWnd.setIcon(num: Integer);
begin
  TrayImageList.GetIcon(num, TrayIcon.Icon);
end;

procedure TMainWnd.FormClose(Sender: TObject; var CloseAction: TCloseAction);
begin
  CloseAction:=caNone;
  Hide;
end;

procedure TMainWnd.FormCreate(Sender: TObject);
var
  i: integer;
begin
  TimeRemindNoComboBox.Clear;
  for i:=1 to MaxRemind do begin
    TimeRemindNoComboBox.AddItem(IntToStr(i),nil);
  end;
  TimeWorkSelect.Clear;
  TimeBreakSelect.Clear;
  TimeRemindSelect.Clear;
  TimeUpdateSelect.Clear;
  for i:=1 to Length(TimeCoeffs) do begin
    TimeWorkSelect.AddItem(TimeNames[i], nil);
    TimeBreakSelect.AddItem(TimeNames[i], nil);
    TimeRemindSelect.AddItem(TimeNames[i], nil);
    TimeUpdateSelect.AddItem(TimeNames[i], nil);
  end;
end;

function TMainWnd.calcMeasurement(time: Cardinal): Integer;
var
  i:integer;
begin
  tram
end;

procedure TMainWnd.setSettings(s: TBreakSettings);
var
  i:integer;
begin
  Settings:=s;
  TimeUpdateEdit.Text:=IntToStr(settings.TimeStep);
  TimeBreakEdit.Text:=IntToStr(settings.TimeBreak);
  TimeWorkEdit.Text:=IntToStr(settings.TimeWork);
  TimeRemindNoComboBox.ItemIndex:=0;
  TimeRemindNoComboBox.OnChange(nil);
  CheckEnMonOff.Checked:=Settings.EnMonOff;
  CheckOff.Checked:=Settings.Off;
  CheckSound.Checked:=Settings.Sound;
end;

function TMainWnd.getSettings(): TBreakSettings;
begin
  Result:=Settings;
end;

procedure TMainWnd.TimeRemindNoComboBoxChange(Sender: TObject);
begin
  TimeRemindEdit.Text:=IntToStr(Settings.TimeRemind[TimeRemindNoComboBox.ItemIndex+1]);
end;

procedure TMainWnd.TimeWorkEditChange(Sender: TObject);
begin
  Settings.TimeWork:=StrToInt(TimeWorkEdit.Text);
  setChanged();
end;

procedure TMainWnd.TrayIconClick(Sender: TObject);
begin
  ActionsOnShow.executeAll();
end;

procedure TMainWnd.setChanged();
begin
  SettingsChanged:=True;
  ButApply.Enabled:=True;
end;

end.
