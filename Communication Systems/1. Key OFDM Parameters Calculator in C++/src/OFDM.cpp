/*
 * Copyright (c) 2025 Christos Axelos.  
 * Provided solely for recruitment evaluation.  
 * See LICENSE.txt for full terms.
 */
#include "OFDM.hpp"
#include <iomanip>
#include <cmath>

OFDM::OFDM() { 
    this->symbolsPerSlot = SYMBOLS_PER_SLOT_IN_5G_NR;     
}

/* Get from user the carrier bandwidth in MHz
*/
void OFDM::get_carrier_bandwidth_MHz_from_user(void) {
    std::cout << "Enter carrier bandwidth (MHz): ";
    std::cin >> this->bandwidthMHz; // TODO: could do some error check in user's value but I didn't, since there was no requirement
}


/* numerology μ and subcarrier spacing

    Requirement: 
        [User's Req]: "μ-index in domain [M_INDEX_MIN, +M_INDEX_MAX]""
    
    Purpose:
        Get the numerology μ from the user.
*/
void OFDM::get_m_index_from_user(void) {
    unsigned short m_index =5; // some random, invalid initialization

    while (1) { 
        std::cout << "Enter numerology mu index (0-4): ";
        std::cin >> m_index;

        if(m_index > M_INDEX_MAX) {
            std::cerr << "Error: mu index must be between 0 and " << M_INDEX_MAX << ".\n\n";
        }
        else {
            this->m_index = m_index;
            this->numOfSlotsPer1msSubframe = ( (unsigned short)1 << m_index); // this command is equivalent to pow(2.0, m_index)
            break;
        }
    }
}


/* OFDM subcarrier spacing calculation

    Requirement:
        [3GPP TS 38.211, v17.2.0, §4.2]: "The subcarrier spacing Δf is defined as 15 × 2^μ kHz, where μ is the numerology index."
        "The Baseline subcarrier space"
    Comment: 
        1. Practically, this shows "how far apart these subcarriers are in frequency"
    Suggestions:
        In case we are interested on High Performance:
            1. substitute the "2^μ" with a left shift
            2. Consider the substitution of this multiplication with a "binary-search based" if/else

*/
void OFDM::set_subcarrier_spacing_in_kHz(void) {
    this->subcarrierSpacing_kHz = BASELINE_SUBCARRIER_SPACE_IN_kHz * this->numOfSlotsPer1msSubframe; // pow(double base, double exponent)
}


/* Number of Subcarrier calculation
 * Requirement:
 *      - TODO
 * Comment:
 *      - Note: This is an approximation. In practice, the standard defines channel-edge guard bands 
 *         and discrete PRB sizes, so the actual number of subcarriers may be slightly less. 
 */
void OFDM::set_num_of_subcarriers(void) {
    this->numOfSubcarriers = static_cast<unsigned short>(std::floor(  (this->bandwidthMHz * 1000) / this->subcarrierSpacing_kHz));
}


/* Slots per subframe and frame

    Requirements:
        1. [GPP TS 38.211 §4.3.2), Table 4.3.2-1]: "For normal cyclic prefix and for For 5G NR, the number of OFDM symbols per slot, slots per frame and slots per subframe  are given from Table 4.3.2-1"
        2. [GPP TS 38.211 §4.3.2), Table 4.3.2-2]: "For extended cyclic prefix and for For 5G NR, the number of OFDM symbols per slot, slots per frame and slots per subframe  are given from Table 4.3.2-1"
    */
void OFDM::set_num_of_slots_per_frame_and_subframe(void) {
    this->slotsPerSubframe = this->numOfSlotsPer1msSubframe;
    this->slotsPerFrame = NUM_OF_SUBFRAMES_PER_10MS_FRAME * this->numOfSlotsPer1msSubframe;    
}


/* OFDM Slot Duration in ms (flexible)
    Requirement:
        [GPP TS 38.211 §4.3.2]: It is an indirect Req, since we know the number of Slots per Frame and the duration of each Subframe (1ms)    
*/
void OFDM::set_slot_duration_in_ms(void) {
    this->slotDuration_ms = 1.0 / this->numOfSlotsPer1msSubframe; 
}


/* OFDM Symbol Duration (Cyclic Prefix included) calculation
    Requirement: 
        1. [3GPP TS 38.211 §4.3] TODO
    Comment:
        - Bibliography uses 1e3 instead of "1000" in order to convert kHz to microseconds.
        - For Simplicity reasons, I kept the Cyclic Prefix time equal to zero (it didn't have the time to implement the equation)
    TODO:
        - Substitute the CYCLIC_PREFIX_TIME=0us with the real equation.
*/
void OFDM::set_symbol_duration_in_us(void) {
    this->symbolDurationWithoutCyclicPrefix_us = 1e3 / this->subcarrierSpacing_kHz;
    this->symbolDurationWithCyclicPrefix_us = (1 + CYCLIC_PREFIX_FACTOR) * this->symbolDurationWithoutCyclicPrefix_us;
}

/* OFDM Cyclic Prefix Duration calculation
    Requirement: 
        1. [3GPP TS 38.211 §4.3] TODO
    Comment:
        - For simplicity reasons, I used 25% as CYCLIC_PREFIX_FACTOR
*/
void OFDM::set_cyclic_prefix_duration_in_us(void) {
    this->cyclicPrefixDuration_us = CYCLIC_PREFIX_FACTOR * (1e3 / this->subcarrierSpacing_kHz);
}


/*
 *
 */
void OFDM::set_number_of_physical_resource_blocks(void) {
    this->n_PRB = this->numOfSubcarriers / NUM_OF_SUBCARRIERS_PER_PHYSICAL_RESOURCE_BLOCK;
}

/* Compute all OFDM params

    Requirements:
        No reqs
    Purpose:
        1. Public function that performs all the parameter calculations, based on numerology μ. These params are:
            a. Subcarrier Spacing
            b. Number of Slots per Frame and Subframe
            c. Duration of Slot, Symbol
        2. Inside this function we call several sub-functions in order to perform the initializations (divide & conquer principle)

*/
void OFDM::compute_params(void) {
    this->set_subcarrier_spacing_in_kHz();
    this->set_num_of_subcarriers();
    this->set_num_of_slots_per_frame_and_subframe();
    this->set_slot_duration_in_ms();
    this->set_symbol_duration_in_us();
    this->set_cyclic_prefix_duration_in_us();
    this->set_number_of_physical_resource_blocks();
}


/* Print all Key OFDM Params
    Requirement: Print in user's screen.
*/
void OFDM::print_params(void) {

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n===== OFDM Configuration =====\n\n";
    std::cout << "Inputs:\n";
    std::cout << "\tNumerology m-index: " << this->m_index << "\n";
    std::cout << "\tSubcarrier Spacing: " << this->subcarrierSpacing_kHz << " kHz\n";
    
    std::cout << "Subcarriers/Slots/Symbols:\n";
    std::cout << "\tNumber of Physical Resource Blocks: " << this->n_PRB << "\n";
    std::cout << "\tNumber of Subcarriers: " << this->numOfSubcarriers << "\n";
    std::cout << "\tSlots per Frame: " << this->slotsPerFrame << "\n";
    std::cout << "\tSlots per Subframe: " << this->slotsPerSubframe << "\n";
    std::cout << "\tSymbols per Slot: " << this->symbolsPerSlot << "\n";
    
    std::cout << "Timings:\n";
    std::cout << "\tSlot Duration: " << this->slotDuration_ms << " ms\n";
    std::cout << "\tSymbol Duration (Cyclic Prefix included): " << this->symbolDurationWithCyclicPrefix_us << " us\n";
    std::cout << "\tSymbol Duration (Without Cyclic Prefix): " << this->symbolDurationWithoutCyclicPrefix_us << " us\n";
    std::cout << "\tCyclic Prefix Duration: " << this->cyclicPrefixDuration_us << " us\n";
    std::cout << "===============================\n";

}
