/**
 * @file
 * @brief Store objects and lights in scene, get their intersections with a
 *        ray.
 */
#ifndef _SCENE_H_
#define _SCENE_H_

#include <memory>
#include <vector>

#include "Camera.h"
#include "Objects.h"
#include "PointLight.h"


/**
 * Responsibilities:
 *
 *   - Maintaining references to the objects and lights
 */
class Scene {
    public:
        std::vector<std::shared_ptr<SceneObject>> mObjects;
        std::vector<std::shared_ptr<PointLight>> mPointLights;
        Camera mCamera;

        Scene();
        bool getIntersection(
            Vec3f origin,
            Vec3f ray,
            std::shared_ptr<SceneObject> &intersectionObject,
            float &intersectionScalar
        );
};


#endif
