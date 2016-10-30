/*
  Copyright 2016 Statoil ASA.

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
 *  The Eclipse PRT log class. 
 */

#ifndef ECLIPSEPRTLOG_H
#define ECLIPSEPRTLOG_H

#include <map>
#include <string>
#include "opm/common/OpmLog/StreamLog.hpp"

namespace Opm {
class EclipsePRTLog : public StreamLog {
 public:
  /**
   * @brief Construct a logger to the <MODEL>.PRT file
   * @param logFile the name of the logfile to use
   * @param messageMask an integer as described in Opm::Log::MessageType
   *                     namespace, in file LogUtils.hpp.
   * @param append if true then we append messages to the file;
   *               otherwise a new file is created
   * @param print_summary if true print a summary to the PRT file
   * @note The message type is defined as follows:
   *       - Debug     =  1   Excessive information
   *       - Note      =  2;  Information that should only go into print file
   *       - Info      =  4;  Normal status information
   *       - Warning   =  8;  Input anomaly - possible error
   *       - Error     = 16;   Error in the input data - should probably exit
   *       - Problem   = 32;   Calculation problems - e.g. convergence failure
   *       - Bug       = 64;   An inconsistent state has been encountered in
   *                           the simulator - should probably exit.
   */
  EclipsePRTLog(const std::string& logFile , int64_t messageMask,
                bool append, bool print_summary);

  /**
   * @brief Construct a logger to the <MODEL>.PRT file
   * @param os the output stream to be used
   * @param messageMask an integer as described in Opm::Log::MessageType
   *                     namespace, in file LogUtils.hpp.
   * @param print_summary if true print a summary to the PRT file
   * @note The message type is defined as follows:
   *       - Debug     =  1   Excessive information
   *       - Note      =  2;  Information that should only go into print file
   *       - Info      =  4;  Normal status information
   *       - Warning   =  8;  Input anomaly - possible error
   *       - Error     = 16;   Error in the input data - should probably exit
   *       - Problem   = 32;   Calculation problems - e.g. convergence failure
   *       - Bug       = 64;   An inconsistent state has been encountered in
   *                           the simulator - should probably exit.
   */
  EclipsePRTLog(std::ostream& os , int64_t messageMask,
                bool print_summary);

  /**
   * @brief Destructor
   */
  ~EclipsePRTLog();

  /**
   * @brief Get the messages that are characterized by a given message type.
   * @param messageType the message type
   * @note The message type is defined as follows:
   *       - Debug     =  1   Excessive information
   *       - Note      =  2;  Information that should only go into print file
   *       - Info      =  4;  Normal status information
   *       - Warning   =  8;  Input anomaly - possible error
   *       - Error     = 16;   Error in the input data - should probably exit
   *       - Problem   = 32;   Calculation problems - e.g. convergence failure
   *       - Bug       = 64;   An inconsistent state has been encountered in
   *                           the simulator - should probably exit.
   */
  size_t numMessages(int64_t messageType) const;

 protected:
  /**
   * @brief Add a message to the log.
   * @param messageType the message flag
   * @param message the message
   * @note This is the method from the base class that should be overriden.
   *       Typically a subclass may filter, change, and output
   *       messages based on configuration and the messageType.
   */
  void addMessageUnconditionally(int64_t messageType,
                                 const std::string& message) override;

 private:
  std::map<int64_t, size_t> m_count;  //!< count messages acc. to their types
  bool print_summary_ = true;  //!< whether to print a summary to the log file
};
}  // namespace Opm
#endif  // ECLIPSEPRTLOG_H
