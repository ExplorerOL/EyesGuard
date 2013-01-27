unit Settings;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils;

const
  MAX_REMIND = 3;
  MAX_MEASUREMENT = 3;
  DEFAULT_SETTINGS_FILENAME = 'set.dat';

type
  TBreakSettings = record
    TimeStep: cardinal;
    TimeWork: cardinal;
    TimeBreak: cardinal;
    TimeRemind: array [1..MAX_REMIND] of cardinal;
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
  IOPolicyConservative: TIOPolicy = (
    createNonExistingFile: False;
    rewriteCorruptedFile: False;
    rewriteGoodFile: False;
    );
  IOPolicyStandard: TIOPolicy = (
    createNonExistingFile: True;
    rewriteCorruptedFile: False;
    rewriteGoodFile: True;
    );

function checkSettings(s: TBreakSettings): boolean;
function calcMeasurement(time: cardinal): integer;
function measurementCoeff(unitNum: integer): integer;

implementation

function calcMeasurement(time: cardinal): integer;
var
  i: integer;
begin
  if time < 1000 then begin
    Result := 1;
  end
  else if time < 60000 then begin
    Result := 2;
  end
  else begin
    Result := 3;
  end;
end;

function measurementCoeff(unitNum: integer): integer;
begin
  case unitNum of
    1: Result := 1;
    2: Result := MSecsPerSec;
    3: Result := SecsPerMin * MSecsPerSec;
    else
      halt;
  end;
end;

function checkSettings(s: TBreakSettings): boolean;
var
  i: integer;
begin
  Result := s.TimeRemind[1] < s.TimeWork;
  for i := 2 to MAX_REMIND do begin
    if s.TimeRemind[i] >= s.TimeRemind[i - 1] then Result := False;
  end;
  if s.TimeRemind[MAX_REMIND] < 0 then Result := False;
end;

end.
