#include <systemc.h>
#include "divider_unsigned_design.h"

SC_MODULE(DividerTB) {

    sc_signal<sc_logic> clk, rst, start;
    sc_signal<sc_lv<16>> divisorBus, dividendBus;
    sc_signal<sc_lv<16>> RBus, QBus;
    sc_signal<sc_logic> ready;

    DividerTop* div_top;

    SC_CTOR(DividerTB) {
        
        div_top = new DividerTop("Divider_1");
        div_top->clk(clk);
        div_top->rst(rst);
        div_top->start(start);
        div_top->divisorBus(divisorBus);
        div_top->dividendBus(dividendBus);
        div_top->RBus(RBus);
        div_top->QBus(QBus);
        div_top->ready(ready);

        SC_THREAD(testing);
        sensitive << clk.posedge_event();

        SC_THREAD(clocking);
    }
    void clocking();
    void testing();
};

