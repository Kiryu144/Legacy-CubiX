/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_PROXY_H
#define CUBIX_PROXY_H

namespace Game
{

class Proxy
{
public:
	static const bool Server{ true };
	static const bool Client{ false };

protected:
	bool m_serverSide;

public:
	Proxy( bool serverSide ) : m_serverSide( serverSide ) {}

	bool isServer() const
	{
		return m_serverSide;
	}

	bool isClient() const
	{
		return !isServer();
	}
};

} // namespace Game

#endif // CUBIX_PROXY_H
