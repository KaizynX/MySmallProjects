`timescale 1ns / 1ps
// 通过数据输入输出测试开关、LED、数码管；通过数码管使能测试按钮
module Board(sw, swb, led, clk, which, seg, enable);
    input [32:1] sw;
    input [6:1]swb;
    output led;
    reg [32:1]temp;
    reg [3:1]op;
    reg [8:1]num;
    always @(posedge swb[1])
    begin
        temp<=sw;
    end
    always @(posedge swb[2])
    begin
        op<=sw[31:29];
        num<=sw[23:16];
    end 
    reg [32:1]out;
    reg shift_carry_out;
    input clk; // 数码管相关
    output [2:0] which;
    output [7:0] seg;
    output reg enable = 1; // 默认开启数码管使能

    //Display barrelshifter32(.);
    barrelshifter32 barrelshifter32(.shift_data(temp),.carrt_flag(swb[3]),.shift_num(num),.shift_op(op),.shift_out(out),.shift_carry_out(shift_carry_out));
    led[0]<=shift_carry_out;
    Display Display_Instance(.clk(clk), .data(out),.which(which), .seg(seg));
    input [1:6] swb;
    assign toggle = |swb; // 按下任意按钮切换数码管使能
    always @(posedge toggle) enable <= ~enable;

endmodule // Board
