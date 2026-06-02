module rca40 (
    output [39:0] S,
    input [39:0] A, B,
    input Cin,
    output Cout
);
    wire [39:0] c;
    wire [39:0] sum_internal;
    
    // Instantiate the first full adder with Cin as the carry-in
    full_adder fa0 (
        .a(A[0]),
        .b(B[0]),
        .cin(Cin),
        .cout(c[0]),
        .sum(sum_internal[0])
    );

    // Loop to instantiate remaining 39 full adders
    full_adder fa1_39 [38:0] (
        .a(A[39:1]),
        .b(B[39:1]),
        .cin(c[38:0]),
        .cout(c[39:1]),
        .sum(sum_internal[39:1])
    );

    assign S = sum_internal;
    assign Cout = c[39];
endmodule

module full_adder (
    input a, b, cin,
    output cout, sum
);
    assign cout = (a & b) | (b & cin) | (a & cin);
    assign sum = a ^ b ^ cin;
endmodule
