#include <systemc.h>
SC_MODULE(controller) {

    sc_in<sc_logic>  clk, rst, start;
    sc_in<sc_logic>  cnt_comp, signbit;

    sc_out<sc_logic> done;
    sc_out<sc_logic> clr_counter, init_r;
    sc_out<sc_logic> load_d, load_q, load_r;
    sc_out<sc_logic> en_cnt, shl_q;
    sc_out<sc_logic> ser_q, sel_shift, sel_sub;

    enum states {IDLE, INIT, LOAD, DIVIDE}; 
    sc_signal<states> p_state, n_state; 

    SC_CTOR(controller) {

        SC_METHOD(comb_nextstate_function);
        sensitive << p_state << start << cnt_comp ;

        SC_METHOD(comb_output_function);
        sensitive << p_state << start << cnt_comp << signbit;

        SC_THREAD(seq_function);
        sensitive << clk << rst;
    };
    void comb_nextstate_function();
    void comb_output_function();
    void seq_function();
};
