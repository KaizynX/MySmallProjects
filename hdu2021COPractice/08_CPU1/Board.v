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

/*
    parameter ADDR = 4;
    parameter NUMB = 1<<ADDR;
    parameter SIZE = 32;
    reg [4:0]M;
    reg Write_PC;
    reg [SIZE:1]PC_New;
    reg Rst;
    reg Write_Reg;
    reg [ADDR:1]R_Addr_A;
    reg [ADDR:1]R_Addr_B;
    reg [ADDR:1]R_Addr_C;
    reg [ADDR:1]W_Addr;
    reg [SIZE:1]W_Data;
    reg [2:0]cnt1;
    reg [3:0]cnt6;
    reg [SIZE:1]Data;
    reg all0;
    
    wire [SIZE:1]R_Data_A;
    wire [SIZE:1]R_Data_B;
    wire [SIZE:1]R_Data_C;//C端口读出数据
    wire [SIZE:1]PC;

	initial begin
        M<=16;
        Write_PC<=0;
        PC_New<=0;
        Rst <= 0;
        Write_Reg<=0;
        R_Addr_A<=0;
        R_Addr_B<=0;
        R_Addr_C<=0;
        W_Addr<=0;
        W_Data<=0;
        cnt1 <= 0;
        cnt6 <= 0;
        Data<=0;
        all0 <= 0;

	end
	
    always @(posedge swb[1])begin
        if(swb[2]==1)begin
            cnt1 = cnt1+1;
            if (cnt1 == 1) begin
                R_Addr_A <= sw[32:29];
                R_Addr_B <= sw[27:24];
                R_Addr_C <= sw[23:20];
                M[3:0] <= sw[16:13];
                W_Addr <= sw[10:7];
                Write_Reg <= sw[2];
                Write_PC <= sw[1];
            end
			else if (cnt1 == 2) begin
                W_Data <= sw[32:1];
			end
			else if (cnt1 == 3) begin
                PC_New <= sw[32:1];
                cnt1=0;
			end
		end
    end
    
    always @(swb[3])begin
        Rst = swb[3];
    end

    always @(posedge swb[4])begin
        // 手动时钟输入
    end

    always @(posedge swb[6])begin
        cnt6 = cnt6+1;
        if (cnt6 == 1) begin
            Data <= R_Data_A;
            all0 <= 0;
        end
        else if (cnt6 == 2) begin
            Data <= R_Data_B;
            all0 <= 0;
        end
        else if (cnt6 == 3) begin
            Data <= R_Data_C;
            all0 <= 0;
        end
        else if (cnt6 == 4) begin
            Data <= PC;
            all0 <= 0;
        end
        else if (cnt6 == 5) begin // 8.8.8.8.8.8.8.8.
            all0 <= 1;
            cnt6 <= 0;
        end
    end

    Display Display_instance(.clk(clk),.data(Data),.which(which),.seg(seg),.all0(all0));
    Multi_Reg Multi_Reg_instance(clk,Rst,
      M,
      Write_PC,PC_New,
      Write_Reg,R_Addr_A,R_Addr_B,R_Addr_C,W_Addr,W_Data,
      R_Data_A,R_Data_B,R_Data_C,PC
    );
    
    assign led[32:30]=cnt1;
	assign led[4:1]=cnt6;
    
    //always @(posedge swb[4])enable<=~enable;

*/
endmodule // Board