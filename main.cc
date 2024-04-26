//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "rtweekend.h"

#include "camera.h"
#include "constant_medium.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "quad.h"
#include "sphere.h"


int main() {
    hittable_list world;

    auto red   = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(15, 15, 15));

    auto earth_texture = make_shared<image_texture>("ground.jpg");
    auto earth_surface = make_shared<lambertian>(earth_texture);

    auto water_texture = make_shared<image_texture>("water.jpg");
    auto water_surface = make_shared<lambertian>(water_texture);

    auto fogo_texture = make_shared<image_texture>("fogo.jpg");
    auto fogo_surface = make_shared<lambertian>(fogo_texture);

    // Cornell box sides
    world.add(make_shared<quad>(point3(555,0,0), vec3(0,0,555), vec3(0,555,0), green));
    //world.add(make_shared<quad>(point3(0,0,555), vec3(0,0,-555), vec3(0,555,0), red));
    //world.add(make_shared<quad>(point3(0,555,0), vec3(555,0,0), vec3(0,0,555), white)); //Teto
    world.add(make_shared<quad>(point3(0,0,555), vec3(555,0,0), vec3(0,0,-555), white)); //Chao
    world.add(make_shared<quad>(point3(555,0,555), vec3(-555,0,0), vec3(0,555,0), white)); //Fundo

    // Light
    world.add(make_shared<quad>(point3(213,554,227), vec3(130,0,0), vec3(0,0,105), light));

    // Box
    shared_ptr<hittable> box1 = box(point3(0,165,0), point3(165,330,165), water_surface);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265,50,295));
    world.add(box1);

    

    // Box
    shared_ptr<hittable> box2 = box(point3(0,0,0), point3(200,200,200), earth_surface);
    //box2 = make_shared<rotate_y>(box2, 15);
    box2 = make_shared<translate>(box2, vec3(300,0,100));
    world.add(box2);

    // Glass Sphere
    auto glass = make_shared<dielectric>(1.5);
    //world.add(make_shared<sphere>(point3(190,90,190), 90, glass));
    world.add(make_shared<sphere>(point3(190,90,250), 50, glass));
    world.add(make_shared<sphere>(point3(190,250,100), 50, fogo_surface));
    world.add(make_shared<sphere>(point3(190,90,400), 25, red));



    // Light Sources
    hittable_list lights;
    auto m = shared_ptr<material>();
    lights.add(make_shared<quad>(point3(343,554,332), vec3(-130,0,0), vec3(0,0,-105), m));
    lights.add(make_shared<sphere>(point3(190, 90, 190), 90, m));

    camera cam;

    cam.aspect_ratio      = 1.0;
    cam.image_width       = 600;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background        = color(0,0,0);

    cam.vfov     = 40;
    cam.lookfrom = point3(278, 278, -800);
    cam.lookat   = point3(278, 278, 0);
    cam.vup      = vec3(0, 1, 0);

    cam.defocus_angle = 0;
//____________________________________________
    camera cam1;

    cam1.aspect_ratio      = 1.0;
    cam1.image_width       = 600;
    cam1.samples_per_pixel = 100;
    cam1.max_depth         = 50;
    cam1.background        = color(0,0,0);

    cam1.vfov     = 40;
    cam1.lookfrom = point3(-800,278,278);
    cam1.lookat   = point3(190,278,278);
    cam1.vup      = vec3(0, 1, 0);

    cam1.defocus_angle = 0;

//____________________________________________
    camera cam2;

    cam2.aspect_ratio      = 1.0;
    cam2.image_width       = 600;
    cam2.samples_per_pixel = 100;
    cam2.max_depth         = 50;
    cam2.background        = color(0,0,0);

    cam2.vfov     = 40;
    cam2.lookfrom = point3(1500, 278, 278);
    cam2.lookat   = point3(278, 278, 278);
    cam2.vup      = vec3(0, 1, 0);

    cam2.defocus_angle = 0;

//____________________________________________
    camera cam3;

    cam3.aspect_ratio      = 1.0;
    cam3.image_width       = 600;
    cam3.samples_per_pixel = 100;
    cam3.max_depth         = 50;
    cam3.background        = color(0,0,0);

    cam3.vfov     = 40;
    cam3.lookfrom = point3(278, 278, 1400);
    cam3.lookat   = point3(278, 278, 278);
    cam3.vup      = vec3(0, 1, 0);

    cam3.defocus_angle = 0;

//____________________________________________
    camera cam4;

    cam4.aspect_ratio      = 1.0;
    cam4.image_width       = 600;
    cam4.samples_per_pixel = 100;
    cam4.max_depth         = 50;
    cam4.background        = color(0,0,0);

    cam4.vfov     = 40;
    cam4.lookfrom = point3(-800, 800, -800);
    cam4.lookat   = point3(278, 278, 278);
    cam4.vup      = vec3(0, 1, 0);

    cam4.defocus_angle = 0;

    cam4.render(world, lights);
}
