#include "texture.h"

#include <glad/glad.h>

namespace Cubix
{
namespace Core
{
namespace GL
{

const TextureParameters::Parameter TextureParameters::Parameters::FILTER_NEAREST[ 2 ]{
	{ GL_TEXTURE_MIN_FILTER, GL_NEAREST }, { GL_TEXTURE_MAG_FILTER, GL_NEAREST }
};
const TextureParameters::Parameter TextureParameters::Parameters::FILTER_LINEAR[ 2 ]{
	{ GL_TEXTURE_MIN_FILTER, GL_LINEAR }, { GL_TEXTURE_MAG_FILTER, GL_LINEAR }
};
const TextureParameters::Parameter TextureParameters::Parameters::WRAP_REPEAT[ 2 ]{
	{ GL_TEXTURE_WRAP_S, GL_REPEAT }, { GL_TEXTURE_WRAP_T, GL_REPEAT }
};
const TextureParameters::Parameter TextureParameters::Parameters::WRAP_MIRRORED_REPEAT[ 2 ]{
	{ GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT }, { GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT }
};
const TextureParameters::Parameter TextureParameters::Parameters::WRAP_CLAMP_TO_EDGE[ 2 ]{
	{ GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE }, { GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE }
};
const TextureParameters::Parameter TextureParameters::Parameters::WRAP_CLAMP_TO_BORDER[ 2 ]{
	{ GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER }, { GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER }
};

TextureParameters::TextureParameters( const Type& mType ) : m_type( mType ) {}

void TextureParameters::addParameter( const TextureParameters::Parameter& parameter )
{
	m_parameters.push_back( parameter );
}

void TextureParameters::addParameter( const TextureParameters::Parameter parameter[ 2 ] )
{
	addParameter( parameter[ 0 ] );
	addParameter( parameter[ 1 ] );
}

thread_local BindableStateID Texture::bindableStateId( glBindTexture, glDeleteTextures );

Texture::~Texture()
{
	clear();
}

void Texture::set( const unsigned char* data,
				   const glm::uvec2& size,
				   const Texture::PixelFormat& pixelFormat,
				   const TextureParameters& textureParameters )
{
	assert( data );
	assert( size.x * size.y );

	if( !containsData() )
	{
		glGenTextures( 1, &m_textureID );
	}

	bind();
	unsigned int textureType = static_cast< GLuint >( textureParameters.getType() );
	for( auto parameter : textureParameters.getParameters() )
	{
		glTexParameteri( textureType, parameter.parameter, parameter.value );
	}

	glTexImage2D( textureType,
				  0,
				  GL_RGBA, // TODO: Detect type
				  size.x,
				  size.y,
				  0,
				  static_cast< GLuint >( pixelFormat ),
				  GL_UNSIGNED_BYTE,
				  data );
	glGenerateMipmap( textureType );

	m_size = size;
	m_type = textureParameters.getType();
}

void Texture::bind() const
{
	assert( containsData() );
	bindableStateId.bind( this );
}

void Texture::clear()
{
	bindableStateId.del( this );
	m_textureID = 0;
}

bool Texture::containsData() const
{
	return m_textureID > 0;
}

const glm::uvec2& Texture::size() const
{
	return m_size;
}

unsigned int Texture::getStateID() const
{
	return m_textureID;
}

unsigned int Texture::getTypeID() const
{
	return static_cast< unsigned int >( m_type );
}

} // namespace GL
} // namespace Core
} // namespace Cubix