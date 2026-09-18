
#include "divider_unsigned_tb.h"
#include <cstdlib> 

// void DividerTB::inputing() {
   
//     start = SC_LOGIC_0;
//     wait(175, SC_NS); 

//     //  100 / 3
//     divisorBus.write("0000000000000011");  
//     dividendBus.write("0000000001100100"); 
//     start = SC_LOGIC_1;
//     wait(100, SC_NS); 
//     start = SC_LOGIC_0;
    
//     wait(2400, SC_NS); 

//     // 50 / 7
//     divisorBus.write("0000000000000111");  
//     dividendBus.write("0000000000110010"); 
//     start = SC_LOGIC_1;
//     wait(100, SC_NS); 
//     start = SC_LOGIC_0;
    
//     wait(2400, SC_NS);
    
// }


void DividerTB::testing() {
   int number_of_test = 10;

    while (number_of_test > 0) {
        rst= SC_LOGIC_1;
        wait(); 
        rst= SC_LOGIC_0;
        wait(); 

        int dividend_number = rand() % 65535;
        int divisor_number = (rand() % 65534) + 1; 

        dividendBus= dividend_number;
        divisorBus= divisor_number; 

        start= SC_LOGIC_1;
        wait(); 
        start= SC_LOGIC_0;
        wait(); 

        wait(ready.posedge_event()); 

        int calculate_quitent = QBus.read().to_uint();
        int calculate_remainder = RBus.read().to_uint();
        int expected_quitent = dividend_number / divisor_number;
        int expected_remainder = dividend_number % divisor_number;

        if (calculate_quitent != expected_quitent || calculate_remainder != expected_remainder) {
            cout << "@ " << sc_time_stamp() << " : ERROR! " 
                 << dividend_number << " / " <<divisor_number 
                 << " -> Expected Quitent: " << expected_quitent << ", R: " << expected_remainder
                 << " | Got Q: " << calculate_quitent << ", R: " << calculate_remainder << endl;
        } else {
            cout << "@ " << sc_time_stamp() << " : SUCCESS! " 
                 << dividend_number << " / " << divisor_number << " = " << calculate_quitent 
                 << " (R: " << calculate_remainder << ")" << endl;
        }


        wait();
        --number_of_test;
    }

    // Stop simulation after all tests are done
    sc_stop();
}


void DividerTB::clocking() {
    // int i;
    // clk = SC_LOGIC_1;
    // for (i = 0; i <= 200; i++) {    
    while (true) {
        clk.write(SC_LOGIC_0);
        wait(50, SC_NS); 
        clk.write(SC_LOGIC_1);
        wait(50, SC_NS);
    }
}


// void DividerTB::resetting() {
//     rst = SC_LOGIC_0;
//     wait(10, SC_NS);
//     rst = SC_LOGIC_1; 
//     wait(10, SC_NS); 
//     rst = SC_LOGIC_0; 
// }

// void DividerTB::displaying() {
//         cout << "@ " << sc_time_stamp()
//              << " ready = " << ready.read()
//              << " Dividend = " << dividendBus.read()
//              << " Divisor = " << divisorBus.read()
//              << " Quotient = " << QBus.read()
//              << " Remainder = " << RBus.read() << endl;
             
//     }
