#include "fft_manager.hpp"


FftManager::FftManager(uint32_t input_buffer_size_,uint32_t sample_late_ , uint32_t m_fft_buffer_size_) :
		m_input_buffer_size(input_buffer_size_),
		m_sample_late(sample_late_),
		m_fft_buffer_size(m_fft_buffer_size_)
{
	m_audio_buffer = new float[m_fft_buffer_size_]{};
	std::memset(m_audio_buffer,0,sizeof(float) * m_fft_buffer_size_);
}

void FftManager::pushBackBuffer(float *buffer_)
{
	std::memmove(m_audio_buffer, m_audio_buffer+m_input_buffer_size,(m_fft_buffer_size-m_input_buffer_size)*sizeof(float));
	std::memcpy(m_audio_buffer+m_fft_buffer_size-m_input_buffer_size,buffer_,m_input_buffer_size*sizeof(float));
}

void FftManager::getFrequency()
{
	fftwf_complex *out;
	fftwf_plan plan;
	float maxAmplitude = 0.0;
	uint32_t maxIndex = 0;

	out = (fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex) * m_fft_buffer_size);
	plan = fftwf_plan_dft_r2c_1d(static_cast<uint32_t>(m_fft_buffer_size), m_audio_buffer, out, FFTW_ESTIMATE);
	fftwf_execute(plan);

	for (uint32_t i = 0; i < m_fft_buffer_size / 2; i++)
	{
		float amplitude = std::sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
		if (amplitude > maxAmplitude)
		{
			maxAmplitude = amplitude;
			maxIndex = i;
		}
	}

	float maxFrequency = (float)maxIndex * (float)m_sample_late / (float)m_fft_buffer_size;

	printf("Max Frequency: %.2f Hz\n", maxFrequency);

	fftwf_destroy_plan(plan);
	fftwf_free(out);
}
