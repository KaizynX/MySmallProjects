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
   Begin VB.OptionButton Optiong 
      Height          =   255
      Index           =   2
      Left            =   3240
      TabIndex        =   10
      Top             =   2280
      Width           =   975
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "A组"
      Height          =   255
      Index           =   1
      Left            =   1800
      TabIndex        =   9
      Top             =   2280
      Width           =   975
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "A组"
      Height          =   255
      Index           =   0
      Left            =   240
      TabIndex        =   7
      Top             =   2160
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
      Left            =   1560
      Top             =   3600
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
      Left            =   6600
      TabIndex        =   8
      Top             =   3240
      Width           =   855
   End
   Begin VB.Label Label_wrong 
      Caption         =   "犯规"
      Height          =   375
      Left            =   4800
      TabIndex        =   6
      Top             =   3000
      Width           =   1215
   End
   Begin VB.Label Label_right 
      Caption         =   "答对"
      Height          =   615
      Left            =   2760
      TabIndex        =   5
      Top             =   3120
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
      Left            =   600
      TabIndex        =   3
      Top             =   3120
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
Dim right(3), wrong(3), time(3), pass(3) As Integer '记录答对和犯规
Dim sum_theme, num_theme As Integer ' 记录主题
Dim str_theme(1000) As String ' 主题
Dim sum_cy, num_cy As Integer '成语
Dim str_cy(1000) As String
Dim use_cy, use_theme As Integer
Dim vis_cy(1000), vis_theme(1000) As Boolean  '判断重复
Dim is_rest As Boolean '防止用完
Dim gnum As Integer
Dim cur, time_now, i As Integer
Dim win(3) As Integer

Private Sub Form_Load()
    beautify

    is_ok = True

    time_now = 0
    use_cy = 0
    use_theme = 0
    
    gnum = form0.gnum
    
    For i = 0 To gnum
        time(i) = 0
        right(i) = 0
        wrong(i) = 0
        pass(i) = 0
        Optiong(i).Caption = form0.qname(i) + "组"
    Next i
    
    ' 默认为A组
    Optiong(0).Value = True
    Optiong(1).Value = False
    If form0.gnum < 3 Then
        Optiong(2).Enabled = False '禁用
    Else
        Optiong(2).Value = False
    End If
    
    Label_time.Caption = "用时:" + Str(time_now)
    
    '主题init
    Open "resources\part1\theme.txt" For Input As #1
        i = 0
        Do Until EOF(1)
            Line Input #1, str_theme(i)
            i = i + 1
        Loop
    Close #1
    sum_theme = i - 1
    
End Sub

Private Sub judge() ' 判断胜负

    Dim maxv, maxn, maxi As Integer '记录最高分的分数和个数序号

    '先累计初始分
    For i = 0 To 2
        win(i) = 10
    Next i
    
    '答对
    maxv = 0
    maxi = -1
    maxn = 0
    For i = 0 To gnum
        If right(i) > maxv Then
            maxv = win(i)
            maxn = 1
            maxi = i
        ElseIf maxv = win(i) Then
            maxn = maxn + 1
        End If
    Next i
    
    
End Sub

Private Function winner() As Integer

    Dim maxv, maxn, maxi As Integer  '记录最高分的分数和个数
    maxv = 0
    maxn = 0
    For i = 0 To gnum
        If win(i) > maxv Then
            maxv = win(i)
            maxn = 1
            maxi = i
        ElseIf maxv = win(i) Then
            maxn = maxn + 1
        End If
    Next i
    '如果只有一个，则决出胜负
    '否则没有
    If maxn > 1 Then
        winner = -1
    Else
        winner = maxi
    End If
    
End Function


Private Sub Label_right_Click() ' 正确

    If is_rest = False Then Exit Sub
    '获得当前组
    get_now
    
    right(cur) = right(cur) + 1
    
    state_show
    
    If right(cur) >= form0.rule1_right Then
        Timer.Enabled = False ' stop
        tmp = MsgBox("Finish", 0, "可恶")
    Else
        change_cy
    End If

End Sub

Private Sub Label_pass_Click() '跳过

    If is_rest = False Then Exit Sub
    '获得当前组
    get_now
    
    If pass(cur) > form0.rule1_pass Then
        tmp = MsgBox("没机会了", 64, "FBIWarning") ' stop
        Exit Sub
    End If
    
    pass(cur) = pass(cur) + 1
    state_show
    change_cy
    
End Sub

Private Sub Label_wrong_Click() '错误
    
    If is_rest = False Then Exit Sub
    '获得当前组
    get_now
    
    If wrong(cur) > form0.rule1_wrong Then
        Timer.Enabled = False
        is_rest = False '暂停
        tmp = MsgBox("你错好多啊", 64, "FBIWarning") ' stop
        Exit Sub
    End If
    
    wrong(cur) = wrong(cur) + 1
    state_show
    change_cy
    
End Sub

Private Sub Label_theme_Click() '切换主题

    '？？？
    Timer.Enabled = False
    
    If use_theme > sum_theme Then
        is_rest = False
        tmp = MsgBox("主题用完了", 64, "FBIWarning")
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
    If is_rest = False Then Exit Sub

    If use_cy > sum_cy Then
        Timer.Enabled = False
        is_rest = False
        tmp = MsgBox("成语用完了", 64, "FBIWarning")
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
    is_rest = True
End Sub

Private Sub Optiong_Click(Index As Integer)
    state_show
End Sub

Private Sub Timer_Timer() '计时
    time_now = time_now + 1
    
    get_now
    
    time(cur) = time_now
    
    Label_time.Caption = "用时:" + Str(time_now)
End Sub

Private Sub Command_exit_Click()
    judge '判断胜负
    form0.score_show
    Unload Me '关闭
End Sub

Private Sub Command_start_Click() ' 开始计时，出现成语
    time_npw = 0
    Timer.Enabled = True
    change_cy
End Sub

Private Sub state_show()

    '获得当前组
    get_now
    
    Label_right.Caption = "答对:" + Str(right(cur))
    Label_wrong.Caption = "犯规:" + Str(wrong(cur))
    Label_time.Caption = "用时:" + Str(time(cur))
    Label_pass.Caption = "跳过:" + Str(pass(cur))
    
End Sub

Private Sub get_now()
    '获得当前组
    For i = 0 To gnum
        If Optiong(i) = True Then cur = i
    Next i
End Sub

Private Sub beautify()
'none
End Sub

