VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "目标计时"
   ClientHeight    =   5040
   ClientLeft      =   6675
   ClientTop       =   4320
   ClientWidth     =   7725
   LinkTopic       =   "Form2"
   ScaleHeight     =   5040
   ScaleWidth      =   7725
   Begin VB.OptionButton Option_b 
      Caption         =   "B组"
      Height          =   255
      Left            =   1680
      TabIndex        =   8
      Top             =   1320
      Width           =   855
   End
   Begin VB.OptionButton Option_a 
      Caption         =   "A组"
      Height          =   255
      Left            =   360
      TabIndex        =   7
      Top             =   1320
      Width           =   975
   End
   Begin VB.CommandButton Command_start 
      Caption         =   "开始"
      Height          =   615
      Left            =   4200
      TabIndex        =   4
      Top             =   3840
      Width           =   975
   End
   Begin VB.Timer Timer 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   1920
      Top             =   2160
   End
   Begin VB.CommandButton Command_exit 
      Caption         =   "退出"
      Height          =   615
      Left            =   5880
      TabIndex        =   0
      Top             =   3840
      Width           =   1095
   End
   Begin VB.Label Label_pass 
      Caption         =   "跳过"
      Height          =   495
      Left            =   6360
      TabIndex        =   9
      Top             =   1920
      Width           =   855
   End
   Begin VB.Label Label_wrong 
      Caption         =   "犯规"
      Height          =   375
      Left            =   4800
      TabIndex        =   6
      Top             =   1920
      Width           =   1215
   End
   Begin VB.Label Label_right 
      Caption         =   "答对"
      Height          =   615
      Left            =   2760
      TabIndex        =   5
      Top             =   1920
      Width           =   1695
   End
   Begin VB.Label Label_time 
      Caption         =   "计时"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   18
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   840
      TabIndex        =   3
      Top             =   1800
      Width           =   1695
   End
   Begin VB.Label Label_theme 
      Caption         =   "主题"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   26.25
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Left            =   720
      TabIndex        =   2
      Top             =   120
      Width           =   1575
   End
   Begin VB.Label Label_cy 
      Caption         =   "先选主题"
      BeginProperty Font 
         Name            =   "隶书"
         Size            =   42
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1095
      Left            =   2880
      TabIndex        =   1
      Top             =   360
      Width           =   3855
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim time, time_a, time_b As Integer '计时
Dim right_a, wrong_a, right_b, wrong_b, pass_a, pass_b As Integer '记录答对和犯规
Dim sum_theme, num_theme As Integer ' 记录主题
Dim str_theme(1000) As String ' 主题
Dim sum_cy, num_cy As Integer '成语
Dim str_cy(1000) As String
Dim use_cy, use_theme As Integer
Dim vis_cy(1000), vis_theme(1000) As Boolean  '判断重复
Dim is_ok As Boolean '防止用完


Private Sub Form_Load()
    beautify

    is_ok = True
    
    time = 0
    time_a = 0
    time_b = 0
    right_a = 0
    right_b = 0
    wrong_a = 0
    wrong_b = 0
    pass_a = 0
    pass_b = 0
    use_cy = 0
    use_theme = 0
    Option_a.Caption = Form0.name_a + "组"
    Option_b.Caption = Form0.name_b + "组"
    ' 默认为A组
    Option_a.Value = True
    Option_b.Value = False
    
    Label_time.Caption = "用时:" + Str(time)
    
    '主题init
    Open "resources\part1\theme.txt" For Input As #1
        Dim i As Integer
        i = 0
        Do Until EOF(1)
            Line Input #1, str_theme(i)
            i = i + 1
        Loop
    Close #1
    sum_theme = i - 1
    
End Sub

Private Sub judge() ' 判断胜负
    If time_a < time_b Then ' A win
        Form0.score_a = Form0.score_a + 1
    ElseIf time_a > time_b Then ' B win
        Form0.score_b = Form0.score_b + 1
    Else 'use the same time
        Form0.score_a = Form0.score_a + 1
        Form0.score_b = Form0.score_b + 1
    End If
End Sub


Private Sub Label_right_Click() ' 正确

    If Option_a.Value = True Then
        If is_ok Then right_a = right_a + 1
        Label_right.Caption = "答对:" + Str(right_a)
        
        If right_a >= Form0.rule1_right Then
            Timer.Enabled = False ' stop
            tmp = MsgBox("Finish", 0, "可恶")
        End If
    Else
        If is_ok Then right_b = right_b + 1
        Label_right.Caption = "答对:" + Str(right_b)
        
        If right_b >= Form0.rule1_right Then
            Timer.Enabled = False ' stop
            tmp = MsgBox("Finish", 0, "可恶")
        End If
    End If
    change_cy
    
    
    
End Sub

Private Sub Label_pass_Click() '跳过

    If Option_a.Value = True Then
        If is_ok Then pass_a = pass_a + 1
        Label_pass.Caption = "跳过:" + Str(pass_a)
        
        If pass_a > Form0.rule1_pass Then
            tmp = MsgBox("没机会了", 0, "FBIWarning") ' stop
        Else: change_cy
        End If
    Else
        If is_ok Then pass_b = pass_b + 1
        Label_pass.Caption = "跳过:" + Str(pass_b)
        
        If pass_b > Form0.rule1_pass Then
            tmp = MsgBox("没机会了", 0, "FBIWarning") ' stop
        Else: change_cy
        End If
    End If
    
End Sub

Private Sub Label_wrong_Click() '错误
    If Option_a.Value = True Then
        If is_ok Then wrong_a = wrong_a + 1
        Label_wrong.Caption = "犯规:" + Str(wrong_a)
        
        If wrong_a > Form0.rule1_wrong Then
            is_ok = False
            Timer.Enabled = False ' stop
            tmp = MsgBox("犯规", 0, "FBIWarning")
        End If
    Else
        If is_ok Then wrong_b = wrong_b + 1
        Label_wrong.Caption = "犯规:" + Str(wrong_b)
        
        If wrong_b > Form0.rule1_wrong Then
            is_ok = False
            Timer.Enabled = False ' stop
            tmp = MsgBox("犯规", 0, "FBIWarning")
        End If
    End If
    
    change_cy
    
End Sub

Private Sub Label_theme_Click() '切换主题

    If use_theme > sum_theme Then
        is_ok = False
        tmp = MsgBox("主题用完了", 0, "FBIWarning")
        Exit Sub
    End If
    
    num_theme = Rnd() * sum_theme '第一次的随机
    Do While vis_theme(num_theme) = True
        num_theme = Rnd() * sum_theme
    Loop
    vis_theme(num_theme) = True
    use_theme = use_theme + 1
    Label_theme.Caption = str_theme(num_theme)
    
    reset_cy '重置vis
    
    '打开对应主题的成语库
    Open "resources\part1\theme" + Replace(Str(num_theme), " ", "") + ".txt" For Input As #2
        Dim i As Integer
        i = 0
        Do Until EOF(2)
            Line Input #2, str_cy(i)
            i = i + 1
        Loop
    Close #2
    sum_cy = i - 1
    
    
End Sub

Private Sub change_cy() ' 换成语
    If is_ok = False Then Exit Sub

    If use_cy > sum_cy Then
        is_ok = False
        tmp = MsgBox("成语用完了", 0, "FBIWarning")
        Exit Sub
    End If
    
    num_cy = Rnd() * sum_cy '第一次的随机
    Do While vis_cy(num_cy) = True
        num_cy = Rnd() * sum_cy
    Loop
    
    vis_cy(num_cy) = True
    use_cy = use_cy + 1
    Label_cy.Caption = str_cy(num_cy)
    
End Sub


Private Sub reset_cy() '重置成语vis
    Dim i As Integer
    For i = 0 To 999
        vis_cy(i) = False
    Next i
    use_cy = 0
    is_ok = True
End Sub

Private Sub Option_a_Click() '更改小组
    state_show
End Sub

Private Sub Option_b_Click()
    state_show
End Sub

Private Sub Timer_Timer() '计时
    time = time + 1
     If Option_a.Value = True Then
        time_a = time
    Else
        time_b = time
    End If
    Label_time.Caption = "用时:" + Str(time)
End Sub

Private Sub Command_exit_Click()
    judge '判断胜负
    Form0.score_show
    Unload Me '关闭
End Sub

Private Sub Command_start_Click() ' 开始计时，出现成语
    time = 0
    Timer.Enabled = True
    change_cy
End Sub

Private Sub state_show()
    If Option_b.Value = True Then
        Label_right.Caption = "答对:" + Str(right_b)
        Label_wrong.Caption = "犯规:" + Str(wrong_b)
        Label_time.Caption = "用时:" + Str(time_b)
        Label_pass.Caption = "跳过:" + Str(pass_b)
    Else
        Label_right.Caption = "答对:" + Str(right_a)
        Label_wrong.Caption = "犯规:" + Str(wrong_a)
        Label_time.Caption = "用时:" + Str(time_a)
        Label_pass.Caption = "跳过:" + Str(pass_a)
    End If
End Sub

Private Sub beautify()
'none
End Sub

