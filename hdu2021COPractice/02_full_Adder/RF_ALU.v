`timescale 1ns / 1ps
//寄存器堆+ALU组合模块
module RF_ALU(
        Clk,Clr,Write_Reg,Write_Select,//控制信号
        R_Addr_A,R_Addr_B,R_Addr_C,W_Addr,//读写地址
        Input_Data,R_Data_A,R_Data_B,R_Data_C,//数据IO
        OP,ZF,CF,OF,SF,PF,F//ALU运算
        );
    parameter ADDR = 4;//地址位宽
    parameter SIZE = 32;//数据位宽
    
    //寄存器堆
    input Clk, Clr;//写入时钟信号, 清零信号
    input Write_Reg;//写控制信号
    input [ADDR:1]R_Addr_A;//A读端口寄存器地址
    input [ADDR:1]R_Addr_B;//B读端口寄存器地址
    input [ADDR:1]R_Addr_C;//C读端口寄存器地址
    input [ADDR:1]W_Addr;//写寄存器地址
    input [SIZE:1]Input_Data;//外部输入数据
    
    output [SIZE:1]R_Data_A;//A端口读出数据
    output [SIZE:1]R_Data_B;//B端口读出数据
    output [SIZE:1]R_Data_C;//B端口读出数据
    
    //ALU
    input [3:0] OP;//运算符编码
    output ZF,//零标志
           CF,//进借位标志(只对无符号数运算有意义)
           OF,//溢出标志(只对有符号数运算有意义)
           SF,//符号标志(只对有符号数运算有意义)
           PF;//奇偶标志
    output [SIZE:1]F;//运算结果F
    
    input Write_Select;//写入数据选择信号
    wire [SIZE:1]ALU_F;//ALU运算结果中间变量
    wire [SIZE:1]W_Data;//写入数据

    //Write_Select高电平则写外部输入，否则写运算结果
    assign W_Data=Write_Select ? Input_Data : ALU_F;
    assign F = ALU_F;//输出运算结果F

    //实例化寄存器堆模块
    RegFile RF_Test(
        //输入
        .Clk(Clk),//时钟信号
        .Clr(Clr),//清零信号
        .Write_Reg(Write_Reg),//写入控制
        .R_Addr_A(R_Addr_A),//A端口读地址
        .R_Addr_B(R_Addr_B),//B端口读地址
        .R_Addr_C(R_Addr_C),//C端口读地址
        .W_Addr(W_Addr),//写入地址
        .W_Data(W_Data),//写入数据, 由外部或ALU输入
        
        //输出
        .R_Data_A(R_Data_A),//A端口读出数据
        .R_Data_B(R_Data_B)//B端口读出数据
        .R_Data_C(R_Data_C)//C端口读出数据
    );   
       
    //实例化ALU模块
    ALU ALU_Test(
        //输入
        .OP(OP),//运算符
        
        .A(R_Data_A),//从寄存器读A操作数
        .B(R_Data_B),//从寄存器读B操作数
        .F(ALU_F),//ALU_F作为中间变量暂存运算结果，与Input_Data选择输入寄存器
        
        //输出
        .ZF(ZF),//零标志
        .CF(CF),//进借位标志(只对无符号数运算有意义)
        .OF(OF),//溢出标志(只对有符号数运算有意义)
        .SF(SF),//符号标志(只对有符号数运算有意义)
        .PF(PF)//奇偶标志
    );
endmodule