# Raytracer

This is an advanced Raytracer application, developed in C++, that utilizes OpenMP for parallel computing to enhance performance. The project features motion blur, global illumination, and depth of field, designed to encapsulate and illustrate the intricate processes of rendering photorealistic images from 3D models and scenes, effectively demonstrating the power and capabilities of computer graphics programming.

![cornell_box_](https://github.com/AmrHMorsy/Raytracer-/assets/56271967/0ff224f0-9637-4f56-9a25-273a2a581e37)

## Features

### OpenMP Parallelization

This project incorporates OpenMP (Open Multi-Processing), a parallel programming model for shared-memory multiprocessor architectures, to achieve faster performance. By distributing computations across multiple CPU cores, the application can render complex scenes more quickly and efficiently.

### Motion Blur

A feature that adds cinematic qualities to the rendered scenes, the motion blur function simulates the photographic phenomenon where fast-moving objects appear blurred along the direction of relative motion.

### Global Illumination 

By emulating how light interplays with objects within a scene, the global illumination feature provides richer and more lifelike visual outputs. It models the details of how light bounces around an environment and scatters in various directions, capturing the subtle nuances of natural light and shade.

### Depth of Field

This attribute allows for the simulation of the lens focus effect seen in real-world cameras. By adjusting the depth of field, users can emphasize specific subjects in the scene while artistically blurring other elements, creating a strikingly realistic and depth-perceptive visualization.

### Soft Shadows 

The Soft Shadows feature simulates the effect of shadows when light is obstructed by objects in the scene. The 'soft' refers to the non-uniform, irregular shape of the shadows, which contribute to the realistic rendering of scenes by simulating the scattering and diffraction of light.


### Phong Local Illumination

The Phong Local Illumination model calculates the color of an object based on its diffuse, specular, and ambient color, as well as the light present in the scene. This feature contributes to more accurate and visually pleasing renderings by considering the local properties of the objects and the lighting conditions.

![jumping_ball](https://github.com/AmrHMorsy/Raytracer-/assets/56271967/548bd100-d515-401c-880d-fe52c0427db0)

## Installation

1. Clone the repository:
```
git clone https://github.com/AmrHMorsy/Raytracer-.git
```
2. Navigate to the project directory: 
```
cd raytracer
```
3. Create a build directory: 
```
mkdir build
```
4. Navigate to the build directory: 
```
cd build
```
5. Generate makefiles using cmake: 
```
cmake ../
```
6. compile using makefile: 
```
make
```
7. Run the program: 
```
./raytracer <Model_Filepath>.json
```
  
![TripleB](https://github.com/AmrHMorsy/Raytracer-/assets/56271967/7a8be9a4-eb5d-49a2-8570-50b5362e4ebb)

## Future Work

- **Glossy Reflection:** Introduce a more physically accurate reflection model that can simulate the subtle blurry reflections seen on surfaces like brushed metal and wet floors. This will enhance realism by accounting for microsurface details.
  
- **BVH (Bounding Volume Hierarchy):** Improve the ray tracing performance by implementing a BVH acceleration structure. This will allow for faster and more efficient intersection tests by grouping objects and discarding non-relevant intersections early in the tracing process.
  
- **Procedural Texturing:** Allow for more dynamic and versatile texturing options by implementing procedural texture generation. This can be used to create patterns like wood grain, marble, and noise-based textures without relying on image-based sources.

- **Transparency and Caustics:** Enhance the realism by supporting transparency and simulating the focused light patterns (caustics) produced when light passes through transparent objects. This will make the depiction of glass, water, and other transparent materials more realistic.

- **Ambient Occlusion:** Add ambient occlusion to simulate the soft global illumination shadows that occur in crevices and corners where light is occluded. This provides a greater depth and realism to scenes by accounting for subtle shadowing effects.

- **Switch to Eigen:** Transition to the Eigen library for all matrix and vector computations. This should offer a more efficient and robust system for handling the linear algebra operations necessary for ray tracing.

- **Add more scenes:** Expand the portfolio of test scenes to showcase the capabilities of the ray tracer. This could include complex indoor environments, outdoor landscapes, and scenes with a variety of materials and lighting setups.

- **Fix Pixel Sampling:** for Antialiasing and shadow sampling for area lights: Refine the sampling techniques to reduce jagged edges and achieve smoother shadows. Implementing a more advanced antialiasing method and increasing shadow sampling for area lights will ensure a higher-quality render.

## Contribution

This project is open to contributions. If you have suggestions or improvements, feel free to fork the project, make your changes, and open a pull request.

## License

This project is licensed under the terms of the MIT license. For more information, see the LICENSE file.

## Acknowledgments

This project has been a product of continuous learning and inspiration, made possible by a multitude of invaluable resources.

A significant acknowledgement goes to the Ray Tracing in One Weekend series https://raytracing.github.io. This resource has provided the fundamental knowledge and understanding needed to bring this project to life. Its comprehensive and accessible approach to explaining the concept of ray tracing has been instrumental in the development of this application.

I would also like to express my gratitude to the course COMP 371 - Computer Graphics at Concordia University. The theoretical framework and practical exercises provided throughout the course have immensely contributed to my understanding and skills in computer graphics, which have been vital in developing this project. The guidance from the faculty and the comprehensive curriculum helped transform a complex subject into a manageable and fascinating one.

Last but not least, I am indebted to the open-source community for consistently providing resources, inspiration, and a platform to learn, create, and share. Your contributions to my journey in computer graphics are immensely appreciated.
