#ifndef COREENGINE_H
#define COREENGINE_H

#include <string>
#include "Profiling.h"
#include "../Rendering/RenderingEngine.h"

class Game;

class CoreEngine
{
private:
	bool m_isRunning;
	int m_width;
	int m_height;
	double m_frameRate;
	Game* m_game;
	RenderingEngine* m_renderingEngine;
	Window* m_window;
	const Camera* m_mainCamera;

	ProfileTimer m_windowUpdateTimer;
	ProfileTimer m_swapBufferTimer;
	ProfileTimer m_sleepTimer;

	void run();

	void operator =(const CoreEngine& coreEgine) {};

public:
	CoreEngine(int width, int height, double frameRate, Game* game);
	virtual ~CoreEngine();

	void createWindow(const std::string& title);

	void start();
	void stop();

	RenderingEngine* getRenderingEngine();

	void setCamera(const Camera& camera);
};

#endif