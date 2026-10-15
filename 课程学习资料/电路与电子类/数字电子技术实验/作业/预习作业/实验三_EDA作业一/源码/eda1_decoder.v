// Experiment 3, EDA assignment 1: optional HDL preparation.
// Port order follows the assignment, so Y2 selects AB=10.
module eda1_decoder (
    input  wire A,
    input  wire B,
    output wire Y1,
    output wire Y2,
    output wire Y3,
    output wire Y4
);
    assign Y1 = ~A & ~B;
    assign Y2 =  A & ~B;
    assign Y3 = ~A &  B;
    assign Y4 =  A &  B;
endmodule
