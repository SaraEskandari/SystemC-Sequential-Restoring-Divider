#include <systemc.h>
#include "datapath_divider_unsigned.h"
#include "controler_divider_unsigned.h" 

SC_MODULE(DividerTop) {

    sc_in<sc_logic> clk, rst, start;
    sc_in<sc_lv<16>> divisorBus, dividendBus;
    
    sc_out<sc_lv<16>> RBus, QBus;
    sc_out<sc_logic> ready;

    sc_signal<sc_logic> load_d, init_r, load_r;
    sc_signal<sc_logic> sel_sub, shl_q, load_q, ser_q, sel_shift;
    sc_signal<sc_logic> clr_counter, en_cnt;
    sc_signal<sc_logic> signbit, cnt_comp;
    sc_signal<sc_lv<4>> count_out; 

    Datapath* DP;
    controller*      CNTRL; 

    SC_CTOR(DividerTop) {

        DP = new Datapath("Datapath");
        DP->clk(clk);
        DP->rst(rst);
        DP->loadD(load_d);
        DP->InitR(init_r);
        DP->loadR(load_r);
        DP->SelSub(sel_sub);
        DP->ShIQ(shl_q);
        DP->loadQ(load_q);
        DP->SerQ(ser_q);
        DP->clrCnt(clr_counter);
        DP->enCnt(en_cnt);
        DP->divisorBus(divisorBus);
        DP->dividendBus(dividendBus);
        DP->RBus(RBus);
        DP->QBus(QBus);
        DP->count_out(count_out);
        DP->signbit(signbit);
        DP->cnt_comp(cnt_comp);

        CNTRL = new controller("Controller");
        CNTRL->clk(clk);
        CNTRL->rst(rst);
        CNTRL->start(start);
        CNTRL->signbit(signbit);
        CNTRL->cnt_comp(cnt_comp);
        CNTRL->load_d(load_d);
        CNTRL->init_r(init_r);
        CNTRL->load_r(load_r); 
        CNTRL->sel_sub(sel_sub);
        CNTRL->sel_shift(sel_shift); 
        CNTRL->shl_q(shl_q);
        CNTRL->load_q(load_q);
        CNTRL->ser_q(ser_q);
        CNTRL->clr_counter(clr_counter);
        CNTRL->en_cnt(en_cnt);
        CNTRL->done(ready);
    }
};

