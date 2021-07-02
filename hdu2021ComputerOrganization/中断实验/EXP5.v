`timescale 1ns / 1ps

module MOVS(
    input clk,
    input rst,
    input [31:0] IR,
    
    output reg Write_Reg,
    output reg Write_PC,
    output reg Write_IR,
    output reg Write_CPSR,
    output reg S,
    output reg SP_in,
    output reg SP_out,
    output reg ALU_A_s,
    output reg rt_rd_s,
    output reg Reg_C_s,
    output reg BitCount_Reg_list,
    output reg [1:0] W_Rdata_s,
    output reg [1:0] rd_s,
    output reg [2:0] W_CPSR_s,
    output reg [2:0] ALU_B_s,
    output reg [3:0] PC_s,
    output reg [3:0] ALU_OP,
    output reg [3:0] rt_rd_out,
    output reg [4:0] ST,
    output reg [4:0] Next_ST

    );
    reg [3:0] block_index,turn;
    
    parameter 
        Idle = 6'b000000,
        S0 = 6'b000001,
        S1 = 6'b000010,
        S2 = 5'b00011, 
        S3 = 5'b00100, 
        S4 = 5'b00101, 
        S5 = 5'b00110, 
        S6 = 5'b00111,
        S7 = 5'b01000,
        S8 = 5'b01001,
        S9 = 5'b01010,
        S10 = 5'b01011,
        S11 = 5'b01100,
        S12 = 5'b01101,
        S13 = 5'b01110,
        S14 = 5'b01111,
        S15 = 5'b10000,
        S16 = 5'b10001,
        S17 = 5'b10010,
        S18 = 5'b10011,
        S19 = 6'b010100,
        S20 = 6'b010101,
        S21 = 6'b010110,
        S22 = 6'b010111,
        S26 = 6'b011011,
        S27 = 6'b011100,
        S28 = 6'b011101;
    
    always @(posedge rst or posedge clk)  begin
	  if (rst) ST <= Idle;
      else  ST <= Next_ST;
    end
    
    always @(*) begin	
        Next_ST = Idle;
        case (ST)
            Idle: Next_ST = S0;
            S0: Next_ST = S1;
            S1:
                if (IR[27:25] == 3'b100)
                    Next_ST = S19; 
                else Next_ST = S28;
            S27: 
                Next_ST = S0;
            S28: Next_ST = S26;
            S26: Next_ST = S27;
            default:  Next_ST = S0; 
        endcase
    end
    
    
    always @(posedge rst or posedge clk) begin
        if (rst) begin
        end
        else
            case(Next_ST)
                S0: begin
                    Write_PC <= 1;
                    PC_s <= 3'b000;
                    Write_IR <= 1;
                end
                S1:;
                S26: begin
                   W_Rdata_s <= 0;
                   Write_CPSR <= 1;
                   W_CPSR_s <= 0;
                   S <= 0;
                   PC_s <= 2'b01;
                   SP_out <= 1;
                end
                S27: begin
                    SP_in <= 1;
                end
                S28: begin //MOVS
                   ALU_OP <= 4'b1000; 
                   S <= 1;
                end
            endcase
    end
endmodule
