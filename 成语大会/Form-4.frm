VERSION 5.00
Begin VB.Form Form4 
   Caption         =   "限时竞猜"
   ClientHeight    =   6375
   ClientLeft      =   6480
   ClientTop       =   3750
   ClientWidth     =   8850
   LinkTopic       =   "Form4"
   ScaleHeight     =   6375
   ScaleWidth      =   8850
   Begin VB.OptionButton Optiong 
      Height          =   255
      Index           =   2
      Left            =   3360
      TabIndex        =   10
      Top             =   4800
      Width           =   975
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "2"
      Height          =   255
      Index           =   1
      Left            =   1920
      TabIndex        =   9
      Top             =   4920
      Width           =   975
   End
   Begin VB.CommandButton Command_answer 
      Caption         =   "公布答案"
      Height          =   615
      Left            =   6600
      TabIndex        =   8
      Top             =   3960
      Width           =   1215
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "A组"
      Height          =   255
      Index           =   0
      Left            =   360
      TabIndex        =   4
      Top             =   4800
      Width           =   975
   End
   Begin VB.CommandButton Command_run 
      Caption         =   "控制"
      Height          =   735
      Left            =   2640
      TabIndex        =   3
      Top             =   3600
      Width           =   1215
   End
   Begin VB.CommandButton Command_change 
      Caption         =   "换"
      Height          =   615
      Left            =   1200
      TabIndex        =   2
      Top             =   3600
      Width           =   1095
   End
   Begin VB.CommandButton Command_exit 
      Caption         =   "退出"
      Height          =   615
      Left            =   7080
      TabIndex        =   1
      Top             =   5640
      Width           =   1095
   End
   Begin VB.Timer Timer 
      Interval        =   500
      Left            =   360
      Top             =   3720
   End
   Begin VB.Label Label_answer 
      Caption         =   "答案:"
      Height          =   735
      Left            =   4320
      TabIndex        =   7
      Top             =   3720
      Width           =   1695
   End
   Begin VB.Label Label_wrong 
      Caption         =   "犯规"
      Height          =   375
      Left            =   2640
      TabIndex        =   6
      Top             =   5520
      Width           =   1215
   End
   Begin VB.Label Label_right 
      Caption         =   "答对"
      Height          =   615
      Left            =   240
      TabIndex        =   5
      Top             =   5520
      Width           =   1695
   End
   Begin VB.Label Label 
      Caption         =   "判断"
      Height          =   3135
      Left            =   600
      TabIndex        =   0
      Top             =   360
      Width           =   6855
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

Private Sub Form_Load()
    beautify

    is_ok = True
    gnum = form0.gnum
    
    For i = 0 To gnum
        right(i) = 0
        wrong(i) = 0
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
    
    Timer.Enabled = False
    Timer.Interval = form0.rule4_v
    num_answer = 0
    reset_answer
    num_line = 0
    num_len = 0
    is_start = False
    Command_run.Caption = "开始"
    Label.Caption = ""
    Label_answer.Caption = "答案:"
    
    'answer Initialization
    Open "resources\part4\answer.txt" For Input As #1
        i = 0
        Do Until EOF(1)
            Line Input #1, str_answer(i)
            i = i + 1
        Loop
    Close #1
    sum_answer = i - 1
    
End Sub

Private Sub Label_right_Click() ' 正确

    If is_ok = False Then Exit Sub
    '获得当前组
    get_now
    
    right(cur) = right(cur) + 1
    
    state_show
    
    If right(cur) >= form0.rule1_right Then
        is_ok = False
        Timer.Enabled = False ' stop
        tmp = MsgBox("Finish", 0, "可恶")
    End If
    
    judge
    
End Sub


Private Sub Label_wrong_Click() '错误
    
    If is_ok = False Then Exit Sub
    '获得当前组
    get_now
    wrong(cur) = wrong(cur) + 1
    For i = 0 To gnum
        If i = cur Then 'none
        Else: right(i) = right(i) + 1
        End If
    Next i
    state_show

'    If Option_a.Value = True Then
'
'        wrong_a = wrong_a + 1
'        Label_wrong.Caption = "犯规:" + Str(wrong_a)
'
'        If wrong_a > form0.rule4_wrong Then
'            right_b = right_b + 1
'            tmp = MsgBox("答错，对方加分", 0, "FBIWarning")
'        End If
'    Else
'        wrong_b = wrong_b + 1
'        Label_wrong.Caption = "犯规:" + Str(wrong_b)
'
'        If wrong_b > form0.rule4_wrong Then
'            right_a = right_a + 1
'            tmp = MsgBox("答错，对方加分", 0, "FBIWarning")
'        End If
'    End If
    
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

Private Sub Command_change_Click()

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
    
    Open "resources\part4\data" + Replace(Str(num_answer), " ", "") + ".txt" For Input As #2
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
    Label_answer.Caption = "答案:"
    
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
        num_len = num_len + 1
    Else
        '读取下一行
        Label.Caption = Label.Caption + vbCrLf
        num_line = num_line + 1
        num_len = 0
    End If
    
End Sub

Private Sub Command_answer_Click()
    Label_answer.Caption = "答案:" + str_answer(num_answer)
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
        If right(i) >= form0.rule4_right Then
            winner = i
            Exit For
        End If
    Next i
    
    If winner = -1 Then Exit Sub
    
    tmp = MsgBox(form0.qname(winner) + "组赢了", 0, "结果")
    form0.add_score (winner)
    form0.score_show
    is_ok = False
    
End Sub

Private Sub state_show()

    '获得当前组
    get_now
    
    Label_right.Caption = "答对:" + Str(right(cur))
    Label_wrong.Caption = "犯规:" + Str(wrong(cur))
    
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

