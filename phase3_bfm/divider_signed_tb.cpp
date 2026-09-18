#include "divider_signed_tb.h"
#include <cstdlib>

void dividerTB::clocking() {
        while (true) {
            clk.write(SC_LOGIC_0);
            wait(50, SC_NS); 
            clk.write(SC_LOGIC_1);
            wait(50, SC_NS);
        }
    }


void dividerTB::testing() {

    int number_of_test = 10;
    
    while (number_of_test > 0) 
    {
        rst= SC_LOGIC_1;
        wait(); 
        rst= SC_LOGIC_0;
        wait(); 

        int dividend_number = (rand() % 65536) - 32768;
        int divisor_number = (rand() % 65535) - 32767; 
        if (divisor_number == 0) divisor_number = 1; 

        Dividend = dividend_number;
        Divisor = divisor_number; 

        start = SC_LOGIC_1;
        wait(); 
        start = SC_LOGIC_0;

        while (ready == SC_LOGIC_0) 
            wait();
        
        int calculate_quotient   = static_cast<int>(sc_dt::sc_int<16>(Quotient.read()));
        int calculate_remainder   = static_cast<int>(sc_dt::sc_int<16>(Remainder.read()));

        int expected_quotient = dividend_number / divisor_number;
        int expected_remainder = dividend_number % divisor_number;

        if (calculate_quotient != expected_quotient || calculate_remainder != expected_remainder) {
            cout << "@ " << sc_time_stamp() << " : ERROR! " 
                 << dividend_number << " / " << divisor_number 
                 << " -> Expected Quotient: " << expected_quotient << ", R: " << expected_remainder
                 << " | Got Q: " << calculate_quotient << ", R: " << calculate_remainder << endl;
        } 
        else {
            cout << "@ " << sc_time_stamp() << " : SUCCESS! " 
                 << dividend_number << " / " << divisor_number << " = " << calculate_quotient 
                 << " (R: " << calculate_remainder << ")" << endl;
        }


        
            wait();
            --number_of_test;
    }

    sc_stop();
}


