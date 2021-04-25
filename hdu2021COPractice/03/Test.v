`timescale 1ns / 1ps

module Test();
    parameter ADDR = 4;//寄存器编码/地址位宽
    parameter NUMB = 1<<ADDR;//寄存器个数
    parameter SIZE = 32;//寄存器数据位宽
    
    reg [4:0]M;//工作模式
    reg Write_PC;// 
    reg PC_New;//
    reg Clk;//写入时钟信号
    reg Clr;//清零信号
    reg Write_Reg;//写控制信号
    reg [ADDR:1]R_Addr_A;//A端口读寄存器地址
    reg [ADDR:1]R_Addr_B;//B端口读寄存器地址
    reg [ADDR:1]R_Addr_C;//C端口读寄存器地址
    reg [ADDR:1]W_Addr;//写寄存器地址
    reg [SIZE:1]W_Data;//写入数据
    
    wire [SIZE:1]R_Data_A;//A端口读出数据
    wire [SIZE:1]R_Data_B;//B端口读出数据
    wire [SIZE:1]R_Data_C;//c端口读出数据

    // ALU32 ALU32_Instance(.OP(OP),.A(A),.B(B),.SCO(SCO),.CF(CF),.VF(VF),.F(F),.N(N),.Z(Z),.C(C),.V(V));
    always #10 Clk=~Clk;
    Multi_Reg Multi_Reg_instance(Clk,Clr,
      M,
      Write_PC,PC_New,
      Write_Reg,R_Addr_A,R_Addr_B,R_Addr_C,W_Addr,W_Data,
      R_Data_A,R_Data_B,R_Data_C,
    );
    initial begin
        Clk = 0;
        M <= 5'b10000;
        Write_PC <= 0;
        PC_New <= 0;
        Clr <= 0;
        W_Addr <= 0;
        W_Data <= 1;
        Write_Reg <= 1;
        R_Addr_A <= 0;
        R_Addr_B <= 8;
        R_Addr_C <= 13;
        #50
        M <= 5'b10001;
        W_Addr <= 8;
        W_Data <= 2;
        #50
        M <= 5'b10010;
        W_Addr <= 13;
        W_Data <= 3;
        #50
        M <= 5'b11111;
    end

endmodule
