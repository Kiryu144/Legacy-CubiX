/*
 * Copyright (c) 2020 David Klostermann.
 */

#ifndef CUBIX_CUBIX_CLIENT_H
#define CUBIX_CUBIX_CLIENT_H

#include "core/io/window.h"
#include "core/net/net_client.h"

#include "game/cubix.h"
#include "game/rendering/moveable_view.h"
#include "game/rendering/renderer.h"

namespace Game
{

class PlayerController;

class CubixClient : public Cubix,
					public Core::NetClient,
					public Core::Listener< Core::EventWindowResize >,
					public Core::Listener< Core::EventWindowFileDrop >,
					public Core::Listener< Core::UserInputHandler::EventUpdate >
{
private:
	Core::Window m_window;
	Renderer m_renderer;
	MoveableView m_moveableView;
	std::shared_ptr< PlayerController > m_playerController;

	int m_viewDistance{ 12 };

	void update() override;

#if CUBIX_IMGUI
	std::string m_voxelMemoryConsumption{ "Total Voxel Memory: 0B" };
#endif

	void setWindowTitle();

protected:
	void onPacketReceive( Core::PeerID id, std::istream& istream ) override;
	void onEvent( const Core::EventWindowResize& eventType ) override;
	void onEvent( const Core::EventWindowFileDrop& eventType ) override;
	void onEvent( const Core::UserInputHandler::EventUpdate& eventType ) override;

public:
	CubixClient();
};

} // namespace Game

#endif
