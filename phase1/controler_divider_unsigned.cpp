#include "controler_divider_unsigned.h"

void controller::comb_output_function() {


    done        = SC_LOGIC_0;
    clr_counter = SC_LOGIC_0;
    init_r      = SC_LOGIC_0;
    load_d      = SC_LOGIC_0;
    load_q      = SC_LOGIC_0;
    load_r      = SC_LOGIC_0;
    en_cnt      = SC_LOGIC_0;
    shl_q       = SC_LOGIC_0;
    ser_q       = SC_LOGIC_0;
    sel_shift   = SC_LOGIC_0;
    sel_sub     = SC_LOGIC_0;

    switch (p_state) {
        case IDLE:
            done = SC_LOGIC_1;
            break;

        case INIT:
            clr_counter = SC_LOGIC_1;
            init_r      = SC_LOGIC_1;
            done        = SC_LOGIC_0;
            break;

        case LOAD:
            load_d = SC_LOGIC_1;
            load_q = SC_LOGIC_1;
            break;

        case DIVIDE:
            en_cnt = SC_LOGIC_1;
            shl_q  = SC_LOGIC_1;
            load_r = SC_LOGIC_1;

            if (signbit == SC_LOGIC_1) {
                ser_q     = SC_LOGIC_0;
                sel_shift = SC_LOGIC_1;
                sel_sub   = SC_LOGIC_0;
            } 
            else {
                ser_q     = SC_LOGIC_1;
                sel_shift = SC_LOGIC_0;
                sel_sub   = SC_LOGIC_1;
            }
            break;

        default:
            done        = SC_LOGIC_0;
            clr_counter = SC_LOGIC_0;
            init_r      = SC_LOGIC_0;
            load_d      = SC_LOGIC_0;
            load_q      = SC_LOGIC_0;
            load_r      = SC_LOGIC_0;
            en_cnt      = SC_LOGIC_0;
            shl_q       = SC_LOGIC_0;
            ser_q       = SC_LOGIC_0;
            sel_shift   = SC_LOGIC_0;
            sel_sub     = SC_LOGIC_0;
            break;
    }
}


void controller::comb_nextstate_function() {
  
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
                n_state = LOAD;
            else 
                n_state = INIT;
            break;           
            
        case LOAD:
            n_state = DIVIDE;
            break;
            
        case DIVIDE:
            if (cnt_comp == SC_LOGIC_1) 
                n_state = IDLE;
            else 
                n_state = DIVIDE;           
            break;

        default:
            n_state = IDLE;
            break;
    }
}

void controller::seq_function() {

    while(1){
        if (rst == '1') 
            p_state = IDLE;
        else if (clk-> event() && clk == '1')
            p_state = n_state;
        wait();

    }

}
