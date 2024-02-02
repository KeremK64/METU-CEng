`timescale 1ns / 1ps
module SelectionOfAvatar(
	input [1:0] mode,
	input [5:0] userID,
	input [1:0] candidate, // 00:Air 01:Fire, 10:Earth, 11: Water
	input CLK,
	output reg [1:0] ballotBoxId,
	output reg [5:0] numberOfRegisteredVoters,
	output reg [5:0] numberOfVotesWinner, // number of votes of winner
	output reg [1:0] WinnerId,
	output reg AlreadyRegistered,
	output reg AlreadyVoted,
	output reg NotRegistered,
	output reg VotingHasNotStarted,
	output reg RegistrationHasEnded
	);

	reg [5:0]votes00;
	reg [5:0]votes01;
	reg [5:0]votes10;
	reg [5:0]votes11;
	
	reg ballot00[15:0];
	reg ballot01[15:0];
	reg ballot10[15:0];
	reg ballot11[15:0];
	
	reg BBallot00[15:0];
	reg BBallot01[15:0];
	reg BBallot10[15:0];
	reg BBallot11[15:0];
	
	reg [8:0]clock;
	
	integer i;
	integer max1, winner1, max2, winner2;
	
	initial begin
		numberOfRegisteredVoters = 0;
		votes00 = 0;
		votes01 = 0;
		votes10 = 0;
		votes11 = 0;
		
		clock = 0;
		
		for(i = 0; i < 16; i = i+1)begin
			ballot00[i] = 0;
			ballot01[i] = 0;
			ballot10[i] = 0;
			ballot11[i] = 0;
		end
		
		for(i = 0; i < 16; i = i+1)begin
			BBallot00[i] = 0;
			BBallot01[i] = 0;
			BBallot10[i] = 0;
			BBallot11[i] = 0;
		end
		
		WinnerId = 2'b00;
		numberOfVotesWinner = 6'b000000;
		AlreadyVoted = 0;
		NotRegistered = 0;
		VotingHasNotStarted = 0;
		RegistrationHasEnded = 0; 
		AlreadyRegistered = 0;
	end

	always @(posedge CLK)
	begin
		AlreadyRegistered = 0;
		AlreadyVoted = 0;
		NotRegistered = 0;
		clock = clock + 1;
		ballotBoxId = userID[5:4];
		if(clock <= 100)begin
			if(mode == 1)begin
				VotingHasNotStarted = 1;
			end
			if(!mode)begin				
				VotingHasNotStarted = 0;
				
				if(ballotBoxId == 0)begin
					if(ballot00[userID[3:0]] != 1)begin
						ballot00[userID[3:0]] = 1;
						numberOfRegisteredVoters = numberOfRegisteredVoters + 1;
						
					end
					else begin
						AlreadyRegistered = 1;
					end
				end	
					else if(ballotBoxId == 1)begin
						if(ballot01[userID[3:0]] != 1)begin
							ballot01[userID[3:0]] = 1;
							numberOfRegisteredVoters = numberOfRegisteredVoters + 1;
							
						end
						else begin
							AlreadyRegistered = 1;
						end
					end
					
					else if(ballotBoxId == 2)begin
						if(ballot10[userID[3:0]] != 1)begin
							ballot10[userID[3:0]] = 1;
							numberOfRegisteredVoters = numberOfRegisteredVoters + 1;
							
						end
						else begin
							AlreadyRegistered = 1;
						end
					end
					
					else if(ballotBoxId == 3)begin
						if(ballot11[userID[3:0]] != 1)begin
							ballot11[userID[3:0]] = 1;
							numberOfRegisteredVoters = numberOfRegisteredVoters + 1;
							
						end
						else begin
							AlreadyRegistered = 1;
						end
					end
				end
			end 
			if(clock <= 200 && clock > 100)begin
				RegistrationHasEnded = 0;
				AlreadyVoted = 0;
				if(!mode)begin
					RegistrationHasEnded = 1;
				end
				if(mode)begin
					case(userID[5:4])
						0: if(ballot00[userID[3:0]] == 0) begin NotRegistered = 1; end
						1: if(ballot01[userID[3:0]] == 0) begin NotRegistered = 1; end
						2: if(ballot10[userID[3:0]] == 0) begin NotRegistered = 1; end
						3: if(ballot11[userID[3:0]] == 0) begin NotRegistered = 1; end
					endcase
					
					
					if(ballotBoxId == 0)begin
						if(BBallot00[userID[3:0]] != 1 && !NotRegistered)begin
							BBallot00[userID[3:0]] = 1;
							case(candidate)
								0:votes00 = votes00 + 1;
								1:votes01 = votes01 + 1;
								2:votes10 = votes10 + 1;
								3:votes11 = votes11 + 1;
								
							endcase
						end
						else if(BBallot00[userID[3:0]] != 1 && NotRegistered)begin
							AlreadyVoted = 0;
						end
						else begin AlreadyVoted = 1; end
					end
					
					else if(ballotBoxId == 1)begin
						if(BBallot01[userID[3:0]] != 1 && !NotRegistered)begin
							BBallot01[userID[3:0]] = 1;
							case(candidate)
								0:votes00 = votes00 + 1;
								1:votes01 = votes01 + 1;
								2:votes10 = votes10 + 1;
								3:votes11 = votes11 + 1;
								
							endcase
						end
						else if(BBallot01[userID[3:0]] != 1 && NotRegistered)begin
							AlreadyVoted = 0;
						end
						else begin AlreadyVoted = 1; end
					end
					
					else if(ballotBoxId == 2)begin
						if(BBallot10[userID[3:0]] != 1 && !NotRegistered)begin
							BBallot10[userID[3:0]] = 1;
							case(candidate)
								0:votes00 = votes00 + 1;
								1:votes01 = votes01 + 1;
								2:votes10 = votes10 + 1;
								3:votes11 = votes11 + 1;
								
							endcase
						end
						else if(BBallot10[userID[3:0]] != 1 && NotRegistered)begin
							AlreadyVoted = 0;
						end
						else begin AlreadyVoted = 1; end
					end
					
					else if(ballotBoxId == 3)begin
						if(BBallot11[userID[3:0]] != 1 && !NotRegistered)begin
							BBallot11[userID[3:0]] = 1;
							case(candidate)
								0:votes00 = votes00 + 1;
								1:votes01 = votes01 + 1;
								2:votes10 = votes10 + 1;
								3:votes11 = votes11 + 1;
								
							endcase
						end
						else if (BBallot11[userID[3:0]] != 1 && NotRegistered)begin
							AlreadyVoted = 0;
						end
						else begin AlreadyVoted = 1; end
					end
				end
			end
			if(clock > 200)begin
				if(votes00 >= votes01)begin
					max1 = votes00;
					winner1 = 0;
				end
				else begin
					max1 = votes01;
					winner1 = 1;
				end
				if(votes10 >= votes11)begin
					max2 = votes10;
					winner2 = 2;
				end
				else begin
					max2 = votes11;
					winner2 = 3;
				end
				
				if(max1 > max2)begin
					numberOfVotesWinner = max1;
					WinnerId = winner1;
				end
				else begin
					numberOfVotesWinner = max2;
					WinnerId = winner2;
				end
			end
	end

endmodule
