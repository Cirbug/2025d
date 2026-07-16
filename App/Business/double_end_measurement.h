#ifndef DOUBLE_END_MEASUREMENT_H
#define DOUBLE_END_MEASUREMENT_H

#include <stdint.h>
#include "cable_test_manager.h"
#include "calibration_model.h"

typedef struct
{
  uint8_t valid;
  int32_t difference;
  float voltage_mv;
  float resistance_ohm;
  uint8_t length_valid;
  float length_m;
  uint16_t adc3_input;
  uint16_t adc3_output;
  uint8_t attenuation_valid;
  float attenuation_db;
  CableTestResult cable;
} DoubleEndMeasurementResult;

void DoubleEndMeasurement_Calculate(int32_t difference,
                                    const CableTestResult *cable,
                                    const DoubleCalibrationData *calibration,
                                    const DoubleFieldCalibrationData *field_calibration,
                                    uint16_t adc3_input,
                                    uint16_t adc3_output,
                                    DoubleEndMeasurementResult *result);

#endif /* DOUBLE_END_MEASUREMENT_H */
