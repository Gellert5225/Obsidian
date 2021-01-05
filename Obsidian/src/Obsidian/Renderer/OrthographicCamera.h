#pragma once

#include <glm/glm.hpp>

namespace Obsidian {
	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		const float GetRotation() const { return m_Rotation; }

		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4 GetVPMatrix() const { return m_VPMatrix; }
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_VPMatrix;
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;

		void RecalculateViewMatrix();
	};
}