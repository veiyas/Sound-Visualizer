#include "WaveReader.hpp"

WaveReader::WaveReader(const char* _path)
{
		//Open file
		SndfileHandle reader = SndfileHandle(_path);
		sf_count_t wav_size = reader.frames();
		
		//Read data into vector frames and samplerate into fs
		frames.resize(wav_size);
		reader.read(&frames[0], reader.frames());
		fs = reader.samplerate();

		freq_data.resize(ceil(wav_size / BUFFER));
		//FFT with buffer size 1000 samples
		for (long long int i = 0; i < wav_size; i++)
		{
			//Because the next loop keeps accessing OOB for some reason, TODO lmao
			bool end_of_frames = false;

			//Läs in värden i temporär array
			double *temp = new double[BUFFER]{ 0.0 };

			for (long long int j = i*BUFFER; j < (i + 1) * BUFFER; j++)
			{
				if ((i + 1) * BUFFER >= frames.size())
				{
					end_of_frames = true;
					break;
				}
				double multiplier = 0.5 * (1 - cos(2 * 3.141 * (j % BUFFER) / (BUFFER - 1)));

				temp[j % BUFFER] = multiplier * frames[j];
			}
			if (end_of_frames)
				break;
			
			fftw_complex* out = fftw_alloc_complex(BUFFER);

			fftw_plan fft_plan = fftw_plan_dft_r2c_1d(BUFFER, temp, out, FFTW_ESTIMATE);

			fftw_execute(fft_plan);

			freq_data[i] = out;

			delete[] temp;
			fftw_destroy_plan(fft_plan);
			fftw_cleanup();
		}
}