VERSION 5.00
Begin VB.Form form0 
   BackColor       =   &H00FFFFFF&
   Caption         =   "��ʦ��̨�ݸ��е�һ���й�������"
   ClientHeight    =   8415
   ClientLeft      =   3780
   ClientTop       =   3165
   ClientWidth     =   15765
   ForeColor       =   &H00000000&
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   8415
   ScaleWidth      =   15765
   Begin VB.ComboBox Combo_g2 
      Height          =   300
      Left            =   12360
      TabIndex        =   12
      Text            =   "Combo1"
      Top             =   2040
      Width           =   1935
   End
   Begin VB.ComboBox Combo_g1 
      Height          =   300
      Left            =   720
      TabIndex        =   11
      Text            =   "Combo1"
      Top             =   2040
      Width           =   1695
   End
   Begin VB.CommandButton Command5 
      Caption         =   "�����ս"
      Height          =   666
      Left            =   9120
      Style           =   1  'Graphical
      TabIndex        =   5
      Top             =   7320
      Width           =   1260
   End
   Begin VB.CommandButton Command4 
      Caption         =   "�����³���"
      Height          =   666
      Left            =   7200
      Style           =   1  'Graphical
      TabIndex        =   4
      Top             =   7200
      Width           =   1260
   End
   Begin VB.CommandButton Command3 
      Caption         =   "��ʱ�Կ���"
      Height          =   666
      Left            =   5400
      Style           =   1  'Graphical
      TabIndex        =   3
      Top             =   7440
      Width           =   1020
   End
   Begin VB.CommandButton Command2 
      Caption         =   "˫���ڲ´�"
      Height          =   666
      Left            =   2880
      Style           =   1  'Graphical
      TabIndex        =   2
      Top             =   7440
      Width           =   1140
   End
   Begin VB.CommandButton Command_setting 
      Caption         =   "����"
      Height          =   615
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   0
      Top             =   1200
      Width           =   1455
   End
   Begin VB.CommandButton Command_exit 
      Caption         =   "�˳�"
      Height          =   495
      Left            =   14160
      Style           =   1  'Graphical
      TabIndex        =   6
      Top             =   720
      Width           =   735
   End
   Begin VB.CommandButton Command1 
      BackColor       =   &H00FFFFFF&
      Caption         =   "���ʾ���"
      BeginProperty Font 
         Name            =   "��������"
         Size            =   26.25
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   900
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   1
      Top             =   7200
      Width           =   2220
   End
   Begin VB.PictureBox WindowsMediaPlayer1 
      Height          =   975
      Left            =   11880
      ScaleHeight     =   915
      ScaleWidth      =   3675
      TabIndex        =   10
      Top             =   6360
      Visible         =   0   'False
      Width           =   3735
   End
   Begin VB.Image Image_g2 
      Height          =   975
      Left            =   12720
      Picture         =   "Form1.frx":000C
      Stretch         =   -1  'True
      Top             =   3480
      Width           =   1215
   End
   Begin VB.Image Image_g1 
      Height          =   855
      Left            =   1080
      Picture         =   "Form1.frx":284F
      Stretch         =   -1  'True
      Top             =   3480
      Width           =   1575
   End
   Begin VB.Label Labelg 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "ȥ�����"
      Height          =   495
      Index           =   2
      Left            =   12960
      TabIndex        =   9
      Top             =   5520
      Width           =   1455
   End
   Begin VB.Label Labelg 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "����"
      ForeColor       =   &H80000008&
      Height          =   495
      Index           =   1
      Left            =   10680
      TabIndex        =   8
      Top             =   1800
      Width           =   1455
   End
   Begin VB.Label Labelg 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BackStyle       =   0  'Transparent
      Caption         =   "һ��"
      ForeColor       =   &H80000008&
      Height          =   735
      Index           =   0
      Left            =   3240
      TabIndex        =   7
      Top             =   1800
      Width           =   1455
   End
   Begin VB.Image Image1 
      Height          =   8415
      Left            =   -120
      Picture         =   "Form1.frx":5092
      Stretch         =   -1  'True
      Top             =   0
      Width           =   15780
   End
End
Attribute VB_Name = "form0"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public gnum As Integer
Private gname(3) As String
Private score(3) As Integer
Public rule0_win As Integer
'Public rule1_right, rule1_wrong, rule1_pass As Integer
'Public rule2_wrong, rule2_right As Integer
'Public rule3_time, rule3_wrong, rule3_pass As Integer
'Public rule4_v, rule4_wrong, rule4_right As Integer
'Public rule5_time As Integer
Dim i As Integer

Private Sub Form_Load()
    
    is_finish = False
    
    For i = 0 To 2
        score(i) = 0
    Next i
    
    gnum = 1
    'gnum = Val(InputBox("����������:", "��������"))
    
    'If gnum = 0 Then
    '    gnum = 2 'δ���룬������ Ĭ��2��
    'ElseIf gnum > 3 Then
    '    gnum = 3 '�����ʲô
    'End If
    
    'gnum = gnum - 1 ' ����������� 0 ~ gnum
    
    'If gnum < 2 Then ' ����
    '    Labelg(2).Caption = "" '����c��
    '    Labelg(2).Visible = False
    '    rule0_win = 3 '�����������
    'Else
    '    rule0_win = 2
    'End If
    
    '��������
    'For i = 0 To gnum
    '    gname(i) = InputBox("�������" + str(i + 1) + "�������:", "��������")
    'Next i
    
    'Ĭ������
    'For i = 0 To gnum
    '    If gname(i) = "" Then gname(i) = str(i + 1)
    'Next i
    
    score_show '��ʾ�ȷ�

    'WindowsMediaPlayer1.URL = App.Path & "\resources\music\bgm.mp3"
    'WindowsMediaPlayer1.Visible = False ''''''''''''''''
    'If WindowsMediaPlayer1.playState = wmppsStopped Then
        'WindowsMediaPlayer1.URL = App.Path & "\2.mp3"
    'End If

    '��������
    Open App.Path & "\resources\group\name.txt" For Input As #1
        Dim groupname As String
        Do Until EOF(1)
            Line Input #1, groupname
            Combo_g1.AddItem (groupname)
            Combo_g2.AddItem (groupname)
        Loop
    Close #1
    
    beautify
    Me.WindowState = 2 'ȫ��
    
End Sub

Public Sub score_show()

    For i = 0 To gnum
        'Labelg(i).Caption = gname(i) + str(score(i))
        Labelg(i).Caption = str(score(i))
    Next i
    
    '6.1 delete
    'judge
End Sub
'6.1ɾ��
'Private Function swap(a As Integer, b As Integer) As Boolean
'    Dim tmp_int As Integer
'    Dim tmp_str As String
'
'    tmp_int = score(a)
'    score(a) = score(b)
'    score(b) = tmp_int
'
'    tmp_str = gname(a)
'    gname(a) = gname(b)
'    gname(b) = tmp_str
'
'End Function

'Private Sub judge()
'
'    For i = 0 To gnum
'        If score(i) >= rule0_win Then
'            tmp = MsgBox(gname(i) + "Ӯ��", 0, "���")
'            'ɾ����С�飬ʣ�������ƴ
'            'tmp = swap(i, gnum)
'            'Labelg(gnum).Caption = "" '���ػ�ʤ��
'            'Labelg(2).Visible = False
'            'gnum = gnum - 1
'            'score_show
'            Exit For
'        End If
'    Next i
'
'    'If gnum < 1 Then ' ��Ϸ����
'    '    command_enable (False)
'    'Else
'    '    command_enable (True)
'    'End If
'
'End Sub

Public Function add_score(win As Integer)
    
    score(win) = score(win) + 1
    
    score_show
    
End Function

'���ⲿ��������
Public Function qname(i As Integer) As String
    qname = gname(i)
End Function
Public Function cname(i As Integer, str As String) As Boolean
    gname(i) = str
    cname = True
End Function
'���ⲿ���ʷ���
Public Function qscore(i As Integer) As Integer
    qscore = score(i)
End Function
'���ⲿ�޸ķ���
Public Function cscore(i As Integer, v As Integer) As Boolean
    score(i) = v
    cscore = True '???
End Function

Private Sub Command_exit_Click()
    'judge
    End
End Sub

Private Sub Command_setting_Click()
    Form_setting.Show
End Sub

Private Sub Command1_Click()
    Form1.Show
End Sub

Private Sub Command2_Click()
    Form2.Show
End Sub

Private Sub Command3_Click()
    Form3.Show
End Sub

Private Sub Command4_Click()
    Form4.Show
End Sub

Private Sub Command5_Click()
    Form5.Show
End Sub
'6.1delete
'Private Function command_enable(a As Boolean)
'    If a = False Then
'        Command1.Enabled = False
'        Command2.Enabled = False
'        Command3.Enabled = False
'        Command4.Enabled = False
'        Command5.Enabled = False
'    Else
'        Command1.Enabled = True
'        Command2.Enabled = True
'        Command3.Enabled = True
'        Command4.Enabled = True
'        Command5.Enabled = True
'    End If
'End Function

Private Sub Form_Resize()
    beautify
End Sub

Private Sub Combo_g1_Click()
    score(0) = 0: score(1) = 0 ' ��ճɼ�
    gname(0) = Combo_g1.Text
    picture_url = App.Path + "\resources\group\" + Replace(Combo_g1.Text, " ", "") + ".jpg"
    Image_g1.Picture = LoadPicture(picture_url)
End Sub

Private Sub Combo_g2_Click()
    score(0) = 0: score(1) = 0 ' ��ճɼ�
    gname(1) = Combo_g2.Text
    picture_url = App.Path + "\resources\group\" + Replace(Combo_g2.Text, " ", "") + ".jpg"
    Image_g2.Picture = LoadPicture(picture_url)
End Sub

Private Sub beautify()

'    Me.WindowState = 2 'ȫ��
    Image1.Left = 0
    Image1.Top = 0
    'Image1.Height = Screen.Height
    'Image1.Width = Screen.Width
    Image1.Width = Me.Width
    Image1.Height = Me.Height
    
    Command1.BackColor = vbWhite
    Command1.Font.Name = "��������"
    Command1.Font.Size = Me.Width / 750
    Command1.Width = Me.Width * 14 / 100
    Command1.Height = Me.Height / 10
    Command1.Left = Me.Width * 5 / 100
    Command1.Top = Me.Height * 5 / 6
    
    Command2.BackColor = vbWhite
    Command2.Font.Name = "��������"
    Command2.Font.Size = Me.Width / 750
    Command2.Width = Me.Width * 14 / 100
    Command2.Height = Me.Height / 10
    Command2.Left = Me.Width * 24 / 100
    Command2.Top = Me.Height * 5 / 6
    
    Command3.BackColor = vbWhite
    Command3.Font.Name = "��������"
    Command3.Font.Size = Me.Width / 750
    Command3.Width = Me.Width * 14 / 100
    Command3.Height = Me.Height / 10
    Command3.Left = Me.Width * 43 / 100
    Command3.Top = Me.Height * 5 / 6
    
    Command4.BackColor = vbWhite
    Command4.Font.Name = "��������"
    Command4.Font.Size = Me.Width / 750
    Command4.Width = Me.Width * 14 / 100
    Command4.Height = Me.Height / 10
    Command4.Left = Me.Width * 62 / 100
    Command4.Top = Me.Height * 5 / 6
    
    Command5.BackColor = vbWhite
    Command5.Font.Name = "��������"
    Command5.Font.Size = Me.Width / 750
    Command5.Width = Me.Width * 14 / 100
    Command5.Height = Me.Height / 10
    Command5.Left = Me.Width * 81 / 100
    Command5.Top = Me.Height * 5 / 6
    '����
    Command_setting.BackColor = vbWhite
    Command_setting.Font.Name = "��������"
    Command_setting.Font.Size = Me.Width / 750
    Command_setting.Width = Me.Width * 7 / 100
    Command_setting.Height = Me.Height * 8 / 100
    Command_setting.Left = Me.Width * 5 / 100
    Command_setting.Top = Me.Height * 5 / 100
    '�˳�
    Command_exit.BackColor = vbWhite
    Command_exit.Font.Name = "��������"
    Command_exit.Font.Size = Me.Width / 750
    Command_exit.Width = Me.Width * 7 / 100
    Command_exit.Height = Me.Height * 8 / 100
    Command_exit.Left = Me.Width * 90 / 100
    Command_exit.Top = Me.Height * 5 / 100
    
    For i = 0 To gnum
        Labelg(i).Alignment = 2
        Labelg(i).BackColor = vbWhite
        Labelg(i).BorderStyle = 1
        Labelg(i).Font.Name = "��������"
        Labelg(i).Font.Size = Me.Width / 200
        Labelg(i).ForeColor = vbWhite
        Labelg(i).Width = Me.Width * 10 / 100
        Labelg(i).Height = Me.Height * 20 / 100
        'Labelg(i).Left = Me.Width * 5 / 100 + i * Me.Width * 30 / 100
        Labelg(i).Top = Me.Height * 5 / 100
        'Labelg(i).Visible = False '����������
    Next i
    Labelg(0).Left = Me.Width * 25 / 100
    Labelg(1).Left = Me.Width * 65 / 100
    Labelg(2).Visible = False
    
    'WindowsMediaPlayer1.Height = Screen.Height * 6 / 100
    'WindowsMediaPlayer1.Width = Screen.Width * 10 / 100
    'WindowsMediaPlayer1.Left = Screen.Width * 88 / 100
    'WindowsMediaPlayer1.Top = Screen.Height * 60 / 100
    
    Combo_g1.BackColor = vbBlack
    Combo_g2.BackColor = vbBlack
    Combo_g1.ForeColor = vbWhite
    Combo_g2.ForeColor = vbWhite
    '5.31��
    Combo_g1.Text = "��ѡ��С��"
    Combo_g1.Width = Me.Width * 20 / 100
    Combo_g1.Top = Me.Height * 20 / 100
    Combo_g1.Font.Name = "��������"
    Combo_g1.Font.Size = Me.Width / 750
    Image_g1.Width = Me.Width * 20 / 100
    Image_g1.Height = Me.Height * 45 / 100
    Image_g1.Top = Me.Height * 30 / 100
    Combo_g2.Text = "��ѡ��С��"
    Combo_g2.Width = Me.Width * 20 / 100
    Combo_g2.Top = Me.Height * 20 / 100
    Combo_g2.Font.Name = "��������"
    Combo_g2.Font.Size = Me.Width / 750
    Image_g2.Width = Me.Width * 20 / 100
    Image_g2.Height = Me.Height * 45 / 100
    Image_g2.Top = Me.Height * 30 / 100
    
    Combo_g1.Left = Me.Width * 3 / 100
    Combo_g2.Left = Me.Width * 77 / 100
    Image_g1.Left = Me.Width * 3 / 100
    Image_g2.Left = Me.Width * 77 / 100
    
End Sub
