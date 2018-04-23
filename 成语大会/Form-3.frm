VERSION 5.00
Begin VB.Form Form3 
   Caption         =   "单词限猜"
   ClientHeight    =   5940
   ClientLeft      =   5910
   ClientTop       =   2970
   ClientWidth     =   11265
   Icon            =   "Form-3.frx":0000
   LinkTopic       =   "Form3"
   ScaleHeight     =   5940
   ScaleWidth      =   11265
   Begin VB.TextBox Textr_time 
      Height          =   495
      Left            =   9240
      TabIndex        =   17
      Text            =   "倒计时"
      Top             =   4680
      Width           =   1815
   End
   Begin VB.CommandButton Command_change 
      Caption         =   "修改规则"
      Height          =   495
      Left            =   7200
      Style           =   1  'Graphical
      TabIndex        =   15
      Top             =   5280
      Width           =   1695
   End
   Begin VB.TextBox Textr_pass 
      Height          =   495
      Left            =   7200
      TabIndex        =   14
      Text            =   "跳过"
      Top             =   4680
      Width           =   1815
   End
   Begin VB.TextBox Textr_wrong 
      Height          =   495
      Left            =   5280
      TabIndex        =   12
      Text            =   "犯规"
      Top             =   4680
      Width           =   1695
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "3"
      Height          =   255
      Index           =   2
      Left            =   3480
      Style           =   1  'Graphical
      TabIndex        =   9
      Top             =   3240
      Width           =   975
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "2"
      Height          =   255
      Index           =   1
      Left            =   2040
      Style           =   1  'Graphical
      TabIndex        =   8
      Top             =   3240
      Width           =   975
   End
   Begin VB.CommandButton Command_exit 
      Caption         =   "退出"
      Height          =   615
      Left            =   9720
      Style           =   1  'Graphical
      TabIndex        =   7
      Top             =   5280
      Width           =   1095
   End
   Begin VB.CommandButton Command_start 
      Caption         =   "开始"
      Height          =   615
      Left            =   3360
      Style           =   1  'Graphical
      TabIndex        =   6
      Top             =   2040
      Width           =   975
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "A组"
      Height          =   255
      Index           =   0
      Left            =   600
      Style           =   1  'Graphical
      TabIndex        =   2
      Top             =   3240
      Width           =   975
   End
   Begin VB.Timer Timer 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   2040
      Top             =   2280
   End
   Begin VB.Label Labelr_time 
      Caption         =   "正倒计时"
      Height          =   495
      Left            =   9360
      TabIndex        =   16
      Top             =   3720
      Width           =   1575
   End
   Begin VB.Label Labelr_pass 
      Caption         =   "跳过"
      Height          =   615
      Left            =   7560
      TabIndex        =   13
      Top             =   3720
      Width           =   1575
   End
   Begin VB.Label Labelr_wrong 
      Caption         =   "犯规"
      Height          =   495
      Left            =   5280
      TabIndex        =   11
      Top             =   3720
      Width           =   1815
   End
   Begin VB.Label Label_rule 
      Caption         =   "几把规则"
      Height          =   2895
      Left            =   5280
      TabIndex        =   10
      Top             =   360
      Width           =   5775
   End
   Begin VB.Label Label_pass 
      Caption         =   "跳过"
      Height          =   495
      Left            =   3840
      TabIndex        =   5
      Top             =   4320
      Width           =   855
   End
   Begin VB.Label Label_wrong 
      Caption         =   "犯规"
      Height          =   375
      Left            =   2040
      TabIndex        =   4
      Top             =   4320
      Width           =   1215
   End
   Begin VB.Label Label_right 
      Caption         =   "答对"
      Height          =   615
      Left            =   120
      TabIndex        =   3
      Top             =   4200
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
      Left            =   120
      TabIndex        =   1
      Top             =   2040
      Width           =   1695
   End
   Begin VB.Label Label_cy 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "成语"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   42
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1095
      Left            =   480
      TabIndex        =   0
      Top             =   480
      Width           =   3855
   End
   Begin VB.Image Image1 
      Height          =   840
      Left            =   960
      Picture         =   "Form-3.frx":1084A
      Stretch         =   -1  'True
      Top             =   5040
      Width           =   2115
   End
End
Attribute VB_Name = "Form3"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim time As Integer '计时
Dim right(3), wrong(3), pass(3) As Integer '记录答对和犯规
Dim sum_cy, num_cy As Integer '成语
Dim str_cy(1000) As String
Dim use_cy As Integer
Dim vis_cy(1000) As Boolean  '判断重复
Dim is_ok As Boolean '防止用完
Dim cur, gnum, i As Integer
Dim rule_wrong, rule_pass, rule_time As Integer


Private Sub Form_Load()
    
    is_ok = True
    
    gnum = form0.gnum
    
    For i = 0 To gnum
        right(i) = 0
        wrong(i) = 0
        pass(i) = 0
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
    
    '链接成语库
    Open "resources\part3\data.txt" For Input As #1
        i = 0
        Do Until EOF(1)
            Line Input #1, str_cy(i)
            i = i + 1
        Loop
    Close #1
    sum_cy = i - 1
    
    '规则
    rule_wrong = 2
    rule_pass = 2
    rule_time = 90
    Labelr_wrong.Caption = "犯规"
    Labelr_pass.Caption = "跳过"
    Labelr_time.Caption = "倒计时"
    Textr_wrong.Text = str(rule_wrong)
    Textr_pass.Text = str(rule_pass)
    Textr_time.Text = str(rule_time)
    
    time = rule_time
    Label_time.Caption = "倒计时:" + str(time)
    
    beautify
    
End Sub

Private Sub judge()
    Dim maxv, maxn, maxi As Integer '记录最高分的分数和个数序号
    Dim win(3) As Integer
    '初始
    For i = 0 To gnum
        win(i) = True
    Next i
    
    '答对
    maxv = -1
    maxi = -1
    maxn = 0
    For i = 0 To gnum
        If win(i) = False Then '跳过
        ElseIf right(i) > maxv Then
            maxv = right(i)
            maxn = 1
            maxi = i
        ElseIf maxv = right(i) Then
            maxn = maxn + 1
        End If
    Next i
    
    If maxn = 1 Then ' find the wineer
        tmp = MsgBox(form0.qname(maxi) + "赢了", 0, "结果")
        form0.add_score (maxi)
        Exit Sub
    Else ' maxn > 1
        For i = 0 To gnum
            If right(i) < maxv Then
                win(i) = False 'no chance to win
            End If
        Next i
    End If
    
    
    '犯规犯规少的
    maxv = 10000
    maxi = -1
    maxn = 0
    For i = 0 To gnum
        If win(i) = False Then 'jump
        ElseIf wrong(i) < maxv Then
            maxv = wrong(i)
            maxn = 1
            maxi = i
        ElseIf maxv = wrong(i) Then
            maxn = maxn + 1
        End If
    Next i
    
    If maxn = 1 Then ' find the wineer
        tmp = MsgBox(form0.qname(maxi) + "赢了", 0, "结果")
        form0.add_score (maxi)
        Exit Sub
    Else ' maxn > 1
        For i = 0 To gnum
            If wrong(i) > maxv Then
                win(i) = False 'no chance to win
            End If
        Next i
    End If
    
    '跳过少的
    maxv = 10000
    maxi = -1
    maxn = 0
    For i = 0 To gnum
        If win(i) = False Then '
        ElseIf pass(i) < maxv Then
            maxv = pass(i)
            maxn = 1
            maxi = i
        ElseIf maxv = pass(i) Then
            maxn = maxn + 1
        End If
    Next i
    
    If maxn = 1 Then ' find the wineer
        tmp = MsgBox(form0.qname(maxi) + "赢了", 0, "结果")
        form0.add_score (maxi)
        Exit Sub
    Else ' maxn > 1
        For i = 0 To gnum
            If pass(i) > maxv Then
                win(i) = False 'no chance to win
            End If
        Next i
    End If
    
    tmp = MsgBox("平", 0, "这我还能怎么办")
    form0.score_show
    
End Sub


Private Sub Label_right_Click() ' 正确
    
    If is_ok = False Then Exit Sub
    '获得当前组
    get_now
    
    right(cur) = right(cur) + 1
    
    state_show
    
    change_cy
    
End Sub

Private Sub Label_pass_Click() '跳过

    If is_ok = False Then Exit Sub
    '获得当前组
    get_now
    
    If pass(cur) >= rule_pass Then
        tmp = MsgBox("没机会了", 64, "FBIWarning") ' stop
        Exit Sub
    End If
    
    pass(cur) = pass(cur) + 1
    state_show
    change_cy
    
End Sub

Private Sub Label_wrong_Click() '错误
    
    If is_ok = False Then Exit Sub
    '获得当前组
    get_now
    
    If wrong(cur) >= rule_wrong Then
        Timer.Enabled = False
        is_ok = False '暂停
        tmp = MsgBox("你错好多啊", 64, "FBIWarning") ' stop
        Exit Sub
    End If
    
    wrong(cur) = wrong(cur) + 1
    state_show
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

Private Sub Optiong_Click(Index As Integer)
    Timer.Enabled = False
    state_show
End Sub

Private Sub Timer_Timer() '计时
    time = time - 1
    If time = 0 Then
        Timer.Enabled = False
        tmp = MsgBox("时间到", 0, "哈哈蠢鸡")
        is_ok = False
    End If
    Label_time.Caption = "倒计时:" + str(time)
End Sub

Private Sub Command_exit_Click()
    judge '判断胜负
    form0.score_show
    Unload Me '关闭
End Sub

Private Sub Command_start_Click() ' 开始计时，出现成语
    
    time = rule_time
    Label_time.Caption = "倒计时:" + str(time)
    is_ok = True
    Timer.Enabled = True
    change_cy
    
End Sub

Private Sub state_show()
     '获得当前组
    get_now
    
    Label_right.Caption = "答对:" + str(right(cur))
    Label_wrong.Caption = "犯规:" + str(wrong(cur))
    Label_pass.Caption = "跳过:" + str(pass(cur))
    
End Sub

Private Sub get_now()
    '获得当前组
    For i = 0 To gnum
        If Optiong(i) = True Then cur = i
    Next i
End Sub

Private Sub Command_change_Click()
    rule_wrong = Val(Textr_wrong.Text)
    rule_pass = Val(Textr_pass.Text)
    rule_time = Val(Textr_time.Text)
    time = rule_time
    Label_time.Caption = "倒计时:" + str(time)
    tmp = MsgBox("修改成功", 0, "恭喜你")
End Sub


Private Sub Form_Resize()
    beautify
End Sub

Private Sub beautify()
    
    Me.Height = Screen.Height * 2 / 3
    Me.Width = Screen.Width * 2 / 3
    Me.Top = Screen.Height / 6
    Me.Left = Screen.Width / 6
    Image1.Left = 0
    Image1.Top = 0
    Image1.Height = Me.Height
    Image1.Width = Me.Width
    
    Label_rule.Caption = "两组选手（交换描述方和猜词方）先后在90秒的时间内进行描述，猜词，猜中成语个数多的一方获胜，若数量相同，则根据犯规或'过'的次数少一方为胜（若还相同，则根据题组难度分高低来判定胜利方）。每队最多有一次犯规和说'过'的机会。（可根据难度适当增加允许犯规或跳过次数）"
    'Label_rule.Caption = Label_rule.Caption + vbCrLf + "先比较答对题数，再比较犯规次数，最后比较跳过次数"
    
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
            obj.Width = Me.Width * 15 / 100
            obj.Height = Me.Height * 10 / 100
            obj.Top = Me.Height * 55 / 100
        End If
    Next
    
    '成语
    Label_cy.Font.Size = Me.Width / 200
    Label_cy.Width = Me.Width * 45 / 100
    Label_cy.Height = Me.Height * 25 / 100
    Label_cy.Top = Me.Height * 10 / 100
    Label_cy.Left = Me.Width * 10 / 100
    '组
    Optiong(0).Left = Me.Width * 5 / 100
    Optiong(1).Left = Me.Width * 25 / 100
    Optiong(2).Left = Me.Width * 45 / 100
    '成绩
    Label_right.Width = Me.Width * 15 / 100
    Label_right.Height = Me.Height * 10 / 100
    Label_right.Top = Me.Height * 70 / 100
    Label_right.Left = Me.Width * 5 / 100
    
    Label_wrong.Width = Me.Width * 15 / 100
    Label_wrong.Height = Me.Height * 10 / 100
    Label_wrong.Top = Me.Height * 70 / 100
    Label_wrong.Left = Me.Width * 25 / 100
    
    Label_pass.Width = Me.Width * 15 / 100
    Label_pass.Height = Me.Height * 10 / 100
    Label_pass.Top = Me.Height * 70 / 100
    Label_pass.Left = Me.Width * 45 / 100
    '计时
    Label_time.Width = Me.Width * 35 / 100
    Label_time.Height = Me.Height * 10 / 100
    Label_time.Top = Me.Height * 40 / 100
    Label_time.Left = Me.Width * 5 / 100
    '开始
    Command_start.Width = Me.Width * 15 / 100
    Command_start.Height = Me.Height * 10 / 100
    Command_start.Top = Me.Height * 40 / 100
    Command_start.Left = Me.Width * 45 / 100
    '规则
    Label_rule.Alignment = 0
    Label_rule.Width = Me.Width * 30 / 100
    Label_rule.Height = Me.Height * 54 / 100
    Label_rule.Top = Me.Height * 3 / 100
    Label_rule.Left = Me.Width * 65 / 100
    
    Labelr_wrong.Width = Me.Width * 8 / 100
    Labelr_wrong.Height = Me.Height * 8 / 100
    Labelr_wrong.Top = Me.Height * 60 / 100
    Labelr_wrong.Left = Me.Width * 65 / 100
    
    Labelr_pass.Width = Me.Width * 8 / 100
    Labelr_pass.Height = Me.Height * 8 / 100
    Labelr_pass.Top = Me.Height * 60 / 100
    Labelr_pass.Left = Me.Width * 76 / 100
    
    Labelr_time.Width = Me.Width * 8 / 100
    Labelr_time.Height = Me.Height * 8 / 100
    Labelr_time.Top = Me.Height * 60 / 100
    Labelr_time.Left = Me.Width * 87 / 100
    
    Textr_wrong.Width = Me.Width * 8 / 100
    Textr_wrong.Height = Me.Height * 8 / 100
    Textr_wrong.Top = Me.Height * 71 / 100
    Textr_wrong.Left = Me.Width * 65 / 100
    
    Textr_pass.Width = Me.Width * 8 / 100
    Textr_pass.Height = Me.Height * 8 / 100
    Textr_pass.Top = Me.Height * 71 / 100
    Textr_pass.Left = Me.Width * 76 / 100
    
    Textr_time.Width = Me.Width * 8 / 100
    Textr_time.Height = Me.Height * 8 / 100
    Textr_time.Top = Me.Height * 71 / 100
    Textr_time.Left = Me.Width * 87 / 100
    '修改规则
    Command_change.Width = Me.Width * 19 / 100
    Command_change.Height = Me.Height * 8 / 100
    Command_change.Top = Me.Height * 82 / 100
    Command_change.Left = Me.Width * 65 / 100
    '退出
    Command_exit.Width = Me.Width * 8 / 100
    Command_exit.Height = Me.Height * 8 / 100
    Command_exit.Top = Me.Height * 82 / 100
    Command_exit.Left = Me.Width * 87 / 100
    
End Sub

