// TimeSource.hh --- The Time
//
// Copyright (C) 2012 Rob Caelers <robc@krandor.nl>
// All rights reserved.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef WORKRAVE_UTILS_TIMESOURCE_HH
#define WORKRAVE_UTILS_TIMESOURCE_HH

#include "ITimeSource.hh"

namespace workrave
{
  namespace utils
  {
    //! A source of time.
    class TimeSource
    {
    public:
      static const gint64 USEC_PER_SEC = G_USEC_PER_SEC;
      
      //! Returns the system wall-clock time.
      static gint64 get_real_time_usec();

      //! Returns the system monotonic time, if available.
      static gint64 get_monotonic_time_usec();

      //! Returns the system wall-clock time in seconds.
      static gint64 get_real_time_sec();

      //! Returns the system monotonic time in seconds, if available.
      static gint64 get_monotonic_time_sec();

      //! Returns the system wall-clock time synchronized with core in seconds.
      static gint64 get_real_time_sync();

      //! Returns the system monotonic time synchronized with core in seconds, if available.
      static gint64 get_monotonic_time_sync();

      //! Synchronize current time.
      static void sync();
      
    public:
      static ITimeSource::Ptr source;
      static gint64 synced_real_time;
      static gint64 synced_monotonic_time;
    };
  }
}

#endif // WORKRAVE_UTILS_TIMESOURCE_HH