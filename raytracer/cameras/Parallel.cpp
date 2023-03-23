#include "Parallel.hpp"

Parallel::Parallel():dir(Vector3D(0, 0, -1)){}

Parallel::Parallel(float c){
	this->dir = Vector3D(c, c, c);
	this->dir.normalize();
}

Parallel::Parallel(float x, float y, float z){
	this->dir = Vector3D(x, y, z);
	this->dir.normalize();
}

Parallel::Parallel(const Vector3D &d){
	this->dir = d;
	this->dir.normalize();
}

Parallel::Parallel(const Parallel &camera){
	this->dir = camera.dir;
}


Vector3D Parallel::get_direction(const Point3D &p) const
{
	return this->dir;
}