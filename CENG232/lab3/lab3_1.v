`timescale 1ns / 1ps

module bh(input B, input H, input clk, output reg Q);

    initial begin
        Q = 1;
    end
	 always@(posedge clk)
	 begin
			Q <= (!B && !Q) || (H && Q);
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
              output Z);
	 
	 assign x = ((A0^(!A1)) || A2);
	 assign x2 = (A0 && !A2);
	 assign y = (A0 && !A2);
	 assign y2 = (!(!A0 || A1) && A2);
	 bh bh1(
				.B(x),
				.H(x2),
				.clk(clk),
				.Q(Q0)
			);
			bh bh2(
				.B(y),
				.H(y2),
				.clk(clk),
				.Q(Q1)
			);
    
	 assign Z = !(Q0 ^ Q1);

endmodule
