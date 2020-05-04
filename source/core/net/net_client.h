/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_NET_CLIENT_H
#define CUBIX_NET_CLIENT_H

#include "net_instance.h"

#include "core/cubix_macro.h"

namespace Core
{

class NetClient : public virtual NetInstance
{
protected:
	ENetPeer* m_peer{ nullptr };
	bool m_peerConnected{ false };
	std::string m_connectedName;

	void onNetworkingEvent( const ENetEvent& event ) override;

public:
	NetClient();
	virtual ~NetClient();

	CUBIX_GET_V( m_peerConnected, Connected );
	CUBIX_GET_CR( m_connectedName, Host );

	bool connect( const std::string& name );
	void disconnect();
};

} // namespace Core

#endif
