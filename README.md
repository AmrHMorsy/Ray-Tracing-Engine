# Raytracer

Advanced Raytracer application, developed in C++, that utilizes OpenMP for parallel computing to enhance performance. The project features global illumination, motion blur, depth of field, soft shadows and Phong Local Illumination. 

![cornell_box_](https://github.com/AmrHMorsy/Raytracer-/assets/56271967/0ff224f0-9637-4f56-9a25-273a2a581e37)

## Features

### OpenMP Parallelization

This project incorporates OpenMP (Open Multi-Processing), a parallel programming model for shared-memory multiprocessor architectures, to achieve faster performance. By distributing computations across multiple CPU cores, the application can render complex scenes more quickly and efficiently.

### Motion Blur

A feature that adds cinematic qualities to the rendered scenes, the motion blur function simulates the photographic phenomenon where fast-moving objects appear blurred along the direction of relative motion.

### Global Illumination 

By emulating how light interplays with objects within a scene, the global illumination feature provides richer and more lifelike visual outputs. It models the details of how light bounces around an environment and scatters in various directions, capturing the subtle nuances of natural light and shade.

![TripleB](https://github.com/AmrHMorsy/Raytracer-/assets/56271967/7a8be9a4-eb5d-49a2-8570-50b5362e4ebb)

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
  
