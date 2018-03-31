VERSION 5.00
Begin VB.Form Form1 
   BackColor       =   &H00FFFFFF&
   Caption         =   "一个火柴人的故事"
   ClientHeight    =   9435
   ClientLeft      =   120
   ClientTop       =   750
   ClientWidth     =   9765
   ForeColor       =   &H00FFFFFF&
   LinkTopic       =   "Form1"
   Picture         =   "Form1.frx":0000
   ScaleHeight     =   10030.56
   ScaleMode       =   0  'User
   ScaleWidth      =   10015.38
   StartUpPosition =   2  '屏幕中心
   Begin VB.Timer time_talk 
      Interval        =   2000
      Left            =   8040
      Top             =   120
   End
   Begin VB.OptionButton no 
      BackColor       =   &H00808080&
      Caption         =   "No"
      BeginProperty Font 
         Name            =   "微软雅黑"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   376
      Left            =   5760
      TabIndex        =   2
      Top             =   8654
      Visible         =   0   'False
      Width           =   2438
   End
   Begin VB.OptionButton yes 
      BackColor       =   &H00808080&
      Caption         =   "Yes"
      BeginProperty Font 
         Name            =   "微软雅黑"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   376
      Left            =   3000
      TabIndex        =   1
      Top             =   8654
      Visible         =   0   'False
      Width           =   2438
   End
   Begin VB.Timer Timer_judge 
      Interval        =   500
      Left            =   8640
      Top             =   120
   End
   Begin VB.Timer Timer_walk 
      Interval        =   50
      Left            =   9240
      Top             =   120
   End
   Begin VB.Image face2 
      Height          =   1875
      Left            =   240
      Picture         =   "Form1.frx":4634
      Stretch         =   -1  'True
      Top             =   7320
      Width           =   1950
   End
   Begin VB.Image face1 
      Height          =   1875
      Left            =   240
      Picture         =   "Form1.frx":BD76
      Stretch         =   -1  'True
      Top             =   7320
      Width           =   1950
   End
   Begin VB.Image command 
      Height          =   750
      Left            =   8520
      MouseIcon       =   "Form1.frx":13E81
      MousePointer    =   99  'Custom
      Picture         =   "Form1.frx":144CB
      Top             =   8400
      Width           =   750
   End
   Begin VB.Label Label 
      BackColor       =   &H00FFFFFF&
      Caption         =   "Hello!"
      BeginProperty Font 
         Name            =   "微软雅黑"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   2880
      TabIndex        =   0
      Top             =   7440
      Width           =   6375
   End
   Begin VB.Image marchman2 
      Height          =   960
      Left            =   4320
      Picture         =   "Form1.frx":16DD2
      Top             =   3000
      Width           =   960
   End
   Begin VB.Image marchman1 
      Height          =   960
      Left            =   4320
      Picture         =   "Form1.frx":1BDAA
      Top             =   3120
      Width           =   960
   End
   Begin VB.Image start_2 
      Height          =   1500
      Left            =   3240
      MouseIcon       =   "Form1.frx":20A41
      MousePointer    =   99  'Custom
      Picture         =   "Form1.frx":2108B
      Top             =   3240
      Width           =   3000
   End
   Begin VB.Image scene_d 
      Height          =   7055
      Left            =   0
      Picture         =   "Form1.frx":24CF6
      Stretch         =   -1  'True
      Top             =   0
      Width           =   9750
   End
   Begin VB.Image scene_dd 
      Height          =   7200
      Left            =   0
      Picture         =   "Form1.frx":2A666
      Stretch         =   -1  'True
      Top             =   0
      Width           =   9750
   End
   Begin VB.Image scene_dr 
      Height          =   7200
      Left            =   0
      Picture         =   "Form1.frx":2FD3D
      Stretch         =   -1  'True
      Top             =   0
      Visible         =   0   'False
      Width           =   9750
   End
   Begin VB.Image scene_dl 
      Height          =   7055
      Left            =   0
      Picture         =   "Form1.frx":35463
      Stretch         =   -1  'True
      Top             =   0
      Visible         =   0   'False
      Width           =   9750
   End
   Begin VB.Image scene_r 
      Height          =   7050
      Left            =   0
      Picture         =   "Form1.frx":37F80
      Stretch         =   -1  'True
      Top             =   0
      Visible         =   0   'False
      Width           =   9750
   End
   Begin VB.Image bridge 
      Height          =   450
      Left            =   4290
      Picture         =   "Form1.frx":3BD61
      Stretch         =   -1  'True
      Top             =   4815
      Visible         =   0   'False
      Width           =   6270
   End
   Begin VB.Image p_1 
      Height          =   4500
      Left            =   0
      Picture         =   "Form1.frx":3E1A0
      Top             =   0
      Width           =   4500
   End
   Begin VB.Image p_2 
      Height          =   960
      Left            =   1800
      Picture         =   "Form1.frx":42711
      Top             =   1800
      Width           =   960
   End
   Begin VB.Label talk2 
      BackColor       =   &H00FFFFFF&
      Caption         =   "大侠救我"
      BeginProperty Font 
         Name            =   "微软雅黑"
         Size            =   12
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1680
      TabIndex        =   4
      Top             =   240
      Visible         =   0   'False
      Width           =   1455
   End
   Begin VB.Label talk1 
      BackColor       =   &H00FFFFFF&
      Caption         =   "我是公主"
      BeginProperty Font 
         Name            =   "微软雅黑"
         Size            =   12
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1800
      TabIndex        =   3
      Top             =   240
      Visible         =   0   'False
      Width           =   1695
   End
   Begin VB.Image knife 
      Height          =   5400
      Left            =   1200
      Picture         =   "Form1.frx":453A9
      Stretch         =   -1  'True
      Top             =   0
      Visible         =   0   'False
      Width           =   75
   End
   Begin VB.Image bad_2 
      Height          =   960
      Left            =   1073
      Picture         =   "Form1.frx":47A8C
      Top             =   4797
      Visible         =   0   'False
      Width           =   960
   End
   Begin VB.Image bad_1 
      Height          =   960
      Left            =   1073
      Picture         =   "Form1.frx":4AD61
      Top             =   4797
      Width           =   960
   End
   Begin VB.Image scene_l 
      Height          =   7055
      Left            =   0
      Picture         =   "Form1.frx":4DA02
      Stretch         =   -1  'True
      Top             =   0
      Visible         =   0   'False
      Width           =   9750
   End
   Begin VB.Image end_u1 
      Height          =   9406
      Left            =   0
      Picture         =   "Form1.frx":5051F
      Stretch         =   -1  'True
      Top             =   0
      Visible         =   0   'False
      Width           =   9750
   End
   Begin VB.Image end_u2 
      Height          =   9406
      Left            =   0
      Picture         =   "Form1.frx":76BA0
      Stretch         =   -1  'True
      Top             =   0
      Width           =   9750
   End
   Begin VB.Image end_dd 
      Height          =   9406
      Left            =   0
      Picture         =   "Form1.frx":89D76
      Stretch         =   -1  'True
      Top             =   0
      Width           =   9750
   End
   Begin VB.Image end_dl2 
      Height          =   9406
      Left            =   0
      Picture         =   "Form1.frx":BEB59
      Stretch         =   -1  'True
      Top             =   0
      Width           =   9750
   End
   Begin VB.Image end_dl1 
      Height          =   9406
      Left            =   0
      Picture         =   "Form1.frx":DF8F7
      Stretch         =   -1  'True
      Top             =   0
      Visible         =   0   'False
      Width           =   9750
   End
   Begin VB.Image end_r3 
      Height          =   9406
      Left            =   0
      Picture         =   "Form1.frx":F1C3D
      Stretch         =   -1  'True
      Top             =   0
      Width           =   9750
   End
   Begin VB.Image end_r2 
      Height          =   9406
      Left            =   0
      Picture         =   "Form1.frx":10A193
      Stretch         =   -1  'True
      Top             =   0
      Width           =   9750
   End
   Begin VB.Image end_r1 
      Height          =   9406
      Left            =   0
      Picture         =   "Form1.frx":145B0A
      Stretch         =   -1  'True
      Top             =   0
      Width           =   9750
   End
   Begin VB.Image end_dr2 
      Height          =   9406
      Left            =   0
      Picture         =   "Form1.frx":1647D4
      Stretch         =   -1  'True
      Top             =   0
      Width           =   9750
   End
   Begin VB.Image end_dr1 
      Height          =   9406
      Left            =   0
      Picture         =   "Form1.frx":1766C6
      Stretch         =   -1  'True
      Top             =   0
      Width           =   9750
   End
   Begin VB.Image end_l5 
      Height          =   9406
      Left            =   0
      Picture         =   "Form1.frx":19EC03
      Stretch         =   -1  'True
      Top             =   0
      Visible         =   0   'False
      Width           =   9750
   End
   Begin VB.Image end_l4 
      Height          =   9406
      Left            =   0
      Picture         =   "Form1.frx":1BE95E
      Stretch         =   -1  'True
      Top             =   0
      Width           =   9750
   End
   Begin VB.Image end_l3 
      Height          =   9406
      Left            =   0
      Picture         =   "Form1.frx":1D278A
      Stretch         =   -1  'True
      Top             =   0
      Width           =   9750
   End
   Begin VB.Image end_l2 
      Height          =   9406
      Left            =   0
      Picture         =   "Form1.frx":1E50F5
      Stretch         =   -1  'True
      Top             =   0
      Visible         =   0   'False
      Width           =   9750
   End
   Begin VB.Image end_l1 
      Height          =   9406
      Left            =   0
      Picture         =   "Form1.frx":1FFA59
      Stretch         =   -1  'True
      Top             =   0
      Visible         =   0   'False
      Width           =   9750
   End
   Begin VB.Image scene0 
      Height          =   7050
      Left            =   0
      Picture         =   "Form1.frx":21AA5A
      Stretch         =   -1  'True
      Top             =   0
      Width           =   9750
   End
   Begin VB.Image background 
      Height          =   9407
      Left            =   0
      Picture         =   "Form1.frx":220762
      Stretch         =   -1  'True
      Top             =   0
      Width           =   9750
   End
   Begin VB.Image scene_u 
      Height          =   7055
      Left            =   0
      Picture         =   "Form1.frx":2267F6
      Stretch         =   -1  'True
      Top             =   0
      Visible         =   0   'False
      Width           =   9750
   End
   Begin VB.Image start_1 
      Height          =   9406
      Left            =   0
      Picture         =   "Form1.frx":22C4FE
      Stretch         =   -1  'True
      Top             =   0
      Width           =   9750
   End
   Begin VB.Menu menu 
      Caption         =   "菜单"
      Begin VB.Menu new 
         Caption         =   "新游戏"
      End
      Begin VB.Menu shuoming 
         Caption         =   "游戏说明"
      End
      Begin VB.Menu help 
         Caption         =   "攻略"
      End
      Begin VB.Menu end 
         Caption         =   "退出游戏"
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim t, m_l, m_t As Integer
Dim u_judge, u_time, u_direction, u_last As Integer
Dim d_time, dd_time, dr_time, dl_time As Integer
Dim r_judge As Integer
Dim l_time As Integer
Dim h_time As Integer
Dim jieju As Integer

Private Sub end_Click()
    End
End Sub

Private Sub Form_Load()
    '初始火柴人位置
    marchman1.Left = 4500 ' 1800 4800桥4300
    marchman1.Top = 3200 ' 1100 4100桥5120
    marchman2.Left = marchman1.Left
    marchman2.Top = marchman1.Top
    m_l = marchman1.Left
    m_t = marchman1.Top
    '开始界面
    face1.ZOrder
    face2.ZOrder
    start_1.ZOrder
    start_2.ZOrder
    start_1.Visible = True
    start_2.Visible = True
    face1.Visible = True
    face2.Visible = False
    '其他隐藏
    scene0.Visible = False
    scene_u.Visible = False
    scene_d.Visible = False
    scene_dd.Visible = False
    scene_dl.Visible = False
    scene_r.Visible = False
    bridge.Visible = False
    scene_l.Visible = False
    p_1.Visible = False
    p_2.Visible = False
    yes.Visible = False
    no.Visible = False
    talk1.Visible = False
    talk2.Visible = False
    bad_1.Visible = False
    bad_2.Visible = False
    knife.Visible = False
    end_u1.Visible = False
    end_u2.Visible = False
    end_dd.Visible = False
    end_dl1.Visible = False
    end_dl2.Visible = False
    end_dr1.Visible = False
    end_dr2.Visible = False
    end_r1.Visible = False
    end_r2.Visible = False
    end_r3.Visible = False
    end_l1.Visible = False
    end_l2.Visible = False
    end_l3.Visible = False
    end_l4.Visible = False
    end_l5.Visible = False
    '初始值
    u_judge = 1
    u_direction = 1
    t = 0
    u_time = 0
    u_last = 0
    d_time = 0
    dd_time = 0
    dr_time = 0
    dl_time = 0
    l_time = 0
    h_time = 0
    r_judge = 0
    jieju = 0
End Sub

Private Sub help_Click()
    'vbInformation , "游戏说明"
    If start_1.Visible = True Then
        MsgBox "点开始游戏啊！", vbInformation, "来自作者的深切关怀"
    ElseIf scene0.Visible = True Then
        MsgBox "每条路都会引向精彩的人生，如果你能把握好自己。", vbInformation, "来自作者的导语"
    ElseIf scene_u.Visible = True Then
        If u_time = 0 Then
            MsgBox "同样每条路都不差,相信你的决定并不会错。", vbInformation, "来自作者的循循善诱"
        ElseIf u_time = 1 Then
            MsgBox "坚持你做出的选择吧，你要为你的选择负责。", vbInformation, "来自作者的循循善诱"
        ElseIf u_time = 2 Then
            MsgBox "只要你不忘初心，坚持你最初的方向，就能成功。", vbInformation, "来自作者的循循善诱"
        End If
    ElseIf scene_d.Visible = True Then
        If h_time = 0 Then
            MsgBox "我并不能说那条路是‘歪门邪道’，也不保证每条路都是所谓‘正道’", vbInformation, "来自作者的排忧解疑"
            h_time = h_time + 1
        ElseIf h_time = 1 Then
            MsgBox "孩子，路是你自己探索的，不要总希望有人能帮助你。", vbInformation, "来自作者的叹息"
            h_time = h_time + 1
        ElseIf h_time = 2 Then
            MsgBox "好吧，既然你执意想知道答案，那就诚心诚意的再问一次。", vbInformation, "来自作者的无奈"
            h_time = h_time + 1
        ElseIf h_time = 3 Then
            MsgBox "走正道是不会错的，只是你也要付出真功夫" & vbCrLf & "如果你想投机取巧走捷径，那么你就要抓住机会，机不可失" & vbCrLf & "如果你非要去左边，只能说你很有探索精神，但还是要慎重考虑", vbInformation, "来自作者的坦白"
            h_time = h_time + 1
        ElseIf h_time = 4 Then
            MsgBox "怎么？还没想通" & vbCrLf & "你需要在三秒之内做出决定进入捷径，才能把握住机会" & vbCrLf & "你需要慎重考虑5秒以上才可以去左边", vbInformation, "来自作者的无语"
        End If
    ElseIf scene_r.Visible = True Then
        MsgBox "即使在困难面前也不要放弃，哪怕是挣扎", vbInformation, "来自作者的话语"
    ElseIf scene_l.Visible = True Then
        If bad_1.Visible = False Then
            MsgBox "救人一命胜造七级浮屠", vbInformation, "来自作者的提醒"
        ElseIf bad_2.Visible = flase Then
            MsgBox "要敢于同恶势力作斗争", vbInformation, "来自作者的怂恿"
        ElseIf knife.Visible = flase Then
            MsgBox "人有多大胆，地有多大产", vbInformation, "来自作者的怂恿"
        ElseIf knife.Visible = True Then
            MsgBox "有些事情不是一头热就能解决的，留得青山在不怕没柴烧。", vbInformation, "40M外作者的呼叫"
        End If
    ElseIf scene_dd.Visible = True Then
        MsgBox "坚持就是胜利", vbInformation, "来自作者的鼓励"
    ElseIf scene_dr.Visible = True Then
        MsgBox "并不是所有的“捷径”都是真的", vbInformation, "来自作者的劝诫"
    ElseIf scene_dl.Visible = True Then
        MsgBox "你选择了这条前无古人的道路，是成是败，就看你的造化了" & vbCrLf & "到处走走，耐心等等", vbInformation, "来自作者的话"
    End If
End Sub

Private Sub new_Click()
    '初始火柴人位置
    marchman1.Left = 4500 ' 1800 4800桥4300
    marchman1.Top = 3200 ' 1100 4100桥5120
    marchman2.Left = marchman1.Left
    marchman2.Top = marchman1.Top
    m_l = marchman1.Left
    m_t = marchman1.Top
    '开始界面
    face1.ZOrder
    face2.ZOrder
    start_1.ZOrder
    start_2.ZOrder
    start_1.Visible = True
    start_2.Visible = True
    face1.Visible = True
    face2.Visible = False
    '其他隐藏
    scene0.Visible = False
    scene_u.Visible = False
    scene_d.Visible = False
    scene_dd.Visible = False
    scene_dl.Visible = False
    scene_r.Visible = False
    bridge.Visible = False
    scene_l.Visible = False
    p_1.Visible = False
    p_2.Visible = False
    yes.Visible = False
    no.Visible = False
    talk1.Visible = False
    talk2.Visible = False
    bad_1.Visible = False
    bad_2.Visible = False
    knife.Visible = False
    end_u1.Visible = False
    end_u2.Visible = False
    end_dd.Visible = False
    end_dl1.Visible = False
    end_dl2.Visible = False
    end_dr1.Visible = False
    end_dr2.Visible = False
    end_r1.Visible = False
    end_r2.Visible = False
    end_r3.Visible = False
    end_l1.Visible = False
    end_l2.Visible = False
    end_l3.Visible = False
    end_l4.Visible = False
    end_l5.Visible = False
    '初始值
    u_judge = 1
    u_direction = 1
    t = 0
    u_time = 0
    u_last = 0
    d_time = 0
    dd_time = 0
    dr_time = 0
    dl_time = 0
    l_time = 0
    h_time = 0
    r_judge = 0
    jieju = 0
End Sub

Private Sub shuoming_Click()
    Form2.Show
End Sub

Private Sub start_2_Click() '开始游戏
    start_1.Visible = False
    start_2.Visible = False
    scene0.Visible = True
    Form2.Show
End Sub

Private Sub time_talk_Timer()
    If scene_l.Visible = True Then '场景l
        If p_1.Visible = True Then
            l_time = l_time + 1
            If l_time = 60 Then l_time = 0
            talk1.Visible = (0 = (l_time Mod 2))
            talk2.Visible = (1 = (l_time Mod 2))
        ElseIf p_2.Visible = True Then
            l_time = l_time + 1
            If l_time = 3 Then
                jieju = 31
            End If
            face2.Visible = False
            talk1.Caption = "谢谢你救了我"
            talk2.Caption = "我要以身相许"
            talk1.Visible = (0 = (l_time Mod 2))
            talk2.Visible = (1 = (l_time Mod 2))
        End If
    End If
End Sub

Private Sub Timer_judge_Timer()
    If scene0.Visible = True Then '场景0的选择
        Label.Caption = "作者：" + vbCrLf + "        选择一条道路，开始你的旅行!" 'vbCrLf换行
        If m_l < 0 Or m_l > 9200 Or m_t = 0 Or m_t = 6400 Then
            Label.Caption = "        你确定选择这条路?"
        End If
    End If
    Dim t_u As Integer
    If scene_u.Visible = True Then '场景u的结局
        'label的话
        If u_time = 1 Then
            Label.Caption = "作者：" + vbCrLf + "        人生的道路从来不是笔直的"
        ElseIf u_time = 2 Then
            Label.Caption = "作者：" + vbCrLf + "        既然做出了选择，就不要后悔继续向前吧！"
        End If
        'judge判断
        If u_last <> 0 And u_last <> u_direction Then
            u_judge = 0
        End If
        '决定胜负
        If u_time = 3 Then
            t_u = t - u + 1 '需要延时
            If t_u > 1 Then
                If u_judge = 1 Then '赢了
                    jieju = 12
                Else                '输了
                    jieju = 11
                End If
            End If
        End If
    ElseIf scene_d.Visible = True Then '场景d
        Label.Caption = "        前方出现了三条路"
        If m_t = 0 Then
            Label.Caption = "        你已经选择了这人生，你没办法后悔"
        ElseIf m_t = 6400 Then
            Label.Caption = "作者：" + vbCrLf + "        这条路很长，你不试试右边那条？"
        ElseIf m_l = 0 Then
            Label.Caption = "作者：" + vbCrLf + "        此路不通车,请慎重考虑！"
            d_time = d_time + 1
        ElseIf m_l = 9200 Then
            Label.Caption = "作者：" + vbCrLf + "        这是条捷径！比下面那条快多了!"
            d_time = d_time + 1
        Else
            d_time = 0
        End If
    ElseIf scene_dd.Visible = True Then '场景dd
        If m_t = 6500 Then
            m_l = 4500: m_t = 100
            marchman1.Left = m_l: marchman2.Left = m_l
            marchman1.Top = m_t: marchman2.Top = m_t
            dd_time = dd_time + 1
            If dd_time = 3 Then
                jieju = 22
            End If
        ElseIf m_t = 0 Then
            Label.Caption = "作者：" + vbCrLf + "        不得脱离正轨"
        Else
            Label.Caption = "作者：" + vbCrLf + "        年轻人，现在依然能坚持走这条路的人已经不多了，但我要告诉你的是：这条路真的不短。"
        End If
    ElseIf scene_dr.Visible = True Then '场景dr
        Label.Caption = "作者：" + vbCrLf + "        这是捷径，走过这个路口就到终点了。"
        If m_l = 0 Then
            Label.Caption = "作者：" + vbCrLf + "        别回头了，没有更快的了。"
        ElseIf m_l = 9200 Then
            m_l = 100: m_t = 3200
            marchman1.Left = m_l: marchman2.Left = m_l
            marchman1.Top = m_t: marchman2.Top = m_t
            dr_time = dr_time + 1
        End If
        If dr_time = 1 Then
            If d_time <= 6 Then
                jieju = 241
            End If
        ElseIf dr_time = 3 Then
            jieju = 242
        End If
    ElseIf scene_dl.Visible = True Then '场景dl
        If d_time >= 10 Then
            If m_l = 0 Then
                jieju = 232
            End If
        Else
            dl_time = dl_time + 1
            If dl_time >= 6 Then
                jieju = 231
            End If
        End If
    ElseIf scene_l.Visible = True Then '场景l
        If knife.Visible = True Then
            If l_time = 3 Then
                scene_l.Visible = False
                end_l3.Visible = True
                end_l3.ZOrder
                yes.Visible = False: no.Visible = False
            End If
        End If
    End If
End Sub

Private Sub Timer_walk_Timer()
    t = t + 1
    If t = 60 Then t = 0
    If scene_r.Visible = True Then
        If m_t = 6200 Then
            If r_judge = 0 Then
                jieju = 41
            ElseIf r_judge = 1 Then
                jieju = 43
            End If
        ElseIf m_t = 4100 And m_l >= 3800 Then
            bridge.Left = 4400
            bridge.Visible = True
            bridge.ZOrder
            If r_judge = 0 Then
                Label.Caption = "        天空中出现了一座桥！"
                face2.Visible = False
            End If
            r_judge = 1
            If m_l = 9200 Then
                jieju = 42
            End If
        Else
            m_t = m_t + 100
            marchman2.Top = m_t: marchman1.Top = m_t
            If r_judge = 1 Then
                Label.Caption = "Oh!--shit！!!"
                face2.Visible = True
            End If
        End If
    End If
End Sub
Private Sub command_Click()
    If jieju = 11 Then '上
        scene_u.Visible = False
        end_u1.Visible = True
        end_u1.ZOrder
    ElseIf jieju = 12 Then
        scene_u.Visible = False
        end_u2.Visible = True
        end_u2.ZOrder
    ElseIf jieju = 22 Then '下下
        scene_d.Visible = False
        end_dd.Visible = True
        end_dd.ZOrder
    ElseIf jieju = 231 Then '下←
        scene_dl.Visible = False
        end_dl1.Visible = True
        end_dl1.ZOrder
    ElseIf jieju = 232 Then
        scene_dl.Visible = False
        end_dl2.Visible = True
        end_dl2.ZOrder
    ElseIf jieju = 241 Then '下右
        scene_dr.Visible = False
        end_dr1.Visible = True
        end_dr1.ZOrder
    ElseIf jieju = 242 Then
        scene_dr.Visible = False
        end_dr2.Visible = True
        end_dr2.ZOrder
    ElseIf jieju = 41 Then '右
        scene_r.Visible = False
        end_r1.Visible = True
        end_r1.ZOrder
    ElseIf jieju = 42 Then
        scene_r.Visible = False
        end_r2.Visible = True
        end_r2.ZOrder
    ElseIf jieju = 43 Then
        scene_r.Visible = False
        end_r3.Visible = True
        end_r3.ZOrder
    ElseIf jieju = 31 Then '←
        scene_l.Visible = False
        end_l1.Visible = True
        end_l1.ZOrder
    ElseIf jieju = 32 Then
        scene_l.Visible = False
        end_l2.Visible = True
        end_l2.ZOrder
    ElseIf jieju = 34 Then
        scene_l.Visible = False
        end_l4.Visible = True
        end_l4.ZOrder
    ElseIf jieju = 35 Then
        scene_l.Visible = False
        end_l5.Visible = True
        end_l5.ZOrder
    End If
    If scene0.Visible = True Then '场景0
        If m_t = 0 Then '上路
            scene0.Visible = False
            scene_u.Visible = True
            scene_u.ZOrder
            marchman2.ZOrder: marchman1.ZOrder
            m_l = 4500: m_t = 6300
            marchman1.Left = m_l: marchman2.Left = m_l
            marchman1.Top = m_t: marchman2.Top = m_t
            Label.Caption = "作者：" + vbCrLf + "        人生处处充满选择，再次做出选择吧！"
        ElseIf m_t = 6400 Then '下路
            scene0.Visible = False
            scene_d.Visible = True
            scene_d.ZOrder
            marchman2.ZOrder: marchman1.ZOrder
            m_l = 4500: m_t = 100
            marchman1.Left = m_l: marchman2.Left = m_l
            marchman1.Top = m_t: marchman2.Top = m_t
        ElseIf m_l < 0 Then '左边
            scene0.Visible = False
            scene_l.Visible = True
            p_1.Visible = True
            scene_l.ZOrder: p_1.ZOrder
            marchman2.ZOrder: marchman1.ZOrder
            m_l = 7000: m_t = 3200
            marchman1.Left = m_l: marchman2.Left = m_l
            marchman1.Top = m_t: marchman2.Top = m_t
            Label.Caption = "作者：" + vbCrLf + "        你要拯救那个笼子里的人吗？"
            yes.Visible = True: no.Visible = True
            yes.Caption = "按套路，应该救"
            no.Caption = "丑拒……"
            yes.Value = False: no.Value = False
            talk1.ZOrder: talk2.ZOrder
            bad_1.ZOrder
        ElseIf m_l > 9200 Then '右边
            scene0.Visible = False
            scene_r.Visible = True
            scene_r.ZOrder
            marchman2.ZOrder: marchman1.ZOrder
            m_l = 1800: m_t = 1100
            marchman1.Left = m_l: marchman2.Left = m_l
            marchman1.Top = m_t: marchman2.Top = m_t
            Label.Caption = "        啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊"
            face2.Visible = True
        End If
    ElseIf scene_u.Visible = True Then '场景u
        'Dim u_judge, u_time, u_direction As Integer 1上2下3左4右
        u_last = u_direction
        If m_t = 0 Then '上路
            If u_direction = 2 Then
                MsgBox "不能走回头路", vbInformation, "Warning!"
            Else
                m_l = 4500: m_t = 6300
                marchman1.Left = m_l: marchman2.Left = m_l
                marchman1.Top = m_t: marchman2.Top = m_t
                u_time = u_time + 1
                u_direction = 1
            End If
        ElseIf m_t = 6400 Then '下路
            If u_direction = 1 Then
                MsgBox "不能走回头路", vbInformation, "Warning!"
            Else
                m_l = 4500: m_t = 100
                marchman1.Left = m_l: marchman2.Left = m_l
                marchman1.Top = m_t: marchman2.Top = m_t
                u_time = u_time + 1
                u_direction = 2
            End If
        End If
        If m_l <= 0 Then '左边
            If u_direction = 4 Then
                MsgBox "不能走回头路", vbInformation, "Warning!"
            Else
                m_l = 9100: m_t = 3200
                marchman1.Left = m_l: marchman2.Left = m_l
                marchman1.Top = m_t: marchman2.Top = m_t
                u_time = u_time + 1
                u_direction = 3
            End If
        ElseIf m_l >= 9200 Then '右边
            If u_direction = 3 Then
                MsgBox "不能走回头路", vbInformation, "Warning!"
            Else
                m_l = 100: m_t = 3200
                marchman1.Left = m_l: marchman2.Left = m_l
                marchman1.Top = m_t: marchman2.Top = m_t
                u_time = u_time + 1
                u_direction = 4
            End If
        End If
    ElseIf scene_d.Visible = True Then '场景d
        If m_t = 0 Then
            MsgBox "你没有机会后悔", vbInformation, "Sorry"
        ElseIf m_t = 6400 Then '正道
            scene_d.Visible = False
            scene_dd.Visible = True
            scene_dd.ZOrder
            marchman2.ZOrder: marchman1.ZOrder
            m_l = 4500: m_t = 100
            marchman1.Left = m_l: marchman2.Left = m_l
            marchman1.Top = m_t: marchman2.Top = m_t
        ElseIf m_l = 0 Then '禁止
            scene_d.Visible = False
            scene_dl.Visible = True
            scene_dl.ZOrder
            marchman2.ZOrder: marchman1.ZOrder
            m_l = 9000: m_t = 3200
            marchman1.Left = m_l: marchman2.Left = m_l
            marchman1.Top = m_t: marchman2.Top = m_t
            Label.Caption = "作者：" + vbCrLf + "        你来到了一块不毛之地。"
        ElseIf m_l = 9200 Then '捷径
            scene_d.Visible = False
            scene_dr.Visible = True
            scene_dr.ZOrder
            marchman2.ZOrder: marchman1.ZOrder
            m_l = 100: m_t = 3200
            marchman1.Left = m_l: marchman2.Left = m_l
            marchman1.Top = m_t: marchman2.Top = m_t
        End If
    ElseIf scene_l.Visible = True Then '场景l
        If yes.Value = False And no.Value = False Then
            MsgBox "你还没有做出选择", vbInformation, "你逗我呢"
            yes.Value = False: no.Value = False
        Else
            If p_1.Visible = True And bad_1.Visible = False Then
                If no.Value = True Then MsgBox "不救也得救！", vbInformation, "来自作者的恐吓"
                bad_1.Visible = True
                yes.Value = False: no.Value = False
                Label.Caption = "这时出现了一个人……" + vbCrLf + "        你是否执意要救 它 。"
                yes.Caption = "是的，我愿意"
                no.Caption = "那个啥 我想上厕所"
            ElseIf bad_1.Visible = True And bad_2.Visible = False Then
                If no.Value = True Then
                    jieju = 34
                    yes.Visible = False: no.Visible = False
                ElseIf yes.Value = True Then
                    bad_2.Visible = True
                    bad_2.ZOrder
                    yes.Value = False: no.Value = False
                    Label.Caption = "那厮掏出了一把明晃晃的小刀刀！" + vbCrLf + "        你还要爱着那个女孩吗？"
                    yes.Caption = "双手接白刃！"
                    no.Caption = "哼-待会再来收拾你"
                End If
            ElseIf bad_2.Visible = True And knife.Visible = False Then
                If no.Value = True Then
                    jieju = 35
                    yes.Visible = False: no.Visible = False
                ElseIf yes.Value = True Then
                    yes.Value = False: no.Value = False
                    knife.Visible = True
                    knife.ZOrder
                    Label.Caption = "坏人从腰间拔出了一把长达40M的大刀" + vbCrLf + "        你还是快跑吧-"
                    face2.Visible = True
                    yes.Caption = "我不会丢下公主走的！"
                    no.Caption = "我一定会回来的！~~"
                    l_time = 0
                End If
            ElseIf knife.Visible = True Then
                If no.Value = True Then
                    MsgBox "明智的选择", vbInformation, "作者的赞叹"
                    p_1.Visible = False
                    bad_1.Visible = False
                    bad_2.Visible = False
                    knife.Visible = False
                    p_2.Visible = True
                    p_2.ZOrder
                    Label.Caption = "        几分钟后，坏人走了，你救出了公主"
                    yes.Visible = False: no.Visible = False
                ElseIf yes.Value = True Then
                    jieju = 32
                    yes.Visible = False: no.Visible = False
                End If
            End If
        End If
    End If
End Sub

Private Sub Form_KeyDown(KeyCode As Integer, Shift As Integer)
    Dim mj_l, mj_r, mj_u, mj_d As Boolean '判断能否行走move judge_left,right,up,down
    If scene0.Visible = True Or scene_u.Visible = True Or scene_d.Visible = True Then '在场景0或up的情况
        If m_t >= 3000 And m_t <= 3500 And m_l > 0 Or m_l > 4400 Then mj_l = True
        If m_t >= 3000 And m_t <= 3500 And m_l < 9200 Or m_l < 4800 Then mj_r = True
        If m_l >= 4300 And m_l <= 4800 And m_t > 0 Or m_t > 3000 Then mj_u = True
        If m_l >= 4300 And m_l <= 4800 And m_t < 6400 Or m_t < 3500 Then mj_d = True
    ElseIf scene_dd.Visible = True Then
        If m_t > 0 Then mj_u = True
        If m_t < 6500 Then mj_d = True
    ElseIf scene_dr.Visible = True Then
        If m_l > 0 Then mj_l = True
        If m_l < 9200 Then mj_r = True
    ElseIf scene_dl.Visible = True Then
        If m_t > 0 Then mj_u = True
        If m_t < 6500 Then mj_d = True
        If m_l > 0 Then mj_l = True
        If m_l < 9200 Then mj_r = True
    ElseIf scene_r.Visible = True Then
        If m_l > 1800 Then mj_l = True
        If m_l < 9200 Then mj_r = True
    ElseIf scene_l.Visible = True Then
        If m_t > 0 Then mj_u = True
        If m_t < 6500 Then mj_d = True
        If m_l > 4000 Then mj_l = True
        If m_l < 9200 Then mj_r = True
    End If
    If KeyCode = 37 Or KeyCode = 65 Then '按下←或A
        If mj_l Then
            m_l = m_l - 100
            marchman1.Left = m_l
            marchman2.Left = m_l
            marchman1.Visible = (1 = (t Mod 2))
            marchman2.Visible = (0 = (t Mod 2))
        End If
    ElseIf KeyCode = 38 Or KeyCode = 87 Then '按下↑或W
        If mj_u Then
            m_t = m_t - 100
            marchman1.Top = m_t
            marchman2.Top = m_t
            marchman1.Visible = (1 = (t Mod 2))
            marchman2.Visible = (0 = (t Mod 2))
        End If
    ElseIf KeyCode = 39 Or KeyCode = 68 Then  '按下→或D
        If mj_r Then
            m_l = m_l + 100
            marchman1.Left = m_l
            marchman2.Left = m_l
            marchman1.Visible = (1 = (t Mod 2))
            marchman2.Visible = (0 = (t Mod 2))
        End If
    ElseIf KeyCode = 40 Or KeyCode = 83 Then  '按下↓或S
        If mj_d Then
            m_t = m_t + 100
            marchman1.Top = m_t
            marchman2.Top = m_t
            marchman1.Visible = (1 = (t Mod 2))
            marchman2.Visible = (0 = (t Mod 2))
        End If
    ElseIf KeyCode = 13 Then '回车
        If jieju = 11 Then '上
        scene_u.Visible = False
        end_u1.Visible = True
        end_u1.ZOrder
    ElseIf jieju = 12 Then
        scene_u.Visible = False
        end_u2.Visible = True
        end_u2.ZOrder
    ElseIf jieju = 22 Then '下下
        scene_d.Visible = False
        end_dd.Visible = True
        end_dd.ZOrder
    ElseIf jieju = 231 Then '下←
        scene_dl.Visible = False
        end_dl1.Visible = True
        end_dl1.ZOrder
    ElseIf jieju = 232 Then
        scene_dl.Visible = False
        end_dl2.Visible = True
        end_dl2.ZOrder
    ElseIf jieju = 241 Then '下右
        scene_dr.Visible = False
        end_dr1.Visible = True
        end_dr1.ZOrder
    ElseIf jieju = 242 Then
        scene_dr.Visible = False
        end_dr2.Visible = True
        end_dr2.ZOrder
    ElseIf jieju = 41 Then '右
        scene_r.Visible = False
        end_r1.Visible = True
        end_r1.ZOrder
    ElseIf jieju = 42 Then
        scene_r.Visible = False
        end_r2.Visible = True
        end_r2.ZOrder
    ElseIf jieju = 43 Then
        scene_r.Visible = False
        end_r3.Visible = True
        end_r3.ZOrder
    ElseIf jieju = 31 Then '←
        scene_l.Visible = False
        end_l1.Visible = True
        end_l1.ZOrder
    ElseIf jieju = 32 Then
        scene_l.Visible = False
        end_l2.Visible = True
        end_l2.ZOrder
    ElseIf jieju = 34 Then
        scene_l.Visible = False
        end_l4.Visible = True
        end_l4.ZOrder
    ElseIf jieju = 35 Then
        scene_l.Visible = False
        end_l5.Visible = True
        end_l5.ZOrder
    End If
    If scene0.Visible = True Then '场景0
        If m_t = 0 Then '上路
            scene0.Visible = False
            scene_u.Visible = True
            scene_u.ZOrder
            marchman2.ZOrder: marchman1.ZOrder
            m_l = 4500: m_t = 6300
            marchman1.Left = m_l: marchman2.Left = m_l
            marchman1.Top = m_t: marchman2.Top = m_t
            Label.Caption = "作者：" + vbCrLf + "        人生处处充满选择，再次做出选择吧！"
        ElseIf m_t = 6400 Then '下路
            scene0.Visible = False
            scene_d.Visible = True
            scene_d.ZOrder
            marchman2.ZOrder: marchman1.ZOrder
            m_l = 4500: m_t = 100
            marchman1.Left = m_l: marchman2.Left = m_l
            marchman1.Top = m_t: marchman2.Top = m_t
        ElseIf m_l < 0 Then '左边
            scene0.Visible = False
            scene_l.Visible = True
            p_1.Visible = True
            scene_l.ZOrder: p_1.ZOrder
            marchman2.ZOrder: marchman1.ZOrder
            m_l = 7000: m_t = 3200
            marchman1.Left = m_l: marchman2.Left = m_l
            marchman1.Top = m_t: marchman2.Top = m_t
            Label.Caption = "作者：" + vbCrLf + "        你要拯救那个笼子里的人吗？"
            yes.Visible = True: no.Visible = True
            yes.Caption = "按套路，应该救"
            no.Caption = "丑拒……"
            yes.Value = False: no.Value = False
            talk1.ZOrder: talk2.ZOrder
            bad_1.ZOrder
        ElseIf m_l > 9200 Then '右边
            scene0.Visible = False
            scene_r.Visible = True
            scene_r.ZOrder
            marchman2.ZOrder: marchman1.ZOrder
            m_l = 1800: m_t = 1100
            marchman1.Left = m_l: marchman2.Left = m_l
            marchman1.Top = m_t: marchman2.Top = m_t
            Label.Caption = "        啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊"
            face2.Visible = True
        End If
    ElseIf scene_u.Visible = True Then '场景u
        'Dim u_judge, u_time, u_direction As Integer 1上2下3左4右
        u_last = u_direction
        If m_t = 0 Then '上路
            If u_direction = 2 Then
                MsgBox "不能走回头路", vbInformation, "Warning!"
            Else
                m_l = 4500: m_t = 6300
                marchman1.Left = m_l: marchman2.Left = m_l
                marchman1.Top = m_t: marchman2.Top = m_t
                u_time = u_time + 1
                u_direction = 1
            End If
        ElseIf m_t = 6400 Then '下路
            If u_direction = 1 Then
                MsgBox "不能走回头路", vbInformation, "Warning!"
            Else
                m_l = 4500: m_t = 100
                marchman1.Left = m_l: marchman2.Left = m_l
                marchman1.Top = m_t: marchman2.Top = m_t
                u_time = u_time + 1
                u_direction = 2
            End If
        End If
        If m_l <= 0 Then '左边
            If u_direction = 4 Then
                MsgBox "不能走回头路", vbInformation, "Warning!"
            Else
                m_l = 9100: m_t = 3200
                marchman1.Left = m_l: marchman2.Left = m_l
                marchman1.Top = m_t: marchman2.Top = m_t
                u_time = u_time + 1
                u_direction = 3
            End If
        ElseIf m_l >= 9200 Then '右边
            If u_direction = 3 Then
                MsgBox "不能走回头路", vbInformation, "Warning!"
            Else
                m_l = 100: m_t = 3200
                marchman1.Left = m_l: marchman2.Left = m_l
                marchman1.Top = m_t: marchman2.Top = m_t
                u_time = u_time + 1
                u_direction = 4
            End If
        End If
    ElseIf scene_d.Visible = True Then '场景d
        If m_t = 0 Then
            MsgBox "你没有机会后悔", vbInformation, "Sorry"
        ElseIf m_t = 6400 Then '正道
            scene_d.Visible = False
            scene_dd.Visible = True
            scene_dd.ZOrder
            marchman2.ZOrder: marchman1.ZOrder
            m_l = 4500: m_t = 100
            marchman1.Left = m_l: marchman2.Left = m_l
            marchman1.Top = m_t: marchman2.Top = m_t
        ElseIf m_l = 0 Then '禁止
            scene_d.Visible = False
            scene_dl.Visible = True
            scene_dl.ZOrder
            marchman2.ZOrder: marchman1.ZOrder
            m_l = 9000: m_t = 3200
            marchman1.Left = m_l: marchman2.Left = m_l
            marchman1.Top = m_t: marchman2.Top = m_t
            Label.Caption = "作者：" + vbCrLf + "        你来到了一块不毛之地。"
        ElseIf m_l = 9200 Then '捷径
            scene_d.Visible = False
            scene_dr.Visible = True
            scene_dr.ZOrder
            marchman2.ZOrder: marchman1.ZOrder
            m_l = 100: m_t = 3200
            marchman1.Left = m_l: marchman2.Left = m_l
            marchman1.Top = m_t: marchman2.Top = m_t
        End If
    ElseIf scene_l.Visible = True Then '场景l
        If yes.Value = False And no.Value = False Then
            MsgBox "你还没有做出选择", vbInformation, "你逗我呢"
            yes.Value = False: no.Value = False
        Else
            If p_1.Visible = True And bad_1.Visible = False Then
                If no.Value = True Then MsgBox "不救也得救！", vbInformation, "来自作者的恐吓"
                bad_1.Visible = True
                yes.Value = False: no.Value = False
                Label.Caption = "这时出现了一个人……" + vbCrLf + "        你是否执意要救 它 。"
                yes.Caption = "是的，我愿意"
                no.Caption = "那个啥 我想上厕所"
            ElseIf bad_1.Visible = True And bad_2.Visible = False Then
                If no.Value = True Then
                    jieju = 34
                    yes.Visible = False: no.Visible = False
                ElseIf yes.Value = True Then
                    bad_2.Visible = True
                    bad_2.ZOrder
                    yes.Value = False: no.Value = False
                    Label.Caption = "那厮掏出了一把明晃晃的小刀刀！" + vbCrLf + "        你还要爱着那个女孩吗？"
                    yes.Caption = "双手接白刃！"
                    no.Caption = "哼-待会再来收拾你"
                End If
            ElseIf bad_2.Visible = True And knife.Visible = False Then
                If no.Value = True Then
                    jieju = 35
                    yes.Visible = False: no.Visible = False
                ElseIf yes.Value = True Then
                    yes.Value = False: no.Value = False
                    knife.Visible = True
                    knife.ZOrder
                    Label.Caption = "坏人从腰间拔出了一把长达40M的大刀" + vbCrLf + "        你还是快跑吧-"
                    face2.Visible = True
                    yes.Caption = "我不会丢下公主走的！"
                    no.Caption = "我一定会回来的！~~"
                    l_time = 0
                End If
            ElseIf knife.Visible = True Then
                If no.Value = True Then
                    MsgBox "明智的选择", vbInformation, "作者的赞叹"
                    p_1.Visible = False
                    bad_1.Visible = False
                    bad_2.Visible = False
                    knife.Visible = False
                    p_2.Visible = True
                    p_2.ZOrder
                    Label.Caption = "        几分钟后，坏人走了，你救出了公主"
                    yes.Visible = False: no.Visible = False
                ElseIf yes.Value = True Then
                    jieju = 32
                    yes.Visible = False: no.Visible = False
                End If
            End If
        End If
    End If
    End If
End Sub
