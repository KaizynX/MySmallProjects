VERSION 5.00
Object = "{6BF52A50-394A-11D3-B153-00C04F79FAA6}#1.0#0"; "wmp.dll"
Begin VB.Form form0 
   Caption         =   "北师大台州附中第一届中国成语大会"
   ClientHeight    =   8415
   ClientLeft      =   3780
   ClientTop       =   3165
   ClientWidth     =   15765
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   8415
   ScaleWidth      =   15765
   Begin VB.CommandButton Command5 
      Caption         =   "点球大战"
      Height          =   666
      Left            =   9120
      Style           =   1  'Graphical
      TabIndex        =   5
      Top             =   7320
      Width           =   1260
   End
   Begin VB.CommandButton Command4 
      Caption         =   "出处猜成语"
      Height          =   666
      Left            =   7200
      Style           =   1  'Graphical
      TabIndex        =   4
      Top             =   7200
      Width           =   1260
   End
   Begin VB.CommandButton Command3 
      Caption         =   "限时对抗赛"
      Height          =   666
      Left            =   5400
      Style           =   1  'Graphical
      TabIndex        =   3
      Top             =   7440
      Width           =   1020
   End
   Begin VB.CommandButton Command2 
      Caption         =   "双音节猜词"
      Height          =   666
      Left            =   2880
      Style           =   1  'Graphical
      TabIndex        =   2
      Top             =   7440
      Width           =   1140
   End
   Begin VB.CommandButton Command_setting 
      Caption         =   "设置"
      Height          =   615
      Left            =   13560
      Style           =   1  'Graphical
      TabIndex        =   0
      Top             =   5640
      Width           =   1455
   End
   Begin VB.CommandButton Command_exit 
      Caption         =   "退出"
      Height          =   495
      Left            =   14040
      Style           =   1  'Graphical
      TabIndex        =   6
      Top             =   6600
      Width           =   735
   End
   Begin VB.CommandButton Command1 
      BackColor       =   &H00FFFFFF&
      Caption         =   "六词竞速"
      BeginProperty Font 
         Name            =   "华文行楷"
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
   Begin WMPLibCtl.WindowsMediaPlayer WindowsMediaPlayer1 
      Height          =   975
      Left            =   11160
      TabIndex        =   10
      Top             =   7320
      Width           =   3735
      URL             =   ""
      rate            =   1
      balance         =   0
      currentPosition =   0
      defaultFrame    =   ""
      playCount       =   1
      autoStart       =   -1  'True
      currentMarker   =   0
      invokeURLs      =   -1  'True
      baseURL         =   ""
      volume          =   50
      mute            =   0   'False
      uiMode          =   "full"
      stretchToFit    =   0   'False
      windowlessVideo =   0   'False
      enabled         =   -1  'True
      enableContextMenu=   -1  'True
      fullScreen      =   0   'False
      SAMIStyle       =   ""
      SAMILang        =   ""
      SAMIFilename    =   ""
      captioningID    =   ""
      enableErrorDialogs=   0   'False
      _cx             =   6588
      _cy             =   1720
   End
   Begin VB.Label Labelg 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "A"
      Height          =   495
      Index           =   2
      Left            =   5400
      TabIndex        =   9
      Top             =   600
      Width           =   1455
   End
   Begin VB.Label Labelg 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "A"
      Height          =   495
      Index           =   1
      Left            =   2520
      TabIndex        =   8
      Top             =   720
      Width           =   1455
   End
   Begin VB.Label Labelg 
      Alignment       =   2  'Center
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "A"
      Height          =   735
      Index           =   0
      Left            =   600
      TabIndex        =   7
      Top             =   600
      Width           =   1455
   End
   Begin VB.Image Image1 
      Height          =   8415
      Left            =   0
      Picture         =   "Form1.frx":1084A
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
    
    gnum = Val(InputBox("请输入组数:", "输入组数"))
    
    If gnum = 0 Then
        gnum = 2 '未输入，草泥马 默认2组
    ElseIf gnum > 3 Then
        gnum = 3 '又想搞什么
    End If
    
    gnum = gnum - 1 ' 方便后续操作 0 ~ gnum
    
    If gnum < 2 Then ' 两组
        Labelg(2).Caption = "" '隐藏c组
        Labelg(2).Visible = False
        rule0_win = 3 '额这个规则吗
    Else
        rule0_win = 2
    End If
    
    '输入组名
    For i = 0 To gnum
        gname(i) = InputBox("请输入第" + str(i + 1) + "组的组名:", "输入组名")
    Next i
    
    '默认组名
    For i = 0 To gnum
        If gname(i) = "" Then gname(i) = str(i + 1)
    Next i
    
    score_show '显示比分

    WindowsMediaPlayer1.URL = App.Path & "\resources\music\bgm.mp3"
    'If WindowsMediaPlayer1.playState = wmppsStopped Then
        'WindowsMediaPlayer1.URL = App.Path & "\2.mp3"
    'End If

    beautify
    
End Sub

Public Sub score_show()

    For i = 0 To gnum
        Labelg(i).Caption = gname(i) + str(score(i))
    Next i
    
    judge
End Sub

Private Function swap(a As Integer, b As Integer) As Boolean
    Dim tmp_int As Integer
    Dim tmp_str As String
    
    tmp_int = score(a)
    score(a) = score(b)
    score(b) = tmp_int
    
    tmp_str = gname(a)
    gname(a) = gname(b)
    gname(b) = tmp_str
    
End Function

Private Sub judge()

    For i = 0 To gnum
        If score(i) >= rule0_win Then
            tmp = MsgBox(gname(i) + "赢了", 0, "结果")
            '删除该小组，剩下两组比拼
            'tmp = swap(i, gnum)
            'Labelg(gnum).Caption = "" '隐藏获胜组
            'Labelg(2).Visible = False
            'gnum = gnum - 1
            'score_show
            Exit For
        End If
    Next i
    
    'If gnum < 1 Then ' 游戏结束
    '    command_enable (False)
    'Else
    '    command_enable (True)
    'End If
    
End Sub

Public Function add_score(win As Integer)
    
    score(win) = score(win) + 1
    
    score_show
    
End Function

'从外部访问组名
Public Function qname(i As Integer) As String
    qname = gname(i)
End Function
Public Function cname(i As Integer, str As String) As Boolean
    gname(i) = str
    cname = True
End Function
'从外部访问分数
Public Function qscore(i As Integer) As Integer
    qscore = score(i)
End Function
'从外部修改分数
Public Function cscore(i As Integer, v As Integer) As Boolean
    score(i) = v
    cscore = True '???
End Function

Private Sub Command_exit_Click()
    judge
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

Private Function command_enable(a As Boolean)
    If a = False Then
        Command1.Enabled = False
        Command2.Enabled = False
        Command3.Enabled = False
        Command4.Enabled = False
        Command5.Enabled = False
    Else
        Command1.Enabled = True
        Command2.Enabled = True
        Command3.Enabled = True
        Command4.Enabled = True
        Command5.Enabled = True
    End If
End Function

Private Sub Form_Resize()
    beautify
End Sub

Private Sub beautify()

    Me.WindowState = 2 '全屏
    Image1.Left = 0
    Image1.Top = 0
    Image1.Height = Screen.Height
    Image1.Width = Screen.Width
    
    Command1.BackColor = vbWhite
    Command1.Font.Name = "华文行楷"
    Command1.Font.Size = Me.Width / 750
    Command1.Width = Me.Width * 14 / 100
    Command1.Height = Me.Height / 10
    Command1.Left = Me.Width * 5 / 100
    Command1.Top = Me.Height * 5 / 6
    
    Command2.BackColor = vbWhite
    Command2.Font.Name = "华文行楷"
    Command2.Font.Size = Me.Width / 750
    Command2.Width = Me.Width * 14 / 100
    Command2.Height = Me.Height / 10
    Command2.Left = Me.Width * 24 / 100
    Command2.Top = Me.Height * 5 / 6
    
    Command3.BackColor = vbWhite
    Command3.Font.Name = "华文行楷"
    Command3.Font.Size = Me.Width / 750
    Command3.Width = Me.Width * 14 / 100
    Command3.Height = Me.Height / 10
    Command3.Left = Me.Width * 43 / 100
    Command3.Top = Me.Height * 5 / 6
    
    Command4.BackColor = vbWhite
    Command4.Font.Name = "华文行楷"
    Command4.Font.Size = Me.Width / 750
    Command4.Width = Me.Width * 14 / 100
    Command4.Height = Me.Height / 10
    Command4.Left = Me.Width * 62 / 100
    Command4.Top = Me.Height * 5 / 6
    
    Command5.BackColor = vbWhite
    Command5.Font.Name = "华文行楷"
    Command5.Font.Size = Me.Width / 750
    Command5.Width = Me.Width * 14 / 100
    Command5.Height = Me.Height / 10
    Command5.Left = Me.Width * 81 / 100
    Command5.Top = Me.Height * 5 / 6
    
    Command_setting.BackColor = vbWhite
    Command_setting.Font.Name = "华文行楷"
    Command_setting.Font.Size = Me.Width / 750
    Command_setting.Width = Me.Width * 7 / 100
    Command_setting.Height = Me.Height * 8 / 100
    Command_setting.Left = Me.Width * 80 / 100
    Command_setting.Top = Me.Height * 70 / 100
    
    Command_exit.BackColor = vbWhite
    Command_exit.Font.Name = "华文行楷"
    Command_exit.Font.Size = Me.Width / 750
    Command_exit.Width = Me.Width * 7 / 100
    Command_exit.Height = Me.Height * 8 / 100
    Command_exit.Left = Me.Width * 90 / 100
    Command_exit.Top = Me.Height * 70 / 100
    
    For i = 0 To gnum
        Labelg(i).Alignment = 2
        Labelg(i).BackColor = vbWhite
        Labelg(i).BorderStyle = 1
        Labelg(i).Font.Name = "华文行楷"
        Labelg(i).Font.Size = Me.Width / 750
        Labelg(i).Width = Me.Width * 15 / 100
        Labelg(i).Height = Me.Height / 15
        Labelg(i).Left = Me.Width * 5 / 100 + i * Me.Width * 20 / 100
        Labelg(i).Top = Me.Height * 5 / 100
    Next i

    WindowsMediaPlayer1.Height = Screen.Height * 6 / 100
    WindowsMediaPlayer1.Width = Screen.Width * 10 / 100
    WindowsMediaPlayer1.Left = Screen.Width * 88 / 100
    WindowsMediaPlayer1.Top = Screen.Height * 60 / 100
    
End Sub
