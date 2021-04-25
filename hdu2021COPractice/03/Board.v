`timescale 1ns / 1ps
module Board(
    input [32:1] sw,
    input [6:1] swb,
    output [32:1] led,
    input clk,
    output [2:0] which,
    output [7:0] seg,
    output reg enable = 1
);

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
    reg cnt1, cnt6;
    
    wire [SIZE:1]R_Data_A;//A端口读出数据
    wire [SIZE:1]R_Data_B;//B端口读出数据
    wire [SIZE:1]R_Data_C;//C端口读出数据

    always #10 Clk=~Clk;
	initial begin
        Clk = 0;
        cnt1 = 0;
        cnt6 = 0;
        Clr = 0;
	end
	
    always @(posedge swb[1])begin
        if(swb[2]==1)begin
            cnt1 += 1;
            if (cnt == 1) begin
                R_Addr_A = sw[31:28];
                R_Addr_B = sw[26:23];
                R_Addr_C = sw[22:19];
                M[4:0] = sw[15:12];
                W_Addr = sw[9:6];
                Write_Reg = sw[1];
                Write_PC = sw[0];
            end
			else if (cnt == 2) begin
                W_Data = sw[31:0];
			end
			else if (cnt == 3) begin
                PC_New = sw[31:0];
			end
		end
    end
    always @(posedge swb[3])begin
        Clr = 1;
    end
    always @(posedge swb[4])begin
        // 手动始终输入
    end
    always @(posedge swb[4])begin
        cnt6 += 1;
        if (cnt6 == 1) begin
            Display Display_instance(.clk(clk),.data(R_Data_A),.which(which),.seg(seg));
        end
        else if (cnt6 == 2) begin
            Display Display_instance(.clk(clk),.data(R_Data_B),.which(which),.seg(seg));
        end
        else if (cnt6 == 3) begin
            Display Display_instance(.clk(clk),.data(R_Data_C),.which(which),.seg(seg));
        end
        else if (cnt6 == 4) begin
            // R15
            Display Display_instance(.clk(clk),.data(R_Data_C),.which(which),.seg(seg));
        end
        else if (cnt6 == 5) begin
            Display Display_instance(.clk(clk),.data(0),.which(which),.seg(seg));
        end
        else if (cnt6 == 6) begin
            // reset
            cnt6 = 0;
        end
    end

	// always @(posedge swb[2])begin
	// 	cnt=0;
	// end
    Multi_Reg Multi_Reg_instance(Clk,Clr,
      M,
      Write_PC,PC_New,
      Write_Reg,R_Addr_A,R_Addr_B,R_Addr_C,W_Addr,W_Data,
      R_Data_A,R_Data_B,R_Data_C,
    );
	// assign led=F;
	assign led[31:29]=cnt1;
	assign led[3:0]=cnt6;
    
    //always @(posedge swb[4])enable<=~enable;

endmodule // Board