#include <systemc.h>
#include "divider_signed.h" 

SC_MODULE(dividerTB) {
    
    sc_signal<sc_logic> clk, rst, start, ready;
    sc_signal<sc_lv<16>> Dividend, Divisor, Quotient, Remainder;
    divider<16, 9>* DIV;
    SC_CTOR(dividerTB) {
       
            DIV = new divider<16, 9>("Divider_signed");
            DIV->Dividend(Dividend);
            DIV->Divisor(Divisor);
            DIV->clk(clk);
            DIV->rst(rst);
            DIV->start(start);
            DIV->Quotient(Quotient);
            DIV->Remainder(Remainder);
            DIV->ready(ready);

        SC_THREAD(testing);
        sensitive << clk.posedge_event();
        SC_THREAD(clocking);
    }
    void clocking();
    void testing();
};

