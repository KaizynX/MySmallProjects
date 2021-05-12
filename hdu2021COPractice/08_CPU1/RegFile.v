`timescale 1ns / 1ps
//寄存器堆模块
module RegFile(
	Clk,
	Rst,
	Write_Reg,
	R_Addr_A,
	R_Addr_B,
	R_Addr_C,
	W_Addr,
	W_Data,
	R_Data_A,
	R_Data_B,
	R_Data_C
);
    parameter ADDR = 4;//寄存器编�?/地址位宽
    parameter NUMB = 1<<ADDR;//寄存器个�?
    parameter SIZE = 32;//寄存器数据位�?
    
    input Clk;//写入时钟信号
    input Rst;//清零信号
    input Write_Reg;//写控制信�?
    input [ADDR:1]R_Addr_A;//A端口读寄存器地址
    input [ADDR:1]R_Addr_B;//B端口读寄存器地址
    input [ADDR:1]R_Addr_C;//C端口读寄存器地址
    input [ADDR:1]W_Addr;//写寄存器地址
    input [SIZE:1]W_Data;//写入数据
    
    output [SIZE:1]R_Data_A;//A端口读出数据
    output [SIZE:1]R_Data_B;//B端口读出数据
    output [SIZE:1]R_Data_C;//B端口读出数据
    
    reg [SIZE:1]REG_Files[0:NUMB-1];//寄存器堆本体
    integer i;//用于遍历NUMB个寄存器
    
    initial//初始化NUMB个寄存器，全�?0
        for(i=0;i<NUMB;i=i+1) REG_Files[i]<=0;
    always@(posedge Clk or posedge Rst)//时钟信号或清零信号上升沿
    begin
        if(Rst)//清零
                for(i=0;i<NUMB;i=i+1) REG_Files[i]<=0;
        else//不清�?,�?测写控制, 高电平则写入寄存�?
                if(Write_Reg) REG_Files[W_Addr]<=W_Data;
    end
    
    //读操作没有使能或时钟信号控制, 使用数据流建�?(组合逻辑电路,读不�?要时钟控�?)
    assign R_Data_A=REG_Files[R_Addr_A];
    assign R_Data_B=REG_Files[R_Addr_B];
    assign R_Data_C=REG_Files[R_Addr_C];

endmodule