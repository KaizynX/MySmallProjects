VERSION 5.00
Begin VB.Form Form5 
   Caption         =   "点球大战"
   ClientHeight    =   4860
   ClientLeft      =   7065
   ClientTop       =   4125
   ClientWidth     =   8910
   LinkTopic       =   "Form5"
   ScaleHeight     =   4860
   ScaleWidth      =   8910
   Begin VB.Timer Timer 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   6720
      Top             =   240
   End
   Begin VB.CommandButton Command_wrong 
      Caption         =   "×"
      Height          =   615
      Left            =   2040
      TabIndex        =   8
      Top             =   3840
      Width           =   855
   End
   Begin VB.CommandButton Command_right 
      Caption         =   "√"
      Height          =   495
      Left            =   480
      TabIndex        =   7
      Top             =   3840
      Width           =   615
   End
   Begin VB.CommandButton Command_change 
      Caption         =   "换"
      Height          =   615
      Left            =   6720
      TabIndex        =   6
      Top             =   1920
      Width           =   1095
   End
   Begin VB.CommandButton Command_answer 
      Caption         =   "公布答案"
      Height          =   615
      Left            =   6600
      TabIndex        =   5
      Top             =   3000
      Width           =   1215
   End
   Begin VB.CommandButton Command_exit 
      Caption         =   "退出"
      Height          =   615
      Left            =   7320
      TabIndex        =   3
      Top             =   3960
      Width           =   1095
   End
   Begin VB.OptionButton Option_b 
      Caption         =   "B组"
      Height          =   255
      Left            =   1920
      TabIndex        =   2
      Top             =   2760
      Width           =   1575
   End
   Begin VB.OptionButton Option_a 
      Caption         =   "A组"
      Height          =   255
      Left            =   360
      TabIndex        =   1
      Top             =   2760
      Width           =   1335
   End
   Begin VB.Label Label_time 
      Caption         =   "倒计时:"
      Height          =   495
      Left            =   6360
      TabIndex        =   10
      Top             =   960
      Width           =   1455
   End
   Begin VB.Label Label_num 
      Caption         =   "局"
      Height          =   495
      Left            =   2640
      TabIndex        =   9
      Top             =   120
      Width           =   2655
   End
   Begin VB.Label Label_answer 
      Caption         =   "答案:"
      Height          =   735
      Left            =   4320
      TabIndex        =   4
      Top             =   3000
      Width           =   1695
   End
   Begin VB.Label Label 
      Caption         =   "判断"
      Height          =   1815
      Left            =   480
      TabIndex        =   0
      Top             =   720
      Width           =   5295
   End
End
Attribute VB_Name = "Form5"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim sum_answer, num_answer As Integer
Dim str_answer(1000) As String
Dim use_answer As Integer
Dim vis_answer(1000) As Boolean
Dim is_start As Boolean
Dim is_ok, is_finish As Boolean
' state_now 记录回答了题目的组数
Dim state_a, state_b As Integer ' 0 表示没回答 1 表示答错 2 表示答对
Dim str_tmp As String
Dim now As Integer
Dim time As Integer

Private Sub Form_Load()
    beautify

    is_ok = True
    is_finish = False
    state_a = 0
    state_b = 0
    state_now = 0
    Timer.Interval = 1000
    Timer.Enabled = False
    time = Form0.rule5_time
    
    now = 1
    Label_num.Caption = "第" + Str(now) + "局"
    
    state_change
    ' 默认为A组
    Option_a.Value = True
    Option_b.Value = False
    
    reset_answer
    Label.Caption = ""
    Label_answer.Caption = "答案:"
    
    'answer Initialization
    Open "resources\part5\answer.txt" For Input As #1
        Dim i As Integer
        i = 0
        Do Until EOF(1)
            Line Input #1, str_answer(i)
            i = i + 1
        Loop
    Close #1
    sum_answer = i - 1
    
End Sub

Private Sub Command_right_Click() ' 正确

    If is_ok = False Or is_finish = True Then Exit Sub

    If Option_a.Value = True Then
        state_a = 2
    Else
        state_b = 2
    End If
    
    state_change
    judge
End Sub

Private Sub Command_wrong_Click() '错误
    
    If is_ok = False Or is_finish = True Then Exit Sub

    If Option_a.Value = True Then
        state_a = 1
    Else
        state_b = 1
    End If
    
    state_change
    judge
End Sub

Private Sub Command_change_Click() '换题

    If is_finish = True Then
        tmp = MsgBox("比赛已经结束", 0, "还点你麻痹点")
        Exit Sub
    End If

    If use_answer > sum_answer Then
        tmp = MsgBox("题目用完了", 0, "FBIWarning")
        Exit Sub
    End If
    
    is_ok = True
    
    num_answer = Rnd() * sum_answer '第一次的随机
    Do While vis_answer(num_answer) = True
        num_answer = Rnd() * sum_answer
    Loop
    vis_answer(num_answer) = True
    use_answer = use_answer + 1
    Label.Caption = ""
    
    Open "resources\part5\data" + Replace(Str(num_answer), " ", "") + ".txt" For Input As #2
        Do Until EOF(2)
            Line Input #2, str_tmp
            Label.Caption = Label.Caption + vbCrLf + str_tmp
        Loop
    Close #2
    '清空答案
    Label_answer.Caption = "答案:"
    
    '开始计时
    time = Form0.rule5_time
    Timer.Enabled = True
    Label_time.Caption = "倒计时:" + Str(time)
    
End Sub

Private Sub Command_answer_Click()
    Timer.Enabled = False
    Label_answer.Caption = "答案:" + str_answer(num_answer)
End Sub

Private Sub Command_exit_Click()
    Form0.score_show
    Unload Me
End Sub

Private Sub reset_answer() '重置vis
    Dim i As Integer
    For i = 0 To 999
        vis_answer(i) = False
    Next i
    use_answer = 0
End Sub

Private Sub judge()
    '还没答完
    If state_a = 0 Or state_b = 0 Then Exit Sub
        
    If state_a = state_b Then
        tmp = MsgBox("进入下一局", 0, "额")
        '局数 + 1
        now = now + 1
        Label_num.Caption = "第" + Str(now) + "局"
        
    ElseIf state_a > state_b Then
        Form0.score_a = Form0.score_a + 1
        Form0.score_show
        tmp = MsgBox(name_a + "组赢了", 0, "恭恭喜发财")
        is_finish = True
        
    Else
        Form0.score_a = Form0.score_a + 1
        Form0.score_show
        tmp = MsgBox(name_b + "组赢了", 0, "恭恭喜发财")
        is_finish = True
        
    End If
    '状态重置
    state_a = 0
    state_b = 0
    state_change
    
End Sub

Private Sub state_change()
    '暂停
    Timer.Enabled = False
    
    If state_a = 0 Then
        Option_a.Caption = Form0.name_a + "组"
    ElseIf state_a = 1 Then
        Option_a.Caption = Form0.name_a + "组×"
    Else
        Option_a.Caption = Form0.name_a + "组√"
    End If
    
    If state_b = 0 Then
        Option_b.Caption = Form0.name_b + "组"
    ElseIf state_b = 1 Then
        Option_b.Caption = Form0.name_b + "组×"
    Else
        Option_b.Caption = Form0.name_b + "组√"
    End If
    
End Sub

Private Sub beautify()
'none
End Sub


Private Sub Timer_Timer()
    time = time - 1
    Label_time.Caption = "倒计时:" + Str(time)
    If time <= 0 Then
        '算错
        If Option_a.Value = True Then
            state_a = 1
        Else
            state_b = 1
        End If
        state_change
        judge
        '以上
        Timer.Enabled = False
        is_ok = False
        tmp = MsgBox("时间到", 0, "warning")
    End If
End Sub
