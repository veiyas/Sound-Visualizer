#include "WaveReader.hpp"

WaveReader::WaveReader(const char* _path)
{
		SndfileHandle reader = SndfileHandle(_path);
		
		frames.resize(reader.frames());

		reader.read(&frames[0], reader.frames());

		fs = reader.samplerate();

		for (size_t i = 0; i < INTERVAL; i++)
		{
			//Läs in värden i temporär array

			//Gör fft plan osv osv osv och lagra i freq_data
		}
}