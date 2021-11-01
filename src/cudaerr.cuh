/* --------------------------------- Header --------------------------------- */


/**
 * @file    cudaerr.cuh
 * @brief   Contains CUDA error-handling functions
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef CUDAERR_CUH
# define CUDAERR_CUH


/* --------------------------------- Macros --------------------------------- */


/**
 * Handles a CUDA error
 */
# define HANDLE_CUDA_ERROR( err ) ( HandleCUDAError( err, __FILE__, __LINE__ ) )


/* -------------------------------- Functions ------------------------------- */

/**
 * Handles a CUDA error
 *
 * @param err   The CUDA error code
 * @param file  The file the error occurred in
 * @param line  The line the error occurred on
 */
void HandleCUDAError( cudaError_t err, const char *file, int line );


/* --------------------------------- Footer --------------------------------- */


# endif // CUDAERR_CUH


/* -------------------------------------------------------------------------- */