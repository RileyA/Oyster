#include <iostream>
#include "../include/Oyster.h"

// simple usage example, makes a GUI and saves the resulting mesh data to a wavefront .obj file
int main(int argc, char** argv)
{
	// TODO...
	Oyster::Oyster* oyster = new Oyster::Oyster();

	oyster->createAtlas("atlas1", "example.cpp");
	Oyster::Batch* b = oyster->createBatch("batch1", "atlas1");

	b->createRectangle(0, 0, 50, 50);

	delete oyster;
	return 0;
}
