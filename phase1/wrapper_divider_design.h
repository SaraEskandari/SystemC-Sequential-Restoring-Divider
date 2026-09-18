
#include <systemc.h>
#include "wrapper_divider_datapath.h"
#include "wrapper_divider_signed_controller.h"

template <int N = 16>
SC_MODULE(SignedDividerTop) {
    sc_in<sc_logic> clk;
    sc_in<sc_logic> rst;
    sc_in<sc_logic> start;
    sc_in<sc_lv<N>> dividend;
    sc_in<sc_lv<N>> divisor;
    
    sc_out<sc_logic> ready;
    sc_out<sc_lv<N>> quotient;
    sc_out<sc_lv<N>> reminder; 

    sc_signal<sc_logic> sig_ready_divider;
    sc_signal<sc_logic> sig_start_divider;
    sc_signal<sc_logic> sig_ctrl_signbit;
    sc_signal<sc_logic> sig_output_unsigned;


    WrapperDatapath<N>* DP;
    Controller* CNTRL;

    SC_CTOR(SignedDividerTop) {
        
        DP = new WrapperDatapath<N>("Datapath");
        DP->clk(clk);
        DP->rst(rst);
        DP->dividend(dividend);
        DP->divisor(divisor);
        DP->ctrl_signbit(sig_ctrl_signbit);
        DP->start_divider(sig_start_divider);
        DP->output_unsigned(sig_output_unsigned);
        DP->ready_divider(sig_ready_divider);
        DP->quotient(quotient);
        DP->reminder(reminder);

        CNTRL = new Controller("Controller");
        CNTRL->clk(clk);
        CNTRL->rst(rst);
        CNTRL->start(start);
        CNTRL->ready_divider(sig_ready_divider);
        CNTRL->ready(ready);
        CNTRL->start_divider(sig_start_divider);
        CNTRL->ctrl_signbit(sig_ctrl_signbit);
        CNTRL->output_unsigned(sig_output_unsigned);
    }
};
