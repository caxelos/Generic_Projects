/*
 * Copyright (c) 2025 Christos Axelos.  
 * Provided solely for recruitment evaluation.  
 * See LICENSE.txt for full terms.
 */

#ifndef OFDMCONFIG_HPP
#define OFDMCONFIG_HPP
#endif

/*
 * Basic Defines
 */
#define M_INDEX_MAX (unsigned short)4
#define SYMBOLS_PER_SLOT_IN_5G_NR 14
#define BASELINE_SUBCARRIER_SPACE_IN_kHz (double)15.0 // for LTE/NR
#define NUM_OF_SUBFRAMES_PER_10MS_FRAME (unsigned short)10
#define NUM_OF_SLOTS_PER_1_MS_SUBFRAME (unsigned short)pow(2.0, m_index) 
#define CYCLIC_PREFIX_FACTOR (double)0.25 //for simplicity reasons, let's keep it at 25% of Symnbol time. TODO: substitute it with the real one


#include <iostream>
class OFDM {
    private:
        //Private Members
        unsigned short symbolsPerSlot;
        double bandwidthMHz, subcarrierSpacing_kHz, slotDuration_ms;
        unsigned short m_index, slotsPerSubframe, slotsPerFrame, numOfSlotsPer1msSubframe;
        unsigned int symbolDuration_us, cyclicPrefixDuration_us;

        //Helper functions
        void set_subcarrier_spacing_in_kHz();
        void set_num_of_slots_per_frame_and_subframe();
        void set_slot_duration_in_ms();
        void set_symbol_duration_in_us();
        void set_cyclic_prefix_duration_in_us();
        
    public:
        //constructor
        OFDM(void);

        //functions
        void get_carrier_bandwidth_MHz_from_user(void);
        void get_m_index_from_user(void);
        void compute_params(void);
        void print_params();
        
};