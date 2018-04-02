VERSION 5.00
Begin VB.Form Form5 
   Caption         =   "�����ս"
   ClientHeight    =   4860
   ClientLeft      =   7065
   ClientTop       =   4125
   ClientWidth     =   8910
   LinkTopic       =   "Form5"
   ScaleHeight     =   4860
   ScaleWidth      =   8910
   Begin VB.Timer Timer 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   6720
      Top             =   240
   End
   Begin VB.CommandButton Command_wrong 
      Caption         =   "��"
      Height          =   615
      Left            =   2040
      TabIndex        =   8
      Top             =   3840
      Width           =   855
   End
   Begin VB.CommandButton Command_right 
      Caption         =   "��"
      Height          =   495
      Left            =   480
      TabIndex        =   7
      Top             =   3840
      Width           =   615
   End
   Begin VB.CommandButton Command_change 
      Caption         =   "��"
      Height          =   615
      Left            =   6720
      TabIndex        =   6
      Top             =   1920
      Width           =   1095
   End
   Begin VB.CommandButton Command_answer 
      Caption         =   "������"
      Height          =   615
      Left            =   6600
      TabIndex        =   5
      Top             =   3000
      Width           =   1215
   End
   Begin VB.CommandButton Command_exit 
      Caption         =   "�˳�"
      Height          =   615
      Left            =   7320
      TabIndex        =   3
      Top             =   3960
      Width           =   1095
   End
   Begin VB.OptionButton Option_b 
      Caption         =   "B��"
      Height          =   255
      Left            =   1920
      TabIndex        =   2
      Top             =   2760
      Width           =   1575
   End
   Begin VB.OptionButton Option_a 
      Caption         =   "A��"
      Height          =   255
      Left            =   360
      TabIndex        =   1
      Top             =   2760
      Width           =   1335
   End
   Begin VB.Label Label_time 
      Caption         =   "����ʱ:"
      Height          =   495
      Left            =   6360
      TabIndex        =   10
      Top             =   960
      Width           =   1455
   End
   Begin VB.Label Label_num 
      Caption         =   "��"
      Height          =   495
      Left            =   2640
      TabIndex        =   9
      Top             =   120
      Width           =   2655
   End
   Begin VB.Label Label_answer 
      Caption         =   "��:"
      Height          =   735
      Left            =   4320
      TabIndex        =   4
      Top             =   3000
      Width           =   1695
   End
   Begin VB.Label Label 
      Caption         =   "�ж�"
      Height          =   1815
      Left            =   480
      TabIndex        =   0
      Top             =   720
      Width           =   5295
   End
End
Attribute VB_Name = "Form5"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim sum_answer, num_answer As Integer
Dim str_answer(1000) As String
Dim use_answer As Integer
Dim vis_answer(1000) As Boolean
Dim is_start As Boolean
Dim is_ok, is_finish As Boolean
' state_now ��¼�ش�����Ŀ������
Dim state_a, state_b As Integer ' 0 ��ʾû�ش� 1 ��ʾ��� 2 ��ʾ���
Dim str_tmp As String
Dim now As Integer
Dim time As Integer

Private Sub Form_Load()
    beautify

    is_ok = True
    is_finish = False
    state_a = 0
    state_b = 0
    state_now = 0
    Timer.Interval = 1000
    Timer.Enabled = False
    time = Form0.rule5_time
    
    now = 1
    Label_num.Caption = "��" + Str(now) + "��"
    
    state_change
    ' Ĭ��ΪA��
    Option_a.Value = True
    Option_b.Value = False
    
    reset_answer
    Label.Caption = ""
    Label_answer.Caption = "��:"
    
    'answer Initialization
    Open "resources\part5\answer.txt" For Input As #1
        Dim i As Integer
        i = 0
        Do Until EOF(1)
            Line Input #1, str_answer(i)
            i = i + 1
        Loop
    Close #1
    sum_answer = i - 1
    
End Sub

Private Sub Command_right_Click() ' ��ȷ

    If is_ok = False Or is_finish = True Then Exit Sub

    If Option_a.Value = True Then
        state_a = 2
    Else
        state_b = 2
    End If
    
    state_change
    judge
End Sub

Private Sub Command_wrong_Click() '����
    
    If is_ok = False Or is_finish = True Then Exit Sub

    If Option_a.Value = True Then
        state_a = 1
    Else
        state_b = 1
    End If
    
    state_change
    judge
End Sub

Private Sub Command_change_Click() '����

    If is_finish = True Then
        tmp = MsgBox("�����Ѿ�����", 0, "��������Ե�")
        Exit Sub
    End If

    If use_answer > sum_answer Then
        tmp = MsgBox("��Ŀ������", 0, "FBIWarning")
        Exit Sub
    End If
    
    is_ok = True
    
    num_answer = Rnd() * sum_answer '��һ�ε����
    Do While vis_answer(num_answer) = True
        num_answer = Rnd() * sum_answer
    Loop
    vis_answer(num_answer) = True
    use_answer = use_answer + 1
    Label.Caption = ""
    
    Open "resources\part5\data" + Replace(Str(num_answer), " ", "") + ".txt" For Input As #2
        Do Until EOF(2)
            Line Input #2, str_tmp
            Label.Caption = Label.Caption + vbCrLf + str_tmp
        Loop
    Close #2
    '��մ�
    Label_answer.Caption = "��:"
    
    '��ʼ��ʱ
    time = Form0.rule5_time
    Timer.Enabled = True
    Label_time.Caption = "����ʱ:" + Str(time)
    
End Sub

Private Sub Command_answer_Click()
    Timer.Enabled = False
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

Private Sub judge()
    '��û����
    If state_a = 0 Or state_b = 0 Then Exit Sub
        
    If state_a = state_b Then
        tmp = MsgBox("������һ��", 0, "��")
        '���� + 1
        now = now + 1
        Label_num.Caption = "��" + Str(now) + "��"
        
    ElseIf state_a > state_b Then
        Form0.score_a = Form0.score_a + 1
        Form0.score_show
        tmp = MsgBox(name_a + "��Ӯ��", 0, "����ϲ����")
        is_finish = True
        
    Else
        Form0.score_a = Form0.score_a + 1
        Form0.score_show
        tmp = MsgBox(name_b + "��Ӯ��", 0, "����ϲ����")
        is_finish = True
        
    End If
    '״̬����
    state_a = 0
    state_b = 0
    state_change
    
End Sub

Private Sub state_change()
    '��ͣ
    Timer.Enabled = False
    
    If state_a = 0 Then
        Option_a.Caption = Form0.name_a + "��"
    ElseIf state_a = 1 Then
        Option_a.Caption = Form0.name_a + "���"
    Else
        Option_a.Caption = Form0.name_a + "���"
    End If
    
    If state_b = 0 Then
        Option_b.Caption = Form0.name_b + "��"
    ElseIf state_b = 1 Then
        Option_b.Caption = Form0.name_b + "���"
    Else
        Option_b.Caption = Form0.name_b + "���"
    End If
    
End Sub

Private Sub beautify()
'none
End Sub


Private Sub Timer_Timer()
    time = time - 1
    Label_time.Caption = "����ʱ:" + Str(time)
    If time <= 0 Then
        '���
        If Option_a.Value = True Then
            state_a = 1
        Else
            state_b = 1
        End If
        state_change
        judge
        '����
        Timer.Enabled = False
        is_ok = False
        tmp = MsgBox("ʱ�䵽", 0, "warning")
    End If
End Sub
