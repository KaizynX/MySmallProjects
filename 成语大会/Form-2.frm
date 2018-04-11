VERSION 5.00
Begin VB.Form Form2 
   Caption         =   "双音节同题"
   ClientHeight    =   4695
   ClientLeft      =   7455
   ClientTop       =   3930
   ClientWidth     =   7320
   LinkTopic       =   "Form2"
   ScaleHeight     =   4695
   ScaleWidth      =   7320
   Begin VB.OptionButton Optiong 
      Caption         =   "3"
      Height          =   495
      Index           =   2
      Left            =   3000
      TabIndex        =   9
      Top             =   2640
      Width           =   1095
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "2"
      Height          =   495
      Index           =   1
      Left            =   1800
      TabIndex        =   8
      Top             =   2520
      Width           =   1095
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "1"
      Height          =   495
      Index           =   0
      Left            =   360
      TabIndex        =   7
      Top             =   2520
      Width           =   1095
   End
   Begin VB.CommandButton Command_tip 
      Caption         =   "增加"
      Height          =   615
      Left            =   5880
      TabIndex        =   4
      Top             =   1800
      Width           =   1095
   End
   Begin VB.TextBox Text_tip 
      Height          =   855
      Left            =   3840
      TabIndex        =   3
      Text            =   "增加提示"
      Top             =   1800
      Width           =   1455
   End
   Begin VB.CommandButton Command_exit 
      Caption         =   "退出"
      Height          =   375
      Left            =   6120
      TabIndex        =   2
      Top             =   4200
      Width           =   855
   End
   Begin VB.Label Label_wrong 
      Caption         =   "答错"
      Height          =   375
      Left            =   3000
      TabIndex        =   6
      Top             =   3480
      Width           =   1215
   End
   Begin VB.Label Label_right 
      Caption         =   "答对"
      Height          =   615
      Left            =   840
      TabIndex        =   5
      Top             =   3480
      Width           =   1695
   End
   Begin VB.Label Label_tip 
      Caption         =   "提示:"
      Height          =   1455
      Left            =   3720
      TabIndex        =   1
      Top             =   120
      Width           =   3015
   End
   Begin VB.Label Label_cy 
      Caption         =   "成语"
      Height          =   1455
      Left            =   360
      TabIndex        =   0
      Top             =   360
      Width           =   2535
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim str_cy(1000) As String
Dim sum_cy, num_cy As Integer
Dim is_ok As Boolean
Dim use_cy As Integer
Dim vis_cy(1000) As Boolean
Dim right(3), wrong(3) As Integer '记录答对和犯规
Dim gnum, cur, i As Integer


Private Sub Form_Load()
    beautify
    
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

    Label_tip = "提示:"

    reset_cy
    
    Open "resources\part2\data.txt" For Input As #1
        i = 0
        Do Until EOF(1)
            Line Input #1, str_cy(i)
            i = i + 1
        Loop
    Close #1
    sum_cy = i - 1
End Sub

Private Sub Label_right_Click() ' 正确

    If is_ok = False Then Exit Sub
    '获得当前组
    get_now
    
    right(cur) = right(cur) + 1
    
    state_show
    
    If right(cur) >= form0.rule2_right Then
        is_ok = False
        tmp = MsgBox("Finish", 0, "可恶")
    Else
        change_cy
    End If

End Sub


Private Sub Label_wrong_Click() '错

     If is_ok = False Then Exit Sub
    '获得当前组
    get_now
    
    If wrong(cur) > form0.rule1_wrong Then
        'is_ok = False '暂停
        tmp = MsgBox("该题目难，请换成语", 64, "FBIWarning") ' stop
        Exit Sub
    End If
    
    wrong(cur) = wrong(cur) + 1
    state_show
    change_cy
    
End Sub


Private Sub Label_cy_Click() ' 换成语，同时清空提示
    Label_tip = "提示:"
    change_cy
    '犯规清0
    For i = 0 To gnum
        wrong(i) = 0
    Next i
    
    state_show
    
End Sub
Private Sub change_cy() ' 换成语

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
    Label_tip.Caption = "提示:"
    
End Sub

Private Sub reset_cy() '重置成语vis
    Dim i As Integer
    For i = 0 To 999
        vis_cy(i) = False
    Next i
    use_cy = 0
    is_ok = True
End Sub

Private Sub judge()
    
End Sub

 '更改小组
Private Sub Optiong_Click(Index As Integer)
    state_show
End Sub

Private Sub Command_exit_Click()
    judge
    form0.score_show
    Unload Me
End Sub

Private Sub Command_tip_Click()
    Label_tip.Caption = Label_tip.Caption + " " + Text_tip.Text
End Sub

Private Sub state_show()
    '获得当前组
    get_now
    
    Label_right.Caption = "答对:" + Str(right(cur))
    Label_wrong.Caption = "答错:" + Str(wrong(cur))

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

