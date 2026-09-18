#include "divider_signed_tb.h"


int sc_main(int argc, char *argv[]) 
{

    dividerTB* TOP = new dividerTB("divider_signed_TB");

    sc_trace_file* VCDFile;
    VCDFile = sc_create_vcd_trace_file("Divider_Signed_Waveform");
    
    sc_trace(VCDFile, TOP->Dividend, "Dividend");
    sc_trace(VCDFile, TOP->Divisor,  "Divisor");
    sc_trace(VCDFile, TOP->clk,      "clk");
    sc_trace(VCDFile, TOP->rst,      "rst");
    sc_trace(VCDFile, TOP->start,    "start");
    sc_trace(VCDFile, TOP->ready,    "ready");
    sc_trace(VCDFile, TOP->Quotient, "Quotient");
    sc_trace(VCDFile, TOP->Remainder,"Remainder");

    sc_start(500000, SC_NS);
    sc_close_vcd_trace_file(VCDFile);

    return 0;
}
