/*
Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000-2012 The XCSoar Project
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/

#include "Declaration.hpp"
#include "Logger/Settings.hpp"
#include "Plane/Plane.hpp"
#include "Engine/Task/Tasks/BaseTask/ObservationZonePoint.hpp"
#include "Engine/Task/ObservationZones/CylinderZone.hpp"
#include "Task/Tasks/OrderedTask.hpp"
#include "Task/Tasks/BaseTask/OrderedTaskPoint.hpp"

gcc_pure
static Declaration::TurnPoint::Shape
get_shape(const OrderedTaskPoint &tp)
{
  const ObservationZonePoint *oz = tp.GetOZPoint();
  if (oz == NULL)
    return Declaration::TurnPoint::SECTOR;

  switch (oz->shape) {
  case ObservationZonePoint::LINE:
    return Declaration::TurnPoint::LINE;

  case ObservationZonePoint::CYLINDER:
    return Declaration::TurnPoint::CYLINDER;

  default:
    return Declaration::TurnPoint::SECTOR;
  }
}

gcc_pure
static unsigned
get_radius(const OrderedTaskPoint &tp)
{
  const ObservationZonePoint *oz = tp.GetOZPoint();
  if (oz == NULL)
    return Declaration::TurnPoint::SECTOR;

  return (unsigned)((const CylinderZone *)oz)->getRadius();
}

Declaration::TurnPoint::TurnPoint(const OrderedTaskPoint &tp)
  :waypoint(tp.GetWaypoint()),
   shape(get_shape(tp)), radius(get_radius(tp))
{
}

Declaration::Declaration(const LoggerSettings &logger_settings,
                         const Plane &plane,
                         const OrderedTask* task)
  :pilot_name(logger_settings.pilot_name),
   aircraft_type(plane.type),
   aircraft_registration(plane.registration),
   competition_id(plane.competition_id)
{
  if (task)
    for (unsigned i = 0; i < task->TaskSize(); i++)
      turnpoints.push_back(task->GetTaskPoint(i));
}
