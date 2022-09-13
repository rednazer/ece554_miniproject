// fifo.sv
// Implements delay buffer (fifo)
// On reset all entries are set to 0
// Shift causes fifo to shift out oldest entry to q, shift in d

module fifo
  #(
  parameter DEPTH=8,
  parameter BITS=64
  )
  (
  input clk,rst_n,en,
  input [BITS-1:0] d,
  output [BITS-1:0] q
  );
	// Create the buffer and the head pointer
	reg [BITS-1:0] buffer [0:DEPTH-1];
	reg [$clog2(DEPTH)-1:0] head;

	// assign output as current head
	assign q = buffer[head];

	always @(posedge clk, negedge rst_n) begin
		if(~rst_n) begin
			head <= 0;
			for(int index = 0; index < DEPTH; index=index+1'b1) begin
				buffer[index] <= 0;
			end
		end else if(en) begin // when enabled, move the buffer and increment the head
			buffer[head] = d;
			head = head + 1'b1;
		end
	end
	
endmodule // fifo
