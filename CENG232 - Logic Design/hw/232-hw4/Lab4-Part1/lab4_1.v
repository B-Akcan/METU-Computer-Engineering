`timescale 1ns / 1ps

module ROM (
input [2:0] addr,
output reg [7:0] dataOut);

	reg [7:0] data [0:7];
	initial begin
		data [0] [7 -: 8] = 8'b00000000;
		data [1] [7 -: 8] = 8'b01010101;
		data [2] [7 -: 8] = 8'b10101010;
		data [3] [7 -: 8] = 8'b00110011;
		data [4] [7 -: 8] = 8'b11001100;
		data [5] [7 -: 8] = 8'b00001111;
		data [6] [7 -: 8] = 8'b11110000;
		data [7] [7 -: 8] = 8'b11111111;
		dataOut = 0;
	end
	
	always@(addr)
	begin
		dataOut = data [addr] [7 -: 8];
	end
	
endmodule

module Difference_RAM (
input mode,
input [2:0] addr,
input [7:0] dataIn,
input [7:0] mask,
input CLK,
output reg [7:0] dataOut);

	reg [7:0] data [0:7];
	initial begin
		data [0] [7 -: 8] = 0;
		data [1] [7 -: 8] = 0;
		data [2] [7 -: 8] = 0;
		data [3] [7 -: 8] = 0;
		data [4] [7 -: 8] = 0;
		data [5] [7 -: 8] = 0;
		data [6] [7 -: 8] = 0;
		data [7] [7 -: 8] = 0;
		dataOut = 0;
	end
	
	always@(posedge CLK)
	begin
		if (mode == 0)
		begin
			data [addr] [7 -: 8] <= (dataIn > mask) ? (dataIn - mask) : (mask - dataIn);
		end
	end
	
	always@(mode)
	begin
		if (mode == 1) 
		begin
			dataOut = data [addr] [7 -: 8];
		end
	end


endmodule


module EncodedMemory (
input mode,
input [2:0] index,
input [7:0] number,
input CLK,
output [7:0] result);

	wire [7:0] mask;

	ROM R(index, mask);
	Difference_RAM DR(mode, index, number, mask, CLK, result);

endmodule


