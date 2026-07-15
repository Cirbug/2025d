#ifndef CALIBRATION_MODEL_H
#define CALIBRATION_MODEL_H

#include <stdint.h>

#define CALIBRATION_MAX_POINTS 10U

typedef struct
{
  uint32_t point_count;
  float length_m[CALIBRATION_MAX_POINTS];
  float resistance_ohm[CALIBRATION_MAX_POINTS];
  float resistance_per_meter;
  float zero_resistance;
} DoubleCalibrationData;

typedef struct
{
  uint32_t point_count;
  float length_m[CALIBRATION_MAX_POINTS];
  uint32_t frequency_hz[CALIBRATION_MAX_POINTS];
  float inverse_period_slope;
  float offset_m;
} SingleCalibrationData;

typedef struct
{
  uint32_t valid;
  float resistance_per_meter;
  float zero_resistance;
  uint32_t pending_zero_valid;
  float pending_zero_resistance;
  float reference_resistance;
  float reference_length;
} DoubleFieldCalibrationData;

uint8_t CalibrationModel_FitDouble(DoubleCalibrationData *calibration);
uint8_t CalibrationModel_FitSingle(SingleCalibrationData *calibration);
uint8_t CalibrationModel_GetDoubleLength(const DoubleCalibrationData *calibration,
                                         const DoubleFieldCalibrationData *field_calibration,
                                         float resistance_ohm,
                                         float *length_m);
uint8_t CalibrationModel_GetSingleLength(const SingleCalibrationData *calibration,
                                         uint32_t frequency_hz,
                                         float *length_m);
void CalibrationModel_ResetField(DoubleFieldCalibrationData *field_calibration);
void CalibrationModel_SetFieldZero(DoubleFieldCalibrationData *field_calibration,
                                   float zero_resistance);
uint8_t CalibrationModel_ApplyFieldReference(const DoubleCalibrationData *base_calibration,
                                             DoubleFieldCalibrationData *field_calibration,
                                             float reference_resistance,
                                             float reference_length);

#endif /* CALIBRATION_MODEL_H */
