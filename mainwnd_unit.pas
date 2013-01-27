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

    OptionsLabel: TLabel;

    TimeWorkLabel: TLabel;
    TimeWorkEdit: TEdit;
    TimeWorkSelect: TComboBox;

    TimeBreakLabel: TLabel;
    TimeBreakEdit: TEdit;
    TimeBreakSelect: TComboBox;

    TimeRemindLabel: TLabel;
    TimeRemindNoComboBox: TComboBox;
    TimeRemindLabel1: TLabel;
    TimeRemindEdit: TEdit;
    TimeRemindSelect: TComboBox;

    TimeStepLabel: TLabel;
    TimeStepEdit: TEdit;
    TimeStepSelect: TComboBox;

    CheckEnMonOff: TCheckBox;
    CheckSound: TCheckBox;
    CheckOff: TCheckBox;

    Image1: TImage;

    ButOK: TButton;
    ButApply: TButton;
    ButCancel: TButton;
    ButExit: TButton;

    InfoLabel: TLabel;

    TrayIcon: TTrayIcon;
    TrayImageList: TImageList;

    MainPopupMenu: TPopupMenu;
    PopupExit: TMenuItem;
    PopupOff: TMenuItem;
    PopupBreakLine: TMenuItem;
    PopupSet: TMenuItem;
    PopupMakeBr: TMenuItem;
    PopupTimerReset: TMenuItem;

    PopupImageList: TImageList;
    Timer: TTimer;
    HintTimer: TTimer;

    procedure FormClose(Sender: TObject; var CloseAction: TCloseAction);
    procedure FormCreate(Sender: TObject);

    procedure ButOKClick(Sender: TObject);
    procedure ButApplyClick(Sender: TObject);
    procedure ButCancelClick(Sender: TObject);
    procedure ButExitClick(Sender: TObject);

    procedure TimeWorkEditChange(Sender: TObject);
    procedure TimeBreakEditChange(Sender: TObject);
    procedure TimeRemindNoComboBoxChange(Sender: TObject);
    procedure TimeRemindEditChange(Sender: TObject);
    procedure TimeRemindSelectChange(Sender: TObject);
    procedure TimeStepEditChange(Sender: TObject);

    procedure TrayIconClick(Sender: TObject);

    procedure CheckEnMonOffChange(Sender: TObject);
    procedure CheckSoundChange(Sender: TObject);
    procedure CheckOffChange(Sender: TObject);

    procedure selectIcon(num: integer);

    procedure setSettings(s: TBreakSettings);
    function getSettings(): TBreakSettings;

    procedure setChanged(isChanged: boolean);

  private
    settings: TBreakSettings;
    settingsChanged: boolean;
    changing: boolean;
  public
    actionsOnSave: TSimpleEventList;
    actionsOnShow: TSimpleEventList;
  end;

type
  TimeSetting = record
    Value: string;
    unitNum: 1..MAX_MEASUREMENT;
  end;

function loadSetting(Text: TimeSetting; default: cardinal): cardinal;
function showSetting(time: cardinal): TimeSetting;

implementation

{$R *.lfm}

function loadSetting(Text: TimeSetting; default: cardinal): cardinal;
begin
  Result := StrToIntDef(Text.Value, default div measurementCoeff(Text.unitNum)) * measurementCoeff(Text.unitNum);
end;

function showSetting(time: cardinal): TimeSetting;
begin
  Result.unitNum := calcMeasurement(time);
  Result.Value := IntToStr(time div measurementCoeff(Result.unitNum));
end;

{ TMainWnd }

procedure TMainWnd.selectIcon(num: integer);
begin
  TrayImageList.GetIcon(num, TrayIcon.Icon);
end;

procedure TMainWnd.FormClose(Sender: TObject; var CloseAction: TCloseAction);
begin
  CloseAction := caNone;
  Hide;
end;

procedure TMainWnd.ButOKClick(Sender: TObject);
begin
  actionsOnSave.executeAll();
  Self.Close;
end;

procedure TMainWnd.ButApplyClick(Sender: TObject);
begin
  actionsOnSave.executeAll();
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
  settings.EnMonOff := CheckEnMonOff.Checked;
  setChanged(True);
end;

procedure TMainWnd.CheckOffChange(Sender: TObject);
begin
  settings.Off := CheckOff.Checked;
  setChanged(True);
end;

procedure TMainWnd.CheckSoundChange(Sender: TObject);
begin
  settings.Sound := CheckSound.Checked;
  setChanged(True);
end;

procedure TMainWnd.FormCreate(Sender: TObject);
var
  i: integer;
begin
  changing := True;
  TimeRemindNoComboBox.Clear;
  for i := 1 to MAX_REMIND do begin
    TimeRemindNoComboBox.AddItem(IntToStr(i), nil);
  end;
  TimeWorkSelect.Clear;
  TimeBreakSelect.Clear;
  TimeRemindSelect.Clear;
  TimeStepSelect.Clear;
  for i := 1 to Length(TimeCoeffs) do begin
    TimeWorkSelect.AddItem(TimeNames[i], nil);
    TimeBreakSelect.AddItem(TimeNames[i], nil);
    TimeRemindSelect.AddItem(TimeNames[i], nil);
    TimeStepSelect.AddItem(TimeNames[i], nil);
  end;
  changing := False;
end;

procedure TMainWnd.setSettings(s: TBreakSettings);
var
  setRec: TimeSetting;
begin
  settings := s;
  Assert(changing = False, 'Changing is true when called setSettings');
  changing := True;

  TimeRemindNoComboBox.ItemIndex := 0;

  setRec := showSetting(settings.TimeStep);
  TimeStepEdit.Text := setRec.Value;
  TimeStepSelect.ItemIndex := setRec.unitNum - 1;

  setRec := showSetting(settings.TimeBreak);
  TimeBreakEdit.Text := setRec.Value;
  TimeBreakSelect.ItemIndex := setRec.unitNum - 1;

  setRec := showSetting(settings.TimeWork);
  TimeWorkEdit.Text := setRec.Value;
  TimeWorkSelect.ItemIndex := setRec.unitNum - 1;

  TimeRemindNoComboBox.OnChange(nil);

  CheckEnMonOff.Checked := settings.EnMonOff;
  CheckOff.Checked := settings.Off;
  CheckSound.Checked := settings.Sound;

  changing := False;
  setChanged(False);
end;

function TMainWnd.getSettings(): TBreakSettings;
begin
  Result := settings;
end;

procedure TMainWnd.TimeRemindNoComboBoxChange(Sender: TObject);
var
  setRec: TimeSetting;
  i: integer;
  changingBuf: boolean;
begin
  changingBuf := changing;
  changing := True;
  i := TimeRemindNoComboBox.ItemIndex + 1;
  setRec:=showSetting(settings.TimeRemind[i]);
  TimeRemindSelect.ItemIndex:=setRec.unitNum-1;
  TimeRemindEdit.Text:=setRec.Value;
  changing := changingBuf;
end;

procedure TMainWnd.TimeRemindSelectChange(Sender: TObject);
begin

end;

procedure TMainWnd.TimeStepEditChange(Sender: TObject);
var
  setRec: TimeSetting;
begin
  if changing then Exit;
  setRec.Value:=TimeStepEdit.Text;
  setRec.unitNum:=TimeStepSelect.ItemIndex+1;
  settings.TimeStep:=loadSetting(setRec, settings.TimeStep);
  setChanged(True);
end;

procedure TMainWnd.TimeWorkEditChange(Sender: TObject);
var
  setRec: TimeSetting;
begin
  if changing then Exit;
  setRec.Value:=TimeWorkEdit.Text;
  setRec.unitNum:=TimeWorkSelect.ItemIndex+1;
  settings.TimeWork:=loadSetting(setRec, settings.TimeWork);
  setChanged(True);
end;

procedure TMainWnd.TrayIconClick(Sender: TObject);
begin
  actionsOnShow.executeAll();
end;

procedure TMainWnd.setChanged(isChanged: boolean);
begin
  settingsChanged := isChanged;
  ButApply.Enabled := isChanged;
end;

procedure TMainWnd.TimeBreakEditChange(Sender: TObject);
var
  setRec: TimeSetting;
begin
  if changing then Exit;
  setRec.Value:=TimeBreakEdit.Text;
  setRec.unitNum:=TimeBreakSelect.ItemIndex+1;
  settings.TimeBreak:=loadSetting(setRec, settings.TimeBreak);
  setChanged(True);
end;

procedure TMainWnd.TimeRemindEditChange(Sender: TObject);
var
  setRec: TimeSetting;
  i: Integer;
begin
  if changing then Exit;
  i :=TimeRemindNoComboBox.ItemIndex + 1;
  setRec.Value:=TimeRemindEdit.Text;
  setRec.unitNum:=TimeRemindSelect.ItemIndex+1;
  settings.TimeRemind[i]:=loadSetting(setRec, settings.TimeRemind[i]);
  setChanged(True);
end;

end.
