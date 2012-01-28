module divider(input CLK_1ms,
    input [15:0] DIVIDEND,        // dividend input
    input [7:0] DIVISOR,          // divisor input
    output reg [7:0] QUOTIENT,    // quotient output
    output reg [7:0] REMAINDER,   // remainder output
    output reg DZ,                // divided by zero flag
    output reg DO                 // divider overflow flag	 
    );

	 reg[23:0] divid;
	 reg[7:0] diviso;
	 
	 initial begin
	    QUOTIENT = 0;
	    REMAINDER = 0;
		 DZ = 0;
		 DO =0;
	 end
	 
    always@(posedge CLK_1ms)begin
		divid[15:0]=DIVIDEND;
		divid[23:16]=0;
		diviso=DIVISOR;
      repeat(16) 
		begin
			divid=divid<<1;
			if(divid[23:16] >= diviso)
			begin
				divid[23:16]=divid[23:16]-diviso;
				divid[0]=1;
         end
      end
		
		if(DIVISOR == 0) 
		begin
			DZ = 1; DO = 0;
			QUOTIENT = 0;
			REMAINDER = 0;
		end else if(divid[15:0] > 255) 
		begin
			DO = 1; DZ = 0;
			QUOTIENT = divid[7:0];
			REMAINDER =divid[23:16];																																
		end else 
		begin
			DO = 0; DZ = 0;
			QUOTIENT = divid[7:0];
			REMAINDER = divid[23:16];		    
		end
	 end
endmodule
