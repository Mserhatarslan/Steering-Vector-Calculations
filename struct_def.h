#ifndef STRUCT_DEF
#define STRUCT_DEF

/**
 * @struct AzimuthCalculations
 * @brief Represents the azimuth calculations for a radar system.
 */

typedef struct AzimuthCalculations {
    int numberOfSteerVectorAzimuthDirection;
    int AzimuthFov;
    double AzimuthStepSize;
    double AzimuthVectorInitialize;
    double AzimuthVectorStep;
    double AzimuthVectorValues[SIZE];
} AzimuthCalc;

/**
 * @struct ElevationCalculations
 * @brief Represents the elevation calculations for a radar system.
 */

typedef struct ElevationCalculations {
    int numberOfSteerVectorElevationDirection;
    int ElevationFov;
    double ElevationStepSize;
    double ElevationVectorInitialize;
    double ElevationVectorStep;
    double ElevationVectorValues[SIZE];
} ElevationCalc;

#endif
