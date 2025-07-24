/*
 * Copyright (c) 2025 Yuntai (Modified from DERONNE SOFTWARE ENGINEERING)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Yuntai (Original Author: Sébastien Deronne)
 */

#ifndef UHR_CONFIGURATION_H
#define UHR_CONFIGURATION_H

#include "ns3/object.h"

namespace ns3
{

/**
 * \brief UHR configuration
 * \ingroup wifi
 *
 * This object stores UHR (Ultra High Reliability) configuration information, for use in modifying
 * AP or STA behavior and for constructing UHR-related information elements.
 *
 */
class UhrConfiguration : public Object
{
  public:
    UhrConfiguration();
    ~UhrConfiguration() override;

    /**
     * \brief Get the type ID.
     * \return the object TypeId
     */
    static TypeId GetTypeId();
    /**
     * \brief Get whether Unequal Modulation is enabled in the configuration.
     * \return true if enabled, false otherwise.
     */
    bool IsUneqmEnabled() const;

  private:
    bool m_uneqmEnabled; ///< Whether Unequal Modulation is enabled
};

} // namespace ns3

#endif /* UHR_CONFIGURATION_H */