/*
 * Copyright (c) 2025 Your Name/Organization (Modified from DERONNE SOFTWARE ENGINEERING)
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
 * Author: Your Name <your.email@example.com> (Original Author: Sébastien Deronne)
 */

#ifndef UHR_CAPABILITIES_H
#define UHR_CAPABILITIES_H

#include "ns3/wifi-information-element.h"

namespace ns3
{

/**
 * \ingroup wifi
 *
 * The IEEE 802.11bn UHR Capabilities
 */
class UhrCapabilities : public WifiInformationElement
{
  public:
    UhrCapabilities();

    // --- Public API for setting/getting capabilities ---
    /**
     * \brief Set whether Unequal Modulation is supported.
     * \param supported true if supported, false otherwise.
     */
    void SetUneqmSupported(bool supported);

    /**
     * \brief Get whether Unequal Modulation is supported.
     * \return true if supported, false otherwise.
     */
    bool IsUneqmSupported() const;

    // --- Implementations of pure virtual methods from base class ---
    WifiInformationElementId ElementId() const override;
    WifiInformationElementId ElementIdExt() const override;

  private:
    uint16_t GetInformationFieldSize() const override;
    void SerializeInformationField(Buffer::Iterator start) const override;
    uint16_t DeserializeInformationField(Buffer::Iterator start, uint16_t length) override;

    // --- UHR Capability Fields ---
    // UHR: This bit indicates if the STA supports Unequal Modulation (UEQM).
    bool m_uneqmSupported;
};

/**
 * \brief Stream insertion operator for UhrCapabilities.
 * \param os the output stream
 * \param uhrCapabilities the UHR capabilities
 * \returns the output stream
 */
std::ostream& operator<<(std::ostream& os, const UhrCapabilities& uhrCapabilities);

} // namespace ns3

#endif /* UHR_CAPABILITIES_H */