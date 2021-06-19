// SmartSpin2K code
// This software registers an ESP32 as a BLE FTMS device which then uses a stepper motor to turn the resistance knob on a regular spin bike.
// BLE code based on examples from https://github.com/nkolban
// Copyright 2020 Anthony Doud & Joel Baranick
// This work is licensed under the GNU General Public License v2
// Prototype hardware build from plans in the SmartSpin2k repository are licensed under Cern Open Hardware Licence version 2 Permissive

#pragma once

#include <Arduino.h>
#include "SensorData.h"

class FitnessMachineIndoorBikeData : public SensorData
{
public:
    FitnessMachineIndoorBikeData() : SensorData("FTMS"){};

    bool hasHeartRate();
    bool hasCadence();
    bool hasPower();
    bool hasSpeed();
    int getHeartRate();
    float getCadence();
    int getPower();
    float getSpeed();
    void decode(uint8_t *data, size_t length);

    enum Types : uint8_t
    {
        InstantaneousSpeed = 0,
        AverageSpeed = 1,
        InstantaneousCadence = 2,
        AverageCadence = 3,
        TotalDistance = 4,
        ResistanceLevel = 5,
        InstantaneousPower = 6,
        AveragePower = 7,
        TotalEnergy = 8,
        EnergyPerHour = 9,
        EnergyPerMinute = 10,
        HeartRate = 11,
        MetabolicEquivalent = 12,
        ElapsedTime = 13,
        RemainingTime = 14
    };

    static constexpr uint8_t FieldCount = Types::RemainingTime + 1;

private:
    double_t values[FieldCount];

    // See: https://github.com/oesmith/gatt-xml/blob/master/org.bluetooth.characteristic.indoor_bike_data.xml
    static uint8_t const flagBitIndices[];
    static uint8_t const flagEnabledValues[];
    static size_t const byteSizes[];
    static uint8_t const signedFlags[];
    static double_t const resolutions[];

    static int convert(int value, size_t length, uint8_t isSigned);
};