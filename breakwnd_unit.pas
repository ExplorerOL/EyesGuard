unit BreakWnd_Unit;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, StdCtrls,
  ExtCtrls, Menus;

type

  { TBreakWnd }

  TBreakWnd = class(TForm)
    BreakLabel1: TLabel;
    BreakLabel2: TLabel;
    procedure FormShow(Sender: TObject);
  private
    { private declarations }
  public
    { public declarations }
  end;

implementation

{$R *.lfm}

{ TBreakWnd }

procedure TBreakWnd.FormShow(Sender: TObject);
begin
  SetFocus;
end;

end.
