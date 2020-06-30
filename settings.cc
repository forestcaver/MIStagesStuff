// Copyright 2017 Olivier Gillet.
//
// Author: Olivier Gillet (ol.gillet@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// 
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------
//
// Settings storage.

#include "stages/settings.h"

#include <algorithm>

#include "stmlib/system/storage.h"

namespace stages {

using namespace std;

#define FIX_OUTLIER(destination, expected_value) if (fabsf(destination / expected_value - 1.0f) > 0.1f) { destination = expected_value; }
#define FIX_OUTLIER_ABSOLUTE(destination, expected_value) if (fabsf(destination - expected_value) > 0.1f) { destination = expected_value; }


bool Settings::Init() {
  ChannelCalibrationData default_calibration_data;

  default_calibration_data.dac_offset = 32768.0f;
  default_calibration_data.dac_scale = -32263.0f;
  default_calibration_data.adc_offset = 0.0f;
  default_calibration_data.adc_scale = -1.0f;
 
  fill(
      &persistent_data_.channel_calibration_data[0],
      &persistent_data_.channel_calibration_data[kNumChannels],
      default_calibration_data);
  
  fill(
      &state_.segment_configuration[0],
      &state_.segment_configuration[kNumChannels],
      0);

#if 0
  // AJH
  persistent_data_.channel_calibration_data[0].dac_offset = 32768.0f;
  persistent_data_.channel_calibration_data[0].dac_scale = -32263.0f;
  persistent_data_.channel_calibration_data[1].dac_offset = 32768.0f;
  persistent_data_.channel_calibration_data[1].dac_scale = -32263.0f;
  persistent_data_.channel_calibration_data[2].dac_offset = 32768.0f;
  persistent_data_.channel_calibration_data[2].dac_scale = -32263.0f;
  persistent_data_.channel_calibration_data[3].dac_offset = 32768.0f;
  persistent_data_.channel_calibration_data[3].dac_scale = -32263.0f;
  persistent_data_.channel_calibration_data[4].dac_offset = 32768.0f;
  persistent_data_.channel_calibration_data[4].dac_scale = -32263.0f;
  persistent_data_.channel_calibration_data[5].dac_offset = 32768.0f;
  persistent_data_.channel_calibration_data[5].dac_scale = -32263.0f;

  persistent_data_.channel_calibration_data[0].adc_offset = 0.0f /* FIXME */;
  persistent_data_.channel_calibration_data[0].adc_scale = -1.0f /* FIXME */;
  persistent_data_.channel_calibration_data[1].adc_offset = 0.0f /* FIXME */;
  persistent_data_.channel_calibration_data[1].adc_scale = -1.0f /* FIXME */;
  persistent_data_.channel_calibration_data[2].adc_offset = 0.0f /* FIXME */;
  persistent_data_.channel_calibration_data[2].adc_scale = -1.0f /* FIXME */;
  persistent_data_.channel_calibration_data[3].adc_offset = 0.0f /* FIXME */;
  persistent_data_.channel_calibration_data[3].adc_scale = -1.0f /* FIXME */;
  persistent_data_.channel_calibration_data[4].adc_offset = 0.0f /* FIXME */;
  persistent_data_.channel_calibration_data[4].adc_scale = -1.0f /* FIXME */;
  persistent_data_.channel_calibration_data[5].adc_offset = 0.0f /* FIXME */;
  persistent_data_.channel_calibration_data[5].adc_scale = -1.0f /* FIXME */;
#endif

#if 0
// Module 1
  persistent_data_.channel_calibration_data[0].dac_offset = 32737.99804688f;
  persistent_data_.channel_calibration_data[0].dac_scale = -32265.08398438f;
  persistent_data_.channel_calibration_data[1].dac_offset = 32810.53906250f;
  persistent_data_.channel_calibration_data[1].dac_scale = -32258.11914062f;
  persistent_data_.channel_calibration_data[2].dac_offset = 32857.98437500f;
  persistent_data_.channel_calibration_data[2].dac_scale = -32323.60937500f;
  persistent_data_.channel_calibration_data[3].dac_offset = 32778.89843750f;
  persistent_data_.channel_calibration_data[3].dac_scale = -32234.63476562f;
  persistent_data_.channel_calibration_data[4].dac_offset = 32868.21093750f;
  persistent_data_.channel_calibration_data[4].dac_scale = -32279.07226562f;
  persistent_data_.channel_calibration_data[5].dac_offset = 32774.89453125f;
  persistent_data_.channel_calibration_data[5].dac_scale = -32311.40039062f;

  persistent_data_.channel_calibration_data[0].adc_offset = 0.04925025f;
  persistent_data_.channel_calibration_data[0].adc_scale = -0.99435210f;
  persistent_data_.channel_calibration_data[1].adc_offset = 0.05052660f;
  persistent_data_.channel_calibration_data[1].adc_scale = -0.99235559f;
  persistent_data_.channel_calibration_data[2].adc_offset = 0.04993458f;
  persistent_data_.channel_calibration_data[2].adc_scale = -0.99380523f;
  persistent_data_.channel_calibration_data[3].adc_offset = 0.04993078f;
  persistent_data_.channel_calibration_data[3].adc_scale = -0.98984754f;
  persistent_data_.channel_calibration_data[4].adc_offset = 0.05473220f;
  persistent_data_.channel_calibration_data[4].adc_scale = -0.98638785f;
  persistent_data_.channel_calibration_data[5].adc_offset = 0.05093442f;
  persistent_data_.channel_calibration_data[5].adc_scale = -0.98273659f;
  //
#endif

#if 0
// Module 2
  persistent_data_.channel_calibration_data[0].dac_offset = 32904.73046875f;
  persistent_data_.channel_calibration_data[0].dac_scale = -32346.59960938f;
  persistent_data_.channel_calibration_data[1].dac_offset = 32877.87109375f;
  persistent_data_.channel_calibration_data[1].dac_scale = -32407.25976562f;
  persistent_data_.channel_calibration_data[2].dac_offset = 32948.27734375f;
  persistent_data_.channel_calibration_data[2].dac_scale = -32408.03710938f;
  persistent_data_.channel_calibration_data[3].dac_offset = 32880.08984375f;
  persistent_data_.channel_calibration_data[3].dac_scale = -32209.84375000f;
  persistent_data_.channel_calibration_data[4].dac_offset = 33005.67968750f;
  persistent_data_.channel_calibration_data[4].dac_scale = -32368.42187500f;
  persistent_data_.channel_calibration_data[5].dac_offset = 32973.85546875f;
  persistent_data_.channel_calibration_data[5].dac_scale = -32306.72851562f;

  persistent_data_.channel_calibration_data[0].adc_offset = 0.04680140f;
  persistent_data_.channel_calibration_data[0].adc_scale = -0.99366045f;
  persistent_data_.channel_calibration_data[1].adc_offset = 0.05012065f;
  persistent_data_.channel_calibration_data[1].adc_scale = -0.99307823f;
  persistent_data_.channel_calibration_data[2].adc_offset = 0.05360132f;
  persistent_data_.channel_calibration_data[2].adc_scale = -1.00471890f;
  persistent_data_.channel_calibration_data[3].adc_offset = 0.05125576f;
  persistent_data_.channel_calibration_data[3].adc_scale = -0.99710512f;
  persistent_data_.channel_calibration_data[4].adc_offset = 0.05162805f;
  persistent_data_.channel_calibration_data[4].adc_scale = -0.99055344f;
  persistent_data_.channel_calibration_data[5].adc_offset = 0.04897073f;
  persistent_data_.channel_calibration_data[5].adc_scale = -0.99525601f;
#endif
  

  state_.color_blind = 0;
  
  bool success = chunk_storage_.Init(&persistent_data_, &state_);
  
  // Sanitize settings read from flash.
  if (success) {
    for (size_t i = 0; i < kNumChannels; ++i) {
      ChannelCalibrationData* c = &persistent_data_.channel_calibration_data[i];
      FIX_OUTLIER_ABSOLUTE(c->adc_offset, 0.0f);
      
      FIX_OUTLIER(c->dac_offset, 32768.0f);
      FIX_OUTLIER(c->dac_scale, -32263.0f);
      FIX_OUTLIER(c->adc_scale, -1.0f);

      uint8_t type_bits = state_.segment_configuration[i] & 0x3;
      uint8_t loop_bit = state_.segment_configuration[i] & 0x4;
      CONSTRAIN(type_bits, 0, 3);
      state_.segment_configuration[i] = type_bits | loop_bit;
    }
  }

  return success;
}

void Settings::SavePersistentData() {
  chunk_storage_.SavePersistentData();
}

void Settings::SaveState() {
  chunk_storage_.SaveState();
}

}  // namespace stages
