#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <cmath>

#include "include/RtAudio.h"

#include "fft_manager.hpp"

class RtManager
{
public:
	RtManager(uint32_t sample_late_, uint32_t buffer_size_);
	std::vector<std::string> getDeviceList();
	void openStream(uint32_t device_id_);
	void startStream();
	void stopStream();
	~RtManager();
private:
	static int rtCallback(void *outputBuffer, void *inputBuffer, uint32_t nBufferFrames,
	                double streamTime, RtAudioStreamStatus status, void *userData);
private:
	const uint32_t m_sample_late;
	uint32_t m_buffer_size;

	RtAudio *m_rt_audio;
	static FftManager *m_fft_manager;
};
