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
	reg [4:0] numOfWaterVM1;
	reg [4:0] numOfWaterVM2;
	reg [4:0] numOfCoffee;
	reg [4:0] numOfTea;

	initial
	begin
		numOfSandwiches = 10;
		numOfChocolate = 10;
		numOfWaterVM1 = 5;
		numOfWaterVM2 = 10;
		numOfCoffee = 10;
		numOfTea = 10;
	end
	
	
	
									
	//Modify the lines below to implement your design
	always @(posedge CLK)
	begin
		if (vm == 1 && productID == 3'b010 && sugar == 1)
			sugarUnsuitable = 1;
		else
			sugarUnsuitable = 0;
		
		if ((numOfSandwiches == 0 && productID == 0 && vm == 0) || (numOfChocolate == 0 && productID == 1 && vm == 0) 
	                        || (numOfWaterVM1 == 0 && productID == 2 && vm == 0) || (numOfWaterVM2 == 0 && productID == 2 && vm == 1) 
									|| (numOfCoffee == 0 && productID == 3 && vm == 1) || (numOfTea == 0 && productID == 4 && vm == 1)) begin
			productUnavailable = 1;
		end
		
		else 
		   productUnavailable = 0;
		
		if ((vm == 0  && productID == 3) || (vm == 0 && productID == 4) || productID > 4)
			invalidProduct = 1;
		else if ((vm == 1 && productID == 0) || (vm == 1 && productID == 1) || productID > 4)
			invalidProduct = 1;
		else 
			invalidProduct = 0;
			
		if(vm == 0 && ((productID == 0 && money == 20) || (productID == 1 && money == 10) || (productID == 2 && money == 5)))
			notExactFund = 0;
		else
			notExactFund = 1;
			
		if(vm == 1 && ((productID == 2 && money < 5) || (productID == 3 && money < 12) || (productID == 4 && money < 8)))
			insufficientFund = 1;
		else
			insufficientFund = 0;
			
		if(!productUnavailable && !invalidProduct && !insufficientFund && !sugarUnsuitable)
			productReady = 1;
		else
			productReady = 0;
			
		if(productReady)begin
			case(productID)
				0 : itemLeft = numOfSandwiches - 1;
				1 : itemLeft = numOfChocolate - 1;
				3 : itemLeft = numOfCoffee - 1;
				4 : itemLeft = numOfTea - 1 ;
			endcase
			if(vm == 0 && productID == 2)
				itemLeft = numOfWaterVM1 - 1;
			if(vm == 1 && productID == 2)
				itemLeft = numOfWaterVM2 - 1;
		end
		
		if(vm == 0)begin
			if(productReady == 1 && !notExactFund)
				moneyLeft = 0;
			else
				moneyLeft = money;
		end
		
		if(vm == 1)begin
			if(productReady)begin
				case(productID)
					2 : moneyLeft = money - 5;
					3 : moneyLeft = money - 12;
					4 : moneyLeft = money - 8 ;
				endcase
			end
			else
				moneyLeft = money;
		end
			
		if(productReady && !notExactFund && vm == 0)begin
			case(productID)
				0 : numOfSandwiches = numOfSandwiches - 1;
				1 : numOfChocolate = numOfChocolate - 1;
				2 : numOfWaterVM1 = numOfWaterVM1 - 1;
			endcase
		end
		
		if(productReady && vm == 1)begin
			case(productID)
				2 : numOfWaterVM2 = numOfWaterVM2 - 1;
				3 : numOfCoffee = numOfCoffee - 1;
				4 : numOfTea = numOfTea - 1;
			endcase
		end
	end


endmodule



