`timescale 1ns / 1ps

module ROM (
input [2:0] addr,
output reg [7:0] dataOut);
	always @(*)
  begin
    case (addr)
      3'd0: dataOut = 8'b00000000;
      3'd1: dataOut = 8'b01010101;
      3'd2: dataOut = 8'b10101010;
      3'd3: dataOut = 8'b00110011;
      3'd4: dataOut = 8'b11001100;
      3'd5: dataOut = 8'b00001111;
      3'd6: dataOut = 8'b11110000;
      3'd7: dataOut = 8'b11111111;
      default: dataOut = 8'b00000000;
    endcase
  end
endmodule

module Difference_RAM (
input mode,
input [2:0] addr,
input [7:0] dataIn,
input [7:0] mask,
input CLK,
output reg [7:0] dataOut);
	
	reg [7:0] memory [0:7];
	reg [7:0] lastData;
  integer i;
  initial begin
    
    for (i = 0; i < 8; i = i + 1) begin
      memory[i] = 8'b0;
    end
  end
  
  always @(posedge CLK) begin
    if (mode == 0) begin
      if (dataIn >= mask)
        memory[addr] <= dataIn - mask;
      else
        memory[addr] <= mask - dataIn;
    end
  end
  
  always @(addr, mode) begin
    if (mode == 1) begin
      dataOut <= memory[addr];
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


