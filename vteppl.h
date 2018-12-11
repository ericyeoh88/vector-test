
//  DON'T ALTER THIS FILE                                  
                                  
                                  
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the VTEPPL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// VTEPPL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef VTEPPL_EXPORTS
#define VTEPPL_API __declspec(dllexport)
#else
#define VTEPPL_API __declspec(dllimport)
#endif


/* Define bit positions for each data line (port A on the PMD-1208LS) */
#define PWRSUP		0
#define DATAIN		1
#define CLKA		2
#define CLKB		3
#define PROBECTL	4


/* Where the ADC channels are connected */
#define ADC_CHANNEL_PWRSUP  0
#define ADC_CHANNEL_VERIFY  1
#define ADC_CHANNEL_SIGHILO 2


/* Mux card addresses can be 1 through 15 */
#define MUXADDRESSMIN    1
#define MUXADDRESSMAX   15
#define MUXADDRESSARRAYSIZE (MUXADDRESSMAX+1)  /* array sized so 1 thru 15 are valid indexes, 0 is not used */


/* Probe addresses can be 1 through 64 */
#define PROBEADDRESSMIN  1
#define PROBEADDRESSMAX 64
#define PROBEADDRESSARRAYSIZE (PROBEADDRESSMAX+1)  /* array sized so 1 thru 64 are valid indexes, 0 is not used */


#define MAXVTEPMUXCARDS 6   /* Max number of VTEP mux cards allowed */

typedef enum VTEPPL_API vplMuxPowerEnum {
    POWEROFF,
    POWERON
} VplMuxPowerEnum;



typedef enum VTEPPL_API vplMuxTypeEnum {
    MUXNONE,
    MUXVTEP,
    MUXTESTJET
} VplMuxTypeEnum;

typedef enum VTEPPL_API vplProbeTypeEnum {
    PROBEVTEP,
    PROBEVTEPSMALL,
    PROBETESTJET,
    PROBEMISSING,
    PROBEUNKNOWN,
    PROBEBACKWARDS,
    PROBEPRESENT
} VplProbeTypeEnum;

typedef enum VTEPPL_API vplSensorPlateEnum {
    SENSORNONE,
    SENSOROK,
    SENSORBACKWARDS
} VplSensorPlateEnum;

typedef struct VTEPPL_API vplProbeInfo {
    VplProbeTypeEnum type;
    VplSensorPlateEnum sensor;
} VplProbeInfo;



typedef struct VTEPPL_API vplMuxProbeInfo {
    VplMuxTypeEnum muxType;
    VplProbeInfo probeInfo[PROBEADDRESSARRAYSIZE];
} VplMuxProbeInfo;



/**
 * Initialize the VTEP pl for use. This must be called once
 * before calling any of the other functions contained in this
 * library.
 * 
 * @param boardnum Board number parameter used by the PMD-1208LS
 *                 library routines.
 */
VTEPPL_API void vplInit(int boardnum);


/**
 * This function MUST be called anytime the power to the mux
 * card is turned off.
 *
 * @see VTEPMUXPOWERENUM
 */
VTEPPL_API void vplMuxInformPower(VplMuxPowerEnum onoff);


VTEPPL_API void vplDetermineMuxTypes(VplMuxProbeInfo mpi[]);

VTEPPL_API void vplDetermineProbeTypes(VplMuxProbeInfo mpi[], VplMuxTypeEnum hardwaretype);

VTEPPL_API void vplDetermineProbeLocaVTEP(int mux, int probe, char* probeResult);

VTEPPL_API void vplDetermineProbeLocaVTEPSMALL(int mux, int probe, char* probeResult);

VTEPPL_API void vplDetermineProbeLocaTESTJET(int mux, int probe, char* probeResult);

VTEPPL_API void headerDisclaimer();

VTEPPL_API int ReverifyMux(int mux);

VTEPPL_API void setTimeout();

VTEPPL_API double AutoStartMeas(double Delta, int mux, int probe, char* probeResult, double UpperLimit);

VTEPPL_API double ManualStartMeas(double Delta, int mux, int probe, char* probeResult, double UpperLimit);

VTEPPL_API double AutoStartMeasTJ(double Delta, int mux, int probe, char* probeResult, double LowerLimit);

VTEPPL_API double ManualStartMeasTJ(double Delta, int mux, int probe, char* probeResult, double LowerLimit);