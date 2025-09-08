/*
 * Copyright (c) 2025 Christos Axelos
 *
 * This code is provided solely for evaluating my skills as part of
 * the recruitment process. Unauthorized use or distribution is prohibited.
 */

/*
 * - Write a small C++ program that, given a carrier bandwidth (in MHz) 
 * and a numerology index μ (0–4), computes and prints key OFDM numerology 
 * parameters for normal Cyclic Prefix.
 *
 */
#include <iostream>
#include <cmath>
#include <iomanip>
#include "OFDM.hpp"
using namespace std;

int main() {
       
    OFDM OfdmConfig;

    OfdmConfig.get_carrier_bandwidth_MHz_from_user();
    OfdmConfig.get_m_index_from_user();
    OfdmConfig.compute_params();
    OfdmConfig.print_params();

    return 0;
}