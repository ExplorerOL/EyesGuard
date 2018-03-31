object BreakWnd: TBreakWnd
  Left = 412
  Top = 0
  AlphaBlend = True
  AlphaBlendValue = 215
  BorderStyle = bsNone
  Caption = 'BreakWnd'
  ClientHeight = 838
  ClientWidth = 1436
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Visible = True
  WindowState = wsMaximized
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object BreakLabel1: TLabel
    Left = 0
    Top = 0
    Width = 1436
    Height = 136
    Align = alTop
    Alignment = taCenter
    AutoSize = False
    Caption = 'BREAK IN PROGRESS!!!'
    Color = clBlack
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clLime
    Font.Height = -25
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    Layout = tlBottom
  end
  object BreakLabel2: TLabel
    Left = 0
    Top = 136
    Width = 1436
    Height = 145
    Align = alTop
    Alignment = taCenter
    AutoSize = False
    Caption = 'Let your eyes to relax!'
    Color = clBtnFace
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clYellow
    Font.Height = -20
    Font.Name = 'Arial'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Transparent = True
    Layout = tlCenter
  end
  object LabelTimeBreakLeft: TLabel
    Left = 0
    Top = 798
    Width = 1436
    Height = 40
    Align = alBottom
    Alignment = taCenter
    AutoSize = False
    Caption = 'XX:XX:XX'
    Color = clBtnFace
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clYellow
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Transparent = True
    Layout = tlCenter
  end
  object GaugeBreakProgress: TCGauge
    Left = 0
    Top = 773
    Width = 1436
    Height = 25
    Align = alBottom
    Anchors = [akRight, akBottom]
    Color = clGreen
    ShowText = False
    ForeColor = clGreen
    BackColor = clSilver
    ParentColor = False
  end
end
