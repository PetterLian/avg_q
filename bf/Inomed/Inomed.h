#define MAX_NUMBER_OF_CHANNELS 32

typedef struct                      //Struktur Filterparameter
{
        char    szName[30];         //Filterbezeichnung
        float   fCutoffFrequency;   //Cutoff-Frequenz in Hz
        char    szReserve[64];      //Reserve-Bytes für spätere Änderungen
}DIG_FILTER;

// diese structur wird als structur der gespeicherten Messwerte
// benutzt. Änderungen können zu kompatibilitätsprobleme führen !
typedef struct
//Struktur zur Beschreibung eines Kanals
{
        short   sADInputChannelNumber,                  //Kanalnummer 0..31
                        sFlags, //Sichtbar Flag  CHAN_VISIBLE CHAN_MEASURE CHAN_NOTCHFILTER, CHAN_BLANKING... 
                        sHeadboxTransferChannel[2], //1 Headboxkanal positives Signal, 2 Headboxkanal negatives Signal, wenn beide gleich, dann differentiell
                        sSound; //Soundflag
        int             iColor, //Farbe
                        iGainHardware, //Verstärkung Hardware
                        iOffsetHardware; //Offset Hardware
        float   fGainSoftware, //Verstärkung Software
                        fOffsetSoftware; //Offset Software
        char    szChannelSite[30],                              //Messort
                        szElectrodePair[2][30]; //Messelektrodenbezeichnungen
        float   fHardwareHighpassFrequency;             //Filterfrequenz 
        short   Device;			// 16bit device 0 = 1. isis 2 = 2.isis
        char    AmplTrgMode;            // kanal-trigger
        char    Reseve2;
        float   fAmplThreshold;         // emg select. saved
        float   fTriggerAmplThreshold;  // emg. trgg.ampl
        float   blankingTime;           // blanking-Zeit in ms
        double  scaling;                // Skalierung für den Kanal, wenn der Kanal eine eigene Skalierung hat
        char    szReserve[228]; //Reserve-Bytes für spätere Änderungen

        DIG_FILTER      strctHighPass,
                                strctLowPass;
}CHANNEL;

// Header-Structur from NeuroExplorer
// Size in Bytes = 19668
typedef struct 							//Signaleigenschaften
{
	char	 	szVersion[20],				// 00..19
			szDate[11],				// 20..30
			szTime[9];				// 31..39  bei Kaskaden Zeiteintrag	
	short   	sSignaltype,				// 40..41  EMG//EEG
			sNumberOfChannels;			// 42..43
	char 		szComment[30];				// 44..73 --> Allignment 74/75
	float		fSamplingFrequency;			// 76..79 
	unsigned long 	ulNumberOfSamples;			// 80..83
	int     	Flag;					// 84..87
	int		BkgndColor;				// 88..91
	int		GridColor;				// 92..95
	char 		szReserve[1024 - 12];			// To size 1024+84=1108
	CHANNEL 	strctChannel[MAX_NUMBER_OF_CHANNELS];	// = 32 Channels, 580 Bytes per channel
} MULTI_CHANNEL_CONTINUOUS;

// MER
// Header-Structur from NeuroExplorer
// Matlab code skips 604 bytes; 2*40+11*4+3*40+4+354=602
// Data are 16-bit shorts; read unsigned, subtract 2048 and multiply by (0.4/4096)
typedef struct
{
   char PatName [40];   // Patientenkürzel
   char Position [40];  // Position (für EMG nicht relevant)
   int SamplingRate;
   int SpikeCount;      // für EMG nicht relevant
   int TriggerLinie;    // für EMG nicht relevant
   int SiteNr;          // für EMG nicht relevant
   int KanalNr;         // Nummer des Messkanals
   int op_id;           // ID der Operation
   int SiteID;          // ID der Site
   int MaxYValue;       // Maximale Auflösung (Amplitude) der Y - Achse
                        // (ISIS MER: 4095)
   int typ;             // Typ der Datei 
                        //(0 = Normale Messdatendatei, 255 =EMG - Datei)

   int Multiplexing;    // Zur Zeit nicht benutzt
   int EMGChannels;     // Zugeordnete EMG - Kanäle
   char EMGChannelsDesc [3][40];  // Bezeichner der EMG - Kanäle
   int BitsPerValue;    // Compression, wenn Wert <> 12 keine Kompression
   char filler [354];   // Reserve für zukünftige Nutzung
} PlotWinInfo;

#include <read_struct.h>
extern struct_member sm_MULTI_CHANNEL_CONTINUOUS[], sm_CHANNEL[], sm_DIG_FILTER[];
extern struct_member_description smd_MULTI_CHANNEL_CONTINUOUS[], smd_CHANNEL[], smd_DIG_FILTER[];

extern struct_member sm_PlotWinInfo[];
extern struct_member_description smd_PlotWinInfo[];
