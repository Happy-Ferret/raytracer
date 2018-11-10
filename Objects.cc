#include <cmath>

#include "Objects.h"


SceneObject::SceneObject() {}


Sphere::Sphere(Vec3f origin, float radius)
: SceneObject()
, mOrigin(origin)
, mRadius(radius)
{}


bool Sphere::intersect(Vec3f rayOrigin, Vec3f rayDirection, Vec3f &intersection, Vec3f &normal) {
    Vec3f raySphereSegment = subtract(mOrigin, rayOrigin);
    // This is the length of the projection of the ray-sphere line segment
    // onto the ray.
    float raySphereProjectionNorm = dot(raySphereSegment, rayDirection);
    if (raySphereProjectionNorm < 0) {
        return false;
    }

    float discriminant = (
        dot(raySphereSegment, raySphereSegment) -
        raySphereProjectionNorm * raySphereProjectionNorm
    );
    float radiusSq = mRadius * mRadius;
    if (discriminant > radiusSq) {
        return false;
    }

    float circleDelta = sqrt(radiusSq - discriminant);
    Vec3f intersectionA = subtract(raySphereSegment, circleDelta);
    Vec3f intersectionB = add(raySphereSegment, circleDelta);
    float normA = dot(intersectionA, intersectionA);
    float normB = dot(intersectionB, intersectionB);
    if (normA < normB && normA > 0) {
        intersection = intersectionA;
    } else if (normB > 0) {
        intersection = intersectionB;
    } else {
        return false;
    }

    normal = normalize(subtract(intersection, mOrigin));

    return true;
}
