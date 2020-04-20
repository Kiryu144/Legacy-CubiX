/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_SUB_RENDERER_H
#define CUBIX_SUB_RENDERER_H

namespace Game
{

class Renderer;

class SubRenderer
{
protected:
	Renderer& m_renderer;

public:
	SubRenderer( Renderer& renderer ) : m_renderer( renderer ) {}
	virtual void finalize() = 0;
};

} // namespace Game

#endif // CUBIX_SUB_RENDERER_H
