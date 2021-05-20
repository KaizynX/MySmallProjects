module fadder_dec
(
	input a, b, ci,
	output reg so,co
);

always @*
	case ({ci,b,a})
		3'b000 : {co,so}=2'b00;
		3'b001 : {co,so}=2'b01;
		3'b010 : {co,so}=2'b01;
		3'b011 : {co,so}=2'b10;
		3'b100 : {co,so}=2'b01;
		3'b101 : {co,so}=2'b10;
		3'b110 : {co,so}=2'b10;
		3'b111 : {co,so}=2'b11;
		default: {co,so}=2'b00;
	endcase

endmodule