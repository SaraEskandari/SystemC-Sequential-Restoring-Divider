# Parameterized Sequential Restoring Divider in SystemC (RTL to BFM)

[![SystemC](https://img.shields.io/badge/SystemC-2.3.3%2B-blue.svg)](https://www.accellera.org/)
[![C++](https://img.shields.io/badge/C%2B%2B-17-green.svg)](https://en.cppreference.com/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Verification](https://img.shields.io/badge/Verification-Co--Simulation%20%26%20GTKWave-brightgreen.svg)]()

A fully parameterized, cycle-accurate sequential restoring divider hardware architecture implemented in **SystemC (C++17)**. This repository covers the complete digital design lifecycle across multiple abstraction levels: **RTL Datapath & Huffman FSM Controller**, **2's Complement Signed Wrapper**, **Bus-Functional Model (BFM)**, and **Co-Simulation Trace Alignment**.

---

## 📋 Table of Contents
- [Architecture Overview](#-architecture-overview)
- [Project Phases & Implementation Details](#-project-phases--implementation-details)
  - [Phase 1: Parameterized Unsigned Restoring Divider RTL](#phase-1-parameterized-unsigned-restoring-divider-rtl)
  - [Phase 2: Signed Division Extension & Wrapper](#phase-2-signed-division-extension--wrapper)
  - [Phase 3: Bus-Functional Modeling (BFM)](#phase-3-bus-functional-modeling-bfm)
  - [Phase 4: Co-Simulation & Trace Alignment](#phase-4-co-simulation--trace-alignment)
- [Mathematical Background & Algorithm](#-mathematical-background--algorithm)
- [Waveform Verification](#-waveform-verification)

---

## 🏛 Architecture Overview

The system is structured hierarchically, separating the datapath computation units from the control logic following standard digital design practices.

| Unsigned Divider Top-Level | Top-Level Structural View |
| :---: | :---: |
| ![Unsigned Divider](assets/unsigned%20divider.png) | ![Top View](assets/top%20view%20of%20unsigned%20divider.png) |

---

## 🔬 Project Phases & Implementation Details

### Phase 1: Parameterized Unsigned Restoring Divider RTL
* **Parametric Templates:** Configurable data bit-width ($N$) and counter width ($C = \lceil\log_2 N\rceil$).
* **Datapath Elements:**
  * Remainder Register (`RReg` / Accumulator) & Divisor Register (`DReg`).
  * Quotient Register (`QReg`) with serial shift-in capability.
  * Concatenator, Left Shifter (`LShifter`), Subtractor, and 2-to-1 Multiplexer for restoring logic.
  * Synchronous iteration counter (`Cnt`) with comparison flag (`cnt_comp`).
* **Huffman Controller Architecture:**
  Strict separation into three distinct SystemC processes:
  1. `seq_function` (`SC_THREAD`): State register transition sensitive to `clk.pos()` with asynchronous active-high `reset`.
  2. `comb_nextstate_function` (`SC_METHOD`): Combinational next-state decode logic sensitive to current state, `start`, and `ready`.
  3. `comb_output_function` (`SC_METHOD`): Moore/Mealy output control signal generation (`sel_shift`, `sel_sub`, `ser_q`, `enCnt`, `done`).
* **FSM State Progression:** `IDLE` $\rightarrow$ `INIT` $\rightarrow$ `LOAD` $\rightarrow$ `DIVIDE`.

### Phase 2: Signed Division Extension & Wrapper
* **Encapsulation:** Encapsulates the unsigned RTL core inside a 2's complement signed interface without altering internal core logic.
* **Magnitude Extraction:** Continuous sign extraction on input operands (`sc_int<W>`) using $N$-bit 2's complementers and multiplexers.
* **Sign Correction & Tracking:** 
  $$\text{Sign}(Q) = \text{Sign}(\text{Dividend}) \oplus \text{Sign}(\text{Divisor})$$
  $$\text{Sign}(R) = \text{Sign}(\text{Dividend})$$
  Signs are tracked through D flip-flops and restored at the output stage. Includes zero-division detection and boundary edge handling.

<p align="center">
  <img src="assets/wrapper.png" alt="Signed Wrapper Architecture" width="75%">
</p>

### Phase 3: Bus-Functional Modeling (BFM)
* **Transaction-Centric Abstraction:** Replaces cycle-by-cycle internal microarchitectural datapath transitions with high-level behavioral timing mimicry.
* **Protocol & Interface Parity:** Retains the exact external pin interface, handshaking transitions (`start`/`ready`/`done`), and cycle-accurate latency ($N$ clock cycles) as the RTL core.

### Phase 4: Co-Simulation & Trace Alignment
* **Dual-Model Testbench:** Concurrently instantiates the **Phase 2 Signed RTL Wrapper** and the **Phase 3 BFM**.
* **Lock-Step Verification:** Feeds identical pseudo-randomized stimulus vectors to both modules under the same clock generator.
* **Automated Checking:** Compares output data and handshaking signals cycle-by-cycle; logs timestamped status flags (`SUCCESS` / `ERROR`).
* **VCD Export:** Simultaneous multi-signal dump into `.vcd` files for visual inspection in GTKWave.

---

## 📐 Mathematical Background & Algorithm

The sequential restoring division calculates quotient $Q$ and remainder $R$ for dividend $Z$ and divisor $D$:
$$Z = D \cdot Q + R \quad \text{such that} \quad 0 \le R < |D|$$

### Algorithm Execution Loop (per iteration $i$):
1. **Left-Shift:** Shift register pair $[R, Q]$ left by 1 bit:
   $$R^{(i)\prime} = (R^{(i-1)} \ll 1) \mid Q_{N-1}^{(i-1)}$$
2. **Trial Subtraction:** 
   $$\Delta = R^{(i)\prime} - D$$
3. **Restoring / Update Step:**
   $$R^{(i)} = \begin{cases} \Delta, & \text{if } \Delta \ge 0 \quad (\text{Signbit} = 0 \implies \text{Non-Restoring}, \; Q_0^{(i)} = 1) \\ R^{(i)\prime}, & \text{if } \Delta < 0 \quad (\text{Signbit} = 1 \implies \text{Restoring}, \; Q_0^{(i)} = 0) \end{cases}$$

---



## 📊 Waveform Verification

* **Handshake Protocol:** De-assertion of `ready` upon `start` trigger pulse, locking input buses (`dividendBus`, `divisorBus`).
* **Trace Parity:** Signal traces from RTL and BFM align clock-for-clock across randomized test vectors.
* **Outputs:** Valid quotient and remainder outputs asserted simultaneously with `done = 1`.

---

## 📚 References

1. **[1]** D. A. Patterson and J. L. Hennessy, *Computer Organization and Design: The Hardware/Software Interface*, 5th ed. Waltham, MA: Morgan Kaufmann, 2014.
2. **[2]** IEEE Standard for Standard SystemC Language Reference Manual, *IEEE Std 1666-2011*, pp. 1–638, Jan. 2012.
3. **[3]** S. Palnitkar, *Verilog HDL: A Guide to Digital Design and Synthesis*, 2nd ed. Upper Saddle River, NJ: Prentice Hall, 2003.
4. **[4]** F. Vahid, *Digital Design with RTL Design, VHDL, and Verilog*, 2nd ed. Hoboken, NJ: John Wiley & Sons, 2010.
