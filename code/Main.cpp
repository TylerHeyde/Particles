#include <SFML/Graphics.hpp>
#include <iostream>
#include "Engine.h"
#include "Matrices.h"
#include "Particle.h"



using namespace sf;

using namespace std;




int main()
{
	srand(time(0));
	// Declare an instance of Engine
	Engine engine;
	// Start the engine
	engine.run();
	// Quit in the usual way when the engine is stopped
	return 0;
}