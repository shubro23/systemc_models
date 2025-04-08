#include <systemc.h>
#include<adder.h>
SC_MODULE(Testbench){
  sc_signal<int> a_sig,b_sig,c_sig;
  Adder* adder;
Void adding_delay(){
a_sig=0;
b_sig=0;
wait(5,SC_NS);
a_sig=5;
b_sig=7;
wait(4,SC_NS);
b_sig=10;
wait(3,SC_NS);
a_sig=7;
b_sig=8;
wait(5,SC_NS);
void monitor(){
while(true){
wait();
SC_REPORT<<"@"<<sc_time_stamp()<<"output"<<c_sig.read()<<endl;}
}
SC_CTOR(Testbench){
adder = new adder("adder");
  adder->a(a_sig); 
  adder->b(b_sig);
  adder->c(c_sig);
SC_THREAD(adding_delay);
SC_METHOD(monitor);
sensetive<<c_sig;
}
};
  
