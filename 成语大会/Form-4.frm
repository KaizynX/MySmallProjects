VERSION 5.00
Begin VB.Form Form4 
   Caption         =   "限时竞猜"
   ClientHeight    =   6480
   ClientLeft      =   6480
   ClientTop       =   3750
   ClientWidth     =   14250
   Icon            =   "Form-4.frx":0000
   LinkTopic       =   "Form4"
   ScaleHeight     =   6480
   ScaleWidth      =   14250
   Begin VB.TextBox Text_answer 
      Height          =   615
      Left            =   840
      TabIndex        =   15
      Text            =   "输入"
      Top             =   3240
      Width           =   2895
   End
   Begin VB.TextBox Textr_v 
      Height          =   495
      Left            =   12000
      TabIndex        =   14
      Text            =   "速度"
      Top             =   4440
      Width           =   1815
   End
   Begin VB.CommandButton Command_change 
      Caption         =   "修改规则"
      Height          =   495
      Left            =   10560
      Style           =   1  'Graphical
      TabIndex        =   12
      Top             =   5760
      Width           =   1695
   End
   Begin VB.TextBox Textr_right 
      Height          =   495
      Left            =   12000
      TabIndex        =   11
      Text            =   "正确"
      Top             =   3480
      Width           =   1815
   End
   Begin VB.OptionButton Optiong 
      Height          =   255
      Index           =   2
      Left            =   3480
      Style           =   1  'Graphical
      TabIndex        =   8
      Top             =   4320
      Width           =   975
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "2"
      Height          =   255
      Index           =   1
      Left            =   1920
      Style           =   1  'Graphical
      TabIndex        =   7
      Top             =   4320
      Width           =   975
   End
   Begin VB.CommandButton Command_answer 
      Caption         =   "公布答案"
      Height          =   615
      Left            =   7080
      Style           =   1  'Graphical
      TabIndex        =   6
      Top             =   3240
      Width           =   1215
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "A组"
      Height          =   255
      Index           =   0
      Left            =   480
      Style           =   1  'Graphical
      TabIndex        =   4
      Top             =   4320
      Width           =   975
   End
   Begin VB.CommandButton Command_run 
      Caption         =   "控制"
      Height          =   735
      Left            =   5520
      Style           =   1  'Graphical
      TabIndex        =   3
      Top             =   5040
      Width           =   1215
   End
   Begin VB.CommandButton Command_cg 
      Caption         =   "换"
      Height          =   615
      Left            =   3600
      Style           =   1  'Graphical
      TabIndex        =   2
      Top             =   4920
      Width           =   1095
   End
   Begin VB.CommandButton Command_exit 
      Caption         =   "退出"
      Height          =   615
      Left            =   12600
      Style           =   1  'Graphical
      TabIndex        =   1
      Top             =   5640
      Width           =   1095
   End
   Begin VB.Timer Timer 
      Interval        =   500
      Left            =   0
      Top             =   0
   End
   Begin VB.Label Labelr_v 
      Caption         =   "速度"
      Height          =   495
      Left            =   10200
      TabIndex        =   13
      Top             =   4440
      Width           =   1575
   End
   Begin VB.Label Labelr_right 
      Caption         =   "正确"
      Height          =   495
      Left            =   9840
      TabIndex        =   10
      Top             =   3600
      Width           =   1575
   End
   Begin VB.Label Label_rule 
      Caption         =   "几把规则"
      Height          =   2895
      Left            =   9600
      TabIndex        =   9
      Top             =   360
      Width           =   4095
   End
   Begin VB.Label Label_right 
      Caption         =   "答对"
      Height          =   615
      Left            =   840
      TabIndex        =   5
      Top             =   5040
      Width           =   1695
   End
   Begin VB.Label Label 
      Caption         =   "判断"
      Height          =   2580
      Left            =   600
      TabIndex        =   0
      Top             =   360
      Width           =   7800
   End
   Begin VB.Image Image1 
      Height          =   840
      Left            =   8040
      Picture         =   "Form-4.frx":1084A
      Stretch         =   -1  'True
      Top             =   5640
      Width           =   2115
   End
End
Attribute VB_Name = "Form4"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim sum_answer, num_answer As Integer
Dim sum_line, num_line As Integer
Dim sum_len, num_len As Integer
Dim str_answer(1000) As String
Dim str_words(1000) As String
Dim use_answer As Integer
Dim vis_answer(1000) As Boolean
Dim is_start As Boolean
Dim is_ok As Boolean
Dim right(3), wrong(3) As Integer '记录答对和犯规
Dim cur, gnum, i As Integer
Dim rule_right, rule_v As Integer
Dim num_in_label As Integer

Private Sub Form_Load()

    is_ok = True
    gnum = form0.gnum
    num_in_label = 0
    
    For i = 0 To gnum
        right(i) = 0
        wrong(i) = 0
        Optiong(i).Caption = form0.qname(i)
    Next i
    
    ' 默认为A组
    Optiong(0).Value = True
    Optiong(1).Value = False
    If form0.gnum < 2 Then
        Optiong(2).Caption = ""
        Optiong(2).Enabled = False '禁用
        Optiong(2).Visible = False
    Else
        Optiong(2).Value = False
    End If
    
    num_answer = 0
    reset_answer
    num_line = 0
    num_len = 0
    is_start = False
    Command_run.Caption = "开始"
    Label.Caption = ""
    
    'answer Initialization
    Open "resources\part4\answer.txt" For Input As #1
        i = 0
        Do Until EOF(1)
            Line Input #1, str_answer(i)
            i = i + 1
        Loop
    Close #1
    sum_answer = i - 1
    
    '规则
    rule_right = 2
    rule_v = 250
    Labelr_right.Caption = "题数"
    'Labelr_v.Caption = "速度 单位:字/秒"
    Labelr_v.Caption = "速度"
    Textr_right.Text = str(rule_right)
    Textr_v.Text = str(1000 / rule_v)
    
    Timer.Enabled = False
    Timer.Interval = rule_v
    
    beautify
    Me.Height = Screen.Height
    Me.Width = Screen.Width
    Me.Top = 0
    Me.Left = 0
    Me.WindowState = 2 '全屏
    
End Sub

Private Sub Label_right_Click() ' 正确

    If is_ok = False Then Exit Sub
    '获得当前组
    get_now
    
    right(cur) = right(cur) + 1
    
    state_show
    
    If right(cur) >= rule_right Then
        is_ok = False
        Timer.Enabled = False ' stop
        'tmp = MsgBox("完成", 0, "提示")
    End If
    
    judge
    
End Sub


Private Sub Command_run_Click()

    If is_start Then '原本开始,现在暂停
        Timer.Enabled = False
        is_start = False
        Command_run.Caption = "开始"
    Else
        Timer.Enabled = True
        is_start = True
        Command_run.Caption = "暂停"
    End If
End Sub

Private Sub Command_cg_Click()

    If use_answer > sum_answer Then
        tmp = MsgBox("成语用完了", 0, "FBIWarning")
        Exit Sub
    End If
    
    num_answer = Rnd() * sum_answer '第一次的随机
    Do While vis_answer(num_answer) = True
        num_answer = Rnd() * sum_answer
    Loop
    vis_answer(num_answer) = True
    use_answer = use_answer + 1
    Label.Caption = ""
    num_in_label = 0
    
    Open "resources\part4\data" + Replace(str(num_answer), " ", "") + ".txt" For Input As #2
        Dim i As Integer
        i = 0
        Do Until EOF(2)
            Line Input #2, str_words(i)
            i = i + 1
        Loop
    Close #2
    sum_line = i - 1
    num_line = 0
    num_len = 0
    '换了要暂停
    Timer.Enabled = False
    is_start = False
    Command_run.Caption = "开始"
    '清空答案
    Text_answer.Text = "输入你的伟大猜想"
    '显示序号
    Command_cg.Caption = "当前:" + str(num_answer)
End Sub

Private Sub Optiong_Click(Index As Integer)
    state_show
End Sub

Private Sub Timer_Timer()
    '读完了
    If num_line > sum_line Then
        Timer.Enabled = False
        Exit Sub
    End If
    
    sum_len = Len(str_words(num_line))
    If num_len < sum_len Then
        Label.Caption = Label.Caption + Mid(str_words(num_line), num_len + 1, 1)
        num_in_label = num_in_label + 1
        num_len = num_len + 1
    Else
        '读取下一行
        Label.Caption = Label.Caption + vbCrLf
        num_line = num_line + 1
        num_len = 0
    End If
    
End Sub

Private Sub Command_answer_Click()
    Dim your_answer As String
    your_answer = Replace(Text_answer.Text, " ", "")
    If Replace(str_answer(num_answer), " ", "") = your_answer Then
        tmp = MsgBox("答对了", 0, "恭喜李")
        Label_right_Click '加分
    Else
        tmp = MsgBox("答错了", 0, "恭喜李")
    End If
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
    Dim winner As Integer
    winner = -1
    For i = 0 To gnum
        If right(i) >= rule_right Then
            winner = i
            Exit For
        End If
    Next i
    
    If winner = -1 Then Exit Sub
    
    tmp = MsgBox(form0.qname(winner) + "赢了", 0, "结果")
    form0.add_score (winner)
    form0.score_show
    is_ok = False
    
End Sub

Private Sub state_show()

    '获得当前组
    get_now
    
    Label_right.Caption = "答对:" + str(right(cur))
    
End Sub

Private Sub get_now()
    '获得当前组
    For i = 0 To gnum
        If Optiong(i) = True Then cur = i
    Next i
End Sub

Private Sub Command_change_Click()
    rule_right = Val(Textr_right.Text)
    rule_v = 1000 / Val(Textr_v.Text)
    Timer.Interval = rule_v
    tmp = MsgBox("修改成功", 0, "恭喜你")
End Sub

Private Sub Form_Resize()
    beautify
End Sub

Private Sub beautify()
    
    'Me.Height = Screen.Height * 2 / 3
    'Me.Width = Screen.Width * 2 / 3
    'Me.Top = Screen.Height / 6
    'Me.Left = Screen.Width / 6
    Image1.Left = 0
    Image1.Top = 0
    Image1.Height = Me.Height
    Image1.Width = Me.Width
    
    Label_rule.Caption = "两队在主持人描述题中的成语的出处或相关背景时进行抢答，然后在规定时间内说出结果，若正确，计入一分，若在第三次（及以上）错误或不答，这一分计入对方队伍。先拿到两分的一方胜出。"
    
    '统一设置背景颜色，字体，字体大小
    Dim obj As Object
    For Each obj In Me.Controls
        If TypeName(obj) = "TextBox" Then
            obj.Font.Name = "华文行楷"
            obj.BackColor = vbWhite
            obj.Font.Size = Me.Width / 750
        ElseIf TypeName(obj) = "CommandButton" Then
            obj.Font.Name = "华文行楷"
            obj.BackColor = vbWhite
            obj.Font.Size = Me.Width / 750
        ElseIf TypeName(obj) = "Label" Then
            obj.Alignment = 2
            obj.Font.Name = "华文行楷"
            obj.BackColor = vbWhite
            obj.Font.Size = Me.Width / 750
        ElseIf TypeName(obj) = "OptionButton" Then
            obj.Font.Name = "华文行楷"
            obj.BackColor = vbWhite
            obj.Font.Size = Me.Width / 750
            obj.Width = Me.Width * 18 / 100
            obj.Height = Me.Height * 8 / 100
            obj.Top = Me.Height * 74 / 100
        End If
    Next
    
    '成语
    Label.Alignment = 0
    Label.Width = Me.Width * 64 / 100
    Label.Height = Me.Height * 57 / 100
    Label.Top = Me.Height * 3 / 100
    Label.Left = Me.Width * 3 / 100
    Label.Font.Size = Me.Width / 1000
    'List.Visible = False
    'List.Width = Me.Width * 55 / 100
    'List.Height = Me.Height * 40 / 100
    'List.Top = Me.Height * 5 / 100
    'List.Left = Me.Width * 5 / 100
    '组
    Optiong(0).Left = Me.Width * 3 / 100
    Optiong(1).Left = Me.Width * 26 / 100
    Optiong(2).Left = Me.Width * 44 / 100
    '成绩
    Label_right.Width = Me.Width * 18 / 100
    Label_right.Height = Me.Height * 8 / 100
    Label_right.Top = Me.Height * 85 / 100
    Label_right.Left = Me.Width * 3 / 100
    '输入
    Text_answer.Width = Me.Width * 41 / 100
    Text_answer.Height = Me.Height * 8 / 100
    Text_answer.Top = Me.Height * 63 / 100
    Text_answer.Left = Me.Width * 3 / 100
    '验证
    Command_answer.Width = Me.Width * 18 / 100
    Command_answer.Height = Me.Height * 8 / 100
    Command_answer.Top = Me.Height * 63 / 100
    Command_answer.Left = Me.Width * 49 / 100
    '换
    Command_cg.Width = Me.Width * 18 / 100
    Command_cg.Height = Me.Height * 8 / 100
    Command_cg.Top = Me.Height * 85 / 100
    Command_cg.Left = Me.Width * 26 / 100
    '控制
    Command_run.Width = Me.Width * 18 / 100
    Command_run.Height = Me.Height * 8 / 100
    Command_run.Top = Me.Height * 85 / 100
    Command_run.Left = Me.Width * 49 / 100
    '规则
    Label_rule.Alignment = 0
    Label_rule.Width = Me.Width * 25 / 100
    Label_rule.Height = Me.Height * 57 / 100
    Label_rule.Top = Me.Height * 3 / 100
    Label_rule.Left = Me.Width * 72 / 100
    
    Labelr_right.Width = Me.Width * 10 / 100
    Labelr_right.Height = Me.Height * 8 / 100
    Labelr_right.Top = Me.Height * 63 / 100
    Labelr_right.Left = Me.Width * 72 / 100
    
    Textr_right.Width = Me.Width * 10 / 100
    Textr_right.Height = Me.Height * 8 / 100
    Textr_right.Top = Me.Height * 63 / 100
    Textr_right.Left = Me.Width * 87 / 100
    
    Labelr_v.Width = Me.Width * 10 / 100
    Labelr_v.Height = Me.Height * 8 / 100
    Labelr_v.Top = Me.Height * 74 / 100
    Labelr_v.Left = Me.Width * 72 / 100
    
    Textr_v.Width = Me.Width * 10 / 100
    Textr_v.Height = Me.Height * 8 / 100
    Textr_v.Top = Me.Height * 74 / 100
    Textr_v.Left = Me.Width * 87 / 100
    '修改规则
    Command_change.Width = Me.Width * 12 / 100
    Command_change.Height = Me.Height * 8 / 100
    Command_change.Top = Me.Height * 85 / 100
    Command_change.Left = Me.Width * 72 / 100
    '退出
    Command_exit.Width = Me.Width * 10 / 100
    Command_exit.Height = Me.Height * 8 / 100
    Command_exit.Top = Me.Height * 85 / 100
    Command_exit.Left = Me.Width * 87 / 100
    
    
End Sub

