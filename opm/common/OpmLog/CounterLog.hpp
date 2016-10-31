/*
  Copyright 2014 Andreas Lauser

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 *  A simple system for log message which are found by the
 *  Parser/Deck/EclipseState classes during processing the deck.
 */

#ifndef OPM_COUNTERLOG_HPP
#define OPM_COUNTERLOG_HPP

#include <string>
#include <memory>
#include <map>
#include "opm/common/OpmLog/LogBackend.hpp"

namespace Opm {
/**
 * @brief Provides a simple system for log message which are found by the
 *        Parser/Deck/EclipseState classes during processing the deck.
 */
class CounterLog : public LogBackend {
 public:
  /**
   * @brief Construct a counter log.
   */
  CounterLog();

  /**
   * @brief Construct a counter log given a messaqge mask
   * @param  messageMask the message mask
   * @note Message mask is one of the following:
   *       - Debug     =  1   Excessive information
   *       - Note      =  2;  Information that should only go into print file
   *       - Info      =  4;  Normal status information
   *       - Warning   =  8;  Input anomaly - possible error
   *       - Error     = 16;   Error in the input data - should probably exit
   *       - Problem   = 32;   Calculation problems - e.g. convergence failure
   *       - Bug       = 64;   An inconsistent state has been encountered in
   *                           the simulator - should probably exit
   */
  explicit CounterLog(int64_t messageMask);

  /**
   * @brief gewt the number of messages that are of given message type
   * @param  messageType type message type
   * @note Message type is one of the following:
   *       - Debug     =  1   Excessive information
   *       - Note      =  2;  Information that should only go into print file
   *       - Info      =  4;  Normal status information
   *       - Warning   =  8;  Input anomaly - possible error
   *       - Error     = 16;   Error in the input data - should probably exit
   *       - Problem   = 32;   Calculation problems - e.g. convergence failure
   *       - Bug       = 64;   An inconsistent state has been encountered in
   *                           the simulator - should probably exit
   */
  size_t numMessages(int64_t messageType) const;

  /**
   * @brief Clear the message counter.
   */
  void clear();

 protected:
  /**
   * @brief Add a message to the log.
   * @param messageFlag the message flag
   * @param message the message
   * @note Message flag is one of the following:
   *       - Debug     =  1   Excessive information
   *       - Note      =  2;  Information that should only go into print file
   *       - Info      =  4;  Normal status information
   *       - Warning   =  8;  Input anomaly - possible error
   *       - Error     = 16;   Error in the input data - should probably exit
   *       - Problem   = 32;   Calculation problems - e.g. convergence failure
   *       - Bug       = 64;   An inconsistent state has been encountered in
   *                           the simulator - should probably exit
   */
  void addMessageUnconditionally(int64_t messageFlag,
                                const std::string& message) override;

 private:
    std::map<int64_t , size_t> m_count;  //!< count messages acc. to their flags
};
}  // namespace Opm
#endif
