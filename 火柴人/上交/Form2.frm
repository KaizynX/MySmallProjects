VERSION 5.00
Begin VB.Form Form2 
   Caption         =   "游戏说明"
   ClientHeight    =   9435
   ClientLeft      =   2745
   ClientTop       =   1215
   ClientWidth     =   9765
   LinkTopic       =   "Form2"
   ScaleHeight     =   9435
   ScaleWidth      =   9765
   Begin VB.CommandButton Command1 
      BackColor       =   &H00FF0000&
      Caption         =   "开始游戏"
      BeginProperty Font 
         Name            =   "微软雅黑"
         Size            =   12
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   7920
      TabIndex        =   0
      Top             =   360
      Width           =   1575
   End
   Begin VB.Timer Timer1 
      Interval        =   1
      Left            =   360
      Top             =   360
   End
   Begin VB.Image Image1 
      Height          =   9500
      Left            =   0
      Picture         =   "Form2.frx":0000
      Stretch         =   -1  'True
      Top             =   0
      Width           =   10000
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
    Image1.Top = 10000
    Command1.Visible = False
End Sub

Private Sub Command1_Click()
    Unload Form2
End Sub

Private Sub Timer1_Timer()
    If Image1.Top > 0 Then
        Image1.Top = Image1.Top - 50
    Else
        Command1.Visible = True
    End If
End Sub
