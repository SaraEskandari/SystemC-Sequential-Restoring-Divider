#include <systemc.h>

SC_MODULE(Controller) {

    sc_in<sc_logic> clk, rst, start;
    sc_in<sc_logic> ready_divider;
    
    sc_out<sc_logic> ready;
    sc_out<sc_logic> start_divider;
    sc_out<sc_logic> ctrl_signbit;
    sc_out<sc_logic> output_unsigned;

    enum states { IDLE, INIT, DIVIDE };
    sc_signal<states> p_state, n_state;


    SC_CTOR(Controller) {
        
        SC_METHOD(comb_nextstate_function);
        sensitive << p_state << start << ready_divider;

        SC_METHOD(comb_output_function);
        sensitive << p_state << ready_divider;


        SC_THREAD(seq_function);
        sensitive << clk << rst; 
    };

    void comb_nextstate_function();
    void comb_output_function();
    void seq_function();
};