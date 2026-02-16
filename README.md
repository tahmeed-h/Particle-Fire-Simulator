
# Particle-Fire-Simulator
A real-time particle swarm simulation built using C++ and SDL2, demonstrating low-level pixel manipulation, dynamic memory management, time-based animation, coordinate transformations, and custom post-processing effects.

This project renders 5000 particles in real-time, applying a box blur algorithm to create a smooth trailing “fire explosion” visual effect.

Features
	•	Real-time particle system (5000 particles)
	•	Frame-rate independent motion
	•	Polar → Cartesian coordinate transformations
	•	Manual pixel buffer manipulation
	•	Custom 3×3 box blur post-processing effect
	•	Dynamic RGB colour cycling using sine functions
	•	Double buffering for smooth rendering
	•	VSync-enabled renderer

⸻

Technical Concepts Demonstrated
	•	Manual heap allocation & cleanup 
	•	Pointer safety & const correctness
	•	Double buffering & buffer swapping
	•	Bitwise colour packing (RGBA 32-bit format)
	•	Time-delta based animation
	•	Low-level pixel indexing in 1D memory
	•	Event-driven rendering loop (SDL)
	•	Performance-aware design
  

⸻
 How It Works 
	1.	Particles are initialised at the center with random direction & speed.
	2.	Positions update each frame using time-scaled motion.
	3.	Coordinates are mapped from normalized space to screen pixels.
	4.	Pixels are written directly to a raw buffer.
	5.	A box blur blends neighboring pixels to create motion trails.
	6.	The texture is updated and rendered to the window.
