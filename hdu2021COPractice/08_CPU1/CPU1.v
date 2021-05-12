`timescale 1ns / 1ps

module CPU1(
	input clk,
	input rst,
	output reg[31:0] IR,
	output reg[7:0] PC,
	output reg[3:0] NZCV,
	output reg rm_imm_s,
	output reg rs_imm_s,
	output reg[3:0]ALU_OP,
	output reg[3:0]shift_op,
	output reg Write_PC, // 压根没用到这玩意啊g
	output reg Write_IR, // 这玩意好像也没有�?
	output reg Write_Reg,
	output reg[31:0] A,
	output reg[31:0] B,
	output reg[31:0] C,
	output reg[31:0] F
);
	// initial IR <= 0;
	// 实验7 得到IR
	wire[4:0] OP;
	wire[3:0] rn;
	wire S;
	wire[3:0] rd;
	wire[4:0] imm5;
	wire[1:0] type;
	wire[3:0] rm;
	wire[3:0] rs;
	wire[11:0] imm12;
	reg [3:0]shift_data;
	reg [31:0]shift_num;

	assign OP = IR[24:21];
	assign S = IR[20];
	assign rn = IR[19:16];
	assign rd = IR[15:12];
	assign imm5 = IR[11:7];
	assign type = IR[6:5];
	assign rm = IR[3:0];
	assign rs = IR[11:8];
	assign imm12 = IR[11:0];

	barrelshifter32 barrelshifter32_instance(
		.shift_data(shift_data),
		.carry_flag(),
		.shift_num(shift_num),
		.shift_op(shift_op),
		.shift_out(shift_out),
		.shift_carry_out(shift_carry_out)
	);
	ALU32 ALU_OP_instance(
		.OP(ALU_OP),
		.A(A),
		.B(shift_out),
		.SCO(shift_carry_out),
		.CF(),
		.VF(),
		.F(F),
		.N(NZCV[3]),
		.Z(NZCV[2]),
		.C(NZCV[1]),
		.V(NZCV[0])
	);
	RegFile RegFile_instance(
		.Clk(clk),
		.Rst(rst),
		.Write_Reg(Write_Reg),
		.R_Addr_A(rn),
		.R_Addr_B(rm),
		.R_Addr_C(rs),
		.W_Addr(rd),
		.W_Data(F),
		.R_Data_A(A),
		.R_Data_B(B),
		.R_Data_C(C)
	);
	// PPT p43
	always@(clk/*上跳沿下跳沿有讲究，之前写的可能也没注意*/) begin
		// PPT p6
		case(OP)
			4'b0000:ALU_OP<=0'b0000;
			4'b0001:ALU_OP<=0'b0001;
			4'b0010:ALU_OP<=0'b0010;
			4'b0011:ALU_OP<=0'b0011;
			4'b0100:ALU_OP<=0'b0100;
			4'b0101:ALU_OP<=0'b0101;
			4'b0110:ALU_OP<=0'b0110;
			4'b0111:ALU_OP<=0'b0111;
			4'b1000:ALU_OP<=0'b0000;
			4'b1001:ALU_OP<=0'b0001;
			4'b1010:ALU_OP<=0'b0010;
			4'b1011:ALU_OP<=0'b0100;
			4'b1100:ALU_OP<=0'b1000;
			4'b1101:ALU_OP<=0'b1001;
			4'b1110:ALU_OP<=0'b1010;
			4'b1111:ALU_OP<=0'b1011;
		endcase

		// PPT p16
		if (OP >= 0'b1000 && OP <= 0'b1011 && S) Write_Reg <= 0;
		else Write_Reg <= 1;

		if (IR[27:25] == 0'b000 && IR[4] == 0) begin                     // DP0
			// PPT p38
			rm_imm_s <= 0;
			rs_imm_s <= 0;
			// PPT p19
			case(type)
				0'b00:shift_op <= 0'b000;
				0'b01:shift_op <= 0'b010;
				0'b10:shift_op <= 0'b100;
				0'b11:shift_op <= 0'b110;
			endcase
		end
		else if (IR[27:25] == 0'b000 && IR[7] == 0 && IR[4] == 1) begin // DP1
			// PPT p39
			rm_imm_s <= 0;
			rs_imm_s <= 1;
			// PPT p20
			case(type)
				0'b00:shift_op <= 0'b001;
				0'b01:shift_op <= 0'b011;
				0'b10:shift_op <= 0'b101;
				0'b11:shift_op <= 0'b111;
			endcase
		end
		else if (IR[27:25] == 0'b001) begin                               // DP2
			// PPT p40
			rm_imm_s <= 1;
			rs_imm_s <= 2;
			// PPT p21
			shift_op <= 0'b111;
		end

		case(rm_imm_s)
			0'b0:shift_data<=B;
			0'b1:shift_data<={{24{0'b0}},imm12[7:0]}; // 零扩�?
		endcase
		case(rs_imm_s)
			0:shift_num<={{3{0'b0}},imm5}; // 零扩�?
			1:shift_num<=C;
			2:shift_num<={{3{0'b0}},imm12[11:8]*2}; // 零扩�?
		endcase

	end
endmodule
