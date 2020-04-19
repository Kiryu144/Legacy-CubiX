/*
 * Copyright (c) 2020 David Klostermann.
 */

#include "cubix_client.h"

#include "core/logic/string_cast.h"
#include "core/opengl/shader_program.h"

#include "game/packet/packet_client_information.h"
#include "game/packet/packet_server_information.h"
#include "game/rendering/gizmo_renderer.h"
#include "game/world/entity/entity.h"

#include <glfw/glfw3.h>
#include <imgui/imgui.h>

namespace Game
{

CubixClient::CubixClient() : m_window( 1440, 900, "CubiX" )
{
	m_world.setRenderer( &m_renderer );
	m_gameTime.setFPSLimit( 10000 );
	connect( "127.0.0.1", 4444 );
	m_moveableView.setSpeed( 30 );

	// World Chunk Shader
	std::shared_ptr< Core::ShaderProgram > worldChunkShader( new Core::ShaderProgram() );
	worldChunkShader
		->compileShaderFromFile( "shader\\world_chunk.vert", Core::ShaderProgram::VERTEX_SHADER )
		.compileShaderFromFile( "shader\\world_chunk.frag", Core::ShaderProgram::FRAGMENT_SHADER )
		.link();
	m_renderer.getShaderRegistry().insert( "world_chunk_shader", std::move( worldChunkShader ) );

	// Gizmo Shader
	std::shared_ptr< Core::ShaderProgram > gizmoShader( new Core::ShaderProgram() );
	gizmoShader
		->compileShaderFromFile( "shader\\gizmo_shader.vert", Core::ShaderProgram::VERTEX_SHADER )
		.compileShaderFromFile( "shader\\gizmo_shader.frag", Core::ShaderProgram::FRAGMENT_SHADER )
		.link();
	m_renderer.getShaderRegistry().insert( "gizmo_shader", std::move( gizmoShader ) );

	// Voxel Structure Shader
	std::shared_ptr< Core::ShaderProgram > voxelStructureShader( new Core::ShaderProgram() );
	voxelStructureShader
		->compileShaderFromFile( "shader\\voxel_structure.vert",
								 Core::ShaderProgram::VERTEX_SHADER )
		.compileShaderFromFile( "shader\\voxel_structure.frag",
								Core::ShaderProgram::FRAGMENT_SHADER )
		.link();
	m_renderer.getShaderRegistry().insert( "voxel_structure_shader",
										   std::move( voxelStructureShader ) );

	m_renderer.initializeSubRenderers();
}

void CubixClient::update()
{
	Cubix::update();
	Core::Window::Update();
	m_window.swap();

	if( m_window.shouldClose() )
	{
		quit();
	}

	glm::ivec3 playerChunkPos{ IWorldChunk::ChunkPosFromWorldPos( m_moveableView.getPosition() ) };
	for( int x = -m_viewDistance; x <= m_viewDistance; ++x )
	{
		for( int z = -m_viewDistance; z <= m_viewDistance; ++z )
		{
			glm::ivec2 chunkPos{ playerChunkPos.x + x, playerChunkPos.z + z };
			double distance{ std::sqrt(
				std::pow( static_cast< float >( chunkPos.x ) - playerChunkPos.x, 2 )
				+ std::pow( static_cast< float >( chunkPos.y ) - playerChunkPos.z, 2 ) ) };
			if( distance <= m_viewDistance )
			{
				m_world.updateForPlayer( chunkPos );
			}
		}
	}

	m_moveableView.update( m_gameTime.getDeltaTime() );
	m_renderer.setView( m_moveableView.getViewMatrix() );
	m_world.render();

#if CUBIX_IMGUI
	bool active = true;
	ImGui::Begin( "Debug Information", &active );
	ImGui::Text( "FPS: %d", int( m_gameTime.getFPS() ) );
	ImGui::Text( "Chunks loaded: %d", m_world.getAllChunks().size() );
	ImGui::Text( "Chunk queue: %d", m_world.getChunkWorker().size() );
	ImGui::SliderInt( "View Distance", &m_viewDistance, 2, 32 );
	ImGui::Text( "Position: %d %d %d",
				 static_cast< int >( m_moveableView.getPosition().x ),
				 static_cast< int >( m_moveableView.getPosition().y ),
				 static_cast< int >( m_moveableView.getPosition().z ) );
	ImGui::Text( "Chunk Position: %d %d %d",
				 static_cast< int >(
					 std::floor( m_moveableView.getPosition().x / IWorldChunk::GetSideLength() ) ),
				 static_cast< int >(
					 std::floor( m_moveableView.getPosition().y / IWorldChunk::GetSideLength() ) ),
				 static_cast< int >( std::floor( m_moveableView.getPosition().z
												 / IWorldChunk::GetSideLength() ) ) );
	if( ImGui::Button( m_voxelMemoryConsumption.c_str() ) )
	{
		m_voxelMemoryConsumption = "Total Voxel Memory: "
			+ Core::ByteSizeToString( m_world.calculateVoxelMemoryConsumption() );
	}
	ImGui::End();
#endif
}

void CubixClient::onPacketReceive( Core::PeerID id, std::istream& istream )
{
	PacketType type;
	istream.read( reinterpret_cast< char* >( &type ), sizeof( decltype( type ) ) );

	switch( type )
	{
	case PacketType::CLIENTBOUND_SERVER_INFORMATION:
		PacketServerInformation packetServerInformation( "" );
		packetServerInformation.deserialize( istream );
		Core::Logger::Log( std::string( "Connected to " )
						   + packetServerInformation.getName().get() );
		PacketClientInformation packetClientInformation( "Kiryu" );
		send( id, &packetClientInformation );
		break;
	}
}

void CubixClient::onEvent( const Core::EventWindowResize& eventType )
{
	glm::mat4 projection = glm::perspective(
		glm::radians( 70.0f ), static_cast< float >( eventType.w ) / eventType.h, 0.1f, 1000.0f );
	m_renderer.setProjection( projection );
}

void CubixClient::onEvent( const Core::UserInputHandler::EventUpdate& eventType )
{
	if( eventType.instance.isKeyDown( Core::UserInputHandler::F ) )
	{
		std::shared_ptr< Entity > entity( new Entity() );
		entity->getPosition() = m_moveableView.getPosition();
		entity->setVelocity( m_moveableView.getDirection() * glm::vec3( 50.0f ) );
		m_world.summonEntity( entity );
	}
}

void CubixClient::onEvent( const Core::EventWindowFileDrop& eventType )
{
	// m_group.reset( new VoxelGroup( eventType.fpath ) );
}

} // namespace Game