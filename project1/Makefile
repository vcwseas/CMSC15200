evidence_vec: vec.c evidence_vec.c
	gcc -Wall -Wextra -o evidence_vec evidence_vec.c vec.c
evidence_rgb: rgb.c evidence_rgb.c
	gcc -Wall -Wextra -o evidence_rgb	evidence_rgb.c rgb.c
evidence_ray: ray.c evidence_ray.c
	gcc -Wall -Wextra -o evidence_ray evidence_ray.c ray.c vec.c
evidence_sphere: sphere.c  evidence_sphere.c
	gcc -Wall -Wextra -o evidence_sphere evidence_sphere.c vec.c rgb.c sphere.c
evidence_sl: sphere_list.c evidence_sl.c
	gcc -Wall -Wextra -o evidence_sl evidence_sl.c vec.c rgb.c sphere.c sphere_list.c
evidence_light: evidence_light.c light.c
	gcc -Wall -Wextra -o evidence_light evidence_light.c vec.c rgb.c light.c
evidence_scene: evidence_scene.c scene.c
	gcc -Wall -Wextra -o evidence_scene evidence_scene.c vec.c rgb.c light.c scene.c sphere_list.c sphere.c
evidence_hit_test: evidence_hit_test.c hit_test.c
	gcc -Wall -Wextra -o evidence_hit_test evidence_hit_test.c hit_test.c rgb.c vec.c
evidence_camera: evidence_camera.c camera.c
	gcc -Wall -Wextra -o evidence_camera evidence_camera.c vec.c camera.c
evidence_stage: evidence_stage.c stage.c
	gcc -Wall -Wextra -o evidence_stage evidence_stage.c vec.c camera.c stage.c rgb.c scene.c sphere_list.c sphere.c light.c
evidence_raytracer: evidence_raytracer.c raytracer.c
	gcc -Wall -Wextra -o evidence_raytracer evidence_raytracer.c raytracer.c vec.c camera.c
raytracer: raytracer.c
	gcc -Wall -Wextra -o trace raytracer.c hit_test.c ray.c light.c rgb.c scene.c sphere.c sphere_list.c stage.c vec.c camera.c -lm

