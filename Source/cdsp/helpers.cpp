#include "helpers.hpp"

cdsp::types::disc_32_u cdsp::helpers::two_to_n(types::disc_32_u n) {
	if (n == 0) {
		return 1;
	}

	return 1 << n;
};

cdsp::types::boolean cdsp::helpers::is_power_of_two(types::disc_32_u n) {
	n;
	return true;
};

void cdsp::helpers::sine_sum(std::set<std::tuple<types::cont_64, types::cont_64, types::cont_64> > partials, types::disc_32_u buffer_length, types::sample* buffer) {
	if (buffer_length == 0) {
		throw exceptions::runtime("cdsp::helpers::sine_sum: buffer_length is 0");
	}

	// clear
	for (types::disc_32_u i = 0; i < buffer_length; i++) {
		buffer[i] = values::sample_silence;
	}

	// fill
	for (auto it : partials) {
		std::tuple<types::cont_64, types::cont_64, types::cont_64>& partial = it;
		types::cont_64 harmonic_freq = std::get<0>(partial);
		types::cont_64 harmonic_amp = std::get<1>(partial);
		types::cont_64 harmonic_phase = std::get<2>(partial);
		types::cont_64 index_value = values::two_pi_64 * harmonic_phase;
		types::cont_64 index_increment = (values::two_pi_64 / static_cast<types::cont_64>(buffer_length)) * harmonic_freq;
		for (types::disc_32_u i = 0; i < buffer_length; i++) {
			buffer[i] += static_cast<types::sample>(harmonic_amp * sin(index_value));
			index_value += index_increment;
		}
	}

	// normalize
	types::sample max = values::sample_infinity_n;
	for (types::disc_32_u i = 0; i < buffer_length; i++) {
		if (buffer[i] > max) {
			max = buffer[i];
		}
	}
	if (max > values::sample_infinity_n) {
		types::sample max_inverse = values::sample_line_level / max;
		for (types::disc_32_u i = 0; i < buffer_length; i++) {
			buffer[i] *= max_inverse;
		}
	}
}

cdsp::types::cont_32 cdsp::helpers::inverse_memoized(types::cont_64 x) {
	auto it = inverse_memoize.find(x);
	types::cont_32 result;
	if (it == inverse_memoize.end()) {
		result = static_cast<types::cont_32>(1.0 / x);
		inverse_memoize.insert(std::make_pair(x, result));
	}
	else {
		result = it->second;
	}
	return result;
}

template <typename T>
void write(std::ofstream& stream, const T& t) {
	stream.write((const char*)&t, sizeof(T));
}

void cdsp::helpers::io::wav_file_save(std::string file_path, types::cont_64 sample_rate, types::disc_32_u sample_bit_depth, sample_buffer& buffer) {
	// TODO: use sample bit depth
	sample_bit_depth;

	// adapt my signature
	size_t bufSize = buffer.buffer_size_get();
	short channels = static_cast<short>(buffer.channels_num_get());
	int sampleRate = static_cast<int>(sample_rate);
	typedef types::sample SampleType;
	const types::sample* buf = buffer.channel_pointer_read(0);

	// open
    std::ofstream stream(file_path.c_str(), std::ios::binary);      // Open file stream at "outFile" location

	// http://stackoverflow.com/questions/22226872/two-problems-when-writing-to-wav-c
    /* Header */
    stream.write("RIFF", 4);                                        // sGroupID (RIFF = Resource Interchange File Format)
    write<int>(stream, 36 + bufSize);                               // dwFileLength
    stream.write("WAVE", 4);                                        // sRiffType

    /* Format Chunk */
    stream.write("fmt ", 4);                                        // sGroupID (fmt = format)
    write<int>(stream, 16);                                         // Chunk size (of Format Chunk)
    write<short>(stream, 3);                                        // Format (1 = PCM, 3 = Float)
    write<short>(stream, channels);                                 // Channels
    write<int>(stream, sampleRate);                                 // Sample Rate
    write<int>(stream, sampleRate * channels * sizeof(SampleType)); // Byterate
    write<short>(stream, channels * sizeof(SampleType));            // Frame size aka Block align
    write<short>(stream, 8 * sizeof(SampleType));                   // Bits per sample

    /* Data Chunk */
    stream.write("data", 4);                                        // sGroupID (data)
    stream.write((const char*)&bufSize, 4);                         // Chunk size (of Data, and thus of bufferSize)
    stream.write((const char*)buf, bufSize);                        // The samples DATA!!!

	// close
	stream.close();

	/*
	// create wav file header
	wav_file_header header;
#ifdef CDSP_WIN32
	strncpy_s(header.m_lpcChunkId, 4, "RIFF", _TRUNCATE);
#else
	strncpy(header.m_lpcChunkId, "RIFF", 4);
#endif
	header.m_iChunkSize = static_cast<int>(sizeof(header) + (buffer.buffer_size_get()) - 8);
#ifdef CDSP_WIN32
	strncpy_s(header.m_lpcFormat, 4, "WAVE", _TRUNCATE);
#else
	strncpy(header.m_lpcFormat, "WAVE", 4);
#endif
#ifdef CDSP_WIN32
	strncpy_s(header.m_lpcSubChunkFmt, 4, "fmt", _TRUNCATE);
#else
	strncpy(header.m_lpcSubChunkFmt, "fmt", 4);
#endif
	header.m_iSubChunkFmtSize = 16;
	header.m_siAudioFormat = 1;
	header.m_siNumChannels = static_cast<short int>(buffer.channels_num_get());
	header.m_iSampleRate = static_cast<int>(sample_rate);
	header.m_iByteRate = (sample_rate * sample_bit_depth * buffer.channels_num_get()) / 8;
	header.m_siBlockAlign = 4;
	header.m_siBitsPerSample = static_cast<short int>(sample_bit_depth);
#ifdef CDSP_WIN32
	strncpy_s(header.m_lpcChunkData, 4, "data", _TRUNCATE);
#else
	strncpy(header.m_lpcChunkData, "data", 4);
#endif
	header.m_iSubChunkDataSize = buffer.buffer_length_get();

	FILE* fid = fopen(file_path.c_str(), "wb");
	fwrite(&header, sizeof(char), sizeof(wav_file_header), fid);
	fwrite(buffer.channel_pointer_read(0), sizeof(char), buffer.buffer_size_get(), fid);
	fclose(fid);
	*/
}