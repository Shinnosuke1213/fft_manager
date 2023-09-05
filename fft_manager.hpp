#pragma once

#include <cstring>
#include <cmath>
#include <cstdint>
#include <iostream>
#include "include/fftw3.h"

class FftManager
{
public:
	FftManager(uint32_t input_buffer_size_,uint32_t sample_late_ ,uint32_t m_fft_buffer_size_);

	void pushBackBuffer(float *buffer_);

	void getFrequency();

private:
private:
	uint32_t m_input_buffer_size;
	uint32_t m_sample_late;
	uint32_t m_fft_buffer_size;
	float *m_audio_buffer;
};
