VERSION 5.00
Begin VB.Form Form2 
   Caption         =   "˫����ͬ��"
   ClientHeight    =   4695
   ClientLeft      =   7455
   ClientTop       =   3930
   ClientWidth     =   12435
   Icon            =   "Form-2.frx":0000
   LinkTopic       =   "Form2"
   ScaleHeight     =   4695
   ScaleWidth      =   12435
   Begin VB.CommandButton Command_wrong 
      Caption         =   "��"
      Height          =   615
      Left            =   3960
      Style           =   1  'Graphical
      TabIndex        =   13
      Top             =   3960
      Width           =   855
   End
   Begin VB.CommandButton Command_right 
      Caption         =   "��"
      Height          =   495
      Left            =   2640
      Style           =   1  'Graphical
      TabIndex        =   12
      Top             =   3840
      Width           =   615
   End
   Begin VB.CommandButton Command_change 
      Caption         =   "�޸Ĺ���"
      Height          =   495
      Left            =   7320
      Style           =   1  'Graphical
      TabIndex        =   11
      Top             =   3960
      Width           =   1695
   End
   Begin VB.TextBox Textr_right 
      Height          =   495
      Left            =   9720
      TabIndex        =   10
      Text            =   "��ȷ"
      Top             =   3240
      Width           =   1815
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "3"
      Height          =   495
      Index           =   2
      Left            =   4440
      Style           =   1  'Graphical
      TabIndex        =   7
      Top             =   3000
      Width           =   1095
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "2"
      Height          =   495
      Index           =   1
      Left            =   2520
      Style           =   1  'Graphical
      TabIndex        =   6
      Top             =   3000
      Width           =   1095
   End
   Begin VB.OptionButton Optiong 
      Caption         =   "1"
      Height          =   495
      Index           =   0
      Left            =   840
      Style           =   1  'Graphical
      TabIndex        =   5
      Top             =   3120
      Width           =   1095
   End
   Begin VB.CommandButton Command_tip 
      Caption         =   "����"
      Height          =   615
      Left            =   3360
      Style           =   1  'Graphical
      TabIndex        =   4
      Top             =   2040
      Width           =   1095
   End
   Begin VB.TextBox Text_tip 
      Height          =   375
      Left            =   960
      TabIndex        =   3
      Text            =   "������ʾ"
      Top             =   2160
      Width           =   1455
   End
   Begin VB.CommandButton Command_exit 
      Caption         =   "�˳�"
      Height          =   375
      Left            =   10440
      Style           =   1  'Graphical
      TabIndex        =   2
      Top             =   3960
      Width           =   855
   End
   Begin VB.Label Label_right 
      Caption         =   "����"
      Height          =   495
      Left            =   600
      TabIndex        =   14
      Top             =   3840
      Width           =   1095
   End
   Begin VB.Label Labelr_right 
      Caption         =   "��ȷ"
      Height          =   495
      Left            =   7200
      TabIndex        =   9
      Top             =   3240
      Width           =   1575
   End
   Begin VB.Label Label_rule 
      Caption         =   "���ѹ���"
      Height          =   2895
      Left            =   7080
      TabIndex        =   8
      Top             =   120
      Width           =   6495
   End
   Begin VB.Label Label_tip 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "��ʾ:"
      Height          =   375
      Left            =   720
      TabIndex        =   1
      Top             =   1440
      Width           =   4815
   End
   Begin VB.Label Label_cy 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "����"
      Height          =   855
      Left            =   480
      TabIndex        =   0
      Top             =   360
      Width           =   4695
   End
   Begin VB.Image Image1 
      Height          =   840
      Left            =   5040
      Picture         =   "Form-2.frx":1084A
      Stretch         =   -1  'True
      Top             =   240
      Width           =   2115
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
Dim right(3) As Integer '��¼��Ժͷ���
Dim gnum, i As Integer
Dim cur As Integer
Dim rule_right As Integer

Private Sub Form_Load()
    
    gnum = form0.gnum
    
    For i = 0 To gnum
        right(i) = 0
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
    
     '����
    rule_right = 2
    Labelr_right.Caption = "���"
    Textr_right.Text = str(rule_right)
    
    beautify
    
End Sub

Private Sub Command_right_Click() '�ӷ�
    If is_ok = False Then Exit Sub
    get_now
    right(cur) = right(cur) + 1
    state_show
    
    If right(cur) >= rule_right Then
        is_ok = False
        tmp = MsgBox(form0.qname(cur) + "Ӯ��", 0, "�ɶ�")
        form0.add_score (cur)
        form0.score_show
    End If
End Sub

Private Sub Command_wrong_Click() '����
    If is_ok = False Then Exit Sub
    get_now
    right(cur) = right(cur) - 1
    state_show
End Sub

Private Sub Label_cy_Click() ' ������
    Label_tip = "��ʾ:"
    change_cy
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


 '����С��
Private Sub Optiong_Click(Index As Integer)
    state_show
End Sub

Private Sub Command_exit_Click()
    form0.score_show
    Unload Me
End Sub

Private Sub Command_tip_Click()
    Label_tip.Caption = Label_tip.Caption + " " + Text_tip.Text
End Sub

Private Sub state_show()
    '��õ�ǰ��
    get_now
    
    Label_right.Caption = "���:" + str(right(cur))

End Sub

Private Sub get_now()
    '��õ�ǰ��
    For i = 0 To gnum
        If Optiong(i) = True Then cur = i
    Next i
End Sub


Private Sub Command_change_Click()
    rule_right = Val(Textr_right.Text)
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
    
    Label_rule.Caption = "�ɵ�һ�ֻ�ʤ�����֣����������޶�ʱ����˵��һ��˫���ڴ��飬���ɶ������޶�ʱ���ڲ´ʣ���δ���У���һ��ѡ�ֵ������߼���ͨ��һ��˫���ڴ�����������δ���У��ٽ������Ȳ³����������һ����ʤ������ʱ�����ַ��棬�ô�����Ϊ�ɶԷ��³���"
    
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
            obj.Alignment = 2 '���ж���
            obj.Font.Name = "�����п�"
            obj.BackColor = vbWhite
            obj.Font.Size = Me.Width / 750
        ElseIf TypeName(obj) = "OptionButton" Then
            obj.Font.Name = "�����п�"
            obj.BackColor = vbWhite
            obj.Font.Size = Me.Width / 750
            obj.Width = Me.Width * 15 / 100
            obj.Height = Me.Height * 10 / 100
            obj.Top = Me.Height * 65 / 100
        End If
    Next
    
    '����
    Label_cy.Font.Size = Me.Width / 200
    Label_cy.Width = Me.Width * 45 / 100
    Label_cy.Height = Me.Height * 25 / 100
    Label_cy.Top = Me.Height * 5 / 100
    Label_cy.Left = Me.Width * 10 / 100
    '��ʾ
    Label_tip.Alignment = 0
    Label_tip.Width = Me.Width * 55 / 100
    Label_tip.Height = Me.Height * 10 / 100
    Label_tip.Top = Me.Height * 35 / 100
    Label_tip.Left = Me.Width * 5 / 100
    
    Text_tip.Width = Me.Width * 35 / 100
    Text_tip.Height = Me.Height * 10 / 100
    Text_tip.Top = Me.Height * 50 / 100
    Text_tip.Left = Me.Width * 5 / 100
    
    Command_tip.Width = Me.Width * 15 / 100
    Command_tip.Height = Me.Height * 10 / 100
    Command_tip.Top = Me.Height * 50 / 100
    Command_tip.Left = Me.Width * 45 / 100
    '��
    Optiong(0).Left = Me.Width * 5 / 100
    Optiong(1).Left = Me.Width * 25 / 100
    Optiong(2).Left = Me.Width * 45 / 100
    '�ɼ�
    Label_right.Width = Me.Width * 15 / 100
    Label_right.Height = Me.Height * 10 / 100
    Label_right.Top = Me.Height * 80 / 100
    Label_right.Left = Me.Width * 5 / 100
    '�Դ�
    Command_right.Width = Me.Width * 15 / 100
    Command_right.Height = Me.Height * 10 / 100
    Command_right.Top = Me.Height * 80 / 100
    Command_right.Left = Me.Width * 25 / 100
    
    Command_wrong.Width = Me.Width * 15 / 100
    Command_wrong.Height = Me.Height * 10 / 100
    Command_wrong.Top = Me.Height * 80 / 100
    Command_wrong.Left = Me.Width * 45 / 100
    '����
    Label_rule.Alignment = 0
    Label_rule.Width = Me.Width * 30 / 100
    Label_rule.Height = Me.Height * 55 / 100
    Label_rule.Top = Me.Height * 5 / 100
    Label_rule.Left = Me.Width * 65 / 100
    
    Labelr_right.Width = Me.Width * 12 / 100
    Labelr_right.Height = Me.Height * 10 / 100
    Labelr_right.Top = Me.Height * 65 / 100
    Labelr_right.Left = Me.Width * 65 / 100
    
    Textr_right.Width = Me.Width * 12 / 100
    Textr_right.Height = Me.Height * 10 / 100
    Textr_right.Top = Me.Height * 65 / 100
    Textr_right.Left = Me.Width * 83 / 100
    '�޸Ĺ���
    Command_change.Width = Me.Width * 12 / 100
    Command_change.Height = Me.Height * 10 / 100
    Command_change.Top = Me.Height * 80 / 100
    Command_change.Left = Me.Width * 65 / 100
    '�˳�
    Command_exit.Width = Me.Width * 12 / 100
    Command_exit.Height = Me.Height * 10 / 100
    Command_exit.Top = Me.Height * 80 / 100
    Command_exit.Left = Me.Width * 83 / 100
    
End Sub

