// #pragma once
// ////////////////////////////////////////////////////////////
// // Headers
// ////////////////////////////////////////////////////////////
// #include <SFML/Config.hpp>
// #include <SFML/Window/Context.hpp>
// #include <SFML/Window/ContextSettings.hpp>
// #include <SFML/Window/GlResource.hpp>
// #include <SFML/System/NonCopyable.hpp>



// class GlContext
// {
// private:
//     const unsigned int iID; ///< Unique number that identifies the context
//     void initialize(const ContextSettings& requestedSettings);
//     void checkSettings(const ContextSettings& requestedSettings);


// protected:
//     GlContext();
//     virtual bool makeCurrent(bool current) = 0;
//     void cleanupUnsharedResources();

//     static int evaluateFormat(unsigned int bitsPerPixel, const ContextSettings& settings, int colorBits, int depthBits, int stencilBits, int antialiasing, bool accelerated, bool sRgb);
//     ContextSettings m_settings; ///< Creation settings of the context


// public:
//     static void initResource();
//     static void cleanupResource();
//     static void registerContextDestroyCallback(ContextDestroyCallback callback, void* arg);
//     static void acquireTransientContext();
//     static void releaseTransientContext();

//     static GlContext* create();
//     static GlContext* create(const ContextSettings& settings, const WindowImpl* owner, unsigned int bitsPerPixel);
//     static GlContext* create(const ContextSettings& settings, unsigned int width, unsigned int height);

//     static bool isExtensionAvailable(const char* name);
//     static GlFunctionPointer getFunction(const char* name);
//     static unsigned int getActiveContextId();

//     virtual ~GlContext();

//     const ContextSettings& getSettings() const;
//     bool setActive(bool active);

//     virtual void display() = 0;
//     virtual void setVerticalSyncEnabled(bool enabled) = 0;
// };
