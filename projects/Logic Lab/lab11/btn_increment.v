module btn_increment(
	input wire [3:0] btn,
	input wire [3:0] switch,
	output reg [15:0] op1,op2
);
	
	initial op1 <= 16'b0001_0010_0011_0100; //op1,op2³õÊ¼»¯
	initial op2 <= 16'b0101_0110_0111_1000;
	
	always @(posedge btn[0])
	if(switch[3]==1'b0)begin
		if(switch == 2'b01) op1[ 3: 0]<= op1[ 3: 0] + 1'd1;
		else if(switch == 2'b10) op2[ 3: 0]<= op2[ 3: 0] + 1'd1;
	end

	always @(posedge btn[1])
	if(switch[3]==1'b0)begin
		if(switch == 2'b01) op1[ 7: 4]<= op1[ 7: 4] + 1'd1;
		else if(switch == 2'b10) op2[ 7: 4]<= op2[ 7: 4] + 1'd1;
	end

	always @(posedge btn[2])
	if(switch[3]==1'b0)begin
		if(switch == 2'b01) op1[ 11: 8]<= op1[ 11: 8] + 1'd1;
		else if(switch == 2'b10) op2[ 11: 8]<= op2[ 11: 8] + 1'd1;
	end

	always @(posedge btn[3])
	if(switch[3]==1'b0)begin
		if(switch == 2'b01) op1[ 15: 12]<= op1[ 15: 12] + 1'd1;
		else if(switch == 2'b10) op2[ 15: 12]<= op2[ 15: 12] + 1'd1;
	end
	
endmodule
