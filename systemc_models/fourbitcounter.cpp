
// test bench of 4 bit counter 
#include<systemc.h>
#include<design.cpp>
using namespace std;
int sc_main(int argc, char* argv[]){
 sc_signal<sc_uint<4>>s_out;
  sc_signal<bool>s_reset;
  sc_clock clk_sig("clk_sig", 10, SC_NS);
  
  
  fourbitcounter dut("counter");
  dut.count_out(s_out);
  dut.reset(s_reset);
  dut.clk(clk_sig);
  
    s_reset = 1;
    sc_start(20, SC_NS);
    cout << "@" << sc_time_stamp() << " Reset active, count: " << s_out.read() << endl;

    // 4. Counting Phase (Release reset)
    s_reset = 0;
    
    // Run for 17 cycles to see it hit 15 and then wraparound to 0
    for(int i = 0; i < 18; i++) {
        sc_start(10, SC_NS);
        cout << "@" << sc_time_stamp() << " Count: " << s_out.read() << endl;
    }

    return 0;
};
  // design of 4 bit counter in cpp

#include<systemc.h>
SC_MODULE(fourbitcounter){
  sc_in<bool>reset;
  sc_in<bool> clk;
  sc_uint<4>count_val;
  sc_out<sc_uint<4>>count_out;
  void count(){
    if(reset.read()){
    count_val=0;
    }
      else{
        count_val+=1;
      }
    count_out.write(count_val);
  }
  SC_CTOR(fourbitcounter){
    SC_METHOD(count);
    sensitive<<clk.pos();
  }
};
   

  
  
  
