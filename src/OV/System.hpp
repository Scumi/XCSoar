// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright The XCSoar Project

#pragma once

#include "DisplayOrientation.hpp"

#include <map>
#include <string>

class Path;

enum class SSHStatus {
  ENABLED,
  DISABLED,
  TEMPORARY,
};

enum class VARIODStatus {
  ENABLED,
  DISABLED,
};

enum class SENSORDStatus {
  ENABLED,
  DISABLED,
};

/**
 * Load a system config file and put its variables into a map
*/
void
LoadConfigFile(std::map<std::string, std::string, std::less<>> &map, Path path);
/**
 * Save a map of config variables to a system config file
*/
void
WriteConfigFile(std::map<std::string, std::string, std::less<>> &map, Path path);

uint_least8_t
OpenvarioGetBrightness() noexcept;

void
OpenvarioSetBrightness(uint_least8_t value) noexcept;

DisplayOrientation
OpenvarioGetRotation();

void
OpenvarioSetRotation(DisplayOrientation orientation);

void
OpenvarioSetLanguage(const char* lang);

[[gnu::pure]]
SSHStatus
OpenvarioGetSSHStatus();

bool
OpenvarioEnableSSH(bool temporary);

bool
OpenvarioDisableSSH();

VARIODStatus
OpenvarioGetVARIODStatus();

bool
OpenvarioEnableVARIOD();

bool
OpenvarioDisableVARIOD();

SENSORDStatus
OpenvarioGetSENSORDStatus();

bool
OpenvarioEnableSENSORD();

bool
OpenvarioDisableSENSORD();