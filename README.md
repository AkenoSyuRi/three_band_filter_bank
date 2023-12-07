# three_band_filter_bank

- extracted from the source code of webrtc
- split the target 48k signal into three bands time domain data, which frequencies are ranging in 0~8kHz, 8~16kHz, 16~
  24kHz respectively, as well as synthesizing the three band data back to the original 48k signal (not perfect
  reconstruction)