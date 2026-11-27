#include "RenderManager.h"

RenderManager::RenderManager(std::weak_ptr<Window> window)
{
	engineWindow = window;

	shaderStore = CompileShaders();

	modelStore = std::make_shared<ModelStore>();

	textureStore = std::make_shared<TextureStore>();

	uniformStore = std::make_shared<UniformStore>();
	uniformStore->Set("uPerspectiveProjection", {});
	uniformStore->Set("uOrthographicProjection", {});
	uniformStore->Set("uTexture", 0);

	if (std::shared_ptr<Window> sharedWin = engineWindow.lock())
	{
		windowSize = sharedWin->GetSize();

		glViewport(0, 0, windowSize.first, windowSize.second);
		const float aspectRatio = static_cast<float>(windowSize.first) / static_cast<float>(windowSize.second);
		glm::mat4 perspectiveProj = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
		glm::mat4 orthographicProj = glm::ortho(0.0f, (float)windowSize.first, (float)windowSize.second, 0.0f);

		uniformStore->Set("uPerspectiveProjection", perspectiveProj);
		uniformStore->Set("uOrthographicProjection", orthographicProj);
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

}

RenderManager::~RenderManager()
{

}

void RenderManager::DrawObjects(const std::vector<std::shared_ptr<Object>>& objects)
{
	// Clear Buffers
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Calculate Viewports in case of resize
	if (std::shared_ptr<Window> sharedWin = engineWindow.lock())
	{
		std::pair<int, int> currentSize = sharedWin->GetSize();

		if (windowSize != currentSize)
		{
			windowSize = currentSize;

			glViewport(0, 0, windowSize.first, windowSize.second);
			const float aspectRatio = static_cast<float>(windowSize.first) / static_cast<float>(windowSize.second);
			glm::mat4 perspectiveProj = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
			glm::mat4 orthographicProj = glm::ortho(0.0f, (float)windowSize.first, (float)windowSize.second, 0.0f);

			uniformStore->Set("uPerspectiveProjection", perspectiveProj);
			uniformStore->Set("uOrthographicProjection", orthographicProj);
		}
	}

	// Upload Camera related uniforms
	glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, -10.0f);
	/// NOTE - Since I don't have a camera object yet I'm manually defining the position. When making a camera object, fix this
	uniformStore->Set("uCameraPosition", glm::vec3(0.0f, 0.0f, 10.0f));

	std::vector<LightData> lights;
	lights.reserve(objects.size());
	for (const auto& obj : objects)
	{
		if (!obj) continue;
		
		auto* light = obj->TryGetComponent<Light>();
		auto* transform = obj->TryGetComponent<Transform>();
		if (!light || !transform) continue;

		lights.push_back({ *light, *transform });

	}

	for (const auto& obj : objects)
	{
		if (!obj || !obj->TryGetComponent<Renderer>()) continue;
		{
			Renderer objectRenderComponent = *obj->TryGetComponent<Renderer>();

			auto model = modelStore->Get<Model>(objectRenderComponent.modelName);
			if (!model)
			{
				modelStore->Set(objectRenderComponent.modelName, Model(objectRenderComponent.modelName));
				model = modelStore->Get<Model>(objectRenderComponent.modelName);
			}
			model->Bind();

			auto texture = textureStore->Get<Texture>(objectRenderComponent.textureName);
			if (!texture)
			{
				textureStore->Set(objectRenderComponent.textureName, Texture(objectRenderComponent.textureName));
				texture = textureStore->Get<Texture>(objectRenderComponent.textureName);
			}
			texture->Bind();
			
			// set generic uniforms (position, scale, rotation, texture etc)
			Transform objectTransform = *obj->TryGetComponent<Transform>();

			glm::mat4 transformModel = glm::mat4(1.0f);
			transformModel = glm::translate(transformModel, objectTransform.position);
			transformModel = glm::rotate(transformModel, glm::radians(objectTransform.rotation.x), glm::vec3(1, 0, 0));
			transformModel = glm::rotate(transformModel, glm::radians(objectTransform.rotation.y), glm::vec3(0, 1, 0));
			transformModel = glm::rotate(transformModel, glm::radians(objectTransform.rotation.z), glm::vec3(0, 0, 1));
			transformModel = glm::scale(transformModel, objectTransform.scale);
			uniformStore->Set("uModel", transformModel);

			glm::mat4 view = glm::translate(glm::mat4(1.0f), cameraPosition);
			uniformStore->Set("uView", view);

			/// DEFAULT SHADER
			Shader* shader = shaderStore->Get<Shader>("defaultLight");

			// activate shader 
			glUseProgram(shader->ID());
			
			// get lights that affect object
			const std::vector<const LightData*> affectingLights = GetLightsForObject(lights, objectTransform.position);

			// upload light specific information directly to shader - keeping this in uniform store is memory heavy
			const int lightCount = static_cast<int>(affectingLights.size());
			shader->SetUniform("uLightCount", lightCount);
			for (int i = 0; i < lightCount; ++i)
			{
				const LightData& data = *affectingLights[i];
				const std::string prefix = "uLights[" + std::to_string(i) + "].";

				shader->SetUniform(prefix + "position", data.transform.position);
				shader->SetUniform(prefix + "color", data.light.color);
				shader->SetUniform(prefix + "intensity", data.light.intensity);
				shader->SetUniform(prefix + "range", data.light.range);
			}

			// upload renderer specific information to uniform store
			uniformStore->Set("uBaseColor", objectRenderComponent.baseColor);
			uniformStore->Set("uSpecularColor", objectRenderComponent.specularColor);
			uniformStore->Set("uSpecularStrength", objectRenderComponent.specularStrength);
			uniformStore->Set("uShininess", objectRenderComponent.shininess);

			// for each uniform (x) in default shader
			for (std::string x : shader->GetUniformList())
			{
				auto* value = uniformStore->Get(x);
				if (!value) continue;

				std::visit([&](const auto& uniform)
				{
					using T = std::decay_t<decltype(uniform)>;
					if constexpr (!std::is_same_v<T, std::monostate>)
					{
						shader->SetUniform(x, uniform);
					}
				}, *value);
			}

			// Draw shape
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(model->GetIndexCount()), GL_UNSIGNED_INT, nullptr);

			// Reset the state
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);

			engineWindow.lock()->SwapWindow();
			glUseProgram(0);
		}
	}
}



std::shared_ptr<ShaderStore> RenderManager::CompileShaders()
{
	namespace fs = std::filesystem;

	std::shared_ptr<ShaderStore> store = std::make_shared<ShaderStore>();

	for (const auto& entry : fs::recursive_directory_iterator("assets/shaders"))
	{
		if (!entry.is_regular_file()) continue;

		const fs::path& path = entry.path();

		// Only discover vertex shaders
		if (path.extension() != ".vert") continue;

		std::string shaderName = path.stem().string();

		// Check for matching fragment shader in the same directory
		fs::path fragmentPath = path.parent_path() / (shaderName + ".frag");

		if (!fs::exists(fragmentPath))
		{
			std::cout << "Missing fragment shader for: " << shaderName << " - will not compile" << std::endl;
			continue;
		}

		// At this point, shader exists - create shader object and append it to shader store
		store->Set(shaderName, Shader(path.string(), fragmentPath.string()));
	}

	return store;
}

std::vector<const LightData*> RenderManager::GetLightsForObject(const std::vector<LightData>& lights, const glm::vec3& objectPosition) const
{
	std::vector<std::pair<float, const LightData*>> rankedLights;
	rankedLights.reserve(lights.size());

	for (const LightData& lightData : lights)
	{
		const glm::vec3 offset = lightData.transform.position - objectPosition;
		const float distanceSquared = glm::dot(offset, offset);
		const float rangeSquared = lightData.light.range * lightData.light.range;

		if (distanceSquared > rangeSquared) continue;

		const float distance = std::sqrt(distanceSquared);
		const float score = lightData.light.intensity / (1.0f + distance);

		rankedLights.emplace_back(score, &lightData);
	}

	const std::size_t selectedCount = std::min(MaxLightsPerObject, rankedLights.size());

	std::partial_sort(
		rankedLights.begin(),
		rankedLights.begin() + selectedCount,
		rankedLights.end(),
		[](const auto& a, const auto& b)
		{
			return a.first > b.first;
		});

	std::vector<const LightData*> selectedLights;
	selectedLights.reserve(selectedCount);

	for (std::size_t i = 0; i < selectedCount; ++i)
	{
		selectedLights.push_back(rankedLights[i].second);
	}

	return selectedLights;
}
