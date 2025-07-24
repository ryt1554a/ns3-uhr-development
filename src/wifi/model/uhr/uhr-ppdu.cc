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

#include "uhr-ppdu.h"

#include "uhr-phy.h"

#include "ns3/log.h"
#include "ns3/wifi-psdu.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("UhrPpdu");

UhrPpdu::UhrPpdu(const WifiConstPsduMap& psdus,
                 const WifiTxVector& txVector,
                 uint16_t txCenterFreq,
                 Time ppduDuration,
                 WifiPhyBand band,
                 uint64_t uid,
                 TxPsdFlag flag,
                 uint8_t p20Index)
    : EhtPpdu(psdus, txVector, txCenterFreq, ppduDuration, band, uid, flag, p20Index)
{
    NS_LOG_FUNCTION(this << psdus << txVector << txCenterFreq << ppduDuration << band << uid << flag
                         << p20Index);
}

UhrPpdu::~UhrPpdu()
{
    NS_LOG_FUNCTION(this);
}

WifiPpduType
UhrPpdu::GetType() const
{
    if (m_muUserInfos.empty())
    {
        return WIFI_PPDU_TYPE_SU;
    }
    switch (m_preamble)
    {
    case WIFI_PREAMBLE_UHR_MU:
        return WIFI_PPDU_TYPE_DL_MU;
    case WIFI_PREAMBLE_UHR_TB:
        return WIFI_PPDU_TYPE_UL_MU;
    default:
        NS_ASSERT_MSG(false, "invalid preamble " << m_preamble);
        return WIFI_PPDU_TYPE_SU;
    }
}

bool
UhrPpdu::IsDlMu() const
{
    return (m_preamble == WIFI_PREAMBLE_UHR_MU) && !m_muUserInfos.empty();
}

bool
UhrPpdu::IsUlMu() const
{
    return (m_preamble == WIFI_PREAMBLE_UHR_TB) && !m_muUserInfos.empty();
}

WifiTxVector
UhrPpdu::DoGetTxVector() const
{
    // FIXME: define UHR PHY headers and parse them here
    WifiTxVector txVector;
    txVector.SetPreambleType(m_preamble);
    // Note: This currently assumes HE-SIG-like structure.
    // This part will need significant updates once UHR-SIG is modeled.
    txVector.SetMode(UhrPhy::GetUhrMcs(m_heSig.GetMcs()));
    txVector.SetChannelWidth(m_heSig.GetChannelWidth());
    txVector.SetNss(m_heSig.GetNStreams());
    txVector.SetGuardInterval(m_heSig.GetGuardInterval());
    txVector.SetBssColor(m_heSig.GetBssColor());
    txVector.SetLength(m_lSig.GetLength());
    txVector.SetAggregation(m_psdus.size() > 1 || m_psdus.begin()->second->IsAggregate());
    for (const auto& muUserInfo : m_muUserInfos)
    {
        txVector.SetHeMuUserInfo(muUserInfo.first, muUserInfo.second);
    }
    return txVector;
}

Ptr<WifiPpdu>
UhrPpdu::Copy() const
{
    return ns3::Copy(Ptr(this));
}

} // namespace ns3