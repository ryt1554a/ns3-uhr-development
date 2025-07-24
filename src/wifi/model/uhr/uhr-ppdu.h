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

#ifndef UHR_PPDU_H
#define UHR_PPDU_H

#include "ns3/eht-ppdu.h"

/**
 * \file
 * \ingroup wifi
 * Declaration of ns3::UhrPpdu class.
 */

namespace ns3
{

/**
 * \brief UHR PPDU (11bn)
 * \ingroup wifi
 *
 * UhrPpdu is currently identical to EhtPpdu.
 * This class serves as a placeholder for future UHR-specific PPDU logic.
 */
class UhrPpdu : public EhtPpdu
{
  public:
    /**
     * Create a UHR PPDU, storing a map of PSDUs.
     *
     * This PPDU can either be UL or DL.
     *
     * \param psdus the PHY payloads (PSDUs)
     * \param txVector the TXVECTOR that was used for this PPDU
     * \param txCenterFreq the center frequency (MHz) that was used for this PPDU
     * \param ppduDuration the transmission duration of this PPDU
     * \param band the WifiPhyBand used for the transmission of this PPDU
     * \param uid the unique ID of this PPDU or of the triggering PPDU if this is a UHR TB PPDU
     * \param flag the flag indicating the type of Tx PSD to build
     * \param p20Index the index of the primary 20 MHz channel
     */
    UhrPpdu(const WifiConstPsduMap& psdus,
            const WifiTxVector& txVector,
            uint16_t txCenterFreq,
            Time ppduDuration,
            WifiPhyBand band,
            uint64_t uid,
            TxPsdFlag flag,
            uint8_t p20Index);
    /**
     * Destructor for UhrPpdu.
     */
    ~UhrPpdu() override;

    WifiPpduType GetType() const override;
    Ptr<WifiPpdu> Copy() const override;

  protected:
    bool IsDlMu() const override;
    bool IsUlMu() const override;
    WifiTxVector DoGetTxVector() const override;
}; // class UhrPpdu

} // namespace ns3

#endif /* UHR_PPDU_H */