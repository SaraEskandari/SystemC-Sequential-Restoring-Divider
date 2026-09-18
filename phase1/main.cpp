
#include <systemc.h>
#include "divider_unsigned_tb.h"

int sc_main(int argc, char **argv) {

    DividerTB TB1("Testbench_Top");

    sc_trace_file* vcdfile;
    vcdfile = sc_create_vcd_trace_file("Divider_Waveform");
    
    sc_trace(vcdfile, TB1.clk, "clk");
    sc_trace(vcdfile, TB1.rst, "rst");
    sc_trace(vcdfile, TB1.start, "start");
    sc_trace(vcdfile, TB1.ready, "ready");
    sc_trace(vcdfile, TB1.divisorBus, "divisorBus");
    sc_trace(vcdfile, TB1.dividendBus, "dividendBus");
    sc_trace(vcdfile, TB1.QBus, "QBus");
    sc_trace(vcdfile, TB1.RBus, "RBus");

    sc_start();
    return 0;
}
