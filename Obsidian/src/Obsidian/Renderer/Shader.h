#pragma once

#include <string>

namespace Obsidian {
	class Shader {
	public:
		Shader(const std::string& vertextSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t m_RendererID;
	};
}