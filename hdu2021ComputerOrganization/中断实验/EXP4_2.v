module top (
    input clk,
    input rst,
    input Write_Reg, 

    input [2:0] Change_M,
    input [3:0] R_Addr_A,
    input [3:0] R_Addr_B,
    input [3:0] R_Addr_C,
    input [3:0] W_Addr,
    input [31:0] W_Data,
    
    input W_SPSR_s,
    input [2:0] W_CPSR_s,
    input Write_SPSR,
    input Write_CPSR,
    input [31:0] SPSR_New,
    input [31:0] CPSR_New,
    input [3:0] MASK,
    input [3:0] NZCV,
    input S,

    output [31:0] R_Data_A,
    output [31:0] R_Data_B,
    output [31:0] R_Data_C,
    output [31:0] SPSR_fiq,
    output [31:0] SPSR_irq,
    output [31:0] SPSR_abt,
    output [31:0] SPSR_svc,
    output [31:0] SPSR_und,
    output [31:0] SPSR_mon,
    output [31:0] SPSR_hyp,
    output [31:0] CPSR
);
    wire [31:0] PC_New, PC;
    register_pile reg1 (
        clk,
        rst,
        Write_PC,
        Write_Reg,
        SP_in,
        SP_out,
        Change_M,
        R_Addr_A,
        R_Addr_B,
        R_Addr_C,
        W_Addr,
        CPSR,
        W_Data,
        PC_New,
        R_Data_A,
        R_Data_B,
        R_Data_C,
        PC
    );

    Reg_CPSR CPSR1(
        clk, 
        W_SPSR_s,
        W_CPSR_s,
        Write_SPSR,
        Write_CPSR,
        SPSR_New,
        CPSR_New,
        MASK,
        NZCV,
        Change_M,
        S,
        SPSR_fiq,
        SPSR_irq,
        SPSR_abt,
        SPSR_svc,
        SPSR_und,
        SPSR_mon,
        SPSR_hyp,
        CPSR
    );


endmodule

module register_pile(
    input clk,
    input rst,
    input Write_PC,
    input Write_Reg, 
    input SP_in, 
    input SP_out, 
    input [2:0] Change_M,
    input [3:0] R_Addr_A,
    input [3:0] R_Addr_B,
    input [3:0] R_Addr_C,
    input [3:0] W_Addr,
    input [31:0] CPSR,
    input [31:0] W_Data,
    input [31:0] PC_New,

    
    output [31:0] R_Data_A,
    output [31:0] R_Data_B,
    output [31:0] R_Data_C,
    output [31:0] R15
    );
    
    reg [4:0] M;
    reg [31:0] REG_Pile [0:15];
    reg [31:0] REG_File_user [0:15];
    reg [31:0] REG_File_fiq [8:12];
    reg [31:0] R_fiq[13:14], R_svc[13:14],R_abt[13:14],R_irq[13:14],R_und[13:14],R_mon[13:14],R_hyp;
    
    integer i;
    
    always@(Change_M or CPSR[4:0]) begin
        case(Change_M)
            3'd0: M <= CPSR[4:0];
            3'd1: M <= 5'b10001; //fiq
            3'd2: M <= 5'b10010; //irq
            3'd3: M <= 5'b10011; //svc
            3'd4: M <= 5'b11011; //und
        endcase
    end
    
    always@ ( negedge clk)
    begin
        for(i=0;i<13;i=i+1)
            REG_Pile[i] <= REG_File_user[i];
        if(CPSR[1:0] == 2'b01)
            begin
                REG_Pile[8] <= REG_File_fiq[8];
                REG_Pile[9] <= REG_File_fiq[9];
                REG_Pile[10] <= REG_File_fiq[10];
                REG_Pile[11] <= REG_File_fiq[11];
                REG_Pile[12] <= REG_File_fiq[12];
            end
        case(M[3:0])
        //two ways selecter
    //user
            4'b0000:
                begin
                    REG_Pile[13] <= REG_File_user[13];
                    REG_Pile[14] <= REG_File_user[14];
                end
   //sys
            4'b1111:
                 begin
                   REG_Pile[13] <= REG_File_user[13];
                   REG_Pile[14] <= REG_File_user[14];
                end
    //fiq
            4'b0001:
                begin
                    REG_Pile[13] <= R_fiq[13];
                    REG_Pile[14] <= R_fiq[14];
                end
    //irq
            4'b0010:
                begin
                    REG_Pile[13] <= R_irq[13];
                    REG_Pile[14] <= R_irq[14];
                end
    //svc
            4'b0011:
                begin
                    REG_Pile[13] <= R_svc[13];
                    REG_Pile[14] <= R_svc[14];
                end
    //mon
            4'b0110:
                 begin
                    REG_Pile[13] <= R_mon[13];
                    REG_Pile[14] <= R_mon[14];
                end            
    //abt
            4'b0111:
                 begin
                    REG_Pile[13] <= R_abt[13];
                    REG_Pile[14] <= R_abt[14];
                end
    //hyp
            4'b1010:
                 begin
                    REG_Pile[13] <= R_hyp;
                end
    //und
            4'b1011:
                 begin
                   REG_Pile[13] <= R_und[13];
                   REG_Pile[14] <= R_und[14];
                end
             default:;
        endcase
    end
   
    always@ (negedge clk or posedge rst)
    begin   
        if(rst) begin
            for( i = 0;i < 16;i = i + 1)
            begin
                REG_Pile[i] <= 0;
                REG_File_user[i]<=0;
                REG_File_fiq[i]<=0;
                R_fiq[i] <= 0;
                R_svc[i] <= 0;
                R_abt[i] <= 0;
                R_irq[i] <= 0;
                R_und[i] <= 0;
                R_mon[i] <= 0;
            end
            R_hyp<=0;
        end
        else if(Write_Reg) begin
                //·ÖÅäÆ÷     
            if(W_Addr<8)
                REG_File_user[W_Addr] <= W_Data;
            else if(W_Addr>=8 && W_Addr<13)
                case(CPSR[1:0])
                    2'b01:REG_File_fiq[W_Addr] <= W_Data;
                    default:
                        REG_File_user[W_Addr] <= W_Data;
                endcase
            else
                case(M[3:0])
                    4'b0000:REG_File_user[W_Addr] <= W_Data;
                    4'b1111:REG_File_user[W_Addr] <= W_Data;
                    4'b0001:R_fiq[W_Addr] <= W_Data;
                    4'b0010:R_irq[W_Addr] <= W_Data;
                    4'b0011:R_svc[W_Addr] <= W_Data;
                    4'b0110:R_mon[W_Addr] <= W_Data;
                    4'b0111:R_abt[W_Addr] <= W_Data;
                    4'b1010:R_hyp <= W_Data;
                    4'b1011:R_und[W_Addr] <= W_Data;
                    default:;
                endcase
            if(Write_PC)
                REG_Pile[15] <= PC_New;
        end          
    end
    
    assign R_Data_A = REG_Pile[R_Addr_A];
    assign R_Data_B = REG_Pile[R_Addr_B];
    assign R_Data_C = REG_Pile[R_Addr_C];
    assign R15 = REG_Pile[15];
    
endmodule

module Reg_CPSR(
    input clk, 
    input W_SPSR_s,
    input [2:0] W_CPSR_s,
    input Write_SPSR,
    input Write_CPSR,
    input [31:0] SPSR_New,
    input [31:0] CPSR_New,
    input [3:0] MASK,
    input [3:0] NZCV,
    input [2:0] Change_M,
    input S,
    
    output [31:0] SPSR_fiq,
    output [31:0] SPSR_irq,
    output [31:0] SPSR_abt,
    output [31:0] SPSR_svc,
    output [31:0] SPSR_und,
    output [31:0] SPSR_mon,
    output [31:0] SPSR_hyp,
    output [31:0] CPSR
    );
    reg [31:0] Curr_SPSR, CPSR_in;
    wire [31:0] new_SPSR;
    reg [6:0] clk_m;
    reg [4:0] M;
    
    assign new_SPSR = (W_SPSR_s == 1)? CPSR : SPSR_New;
//    assign CPSR_in = (W_CPSR_s == 1)? CPSR_New : Curr_SPSR;
    
    always@(Change_M or CPSR[4:0]) begin
        case(Change_M)
            3'd0: M <= CPSR[4:0];
            3'd1: M <= 5'b10001; //fiq
            3'd2: M <= 5'b10010; //irq
            3'd3: M <= 5'b10011; //svc
            3'd4: M <= 5'b11011; //und
        endcase
    end
    
    always@(W_CPSR_s)begin
        case(W_CPSR_s)
            3'd0: CPSR_in <= Curr_SPSR;
            3'd1: CPSR_in <= CPSR_New;
            3'd2: CPSR_in <= {CPSR[31:8],8'h92}; //irq
            3'd3: CPSR_in <= {CPSR[31:8],8'hD1}; //fiq
            3'd4: CPSR_in <= {CPSR[31:8],8'h93}; //svc
            3'd5: CPSR_in <= {CPSR[31:8],8'h1B}; //und
        endcase
    end
    
    always@(M[4:0]) begin
        if(M[4]) begin
            case(M[3:0])
                4'b0001: begin 
                    clk_m = 7'b0000001; 
                    Curr_SPSR <= SPSR_fiq;
                end
                4'b0010: begin 
                    clk_m = 7'b0000010; 
                    Curr_SPSR <= SPSR_irq;
                end
                4'b0011: begin 
                    clk_m = 7'b0000100; 
                    Curr_SPSR <= SPSR_svc;
                end 
                4'b0110: begin 
                    clk_m = 7'b0001000; 
                    Curr_SPSR <= SPSR_mon;
                end
                4'b0111: begin 
                    clk_m = 7'b0010000; 
                    Curr_SPSR <= SPSR_abt;
                end
                4'b1010: begin 
                    clk_m = 7'b0100000; 
                    Curr_SPSR <= SPSR_hyp;
                end
                4'b1011: begin 
                    clk_m = 7'b1000000; 
                    Curr_SPSR <= SPSR_und;
                end
            endcase
        end
    end

    
    //SPSR
    d_flip_flop_32 D_SPSR_fiq(
        .d(new_SPSR),
        .clk(~clk * Write_SPSR * clk_m[0]),
        .q(SPSR_fiq)
    );
    d_flip_flop_32 D_SPSR_irq(
        .d(new_SPSR),
        .clk(~clk * Write_SPSR * clk_m[1]),
        .q(SPSR_irq)
    );
    d_flip_flop_32 D_SPSR_svc(
        .d(new_SPSR),
        .clk(~clk * Write_SPSR * clk_m[2]),
        .q(SPSR_svc)
    );
    d_flip_flop_32 D_SPSR_mon(
        .d(new_SPSR),
        .clk(~clk * Write_SPSR * clk_m[3]),
        .q(SPSR_mon)
    );
    d_flip_flop_32 D_SPSR_abt(
        .d(new_SPSR),
        .clk(~clk * Write_SPSR * clk_m[4]),
        .q(SPSR_abt)
    );
    d_flip_flop_32 D_SPSR_hyp(
        .d(new_SPSR),
        .clk(~clk * Write_SPSR * clk_m[5]),
        .q(SPSR_hyp)
    );
    d_flip_flop_32 D_SPSR_und(
        .d(new_SPSR),
        .clk(~clk * Write_SPSR * clk_m[6]),
        .q(SPSR_und)
    );
    
    //CPSR
    d_flip_flop_8 D_CPSR_7_0(
        .d(CPSR_in[7:0]),
        .clk(~clk * Write_CPSR * ~(W_CPSR_s[0] * ~MASK[0] * ~W_CPSR_s[1] * ~W_CPSR_s[2])),
        .q(CPSR[7:0])
    );
    d_flip_flop_8 D_CPSR_15_8(
        .d(CPSR_in[15:8]),
        .clk(~clk * Write_CPSR * ((~W_CPSR_s[0]*~W_CPSR_s[1]*~W_CPSR_s[2])+(~W_CPSR_s[1]*~W_CPSR_s[2]*MASK[1]))),
        .q(CPSR[15:8])
    );
    d_flip_flop_8 D_CPSR_23_16(
        .d(CPSR_in[23:16]),
        .clk(~clk * Write_CPSR * ((~W_CPSR_s[0]*~W_CPSR_s[1]*~W_CPSR_s[2])+(~W_CPSR_s[1]*~W_CPSR_s[2]*MASK[2]))),
        .q(CPSR[23:16])
    );
    d_flip_flop_4 D_CPSR_27_24(
        .d(CPSR_in[27:24]),
        .clk(~clk * Write_CPSR * ((~W_CPSR_s[0]*~W_CPSR_s[1]*~W_CPSR_s[2])+(~W_CPSR_s[1]*~W_CPSR_s[2]*MASK[3]))),
        .q(CPSR[27:24])
    );
    d_flip_flop_4 D_CPSR_31_28(
        .d((S==0)? CPSR_in[31:28] : NZCV),
        .clk((~clk * Write_CPSR * ((~W_CPSR_s[0]*~W_CPSR_s[1]*~W_CPSR_s[2])+(~W_CPSR_s[1]*~W_CPSR_s[2]*MASK[3])))+(~clk  *  S)),
        .q(CPSR[31:28])
    );
endmodule

module d_flip_flop_32(
    input [31:0]d,
    input clk,
    input clr,
    output reg [31:0] q
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

module d_flip_flop_4(
    input [3:0]d,
    input clk,
    input clr,
    output reg [3:0] q
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

module d_flip_flop_8(
    input [7:0]d,
    input clk,
    input clr,
    output reg [7:0] q
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