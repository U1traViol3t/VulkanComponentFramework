#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene0.h"
#include "MMath.h"
#include "Debug.h"
#include "VulkanRenderer.h"
Scene0::Scene0(Renderer *renderer_): Scene(nullptr), renderer(renderer_), camera(nullptr) {
	camera = new Camera();
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}
Scene0::~Scene0() {
	if (camera) delete camera;
}
bool Scene0::OnCreate() {
	int width, height;
	float aspectRatio;
	switch (renderer->getRendererType()){
	case RendererType::VULKAN:
		SDL_GetWindowSize(dynamic_cast<VulkanRenderer*>(renderer)->GetWindow(), &width, &height);
		aspectRatio = static_cast<float>(width) / static_cast<float>(height);
		camera->Perspective(45.0f, aspectRatio, 0.5f, 20.0f);
		camera->setPosition(Vec3(0.0f, 0.0f, -5.0f));
		camera->setRotation(0.0f, Vec3(0.0f, 1.0f, 0.0f));
		lightPos[0] = Vec4(-5.0, 0.0, -4.0, 1.0f);
		lightPos[1] = Vec4(5.0, 0.0, -4.0, 1.0f);
		break;
	case RendererType::OPENGL:
		break;
	}
	return true;
}
void Scene0::HandleEvents(const SDL_Event &sdlEvent) {
	if (sdlEvent.type == SDL_WINDOWEVENT) {
		switch (sdlEvent.window.event) {
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			printf("size changed %d %d\n", sdlEvent.window.data1, sdlEvent.window.data2);
			float aspectRatio = static_cast<float>(sdlEvent.window.data1) / static_cast<float>(sdlEvent.window.data2);
			camera->Perspective(45.0f, aspectRatio, 0.5f, 20.0f);
			break;
		}
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
		VulkanRenderer* vRenderer;
		vRenderer = dynamic_cast<VulkanRenderer*>(renderer);
		vRenderer->setUBO(camera->getProjectionMatrix(), camera->getViewMatrix(), mariosModelMatrix, lightPos);
		vRenderer->Render();
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