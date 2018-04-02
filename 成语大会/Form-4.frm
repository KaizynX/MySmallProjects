VERSION 5.00
Begin VB.Form Form4 
   Caption         =   "��ʱ����"
   ClientHeight    =   6375
   ClientLeft      =   6480
   ClientTop       =   3750
   ClientWidth     =   8850
   LinkTopic       =   "Form4"
   ScaleHeight     =   6375
   ScaleWidth      =   8850
   Begin VB.CommandButton Command_answer 
      Caption         =   "������"
      Height          =   615
      Left            =   6600
      TabIndex        =   9
      Top             =   3960
      Width           =   1215
   End
   Begin VB.OptionButton Option_b 
      Caption         =   "B��"
      Height          =   255
      Left            =   1920
      TabIndex        =   5
      Top             =   4800
      Width           =   855
   End
   Begin VB.OptionButton Option_a 
      Caption         =   "A��"
      Height          =   255
      Left            =   360
      TabIndex        =   4
      Top             =   4800
      Width           =   975
   End
   Begin VB.CommandButton Command_run 
      Caption         =   "����"
      Height          =   735
      Left            =   2640
      TabIndex        =   3
      Top             =   3600
      Width           =   1215
   End
   Begin VB.CommandButton Command_change 
      Caption         =   "��"
      Height          =   615
      Left            =   1200
      TabIndex        =   2
      Top             =   3600
      Width           =   1095
   End
   Begin VB.CommandButton Command_exit 
      Caption         =   "�˳�"
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
      Caption         =   "��:"
      Height          =   735
      Left            =   4320
      TabIndex        =   8
      Top             =   3720
      Width           =   1695
   End
   Begin VB.Label Label_wrong 
      Caption         =   "����"
      Height          =   375
      Left            =   2640
      TabIndex        =   7
      Top             =   5520
      Width           =   1215
   End
   Begin VB.Label Label_right 
      Caption         =   "���"
      Height          =   615
      Left            =   240
      TabIndex        =   6
      Top             =   5520
      Width           =   1695
   End
   Begin VB.Label Label 
      Caption         =   "�ж�"
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
Dim right_a, wrong_a, right_b, wrong_b As Integer '��¼��Ժͷ���


Private Sub Form_Load()
    beautify

    is_ok = True
    right_a = 0
    right_b = 0
    wrong_a = 0
    wrong_b = 0
    Option_a.Caption = Form0.name_a + "��"
    Option_b.Caption = Form0.name_b + "��"
    ' Ĭ��ΪA��
    Option_a.Value = True
    Option_b.Value = False
    
    Timer.Enabled = False
    Timer.Interval = Form0.rule4_v
    num_answer = 0
    reset_answer
    num_line = 0
    num_len = 0
    is_start = False
    Command_run.Caption = "��ʼ"
    Label.Caption = ""
    Label_answer.Caption = "��:"
    
    'answer Initialization
    Open "resources\part4\answer.txt" For Input As #1
        Dim i As Integer
        i = 0
        Do Until EOF(1)
            Line Input #1, str_answer(i)
            i = i + 1
        Loop
    Close #1
    sum_answer = i - 1
    
End Sub

Private Sub Label_right_Click() ' ��ȷ

    If is_ok = False Then Exit Sub

    If Option_a.Value = True Then
    
        right_a = right_a + 1
        Label_right.Caption = "���:" + Str(right_a)
        
    Else
        right_b = right_b + 1
        Label_right.Caption = "���:" + Str(right_b)

    End If
    
    judge
    
End Sub


Private Sub Label_wrong_Click() '����
    
    If is_ok = False Then Exit Sub

    If Option_a.Value = True Then
    
        wrong_a = wrong_a + 1
        Label_wrong.Caption = "����:" + Str(wrong_a)
        
        If wrong_a > Form0.rule4_wrong Then
            right_b = right_b + 1
            tmp = MsgBox("����Է��ӷ�", 0, "FBIWarning")
        End If
    Else
        wrong_b = wrong_b + 1
        Label_wrong.Caption = "����:" + Str(wrong_b)
        
        If wrong_b > Form0.rule4_wrong Then
            right_a = right_a + 1
            tmp = MsgBox("����Է��ӷ�", 0, "FBIWarning")
        End If
    End If
    
    judge
End Sub


Private Sub Command_run_Click()

    If is_start Then 'ԭ����ʼ,������ͣ
        Timer.Enabled = False
        is_start = False
        Command_run.Caption = "��ʼ"
    Else
        Timer.Enabled = True
        is_start = True
        Command_run.Caption = "��ͣ"
    End If
End Sub

Private Sub Command_change_Click()

    If use_answer > sum_answer Then
        tmp = MsgBox("����������", 0, "FBIWarning")
        Exit Sub
    End If
    
    num_answer = Rnd() * sum_answer '��һ�ε����
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
    '����Ҫ��ͣ
    Timer.Enabled = False
    is_start = False
    Command_run.Caption = "��ʼ"
    '��մ�
    Label_answer.Caption = "��:"
    
End Sub

Private Sub Timer_Timer()
    '������
    If num_line > sum_line Then
        Timer.Enabled = False
        Exit Sub
    End If
    
    sum_len = Len(str_words(num_line))
    If num_len < sum_len Then
        Label.Caption = Label.Caption + Mid(str_words(num_line), num_len + 1, 1)
        num_len = num_len + 1
    Else
        '��ȡ��һ��
        Label.Caption = Label.Caption + vbCrLf
        num_line = num_line + 1
        num_len = 0
    End If
    
End Sub

Private Sub Command_answer_Click()
    Label_answer.Caption = "��:" + str_answer(num_answer)
End Sub

Private Sub Command_exit_Click()
    Form0.score_show
    Unload Me
End Sub

Private Sub reset_answer() '����vis
    Dim i As Integer
    For i = 0 To 999
        vis_answer(i) = False
    Next i
    use_answer = 0
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

Private Sub Option_a_Click() '����С��
    state_show
End Sub

Private Sub Option_b_Click()
    state_show
End Sub

Private Sub judge()
        
    If right_a >= Form0.rule4_right Then
        is_ok = False
        Form0.score_a = Form0.score_a + 1
        tmp = MsgBox(Form0.name_a + "��Ӯ��", 0, "�þֽ���")
    ElseIf right_b >= Form0.rule4_right Then
        Form0.score_b = Form0.score_b + 1
        tmp = MsgBox(Form0.name_b + "��Ӯ��", 0, "�þֽ���")
        is_ok = False
    End If
    Form0.score_show
End Sub

Private Sub beautify()
'none
End Sub

