#pragma once
/*
 *      Copyright (C) 2016 Christian Browet
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "network/Network.h"

#include "android/jni/Network.h"
#include "android/jni/NetworkInfo.h"
#include "android/jni/LinkProperties.h"
#include "android/jni/RouteInfo.h"
#include "android/jni/NetworkInterface.h"

class CNetworkAndroid;

class CNetworkInterfaceAndroid : public CNetworkInterface
{
public:
  CNetworkInterfaceAndroid(CJNINetwork network, const CJNINetworkInfo& ni, const CJNILinkProperties& lp, const CJNINetworkInterface& intf);
  std::vector<std::string> GetNameServers();
  
  // CNetworkInterface interface
public:
  virtual std::string& GetName() override;
  virtual bool IsEnabled() override;
  virtual bool IsConnected() override;
  virtual bool IsWireless() override;
  virtual std::string GetMacAddress() override;
  virtual void GetMacAddressRaw(char rawMac[6]) override;
  virtual bool GetHostMacAddress(unsigned long host, std::string& mac) override;
  virtual std::string GetCurrentIPAddress() override;
  virtual std::string GetCurrentNetmask() override;
  virtual std::string GetCurrentDefaultGateway() override;
  virtual std::string GetCurrentWirelessEssId() override;
  virtual std::vector<NetworkAccessPoint> GetAccessPoints() override;
  virtual void GetSettings(NetworkAssignment& assignment, std::string& ipAddress, std::string& networkMask, std::string& defaultGateway, std::string& essId, std::string& key, EncMode& encryptionMode) override;
  virtual void SetSettings(NetworkAssignment& assignment, std::string& ipAddress, std::string& networkMask, std::string& defaultGateway, std::string& essId, std::string& key, EncMode& encryptionMode) override;
  
protected:
  std::string m_name;
  CJNINetwork m_network;
  CJNINetworkInfo m_ni;
  CJNILinkProperties m_lp;
  CJNINetworkInterface m_intf;
};


class CNetworkAndroid : public CNetwork
{
public:
  CNetworkAndroid();
  
  // CNetwork interface
public:
  virtual bool GetHostName(std::string& hostname) override;
  virtual std::vector<CNetworkInterface*>& GetInterfaceList() override;
  virtual CNetworkInterface* GetFirstConnectedInterface() override;
  virtual bool PingHost(unsigned long host, unsigned int timeout_ms) override;
  virtual std::vector<std::string> GetNameServers() override;
  virtual void SetNameServers(const std::vector<std::string>& nameServers) override;
  
protected:
  void RetrieveInterfaces();
  std::vector<CNetworkInterface*> m_interfaces;  
};

