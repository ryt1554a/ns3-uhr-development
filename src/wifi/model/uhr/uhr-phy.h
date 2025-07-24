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

#ifndef UHR_PHY_H
#define UHR_PHY_H

#include "ns3/eht-phy.h"

/**
 * \file
 * \ingroup wifi
 * Declaration of ns3::UhrPhy class.
 */

namespace ns3
{

/**
 * This defines the BSS membership value for UHR PHY.
 */
#define UHR_PHY 122 // FIXME: This is a placeholder value.

/**
 * \brief PHY entity for UHR (11bn)
 * \ingroup wifi
 *
 * UHR PHY is based on EHT PHY.
 *
 * Refer to the latest IEEE P802.11bn draft.
 */
class UhrPhy : public EhtPhy
{
  public:
    /**
     * Constructor for UHR PHY
     * \param buildModeList flag used to add UHR modes to list
     */
    UhrPhy(bool buildModeList = true);
    /**
     * Destructor for UHR PHY
     */
    ~UhrPhy() override;

    // --- Overridden public virtual methods ---
    const PpduFormats& GetPpduFormats() const override;
    Time GetDuration(WifiPpduField field, const WifiTxVector& txVector) const override;
    Ptr<WifiPpdu> BuildPpdu(const WifiConstPsduMap& psdus,
                            const WifiTxVector& txVector,
                            Time ppduDuration) override;

    // --- Public static methods for UHR MCS ---
    static void InitializeModes();
    static WifiMode GetUhrMcs(uint8_t index);
    static WifiMode GetUhrMcs0();
    static WifiMode GetUhrMcs1();
    static WifiMode GetUhrMcs2();
    static WifiMode GetUhrMcs3();
    static WifiMode GetUhrMcs4();
    static WifiMode GetUhrMcs5();
    static WifiMode GetUhrMcs6();
    static WifiMode GetUhrMcs7();
    static WifiMode GetUhrMcs8();
    static WifiMode GetUhrMcs9();
    static WifiMode GetUhrMcs10();
    static WifiMode GetUhrMcs11();
    static WifiMode GetUhrMcs12();
    static WifiMode GetUhrMcs13();
    static WifiMode GetUhrMcs17();
    static WifiMode GetUhrMcs19();
    static WifiMode GetUhrMcs20();
    static WifiMode GetUhrMcs23();
    static WifiCodeRate GetCodeRate(uint8_t mcsValue);
    static uint16_t GetConstellationSize(uint8_t mcsValue);
    static uint64_t GetPhyRate(uint8_t mcsValue,
                               uint16_t channelWidth,
                               uint16_t guardInterval,
                               uint8_t nss);
    static uint64_t GetPhyRateFromTxVector(const WifiTxVector& txVector,
                                           uint16_t staId = SU_STA_ID);
    static uint64_t GetDataRateFromTxVector(const WifiTxVector& txVector,
                                            uint16_t staId = SU_STA_ID);
    static uint64_t GetDataRate(uint8_t mcsValue,
                                uint16_t channelWidth,
                                uint16_t guardInterval,
                                uint8_t nss);

  protected:
    // --- Overridden protected virtual methods ---
    void BuildModeList() override;
    WifiMode GetSigMode(WifiPpduField field, const WifiTxVector& txVector) const override;
    // NOTE: You may need to add more overrides here as you implement more UHR-specific logic
    // For example: DoEndReceiveField, ProcessSig, GetFailureReason, etc.

    // --- Protected static methods ---
    static WifiMode CreateUhrMcs(uint8_t index);
    static const PpduFormats m_uhrPpduFormats; //!< UHR PPDU formats
};

} // namespace ns3

#endif /* UHR_PHY_H */