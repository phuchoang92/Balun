#include "hzpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Balun {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}