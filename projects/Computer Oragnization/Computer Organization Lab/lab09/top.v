`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:30:26 04/17/2011 
// Design Name: 
// Module Name:    top 
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
module top(
	input wire testclk,
	input wire [1:0] btn_in,
	input wire [7:0] switch,
	output wire [3:0] anode,
	output wire [7:0] segment,
	output wire zero,
	output wire carryout,
	output wire overflow
	);
	
	reg [15:0] count;
	
	reg [31:0] display_num;
    wire [31:0] disp_ASCII;
	
	wire clk,rst;
	wire [31:0] testresult;
	wire [8:0] pc_in,pc_out;//
	wire [8:0] o_pc;        //
	wire [31:0] iout;       //
	wire [4:0] datawrite;   //
	wire [31:0] wdata;      //
	wire [31:0] rout1,rout2;//
   wire [31:0] extendout;  //
	wire [2:0] aluctl;      //
	wire [31:0] aluresult;  //
	wire [31:0] dataout;    //
	wire [31:0] branchout;  //
	wire [31:0] srcout;     //
	wire [31:0] add0out;    //
	wire andout;            //
	wire [1:0] o_aluop;//
	wire szero;
	wire o_regdst,o_jump,o_branch,o_memread,o_memtoreg,o_memwrite,o_alusrc,o_regwrite,o_selectzero;//
	
	pbdebounce pb0(testclk, btn_in[0], clk);
	pbdebounce pb1(testclk, btn_in[1], rst);

    display_ASCII dis0(testclk,rst,display_num, 4'b1111, anode,segment); 
	pc p0(clk,rst,pc_in,pc_out);//
	pc_plus4 p_p0(pc_out,o_pc);//
	mux_2_1 m21(zero,~zero,o_selectzero,szero);
	instruction i0(testclk,pc_out,iout);//	
	control c0(rst,iout[31:26],o_aluop,o_regdst,o_jump,o_branch,o_memread,o_memtoreg,o_memwrite,o_alusrc,o_regwrite,o_selectzero);//
	mux5 m0(iout[20:16],iout[15:11],o_regdst,datawrite);//
	mux32 m1(rout2,extendout,o_alusrc,srcout);      //
	registerfile r0(rst,clk,iout[25:21],iout[20:16],switch[4:0],datawrite,wdata,o_regwrite,rout1,rout2,testresult); //  
	extend e0(iout[15:0],extendout);  //
    alu_ctl a0(o_aluop,extendout[5:0],aluctl);//
	alu al0(rout1,srcout,aluctl,aluresult,zero,carryout,overflow);//
	data d0(testclk,rout2,aluresult[8:0],o_memwrite,dataout,testclk,32'h00000000,9'h000,0,disp_ASCII);//
	mux32 mr0(aluresult,dataout,o_memtoreg,wdata);//
	mux32 m2({23'h0,o_pc},add0out,andout,branchout);//
	mux9 m90(branchout[8:0],iout[8:0],o_jump,pc_in);//
	and(andout,szero,o_branch);  //
	Add add0({23'h0,o_pc},extendout[29:0],add0out);//
   
	always @(posedge clk or posedge rst)begin 
		if(rst==1)
			count=16'h0000;
		else 
		   count=count+1;
	end
    
    always @*
        display_num = disp_ASCII;
endmodule
