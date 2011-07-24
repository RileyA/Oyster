#include <iostream>
#include "../include/Oyster.h"

// simple usage example, makes a GUI and saves the resulting mesh data to a wavefront .obj file
int main(int argc, char** argv)
{
	// TODO...
	Oyster::Oyster* oyster = new Oyster::Oyster(1024,768);

	oyster->createAtlas("atlas1", "example.cpp");
	Oyster::Batch* b = oyster->createBatch("batch1", "atlas1");

	b->createLayer(1)->createRectangle(0, 0, 50, 50);
	b->update();
	b->update();

	// save a simple .obj
	std::ofstream out;
	out.open("out.obj");

	const Oyster::Mesh& m = b->getMesh();

	for(int i = 0; i < m.vertices.size(); i+=3)
	{
		out<<"v "<<m.vertices[i]<<" "
			<<m.vertices[i+1]<<" "<<m.vertices[i+2]<<"\n";
	}

	for(int i = 0; i < m.indices.size(); i+=3)
	{
		out<<"f "<<m.indices[i]+1<<" "<<m.indices[i+1]+1
			<<" "<<m.indices[i+2]+1<<"\n";
	}

	delete oyster;
	return 0;
}
