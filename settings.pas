unit Settings;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils;

const
  MaxRemind = 3;
  DefaultSettingsFileName = 'set.dat';

type
  TBreakSettings = record
    TimeStep: cardinal;
    TimeWork: cardinal;
    TimeBreak: cardinal;
    TimeRemind: array [1..MaxRemind] of cardinal;
    EnMonOff: boolean;
    Sound: boolean;
    Off: boolean;
  end;

const
  DefaultSettings: TBreakSettings = (
    TimeStep: MSecsPerSec * 1;
    TimeWork: MSecsPerSec * SecsPerMin * 30;
    TimeBreak: MSecsPerSec * SecsPerMin * 10;
    TimeRemind: (MSecsPerSec * SecsPerMin * 10, MSecsPerSec * 5, 0);
    EnMonOff: False;
    Sound: True;
    Off: False;
    );

type
  TIOPolicy = record
    createNonExistingFile: boolean;
    rewriteCorruptedFile: boolean;
    rewriteGoodFile: boolean;
  end;

const
  DefaultIOPolicy: TIOPolicy = (
    createNonExistingFile: False;
    rewriteCorruptedFile: False;
    rewriteGoodFile: False;
    );

function CheckSettings(s: TBreakSettings): boolean;

implementation

function CheckSettings(s: TBreakSettings): boolean;
var
  i:integer;
begin
  Result:=s.TimeRemind[1]<s.TimeWork;
  for i:=2 to MaxRemind do begin
    if s.TimeRemind[i]>=s.TimeRemind[i-1] then Result:=False;
  end;
  if s.TimeRemind[MaxRemind]<0 then Result:=False;
end;

end.
