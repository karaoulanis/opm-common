/*
  Copyright 2015, 2016 Statoil ASA.
  Copyright 2016 SINTEF ICT, Applied Mathematics.

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

#ifndef OPM_LOGBACKEND_HPP
#define OPM_LOGBACKEND_HPP

#include <opm/common/OpmLog/MessageFormatter.hpp>
#include <opm/common/OpmLog/MessageLimiter.hpp>
#include <cstdint>
#include <string>
#include <memory>

namespace Opm {
/**
 * @class LogBackend
 * @file Abstract interface class for log backends.
 * @brief 
 */
class LogBackend {
 public:
  /**
   * @brief Construct with given message mask.
   * @param mask the mask of the log back end
   */
  explicit LogBackend(int64_t mask);

  /**
   * @brief Virtual destructor to enable inheritance.
   */
  virtual ~LogBackend();

  /**
   * @brief Configure how formatMessage() will modify message strings.
   * @param formatter the string formatter
   */
  void setMessageFormatter(
      std::shared_ptr<MessageFormatterInterface> formatter);

  /**
   * @brief Configure how message tags will be used to limit messages.
   * @param limiter The message limiter.
   */
  void setMessageLimiter(std::shared_ptr<MessageLimiter> limiter);

  /**
   * @brief Add a message to the backend if accepted by the message limiter.
   * @param messageFlag the message flag
   * @param message the message
   * @note The messageTag is assumed an empty string ("") in this case.
   */
  void addMessage(int64_t messageFlag, const std::string& message);

  /**
   * @brief Add a tagged message to the backend if accepted by the message limiter.
   * @param messageFlag the message flag
   * @param messageTag the message tag
   * @param message the message
   */
  void addTaggedMessage(int64_t messageFlag,
                        const std::string& messageTag,
                        const std::string& message);


  /**
   * @brief Get the message mask.
   * @return an integer as described in Opm::Log::MessageType namespace,
   *         in file LogUtils.hpp.
   * 
   *         More specifically:
   *         - Debug     =  1   Excessive information
   *         - Note      =  2;  Information that should only go into print file
   *         - Info      =  4;  Normal status information
   *         - Warning   =  8;  Input anomaly - possible error
   *         - Error     = 16;   Error in the input data - should probably exit
   *         - Problem   = 32;   Calculation problems - e.g. convergence failure
   *         - Bug       = 64;   An inconsistent state has been encountered in
   *                             the simulator - should probably exit.
   */
  int64_t getMask() const;

 protected:
  /**
   * @brief Add a message to the log.
   * @param messageFlag the message flag
   * @param message the message
   * @note This is the method subclasses should override.
   *       Typically a subclass may filter, change, and output
   *       messages based on configuration and the messageFlag.
   */
  virtual void addMessageUnconditionally(int64_t messageFlag,
                                         const std::string& message) = 0;

  /**
   * @brief Return decorated version of message depending on
   *        configureDecoration() arguments.
   * @param messageFlag the message flag
   * @param message the message
   * @return 
   */
  std::string formatMessage(int64_t messageFlag, const std::string& message);

 private:
  /**
   * @brief Check whether to include a message.
   * @param messageFlag the message flag
   * @param message the message
   * @return True if all bits of messageFlag are also set in our mask,
   *         and the message limiter returns a PrintMessage response.
   */
  bool includeMessage(int64_t messageFlag, const std::string& messageTag);

  int64_t m_mask;  //!< the message mask
  std::shared_ptr<MessageFormatterInterface>
      m_formatter;  //!< the message formatter
  std::shared_ptr<MessageLimiter> m_limiter;  //!< the message limiter
};
}  // namespace Opm
#endif
