VERSION 5.00
Begin VB.Form Form_setting 
   Caption         =   "设置"
   ClientHeight    =   5865
   ClientLeft      =   14580
   ClientTop       =   2400
   ClientWidth     =   6375
   Icon            =   "Form_setting.frx":0000
   LinkTopic       =   "Form2"
   ScaleHeight     =   5865
   ScaleWidth      =   6375
   Begin VB.TextBox Text_name 
      Height          =   495
      Left            =   2760
      TabIndex        =   6
      Text            =   "Text1"
      Top             =   4080
      Width           =   1455
   End
   Begin VB.OptionButton Optiong 
      Height          =   255
      Index           =   2
      Left            =   480
      Style           =   1  'Graphical
      TabIndex        =   5
      Top             =   2040
      Width           =   975
   End
   Begin VB.OptionButton Optiong 
      BackColor       =   &H00E0E0E0&
      Caption         =   "A组"
      Height          =   255
      Index           =   1
      Left            =   600
      Style           =   1  'Graphical
      TabIndex        =   4
      Top             =   1200
      Width           =   975
   End
   Begin VB.TextBox Text_score 
      Height          =   495
      Left            =   3240
      TabIndex        =   3
      Text            =   "0"
      Top             =   3120
      Width           =   1455
   End
   Begin VB.OptionButton Optiong 
      BackColor       =   &H00FFFFFF&
      Caption         =   "A组"
      Height          =   255
      Index           =   0
      Left            =   720
      Style           =   1  'Graphical
      TabIndex        =   2
      Top             =   480
      Width           =   975
   End
   Begin VB.CommandButton Command_change 
      Caption         =   "确定"
      Height          =   495
      Left            =   480
      Style           =   1  'Graphical
      TabIndex        =   0
      Top             =   5160
      Width           =   975
   End
   Begin VB.CommandButton Command_exit 
      Caption         =   "退出"
      Height          =   495
      Left            =   4440
      Style           =   1  'Graphical
      TabIndex        =   1
      Top             =   5160
      Width           =   615
   End
   Begin VB.Label Label_name 
      Caption         =   "Label2"
      ForeColor       =   &H00FFFF80&
      Height          =   495
      Left            =   480
      TabIndex        =   8
      Top             =   3960
      Width           =   1695
   End
   Begin VB.Label Label_score 
      BackStyle       =   0  'Transparent
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Label1"
      ForeColor       =   &H00000000&
      Height          =   375
      Left            =   600
      TabIndex        =   7
      Top             =   3240
      Width           =   1575
   End
   Begin VB.Image Image1 
      Height          =   5535
      Left            =   120
      Picture         =   "Form_setting.frx":000C
      Stretch         =   -1  'True
      Top             =   120
      Width           =   5895
   End
   Begin VB.Image Image2 
      Height          =   735
      Left            =   4320
      Picture         =   "Form_setting.frx":7685C
      Stretch         =   -1  'True
      Top             =   480
      Width           =   1095
   End
End
Attribute VB_Name = "Form_setting"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim gnum As Integer
Dim i As Integer
Dim cur As Integer

Private Sub Form_Load()
    
    gnum = form0.gnum
    For i = 0 To gnum
        Optiong(i).Caption = form0.qname(i)
    Next i
    ' 默认为A组
    Optiong(0).Value = True
    Optiong(1).Value = False
    If form0.gnum < 2 Then
        Optiong(2).Caption = ""
        Optiong(2).Enabled = False '禁用
        Optiong(2).Visible = False
    Else
        Optiong(2).Value = False
    End If
    
    state_show
    
    Label_score.Caption = "强制修改分数"
    Label_name.Caption = "强制修改队名"
    
    beautify
    
End Sub

Private Sub state_show()

    '获得当前组
    get_now
    
    Text_score.Text = str(form0.qscore(cur))
    Text_name.Text = form0.qname(cur)
    
End Sub

Private Sub Command_exit_Click()
    Unload Me
End Sub

Private Sub Command_change_Click()
    get_now
    tmp = MsgBox("修改成功", 0, "恭喜你")
    tmp = form0.cscore(cur, Val(Text_score.Text))
    tmp = form0.cname(cur, Text_name.Text)
    form0.score_show
End Sub

Private Sub get_now()
    '获得当前组
    For i = 0 To gnum
        If Optiong(i) = True Then cur = i
    Next i
End Sub

Private Sub Optiong_Click(Index As Integer)
    state_show
End Sub

Private Sub Form_Resize()
    Me.Top = 0
    Me.Height = Screen.Height
End Sub

Private Sub beautify()
    
    Me.BackColor = vbWhite
    Me.Height = Screen.Height
    Me.Width = Screen.Width / 3
    Me.Left = Screen.Width * 2 / 3
    Me.Top = 0
    Image1.Left = 0
    Image1.Top = 0
    Image1.Width = Me.Width
    Image1.Height = Me.Height
    Image2.Left = Screen.Width / 3
    Image2.Top = 0
    Image2.Width = Screen.Width * 2 / 3
    Image2.Height = Screen.Height
    
    Command_change.BackColor = vbWhite
    Command_change.Font.Name = "华文行楷"
    Command_change.Font.Size = Me.Width / 200
    Command_change.Width = Me.Width * 35 / 100
    Command_change.Height = Me.Height / 10
    Command_change.Left = Me.Width * 10 / 100
    Command_change.Top = Me.Height * 8 / 10
    
    Command_exit.BackColor = vbWhite
    Command_exit.Font.Name = "华文行楷"
    Command_exit.Font.Size = Me.Width / 200
    Command_exit.Width = Me.Width * 35 / 100
    Command_exit.Height = Me.Height / 10
    Command_exit.Left = Me.Width * 55 / 100
    Command_exit.Top = Me.Height * 8 / 10
    
    For i = 0 To gnum
        Optiong(i).BackColor = vbWhite
        Optiong(i).Font.Name = "华文行楷"
        Optiong(i).Font.Size = Me.Width / 200
        Optiong(i).Width = Me.Width * 60 / 100
        Optiong(i).Height = Me.Height / 10
        Optiong(i).Left = Me.Width * 20 / 100
        Optiong(i).Top = Me.Height * (5 + i * 15) / 100
    Next i
    
    Label_score.BackColor = vbWhite
    Label_score.Font.Name = "华文行楷"
    Label_score.Font.Size = Me.Width / 350
    Label_score.Width = Me.Width * 37 / 100
    Label_score.Height = Me.Height / 20
    Label_score.Left = Me.Width * 6 / 100
    Label_score.Top = Me.Height * 60 / 100
    Label_score.ForeColor = 0
    Label_score.BackStyle = 0
    Label_score.BorderStyle = 1
    
    Label_name.BackColor = vbWhite
    Label_name.Font.Name = "华文行楷"
    Label_name.Font.Size = Me.Width / 350
    Label_name.Width = Me.Width * 37 / 100
    Label_name.Height = Me.Height / 20
    Label_name.Left = Me.Width * 6 / 100
    Label_name.Top = Me.Height * 70 / 100
    Label_name.ForeColor = 0
    Label_name.BackStyle = 0
    Label_name.BorderStyle = 1
    
    Text_score.BackColor = vbWhite
    Text_score.Font.Name = "华文行楷"
    Text_score.Font.Size = Me.Width / 350
    Text_score.Width = Me.Width * 35 / 100
    Text_score.Height = Me.Height / 20
    Text_score.Left = Me.Width * 55 / 100
    Text_score.Top = Me.Height * 60 / 100
    
    Text_name.BackColor = vbWhite
    Text_name.Font.Name = "华文行楷"
    Text_name.Font.Size = Me.Width / 350
    Text_name.Width = Me.Width * 35 / 100
    Text_name.Height = Me.Height / 20
    Text_name.Left = Me.Width * 55 / 100
    Text_name.Top = Me.Height * 70 / 100
    
End Sub
