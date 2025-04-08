# systemc_model
My First systemc Model
Develop the model of a adder, It should have two inputs A & B of integer type, and one output OUT of integer type.
Whenever any of the input change, it should add both inputs and put the result on output port after 2 ns.

Test bench: Applies the values at input port at following times:
  0 ns: A= 0, B= 0
  5 ns: A= 5, B= 0
  8 ns: A= 5, B= 10
  15 ns: A= 7, B= 8

Whenever the value changes at the output port of adder, the testbench should print the value of this port and the simulation time
SOLUTION 
The code part is divided in 3 parts 
1. adder.h -> contains the basic logic for adder 
2. testbench.h -> contains the testbench
3. main.cpp 
