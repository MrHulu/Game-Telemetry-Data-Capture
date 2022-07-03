#pragma once

struct Dirt2TelemetryData
{
    float   TotalTime;
    float	LapTime;
    float	LapDistance;
    float	TotalDistance;
    float	Position_X;
    float	Position_Y;
    float	Position_Z;
    float	Speed_MS;
    float	Velocity_X;
    float	Velocity_Y;
    float	Velocity_Z;
    float	Left_Dir_X;
    float	Left_Dir_Y;
    float	Left_Dir_Z;
    float	Forward_Dir_X;
    float	Forward_Dir_Y;
    float	Forward_Dir_Z;
    float	Susp_pos_bl;
    float	Susp_pos_br;
    float	Susp_pos_fl;
    float	Susp_pos_fr;
    float	Susp_vel_bl;
    float	Susp_vel_br;
    float	Susp_vel_fl;
    float	Susp_vel_fr;
    float	Wheel_speed_bl;
    float	Wheel_speed_br;
    float	Wheel_speed_fl;
    float	Wheel_speed_fr;
    float	Throttle;
    float	Steer;
    float	Brake;
    float	Clutch;
    float	Gear;       // -1 0 1 2 3...
    float	Gforce_lat;
    float	Gforce_lon;
    float	Lap;
    float	EngineRate;             // rmp / 10
    float	Sli_pro_native_support;
    float	Car_position;
    float	Kers_level;
    float	Kers_max_level;
    float	Drs;
    float	Traction_control;
    float	ABS;                    // ?
    float	Fuel_in_tank;           // no
    float	Fuel_capacity;          // no
    float	In_pits;
    float	Sector;
    float	Sector1_time;
    float	Sector2_time;
    float	Brakes_temp_bl;
    float   Brakes_temp_br;
    float   Brakes_temp_fl;
    float   Brakes_temp_fr;
    float	Wheels_pressure_bl;     // no
    float	Wheels_pressure_br;     // no
    float	Wheels_pressure_fl;     // no
    float	Wheels_pressure_fr;     // no
    float	laps_completed;         //??
    float	Total_laps;
    float	Track_size;
    float	Last_lap_time;
    float	Max_rpm;                // max rpm / 10
    float	Idle_rpm;
    float	Max_gears;
    float	SessionType;
    float	DrsAllowed;
    float	Track_number;
    float	VehicleFIAFlags;
};
