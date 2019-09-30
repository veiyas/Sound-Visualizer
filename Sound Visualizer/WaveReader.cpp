#include "WaveReader.hpp"

WaveReader::WaveReader(const char* _path)
{
		SndfileHandle reader = SndfileHandle(_path);
		
		frames.resize(reader.frames());

		reader.read(&frames[0], reader.frames());

		fs = reader.samplerate();

		for (size_t i = 0; i < INTERVAL; i++)
		{
			//L�s in v�rden i tempor�r array

			//G�r fft plan osv osv osv och lagra i freq_data
		}
}