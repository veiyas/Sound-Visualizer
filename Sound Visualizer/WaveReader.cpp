#include "WaveReader.hpp"

WaveReader::WaveReader(const char* _path)
{
		SndfileHandle reader = SndfileHandle(_path);
		
		frames.resize(reader.frames());

		reader.read(&frames[0], reader.frames());

		fs = reader.samplerate();
}