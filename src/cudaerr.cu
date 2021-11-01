/* --------------------------------- Header --------------------------------- */


/**
 * @file    cudaerr.cu
 * @brief   Contains CUDA error-handling functions
 */


/* -------------------------------- Includes -------------------------------- */


# include <iostream>

# include "cudaerr.cuh"


/* -------------------------------- Namespace ------------------------------- */


using namespace std;


/* -------------------------------- Functions ------------------------------- */


/**
 * Handles a CUDA error
 *
 * @param err   The CUDA error code
 * @param file  The file the error occurred in
 * @param line  The line the error occurred on
 */
void HandleCUDAError( cudaError_t err, const char *file, int line )
{
    if ( err != cudaSuccess )
    {
        cout << "CUDA ERROR: " << cudaGetErrorString( err );
        cout << " in " << file << " at line " << line << endl;
        exit(1);
    }
}


/* -------------------------------------------------------------------------- */