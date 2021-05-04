`timescale 1ns / 1ps
//寄存器堆模块

module Multi_Reg(
      Clk,Clr,
      M,
      Write_PC,PC_New,
      Write_Reg,R_Addr_A,R_Addr_B,R_Addr_C,W_Addr,W_Data,
      R_Data_A,R_Data_B,R_Data_C);
    parameter ADDR = 4;//寄存器编码/地址位宽
    parameter NUMB = 1<<ADDR;//寄存器个数
    parameter SIZE = 32;//寄存器数据位宽
    
    input [4:0]M;//工作模式
    input Write_PC;// 
    input PC_New;//
    input Clk;//写入时钟信号
    input Clr;//清零信号
    input Write_Reg;//写控制信号
    input [ADDR:1]R_Addr_A;//A端口读寄存器地址
    input [ADDR:1]R_Addr_B;//B端口读寄存器地址
    input [ADDR:1]R_Addr_C;//C端口读寄存器地址
    input [ADDR:1]W_Addr;//写寄存器地址
    input [SIZE:1]W_Data;//写入数据
    
    output [SIZE:1]R_Data_A;//A端口读出数据
    output [SIZE:1]R_Data_B;//B端口读出数据
    output [SIZE:1]R_Data_C;//B端口读出数据
    
    reg [SIZE:1] R[0:NUMB-1];
    /*
    reg [SIZE:1] R_fiq[8:12];
    reg [SIZE:1] R13[5'b10000:5'b11111];
    reg [SIZE:1] R14[5'b10000:5'b11111];
    */
    reg [SIZE:1] R_fiq[8:14];
    reg [SIZE:1] R_irq[13:14];
    reg [SIZE:1] R_abt[13:14];
    reg [SIZE:1] R_svc[13:14];
    reg [SIZE:1] R_und[13:14];
    reg [SIZE:1] R_mon[13:14];
    reg [SIZE:1] R_hyp[13:13];
    integer i;//用于遍历NUMB个寄存器
    
    initial begin//初始化NUMB个寄存器，全为0
        for(i=0;i<NUMB;i=i+1) R[i]<=0;
        /*
        for(i=8;i<13;i=i+1) R_fiq[i]<=0;
        for(i=16;i<32;i=i+1) R13[i]<=0;
        for(i=16;i<32;i=i+1) R14[i]<=0;
        */
        for(i=8;i<15;i=i+1) R_fiq[i]<=0;
        for(i=13;i<14;i=i+1) R_irq[i]<=0;
        for(i=13;i<14;i=i+1) R_abt[i]<=0;
        for(i=13;i<14;i=i+1) R_svc[i]<=0;
        for(i=13;i<14;i=i+1) R_und[i]<=0;
        for(i=13;i<14;i=i+1) R_mon[i]<=0;
        R_hyp[13]<=0;
    end
    always@(posedge Clk or posedge Clr)//时钟信号或清零信号上升沿
    begin
        if(Clr) begin//清零
            for(i=0;i<NUMB;i=i+1) R[i]<=0;
            /*
            for(i=8;i<13;i=i+1) R_fiq[i]<=0;
            for(i=16;i<32;i=i+1) R13[i]<=0;
            for(i=16;i<32;i=i+1) R14[i]<=0;
            */
            for(i=8;i<15;i=i+1) R_fiq[i]<=0;
            for(i=13;i<14;i=i+1) R_irq[i]<=0;
            for(i=13;i<14;i=i+1) R_abt[i]<=0;
            for(i=13;i<14;i=i+1) R_svc[i]<=0;
            for(i=13;i<14;i=i+1) R_und[i]<=0;
            for(i=13;i<14;i=i+1) R_mon[i]<=0;
            R_hyp[13]<=0;
        end
        else if (Write_Reg) begin//不清零,检测写控制, 高电平则写入寄存器
            case (M)
              5'b10000:begin //usr用户模式
                R[W_Addr] <= W_Data;
              end
              5'b11111:begin // sys系统
                R[W_Addr] <= W_Data;
              end
              5'b10001:begin // fiq快中断
                if (W_Addr < 8) R[W_Addr] <= W_Data;
                else R_fiq[W_Addr] <= W_Data;
              end
              5'b10010:begin // irq中断
                if (W_Addr < 13) R[W_Addr] <= W_Data;
                else R_irq[W_Addr] = W_Data;
              end
              5'b10011:begin // svc管理
                if (W_Addr < 13) R[W_Addr] <= W_Data;
                else R_svc[W_Addr] = W_Data;
              end
              5'b10110:begin // mon安全扩展
                if (W_Addr < 13) R[W_Addr] <= W_Data;
                else R_mon[W_Addr] = W_Data;
              end
              5'b10111:begin // abt中止
                if (W_Addr < 13) R[W_Addr] <= W_Data;
                else R_abt[W_Addr] = W_Data;
              end
              5'b11010:begin // hyp(非安全)虚拟扩展
                if (W_Addr < 13) R[W_Addr] <= W_Data;
                else R_hyp[W_Addr] = W_Data;
              end
              5'b11011:begin // und未定义
                if (W_Addr < 13) R[W_Addr] <= W_Data;
              end
            endcase
        end
        else if (Write_PC) begin
            R[15] <= PC_New;
        end
    end
    
    //读操作没有使能或时钟信号控制, 使用数据流建模(组合逻辑电路,读不需要时钟控制)
    // assign R_Data_A=REG_Files[R_Addr_A];
    // assign R_Data_B=REG_Files[R_Addr_B];
    // assign R_Data_C=REG_Files[R_Addr_C];
    case (M)
      5'b10000:begin //usr用户模式
        assign R_Data_A = R[R_Addr_A];
        assign R_Data_B = R[R_Addr_B];
        assign R_Data_C = R[R_Addr_C];
      end
      5'b11111:begin // sys系统
        assign R_Data_A = R[R_Addr_A];
        assign R_Data_B = R[R_Addr_B];
        assign R_Data_C = R[R_Addr_C];
      end
      5'b10001:begin // fiq快中断
        if (R_Addr_A < 8) assign R_Data_A = R[R_Addr_A];
        else assign R_Data_A = R_fiq[R_Addr_A];
        if (R_Addr_B < 8) assign R_Data_B = R[R_Addr_B];
        else assign R_Data_B = R_fiq[R_Addr_B];
        if (R_Addr_C < 8) assign R_Data_C = R[R_Addr_C];
        else assign R_Data_C = R_fiq[R_Addr_C];
      end
      5'b10010:begin // irq中断
        if (R_Addr_A < 13) assign R_Data_A = R[R_Addr_A];
        else assign R_Data_A = R_irq[R_Addr_A];
        if (R_Addr_B < 13) assign R_Data_B = R[R_Addr_B];
        else assign R_Data_B = R_irq[R_Addr_B];
        if (R_Addr_C < 13) assign R_Data_C = R[R_Addr_C];
        else assign R_Data_C = R_irq[R_Addr_C];
      end
      5'b10011:begin // svc管理
        if (R_Addr_A < 13) assign R_Data_A = R[R_Addr_A];
        else assign R_Data_A = R_svc[R_Addr_A];
        if (R_Addr_B < 13) assign R_Data_B = R[R_Addr_B];
        else assign R_Data_B = R_svc[R_Addr_B];
        if (R_Addr_C < 13) assign R_Data_C = R[R_Addr_C];
        else assign R_Data_C = R_svc[R_Addr_C];
      end
      5'b10110:begin // mon安全扩展
        if (R_Addr_A < 13) assign R_Data_A = R[R_Addr_A];
        else assign R_Data_A = R_mon[R_Addr_A];
        if (R_Addr_B < 13) assign R_Data_B = R[R_Addr_B];
        else assign R_Data_B = R_mon[R_Addr_B];
        if (R_Addr_C < 13) assign R_Data_C = R[R_Addr_C];
        else assign R_Data_C = R_mon[R_Addr_C];
      end
      5'b10111:begin // abt中止
        if (R_Addr_A < 13) assign R_Data_A = R[R_Addr_A];
        else assign R_Data_A = R_abt[R_Addr_A];
        if (R_Addr_B < 13) assign R_Data_B = R[R_Addr_B];
        else assign R_Data_B = R_abt[R_Addr_B];
        if (R_Addr_C < 13) assign R_Data_C = R[R_Addr_C];
        else assign R_Data_C = R_abt[R_Addr_C];
      end
      5'b11010:begin // hyp(非安全)虚拟扩展
        if (R_Addr_A < 13) assign R_Data_A = R[R_Addr_A];
        else assign R_Data_A = R_hyp[R_Addr_A];
        if (R_Addr_B < 13) assign R_Data_B = R[R_Addr_B];
        else assign R_Data_B = R_hyp[R_Addr_B];
        if (R_Addr_C < 13) assign R_Data_C = R[R_Addr_C];
        else assign R_Data_C = R_hyp[R_Addr_C];
      end
    endcase
endmodule