#include "Plex.h"



using namespace System;
using namespace System::Windows::Forms;

void main(array<String^>^ arg) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Lab2::Plex form;
	Application::Run(%form);
}

