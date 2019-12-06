#include "FFT.h"

FFT::FFT() {

}

void FFT::compute() {
    /*arm_cfft_radix4_instance_f32 fft_inst;
    arm_cfft_radix4_init_f32(&fft_inst, FFT_SIZE, 0, 1);
    arm_cfft_radix4_f32(&fft_inst, input);
    arm_cmplx_mag_f32(input, output, FFT_SIZE);*/

    arm_cfft_radix4_instance_q15 forwardFFT;
    arm_cfft_radix4_init_q15(&forwardFFT, FFT_SIZE, 0, 1);
    arm_cfft_radix4_q15(&forwardFFT, input);
    arm_cmplx_mag_q15(input, output, FFT_SIZE);
}