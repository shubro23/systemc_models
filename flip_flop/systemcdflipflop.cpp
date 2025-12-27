D flip flop model -> it is just used to store value at a particulart time interval
///////test bench?????
#include<systemc.h>
#include<design.cpp>
using namespace std;
int sc_main(int argc, char* argv[]){
  sc_signal<int>s_a,s_b;
  sc_clock clk_sig("clk_sig",10,SC_NS);
  dff dut("D_ff");
    dut.a(s_a);
  	dut.b(s_b);
  	dut.clk(clk_sig);
 cout << "Simulation starts" << endl;

  // 1. Initial state
  s_a = 0;
  sc_start(5, SC_NS); // Move away from the 0ns edge
  cout << "@" << sc_time_stamp() << " Initial b: " << s_b.read() << endl;

  // 2. Change 'a' in the MIDDLE of a clock cycle
  s_a = 555; 
  cout << "@" << sc_time_stamp() << " Changed a to 555" << endl;
  
  sc_start(2, SC_NS); // Still only at 7ns (No edge yet)
  cout << "@" << sc_time_stamp() << " b is still: " << s_b.read() << " (Not 555 yet!)" << endl;

  // 3. Run past the 10ns edge
  sc_start(5, SC_NS); // Now we are at 12ns
  cout << "@" << sc_time_stamp() << " After clock edge, b is: " << s_b.read() << endl;
}
  ????????????//////////design 

#include<systemc.h>
SC_MODULE(dff){
  sc_in<int>a;
  sc_in<bool> clk;
  sc_out<int>b;
  void application(){
    b.write(a.read());
  }
  SC_CTOR(dff){
    SC_METHOD(application);
    sensitive<<clk.pos();
  }
};
  
  
