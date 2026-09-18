#include "wrapper_divider_signed_controller.h"

void Controller::comb_output_function() {
    
    ready           = SC_LOGIC_0;
    start_divider   = SC_LOGIC_0;
    ctrl_signbit    = SC_LOGIC_0;
    output_unsigned = SC_LOGIC_0;

    switch (p_state) {
        case IDLE:
            ready = SC_LOGIC_1;
            break;

        case INIT:
            ctrl_signbit = SC_LOGIC_1; 
            start_divider = SC_LOGIC_1;
            break;

        case DIVIDE:
            if (ready_divider == SC_LOGIC_1)
                  output_unsigned = SC_LOGIC_1;
            else
                  output_unsigned = SC_LOGIC_0;
            break;

        default:
            break;
    }
}

void Controller::comb_nextstate_function() {

    n_state = IDLE; 

    switch (p_state) {
        case IDLE:
            if (start == SC_LOGIC_1) 
                n_state = INIT;
            else
               n_state = IDLE;
            break;

        case INIT:
            if (start == SC_LOGIC_0)
                n_state = DIVIDE;
            else
               n_state = INIT;
            break;
    
            break;

        case DIVIDE:
            if (ready_divider == SC_LOGIC_1)
                n_state = IDLE;
            else
                n_state = DIVIDE;
            break;

        default:
            n_state = IDLE;
            break;
    }
}

void Controller::seq_function() {
    while(1){
        if (rst == '1') 
            p_state = IDLE;
        else if (clk-> event() && clk == '1')
            p_state = n_state;
        wait();

    }
}

