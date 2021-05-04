`timescale 1ns / 1ps

module ALU(ALU_OP,A,B,Shift_carry_out,CF,VF,F,N,Z,C,V);
    input [3:0] ALU_OP;  //运算操作
    input [31:0] A;      //左运算数
    input [31:0] B;      //右运算数
    input Shift_carry_out;
    input CF;
    input VF;
    output reg [31:0] F;  //运算结果
    output reg N;         //符号标志为
    output reg Z;         //零标志位
    output reg C;         //进借标志位
    output reg V;         //溢出标志位
    reg C32;
    always@(*)
    begin
      case(ALU_OP)
        4'b0000:begin 
                  F <= A & B;
                  C <= Shift_carry_out; 
                  V <= VF;
                end
        4'b0001:begin 
                  F <= A ^ B;
                  C <= Shift_carry_out; 
                  V <= VF;
                end
        4'b0010:begin 
                  {C32,F} = A - B;
                  C = ~C32; 
                  V = A[31] ^ B[31] ^ F[31] ^ C32;
                end
        4'b0011:begin 
                  {C32,F} = B - A;
                  C = ~C32; 
                  V = A[31] ^ B[31] ^ F[31] ^ C32;
                end
        4'b0100:begin
                  {C32,F} = A + B;
                  C = C32; 
                  V = A[31] ^ B[31] ^ F[31] ^ C32;
                end
        4'b0101:begin 
                  {C32,F} = A + B + CF;
                  C = C32; 
                  V = A[31] ^ B[31] ^ F[31] ^ C32;
                end
        4'b0110:begin
                  {C32,F} = A - B + CF - 1;
                  C = ~C32; 
                  V = A[31] ^ B[31] ^ F[31] ^ C32;
                end
        4'b0111:begin 
                  {C32,F} = B - A + CF - 1;
                  C = ~C32; 
                  V = A[31] ^ B[31] ^ F[31] ^ C32;
                end
        4'b1000:begin
                  F <= A;
                  C <= Shift_carry_out; 
                  V <= VF;
                end
        4'b1010:begin 
                  {C32,F} = A - B + 4;
                  C = ~C32; 
                  V = A[31] ^ B[31] ^ F[31] ^ C32;
                end
        4'b1100:begin 
                  F <= A | B; 
                  C <= Shift_carry_out;
                  V <= VF;
                end
        4'b1101:begin 
                  F <= B;
                  C <= Shift_carry_out;
                  V <= VF; 
                end
        4'b1110:begin 
                  F <= A & (~B);
                  C <= Shift_carry_out;
                  V <= VF; 
                end
        4'b1111:begin 
                  F <= ~B;
                  C <= Shift_carry_out;
                  V <= VF; 
                end
      endcase
        N = F[31];
        Z = F == 0;
    end
endmodule
