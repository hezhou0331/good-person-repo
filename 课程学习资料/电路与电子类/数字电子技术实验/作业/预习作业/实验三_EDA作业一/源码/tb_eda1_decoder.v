`timescale 1ns/1ps
// Simulation only. Do not add this file to FPGA synthesis sources.
module tb_eda1_decoder;
    reg A, B;
    wire Y1, Y2, Y3, Y4;
    wire [3:0] actual = {Y4, Y3, Y2, Y1};
    reg [3:0] expected;
    integer i;
    integer errors = 0;

    eda1_decoder dut (
        .A(A), .B(B), .Y1(Y1), .Y2(Y2), .Y3(Y3), .Y4(Y4)
    );

    initial begin
        for (i = 0; i < 4; i = i + 1) begin
            {A, B} = i;
            case (i)
                0: expected = 4'b0001;
                1: expected = 4'b0100;
                2: expected = 4'b0010;
                3: expected = 4'b1000;
            endcase
            #1;
            if (actual !== expected) begin
                errors = errors + 1;
                $display("FAIL AB=%b%b got Y4..Y1=%b expected=%b", A, B, actual, expected);
            end
            if ((actual !== 4'b0001) && (actual !== 4'b0010) &&
                (actual !== 4'b0100) && (actual !== 4'b1000)) begin
                errors = errors + 1;
                $display("FAIL: outputs are not one-hot");
            end
            $display("AB=%b%b Y1..Y4=%b%b%b%b", A, B, Y1, Y2, Y3, Y4);
            #99;
        end
        if (errors == 0)
            $display("PASS: all four input combinations match the assignment");
        else
            $display("FAIL: %0d checks failed", errors);
        $finish;
    end
endmodule
