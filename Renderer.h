/**
 * @file
 * @brief Contains the core ray tracing guts.
 */
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <utility>

#include "Scene.h"
#include "Stats.h"
#include "Vector.h"


Vec3f computeReflectionDir(Vec3f incomingRayDirection, Vec3f surfaceNormal);
Vec3f computeRefractionDir(Vec3f ray, Vec3f normal, float refractionIndex, bool &isTotalInternalReflection);
bool isInside(Vec3f rayDirection, Vec3f intersectionNormal);


enum AntiAliasingMethod {
    REGULAR,
    RANDOM
};


/**
 * Responsibilities:
 *
 *   - Rendering settings (anti-aliasing, image dimensions, etc)
 *   - Producing and writing an image
 *   - Creating RenderThread instances
 */
class Renderer {
    private:
        /// Maintain a queue of render jobs to be performed.
        std::queue<std::pair<int, int>> mWorkQueue;
        /// Prevent interference between threads on the work queue.
        std::mutex mQueueLock;
        /// Track the number of rows completed by the render threads for the progress bar.
        int mCompletedRows;
        /// The final image is ultimately just an array of color vectors.
        Vec3f *mImage;

    public:
        Scene &mScene;
        int mWidth;
        int mHeight;
        /// Number of rendering iterations to run and average.
        int mNoiseReduction;
        int mMaxDepth;
        /// Must be a square number.
        int mAntiAliasing;
        AntiAliasingMethod mAntiAliasingMethod;
        bool mEnableSoftShadows;
        int mNumThreads;
        std::string mOutputFile;

        Renderer(Scene &scene);
        ~Renderer();
        bool getWork(int &start, int &end);
        void printProgress();
        void printIntro(std::string file);

        void render();
        void gl();
};


/**
 * Responsibilities:
 *
 *   - Rendering a portion of the image in a std::thread
 *   - Keeping statistics on a rendering
 *   - Ray tracing engine
 *
 * It'd be nice to further decouple this.
 */
class RenderThread {
    private:
        void computePrimaryRay(int x, int y, float xS, float yS, Vec3f &direction, Vec3f &origin);
        Vec3f renderPixel(int x, int y);
        Vec3f trace(Vec3f origin, Vec3f ray, int depth);
        Vec3f computePixelAverage(int x, int y);
        void computeAntiAliasingSample(int samples, int x, int y, float &xS, float &yS);

    public:
        Renderer *mRenderer;
        Stats mStats;
        float mAspectRatio;
        float mFovRatio;
        std::shared_ptr<std::thread> mThread;

        RenderThread(Renderer *renderer, float aspectRatio, float fovRatio);
        void run(Vec3f *image, const int id);
        void render(Vec3f *image, const int id);
        void join();
};


#endif
