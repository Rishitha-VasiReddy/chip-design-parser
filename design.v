module example;
input clk;
output reset;
wire data;
assign data = clk & reset;
endmodule
