VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Ŀ���ʱ"
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
      Caption         =   "A��"
      Height          =   255
      Index           =   1
      Left            =   1800
      TabIndex        =   9
      Top             =   2280
      Width           =   975
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "A��"
      Height          =   255
      Index           =   0
      Left            =   240
      TabIndex        =   7
      Top             =   2160
      Width           =   975
   End
   Begin VB.CommandButton Command_start 
      Caption         =   "��ʼ"
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
      Caption         =   "�˳�"
      Height          =   615
      Left            =   5880
      TabIndex        =   0
      Top             =   3840
      Width           =   1095
   End
   Begin VB.Label Label_pass 
      Caption         =   "����"
      Height          =   495
      Left            =   6600
      TabIndex        =   8
      Top             =   3240
      Width           =   855
   End
   Begin VB.Label Label_wrong 
      Caption         =   "����"
      Height          =   375
      Left            =   4800
      TabIndex        =   6
      Top             =   3000
      Width           =   1215
   End
   Begin VB.Label Label_right 
      Caption         =   "���"
      Height          =   615
      Left            =   2760
      TabIndex        =   5
      Top             =   3120
      Width           =   1695
   End
   Begin VB.Label Label_time 
      Caption         =   "��ʱ"
      BeginProperty Font 
         Name            =   "����"
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
      Caption         =   "����"
      BeginProperty Font 
         Name            =   "����"
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
      Caption         =   "��ѡ����"
      BeginProperty Font 
         Name            =   "����"
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
Dim right(3), wrong(3), time(3), pass(3) As Integer '��¼��Ժͷ���
Dim sum_theme, num_theme As Integer ' ��¼����
Dim str_theme(1000) As String ' ����
Dim sum_cy, num_cy As Integer '����
Dim str_cy(1000) As String
Dim use_cy, use_theme As Integer
Dim vis_cy(1000), vis_theme(1000) As Boolean  '�ж��ظ�
Dim is_rest As Boolean '��ֹ����
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
        Optiong(i).Caption = form0.qname(i) + "��"
    Next i
    
    ' Ĭ��ΪA��
    Optiong(0).Value = True
    Optiong(1).Value = False
    If form0.gnum < 3 Then
        Optiong(2).Enabled = False '����
    Else
        Optiong(2).Value = False
    End If
    
    Label_time.Caption = "��ʱ:" + Str(time_now)
    
    '����init
    Open "resources\part1\theme.txt" For Input As #1
        i = 0
        Do Until EOF(1)
            Line Input #1, str_theme(i)
            i = i + 1
        Loop
    Close #1
    sum_theme = i - 1
    
End Sub

Private Sub judge() ' �ж�ʤ��

    Dim maxv, maxn, maxi As Integer '��¼��߷ֵķ����͸������

    '���ۼƳ�ʼ��
    For i = 0 To 2
        win(i) = 10
    Next i
    
    '���
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

    Dim maxv, maxn, maxi As Integer  '��¼��߷ֵķ����͸���
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
    '���ֻ��һ���������ʤ��
    '����û��
    If maxn > 1 Then
        winner = -1
    Else
        winner = maxi
    End If
    
End Function


Private Sub Label_right_Click() ' ��ȷ

    If is_rest = False Then Exit Sub
    '��õ�ǰ��
    get_now
    
    right(cur) = right(cur) + 1
    
    state_show
    
    If right(cur) >= form0.rule1_right Then
        Timer.Enabled = False ' stop
        tmp = MsgBox("Finish", 0, "�ɶ�")
    Else
        change_cy
    End If

End Sub

Private Sub Label_pass_Click() '����

    If is_rest = False Then Exit Sub
    '��õ�ǰ��
    get_now
    
    If pass(cur) > form0.rule1_pass Then
        tmp = MsgBox("û������", 64, "FBIWarning") ' stop
        Exit Sub
    End If
    
    pass(cur) = pass(cur) + 1
    state_show
    change_cy
    
End Sub

Private Sub Label_wrong_Click() '����
    
    If is_rest = False Then Exit Sub
    '��õ�ǰ��
    get_now
    
    If wrong(cur) > form0.rule1_wrong Then
        Timer.Enabled = False
        is_rest = False '��ͣ
        tmp = MsgBox("���öడ", 64, "FBIWarning") ' stop
        Exit Sub
    End If
    
    wrong(cur) = wrong(cur) + 1
    state_show
    change_cy
    
End Sub

Private Sub Label_theme_Click() '�л�����

    '������
    Timer.Enabled = False
    
    If use_theme > sum_theme Then
        is_rest = False
        tmp = MsgBox("����������", 64, "FBIWarning")
        Exit Sub
    End If
    
    num_theme = Rnd() * sum_theme '��һ�ε����
    Do While vis_theme(num_theme) = True
        num_theme = Rnd() * sum_theme
    Loop
    vis_theme(num_theme) = True
    use_theme = use_theme + 1
    Label_theme.Caption = str_theme(num_theme)
    
    reset_cy '����vis
    
    '�򿪶�Ӧ����ĳ����
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

Private Sub change_cy() ' ������
    If is_rest = False Then Exit Sub

    If use_cy > sum_cy Then
        Timer.Enabled = False
        is_rest = False
        tmp = MsgBox("����������", 64, "FBIWarning")
        Exit Sub
    End If
    
    num_cy = Rnd() * sum_cy '��һ�ε����
    Do While vis_cy(num_cy) = True
        num_cy = Rnd() * sum_cy
    Loop
    
    vis_cy(num_cy) = True
    use_cy = use_cy + 1
    Label_cy.Caption = str_cy(num_cy)
    
End Sub


Private Sub reset_cy() '���ó���vis
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

Private Sub Timer_Timer() '��ʱ
    time_now = time_now + 1
    
    get_now
    
    time(cur) = time_now
    
    Label_time.Caption = "��ʱ:" + Str(time_now)
End Sub

Private Sub Command_exit_Click()
    judge '�ж�ʤ��
    form0.score_show
    Unload Me '�ر�
End Sub

Private Sub Command_start_Click() ' ��ʼ��ʱ�����ֳ���
    time_npw = 0
    Timer.Enabled = True
    change_cy
End Sub

Private Sub state_show()

    '��õ�ǰ��
    get_now
    
    Label_right.Caption = "���:" + Str(right(cur))
    Label_wrong.Caption = "����:" + Str(wrong(cur))
    Label_time.Caption = "��ʱ:" + Str(time(cur))
    Label_pass.Caption = "����:" + Str(pass(cur))
    
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

