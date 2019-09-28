#pragma once

#include <libsndfile/sndfile.hh>
#include <libsndfile/sndfile.h>

#include <vector>
#include <iostream>

class WaveReader
{
public:
	WaveReader(const char * _path);

	std::vector<double> frames;

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