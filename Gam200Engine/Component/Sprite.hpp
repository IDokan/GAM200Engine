/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Sprite.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.14.2019

	Header file for Graphic Component
******************************************************************************/
#pragma once
#include <filesystem>
class Component;

namespace Graphics
{
	class Mesh;
	class Vertices;
	struct material;
	class Texture;
}

class Sprite :
	public Component
{
public:
	Sprite(Object*) noexcept;
	virtual ~Sprite() noexcept = default;

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Clear() override;
	void UpdateUniforms(const matrix3& toNDC, float depth) noexcept;

	public:		// Getter & Setter
	void SetColor(const Graphics::Color4f& color) noexcept;
	void SetImage(const std::filesystem::path&) noexcept;

	Graphics::Vertices* GetVertices() const noexcept;
	Graphics::material* GetMaterial() const noexcept;

	const Graphics::Color4f& GetColor() const noexcept;
	const std::string& GetImagePath() const noexcept;
	unsigned int GetTextureHandle() const noexcept;
	unsigned int* GetRefTextureHandle() noexcept;
	
	bool IsAnimated() const noexcept;
	void SetIsAnimated(bool is_animated) noexcept;

	int GetFrame() const noexcept;
	void SetFrame(int frame) noexcept;

	float GetSpeed() const noexcept;
	void SetSpeed(float speed) noexcept;

private:
	void SendIndex() const noexcept;

	std::shared_ptr<Graphics::Mesh> mesh;
	std::shared_ptr<Graphics::Vertices> vertices;
	std::shared_ptr<Graphics::material> material;
	std::shared_ptr<Graphics::Texture> texture;
	std::string imageFilePath;

	bool isAnimated;
	int frame;
	float speed;
	float index;
};