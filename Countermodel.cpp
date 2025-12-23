// Code your testbench here.
// Uncomment the next line for SystemC modules.
// #include <systemc>
#include <systemc.h>
#include<design.cpp>
using namespace std;
using namespace sc_core;
int sc_main(int argc, char* argv[]) {
  sc_signal<bool> reset_sig;
  sc_signal<sc_uint<4>>count_sig;
  
  sc_clock clk_sig("clk",10,SC_NS);
  
  counter dut("DUT");
  dut.clk(clk_sig);
  dut.reset(reset_sig);
  dut.count_out(count_sig);
  
  cout<<"starting simulation::"<<endl;
  reset_sig=0;
  sc_start(100,SC_NS);
  
  reset_sig=1;
    sc_start(20,SC_NS);
  reset_sig=0;
  sc_start(100,SC_NS);
   cout << "Simulation Finished!" << endl;
    
    return 0;
}

//------ Design side



// Code your testbench here.
// Uncomment the next line for SystemC modules.
// #include <systemc>
#include <systemc.h>
#include<design.cpp>
using namespace std;
using namespace sc_core;
int sc_main(int argc, char* argv[]) {
  sc_signal<bool> reset_sig;
  sc_signal<sc_uint<4>>count_sig;
  
  sc_clock clk_sig("clk",10,SC_NS);
  
  counter dut("DUT");
  dut.clk(clk_sig);
  dut.reset(reset_sig);
  dut.count_out(count_sig);
  
  cout<<"starting simulation::"<<endl;
  reset_sig=0;
  sc_start(100,SC_NS);
  
  reset_sig=1;
    sc_start(20,SC_NS);
  reset_sig=0;
  sc_start(100,SC_NS);
   cout << "Simulation Finished!" << endl;
    
    return 0;
}
