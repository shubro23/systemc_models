#include <systemc.h>
#include<design.cpp>
int sc_main(int argc, char* argv[])
{
  sc_signal<int> a_sig,b_sig,c_sig;
  Adder adder("Adder");
  adder.a(a_sig);
  adder.b(b_sig);
  adder.c(c_sig);
  sc_start(0,SC_NS);
  a_sig.write(3);
  b_sig.write(4);
  sc_start(1,SC_NS);
  cout<<"At "<<sc_time_stamp()<<" c=  "<<c_sig.read()<<endl;
  a_sig.write(7);
  sc_start(3,SC_NS);
    cout<<"At "<<sc_time_stamp()<<" c= "<<c_sig.read()<<endl;
	a_sig.write(9);
  sc_start(6,SC_NS);
  cout<<"AT"<<sc_time_stamp()<<"c="<<c_sig.read()<<endl;
  return 0;
}
