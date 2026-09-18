#include <systemc.h>
#include "divider_signed_tb.h" 

int sc_main(int argc, char **argv) {

    SignedDividerTB TB1("testbench1");

    sc_trace_file* vcdfile;
    vcdfile = sc_create_vcd_trace_file("Signed_Divider_Waveform");

    sc_trace(vcdfile, TB1.clk, "clk");
    sc_trace(vcdfile, TB1.rst, "rst");
    sc_trace(vcdfile, TB1.start, "start");
    sc_trace(vcdfile, TB1.ready, "ready");
    sc_trace(vcdfile, TB1.dividend, "dividend");
    sc_trace(vcdfile, TB1.divisor, "divisor");
    sc_trace(vcdfile, TB1.quotient, "quotient");
    sc_trace(vcdfile, TB1.reminder, "reminder");

    sc_start();
    return 0;
}
