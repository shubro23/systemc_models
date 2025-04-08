#include <systemc.h>
SC_MODULE(Adder){
  sc_in<int>a;
  sc_in<int>b;
  sc_out<int>c;
  void adding(){
    while(true){
      wait(2,SC_NS);
      c.write(a.read()+b.read());
    }
  }
  SC_CTOR(Adder){
    SC_THREAD(adding);
    sensitive<<a<<b;
  }
};

