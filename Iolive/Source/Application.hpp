#pragma once

#include <thread>

namespace Iolive {
	class Application
	{
	public:
		static Application* Get()
		{
			static Application* staticApplication = nullptr;
			if (!staticApplication)
				staticApplication = new Application();

			return staticApplication;
		}

		static void Release()
		{
			delete Application::Get();
		}

		void Run();

	private:
		Application();
		~Application();

		void OnUpdate();
		void OnRender();

		static void OnFrameResizedCallback(int width, int height);
		static void OnScrollCallback(double xoffset, double yoffset);

		/* 
		* TODO: Capturing new frame until flags_StopCapture is true
		*/
		void FaceCaptureLoop();
		
		bool OpenCamera();
		void CloseCamera();

	private:
		std::thread faceCaptureThread; // face capturing thread

		// just a flags
		bool flags_StopCapture;
	};
}