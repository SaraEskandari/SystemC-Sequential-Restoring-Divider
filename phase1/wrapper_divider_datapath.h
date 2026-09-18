
#include <systemc.h>
#include "PARTSLIBRARY.h" 
#include "2's_complement.h"
#include "divider_unsigned_design.h" 


template <int N = 16>
SC_MODULE(WrapperDatapath) {

    sc_in<sc_logic> clk, rst;
    sc_in<sc_lv<N>> dividend, divisor;
    sc_in<sc_logic> ctrl_signbit, start_divider, output_unsigned;
    
    sc_out<sc_logic> ready_divider; 
    sc_out<sc_lv<N>> quotient;
    sc_out<sc_lv<N>> reminder; 


    sc_signal<sc_logic> signal_dividend_sign;
    sc_signal<sc_logic> signal_divisor_sign;
    sc_signal<sc_logic> signal_xor_sign_output;
    sc_signal<sc_lv<1>> signal_quotient_sign_in_vector;
    sc_signal<sc_lv<1>> signal_quotient_sign_out_vector;
    sc_signal<sc_logic> signal_quotient_sign_bit;
    sc_signal<sc_logic> signal_reminder_sign_bit;
    
    sc_signal<sc_lv<N>> signal_complemented_dividend;
    sc_signal<sc_lv<N>> signal_absolute_dividend;
    sc_signal<sc_lv<N>> signal_complemented_divisor;
    sc_signal<sc_lv<N>> signal_absolute_divisor;
     
    sc_signal<sc_lv<N>> signal_unsigned_quotient;
    sc_signal<sc_lv<N>> signal_unsigned_reminder;
    
    sc_signal<sc_lv<N>> signal_complemented_quotient;
    sc_signal<sc_lv<N>> signal_signed_quotient;
    sc_signal<sc_lv<N>> signal_complemented_reminder;
    sc_signal<sc_lv<N>> signal_signed_reminder;


    XorGate2* xor_gate_sign;
    DFlipflop<1>* d_flipflop_quotient_sign;
    
    TwosComplement<N>* twos_complement_dividend;
    Mux2to1<N>* multiplexer_dividend;
    
    TwosComplement<N>* twos_complement_divisor;
    Mux2to1<N>* multiplexer_divisor;
    
    DividerTop* divider_unsigned_core; 
    
    TwosComplement<N>* twos_complement_quotient;
    Mux2to1<N>* multiplexer_quotient;
    DFlipflop<N>* d_flipflop_quotient;
    
    TwosComplement<N>* twos_complement_reminder;
    Mux2to1<N>* multiplexer_reminder;
    DFlipflop<N>* d_flipflop_reminder;


    SC_CTOR(WrapperDatapath) {
        SC_METHOD(extract_signs);
        sensitive << dividend << divisor << signal_quotient_sign_out_vector << signal_xor_sign_output;

        xor_gate_sign = new XorGate2("xor_gate_sign");
        xor_gate_sign->in1(signal_dividend_sign);
        xor_gate_sign->in2(signal_divisor_sign);
        xor_gate_sign->out(signal_xor_sign_output);
        
        d_flipflop_quotient_sign = new DFlipflop<1>("d_flipflop_quotient_sign");
        d_flipflop_quotient_sign->clk(clk);
        d_flipflop_quotient_sign->rst(rst);
        d_flipflop_quotient_sign->en(ctrl_signbit); 
        d_flipflop_quotient_sign->D(signal_quotient_sign_in_vector);
        d_flipflop_quotient_sign->Q(signal_quotient_sign_out_vector);

        twos_complement_dividend = new TwosComplement<N>("twos_complement_dividend");
        twos_complement_dividend->in_data(dividend);
        twos_complement_dividend->out_data(signal_complemented_dividend);

        multiplexer_dividend = new Mux2to1<N>("multiplexer_dividend");
        multiplexer_dividend->in0(dividend);
        multiplexer_dividend->in1(signal_complemented_dividend);
        multiplexer_dividend->sel(signal_dividend_sign);
        multiplexer_dividend->out(signal_absolute_dividend);

        twos_complement_divisor = new TwosComplement<N>("twos_complement_divisor");
        twos_complement_divisor->in_data(divisor);
        twos_complement_divisor->out_data(signal_complemented_divisor);

        multiplexer_divisor = new Mux2to1<N>("multiplexer_divisor");
        multiplexer_divisor->in0(divisor);
        multiplexer_divisor->in1(signal_complemented_divisor);
        multiplexer_divisor->sel(signal_divisor_sign);
        multiplexer_divisor->out(signal_absolute_divisor);

        divider_unsigned_core = new DividerTop("divider_unsigned_core");
        divider_unsigned_core->clk(clk);
        divider_unsigned_core->rst(rst);
        divider_unsigned_core->start(start_divider);
        divider_unsigned_core->dividendBus(signal_absolute_dividend);
        divider_unsigned_core->divisorBus(signal_absolute_divisor);
        divider_unsigned_core->QBus(signal_unsigned_quotient);
        divider_unsigned_core->RBus(signal_unsigned_reminder);
        divider_unsigned_core->ready(ready_divider);

        twos_complement_quotient = new TwosComplement<N>("twos_complement_quotient");
        twos_complement_quotient->in_data(signal_unsigned_quotient);
        twos_complement_quotient->out_data(signal_complemented_quotient);

        multiplexer_quotient = new Mux2to1<N>("multiplexer_quotient");
        multiplexer_quotient->in0(signal_unsigned_quotient);
        multiplexer_quotient->in1(signal_complemented_quotient);
        multiplexer_quotient->sel(signal_quotient_sign_bit);
        multiplexer_quotient->out(signal_signed_quotient);

        d_flipflop_quotient = new DFlipflop<N>("d_flipflop_quotient");
        d_flipflop_quotient->clk(clk);
        d_flipflop_quotient->rst(rst);
        d_flipflop_quotient->en(output_unsigned); 
        d_flipflop_quotient->D(signal_signed_quotient);
        d_flipflop_quotient->Q(quotient);

        twos_complement_reminder = new TwosComplement<N>("twos_complement_reminder");
        twos_complement_reminder->in_data(signal_unsigned_reminder);
        twos_complement_reminder->out_data(signal_complemented_reminder);

        multiplexer_reminder = new Mux2to1<N>("multiplexer_reminder");
        multiplexer_reminder->in0(signal_unsigned_reminder);
        multiplexer_reminder->in1(signal_complemented_reminder);
        multiplexer_reminder->sel(signal_dividend_sign); 
        multiplexer_reminder->out(signal_signed_reminder);

        d_flipflop_reminder = new DFlipflop<N>("d_flipflop_reminder");
        d_flipflop_reminder->clk(clk);
        d_flipflop_reminder->rst(rst);
        d_flipflop_reminder->en(output_unsigned);
        d_flipflop_reminder->D(signal_signed_reminder);
        d_flipflop_reminder->Q(reminder);
    }

    void extract_signs() {
        sc_lv<N> current_dividend = dividend;
        sc_lv<N> current_divisor = divisor;
        
        signal_dividend_sign= current_dividend[N-1];
        signal_divisor_sign= current_divisor[N-1];
        
        sc_lv<1> temp_quotient_in;
        temp_quotient_in[0] = signal_xor_sign_output;
        signal_quotient_sign_in_vector= temp_quotient_in;
        
         signal_quotient_sign_bit = signal_quotient_sign_out_vector.read()[0];
    }
};
