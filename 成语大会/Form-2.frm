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
   Begin VB.OptionButton Option_b 
      Caption         =   "B��"
      Height          =   255
      Left            =   2400
      TabIndex        =   6
      Top             =   2760
      Width           =   855
   End
   Begin VB.OptionButton Option_a 
      Caption         =   "A��"
      Height          =   255
      Left            =   840
      TabIndex        =   5
      Top             =   2640
      Width           =   975
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
      TabIndex        =   8
      Top             =   3480
      Width           =   1215
   End
   Begin VB.Label Label_right 
      Caption         =   "���"
      Height          =   615
      Left            =   840
      TabIndex        =   7
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
Dim right_a, wrong_a, right_b, wrong_b As Integer '��¼��Ժͷ���


Private Sub Form_Load()
    beautify
    
    right_a = 0
    right_b = 0
    wrong_a = 0
    wrong_b = 0
    Option_a.Caption = Form0.name_a + "��"
    Option_b.Caption = Form0.name_b + "��"
    ' Ĭ��ΪA��
    Option_a.Value = True
    Option_b.Value = False

    Label_tip = "��ʾ:"

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

Private Sub Label_right_Click() ' ��ȷ

    If Option_a.Value = True Then
    
        If is_ok Then right_a = right_a + 1
        Label_right.Caption = "���:" + Str(right_a)
        
    Else
        If is_ok Then right_b = right_b + 1
        Label_right.Caption = "���:" + Str(right_b)

    End If
    
    change_cy
End Sub


Private Sub Label_wrong_Click() '��
    If Option_a.Value = True Then
        If is_ok Then wrong_a = wrong_a + 1
        Label_wrong.Caption = "����:" + Str(wrong_a)
        
        If wrong_a > Form0.rule2_wrong Then
            tmp = MsgBox("����Ŀ�ѣ��뻻����", 0, "FBIWarning")
        End If
    Else
        If is_ok Then wrong_b = wrong_b + 1
        Label_wrong.Caption = "����:" + Str(wrong_b)
        
        If wrong_b > Form0.rule2_wrong Then
            mp = MsgBox("����Ŀ�ѣ��뻻����", 0, "FBIWarning")
        End If
    End If
    
End Sub


Private Sub Label_cy_Click() ' �����ͬʱ�����ʾ
    Label_tip = "��ʾ:"
    change_cy
    '������0
    wrong_a = 0
    wrong_b = 0
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
        
    If right_a > right_b Then ' A win
        Form0.score_a = Form0.score_a + 1
    ElseIf right_a > right_b Then ' B win
        Form0.score_b = Form0.score_b + 1
    Else ' either
        Form0.score_a = Form0.score_a + 1
        Form0.score_b = Form0.score_b + 1
    End If
    
End Sub

Private Sub Option_a_Click() '����С��
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
        Label_right.Caption = "���:" + Str(right_b)
        Label_wrong.Caption = "����:" + Str(wrong_b)
    Else
        Label_right.Caption = "���:" + Str(right_a)
        Label_wrong.Caption = "����:" + Str(wrong_a)
    End If
End Sub

Private Sub beautify()
'none
End Sub

