module top(
    input clk,
    input rst,
    input CPSR_6,
    input CPSR_7,
    input EX_irq,
    input EX_fiq,
    input [31:0] INT_Vector,
    input Write_PC,
    
    output INT_irq,
    output INTA_irq,
    output INT_fiq,
    output INTA_fiq,
    output [1:0]PC_s,
    output [31:0] PC

    );
    
    requestfiq requestfiq(
        .CPSR_6(CPSR_6),
        .INTA_fiq(INTA_fiq),
        .EX_fiq(EX_fiq),
        .INT_fiq(INT_fiq)
    );

    request request(
        .CPSR_7(CPSR_7),
        .INTA_irq(INTA_irq),
        .EX_irq(EX_irq),
        .INT_irq(INT_irq),
        .INT_fiq(INT_fiq)
    );
    
    decode decode_mod(
        .clk(clk),
        .INT_irq(INT_irq),
        .INT_fiq(INT_fiq),
        .INTA_irq(INTA_irq),
        .INTA_fiq(INTA_fiq),
        .PC_s(PC_s)
    );   
endmodule


module d_flip_flop(
    input d,
    input clk,
    input clr,
    output reg q
    );
        
    always@ (posedge clk or posedge clr) begin
        if(clr) begin
            q <= 0; 
        end
        else begin
            q <= d;
        end
    end
    
endmodule

module request(
    input CPSR_7,
    input INTA_irq,
    input EX_irq,
    input INT_fiq,
    
    output INT_irq,
    output Q
    );
    
    //wire Q;
    d_flip_flop D1(
        .d(1'b1),
        .clk(~CPSR_7),
        .clr(INTA_irq),
        .q(Q)
    );
    
    d_flip_flop D2(
        .d(Q),
        .clk(EX_irq),
        .clr(INTA_irq),
        .q(INT_irq_t)
    );
    assign  INT_irq = ~INT_fiq & INT_irq_t;
endmodule

module requestfiq(
    input CPSR_6,
    input INTA_fiq,
    input EX_fiq,
    
    output INT_fiq,
    output Q
    );
    
    //wire Q;
    
    d_flip_flop D1(
        .d(1'b1),
        .clk(~CPSR_6),
        .clr(INTA_fiq),
        .q(Q)
    );
    
    d_flip_flop D2(
        .d(Q),
        .clk(EX_fiq),
        .clr(INTA_fiq),
        .q(INT_fiq)
    );
endmodule

module decode(
    input clk,
    input INT_irq,
    input INT_fiq,
    
    output reg INTA_irq,
    output reg INTA_fiq,
    output reg [1:0]PC_s,
    output reg Write_PC
    );
    always@(posedge clk) begin
        if(INT_irq) begin
            INTA_irq <= 1;
            PC_s <= 2'b11;
            Write_PC <= 1;
        end
        else if(INT_fiq) begin
            INTA_fiq <= 1;
            PC_s <= 2'b11;
            Write_PC <= 1;
        end
        else begin
            INTA_fiq <= 0;
            INTA_irq <= 0;
            PC_s <= 2'b00;
            Write_PC <= 0;
        end
    end
endmodule