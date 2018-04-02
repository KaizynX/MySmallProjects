VERSION 5.00
Begin VB.Form Form_setting 
   Caption         =   "设置"
   ClientHeight    =   9885
   ClientLeft      =   14580
   ClientTop       =   2400
   ClientWidth     =   6450
   LinkTopic       =   "Form2"
   ScaleHeight     =   9885
   ScaleWidth      =   6450
   Begin VB.TextBox Text5_time 
      Height          =   495
      Left            =   1800
      TabIndex        =   25
      Text            =   "倒计时"
      Top             =   6960
      Width           =   1455
   End
   Begin VB.CommandButton Command_change 
      Caption         =   "确定"
      Height          =   495
      Left            =   4200
      TabIndex        =   23
      Top             =   9120
      Width           =   975
   End
   Begin VB.TextBox Text4_wrong 
      Height          =   615
      Left            =   1800
      TabIndex        =   22
      Text            =   "错误"
      Top             =   5760
      Width           =   1095
   End
   Begin VB.TextBox Text4_v 
      Height          =   615
      Left            =   120
      TabIndex        =   21
      Text            =   "速度"
      Top             =   5760
      Width           =   1335
   End
   Begin VB.TextBox Text3_pass 
      Height          =   615
      Left            =   3240
      TabIndex        =   18
      Text            =   "3跳过"
      Top             =   4320
      Width           =   1335
   End
   Begin VB.TextBox Text3_wrong 
      Height          =   495
      Left            =   1680
      TabIndex        =   17
      Text            =   "3犯规"
      Top             =   4200
      Width           =   975
   End
   Begin VB.TextBox Text3_time 
      Height          =   615
      Left            =   0
      TabIndex        =   16
      Text            =   "3倒计时"
      Top             =   4200
      Width           =   1215
   End
   Begin VB.TextBox Text2_wrong 
      Height          =   495
      Left            =   1800
      TabIndex        =   12
      Text            =   "犯规"
      Top             =   2760
      Width           =   1215
   End
   Begin VB.CommandButton Command_exit 
      Caption         =   "退出"
      Height          =   495
      Left            =   5520
      TabIndex        =   10
      Top             =   9120
      Width           =   615
   End
   Begin VB.TextBox Text1_pass 
      Height          =   495
      Left            =   3000
      TabIndex        =   4
      Text            =   "跳过"
      Top             =   1680
      Width           =   975
   End
   Begin VB.TextBox Text1_wrong 
      Height          =   615
      Left            =   1800
      TabIndex        =   3
      Text            =   "犯规"
      Top             =   1680
      Width           =   855
   End
   Begin VB.TextBox Text1_right 
      Height          =   615
      Left            =   360
      TabIndex        =   2
      Text            =   "题目"
      Top             =   1800
      Width           =   1215
   End
   Begin VB.TextBox Text_b 
      Height          =   735
      Left            =   4560
      TabIndex        =   1
      Text            =   "B"
      Top             =   240
      Width           =   1215
   End
   Begin VB.TextBox Text_a 
      Height          =   615
      Left            =   1800
      TabIndex        =   0
      Text            =   "A"
      Top             =   120
      Width           =   975
   End
   Begin VB.Label Label5_time 
      Caption         =   "5倒计时"
      Height          =   375
      Left            =   360
      TabIndex        =   24
      Top             =   7080
      Width           =   1215
   End
   Begin VB.Label Label4_wrong 
      Caption         =   "环节4错误"
      Height          =   375
      Left            =   1800
      TabIndex        =   20
      Top             =   5160
      Width           =   975
   End
   Begin VB.Label Label4_v 
      Caption         =   "环节4速度"
      Height          =   375
      Left            =   240
      TabIndex        =   19
      Top             =   5280
      Width           =   1095
   End
   Begin VB.Label Label3_pass 
      Caption         =   "3跳过"
      Height          =   375
      Left            =   3360
      TabIndex        =   15
      Top             =   3600
      Width           =   855
   End
   Begin VB.Label Label3_wrong 
      Caption         =   "3犯规"
      Height          =   375
      Left            =   1800
      TabIndex        =   14
      Top             =   3600
      Width           =   1095
   End
   Begin VB.Label Label3_time 
      Caption         =   "环节三倒计时"
      Height          =   375
      Left            =   120
      TabIndex        =   13
      Top             =   3600
      Width           =   1095
   End
   Begin VB.Label Label2_wrong 
      Caption         =   "环节2犯规"
      Height          =   375
      Left            =   240
      TabIndex        =   11
      Top             =   2760
      Width           =   1095
   End
   Begin VB.Label Label1_pass 
      Caption         =   "跳过"
      Height          =   255
      Left            =   3360
      TabIndex        =   9
      Top             =   1200
      Width           =   975
   End
   Begin VB.Label Label1_wrong 
      Caption         =   "犯规"
      Height          =   495
      Left            =   1800
      TabIndex        =   8
      Top             =   1080
      Width           =   975
   End
   Begin VB.Label Label1_right 
      Caption         =   "题目"
      Height          =   495
      Left            =   360
      TabIndex        =   7
      Top             =   1080
      Width           =   1095
   End
   Begin VB.Label Label_b 
      Caption         =   "B"
      Height          =   375
      Left            =   3000
      TabIndex        =   6
      Top             =   240
      Width           =   1095
   End
   Begin VB.Label Label_a 
      Caption         =   "A"
      Height          =   375
      Left            =   240
      TabIndex        =   5
      Top             =   240
      Width           =   1095
   End
End
Attribute VB_Name = "Form_setting"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False


Private Sub Form_Load()
    
    beautify

    Label_a.Caption = Form0.name_a + "组分数:"
    Label_b.Caption = Form0.name_b + "组分数:"
    Text_a.Text = Str(Form0.score_a)
    Text_b.Text = Str(Form0.score_b)
    
    Label1_right.Caption = "环节一题目数量"
    Label1_wrong.Caption = "环节一犯规次数"
    Label1_pass.Caption = "环节一跳过机会"
    Text1_right.Text = Str(Form0.rule1_right)
    Text1_wrong.Text = Str(Form0.rule1_wrong)
    Text1_pass.Text = Str(Form0.rule1_pass)
    
    Label2_wrong.Caption = "环节二犯规次数"
    Text2_wrong.Text = Str(Form0.rule2_wrong)
    
    Label3_time.Caption = "环节三倒计时"
    Label3_wrong.Caption = "环节三犯规次数"
    Label3_pass.Caption = "环节三跳过机会"
    Text3_time.Text = Str(Form0.rule3_time)
    Text3_wrong.Text = Str(Form0.rule3_wrong)
    Text3_pass.Text = Str(Form0.rule3_pass)
    
    Label4_v.Caption = "环节四朗读速度"
    Label4_wrong.Caption = "环节四犯规次数"
    Text4_v.Text = Str(Form0.rule4_v)
    Text4_wrong.Text = Str(Form0.rule4_wrong)
    
    Label5_time.Caption = "环节五答题倒计时"
    Text5_time.Text = Str(Form0.rule5_time)
End Sub


Private Sub Command_exit_Click()
    Unload Me
End Sub

Private Sub Command_change_Click()
    Form0.score_a = Val(Text_a.Text)
    Form0.score_b = Val(Text_b.Text)
    Form0.score_show

    Form0.rule1_right = Val(Text1_right.Text)
    Form0.rule1_wrong = Val(Text1_wrong.Text)
    Form0.rule1_pass = Val(Text1_pass.Text)

    Form0.rule2_wrong = Val(Text2_wrong.Text)

    Form0.rule3_time = Val(Text3_time.Text)
    Form0.rule3_wrong = Val(Text3_wrong.Text)
    Form0.rule3_pass = Val(Text3_pass.Text)

    Form0.rule4_v = Val(Text4_v.Text)
    Form0.rule4_wrong = Val(Text4_wrong.Text)
    
    Form0.rule5_time = Val(Text5_time.Text)
    
    tmp = MsgBox("修改成功", 0, "恭喜你")
End Sub

Private Sub beautify()
'none
End Sub

