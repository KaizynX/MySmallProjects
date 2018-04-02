VERSION 5.00
Begin VB.Form Form0 
   Caption         =   "北师大台州附中第一届中国成语大会"
   ClientHeight    =   4620
   ClientLeft      =   6285
   ClientTop       =   4320
   ClientWidth     =   9615
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   4620
   ScaleWidth      =   9615
   Begin VB.CommandButton Command5 
      Caption         =   "5"
      Height          =   666
      Left            =   5400
      TabIndex        =   9
      Top             =   3000
      Width           =   666
   End
   Begin VB.CommandButton Command4 
      Caption         =   "4"
      Height          =   666
      Left            =   4200
      TabIndex        =   8
      Top             =   3000
      Width           =   666
   End
   Begin VB.CommandButton Command3 
      Caption         =   "3"
      Height          =   666
      Left            =   3000
      TabIndex        =   7
      Top             =   3000
      Width           =   666
   End
   Begin VB.CommandButton Command2 
      Caption         =   "2"
      Height          =   666
      Left            =   1800
      TabIndex        =   6
      Top             =   3000
      Width           =   666
   End
   Begin VB.CommandButton Command_setting 
      Caption         =   "设置"
      Height          =   615
      Left            =   6480
      TabIndex        =   5
      Top             =   3720
      Width           =   1455
   End
   Begin VB.CommandButton Command_exit 
      Caption         =   "退出"
      Height          =   495
      Left            =   8520
      TabIndex        =   1
      Top             =   3840
      Width           =   735
   End
   Begin VB.CommandButton Command1 
      Caption         =   "1"
      Height          =   666
      Left            =   600
      TabIndex        =   0
      Top             =   3000
      Width           =   666
   End
   Begin VB.Label Label_b 
      Caption         =   "B"
      Height          =   495
      Left            =   4320
      TabIndex        =   4
      Top             =   1680
      Width           =   1455
   End
   Begin VB.Label Label_a 
      Caption         =   "A"
      Height          =   495
      Left            =   960
      TabIndex        =   3
      Top             =   1680
      Width           =   1455
   End
   Begin VB.Label Label_title 
      Caption         =   "北师大台州附中第一届中国成语大会"
      BeginProperty Font 
         Name            =   "隶书"
         Size            =   27.75
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   0
      TabIndex        =   2
      Top             =   360
      Width           =   9375
   End
End
Attribute VB_Name = "Form0"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public name_a, name_b As String
Public score_a, score_b As Integer
Public rule1_right, rule1_wrong, rule1_pass As Integer
Public rule2_wrong As Integer
Public rule3_time, rule3_wrong, rule3_pass As Integer
Public rule4_v, rule4_wrong, rule4_right As Integer
Public rule5_time As Integer
Public group_num As Integer


Private Sub Form_Load()
    
    beautify
    
    score_a = 0
    score_b = 0
    name_a = "A"
    name_b = "B"
    name_a = InputBox("请输入A组组名:", "输入组名")
    name_b = InputBox("请输入B组组名:", "输入组名")
    score_show '显示比分
    
    rule1_right = 6
    rule1_wrong = 2
    rule1_pass = 2
    rule2_wrong = 2
    rule3_time = 60
    rule3_wrong = 2
    rule3_pass = 2
    rule4_v = 100
    rule4_wrong = 3
    rule4_right = 2
    rule5_time = 10
    group_num = 2
    
End Sub

Public Sub score_show()
    Label_a.Caption = name_a + "组" + Str(score_a)
    Label_b.Caption = name_b + "组" + Str(score_b)
    judge
End Sub


Private Sub Command_exit_Click()
    judge
    End
End Sub

Private Sub Command_setting_Click()
    Form_setting.Show
End Sub

Private Sub Command1_Click()
    Form1.Show
End Sub

Private Sub Command2_Click()
    Form2.Show
End Sub

Private Sub Command3_Click()
    Form3.Show
End Sub

Private Sub Command4_Click()
    Form4.Show
End Sub

Private Sub Command5_Click()
    Form5.Show
End Sub

Private Sub judge()
    If score_a >= 3 Then
        tmp = MsgBox(name_a + "组赢了", 0, "结果")
    ElseIf score_b >= 3 Then
        tmp = MsgBox(name_b + "组赢了", 0, "结果")
    End If
End Sub

Private Sub beautify()
'none
End Sub
