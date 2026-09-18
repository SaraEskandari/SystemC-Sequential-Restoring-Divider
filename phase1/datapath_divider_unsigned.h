
#include <systemc.h>
#include "PARTSLIBRARY.H"
#include "Dregister.h"
#include "Qregister.h"
#include "Rregister.h"
#include "subtractor.h"

SC_MODULE(Datapath) {
    
  
    sc_in<sc_logic> clk, rst;
    sc_in<sc_logic> loadD;
    sc_in<sc_logic> InitR, loadR;
    sc_in<sc_logic> SelSub;
    sc_in<sc_logic> ShIQ, loadQ, SerQ;
    sc_in<sc_logic> clrCnt, enCnt; 
    sc_in<sc_lv<16>> divisorBus, dividendBus;

    sc_out<sc_logic> signbit, cnt_comp; 
    sc_out<sc_lv<16>> RBus, QBus;
    sc_out<sc_lv<4>> count_out;

    sc_signal<sc_lv<16>> Dregister_out;
    sc_signal<sc_lv<16>> Qregister_out;
    sc_signal<sc_lv<16>> Rregister_out;
    sc_signal<sc_lv<16>> shift_out;
    sc_signal<sc_lv<16>> sub_out;
    sc_signal<sc_lv<16>> mux_out;
    sc_signal<sc_logic>  Qregister_msb;
 
   
    DRegister<16>*   DReg;
    QRegister<16>*   QReg;
    RRegister<16>*   RReg;
    LeftShifter<16>* LShifter;
    Subtractor<16>*  Sub;
    Mux2to1<16>*     Mux;
    Counter<4>*      Cnt;

    SC_CTOR(Datapath) {

        DReg = new DRegister<16>("Divisor_Register");
        DReg->clk(clk);
        DReg->rst(rst);
        DReg->load(loadD);
        DReg->regin(divisorBus);
        DReg->regout(Dregister_out);

        QReg = new QRegister<16>("Quotient_Register");
        QReg->clk(clk);
        QReg->rst(rst);
        QReg->load(loadQ);
        QReg->shl(ShIQ);
        QReg->ser_in(SerQ);
        QReg->regin(dividendBus);
        QReg->regout(Qregister_out);

        RReg = new RRegister<16>("Remainder_Register");
        RReg->clk(clk);
        RReg->rst(rst);
        RReg->load(loadR);
        RReg->init(InitR);
        RReg->regin(mux_out);
        RReg->regout(Rregister_out);

        LShifter = new LeftShifter<16>("Left_Shifter_Unit");
        LShifter->in_data(Rregister_out);
        LShifter->ser_in(Qregister_msb);
        LShifter->out_data(shift_out);

        Sub = new Subtractor<16>("Subtractor_Unit");
        Sub->in1(shift_out); 
        Sub->in2(Dregister_out);     
        Sub->out(sub_out);
        Sub->signbit(signbit);

        Mux = new Mux2to1<16>("Multiplexer");
        Mux->in0(shift_out); 
        Mux->in1(sub_out);   
        Mux->sel(SelSub);
        Mux->out(mux_out);

        Cnt = new Counter<4>("Iteration_Counter");
        Cnt->clk(clk);
        Cnt->rst(rst);
        Cnt->clr(clrCnt);
        Cnt->en(enCnt);
        Cnt->cnt_out(count_out);

        SC_METHOD(datapath_assign);
        sensitive << Qregister_out << Rregister_out << count_out;
    }

        void datapath_assign() {
       Qregister_msb = Qregister_out.read()[15]; 
       RBus = Rregister_out;
       QBus = Qregister_out; 
       cnt_comp.write((count_out.read().to_uint() == 15) ? SC_LOGIC_1 : SC_LOGIC_0);
    }
};
