VERSION 5.00
Begin VB.Form Form3 
   Caption         =   "单词限猜"
   ClientHeight    =   6945
   ClientLeft      =   5910
   ClientTop       =   2970
   ClientWidth     =   8610
   LinkTopic       =   "Form3"
   ScaleHeight     =   6945
   ScaleWidth      =   8610
   Begin VB.CommandButton Command_exit 
      Caption         =   "退出"
      Height          =   615
      Left            =   5760
      TabIndex        =   8
      Top             =   5640
      Width           =   1095
   End
   Begin VB.CommandButton Command_start 
      Caption         =   "开始"
      Height          =   615
      Left            =   3840
      TabIndex        =   7
      Top             =   5640
      Width           =   975
   End
   Begin VB.OptionButton Option_b 
      Caption         =   "B组"
      Height          =   255
      Left            =   2400
      TabIndex        =   3
      Top             =   3480
      Width           =   855
   End
   Begin VB.OptionButton Option_a 
      Caption         =   "A组"
      Height          =   255
      Left            =   1080
      TabIndex        =   2
      Top             =   3480
      Width           =   975
   End
   Begin VB.Timer Timer 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   2040
      Top             =   2280
   End
   Begin VB.Label Label_pass 
      Caption         =   "跳过"
      Height          =   495
      Left            =   6120
      TabIndex        =   6
      Top             =   4560
      Width           =   855
   End
   Begin VB.Label Label_wrong 
      Caption         =   "犯规"
      Height          =   375
      Left            =   3480
      TabIndex        =   5
      Top             =   4440
      Width           =   1215
   End
   Begin VB.Label Label_right 
      Caption         =   "答对"
      Height          =   615
      Left            =   1080
      TabIndex        =   4
      Top             =   4440
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
      TabIndex        =   1
      Top             =   2040
      Width           =   1695
   End
   Begin VB.Label Label_cy 
      Caption         =   "成语"
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
      Left            =   1920
      TabIndex        =   0
      Top             =   480
      Width           =   3855
   End
End
Attribute VB_Name = "Form3"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim time As Integer '计时
Dim right_a, wrong_a, right_b, wrong_b, pass_a, pass_b As Integer '记录答对和犯规
Dim sum_cy, num_cy As Integer '成语
Dim str_cy(1000) As String
Dim use_cy As Integer
Dim vis_cy(1000) As Boolean  '判断重复
Dim is_ok As Boolean '防止用完


Private Sub Form_Load()
    beautify
    
    is_ok = True
    
    time = Form0.rule3_time
    right_a = 0
    right_b = 0
    wrong_a = 0
    wrong_b = 0
    pass_a = 0
    pass_b = 0
    use_cy = 0
    Option_a.Caption = Form0.name_a + "组"
    Option_b.Caption = Form0.name_b + "组"
    ' 默认为A组
    Option_a.Value = True
    Option_b.Value = False
    
    Label_time.Caption = "倒计时:" + Str(time)
    '链接成语库
    Open "resources\part3\data.txt" For Input As #1
        Dim i As Integer
        i = 0
        Do Until EOF(1)
            Line Input #1, str_cy(i)
            i = i + 1
        Loop
    Close #1
    sum_cy = i - 1
    
End Sub

Private Sub judge()
        
    If right_a > right_b Then ' A win
        Form0.score_a = Form0.score_a + 1
    ElseIf right_a > right_b Then ' B win
        Form0.score_b = Form0.score_b + 1
    Else ' either
        Form0.score_a = Form0.score_a + 1
        Form0.score_b = Form0.score_b + 1
    End If
    
End Sub


Private Sub Label_right_Click() ' 正确

    If Option_a.Value = True Then
    
        If is_ok Then right_a = right_a + 1
        Label_right.Caption = "答对:" + Str(right_a)
        
    Else
    
        If is_ok Then right_b = right_b + 1
        Label_right.Caption = "答对:" + Str(right_b)
        
    End If
    change_cy
    
    
    
End Sub

Private Sub Label_pass_Click() '跳过

    If Option_a.Value = True Then
        If is_ok Then pass_a = pass_a + 1
        Label_pass.Caption = "跳过:" + Str(pass_a)
        
        If pass_a > Form0.rule3_pass Then
            tmp = MsgBox("没机会了", 0, "FBIWarning")
        Else: change_cy
        End If
    Else
        If is_ok Then pass_b = pass_b + 1
        Label_pass.Caption = "跳过:" + Str(pass_b)
        
        If pass_b > Form0.rule3_pass Then
            tmp = MsgBox("没机会了", 0, "FBIWarning")
        Else: change_cy
        End If
    End If
    
End Sub

Private Sub Label_wrong_Click() '错误
    If Option_a.Value = True Then
        If is_ok Then wrong_a = wrong_a + 1
        Label_wrong.Caption = "犯规:" + Str(wrong_a)
        
        If wrong_a > Form0.rule3_wrong Then
            Timer.Enabled = False ' stop
            mp = MsgBox("犯规", 0, "FBIWarning")
        End If
    Else
        If is_ok Then wrong_b = wrong_b + 1
        Label_wrong.Caption = "犯规:" + Str(wrong_b)
        
        If wrong_b > Form0.rule3_wrong Then
            Timer.Enabled = False ' stop
            mp = MsgBox("犯规", 0, "FBIWarning")
        End If
    End If
    
    change_cy
    
End Sub

Private Sub change_cy() ' 换成语

    If use_cy > sum_cy Then
        is_ok = False
        tmp = MsgBox("成语用完了", 0, "FBIWarning")
        Exit Sub
    End If
    
    '四舍五入0-sum_cy
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
    time = time - 1
    If time = 0 Then
        Timer.Enabled = False
        tmp = MsgBox("时间到", 0, "哈哈蠢鸡")
        is_ok = False
    End If
    Label_time.Caption = "倒计时:" + Str(time)
End Sub

Private Sub Command_exit_Click()
    judge '判断胜负
    Form0.score_show
    Unload Me '关闭
End Sub

Private Sub Command_start_Click() ' 开始计时，出现成语
    
    time = Form0.rule3_time
    Label_time.Caption = "倒计时:" + Str(time)
    is_ok = True
    Timer.Enabled = True
    change_cy
End Sub

Private Sub state_show()
    If Option_b.Value = True Then
        Label_right.Caption = "答对:" + Str(right_b)
        Label_wrong.Caption = "犯规:" + Str(wrong_b)
        Label_pass.Caption = "跳过:" + Str(pass_b)
    Else
        Label_right.Caption = "答对:" + Str(right_a)
        Label_wrong.Caption = "犯规:" + Str(wrong_a)
        Label_pass.Caption = "跳过:" + Str(pass_a)
    End If
End Sub

Private Sub beautify()
'none
End Sub

