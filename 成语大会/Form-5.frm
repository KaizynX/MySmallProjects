VERSION 5.00
Begin VB.Form Form5 
   Caption         =   "点球大赛"
   ClientHeight    =   6465
   ClientLeft      =   5715
   ClientTop       =   3750
   ClientWidth     =   11790
   Icon            =   "Form-5.frx":0000
   LinkTopic       =   "Form5"
   ScaleHeight     =   6465
   ScaleWidth      =   11790
   Begin VB.CommandButton Command_change 
      Caption         =   "修改规则"
      Height          =   495
      Left            =   7680
      Style           =   1  'Graphical
      TabIndex        =   14
      Top             =   4200
      Width           =   1695
   End
   Begin VB.TextBox Textr_time 
      Height          =   495
      Left            =   9720
      TabIndex        =   13
      Text            =   "倒计时"
      Top             =   3480
      Width           =   1815
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "A组"
      Height          =   255
      Index           =   1
      Left            =   2640
      Style           =   1  'Graphical
      TabIndex        =   11
      Top             =   3120
      Width           =   1335
   End
   Begin VB.Timer Timer 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   6240
      Top             =   120
   End
   Begin VB.CommandButton Command_wrong 
      Caption         =   "×"
      Height          =   615
      Left            =   5880
      Style           =   1  'Graphical
      TabIndex        =   6
      Top             =   3120
      Width           =   855
   End
   Begin VB.CommandButton Command_right 
      Caption         =   "√"
      Height          =   495
      Left            =   4800
      Style           =   1  'Graphical
      TabIndex        =   5
      Top             =   3120
      Width           =   615
   End
   Begin VB.CommandButton Command_cg 
      Caption         =   "下一题"
      Height          =   615
      Left            =   3840
      Style           =   1  'Graphical
      TabIndex        =   4
      Top             =   3960
      Width           =   1095
   End
   Begin VB.CommandButton Command_answer 
      Caption         =   "公布答案"
      Height          =   615
      Left            =   5520
      Style           =   1  'Graphical
      TabIndex        =   3
      Top             =   3960
      Width           =   1215
   End
   Begin VB.CommandButton Command_exit 
      Caption         =   "退出"
      Height          =   615
      Left            =   9840
      Style           =   1  'Graphical
      TabIndex        =   1
      Top             =   4320
      Width           =   1095
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "A组"
      Height          =   255
      Index           =   0
      Left            =   600
      Style           =   1  'Graphical
      TabIndex        =   0
      Top             =   3120
      Width           =   1335
   End
   Begin VB.Label Labelr_time 
      Caption         =   "正倒计时"
      Height          =   495
      Left            =   7680
      TabIndex        =   12
      Top             =   3480
      Width           =   1575
   End
   Begin VB.Label Label_rule 
      Caption         =   "几把规则"
      Height          =   2895
      Left            =   7920
      TabIndex        =   10
      Top             =   360
      Width           =   2775
   End
   Begin VB.Label Label 
      Caption         =   "Label1"
      Height          =   1815
      Left            =   480
      TabIndex        =   9
      Top             =   960
      Width           =   6735
   End
   Begin VB.Label Label_time 
      Caption         =   "倒计时:"
      Height          =   495
      Left            =   4440
      TabIndex        =   8
      Top             =   120
      Width           =   1455
   End
   Begin VB.Label Label_num 
      Caption         =   "局"
      Height          =   495
      Left            =   840
      TabIndex        =   7
      Top             =   240
      Width           =   2655
   End
   Begin VB.Label Label_answer 
      Caption         =   "答案:"
      Height          =   735
      Left            =   1440
      TabIndex        =   2
      Top             =   3960
      Width           =   1695
   End
   Begin VB.Image Image1 
      Height          =   1350
      Left            =   360
      Picture         =   "Form-5.frx":000C
      Stretch         =   -1  'True
      Top             =   5160
      Width           =   2760
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
Dim state(2) As Integer ' 0 表示没回答 1 表示答错 2 表示答对
Dim str_tmp As String
Dim now As Integer
Dim time As Integer
Dim rule_time As Integer
Dim question_num As Integer '当前题号

Private Sub Form_Load()

    is_ok = True
    is_finish = False
    question_num = 0
    state_a = 0
    state_b = 0
    state_now = 0
    Timer.Interval = 1000
    Timer.Enabled = False
    
    now = 1
    Label_num.Caption = "第" + str(now) + "局"
    
    state_change
    ' 默认为A组
    Optiong(0).Value = True
    Optiong(1).Value = False
    
    reset_answer
    Label.Caption = ""
    Label_answer.Caption = "答案:"
    
    'answer Initialization
    Open App.Path & "\resources\part5\answer.txt" For Input As #1
        Dim i As Integer
        i = 0
        Do Until EOF(1)
            Line Input #1, str_answer(i)
            i = i + 1
        Loop
    Close #1
    sum_answer = i - 1
    
    '规则
    rule_time = 10
    Label_time.Caption = "倒计时" + str(time)
    Labelr_time.Caption = "倒计时"
    Textr_time.Text = str(rule_time)
    time = rule_time
    
    
    beautify
    
    Me.Height = Screen.Height * 2 / 3
    Me.Width = Screen.Width * 2 / 3
    Me.Top = Screen.Height / 6
    Me.Left = Screen.Width / 6
    
End Sub

Private Sub Command_right_Click() ' 正确

    If is_ok = False Or is_finish = True Then Exit Sub

    If Optiong(0).Value = True Then
        state(0) = 2
    Else
        state(1) = 2
    End If
    
    state_change
    judge
End Sub

Private Sub Command_wrong_Click() '错误
    
    If is_ok = False Or is_finish = True Then Exit Sub

    If Optiong(0).Value = True Then
        state(0) = 1
    Else
        state(1) = 1
    End If
    
    state_change
    judge
End Sub

Private Sub Command_cg_Click() '换题

    If is_finish = True Then
        tmp = MsgBox("比赛已经结束", 64, "waring")
        Exit Sub
    End If

    If question_num > sum_answer Then
        tmp = MsgBox("题目用完了", 0, "FBIWarning")
        Exit Sub
    End If
    is_ok = True
    
    Label.Caption = ""
    Open App.Path & "\resources\part5\data" + Replace(str(question_num), " ", "") + ".txt" For Input As #2
        Do Until EOF(2)
            Line Input #2, str_tmp
            Label.Caption = Label.Caption + str_tmp + vbCrLf
        Loop
    Close #2
    '清空答案
    Label_answer.Caption = "答案:"
    question_num = question_num + 1
    
    'If use_answer > sum_answer Then
    '    tmp = MsgBox("题目用完了", 0, "FBIWarning")
    '    Exit Sub
    'End If
    '
    'is_ok = True
    '
    'num_answer = Rnd() * sum_answer '第一次的随机
    'Do While vis_answer(num_answer) = True
    '    num_answer = Rnd() * sum_answer
    'Loop
    'vis_answer(num_answer) = True
    'use_answer = use_answer + 1
    'Label.Caption = ""
    '
    'Open App.Path & "\resources\part5\data" + Replace(str(num_answer), " ", "") + ".txt" For Input As #2
    '    Do Until EOF(2)
    '        Line Input #2, str_tmp
    '        Label.Caption = Label.Caption + vbCrLf + str_tmp
    '    Loop
    'Close #2
    '清空答案
    'Label_answer.Caption = "答案:"
    
    '开始计时
    'time = rule_time
    'Timer.Enabled = True
    'Label_time.Caption = "倒计时:" + str(time)
    
End Sub

Private Sub Command_answer_Click()
    'Timer.Enabled = False
    Label_answer.Caption = "答案:" + str_answer(question_num - 1)
    'Print question_num
End Sub

Private Sub Command_exit_Click()
    form0.score_show
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
    If state(1) = 0 Or state(0) = 0 Then Exit Sub
        
    If state(0) = state(1) Then
        tmp = MsgBox("进入下一局", 0, "额")
        '局数 + 1
        now = now + 1
        Label_num.Caption = "第" + str(now) + "局"
        
    ElseIf state(0) > state(1) Then
        tmp = MsgBox(form0.qname(0) + "赢了", 0, "该局结束")
        is_finish = True
        form0.add_score (0)
        form0.score_show
        
    Else
        tmp = MsgBox(form0.qname(1) + "赢了", 0, "该局结束")
        is_finish = True
        form0.add_score (1)
        form0.score_show
        
    End If
    '状态重置
    reset_state
    state_change
    
End Sub

Private Sub state_change()
    '暂停
    'Timer.Enabled = False
    
    If state(0) = 0 Then
        Optiong(0).Caption = form0.qname(0)
    ElseIf state(0) = 1 Then
        Optiong(0).Caption = form0.qname(0) + "×"
    Else
        Optiong(0).Caption = form0.qname(0) + "√"
    End If
    
    If state(1) = 0 Then
        Optiong(1).Caption = form0.qname(1)
    ElseIf state(1) = 1 Then
        Optiong(1).Caption = form0.qname(1) + "×"
    Else
        Optiong(1).Caption = form0.qname(1) + "√"
    End If
    
End Sub

Private Sub Optiong_Click(Index As Integer)
    state_change
End Sub

Private Sub Timer_Timer()
    'time = time - 1
    'Label_time.Caption = "倒计时:" + str(time)
    'If time <= 0 Then
        '算错
    '    If Optiong(0).Value = True Then
    '        state(0) = 1
    '    Else
    '        state(1) = 1
    '    End If
    '    state_change
    '    judge
        '以上
    '    Timer.Enabled = False
    '    is_ok = False
    '    tmp = MsgBox("时间到", 0, "warning")
    'End If
End Sub

Private Sub reset_state()
    state(0) = 0
    state(1) = 0
End Sub

Private Sub Command_change_Click()
    'rule_time = Val(Textr_time.Text)
    'time = rule_time
    'Label_time.Caption = "倒计时:" + str(time)
    'tmp = MsgBox("修改成功", 0, "恭喜你")
End Sub

Private Sub Form_Resize()
    beautify
End Sub

Private Sub beautify()
    
    Label_rule.Caption = "前一轮胜方优先答题（成语知识相关），采用类似点球大战的方式，当同一道次题（A 方答的第n道题和B方答的第n道题都称为第n道）一方答对，另一方答错时，答对的那一方获得本局胜利，若同一道次的题双方都答错，则答题继续。"
    
'    Me.Height = Screen.Height * 2 / 3
'    Me.Width = Screen.Width * 2 / 3
'    Me.Top = Screen.Height / 6
'    Me.Left = Screen.Width / 6
    Image1.Left = 0
    Image1.Top = 0
    Image1.Height = Me.Height
    Image1.Width = Me.Width
    
     '统一设置背景颜色，字体，字体大小
    Dim obj As Object
    For Each obj In Me.Controls
        If TypeName(obj) = "TextBox" Then
            obj.Font.Name = "华文中宋"
            obj.BackColor = vbWhite
            obj.Font.Size = Me.Width / 750
        ElseIf TypeName(obj) = "CommandButton" Then
            obj.Font.Name = "华文中宋"
            obj.BackColor = vbWhite
            obj.Font.Size = Me.Width / 750
        ElseIf TypeName(obj) = "Label" Then
            obj.Alignment = 2
            obj.Font.Name = "华文中宋"
            obj.BackColor = vbWhite
            obj.Font.Size = Me.Width / 750
            obj.BorderStyle = 1
        ElseIf TypeName(obj) = "OptionButton" Then
            obj.Font.Name = "华文中宋"
            obj.BackColor = vbWhite
            obj.Font.Size = Me.Width / 750
            obj.Width = Me.Width * 15 / 100
            obj.Height = Me.Height * 10 / 100
            obj.Top = Me.Height * 60 / 100
        End If
    Next
    
    '规则
    Label_rule.Alignment = 0
    Label_rule.Width = Me.Width * 25 / 100
    Label_rule.Height = Me.Height * 60 / 100
    Label_rule.Top = Me.Height * 5 / 100
    Label_rule.Left = Me.Width * 70 / 100
    
    Labelr_time.Visible = False
    'Labelr_time.Width = Me.Width * 12 / 100
    'Labelr_time.Height = Me.Height * 8 / 100
    'Labelr_time.Top = Me.Height * 70 / 100
    'Labelr_time.Left = Me.Width * 70 / 100
    
    Textr_time.Visible = False
    'Textr_time.Width = Me.Width * 12 / 100
    'Textr_time.Height = Me.Height * 8 / 100
    'Textr_time.Top = Me.Height * 70 / 100
    'Textr_time.Left = Me.Width * 83 / 100
    '修改规则按钮
    Command_change.Visible = False
    'Command_change.Width = Me.Width * 12 / 100
    'Command_change.Height = Me.Height * 12 / 100
    'Command_change.Top = Me.Height * 80 / 100
    'Command_change.Left = Me.Width * 70 / 100
    '退出按钮
    Command_exit.Width = Me.Width * 12 / 100
    Command_exit.Height = Me.Height * 12 / 100
    Command_exit.Top = Me.Height * 80 / 100
    Command_exit.Left = Me.Width * 83 / 100
    '第几局
    Label_num.Width = Me.Width * 25 / 100
    Label_num.Left = Me.Width * 20 / 100
    Label_num.Height = Me.Height * 10 / 100
    Label_num.Top = Me.Height * 5 / 100
    '倒计时
    Label_time.Visible = False
    'Label_time.Width = Me.Width * 25 / 100
    'Label_time.Left = Me.Width * 35 / 100
    'Label_time.Height = Me.Height * 10 / 100
    'Label_time.Top = Me.Height * 5 / 100
    '题目
    Label.Alignment = 0
    Label.Width = Me.Width * 55 / 100
    Label.Left = Me.Width * 5 / 100
    Label.Height = Me.Height * 35 / 100
    Label.Top = Me.Height * 20 / 100
    '小组
    Optiong(0).Left = Me.Width * 5 / 100
    Optiong(1).Left = Me.Width * 25 / 100
    '对错
    Command_right.Width = Me.Width * 8 / 100
    Command_right.Height = Me.Height * 10 / 100
    Command_right.Top = Me.Height * 60 / 100
    Command_right.Left = Me.Width * 42 / 100
    
    Command_wrong.Width = Me.Width * 8 / 100
    Command_wrong.Height = Me.Height * 10 / 100
    Command_wrong.Top = Me.Height * 60 / 100
    Command_wrong.Left = Me.Width * 52 / 100
    '答案
    Label_answer.Width = Me.Width * 15 / 100
    Label_answer.Height = Me.Height * 10 / 100
    Label_answer.Top = Me.Height * 75 / 100
    Label_answer.Left = Me.Width * 5 / 100
    '换成语
    Command_cg.Width = Me.Width * 15 / 100
    Command_cg.Height = Me.Height * 10 / 100
    Command_cg.Top = Me.Height * 75 / 100
    Command_cg.Left = Me.Width * 25 / 100
    '公布答案
    Command_answer.Width = Me.Width * 15 / 100
    Command_answer.Height = Me.Height * 10 / 100
    Command_answer.Top = Me.Height * 75 / 100
    Command_answer.Left = Me.Width * 45 / 100
    
End Sub

