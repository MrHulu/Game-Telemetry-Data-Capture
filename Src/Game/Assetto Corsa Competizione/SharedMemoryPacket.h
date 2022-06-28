#pragma once



enum class PenaltyShortcut : int {
    None,
    DriveThrough_Cutting,
    StopAndGo_10_Cutting,
    StopAndGo_20_Cutting,
    StopAndGo_30_Cutting,
    Disqualified_Cutting,
    RemoveBestLaptime_Cutting,

    DriveThrough_PitSpeeding,
    StopAndGo_10_PitSpeeding,
    StopAndGo_20_PitSpeeding,
    StopAndGo_30_PitSpeeding,
    Disqualified_PitSpeeding,
    RemoveBestLaptime_PitSpeeding,

    Disqualified_IgnoredMandatoryPit,

    PostRaceTime,
    Disqualified_Trolling,
    Disqualified_PitEntry,
    Disqualified_PitExit,
    Disqualified_WrongWay,

    DriveThrough_IgnoredDriverStint,
    Disqualified_IgnoredDriverStint,

    Disqualified_ExceededDriverStintLimit,
};


typedef int AC_STATUS;

#define AC_OFF 0
#define AC_REPLAY 1
#define AC_LIVE 2
#define AC_PAUSE 3

typedef int AC_SESSION_TYPE;

#define AC_UNKNOWN -1
#define AC_PRACTICE 0
#define AC_QUALIFY 1
#define AC_RACE 2
#define AC_HOTLAP 3
#define AC_TIME_ATTACK 4
#define AC_DRIFT 5
#define AC_DRAG 6
#define AC_HOTSTINT 7
#define AC_HOTLAPSUPERPOLE 8

typedef int AC_FLAG_TYPE;

#define AC_NO_FLAG 0
#define AC_BLUE_FLAG 1
#define AC_YELLOW_FLAG 2
#define AC_BLACK_FLAG 3
#define AC_WHITE_FLAG 4
#define AC_CHECKERED_FLAG 5
#define AC_PENALTY_FLAG 6


#pragma pack(push)
#pragma pack(4)

namespace  ACC {

enum
{
  TYRE_FRONT_LEFT = 0,
  TYRE_FRONT_RIGHT,
  TYRE_REAR_LEFT,
  TYRE_REAR_RIGHT,
  //--------------
};

struct SPageFilePhysics
{

    int packetId = 0;
    float gas = 0;
    float brake = 0;
    float fuel = 0;
    int gear = 0;
    int rpms = 0;
    float steerAngle = 0;
    float speedKmh = 0;
    float velocity[3];
    float accG[3];
    float wheelSlip[4];
    float wheelLoad[4];
    float wheelsPressure[4];
    float wheelAngularSpeed[4];
    float tyreWear[4];
    float tyreDirtyLevel[4];
    float tyreCoreTemperature[4];
    float camberRAD[4];
    float suspensionTravel[4];
    float drs = 0;
    float tc = 0;
    float heading = 0;
    float pitch = 0;
    float roll = 0;
    float cgHeight;
    float carDamage[5];
    int numberOfTyresOut = 0;
    int pitLimiterOn = 0;
    float abs = 0;
    float kersCharge = 0;
    float kersInput = 0;
    int autoShifterOn = 0;
    float rideHeight[2];
    float turboBoost = 0;
    float ballast = 0;
    float airDensity = 0;
    float airTemp = 0;
    float roadTemp = 0;
    float localAngularVel[3];
    float finalFF = 0;
    float performanceMeter = 0;

    int engineBrake = 0;
    int ersRecoveryLevel = 0;
    int ersPowerLevel = 0;
    int ersHeatCharging = 0;
    int ersIsCharging = 0;
    float kersCurrentKJ = 0;

    int drsAvailable = 0;
    int drsEnabled = 0;

    float brakeTemp[4];
    float clutch = 0;

    float tyreTempI[4];
    float tyreTempM[4];
    float tyreTempO[4];

    int isAIControlled;

    float tyreContactPoint[4][3];
    float tyreContactNormal[4][3];
    float tyreContactHeading[4][3];

    float brakeBias = 0;

    float localVelocity[3];

    int P2PActivations = 0;
    int P2PStatus = 0;

    int currentMaxRpm = 0;

    float mz[4];
    float fx[4];
    float fy[4];
    float slipRatio[4];
    float slipAngle[4];


    int tcinAction = 0;
    int absInAction = 0;
    float suspensionDamage[4];
    float tyreTemp[4];

    float waterTemp;		 	//Water Temperature
    float brakePressure[4]; 	//Brake pressure [FL, FR, RL, RR] see Appendix 2
    int frontBrakeCompound; 	//Brake pad compund front
    int rearBrakeCompound; 		//Brake pad compund rear
    float padLife[4]; 			//Brake pad wear [FL, FR, RL, RR]
    float discLife[4]; 			//Brake disk wear [FL, FR, RL, RR]
    int ignitionOn; 			//Ignition switch set to on?
    int starterEngineOn;		//Starter Switch set to on?
    int isEngineRunning; 		//Engine running?
    float kerbVibration; 		//vibrations sent to the FFB, could be used for motion rigs
    float slipVibrations; 		//vibrations sent to the FFB, could be used for motion rigs
    float gVibrations;			//vibrations sent to the FFB, could be used for motion rigs
    float absVibrations; 		//vibrations sent to the FFB, could be used for motion rig

};


struct SPageFileGraphic
{
    int packetId = 0;
    AC_STATUS status = AC_OFF;
    AC_SESSION_TYPE session = AC_PRACTICE;
    wchar_t currentTime[15];
    wchar_t lastTime[15];
    wchar_t bestTime[15];
    wchar_t split[15];
    int completedLaps = 0;
    int position = 0;
    int iCurrentTime = 0;
    int iLastTime = 0;
    int iBestTime = 0;
    float sessionTimeLeft = 0;
    float distanceTraveled = 0;
    int isInPit = 0;
    int currentSectorIndex = 0;
    int lastSectorTime = 0;
    int numberOfLaps = 0;
    wchar_t tyreCompound[33];
    float replayTimeMultiplier = 0;
    float normalizedCarPosition = 0;

    int activeCars = 0;
    float carCoordinates[60][3];
    int carID[60];
    int playerCarID = 0;
    float penaltyTime = 0;
    AC_FLAG_TYPE flag = AC_NO_FLAG;
    PenaltyShortcut penalty = PenaltyShortcut::None;
    int idealLineOn = 0;
    int isInPitLane = 0;

    float surfaceGrip = 0;
    int mandatoryPitDone = 0;

    float windSpeed = 0;
    float windDirection = 0;


    int isSetupMenuVisible = 0;

    int mainDisplayIndex = 0;
    int secondaryDisplayIndex = 0;
    int TC = 0;
    int TCCut = 0;
    int EngineMap = 0;
    int ABS = 0;
    int fuelXLap = 0;
    int rainLights = 0;
    int flashingLights = 0;
    int lightsStage = 0;
    float exhaustTemperature = 0.0f;
    int wiperLV = 0;
    int DriverStintTotalTimeLeft = 0;
    int DriverStintTimeLeft = 0;
    int rainTyres = 0;

    int sessionIndex;
    float usedFuel; 				//Used fuel since last time refueling
    wchar_t deltaLapTime[15]; 		//Delta time in wide character
    int iDeltaLapTime; 				//Delta time time in milliseconds
    wchar_t estimatedLapTime [15]; 	//Estimated lap time in milliseconds
    int iEstimatedLapTime; 			//Estimated lap time in wide character
    int isDeltaPositive; 			//Delta positive (1) or negative (0)
    int iSplit; 					//Last split time in milliseconds
    int isValidLap; 				//Check if Lap is valid for timing
    float fuelEstimatedLaps; 		//Laps possible with current fuel level
    wchar_t trackStatus[33]; 		//Status (Green, Fast, Optimum, Damp, Wet)
    int missingMandatoryPits; 		//Mandatory pitstops the player still has to do
    float Clock; 					//Time of day in seconds
    int directionLightsLeft; 		//Is Blinker left on
    int directionLightsRight;	 	//Is Blinker right on
    int GlobalYellow; 				//Yellow Flag is out?
    int GlobalYellow1; 				//Yellow Flag in Sector 1 is out?
    int GlobalYellow2; 				//Yellow Flag in Sector 2 is out?
    int GlobalYellow3; 				//Yellow Flag in Sector 3 is out?
    int GlobalWhite; 				//White Flag is out?
    int GlobalGreen; 				//Green Flag is out?
    int GlobalChequered; 			//Checkered Flag is out?
    int GlobalRed; 					//Red Flag is out?
    int mfdTyreSet; 				//# of tyre set on the MFD
    float mfdFuelToAdd; 			//How much fuel to add on the MFD
    float mfdTyrePressureLF; 		//Tyre pressure left front on the MFD
    float mfdTyrePressureRF;		//Tyre pressure right front on the MFD
    float mfdTyrePressureLR; 		//Tyre pressure left rear on the MFD
    float mfdTyrePressureRR; 		//Tyre pressure right rear on the MFD

};


struct SPageFileStatic
{
    wchar_t smVersion[15];
    wchar_t acVersion[15];

    // session static info
    int numberOfSessions = 0;
    int numCars = 0;
    wchar_t carModel[33];
    wchar_t track[33];
    wchar_t playerName[33];
    wchar_t playerSurname[33];
    wchar_t playerNick[33];
    int sectorCount = 0;

    // car static info
    float maxTorque = 0;
    float maxPower = 0;
    int	maxRpm = 0;
    float maxFuel = 0;
    float suspensionMaxTravel[4];
    float tyreRadius[4];
    float maxTurboBoost = 0;

    float deprecated_1 = -273;
    float deprecated_2 = -273;

    int penaltiesEnabled = 0;

    float aidFuelRate = 0;
    float aidTireRate = 0;
    float aidMechanicalDamage = 0;
    int aidAllowTyreBlankets = 0;
    float aidStability = 0;
    int aidAutoClutch = 0;
    int aidAutoBlip = 0;

    int hasDRS = 0;
    int hasERS = 0;
    int hasKERS = 0;
    float kersMaxJ = 0;
    int engineBrakeSettingsCount = 0;
    int ersPowerControllerCount = 0;
    float trackSPlineLength = 0;
    wchar_t trackConfiguration[33];
    float ersMaxJ = 0;

    int isTimedRace = 0;
    int hasExtraLap = 0;

    wchar_t carSkin[33];
    int reversedGridPositions = 0;
    int PitWindowStart = 0;
    int PitWindowEnd = 0;
    int isOnline = 0;
};

}// ACC



#pragma pack(pop)
