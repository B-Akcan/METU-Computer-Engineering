`timescale 1ns / 1ps

module lab3_2(
			input[5:0] money,
			input CLK,
			input vm, //0:VM0, 1:VM1
			input [2:0] productID, //000:sandwich, 001:chocolate, 11x: dont care
			input sugar, //0: No sugar, 1: With Sugar
			output reg [5:0] moneyLeft,
			output reg [4:0] itemLeft,
			output reg productUnavailable,//1:show warning, 0:do not show warning
			output reg insufficientFund , //1:full, 0:not full
			output reg notExactFund , //1:full, 0:not full
			output reg invalidProduct, //1: empty, 0:not empty
			output reg sugarUnsuitable, //1: empty, 0:not empty
			output reg productReady	//1:door is open, 0:closed
	);



	// Internal State of the Module

	// (you can change this but you probably need this)

	reg [4:0] numOfSandwiches;
	reg [4:0] numOfChocolate;
	reg [4:0] numOfWaterVM0;
	reg [4:0] numOfWaterVM1;
	reg [4:0] numOfCoffee;
	reg [4:0] numOfTea;



	initial
	begin
		moneyLeft = 6'b000000;
		itemLeft = 5'b00000;
		productUnavailable = 1'b0;
		insufficientFund = 1'b0;
		notExactFund = 1'b0;
		invalidProduct = 1'b0;
		sugarUnsuitable = 1'b0;
		productReady = 1'b0;
		numOfSandwiches = 5'b01010;
		numOfChocolate = 5'b01010;
		numOfWaterVM0 = 5'b00101;
		numOfCoffee = 5'b01010;
		numOfTea = 5'b01010;
		numOfWaterVM1 = 5'b01010;
	end



	always @(posedge CLK)
	begin

		if (productID == 3'b101 || productID == 3'b110 || productID == 3'b111
			 || (vm == 1'b0 && (productID == 3'b011 || productID == 3'b100))
			 || (vm == 1'b1 && (productID == 3'b000 || productID == 3'b001)))
		begin
			invalidProduct <= 1'b1;
			productReady <= 1'b0;
			itemLeft <= 4'bxxxx;
			productUnavailable <= 1'bx;
			insufficientFund <= 1'bx;
			notExactFund <= 1'bx;
			sugarUnsuitable <= 1'bx;
			moneyLeft <= money;
		end
		else if ((productID == 3'b000 && numOfSandwiches == 5'b00000)
					|| (productID == 3'b001 && numOfChocolate == 5'b00000)
					|| (productID == 3'b010 && vm == 0 && numOfWaterVM0 == 5'b00000)
					|| (productID == 3'b010 && vm == 1 && numOfWaterVM1 == 5'b00000)
					|| (productID == 3'b011 && numOfCoffee == 5'b00000)
					|| (productID == 3'b100 && numOfTea == 5'b00000))
		begin
			productUnavailable <= 1'b1;
			invalidProduct <= 1'b0;
			itemLeft <= 4'bxxxx;
			insufficientFund <= 1'bx;
			notExactFund <= 1'bx;
			sugarUnsuitable <= 1'bx;
			productReady <= 1'b0;
			moneyLeft <= money;
		end
		else if (vm == 1 && productID == 3'b010 && sugar == 1)
		begin
			productUnavailable <= 0;
			invalidProduct <= 0;
			sugarUnsuitable <= 1;
			productReady <= 0;
			itemLeft <= 4'bxxxx;
			insufficientFund <= 1'bx;
			notExactFund <= 1'bx;
			moneyLeft <= money;
		end
		else if ((vm == 0 && productID == 3'b000 && money != 5'b10100)
					|| (vm == 0 && productID == 3'b001 && money != 5'b01010)
					|| (vm == 0 && productID == 3'b010 && money != 5'b00101))
		begin
			productUnavailable <= 0;
			invalidProduct <= 0;
			sugarUnsuitable <= 1'bx;
			productReady <= 0;
			itemLeft <= 4'bxxxx;
			insufficientFund <= 1'bx;
			notExactFund <= 1;
			moneyLeft <= money;
		end
		else if ((vm == 1 && productID == 3'b010 && money < 5)
					|| (vm == 1 && productID == 3 && money < 12)
					|| (vm == 1 && productID == 4 && money < 8))
		begin
			productUnavailable <= 0;
			invalidProduct <= 0;
			sugarUnsuitable <= 0;
			productReady <= 0;
			itemLeft <= 4'bxxxx;
			insufficientFund <= 1;
			notExactFund <= 1'bx;
			moneyLeft <= money;
		end
		else begin
			case (productID)
				0: begin
						productUnavailable <= 0;
						invalidProduct <= 0;
						sugarUnsuitable <= 1'bx;
						productReady <= 1;
						insufficientFund <= 1'bx;
						notExactFund <= 0;
						itemLeft <= numOfSandwiches - 1;
						numOfSandwiches <= numOfSandwiches - 1;
						moneyLeft <= 0;
					end
				1: begin
						productUnavailable <= 0;
						invalidProduct <= 0;
						sugarUnsuitable <= 1'bx;
						productReady <= 1;
						insufficientFund <= 1'bx;
						notExactFund <= 0;
						itemLeft <= numOfChocolate - 1;
						numOfChocolate <= numOfChocolate - 1;
						moneyLeft <= 0;
					end
				2: begin
						productUnavailable <= 0;
						invalidProduct <= 0;
						sugarUnsuitable <= 1'bx;
						productReady <= 1;
						insufficientFund <= 0;
						notExactFund <= 0;
						moneyLeft <= money - 5;
						if (vm == 0)
						begin
							itemLeft <= numOfWaterVM0 - 1;
							numOfWaterVM0 <= numOfWaterVM0 - 1;
						end
						else begin
							itemLeft <= numOfWaterVM1 - 1;
							numOfWaterVM1 <= numOfWaterVM1 - 1;
						end
					end
				3: begin
						productUnavailable <= 0;
						invalidProduct <= 0;
						sugarUnsuitable <= 0;
						productReady <= 1;
						insufficientFund <= 0;
						notExactFund <= 1'bx;
						itemLeft <= numOfCoffee - 1;
						numOfCoffee <= numOfCoffee - 1;
						moneyLeft <= money - 12;
					end
				4: begin
						productUnavailable <= 0;
						invalidProduct <= 0;
						sugarUnsuitable <= 0;
						productReady <= 1;
						insufficientFund <= 0;
						notExactFund <= 1'bx;
						itemLeft <= numOfTea - 1;
						numOfTea <= numOfTea - 1;
						moneyLeft <= money - 8;
					end
				default: begin
							productUnavailable <= 1'bx;
							invalidProduct <= 1'bx;
							sugarUnsuitable <= 1'bx;
							productReady <= 1'bx;
							insufficientFund <= 1'bx;
							notExactFund <= 1'bx;
							itemLeft <= 5'bxxxxx;
							moneyLeft <= 6'bxxxxxx;
						end
			endcase
		end
	end
endmodule







