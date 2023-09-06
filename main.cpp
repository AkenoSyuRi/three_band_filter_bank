#include "three_band_filter_bank.h"
#include "audio_utils.h"

int main() {
    const int frame_length_48k = 48 * 16;
    const int frame_length_16k = 16 * 16;
    std::string_view in_pcm_path = R"(../data/input/VOICEACTRESS100_054.pcm)";
    std::string_view out_pcm_paths[]{
            R"(../data/output/VOICEACTRESS100_054_low_band.pcm)",
            R"(../data/output/VOICEACTRESS100_054_mid_band.pcm)",
            R"(../data/output/VOICEACTRESS100_054_high_band.pcm)",
            R"(../data/output/VOICEACTRESS100_054_syn_out.pcm)",
    };

    PCMReader reader(in_pcm_path.data());
    auto n_samples = reader.sample_size_in_16bit();
    auto n_frames = n_samples / frame_length_48k;
    PCMWriter writers[]{
            PCMWriter{out_pcm_paths[0].data()},
            PCMWriter{out_pcm_paths[1].data()},
            PCMWriter{out_pcm_paths[2].data()},
            PCMWriter{out_pcm_paths[3].data()},
    };

    auto frame_48k_bytes_size = frame_length_48k * sizeof(short);
    auto frame_16k_bytes_size = frame_length_16k * sizeof(short);
    std::array<short, frame_length_48k> in_48k_arr_short{};
    std::array<float, frame_length_48k> in_48k_arr_float{};
    std::array<short, frame_length_16k> split_bands_short[3]{{}};
    std::array<float, frame_length_16k> split_bands_float[3]{{}};
    std::array<short, frame_length_48k> out_48k_arr_short{};
    std::array<float, frame_length_48k> out_48k_arr_float{};

    webrtc::ThreeBandFilterBank filterBank;
    rtc::ArrayView<float, frame_length_48k> in_48k_arr_view(in_48k_arr_float);
    rtc::ArrayView<float> split_bands_view[3]{
            {split_bands_float[0]},
            {split_bands_float[1]},
            {split_bands_float[2]},
    };
    rtc::ArrayView<rtc::ArrayView<float>, 3> out_bands_arr_view(split_bands_view);
    rtc::ArrayView<float, frame_length_48k> out_48k_arr_view(out_48k_arr_float);

    for (int i = 0; i < n_frames; ++i) {
        reader.read_bytes(in_48k_arr_short.data(), frame_48k_bytes_size);
        std::copy(in_48k_arr_short.begin(), in_48k_arr_short.end(), in_48k_arr_float.begin());

        filterBank.Analysis(in_48k_arr_view, out_bands_arr_view);

        for (int j = 0; j < 3; ++j) {
            std::copy(split_bands_float[j].begin(), split_bands_float[j].end(), split_bands_short[j].begin());
            writers[j].write_bytes(split_bands_short[j].begin(), frame_16k_bytes_size);
        }

        filterBank.Synthesis(split_bands_view, out_48k_arr_view);
        std::copy(out_48k_arr_float.begin(), out_48k_arr_float.end(), out_48k_arr_short.begin());
        writers[3].write_bytes(out_48k_arr_short.begin(), frame_48k_bytes_size);
        printf("frame_idx=%d\n", i);
    }
    return 0;
}
