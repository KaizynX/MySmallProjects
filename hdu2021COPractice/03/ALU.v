`timescale 1ns / 1ps

module ALU32(
    input [3:0] OP,
    input [32:1] A,
    input [32:1] B,
    input SCO,
    input CF,
    input VF,
    output reg [32:1] F,
    output reg N,
    output reg Z,
    output reg C,
    output reg V
);

    
    always@(*)begin

        C=SCO;
        V=VF;
        case(OP)
            4'b0000:begin
                F=A&B;
            end
            4'b0001:begin
                F=A^B;
            end
            4'b0010:begin
                {C,F}=A-B;
                V = A[32]^B[32]^F[32]^C;
                C=~C;
            end
            4'b0011:begin
                {C,F}=B-A;
                V = A[32]^B[32]^F[32]^C;
                C=~C;
            end
            4'b0100:begin
                {C,F}=A+B;
                V = A[32]^B[32]^F[32]^C;
            end
            4'b0101:begin
                {C,F}=A+B+CF;
                V = A[32]^B[32]^F[32]^C;
            end
            4'b0110:begin
                {C,F}=A-B+CF-1;
                V = A[32]^B[32]^F[32]^C;
                C=~C;
            end
            4'b0111:begin
                {C,F}=B-A+CF-1;
                V = A[32]^B[32]^F[32]^C;
                C=~C;
            end
            4'b1000:begin
                F=A;
            end
            4'b1010:begin
                {C,F}=A-B+4;
                V = A[32]^B[32]^F[32]^C;
                C=~C;
            end
            4'b1100:begin
                F=A|B;
            end
            4'b1101:begin
                F=B;
            end
            4'b1110:begin
                F=A&(~B);
            end
            4'b1111:begin
                F=~B;
            end
        endcase
        Z = F==0;
        N = F[32];
    end
endmodule
