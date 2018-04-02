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
   Begin VB.OptionButton Option_b 
      Caption         =   "B组"
      Height          =   255
      Left            =   2400
      TabIndex        =   6
      Top             =   2760
      Width           =   855
   End
   Begin VB.OptionButton Option_a 
      Caption         =   "A组"
      Height          =   255
      Left            =   840
      TabIndex        =   5
      Top             =   2640
      Width           =   975
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
      TabIndex        =   8
      Top             =   3480
      Width           =   1215
   End
   Begin VB.Label Label_right 
      Caption         =   "答对"
      Height          =   615
      Left            =   840
      TabIndex        =   7
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
Dim right_a, wrong_a, right_b, wrong_b As Integer '记录答对和犯规


Private Sub Form_Load()
    beautify
    
    right_a = 0
    right_b = 0
    wrong_a = 0
    wrong_b = 0
    Option_a.Caption = Form0.name_a + "组"
    Option_b.Caption = Form0.name_b + "组"
    ' 默认为A组
    Option_a.Value = True
    Option_b.Value = False

    Label_tip = "提示:"

    reset_cy
    
    Open "resources\part2\data.txt" For Input As #1
        Dim i As Integer
        i = 0
        Do Until EOF(1)
            Line Input #1, str_cy(i)
            i = i + 1
        Loop
    Close #1
    sum_cy = i - 1
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


Private Sub Label_wrong_Click() '错
    If Option_a.Value = True Then
        If is_ok Then wrong_a = wrong_a + 1
        Label_wrong.Caption = "错误:" + Str(wrong_a)
        
        If wrong_a > Form0.rule2_wrong Then
            tmp = MsgBox("该题目难，请换成语", 0, "FBIWarning")
        End If
    Else
        If is_ok Then wrong_b = wrong_b + 1
        Label_wrong.Caption = "错误:" + Str(wrong_b)
        
        If wrong_b > Form0.rule2_wrong Then
            mp = MsgBox("该题目难，请换成语", 0, "FBIWarning")
        End If
    End If
    
End Sub


Private Sub Label_cy_Click() ' 换成语，同时清空提示
    Label_tip = "提示:"
    change_cy
    '犯规清0
    wrong_a = 0
    wrong_b = 0
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
        
    If right_a > right_b Then ' A win
        Form0.score_a = Form0.score_a + 1
    ElseIf right_a > right_b Then ' B win
        Form0.score_b = Form0.score_b + 1
    Else ' either
        Form0.score_a = Form0.score_a + 1
        Form0.score_b = Form0.score_b + 1
    End If
    
End Sub

Private Sub Option_a_Click() '更改小组
    state_show
End Sub

Private Sub Option_b_Click()
    state_show
End Sub

Private Sub Command_exit_Click()
    judge
    Form0.score_show
    Unload Me
End Sub

Private Sub Command_tip_Click()
    Label_tip.Caption = Label_tip.Caption + " " + Text_tip.Text
End Sub

Private Sub state_show()
    If Option_b.Value = True Then
        Label_right.Caption = "答对:" + Str(right_b)
        Label_wrong.Caption = "犯规:" + Str(wrong_b)
    Else
        Label_right.Caption = "答对:" + Str(right_a)
        Label_wrong.Caption = "犯规:" + Str(wrong_a)
    End If
End Sub

Private Sub beautify()
'none
End Sub

