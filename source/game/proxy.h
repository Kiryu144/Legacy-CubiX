/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_PROXY_H
#define CUBIX_PROXY_H

namespace Game
{

enum class Proxy
{
	CLIENT,
	SERVER,
	UNKNOWN
};

class ProxySided
{
private:
	Proxy m_proxy;

public:
	ProxySided( const Proxy& proxy ) : m_proxy( proxy ) {}

	Proxy getProxy() const
	{
		return m_proxy;
	}
};

} // namespace Game

#endif // CUBIX_PROXY_H
