VERSION 5.00
Begin VB.Form Form2 
   Caption         =   "˫����ͬ��"
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
      Caption         =   "����"
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
      Text            =   "������ʾ"
      Top             =   1800
      Width           =   1455
   End
   Begin VB.CommandButton Command_exit 
      Caption         =   "�˳�"
      Height          =   375
      Left            =   6120
      TabIndex        =   2
      Top             =   4200
      Width           =   855
   End
   Begin VB.Label Label_wrong 
      Caption         =   "���"
      Height          =   375
      Left            =   3000
      TabIndex        =   6
      Top             =   3480
      Width           =   1215
   End
   Begin VB.Label Label_right 
      Caption         =   "���"
      Height          =   615
      Left            =   840
      TabIndex        =   5
      Top             =   3480
      Width           =   1695
   End
   Begin VB.Label Label_tip 
      Caption         =   "��ʾ:"
      Height          =   1455
      Left            =   3720
      TabIndex        =   1
      Top             =   120
      Width           =   3015
   End
   Begin VB.Label Label_cy 
      Caption         =   "����"
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
Dim right(3), wrong(3) As Integer '��¼��Ժͷ���
Dim gnum, cur, i As Integer


Private Sub Form_Load()
    beautify
    
    gnum = form0.gnum
    
    For i = 0 To gnum
        right(i) = 0
        wrong(i) = 0
        Optiong(i).Caption = form0.qname(i) + "��"
    Next i
    
    ' Ĭ��ΪA��
    Optiong(0).Value = True
    Optiong(1).Value = False
    If form0.gnum < 2 Then
        Optiong(2).Caption = ""
        Optiong(2).Enabled = False '����
    Else
        Optiong(2).Value = False
    End If

    Label_tip = "��ʾ:"

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

Private Sub Label_right_Click() ' ��ȷ

    If is_ok = False Then Exit Sub
    '��õ�ǰ��
    get_now
    
    right(cur) = right(cur) + 1
    
    state_show
    
    If right(cur) >= form0.rule2_right Then
        is_ok = False
        tmp = MsgBox("Finish", 0, "�ɶ�")
    Else
        change_cy
    End If

End Sub


Private Sub Label_wrong_Click() '��

     If is_ok = False Then Exit Sub
    '��õ�ǰ��
    get_now
    
    If wrong(cur) > form0.rule1_wrong Then
        'is_ok = False '��ͣ
        tmp = MsgBox("����Ŀ�ѣ��뻻����", 64, "FBIWarning") ' stop
        Exit Sub
    End If
    
    wrong(cur) = wrong(cur) + 1
    state_show
    change_cy
    
End Sub


Private Sub Label_cy_Click() ' �����ͬʱ�����ʾ
    Label_tip = "��ʾ:"
    change_cy
    '������0
    For i = 0 To gnum
        wrong(i) = 0
    Next i
    
    state_show
    
End Sub
Private Sub change_cy() ' ������

    If use_cy > sum_cy Then
        is_ok = False
        tmp = MsgBox("����������", 0, "FBIWarning")
        Exit Sub
    End If
    
    num_cy = Rnd() * sum_cy '��һ�ε����
    Do While vis_cy(num_cy) = True
        num_cy = Rnd() * sum_cy
    Loop
    
    vis_cy(num_cy) = True
    use_cy = use_cy + 1
    Label_cy.Caption = str_cy(num_cy)
    Label_tip.Caption = "��ʾ:"
    
End Sub

Private Sub reset_cy() '���ó���vis
    Dim i As Integer
    For i = 0 To 999
        vis_cy(i) = False
    Next i
    use_cy = 0
    is_ok = True
End Sub

Private Sub judge()
    
End Sub

 '����С��
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
    '��õ�ǰ��
    get_now
    
    Label_right.Caption = "���:" + Str(right(cur))
    Label_wrong.Caption = "���:" + Str(wrong(cur))

End Sub

Private Sub get_now()
    '��õ�ǰ��
    For i = 0 To gnum
        If Optiong(i) = True Then cur = i
    Next i
End Sub

Private Sub beautify()
'none
End Sub

