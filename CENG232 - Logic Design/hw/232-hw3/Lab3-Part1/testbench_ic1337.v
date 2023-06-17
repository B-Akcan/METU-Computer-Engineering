`timescale 1ns / 1ps


module testbench;
	// Inputs
	reg I0;
	reg I1;
	reg I2;
	reg clk;
	// Outputs
	wire Q0;
	wire Q1;
	wire Z;

	// Instantiate the Unit Under Test (UUT)
	ic1337 uut (.A0(I0),
                .A1(I1),
                .A2(I2),
                .clk(clk),
                .Q0(Q0),
                .Q1(Q1),
                .Z(Z));

    // Clock Related
    // At 5, 15, 25, .. clk will change 0->1
	// At 10, 20, 30, .. clk will change 1->0
    initial clk = 0;
    always #5 clk = ~clk;

	initial begin

        // You can implement your test here...
		$monitor("Time=%.2d | A0=%b A1=%b A2=%b | Q0=%b Q1=%b Z=%b", $time, I0, I1, I2, Q0, Q1, Z);
		
		I0 = 1'b0; I1 = 1'b1; I2 = 1'b0;
		#10;
		if (Q0 != 1'b0) $display("Value of Q0 after Q0prev=1 A0=0 A1=1 A2=0 is wrong");
		else if (Q1 != 1'b0) $display("Value of Q1 after Q1prev=1 A0=0 A1=1 A2=0 is wrong");
		else if (Z != 1'b1) $display("Value of Z after Zprev=1 A0=0 A1=1 A2=0 is wrong");
		else $display("Successful");
		
		I0 = 1'b1; I1 = 1'b1; I2 = 1'b0;
		#10;
		if (Q0 != 1'b0) $display("Value of Q0 after Q0prev=0 A0=1 A1=1 A2=0 is wrong");
		else if (Q1 != 1'b0) $display("Value of Q1 after Q1prev=0 A0=1 A1=1 A2=0 is wrong");
		else if (Z != 1'b1) $display("Value of Z after Zprev=1 A0=1 A1=1 A2=0 is wrong");
		else $display("Successful");
		

		I0 = 1'b1; I1 = 1'b1; I2 = 1'b1;
		#10;
		if (Q0 != 1'b0) $display("Value of Q0 after Q0prev=0 A0=1 A1=1 A2=1 is wrong");
		else if (Q1 != 1'b1) $display("Value of Q1 after Q1prev=0 A0=1 A1=1 A2=1 is wrong");
		else if (Z != 1'b0) $display("Value of Z after Zprev=1 A0=1 A1=1 A2=1 is wrong");
		else $display("Successful");
		
		I0 = 1'b0; I1 = 1'b1; I2 = 1'b1;
		#10;
		if (Q0 != 1'b0) $display("Value of Q0 after Q0prev=0 A0=0 A1=1 A2=1 is wrong");
		else if (Q1 != 1'b0) $display("Value of Q1 after Q1prev=1 A0=0 A1=1 A2=1 is wrong");
		else if (Z != 1'b1) $display("Value of Z after Zprev=0 A0=0 A1=1 A2=1 is wrong");
		else $display("Successful");

		
		#5;
		$display("End");
		$finish;
	end

endmodule
