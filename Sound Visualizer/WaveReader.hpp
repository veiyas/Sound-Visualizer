#pragma once

#include <libsndfile/sndfile.hh>
#include <libsndfile/sndfile.h>
#include <FFTW/fftw3.h>

#include <vector>
#include <iostream>

const unsigned INTERVAL = 1000;

class WaveReader
{
public:
	WaveReader(const char * _path);

	std::vector<double> frames;
	std::vector<double> freq_data;

	unsigned fs = 0;
};

//Read test
/*const char* inFileName;
SNDFILE* inFile;
SF_INFO inFileInfo;
int fs;

inFileName = "soundfiles/susann_vega.wav";

inFile = sf_open(inFileName, SFM_READ, &inFileInfo);
sf_close(inFile);

fs = inFileInfo.samplerate;*/