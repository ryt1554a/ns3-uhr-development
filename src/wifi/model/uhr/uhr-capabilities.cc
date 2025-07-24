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

#include "uhr-capabilities.h"
#include "ns3/log.h"
#include "ns3/buffer.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("UhrCapabilities");

UhrCapabilities::UhrCapabilities() : m_uneqmSupported(false)
{
    // Initialize all capabilities to their default (usually false/0)
}

// --- Public API ---
void
UhrCapabilities::SetUneqmSupported(bool supported)
{
    m_uneqmSupported = supported;
}

bool
UhrCapabilities::IsUneqmSupported() const
{
    return m_uneqmSupported;
}

// --- WifiInformationElement virtual methods ---
WifiInformationElementId
UhrCapabilities::ElementId() const
{
    // New IEs use the extension identifier.
    return IE_EXTENSION;
}

WifiInformationElementId
UhrCapabilities::ElementIdExt() const
{
    // This requires adding a new enum value 'IE_EXT_UHR_CAPABILITIES'
    // in src/wifi/model/wifi-information-element.h
    return IE_EXT_UHR_CAPABILITIES;
}

uint16_t
UhrCapabilities::GetInformationFieldSize() const
{
    // For now, we only have one byte for UHR MAC capabilities.
    // This will increase as more capabilities are added.
    return 1;
}

void
UhrCapabilities::SerializeInformationField(Buffer::Iterator start) const
{
    // The information field contains the UHR MAC Capabilities.
    // We will use the first bit of the first byte for Unequal Modulation support.
    uint8_t macCapabilities = 0;

    // Bit 0: Unequal Modulation Supported
    if (m_uneqmSupported)
    {
        macCapabilities |= (1 << 0);
    }

    // Write the byte to the buffer.
    start.WriteU8(macCapabilities);
}

uint16_t
UhrCapabilities::DeserializeInformationField(Buffer::Iterator start, uint16_t length)
{
    // Ensure we have at least one byte to read.
    if (length < 1)
    {
        NS_LOG_WARN("Cannot deserialize UHR Capabilities: length is less than 1 byte.");
        return 0;
    }

    // Read the first byte containing UHR MAC capabilities.
    uint8_t macCapabilities = start.ReadU8();

    // Bit 0: Unequal Modulation Supported
    m_uneqmSupported = (macCapabilities & (1 << 0));

    // Return the number of bytes consumed.
    return 1;
}

std::ostream&
operator<<(std::ostream& os, const UhrCapabilities& uhrCapabilities)
{
    os << "[UneqmSupported: " << (uhrCapabilities.IsUneqmSupported() ? "Yes" : "No");
    os << "]";
    return os;
}

} // namespace ns3