// Copyright (C) 2021 Christian Brommer, Control of Networked Systems, University of Klagenfurt, Austria.
//
// All rights reserved.
//
// This software is licensed under the terms of the BSD-2-Clause-License with
// no commercial use allowed, the full terms of which are made available
// in the LICENSE file. No license in patents is granted.
//
// You can contact the author at <christian.brommer@ieee.org>

#include <mars/time.h>
#include <mars/type_definitions/buffer_entry_type.h>
#include <iostream>
#include <utility>

namespace mars
{
BufferEntryType::BufferEntryType(const Time& timestamp, BufferDataType data, std::shared_ptr<SensorAbsClass> sensor,
                                 const int& metadata)
  : timestamp_(timestamp), data_(std::move(data)), sensor_(move(sensor)), metadata_(metadata)
{
  metadata_state_filter_ = std::set<int>(
      { BufferMetadataType::core_state, BufferMetadataType::sensor_state, BufferMetadataType::init_state });

  metadata_measurement_filter_ =
      std::set<int>({ BufferMetadataType::measurement, BufferMetadataType::measurement_ooo });
}

bool BufferEntryType::operator<(const BufferEntryType& rhs) const
{
  return timestamp_ < rhs.timestamp_;
}

bool BufferEntryType::operator<=(const BufferEntryType& rhs) const
{
  return timestamp_ <= rhs.timestamp_;
}

bool BufferEntryType::operator>(const BufferEntryType& rhs) const
{
  return timestamp_ > rhs.timestamp_;
}

bool BufferEntryType::operator>=(const BufferEntryType& rhs) const
{
  return timestamp_ >= rhs.timestamp_;
}

std::ostream& operator<<(std::ostream& out, const BufferEntryType& entry)
{
  out << entry.sensor_->name_ << '\t';
  out << entry.timestamp_ << '\t';
  out << entry.metadata_ << '\t';

  return out;
}

bool BufferEntryType::IsState() const
{
  return (metadata_state_filter_.find(metadata_) != metadata_state_filter_.end());
}

bool BufferEntryType::IsMeasurement() const
{
  return (metadata_measurement_filter_.find(metadata_) != metadata_measurement_filter_.end());
}
}  // namespace mars
