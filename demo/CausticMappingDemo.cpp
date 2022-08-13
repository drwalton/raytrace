#include <glue/FullScreenQuad.hpp>
#include <glue/GLWindow.hpp>
#include <glue/Texture.hpp>
#include <glue/ShaderProgram.hpp>
#include <glue/Directories.hpp>
#include "raytrace/Scene.hpp"
#include "raytrace/Sphere.hpp"
#include "raytrace/Plane.hpp"
#include "raytrace/Shaders.hpp"
#include "raytrace/PhotonShaders.hpp"
#include "raytrace/CameraModelPinhole.hpp"
#include "raytrace/RandGen.hpp"

#include <array>
#include <Eigen/Dense>
#include <iostream>

const size_t WIDTH = 640;
const size_t HEIGHT = 480;
float FOV = 1.f;

int main(int argc, char *argv[])
{
	glue::GLWindow win("Raytraced Scene", WIDTH, HEIGHT);
	std::unique_ptr<std::array<float, 640 * 480 * 3>> imData(new std::array<float, 640 * 480 * 3>());
	glue::Texture imTex(GL_TEXTURE_2D, GL_RGB, 640, 480, 0, GL_RGB, GL_FLOAT, imData->data());
	glue::ShaderProgram fullScreenTexShader(std::vector<std::string>{
		glue::GLUE_SHADER_DIR + "FullScreenTex.vert",
		glue::GLUE_SHADER_DIR + "FullScreenTex.frag"
	});

	Scene scene;

	//TODO replace with photon mapping shader.
	scene.objectList.emplace_back(new Plane(glue::vec3(0, 0, 1), 1));
	scene.objectList.back()->materialShader = diffuseHardShadowedShaderCaustics;
	scene.objectList.back()->photonShaderCaustic = absorbPhotonShader;
	scene.objectList.back()->color = glue::vec3(0.f, 1.f, 0.f);
	scene.objectList.emplace_back(new Plane(glue::vec3(0, 0, -1), 1));
	scene.objectList.back()->materialShader = diffuseHardShadowedShaderCaustics;
	scene.objectList.back()->photonShaderCaustic = absorbPhotonShader;
	scene.objectList.back()->color = glue::vec3(0.f, 1.f, 1.f);
	scene.objectList.emplace_back(new Plane(glue::vec3(0, 1, 0), 1));
	scene.objectList.back()->materialShader = diffuseHardShadowedShaderCaustics;
	scene.objectList.back()->photonShaderCaustic = absorbPhotonShader;
	scene.objectList.back()->color = glue::vec3(1.f, 1.f, 0.f);
	scene.objectList.emplace_back(new Plane(glue::vec3(0, -1, 0), 1));
	scene.objectList.back()->materialShader = diffuseHardShadowedShaderCaustics;
	scene.objectList.back()->photonShaderCaustic = absorbPhotonShader;
	scene.objectList.back()->color = glue::vec3(1.f, 0.f, 0.f);
	scene.objectList.emplace_back(new Plane(glue::vec3(1, 0, 0), 1));
	scene.objectList.back()->materialShader = diffuseHardShadowedShaderCaustics;
	scene.objectList.back()->photonShaderCaustic = absorbPhotonShader;
	scene.objectList.back()->color = glue::vec3(0.f, 0.f, 1.f);
	scene.objectList.emplace_back(new Plane(glue::vec3(-1, 0, 0), 1));
	scene.objectList.back()->materialShader = diffuseHardShadowedShaderCaustics;
	scene.objectList.back()->photonShaderCaustic = absorbPhotonShader;
	scene.objectList.back()->color = glue::vec3(1.f, 0.f, 1.f);


	scene.objectList.emplace_back(new Sphere(glue::vec3(0.f, -.5f, -.5), 0.25f));
	scene.objectList.back()->materialShader = refractShader;
	scene.objectList.back()->photonShaderCaustic = perfectRefractPhotonShader;
	scene.objectList.back()->properties = CollisionMask(CAUSTIC_BIT);

	scene.objectList.emplace_back(new Sphere(glue::vec3(-0.5f, -.6f, -.5), 0.15f));
	scene.objectList.back()->materialShader = refractShader;
	scene.objectList.back()->photonShaderCaustic = perfectRefractPhotonShader;
	scene.objectList.back()->properties = CollisionMask(CAUSTIC_BIT);

	scene.objectList.emplace_back(new Sphere(glue::vec3(0.85f, .5f, -.5f), 0.125f));
	scene.objectList.back()->materialShader = diffuseHardShadowedShaderCaustics;
	scene.objectList.back()->photonShaderCaustic = absorbPhotonShader;

	scene.pointLightList.push_back(PointLight(glue::vec3(0, 0.9f, 0.f), glue::vec3(1, 1, 1)));
	scene.objectList.emplace_back(new Sphere(glue::vec3(0.f, 0.9f, 0.f), 0.2f));
	scene.objectList.back()->photonShaderCaustic = absorbPhotonShader;
	scene.objectList.back()->materialShader = simpleColorShader;
	scene.objectList.back()->properties = DIFFUSE_BIT;
	scene.objectList.back()->color = glue::vec3(10.f, 10.f, 10.f);

	const size_t nPhotons = 100000;
	std::default_random_engine generator;
	Photon p;
	p.ray.origin = scene.pointLightList.back().pos;
	p.power = scene.pointLightList.back().power / (nPhotons * 1000000.f);

	size_t numCastPhotons = 0;
	while (scene.causticPhotonMap.size() < nPhotons) {
		p.ray.dir = uniformRandSphere(generator);
		scene.traceCausticPhoton(p);
		++numCastPhotons;
	}
	std::cout << "Num. cast caustic photons: " << numCastPhotons << std::endl;
	std::cout << "Num. caustic photons: " << scene.causticPhotonMap.size() << std::endl;
	//TODO caustics

	glue::mat4 camPose = glue::mat4::Identity();
	camPose(2, 3) = -0.75;
	camPose(1, 3) = 0.25;
	glue::mat4 camPoseInv = camPose.inverse();
	CameraModelPinhole camModel(
		WIDTH, HEIGHT, float(WIDTH) / 2.f, float(HEIGHT) / 2.f,
		FOV * float(WIDTH) / 2.f, FOV * float(WIDTH) / 2.f);

	float maxPixelVal = 0.f;
	for (size_t x = 0; x < WIDTH; ++x) {
		for (size_t y = 0; y < HEIGHT; ++y) {
			Ray ray = camModel.imToRay(camPoseInv, x, y);
			glue::vec3 color = scene.trace(ray);
			(*(imData.get()))[x*3 + y*WIDTH*3 + 0] = color.x();
			(*(imData.get()))[x*3 + y*WIDTH*3 + 1] = color.y();
			(*(imData.get()))[x*3 + y*WIDTH*3 + 2] = color.z();

			maxPixelVal = fmaxf(color.x(), maxPixelVal);
			maxPixelVal = fmaxf(color.y(), maxPixelVal);
			maxPixelVal = fmaxf(color.z(), maxPixelVal);
		}
	}

	std::cout << "Max pixel val: " << maxPixelVal << std::endl;

	//scene.causticPhotonMap.visualize(&camModel, camPose, imData->data());

	imTex.update(imData->data());
	glue::FullScreenQuad::showTexture(&imTex, &fullScreenTexShader);
	win.swapBuffers();

	bool running = true;

	SDL_Event e;
	while (running) {
		SDL_Delay(30);
		SDL_PollEvent(&e);
		if (win.eventIsQuit(e)) {
			running = false;
		}
	}

	return 0;
}
