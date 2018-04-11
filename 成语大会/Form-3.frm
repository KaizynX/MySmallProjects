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
   Begin VB.OptionButton Optiong 
      Caption         =   "3"
      Height          =   255
      Index           =   2
      Left            =   3840
      TabIndex        =   9
      Top             =   3480
      Width           =   975
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "2"
      Height          =   255
      Index           =   1
      Left            =   2520
      TabIndex        =   8
      Top             =   3360
      Width           =   975
   End
   Begin VB.CommandButton Command_exit 
      Caption         =   "退出"
      Height          =   615
      Left            =   5760
      TabIndex        =   7
      Top             =   5640
      Width           =   1095
   End
   Begin VB.CommandButton Command_start 
      Caption         =   "开始"
      Height          =   615
      Left            =   3840
      TabIndex        =   6
      Top             =   5640
      Width           =   975
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "A组"
      Height          =   255
      Index           =   0
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
      TabIndex        =   5
      Top             =   4560
      Width           =   855
   End
   Begin VB.Label Label_wrong 
      Caption         =   "犯规"
      Height          =   375
      Left            =   3480
      TabIndex        =   4
      Top             =   4440
      Width           =   1215
   End
   Begin VB.Label Label_right 
      Caption         =   "答对"
      Height          =   615
      Left            =   1080
      TabIndex        =   3
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
         Name            =   "宋体"
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
Dim right(3), wrong(3), pass(3) As Integer '记录答对和犯规
Dim sum_cy, num_cy As Integer '成语
Dim str_cy(1000) As String
Dim use_cy As Integer
Dim vis_cy(1000) As Boolean  '判断重复
Dim is_ok As Boolean '防止用完
Dim cur, gnum, i As Integer


Private Sub Form_Load()
    beautify
    
    is_ok = True
    
    time = form0.rule3_time
    
    gnum = form0.gnum
    
    For i = 0 To gnum
        right(i) = 0
        wrong(i) = 0
        pass(i) = 0
        Optiong(i).Caption = form0.qname(i) + "组"
    Next i
    
    ' 默认为A组
    Optiong(0).Value = True
    Optiong(1).Value = False
    If form0.gnum < 2 Then
        Optiong(2).Caption = ""
        Optiong(2).Enabled = False '禁用
    Else
        Optiong(2).Value = False
    End If
    
    Label_time.Caption = "倒计时:" + Str(time)
    '链接成语库
    Open "resources\part3\data.txt" For Input As #1
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
        form0.score_a = form0.score_a + 1
    ElseIf right_a > right_b Then ' B win
        form0.score_b = form0.score_b + 1
    Else ' either
        form0.score_a = form0.score_a + 1
        form0.score_b = form0.score_b + 1
    End If
    
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
    
    If pass(cur) > form0.rule3_pass Then
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
    
    If wrong(cur) > form0.rule3_wrong Then
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
    Label_time.Caption = "倒计时:" + Str(time)
End Sub

Private Sub Command_exit_Click()
    judge '判断胜负
    form0.score_show
    Unload Me '关闭
End Sub

Private Sub Command_start_Click() ' 开始计时，出现成语
    
    time = form0.rule3_time
    Label_time.Caption = "倒计时:" + Str(time)
    is_ok = True
    Timer.Enabled = True
    change_cy
    
End Sub

Private Sub state_show()
     '获得当前组
    get_now
    
    Label_right.Caption = "答对:" + Str(right(cur))
    Label_wrong.Caption = "犯规:" + Str(wrong(cur))
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

