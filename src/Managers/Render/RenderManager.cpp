#include "RenderManager.h"

RenderManager::RenderManager(std::weak_ptr<Window> window)
{
	engineWindow = window;

	shaderStore = CompileShaders();

	uniformStore = std::make_shared<UniformStore>();
	uniformStore->Set("uPerspectiveProjection", {});
	uniformStore->Set("uOrthographicProjection", {});

	if (std::shared_ptr<Window> sharedWin = engineWindow.lock())
	{
		windowSize = sharedWin->GetSize();

		glm::mat4 perspectiveProj = glm::perspective(45.0f, ((float)windowSize.first, (float)windowSize.second), 0.1f, 100.0f);
		glm::mat4 orthographicProj = glm::ortho(0.0f, (float)windowSize.first, (float)windowSize.second, 0.0f);

		uniformStore->Set("uPerspectiveProjection", perspectiveProj);
		uniformStore->Set("uOrthographicProjection", orthographicProj);
	}

}

RenderManager::~RenderManager()
{

}

void RenderManager::DrawObjects()
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

			glm::mat4 perspectiveProj = glm::perspective(45.0f, ((float)windowSize.first, (float)windowSize.second), 0.1f, 100.0f);
			glm::mat4 orthographicProj = glm::ortho(0.0f, (float)windowSize.first, (float)windowSize.second, 0.0f);

			uniformStore->Set("uPerspectiveProjection", perspectiveProj);
			uniformStore->Set("uOrthographicProjection", orthographicProj);
		}
	}

	//std::cout << (*uniformStore->Get<glm::mat4>("uOrthographicProjection"))[0][0] << std::endl; //test

	// for each gameobject
	{
		// if !object.TryGetComponent<Renderer>() continue
		{
			//Renderer objectRenderComponent = object.TryGetComponent<Renderer>();

			/*auto model = modelStore->Get<Model>(objectRenderComponent.GetModelName();
			if (!model)
			{
				modelStore->Set(objectRenderComponent.GetModelName(), Model(objectRenderComponent.GetModelName()));
				model = modelStore->Get<Model>(objectRenderComponent.GetModelName();
			}
			glBindVertexArray(model.ID());*/

			// texure shenanigans (bind texture)
			// set generic uniforms (position, scale, rotation, texture etc)


			/// DEFAULT SHADER

			// activate shader 
			glUseProgram(shaderStore->Get<Shader>("default")->ID());

			// for each uniform (x) in default shader
			for (std::string x : shaderStore->Get<Shader>("default")->GetUniformList())
			{
				auto* value = uniformStore->Get(x);
				if (!value) continue;

				std::visit([&](const auto& uniform)
				{
					using T = std::decay_t<decltype(uniform)>;
					if constexpr (!std::is_same_v<T, std::monostate>)
					{
						shaderStore->Get<Shader>("default")->SetUniform(x, uniform);
					}
				}, *value);
			}
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

/*
Models and Textures

Assets/Models/

Assets/Textures/

Each have their own loaders, and set into separate stores (ModelStore, TextureStore, yada yada,)
When it comes to initializing the renderer component in a object, take two args: model name and texture name (I'll do the same concept as the shader compiling and use the name of the directory as the key)

Issue is, we don't want to compile all of the models like we do with the shaders.
Instead of compiling every model at runtime do a check to see if the model has already been compiled:

object.AddComponent<Renderer>("TestModel", "TestTexture")
modelKEY = object.TryGetComponent<Renderer>().GetModelName;
if ModelStore[modelKEY] exists
{
  Use existing, compiled model
}
else
{
  Load model //can worry about optimization later
}

Instead of using the FILE NAME as the key, we'll use the FOLDER NAME as the key instead.
Obviously same concept as before, just a little different where:

Model::LoadModel(string name)
{
path = "assets/models/" + name + "/" + name + ".obj"
}

*/