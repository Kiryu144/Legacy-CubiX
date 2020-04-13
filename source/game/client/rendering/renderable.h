/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_RENDERABLE_H
#define CUBIX_RENDERABLE_H

namespace Game
{

class View;
class Projection;

class Renderable
{
public:
	virtual void render( const View& view, const Projection& projection ) = 0;
};

} // namespace Game

#endif // CUBIX_RENDERABLE_H
