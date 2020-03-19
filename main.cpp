#include "Renderer.hpp"
#include "Scene.hpp"
#include "Triangle.hpp"
#include "Vector.hpp"
#include "global.hpp"

#include "Rect.hpp"
#include "Sphere.hpp"

#include <chrono>

// In the main function of the program, we create the scene (create objects and
// lights) as well as set the options for the render (image width and height,
// maximum recursion depth, field-of-view, etc.). We then call the render
// function().
int main(int argc, char** argv)
{
    Scene scene(1280, 960);

	// Red right wall
	Rect_yz rect1(0, 555, 0, 555, 555);
	rect1.m->m_color = Vector3f(0.65, 0.05, 0.05);
	rect1.m->Kd = 0.6;
	rect1.m->Ks = 0;
	rect1.m->specularExponent = 0;
	scene.Add(&rect1);

	// Green left wall
	Rect_yz rect2(0, 555, 0, 555, 0);
	rect2.m->m_color = Vector3f(0.12, 0.45, 0.15);
	rect2.m->Kd = 0.6;
	rect2.m->Ks = 0;
	rect2.m->specularExponent = 0;
	scene.Add(&rect2);

	// Light
	Rect_xz rect3(213, 343, 227, 332, 555);
	rect3.m->m_color = Vector3f(1, 1, 1);
	rect3.m->Kd = 0.6;
	rect3.m->Ks = 1;
	rect3.m->specularExponent = 0;
	scene.Add(&rect3);
	scene.Add(std::make_unique<AreaLight>(Vector3f(213, 554, 227), 1, 130, 105));
	// scene.Add(std::make_unique<Light>(Vector3f(278, 554, 279.5), 1));
	scene.Add(std::make_unique<AreaLight>(Vector3f(213, 277.5, 227), 1, 130, 105));
	// scene.Add(std::make_unique<Light>(Vector3f(277.5, 277.5, 277.5), 1));

	// White floor
	Rect_xz rect4(0, 555, 0, 555, 0);
	rect4.m->m_color = Vector3f(0.73, 0.73, 0.73);
	rect4.m->Kd = 0.6;
	rect4.m->Ks = 0;
	rect4.m->specularExponent = 0;
	scene.Add(&rect4);

	// White back wall
	Rect_xy rect5(0, 555, 0, 555, 0);
	rect5.m->m_color = Vector3f(0.73, 0.73, 0.73);
	rect5.m->Kd = 0.6;
	rect5.m->Ks = 0;
	rect5.m->specularExponent = 0;
	scene.Add(&rect5);

	// White ceiling
	Rect_xz rect6(0, 555, 0, 555, 555);
	rect6.m->m_color = Vector3f(0.73, 0.73, 0.73);
	rect6.m->Kd = 0.6;
	rect6.m->Ks = 0;
	rect6.m->specularExponent = 0;
	scene.Add(&rect6);

	// Sphere sph(Vector3f(277.5, 100, 277.5), 100);
	// sph.m->m_type = REFLECTION_AND_REFRACTION;
	// sph.m->ior = 1.8;
	// scene.Add(&sph);



    // MeshTriangle bunny("../models/bunny/bunny.obj");

    // scene.Add(&bunny);
    // scene.Add(std::make_unique<Light>(Vector3f(-20, 70, 20), 1));
    // scene.Add(std::make_unique<Light>(Vector3f(20, 70, 20), 1));
    scene.buildBVH();

    Renderer r;

    auto start = std::chrono::system_clock::now();
    r.Render(scene);
    auto stop = std::chrono::system_clock::now();

    std::cout << "Render complete: \n";
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << " hours\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() << " minutes\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << " seconds\n";

    return 0;
}