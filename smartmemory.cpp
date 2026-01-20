// this is a smart memeory which create a partition of the memory as one is read only and other is write and read as well
#include<systemc>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
using namespace sc_core;
SC_MODULE(Target){
  tlm_utils::simple_target_socket<Target> tsocket;
  int mem[64];
  SC_CTOR(Target):tsocket("tsocket"){
    tsocket.register_b_transport(this,&Target::b_transport);
  }

void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay){
   tlm::tlm_command cmd = trans.get_command();
    sc_dt::uint64          adr = trans.get_address();
    unsigned char*   ptr = trans.get_data_ptr();

    if (cmd == tlm::TLM_WRITE_COMMAND) {
      
        // Copy data into local memory
     if(adr<=31){//checking its not more the size 
        memcpy(&mem[adr], ptr, trans.get_data_length());
    
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
       
       std::cout << "TARGET: Received value " << *(int*)ptr 
              << " at address " << adr 
              << " at time " << sc_time_stamp() << std::endl;
      }
      else{
        trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
      }
    }else if (cmd == tlm::TLM_READ_COMMAND) { // ADD THIS BACK
        if (adr < 64) {
            // Copy FROM Target memory TO the Initiator's pointer
            memcpy(ptr, &mem[adr], trans.get_data_length());
            trans.set_response_status(tlm::TLM_OK_RESPONSE);
        } else {
            trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
        }
    }
  
} 
  };
  
  SC_MODULE(Initiator){
  tlm_utils::simple_initiator_socket<Initiator> isocket;
  int mem[64];
  SC_CTOR(Initiator):isocket("isocket"){
    SC_THREAD(thread_process);
    
  }
    void thread_process(){
      tlm::tlm_generic_payload *trans= new tlm::tlm_generic_payload;
      sc_time delay=sc_time(10,SC_NS);


      //for write to memory CPU -> MEMORY
      int data =101;
      trans->set_command(tlm::TLM_WRITE_COMMAND);
      trans->set_address(40);
      trans->set_data_ptr(reinterpret_cast<unsigned char*>(&data));// sharing the data pointer of where the date is being stored!
      trans->set_data_length(4);
      isocket->b_transport(*trans, delay);

      //Read from memory to cpu mem->CPU
      int read_data=0;
      
      trans->set_command(tlm::TLM_READ_COMMAND);
      trans->set_data_ptr(reinterpret_cast<unsigned char*>(&read_data));
      trans->set_data_length(4);
      isocket->b_transport(*trans,delay);
      std::cout << "INITIATOR: Read back value " << read_data << " from Target!" << std::endl;
    }
  };
  int sc_main(int argc, char* argv[]) {
  Initiator cpu("cpu");
  Target ram("ram");

  // Bind the sockets (The "Cable")
  cpu.isocket.bind(ram.tsocket);

  sc_start();
  return 0;
}
  
      
      
      
