VERSION 5.00
Begin VB.Form Form3 
   Caption         =   "�����޲�"
   ClientHeight    =   5940
   ClientLeft      =   5910
   ClientTop       =   2970
   ClientWidth     =   11265
   Icon            =   "Form-3.frx":0000
   LinkTopic       =   "Form3"
   ScaleHeight     =   5940
   ScaleWidth      =   11265
   Begin VB.TextBox Textr_time 
      Height          =   495
      Left            =   9240
      TabIndex        =   17
      Text            =   "����ʱ"
      Top             =   4680
      Width           =   1815
   End
   Begin VB.CommandButton Command_change 
      Caption         =   "�޸Ĺ���"
      Height          =   495
      Left            =   7200
      Style           =   1  'Graphical
      TabIndex        =   15
      Top             =   5280
      Width           =   1695
   End
   Begin VB.TextBox Textr_pass 
      Height          =   495
      Left            =   7200
      TabIndex        =   14
      Text            =   "����"
      Top             =   4680
      Width           =   1815
   End
   Begin VB.TextBox Textr_wrong 
      Height          =   495
      Left            =   5280
      TabIndex        =   12
      Text            =   "����"
      Top             =   4680
      Width           =   1695
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "3"
      Height          =   255
      Index           =   2
      Left            =   3480
      Style           =   1  'Graphical
      TabIndex        =   9
      Top             =   3240
      Width           =   975
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "2"
      Height          =   255
      Index           =   1
      Left            =   2040
      Style           =   1  'Graphical
      TabIndex        =   8
      Top             =   3240
      Width           =   975
   End
   Begin VB.CommandButton Command_exit 
      Caption         =   "�˳�"
      Height          =   615
      Left            =   9720
      Style           =   1  'Graphical
      TabIndex        =   7
      Top             =   5280
      Width           =   1095
   End
   Begin VB.CommandButton Command_start 
      Caption         =   "��ʼ"
      Height          =   615
      Left            =   3360
      Style           =   1  'Graphical
      TabIndex        =   6
      Top             =   2040
      Width           =   975
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "A��"
      Height          =   255
      Index           =   0
      Left            =   600
      Style           =   1  'Graphical
      TabIndex        =   2
      Top             =   3240
      Width           =   975
   End
   Begin VB.Timer Timer 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   2040
      Top             =   2280
   End
   Begin VB.Label Labelr_time 
      Caption         =   "������ʱ"
      Height          =   495
      Left            =   9360
      TabIndex        =   16
      Top             =   3720
      Width           =   1575
   End
   Begin VB.Label Labelr_pass 
      Caption         =   "����"
      Height          =   615
      Left            =   7560
      TabIndex        =   13
      Top             =   3720
      Width           =   1575
   End
   Begin VB.Label Labelr_wrong 
      Caption         =   "����"
      Height          =   495
      Left            =   5280
      TabIndex        =   11
      Top             =   3720
      Width           =   1815
   End
   Begin VB.Label Label_rule 
      Caption         =   "���ѹ���"
      Height          =   2895
      Left            =   5280
      TabIndex        =   10
      Top             =   360
      Width           =   5775
   End
   Begin VB.Label Label_pass 
      Caption         =   "����"
      Height          =   495
      Left            =   3840
      TabIndex        =   5
      Top             =   4320
      Width           =   855
   End
   Begin VB.Label Label_wrong 
      Caption         =   "����"
      Height          =   375
      Left            =   2040
      TabIndex        =   4
      Top             =   4320
      Width           =   1215
   End
   Begin VB.Label Label_right 
      Caption         =   "���"
      Height          =   615
      Left            =   120
      TabIndex        =   3
      Top             =   4200
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
      Left            =   120
      TabIndex        =   1
      Top             =   2040
      Width           =   1695
   End
   Begin VB.Label Label_cy 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "����"
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
      Left            =   480
      TabIndex        =   0
      Top             =   480
      Width           =   3855
   End
   Begin VB.Image Image1 
      Height          =   840
      Left            =   960
      Picture         =   "Form-3.frx":1084A
      Stretch         =   -1  'True
      Top             =   5040
      Width           =   2115
   End
End
Attribute VB_Name = "Form3"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim time As Integer '��ʱ
Dim right(3), wrong(3), pass(3) As Integer '��¼��Ժͷ���
Dim sum_cy, num_cy As Integer '����
Dim str_cy(1000) As String
Dim use_cy As Integer
Dim vis_cy(1000) As Boolean  '�ж��ظ�
Dim is_ok As Boolean '��ֹ����
Dim cur, gnum, i As Integer
Dim rule_wrong, rule_pass, rule_time As Integer


Private Sub Form_Load()
    
    is_ok = True
    
    gnum = form0.gnum
    
    For i = 0 To gnum
        right(i) = 0
        wrong(i) = 0
        pass(i) = 0
        Optiong(i).Caption = form0.qname(i)
    Next i
    
    ' Ĭ��ΪA��
    Optiong(0).Value = True
    Optiong(1).Value = False
    If form0.gnum < 2 Then
        Optiong(2).Caption = ""
        Optiong(2).Enabled = False '����
        Optiong(2).Visible = False
    Else
        Optiong(2).Value = False
    End If
    
    '���ӳ����
    Open "resources\part3\data.txt" For Input As #1
        i = 0
        Do Until EOF(1)
            Line Input #1, str_cy(i)
            i = i + 1
        Loop
    Close #1
    sum_cy = i - 1
    
    '����
    rule_wrong = 2
    rule_pass = 2
    rule_time = 90
    Labelr_wrong.Caption = "����"
    Labelr_pass.Caption = "����"
    Labelr_time.Caption = "����ʱ"
    Textr_wrong.Text = str(rule_wrong)
    Textr_pass.Text = str(rule_pass)
    Textr_time.Text = str(rule_time)
    
    time = rule_time
    Label_time.Caption = "����ʱ:" + str(time)
    
    beautify
    
End Sub

Private Sub judge()
    Dim maxv, maxn, maxi As Integer '��¼��߷ֵķ����͸������
    Dim win(3) As Integer
    '��ʼ
    For i = 0 To gnum
        win(i) = True
    Next i
    
    '���
    maxv = -1
    maxi = -1
    maxn = 0
    For i = 0 To gnum
        If win(i) = False Then '����
        ElseIf right(i) > maxv Then
            maxv = right(i)
            maxn = 1
            maxi = i
        ElseIf maxv = right(i) Then
            maxn = maxn + 1
        End If
    Next i
    
    If maxn = 1 Then ' find the wineer
        tmp = MsgBox(form0.qname(maxi) + "Ӯ��", 0, "���")
        form0.add_score (maxi)
        Exit Sub
    Else ' maxn > 1
        For i = 0 To gnum
            If right(i) < maxv Then
                win(i) = False 'no chance to win
            End If
        Next i
    End If
    
    
    '���淸���ٵ�
    maxv = 10000
    maxi = -1
    maxn = 0
    For i = 0 To gnum
        If win(i) = False Then 'jump
        ElseIf wrong(i) < maxv Then
            maxv = wrong(i)
            maxn = 1
            maxi = i
        ElseIf maxv = wrong(i) Then
            maxn = maxn + 1
        End If
    Next i
    
    If maxn = 1 Then ' find the wineer
        tmp = MsgBox(form0.qname(maxi) + "Ӯ��", 0, "���")
        form0.add_score (maxi)
        Exit Sub
    Else ' maxn > 1
        For i = 0 To gnum
            If wrong(i) > maxv Then
                win(i) = False 'no chance to win
            End If
        Next i
    End If
    
    '�����ٵ�
    maxv = 10000
    maxi = -1
    maxn = 0
    For i = 0 To gnum
        If win(i) = False Then '
        ElseIf pass(i) < maxv Then
            maxv = pass(i)
            maxn = 1
            maxi = i
        ElseIf maxv = pass(i) Then
            maxn = maxn + 1
        End If
    Next i
    
    If maxn = 1 Then ' find the wineer
        tmp = MsgBox(form0.qname(maxi) + "Ӯ��", 0, "���")
        form0.add_score (maxi)
        Exit Sub
    Else ' maxn > 1
        For i = 0 To gnum
            If pass(i) > maxv Then
                win(i) = False 'no chance to win
            End If
        Next i
    End If
    
    tmp = MsgBox("ƽ", 0, "���һ�����ô��")
    form0.score_show
    
End Sub


Private Sub Label_right_Click() ' ��ȷ
    
    If is_ok = False Then Exit Sub
    '��õ�ǰ��
    get_now
    
    right(cur) = right(cur) + 1
    
    state_show
    
    change_cy
    
End Sub

Private Sub Label_pass_Click() '����

    If is_ok = False Then Exit Sub
    '��õ�ǰ��
    get_now
    
    If pass(cur) >= rule_pass Then
        tmp = MsgBox("û������", 64, "FBIWarning") ' stop
        Exit Sub
    End If
    
    pass(cur) = pass(cur) + 1
    state_show
    change_cy
    
End Sub

Private Sub Label_wrong_Click() '����
    
    If is_ok = False Then Exit Sub
    '��õ�ǰ��
    get_now
    
    If wrong(cur) >= rule_wrong Then
        Timer.Enabled = False
        is_ok = False '��ͣ
        tmp = MsgBox("���öడ", 64, "FBIWarning") ' stop
        Exit Sub
    End If
    
    wrong(cur) = wrong(cur) + 1
    state_show
    change_cy
    
End Sub

Private Sub change_cy() ' ������

    If use_cy > sum_cy Then
        is_ok = False
        tmp = MsgBox("����������", 0, "FBIWarning")
        Exit Sub
    End If
    
    '��������0-sum_cy
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
    is_ok = True
End Sub

Private Sub Optiong_Click(Index As Integer)
    Timer.Enabled = False
    state_show
End Sub

Private Sub Timer_Timer() '��ʱ
    time = time - 1
    If time = 0 Then
        Timer.Enabled = False
        tmp = MsgBox("ʱ�䵽", 0, "��������")
        is_ok = False
    End If
    Label_time.Caption = "����ʱ:" + str(time)
End Sub

Private Sub Command_exit_Click()
    judge '�ж�ʤ��
    form0.score_show
    Unload Me '�ر�
End Sub

Private Sub Command_start_Click() ' ��ʼ��ʱ�����ֳ���
    
    time = rule_time
    Label_time.Caption = "����ʱ:" + str(time)
    is_ok = True
    Timer.Enabled = True
    change_cy
    
End Sub

Private Sub state_show()
     '��õ�ǰ��
    get_now
    
    Label_right.Caption = "���:" + str(right(cur))
    Label_wrong.Caption = "����:" + str(wrong(cur))
    Label_pass.Caption = "����:" + str(pass(cur))
    
End Sub

Private Sub get_now()
    '��õ�ǰ��
    For i = 0 To gnum
        If Optiong(i) = True Then cur = i
    Next i
End Sub

Private Sub Command_change_Click()
    rule_wrong = Val(Textr_wrong.Text)
    rule_pass = Val(Textr_pass.Text)
    rule_time = Val(Textr_time.Text)
    time = rule_time
    Label_time.Caption = "����ʱ:" + str(time)
    tmp = MsgBox("�޸ĳɹ�", 0, "��ϲ��")
End Sub


Private Sub Form_Resize()
    beautify
End Sub

Private Sub beautify()
    
    Me.Height = Screen.Height * 2 / 3
    Me.Width = Screen.Width * 2 / 3
    Me.Top = Screen.Height / 6
    Me.Left = Screen.Width / 6
    Image1.Left = 0
    Image1.Top = 0
    Image1.Height = Me.Height
    Image1.Width = Me.Width
    
    Label_rule.Caption = "����ѡ�֣������������Ͳ´ʷ����Ⱥ���90���ʱ���ڽ����������´ʣ����г���������һ����ʤ����������ͬ������ݷ����'��'�Ĵ�����һ��Ϊʤ��������ͬ������������Ѷȷָߵ����ж�ʤ��������ÿ�������һ�η����˵'��'�Ļ��ᡣ���ɸ����Ѷ��ʵ����������������������"
    'Label_rule.Caption = Label_rule.Caption + vbCrLf + "�ȱȽϴ���������ٱȽϷ�����������Ƚ���������"
    
    'ͳһ���ñ�����ɫ�����壬�����С
    Dim obj As Object
    For Each obj In Me.Controls
        If TypeName(obj) = "TextBox" Then
            obj.Font.Name = "�����п�"
            obj.BackColor = vbWhite
            obj.Font.Size = Me.Width / 750
        ElseIf TypeName(obj) = "CommandButton" Then
            obj.Font.Name = "�����п�"
            obj.BackColor = vbWhite
            obj.Font.Size = Me.Width / 750
        ElseIf TypeName(obj) = "Label" Then
            obj.Alignment = 2
            obj.Font.Name = "�����п�"
            obj.BackColor = vbWhite
            obj.Font.Size = Me.Width / 750
        ElseIf TypeName(obj) = "OptionButton" Then
            obj.Font.Name = "�����п�"
            obj.BackColor = vbWhite
            obj.Font.Size = Me.Width / 750
            obj.Width = Me.Width * 15 / 100
            obj.Height = Me.Height * 10 / 100
            obj.Top = Me.Height * 55 / 100
        End If
    Next
    
    '����
    Label_cy.Font.Size = Me.Width / 200
    Label_cy.Width = Me.Width * 45 / 100
    Label_cy.Height = Me.Height * 25 / 100
    Label_cy.Top = Me.Height * 10 / 100
    Label_cy.Left = Me.Width * 10 / 100
    '��
    Optiong(0).Left = Me.Width * 5 / 100
    Optiong(1).Left = Me.Width * 25 / 100
    Optiong(2).Left = Me.Width * 45 / 100
    '�ɼ�
    Label_right.Width = Me.Width * 15 / 100
    Label_right.Height = Me.Height * 10 / 100
    Label_right.Top = Me.Height * 70 / 100
    Label_right.Left = Me.Width * 5 / 100
    
    Label_wrong.Width = Me.Width * 15 / 100
    Label_wrong.Height = Me.Height * 10 / 100
    Label_wrong.Top = Me.Height * 70 / 100
    Label_wrong.Left = Me.Width * 25 / 100
    
    Label_pass.Width = Me.Width * 15 / 100
    Label_pass.Height = Me.Height * 10 / 100
    Label_pass.Top = Me.Height * 70 / 100
    Label_pass.Left = Me.Width * 45 / 100
    '��ʱ
    Label_time.Width = Me.Width * 35 / 100
    Label_time.Height = Me.Height * 10 / 100
    Label_time.Top = Me.Height * 40 / 100
    Label_time.Left = Me.Width * 5 / 100
    '��ʼ
    Command_start.Width = Me.Width * 15 / 100
    Command_start.Height = Me.Height * 10 / 100
    Command_start.Top = Me.Height * 40 / 100
    Command_start.Left = Me.Width * 45 / 100
    '����
    Label_rule.Alignment = 0
    Label_rule.Width = Me.Width * 30 / 100
    Label_rule.Height = Me.Height * 54 / 100
    Label_rule.Top = Me.Height * 3 / 100
    Label_rule.Left = Me.Width * 65 / 100
    
    Labelr_wrong.Width = Me.Width * 8 / 100
    Labelr_wrong.Height = Me.Height * 8 / 100
    Labelr_wrong.Top = Me.Height * 60 / 100
    Labelr_wrong.Left = Me.Width * 65 / 100
    
    Labelr_pass.Width = Me.Width * 8 / 100
    Labelr_pass.Height = Me.Height * 8 / 100
    Labelr_pass.Top = Me.Height * 60 / 100
    Labelr_pass.Left = Me.Width * 76 / 100
    
    Labelr_time.Width = Me.Width * 8 / 100
    Labelr_time.Height = Me.Height * 8 / 100
    Labelr_time.Top = Me.Height * 60 / 100
    Labelr_time.Left = Me.Width * 87 / 100
    
    Textr_wrong.Width = Me.Width * 8 / 100
    Textr_wrong.Height = Me.Height * 8 / 100
    Textr_wrong.Top = Me.Height * 71 / 100
    Textr_wrong.Left = Me.Width * 65 / 100
    
    Textr_pass.Width = Me.Width * 8 / 100
    Textr_pass.Height = Me.Height * 8 / 100
    Textr_pass.Top = Me.Height * 71 / 100
    Textr_pass.Left = Me.Width * 76 / 100
    
    Textr_time.Width = Me.Width * 8 / 100
    Textr_time.Height = Me.Height * 8 / 100
    Textr_time.Top = Me.Height * 71 / 100
    Textr_time.Left = Me.Width * 87 / 100
    '�޸Ĺ���
    Command_change.Width = Me.Width * 19 / 100
    Command_change.Height = Me.Height * 8 / 100
    Command_change.Top = Me.Height * 82 / 100
    Command_change.Left = Me.Width * 65 / 100
    '�˳�
    Command_exit.Width = Me.Width * 8 / 100
    Command_exit.Height = Me.Height * 8 / 100
    Command_exit.Top = Me.Height * 82 / 100
    Command_exit.Left = Me.Width * 87 / 100
    
End Sub

