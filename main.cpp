#include "Renderer.hpp"
#include "Scene.hpp"
#include "Triangle.hpp"
#include "Vector.hpp"
#include "global.hpp"

#include "Rect.hpp"

#include <chrono>

// In the main function of the program, we create the scene (create objects and
// lights) as well as set the options for the render (image width and height,
// maximum recursion depth, field-of-view, etc.). We then call the render
// function().
int main(int argc, char** argv)
{
    Scene scene(1280, 960);

    MeshTriangle bunny("../models/bunny/bunny.obj");

    // Rect_xy rect(3, 8, 2, 12, 2);
    // rect.m->m_type = REFLECTION_AND_REFRACTION;
    // rect.m->m_color = Vector3f(255, 0, 0);
    // rect.m->m_emission = Vector3f(1, 2, 100);
    // scene.Add(&rect);


	// Green right wall
	Rect_yz rect1(0, 555, 0, 555, 555);
	// rect1.m->m_type = REFLECTION_AND_REFRACTION;
	// rect1.m->m_color = Vector3f(0.12, 0.45, 0.15);
	rect1.m->m_color = Vector3f(0, 1, 0);
	// rect1.m->m_emission = Vector3f(1, 2, 100);
	scene.Add(&rect1);

	// Red left wall
	Rect_yz rect2(0, 555, 0, 555, 0);
	// rect2.m->m_type = REFLECTION_AND_REFRACTION;
	rect2.m->m_color = Vector3f(0.65, 0.05, 0.05);
	// rect2.m->m_emission = Vector3f(1, 2, 100);
	scene.Add(&rect2);

	// Light
	Rect_xz rect3(213, 343, 227, 332, 554);
	// rect3.m->m_type = REFLECTION_AND_REFRACTION;
	rect3.m->m_color = Vector3f(1, 1, 1);
	// rect3.m->m_emission = Vector3f(1, 2, 100);
	scene.Add(&rect3);
	// scene.Add(std::make_unique<AreaLight>(Vector3f(278, 554 - 1, 279.5), 1, 130, 105));
	scene.Add(std::make_unique<Light>(Vector3f(278, 554 - 1, 279.5), 1));

	// White floor
	Rect_xz rect4(0, 555, 0, 555, 0);
	// rect4.m->m_type = REFLECTION_AND_REFRACTION;
	rect4.m->m_color = Vector3f(0.73, 0.73, 0.73);
	// rect4.m->m_emission = Vector3f(1, 2, 100);
	scene.Add(&rect4);

	// White back wall
	Rect_xy rect5(0, 555, 0, 555, 0);
	// rect5.m->m_type = REFLECTION_AND_REFRACTION;
	rect5.m->m_color = Vector3f(0.73, 0.73, 0.73);
	// rect5.m->m_emission = Vector3f(1, 2, 100);
	scene.Add(&rect5);




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