/*
  Copyright 2015 Statoil ASA.

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

#ifndef STREAMLOG_H
#define STREAMLOG_H

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include "opm/common/OpmLog/LogBackend.hpp"

namespace Opm {
class StreamLog : public LogBackend {
 public:
  /**
   * @brief Constructor
   * @param messageMask the message mask
   * @param append whether to append on the existing stream
   */
  StreamLog(const std::string& logFile , int64_t messageMask,
            bool append = false);

  /**
   * @brief Constructor
   * @param os the output stream used for logging
   * @param messageMask the message mask
   */
  StreamLog(std::ostream& os , int64_t messageMask);

  /**
   * @brief Explicitely disallow copy constructor.
   * @note No implementation is given.
   */
  StreamLog(const StreamLog&);

  /**
   * @brief Explicitely disallow copy assignement.
   * @note No implementation is given.
   */
  void operator=(const StreamLog&);

  /**
   * @brief Desructor.
   */
  ~StreamLog();

 protected:
  /**
   * @brief Add a message to the log.
   * @param messageType the message flag
   * @param message the message
   * @note This is the method subclasses should override.
   *       Typically a subclass may filter, change, and output
   *       messages based on configuration and the messageType.
   */
  void addMessageUnconditionally(int64_t messageType,
                                 const std::string& message) override;

 private:
    /**
     * @brief Close stream.
     */
    void close();
    std::ofstream  m_ofstream;  //!< the output file stream
    std::ostream* m_ostream;  //!< the output stream
    bool m_streamOwner;  //!< whether the instance owns the stream
};
}  // namespace Opm
#endif

