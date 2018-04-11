VERSION 5.00
Begin VB.Form form0 
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
      TabIndex        =   8
      Top             =   3000
      Width           =   666
   End
   Begin VB.CommandButton Command4 
      Caption         =   "4"
      Height          =   666
      Left            =   4200
      TabIndex        =   7
      Top             =   3000
      Width           =   666
   End
   Begin VB.CommandButton Command3 
      Caption         =   "3"
      Height          =   666
      Left            =   3000
      TabIndex        =   6
      Top             =   3000
      Width           =   666
   End
   Begin VB.CommandButton Command2 
      Caption         =   "2"
      Height          =   666
      Left            =   1800
      TabIndex        =   5
      Top             =   3000
      Width           =   666
   End
   Begin VB.CommandButton Command_setting 
      Caption         =   "设置"
      Height          =   615
      Left            =   6480
      TabIndex        =   4
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
   Begin VB.Label Labelg 
      Caption         =   "A"
      Height          =   495
      Index           =   2
      Left            =   4920
      TabIndex        =   10
      Top             =   1680
      Width           =   1455
   End
   Begin VB.Label Labelg 
      Caption         =   "A"
      Height          =   495
      Index           =   1
      Left            =   3000
      TabIndex        =   9
      Top             =   1680
      Width           =   1455
   End
   Begin VB.Label Labelg 
      Caption         =   "A"
      Height          =   495
      Index           =   0
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
Attribute VB_Name = "form0"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public gnum As Integer
Private gname(3) As String
Private score(3) As Integer
Public rule0_win As Integer
Public rule1_right, rule1_wrong, rule1_pass As Integer
Public rule2_wrong As Integer
Public rule3_time, rule3_wrong, rule3_pass As Integer
Public rule4_v, rule4_wrong, rule4_right As Integer
Public rule5_time As Integer


Private Sub Form_Load()
    
    beautify
    
    For i = 0 To 2
        score(i) = 0
    Next i
    
    gnum = Val(InputBox("请输入组数:", "输入组数"))
    
    If gnum = 0 Then
        gnum = 2 '未输入，草泥马 默认2组
    ElseIf gnum > 3 Then
        gnum = 3 '又想搞什么
    End If
    
    If gnum < 3 Then ' 两组
        Labelg(2).Caption = "" '隐藏c组
        rule0_win = 2 '额这个规则吗
    Else
        rule0_win = 3
    End If
    
    gnum = gnum - 1 ' 方便后续操作 0 ~ gnum
    
    '输入组名
    For i = 0 To gnum
        gname(i) = InputBox("请输入第" + Str(i + 1) + "组的组名:", "输入组名")
    Next i
    
    '默认组名
    For i = 0 To gnum
        If gname(i) = "" Then gname(i) = Str(i)
    Next i
    
    score_show '显示比分
    
    '规则初始化
    rule1_right = 6
    rule1_wrong = 2
    rule1_pass = 2
    rule2_wrong = 2
    rule3_time = 60
    rule3_wrong = 2
    rule3_pass = 2
    rule4_v = 250
    rule4_wrong = 3
    rule4_right = 2
    rule5_time = 10
    
End Sub

Public Sub score_show()

    For i = 0 To gnum
        Labelg(i).Caption = gname(i) + "组" + Str(score(i))
    Next i
    
    judge
End Sub


Private Sub judge()

    For i = 0 To gnum
        If score(i) >= rule0_win Then
            tmp = MsgBox(gname(i) + "组赢了", 0, "结果")
            Exit For '应该不会出现平局吧，先这样
        End If
    Next i
    
End Sub

Public Function add_score(win As Integer)
    
    score(win) = score(win) + 1
    
    score_show
    
End Function

'从外部访问组名
Public Function qname(i As Integer) As String
    qname = gname(i)
End Function
'从外部访问分数
Public Function qscore(i As Integer) As Integer
    qscore = score(i)
End Function

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


Private Sub beautify()
'none
End Sub
