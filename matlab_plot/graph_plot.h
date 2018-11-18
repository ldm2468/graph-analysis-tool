//
// MATLAB Compiler: 6.6 (R2018a)
// Date: Sun Nov 18 14:53:12 2018
// Arguments: "-B""macro_default""-W""cpplib:graph_plot""graph_plot.m"
//

#ifndef __graph_plot_h
#define __graph_plot_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" {
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_graph_plot_C_API 
#define LIB_graph_plot_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_graph_plot_C_API 
bool MW_CALL_CONV graph_plotInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_graph_plot_C_API 
bool MW_CALL_CONV graph_plotInitialize(void);

extern LIB_graph_plot_C_API 
void MW_CALL_CONV graph_plotTerminate(void);

extern LIB_graph_plot_C_API 
void MW_CALL_CONV graph_plotPrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_graph_plot_C_API 
bool MW_CALL_CONV mlxGraph_plot(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_graph_plot
#define PUBLIC_graph_plot_CPP_API __declspec(dllexport)
#else
#define PUBLIC_graph_plot_CPP_API __declspec(dllimport)
#endif

#define LIB_graph_plot_CPP_API PUBLIC_graph_plot_CPP_API

#else

#if !defined(LIB_graph_plot_CPP_API)
#if defined(LIB_graph_plot_C_API)
#define LIB_graph_plot_CPP_API LIB_graph_plot_C_API
#else
#define LIB_graph_plot_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_graph_plot_CPP_API void MW_CALL_CONV graph_plot();

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
