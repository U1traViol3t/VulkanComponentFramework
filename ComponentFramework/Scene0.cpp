#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene0.h"
#include "MMath.h"
#include "Debug.h"
#include "VulkanRenderer.h"

Scene0::Scene0(Renderer *renderer_): Scene(nullptr), renderer(renderer_), camera(nullptr) {
	//SDL_GetWindowSize(window, &width, &height);
	camera = new Camera(45.0f, 1.777777779f, 0.1f, 20.0f);
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene0::~Scene0() {
	if (camera) delete camera;
}

bool Scene0::OnCreate() {
	
	switch (renderer->getRendererType()){
	case RendererType::VULKAN:
		renderer->Render();
		break;

	case RendererType::OPENGL:
		break;
	}

	return true;
}

void Scene0::HandleEvents(const SDL_Event &sdlEvent) {
	if (sdlEvent.type == SDL_WINDOWEVENT_RESIZED) {
		std::cout << "resized\n";
		}
}

void Scene0::Update(const float deltaTime) {
	static float totalTime = 0.0f;
	totalTime += deltaTime;
	mariosModelMatrix = MMath::rotate(totalTime * 90.0f, Vec3(0.0f, 1.0f, 0.0f));
}

void Scene0::Render() const {
	switch (renderer->getRendererType()) {
	case RendererType::VULKAN:
		dynamic_cast<VulkanRenderer*>(renderer)->setUBO(camera->getProjectionMatrix(), camera->getViewMatrix(), mariosModelMatrix);
		renderer->Render();
		break;

	case RendererType::OPENGL:
		/// Clear the screen
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		/// Draw your scene here
		
		
		glUseProgram(0);
		
		break;
	}
}


void Scene0::OnDestroy() {}
