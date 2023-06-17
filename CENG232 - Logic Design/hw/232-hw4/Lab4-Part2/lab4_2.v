`timescale 1ns / 1ps
module SelectionOfAvatar(
	input [1:0] mode,
	input [5:0] userID,
	input [1:0] candidate, // 00:Air 01:Fire, 10:Water, 11: Earth
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

	reg [6:0] i;
	reg [7:0] clockCycle;
	reg [5:0] registeredVoters [0:63];
	reg [5:0] votedUsers [0:63];
	reg [5:0] votesOfAir;
	reg [5:0] votesOfFire;
	reg [5:0] votesOfWater;
	reg [5:0] votesOfEarth;
	
	initial begin
		for (i=0; i<64; i=i+1) begin
			registeredVoters[i] = 0;
			votedUsers[i] = 0;
		end
		clockCycle = 0;
		votesOfAir = 0;
		votesOfFire = 0;
		votesOfWater = 0;
		votesOfEarth = 0;
		ballotBoxId = 0;
		numberOfRegisteredVoters = 0;
		numberOfVotesWinner = 0;
		WinnerId = 0;
		AlreadyRegistered = 0;
		AlreadyVoted = 0;
		NotRegistered = 0;
		VotingHasNotStarted = 0;
		RegistrationHasEnded = 0;
	end

	always @(posedge CLK)
	begin
		if (clockCycle < 201)
		begin
			clockCycle <= clockCycle + 1;
		end
		else ;
		
		if (clockCycle <= 100)
		begin
			ballotBoxId <= userID[5:4];
			AlreadyVoted <= 0;
			NotRegistered <= 0;
			RegistrationHasEnded <= 0;
			
			if (registeredVoters[userID] == 0)
			begin
				registeredVoters[userID] <= 1;
				numberOfRegisteredVoters <= numberOfRegisteredVoters + 1;
				AlreadyRegistered <= 0;
			end
			else begin
				AlreadyRegistered <= 1;
			end
			
			if (mode == 1)
			begin
				VotingHasNotStarted <= 1;
			end
			else begin
				VotingHasNotStarted <= 0;
			end
		end
		
		else if (clockCycle > 100 && clockCycle <= 200)
		begin
			ballotBoxId <= userID[5:4];
			AlreadyRegistered <= 0;
			VotingHasNotStarted <= 0;
			
			if (votedUsers[userID] == 0)
			begin
				AlreadyVoted <= 0;
				if (registeredVoters[userID] == 1)
				begin
					votedUsers[userID] <= 1;
					case (candidate)
						0: votesOfAir <= votesOfAir + 1;
						1: votesOfFire <= votesOfFire + 1;
						2: votesOfWater <= votesOfWater + 1;
						3: votesOfEarth <= votesOfEarth + 1;
						default: ;
					endcase
				end
				else ;
			end
			else begin
				AlreadyVoted <= 1;
			end
		
			if (mode == 0)
			begin
				RegistrationHasEnded <= 1;
			end
			else begin
				RegistrationHasEnded <= 0;
			end
			
			if (registeredVoters[userID] == 0)
			begin
				NotRegistered <= 1;
			end
			else begin
				NotRegistered <= 0;
			end
		end
		
		else begin
			ballotBoxId [1:0] <= 2'bxx;
			AlreadyRegistered <= 1'bx;
			AlreadyVoted <= 1'bx;
			NotRegistered <= 1'bx;
			VotingHasNotStarted <= 1'bx;
			RegistrationHasEnded <= 1'bx;
			
			if (votesOfAir > votesOfFire && votesOfAir > votesOfWater && votesOfAir > votesOfEarth)
			begin
				numberOfVotesWinner <= votesOfAir;
				WinnerId <= 0;
			end
			else if (votesOfFire > votesOfAir && votesOfFire > votesOfWater && votesOfFire > votesOfEarth)
			begin
				numberOfVotesWinner <= votesOfFire;
				WinnerId <= 1;
			end
			else if (votesOfWater > votesOfFire && votesOfWater > votesOfAir && votesOfWater > votesOfEarth)
			begin
				numberOfVotesWinner <= votesOfWater;
				WinnerId <= 2;
			end
			else begin
				numberOfVotesWinner <= votesOfEarth;
				WinnerId <= 3;
			end
		end
	end

endmodule
