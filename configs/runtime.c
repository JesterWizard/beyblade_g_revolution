#include "runtime.h"

const RuntimeConfig gRuntimeConfigRom __attribute__((section(".runtime_config"))) = {
    .placeholder = FALSE,
    .uncapBitBeastExp = FALSE,
    .setRPMTo = 10000,
    .fullBitBeastGauge = FALSE,
    .keepBitBeastExp = TRUE,
    .fixHighExpRpm = TRUE,
    .keepBeybladeOnLoss = TRUE,
    .infiniteRipcordHealth = TRUE,
    .infiniteLauncherHealth = TRUE,
    .overworldSpeed = 2,
};
