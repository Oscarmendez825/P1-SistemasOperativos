module display7(input logic [3:0] data,
					output logic [6:0] segments);

	always_comb begin
		case(data)
			4'd_0: segments = 7'b1000000;
			4'd_1: segments = 7'b1111001;
			4'd_2: segments = 7'b0100100;
			4'd_3: segments = 7'b0110000;
			4'd_4: segments = 7'b0011001;
			4'd_5: segments = 7'b0010010;
			4'd_6: segments = 7'b0000010;
			4'd_7: segments = 7'b1111000;
			4'd_8: segments = 7'b0000000;
			4'd_9: segments = 7'b0011000;
			4'd_10: segments = 7'b0001000; //a
			4'd_11: segments = 7'b0000011; //b
			4'd_12: segments = 7'b0100111; //c
			4'd_13: segments = 7'b0100001; //d
			4'd_14: segments = 7'b0000110; //e
			4'd_15: segments = 7'b0001110; //f
			default: segments = 7'b1111111;
		endcase
	end
endmodule