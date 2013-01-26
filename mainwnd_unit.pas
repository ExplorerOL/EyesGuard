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

    procedure ButOKClick(Sender: TObject);
    procedure ButApplyClick(Sender: TObject);
    procedure ButCancelClick(Sender: TObject);
    procedure ButExitClick(Sender: TObject);
    procedure CheckEnMonOffChange(Sender: TObject);
    procedure CheckOffChange(Sender: TObject);
    procedure CheckSoundChange(Sender: TObject);

    procedure FormClose(Sender: TObject; var CloseAction: TCloseAction);
    procedure FormCreate(Sender: TObject);

    procedure setIcon(num: Integer);

    procedure setSettings(s: TBreakSettings);
    function getSettings(): TBreakSettings;

    procedure setChanged(isChanged: Boolean);
    procedure TimeBreakEditChange(Sender: TObject);
    procedure TimeRemindEditChange(Sender: TObject);
    procedure TimeRemindNoComboBoxChange(Sender: TObject);
    procedure TimeRemindSelectChange(Sender: TObject);
    procedure TimeUpdateEditChange(Sender: TObject);
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

procedure TMainWnd.ButOKClick(Sender: TObject);
begin
  ActionsOnSave.executeAll();
  Self.Close;
end;

procedure TMainWnd.ButApplyClick(Sender: TObject);
begin
  ActionsOnSave.executeAll();
end;

procedure TMainWnd.ButCancelClick(Sender: TObject);
begin
  Self.Close;
end;

procedure TMainWnd.ButExitClick(Sender: TObject);
begin
  Application.Terminate();
end;

procedure TMainWnd.CheckEnMonOffChange(Sender: TObject);
begin
  Settings.EnMonOff:=CheckEnMonOff.Checked;
  setChanged(true);
end;

procedure TMainWnd.CheckOffChange(Sender: TObject);
begin
  Settings.Off:=CheckOff.Checked;
  setChanged(true);
end;

procedure TMainWnd.CheckSoundChange(Sender: TObject);
begin
  Settings.Sound:=CheckSound.Checked;
  setChanged(true);
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

procedure TMainWnd.setSettings(s: TBreakSettings);
var
  unitNum:integer;
begin
  Settings:=s;

  TimeRemindNoComboBox.ItemIndex:=0;

  unitNum:=calcMeasurement(Settings.TimeStep);
  TimeUpdateSelect.ItemIndex:=unitNum-1;
  TimeUpdateEdit.Text:=IntToStr(settings.TimeStep div measurementCoeff(unitNum));

  unitNum:=calcMeasurement(Settings.TimeBreak);
  writeln(unitNum);
  TimeBreakSelect.ItemIndex:=unitNum-1;
  TimeBreakEdit.Text:=IntToStr(settings.TimeBreak div measurementCoeff(unitNum));

  unitNum:=calcMeasurement(Settings.TimeWork);
  TimeWorkSelect.ItemIndex:=unitNum-1;
  TimeWorkEdit.Text:=IntToStr(settings.TimeWork div measurementCoeff(unitNum));

  TimeRemindNoComboBox.OnChange(nil);

  CheckEnMonOff.Checked:=Settings.EnMonOff;
  CheckOff.Checked:=Settings.Off;
  CheckSound.Checked:=Settings.Sound;

  setChanged(false);
end;

function TMainWnd.getSettings(): TBreakSettings;
begin
  Result:=Settings;
end;

procedure TMainWnd.TimeRemindNoComboBoxChange(Sender: TObject);
var
  unitNum: integer;
  i: integer;
begin
  i:=TimeRemindNoComboBox.ItemIndex+1;
  unitNum:=calcMeasurement(Settings.TimeRemind[i]);
  TimeRemindSelect.ItemIndex:=unitNum-1;
  TimeRemindEdit.Text:=IntToStr(Settings.TimeRemind[TimeRemindNoComboBox.ItemIndex+1] div measurementCoeff(unitNum));
end;

procedure TMainWnd.TimeRemindSelectChange(Sender: TObject);
begin

end;

procedure TMainWnd.TimeUpdateEditChange(Sender: TObject);
begin
  Settings.TimeStep:=StrToInt(TimeUpdateEdit.Text)*measurementCoeff(TimeUpdateSelect.ItemIndex+1);
  setChanged(true);
end;

procedure TMainWnd.TimeWorkEditChange(Sender: TObject);
begin
  Settings.TimeWork:=StrToInt(TimeWorkEdit.Text)*measurementCoeff(TimeWorkSelect.ItemIndex+1);
  setChanged(true);
end;

procedure TMainWnd.TrayIconClick(Sender: TObject);
begin
  ActionsOnShow.executeAll();
end;

procedure TMainWnd.setChanged(isChanged: Boolean);
begin
  SettingsChanged:=isChanged;
  ButApply.Enabled:=isChanged;
end;

procedure TMainWnd.TimeBreakEditChange(Sender: TObject);
begin
  Settings.TimeBreak:=StrToInt(TimeBreakEdit.Text)*measurementCoeff(TimeBreakSelect.ItemIndex+1);
  setChanged(true);
end;

procedure TMainWnd.TimeRemindEditChange(Sender: TObject);
begin
  Settings.TimeRemind[TimeRemindNoComboBox.ItemIndex+1]:=StrToInt(TimeRemindEdit.Text)*measurementCoeff(TimeRemindSelect.ItemIndex+1);
  setChanged(true);
end;

end.
