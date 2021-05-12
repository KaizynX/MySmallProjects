`timescale 1ns / 1ps

module barrelshifter32(shift_data,carry_flag,shift_num,shift_op,shift_out,shift_carry_out);
    input [31:0] shift_data;
    input carry_flag;
    input [7:0] shift_num;
    input [2:0] shift_op;
    output reg [31:0] shift_out;
    output reg shift_carry_out=0;
    
    always@(*)begin
        // shift_out=shift_data;
        if(shift_op==3'b000||shift_op==3'b001)begin
            if(shift_num==8'b00000000)begin
                shift_out=shift_data;
            end
            else if(shift_num>=1&&shift_num<=32)begin
                shift_out=shift_data<<shift_num;
                shift_carry_out=shift_data[32-shift_num];
            end
            else begin
                shift_out=0;
                shift_carry_out=0;
            end
        end
        else if(shift_op==3'b010||shift_op==3'b011)begin
            if(shift_num==8'b00000000)begin
                if(shift_op==3'b010)begin
                    shift_out=0;
                    shift_carry_out=shift_data[31];
                end
                else shift_out=shift_data;
            end
            else if(shift_num>=1&&shift_num<=32)begin
                shift_out=shift_data>>shift_num;
                shift_carry_out=shift_data[shift_num-1];
            end
            else begin
                shift_out=0;
                shift_carry_out=0;
            end
        end
        else if(shift_op==3'b100||shift_op==3'b101)begin
            if(shift_num==8'b00000000)begin
                if(shift_op==3'b100)begin
                    shift_out={32{shift_data[31]}};
                    shift_carry_out=shift_data[31];
                end
                else shift_out=shift_data;
            end
            else if(shift_num>=1&&shift_num<=31)begin
                shift_out={{32{shift_data[31]}},shift_data}>>shift_num;
                shift_carry_out=shift_data[shift_num-1];
            end
            else begin
                shift_out={32{shift_data[31]}};
                shift_carry_out=shift_data[31];
            end
        end
        else if(shift_op==3'b110||shift_op==3'b111)begin
            if(shift_num==8'b00000000)begin
                if(shift_op==3'b110)begin
                    shift_out={carry_flag,shift_data[31:1]};
                    shift_carry_out=shift_data[0];
                end
                else shift_out=shift_data;
            end
            else if(shift_num>=1&&shift_num<=32)begin
                shift_out={shift_data,shift_data}>>shift_num;
                shift_carry_out=shift_data[shift_num-1];
            end
            else begin
                shift_out={{32{shift_data}},shift_data}>>shift_num[4:0];
                shift_carry_out=shift_data[shift_data[4:0]-1];
            end
        end
    end
endmodule // barrelshifter32
