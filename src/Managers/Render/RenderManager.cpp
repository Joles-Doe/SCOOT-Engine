#include "RenderManager.h"

RenderManager::RenderManager(std::weak_ptr<Window> window)
{
	engineWindow = window;

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

	std::cout << (*uniformStore->Get<glm::mat4>("uOrthographicProjection"))[0][0] << std::endl;

	// Iterate through each gameobject (how I pull them in I'll figure out)
	// Check if GameObject has renderer module
	// If true, pull necessary info from renderer module and draw using a generic shader
	// Check renderer module for additional techniques i.e. shadows. Draw those here after the first shader
}
