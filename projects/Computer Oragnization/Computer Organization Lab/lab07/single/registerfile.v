`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    17:32:27 04/17/2011 
// Design Name: 
// Module Name:    registerfile 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module registerfile(
    input wire rst,
    input wire clk,
    input wire [4:0] i_adr1,  //register index 1
    input wire [4:0] i_adr2,  //register index 2
	 input wire [4:0] test,     //register index for test
    input wire [4:0] i_wreg,  //register to write
    input wire [31:0] i_wdata,//data to write
    input wire i_wen,         //write enable
    output wire [31:0] o_op1, //read data1, out
    output wire [31:0] o_op2,  //read data2, out
	 output wire [31:0] testresult
    );    
	 
    reg [31:0] mem[31:0];
    
	 assign o_op1 = mem[i_adr1];
	 assign o_op2 = mem[i_adr2];
	 assign testresult = mem[test];
	 
    always @(posedge clk or posedge rst) begin
		if (rst == 1) begin
			mem[0] <= 32'h00000000;
		end
		else if (i_wen) begin
			mem[i_wreg] <= (i_wreg == 5'b00000) ? 32'h00000000 : i_wdata;
		end
    end
endmodule

