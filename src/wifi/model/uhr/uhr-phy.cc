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

#include "uhr-phy.h"
#include "uhr-ppdu.h"

#include "ns3/interference-helper.h"
#include "ns3/wifi-phy.h"
#include "ns3/wifi-psdu.h"
#include "ns3/wifi-utils.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("UhrPhy");

/*******************************************************
 * UHR PHY (P802.11bn)
 *******************************************************/

// UHR: For now, we assume the PPDU format is identical to EHT.
// This will be the place to define UHR-specific PPDU formats if they differ.
const PhyEntity::PpduFormats UhrPhy::m_uhrPpduFormats = EhtPhy::m_ehtPpduFormats;

UhrPhy::UhrPhy(bool buildModeList /* = true */)
    : EhtPhy(false) // don't add EHT modes to list
{
    NS_LOG_FUNCTION(this << buildModeList);
    m_bssMembershipSelector = UHR_PHY;
    // UHR: The highest MCS index is now 23, but the set is non-contiguous.
    m_maxMcsIndexPerSs = 23;
    m_maxSupportedMcsIndexPerSs = m_maxMcsIndexPerSs;
    if (buildModeList)
    {
        BuildModeList();
    }
}

UhrPhy::~UhrPhy()
{
    NS_LOG_FUNCTION(this);
}

void
UhrPhy::BuildModeList()
{
    NS_LOG_FUNCTION(this);
    NS_ASSERT(m_modeList.empty());
    NS_ASSERT(m_bssMembershipSelector == UHR_PHY);
    // UHR: Build the non-contiguous list of supported MCSs.
    // Add MCS 0-13
    for (uint8_t index = 0; index <= 13; ++index)
    {
        NS_LOG_LOGIC("Add UhrMcs" << +index << " to list");
        m_modeList.emplace_back(CreateUhrMcs(index));
    }
    // Add new UHR-specific MCSs
    m_modeList.emplace_back(CreateUhrMcs(17));
    m_modeList.emplace_back(CreateUhrMcs(19));
    m_modeList.emplace_back(CreateUhrMcs(20));
    m_modeList.emplace_back(CreateUhrMcs(23));
}

// UHR: For PPDU-related functions, we inherit from EhtPhy for now.
// When the UHR PPDU format is finalized, these functions will need
// to be updated with UHR-specific logic.
WifiMode
UhrPhy::GetSigMode(WifiPpduField field, const WifiTxVector& txVector) const
{
    return EhtPhy::GetSigMode(field, txVector);
}

Time
UhrPhy::GetDuration(WifiPpduField field, const WifiTxVector& txVector) const
{
    return EhtPhy::GetDuration(field, txVector);
}

const PhyEntity::PpduFormats&
UhrPhy::GetPpduFormats() const
{
    return m_uhrPpduFormats;
}

Ptr<WifiPpdu>
UhrPhy::BuildPpdu(const WifiConstPsduMap& psdus, const WifiTxVector& txVector, Time ppduDuration)
{
    NS_LOG_FUNCTION(this << psdus << txVector << ppduDuration);
    // UHR: This should create a UhrPpdu once that class is defined.
    return Create<UhrPpdu>(psdus,
                           txVector,
                           m_wifiPhy->GetOperatingChannel().GetPrimaryChannelCenterFrequency(
                               txVector.GetChannelWidth()),
                           ppduDuration,
                           m_wifiPhy->GetPhyBand(),
                           ObtainNextUid(txVector),
                           HePpdu::PSD_NON_HE_PORTION,
                           m_wifiPhy->GetOperatingChannel().GetPrimaryChannelIndex(20));
}

void
UhrPhy::InitializeModes()
{
    for (uint8_t i = 0; i <= 13; ++i)
    {
        GetUhrMcs(i);
    }
    GetUhrMcs(17);
    GetUhrMcs(19);
    GetUhrMcs(20);
    GetUhrMcs(23);
}

WifiMode
UhrPhy::GetUhrMcs(uint8_t index)
{
#define CASE(x) case x: return GetUhrMcs##x();

    switch (index)
    {
        CASE(0)
        CASE(1)
        CASE(2)
        CASE(3)
        CASE(4)
        CASE(5)
        CASE(6)
        CASE(7)
        CASE(8)
        CASE(9)
        CASE(10)
        CASE(11)
        CASE(12)
        CASE(13)
        CASE(17) 
        CASE(19) 
        CASE(20) 
        CASE(23)
    default:
        NS_ABORT_MSG("Inexistent index (" << +index << ") requested for UHR");
        return WifiMode();
    }
#undef CASE
}

#define GET_UHR_MCS(x) \
    WifiMode UhrPhy::GetUhrMcs##x() \
    { \
        static WifiMode mcs = CreateUhrMcs(x); \
        return mcs; \
    };

GET_UHR_MCS(0)
GET_UHR_MCS(1)
GET_UHR_MCS(2)
GET_UHR_MCS(3)
GET_UHR_MCS(4)
GET_UHR_MCS(5) 
GET_UHR_MCS(6) 
GET_UHR_MCS(7) 
GET_UHR_MCS(8) 
GET_UHR_MCS(9)
GET_UHR_MCS(10) 
GET_UHR_MCS(11) 
GET_UHR_MCS(12) 
GET_UHR_MCS(13)
GET_UHR_MCS(17) 
GET_UHR_MCS(19) 
GET_UHR_MCS(20) 
GET_UHR_MCS(23)
#undef GET_UHR_MCS

WifiMode
UhrPhy::CreateUhrMcs(uint8_t index)
{
    return WifiModeFactory::CreateWifiMcs("UhrMcs" + std::to_string(index),
                                          index,
                                          WIFI_MOD_CLASS_UHR, // UHR: This requires a new enum
                                          false,
                                          MakeBoundCallback(&GetCodeRate, index),
                                          MakeBoundCallback(&GetConstellationSize, index),
                                          MakeCallback(&GetPhyRateFromTxVector),
                                          MakeCallback(&GetDataRateFromTxVector),
                                          MakeBoundCallback(&EhtPhy::GetNonHtReferenceRate, index),
                                          MakeCallback(&IsAllowed));
}

WifiCodeRate
UhrPhy::GetCodeRate(uint8_t mcsValue)
{
    switch (mcsValue)
    {
    // UHR: Add new MCS definitions based on user input
    case 17: // QPSK, R=2/3
    case 19: // 16-QAM, R=2/3
    case 23: // 256-QAM, R=2/3
        return WIFI_CODE_RATE_2_3;
    case 20: // 16-QAM, R=5/6
        return WIFI_CODE_RATE_5_6;
    // For MCS 0-13, fall back to the parent EhtPhy implementation
    default:
        return EhtPhy::GetCodeRate(mcsValue);
    }
}

uint16_t
UhrPhy::GetConstellationSize(uint8_t mcsValue)
{
    switch (mcsValue)
    {
    // UHR: Add new MCS definitions based on user input
    case 17: // QPSK
        return 4;
    case 19: // 16-QAM
    case 20: // 16-QAM
        return 16;
    case 23: // 256-QAM
        return 256;
    // For MCS 0-13, fall back to the parent EhtPhy implementation
    default:
        return EhtPhy::GetConstellationSize(mcsValue);
    }
}

// The following rate calculation functions are generic and can be reused.
// They will automatically use our new GetCodeRate and GetConstellationSize
// functions via the callbacks bound in CreateUhrMcs.

uint64_t
UhrPhy::GetPhyRate(uint8_t mcsValue, uint16_t channelWidth, uint16_t guardInterval, uint8_t nss)
{
    WifiCodeRate codeRate = GetCodeRate(mcsValue);
    uint64_t dataRate = GetDataRate(mcsValue, channelWidth, guardInterval, nss);
    return HtPhy::CalculatePhyRate(codeRate, dataRate);
}

uint64_t
UhrPhy::GetPhyRateFromTxVector(const WifiTxVector& txVector, uint16_t staId /* = SU_STA_ID */)
{
    uint16_t bw = txVector.GetChannelWidth();
    if (txVector.IsMu())
    {
        bw = HeRu::GetBandwidth(txVector.GetRu(staId).GetRuType());
    }
    return UhrPhy::GetPhyRate(txVector.GetMode(staId).GetMcsValue(),
                                bw,
                                txVector.GetGuardInterval(),
                                txVector.GetNss(staId));
}

uint64_t
UhrPhy::GetDataRateFromTxVector(const WifiTxVector& txVector, uint16_t staId /* = SU_STA_ID */)
{
    uint16_t bw = txVector.GetChannelWidth();
    if (txVector.IsMu())
    {
        bw = HeRu::GetBandwidth(txVector.GetRu(staId).GetRuType());
    }
    return UhrPhy::GetDataRate(txVector.GetMode(staId).GetMcsValue(),
                                 bw,
                                 txVector.GetGuardInterval(),
                                 txVector.GetNss(staId));
}

uint64_t
UhrPhy::GetDataRate(uint8_t mcsValue, uint16_t channelWidth, uint16_t guardInterval, uint8_t nss)
{
    NS_ASSERT(guardInterval == 800 || guardInterval == 1600 || guardInterval == 3200);
    NS_ASSERT(nss <= 8);
    return HtPhy::CalculateDataRate(GetSymbolDuration(NanoSeconds(guardInterval)),
                                    GetUsableSubcarriers(channelWidth),
                                    static_cast<uint16_t>(log2(GetConstellationSize(mcsValue))),
                                    HtPhy::GetCodeRatio(GetCodeRate(mcsValue)),
                                    nss);
}

} // namespace ns3

namespace
{
/**
 * Constructor class for UHR modes
 */
class ConstructorUhr
{
  public:
    ConstructorUhr()
    {
        ns3::UhrPhy::InitializeModes();
        // UHR: This requires adding WIFI_MOD_CLASS_UHR to the WifiModulationClass enum
        ns3::WifiPhy::AddStaticPhyEntity(ns3::WIFI_MOD_CLASS_UHR, ns3::Create<ns3::UhrPhy>());
    }
} g_constructor_uhr; ///< the constructor for UHR modes

} // namespace