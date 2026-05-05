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

	int pixelWidth = VideoMode::getDesktopMode().width/2;

	int pixelHeight = VideoMode::getDesktopMode().height/2;

	VideoMode vm(pixelWidth, pixelHeight);
	RenderWindow window(vm, "Particle", Style::Default);

	//-----reorganize this into particle and engine classes later-----//

	View cartesianPlane;
	cartesianPlane.setCenter(0, 0);
	cartesianPlane.setSize((float)pixelWidth, (float)pixelHeight);

	Vector2f center = { 0,0 };
	int numPoints = rand() % 50 + 50;
	vector<Vector2f> vertices(numPoints);
	
	float theta = ((float)rand() / RAND_MAX) * M_PI / 2.0;
	float dTheta = 2 * M_PI / (numPoints - 1);

	for (int i = 0; i < numPoints; ++i) {
		float r = rand() % 80 + 20;
		float dx = r * cos(theta);
		float dy = r * sin(theta);
		//dx and dy are the offsets from the center, so we add them to the center coordinates

		vertices[i].x = center.x + dx;
		vertices[i].y = center.y + dy;
		theta += dTheta;
		//uses trig to spin around unit circle
	}

	VertexArray particle1(TriangleFan);
	particle1.resize(numPoints + 1);

	particle1[0].color = Color::White;
	particle1[0].position = (Vector2f)window.mapCoordsToPixel(center, cartesianPlane);
	
	for (int i = 0; i < numPoints; i++)
	{
		particle1[i + 1].position = (Vector2f)window.mapCoordsToPixel(vertices[i], cartesianPlane);
		particle1[i + 1].color = Color::Blue;
	}
	//---put all this generation inside particle constructor later---//

	while (window.isOpen())

	{

		///Input
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				// Handle the player quitting
				if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}

			}

			if (event.type == Event::Closed)
			{
				window.close();
			}

			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x(pixel): " << event.mouseButton.x << std::endl;
					std::cout << "mouse y(pixel): " << event.mouseButton.y << std::endl;
					Vector2f coord = window.mapPixelToCoords({ event.mouseButton.x,event.mouseButton.y }, cartesianPlane);
					std::cout << "mouse x(coordinate): " << coord.x << std::endl;
					std::cout << "mouse y(coordinate): " << coord.y << std::endl;

				}
			}
		}
		///Update




		///Draw

		window.clear();

		window.draw(particle1);


		window.display();

	}




}