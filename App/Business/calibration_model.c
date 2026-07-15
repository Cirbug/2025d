#include "calibration_model.h"
#include "linear_fit.h"
#include <stddef.h>

uint8_t CalibrationModel_FitDouble(DoubleCalibrationData *calibration)
{
  if ((calibration == NULL) || (calibration->point_count < 2U))
  {
    return 0U;
  }

  if (LinearFit_Calculate(calibration->length_m,
                          calibration->resistance_ohm,
                          calibration->point_count,
                          &calibration->resistance_per_meter,
                          &calibration->zero_resistance) == 0U)
  {
    return 0U;
  }

  return (calibration->resistance_per_meter > 0.000001f) ? 1U : 0U;
}

uint8_t CalibrationModel_FitSingle(SingleCalibrationData *calibration)
{
  float inverse_frequency[CALIBRATION_MAX_POINTS];

  if ((calibration == NULL) || (calibration->point_count < 2U))
  {
    return 0U;
  }

  for (uint32_t i = 0U; i < calibration->point_count; ++i)
  {
    if (calibration->frequency_hz[i] == 0U)
    {
      return 0U;
    }
    inverse_frequency[i] = 1000000.0f / (float)calibration->frequency_hz[i];
  }

  if (LinearFit_Calculate(inverse_frequency,
                          calibration->length_m,
                          calibration->point_count,
                          &calibration->inverse_period_slope,
                          &calibration->offset_m) == 0U)
  {
    return 0U;
  }

  return (calibration->inverse_period_slope > 0.000001f) ? 1U : 0U;
}

uint8_t CalibrationModel_GetDoubleLength(const DoubleCalibrationData *calibration,
                                         const DoubleFieldCalibrationData *field_calibration,
                                         float resistance_ohm,
                                         float *length_m)
{
  float resistance_per_meter;
  float zero_resistance;

  if ((calibration == NULL) || (length_m == NULL))
  {
    return 0U;
  }

  if ((field_calibration != NULL) && (field_calibration->valid != 0U))
  {
    resistance_per_meter = field_calibration->resistance_per_meter;
    zero_resistance = field_calibration->zero_resistance;
  }
  else
  {
    resistance_per_meter = calibration->resistance_per_meter;
    zero_resistance = calibration->zero_resistance;
  }

  if (resistance_per_meter <= 0.000001f)
  {
    return 0U;
  }

  *length_m = (resistance_ohm - zero_resistance) / resistance_per_meter;

  if (*length_m < 0.0f)
  {
    *length_m = 0.0f;
  }
  else if (*length_m > 1000.0f)
  {
    *length_m = 1000.0f;
  }

  return 1U;
}

void CalibrationModel_ResetField(DoubleFieldCalibrationData *field_calibration)
{
  if (field_calibration != NULL)
  {
    *field_calibration = (DoubleFieldCalibrationData){0};
  }
}

void CalibrationModel_SetFieldZero(DoubleFieldCalibrationData *field_calibration,
                                   float zero_resistance)
{
  if (field_calibration == NULL)
  {
    return;
  }

  field_calibration->pending_zero_resistance = zero_resistance;
  field_calibration->pending_zero_valid = 1U;
}

uint8_t CalibrationModel_ApplyFieldReference(const DoubleCalibrationData *base_calibration,
                                             DoubleFieldCalibrationData *field_calibration,
                                             float reference_resistance,
                                             float reference_length)
{
  float resistance_per_meter;
  float zero_resistance;

  if ((base_calibration == NULL) || (field_calibration == NULL) ||
      (reference_length <= 0.0f))
  {
    return 0U;
  }

  if (field_calibration->pending_zero_valid != 0U)
  {
    zero_resistance = field_calibration->pending_zero_resistance;
    resistance_per_meter = (reference_resistance - zero_resistance) / reference_length;
  }
  else
  {
    resistance_per_meter = base_calibration->resistance_per_meter;
    zero_resistance = reference_resistance - resistance_per_meter * reference_length;
  }

  if (resistance_per_meter <= 0.000001f)
  {
    return 0U;
  }

  field_calibration->valid = 1U;
  field_calibration->resistance_per_meter = resistance_per_meter;
  field_calibration->zero_resistance = zero_resistance;
  field_calibration->pending_zero_valid = 0U;
  field_calibration->pending_zero_resistance = 0.0f;
  field_calibration->reference_resistance = reference_resistance;
  field_calibration->reference_length = reference_length;
  return 1U;
}

uint8_t CalibrationModel_GetSingleLength(const SingleCalibrationData *calibration,
                                         uint32_t frequency_hz,
                                         float *length_m)
{
  if ((calibration == NULL) || (length_m == NULL) || (frequency_hz == 0U) ||
      (calibration->point_count < 2U) ||
      (calibration->inverse_period_slope <= 0.000001f))
  {
    return 0U;
  }

  *length_m = calibration->inverse_period_slope * (1000000.0f / (float)frequency_hz) +
              calibration->offset_m;

  if (*length_m < 0.0f)
  {
    *length_m = 0.0f;
  }
  else if (*length_m > 1000.0f)
  {
    *length_m = 1000.0f;
  }

  return 1U;
}
