`timescale 1ns / 1ps

module bh(input B, input H, input clk, output reg Q);

    initial begin
        Q = 1;
    end
	 
	 always@(posedge clk)
	 begin
		if (B == 1'b0 && H == 1'b0)
		begin
			if (Q == 1'b0)
				Q <= 1'b1;
			else
				Q <= 1'b0;
		end
		else if (B == 1'b0 && H == 1'b1)
			Q <= 1'b1;
		else if (B == 1'b1 && H == 1'b0)
			Q <= 1'b0;
		else begin
			if (Q == 1'b0)
				Q <= 1'b0;
			else
				Q <= 1'b1;
		end
	 end

endmodule

module ic1337(// Inputs
              input A0,
              input A1,
              input A2,
              input clk,
              // Outputs
              output Q0,
              output Q1,
              output reg Z);

	 reg b1, h1_b2, h2;
	 initial begin
		b1 = 0;
		h1_b2 = 0;
		h2 = 0;
	 end
	 
	 always@(A0 or A1 or A2)
	 begin
		b1 = (A0 ^ ~A1) | A2;
		h1_b2 = A0 & !A2;
		h2 = ~(~A0 | A1) & A2;
	 end
	 
	 bh bh1(b1, h1_b2, clk, Q0);
	 bh bh2(h1_b2, h2, clk, Q1);

	 always@(Q0 or Q1)
	 begin
		Z <= Q0 ~^ Q1;
	 end


endmodule