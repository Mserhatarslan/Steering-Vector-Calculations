#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define NDEBUG  //(No Debug) assert(expression) ((void)0);
#include <assert.h>
#include "lookUpTable.h"
#include "struct_def.h"

#define SIZE 360
#define M_PI 3.14159265358979323846
#define AZIMUTH_FOV 70
#define ELEVATION_FOV 20
#define AZIMUTH_STEP_SIZE 0.75
#define ELEVATION_STEP_SIZE 0.75

/**
 * Prints the values of the azimuth vector.
 *
 * @param a_print: A pointer to the AzimuthCalc structure.
 */

void printArrayAzimuthVector(const AzimuthCalc *a_print)
{
    for (int i = 0; i < a_print->numberOfSteerVectorAzimuthDirection; ++i) {
        printf("AzimuthVectorValues[%d] = %f\n ", i, a_print->AzimuthVectorValues[i]);
    }
}

/**
 * Prints the values of the elevation vector.
 *
 * @param e_print: A pointer to the ElevationCalc structure.
 */

void printArrayElevationVector(const ElevationCalc *e_print)
{
    for (int i = 0; i < e_print->numberOfSteerVectorElevationDirection; ++i) {
        printf("ElevationVectorValues[%d] = %f\n ", i, e_print->ElevationVectorValues[i]);
    }
}

/**
 * Performs mathematical operations to calculate the values of the AzimuthVectorValues array.
 *
 * @param a: A pointer to the AzimuthCalc struct.
 * @param AzimuthFov: The azimuth field of view.
 * @param AzimuthStepSize: The step size for the azimuth vector.
 * @param cosTable: A pointer to the cosine lookup table.
 * @param az_pd: A pointer to the file to write the azimuth values to.
 */

void AzimuthMathOperations(AzimuthCalc *a, int AzimuthFov, double AzimuthStepSize, FILE *az_pd) {

    assert(AzimuthFov != 0 && AzimuthStepSize != 0);
    
    a->numberOfSteerVectorAzimuthDirection = (2 * AzimuthFov) / AzimuthStepSize;
    a->AzimuthVectorInitialize = -sinTable[AzimuthFov];
    a->AzimuthVectorStep = - (2 * a->AzimuthVectorInitialize) / a->numberOfSteerVectorAzimuthDirection;

    int i = 0; 

    for (i = 0; i < a->numberOfSteerVectorAzimuthDirection; ++i) {

        a->AzimuthVectorValues[i] = a->AzimuthVectorInitialize + i * a->AzimuthVectorStep;
         fprintf(az_pd, "AzimuthVectorValues[%d] = %f\n", i, a->AzimuthVectorValues[i]);
    }

    if (fprintf(az_pd, "%f\n", a->AzimuthVectorValues[i - 1]) < 0) {
        fprintf(stderr, "Error writing to azimuthVal.txt\n");
        fclose(az_pd); 
    }
}

/**
 * Performs mathematical operations to calculate the values of the ElevationVectorValues array.
 *
 * @param e: A pointer to the ElevationCalc struct.
 * @param ElevationFov: The elevation field of view.
 * @param ElevationStepSize: The step size for the elevation vector.
 * @param sinTable: A pointer to the sine lookup table.
 * @param el_pd: A pointer to the file to write the elevation values to.
 */

void ElevationMathOperations(ElevationCalc *e, int ElevationFov, double ElevationStepSize, const float* sinTable, FILE *el_pd) {

    assert(ElevationFov != 0 && ElevationStepSize != 0);

    e->numberOfSteerVectorElevationDirection = (2 * ElevationFov) / ElevationStepSize; // 53
    e->ElevationVectorInitialize = -sinTable[ElevationFov];   // 0.01
    e->ElevationVectorStep = -((2 * e->ElevationVectorInitialize) / e->numberOfSteerVectorElevationDirection); //- 0.34

    int i = 0; 

    for (i = 0; i < e->numberOfSteerVectorElevationDirection; ++i) {

        e->ElevationVectorValues[i] = e->ElevationVectorInitialize + i * e->ElevationVectorStep;
        fprintf(el_pd, " ElevationVectorValues[%d] = %f\n", i, e->ElevationVectorValues[i]);
    }

    if (fprintf(el_pd, "%f\n", e->ElevationVectorValues[i - 1]) < 0) {
        fprintf(stderr, "Error writing to elevationVal.txt\n");
        //fclose(el_pd); 
    }
}

/**
 * The main function of the program.
 *
 * @return: An integer representing the exit status of the program.
 */
int main(void) {

    FILE *az_pd;
    Fıle *el_pd;
    FILE *out_calculations;

    az_pd = fopen("azimuthVal.txt", "w");  // Opening the azimuthVal.txt file in write mode.
    if (az_pd == NULL) {
        fprintf(stderr, "Error opening azimuthVal.txt\n");
        exit(EXIT_FAILURE); 
    }

    el_pd = fopen("elevationVal.txt","w"); // Opening the elevationVal.txt file in write mode.
    if (el_pd == NULL) {
        fprintf(stderr, "Error opening elevationVal.txt\n");
        exit(EXIT_FAILURE); 
    }

    out_calculations = fopen("out_calculations.txt","w"); // Opening the elevationVal.txt file in write mode.
    if (el_pd == NULL) {
        fprintf(stderr, "Error opening out_calculations.txt\n");
        exit(EXIT_FAILURE); 
    }
    
    // Perform azimuth math operations.
    AzimuthCalc azimuthCalc = {0};
    AzimuthMathOperations(&azimuthCalc, AZIMUTH_FOV, AZIMUTH_STEP_SIZE, az_pd);
    fprintf(out_calculations, "Azimuth: %d\n", azimuthCalc.numberOfSteerVectorAzimuthDirection);
    fprintf(out_calculations, "AzimuthVectorInitialize: %f\n", azimuthCalc.AzimuthVectorInitialize);
    fprintf(out_calculations, "AzimuthVectorStep %f\n", azimuthCalc.AzimuthVectorStep);

    // Perform elevation math operations.
    ElevationCalc elevationCalc = {0};
    ElevationMathOperations(&elevationCalc, ELEVATION_FOV, ELEVATION_STEP_SIZE, sinTable, el_pd);
    fprintf(out_calculations, "Elevation: %d\n", elevationCalc.numberOfSteerVectorElevationDirection);
    fprintf(out_calculations, "ElevationVectorInitialize: %f\n", elevationCalc.ElevationVectorInitialize);
    fprintf(out_calculations, "ElevationVectorStep %f\n", elevationCalc.ElevationVectorStep);

    printArrayAzimuthVector(&azimuthCalc);
    printf("\n");
    printArrayElevationVector(&elevationCalc);

    if (fclose(az_pd) != 0) {
             fprintf(stderr, "Error closing azimuthVal.txt\n");}

    if (fclose(el_pd) != 0) {
             fprintf(stderr, "Error closing elevationVal.txt\n");}

    if (fclose(out_calculations) != 0) {
             fprintf(stderr, "Error closing out_calculations.txt\n");}

    exit(EXIT_SUCCESS);
}
