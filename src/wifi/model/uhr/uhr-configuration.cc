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

#include "uhr-configuration.h"
#include "ns3/boolean.h"
#include "ns3/log.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("UhrConfiguration");
NS_OBJECT_ENSURE_REGISTERED(UhrConfiguration);

UhrConfiguration::UhrConfiguration()
{
    NS_LOG_FUNCTION(this);
    m_uneqmEnabled = false;
}

UhrConfiguration::~UhrConfiguration()
{
    NS_LOG_FUNCTION(this);
}

TypeId
UhrConfiguration::GetTypeId()
{
    static ns3::TypeId tid =
        ns3::TypeId("ns3::UhrConfiguration")
            .SetParent<Object>()
            .SetGroupName("Wifi")
            .AddConstructor<UhrConfiguration>()
            // Add the UneqmEnabled attribute
            .AddAttribute("UneqmEnabled",
                          "Whether Unequal Modulation (UEQM) is enabled.",
                          BooleanValue(false), // Default value
                          MakeBooleanAccessor(&UhrConfiguration::m_uneqmEnabled),
                          MakeBooleanChecker());
    return tid;
}

bool
UhrConfiguration::IsUneqmEnabled() const
{
    return m_uneqmEnabled;
}

} // namespace ns3