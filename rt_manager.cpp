#include "rt_manager.hpp"

FftManager * RtManager::m_fft_manager;

RtManager::RtManager(uint32_t sample_late_, uint32_t buffer_size_) :
		m_sample_late(sample_late_),
		m_buffer_size(buffer_size_),
		m_rt_audio(new RtAudio(RtAudio::WINDOWS_ASIO))
{
	m_fft_manager = new FftManager(buffer_size_,sample_late_,2048);
}

std::vector<std::string> RtManager::getDeviceList()
{
	std::vector<std::string> device_lists = {};

	for(const auto id :m_rt_audio->getDeviceIds() ){
		RtAudio::DeviceInfo info = m_rt_audio->getDeviceInfo(id);
		device_lists.push_back(std::to_string(info.ID)+info.name);
	}

	return device_lists;
}

void RtManager::openStream(uint32_t device_id_)
{
	RtAudio::StreamParameters parameters;
	parameters.deviceId = device_id_;
	parameters.nChannels = 1;
	try
	{
		m_rt_audio->openStream(nullptr, &parameters, RTAUDIO_FLOAT32, m_sample_late, &m_buffer_size, rtCallback);
	}
	catch (RtAudioErrorType &e)
	{
		std::cerr << "Error: " << e << std::endl;
	}
}

void RtManager::startStream()
{
	m_rt_audio->startStream();
}

void RtManager::stopStream()
{
	m_rt_audio->stopStream();
}

RtManager::~RtManager()
{
	if (m_rt_audio->isStreamOpen())
		m_rt_audio->closeStream();
	delete(m_rt_audio);
}

int RtManager::rtCallback(void *outputBuffer, void *inputBuffer, uint32_t nBufferFrames, double streamTime,
                           RtAudioStreamStatus status, void *userData)
{
	m_fft_manager->pushBackBuffer((float *)inputBuffer);
	m_fft_manager->getFrequency();

	return 0;
}