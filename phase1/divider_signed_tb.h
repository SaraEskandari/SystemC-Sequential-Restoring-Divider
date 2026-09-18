#include <systemc.h>
#include "wrapper_divider_design.h"
SC_MODULE(SignedDividerTB) {
    sc_signal<sc_logic> clk, rst, start, ready;
    sc_signal<sc_lv<16>> dividend, divisor, quotient, reminder;

    SignedDividerTop<16>* DividerSign;

    SC_CTOR(SignedDividerTB) {
        DividerSign = new SignedDividerTop<16>("Signed_Divider");
        DividerSign->clk(clk);
        DividerSign->rst(rst);
        DividerSign->start(start);
        DividerSign->dividend(dividend);
        DividerSign->divisor(divisor);
        DividerSign->ready(ready);
        DividerSign->quotient(quotient);
        DividerSign->reminder(reminder);

        SC_THREAD(testing);
        sensitive << clk.posedge_event();

        SC_THREAD(clocking);
    }
    void clocking();
    void testing();

};
