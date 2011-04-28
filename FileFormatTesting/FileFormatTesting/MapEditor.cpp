#include "MapEditor.h"

sf::RenderWindow* MapEditor::windowInst = NULL;

MapEditor::MapEditor()
{
	mWindow = new sf::RenderWindow(sf::VideoMode(800, 800), "SenTile Map Editor");

	mainPanel.SetSize(300, 300);
	mainPanel.SetPosition(30, 30);
	mainPanel.SetColor(sf::Color(120, 120, 120));
	
	testButton.SetBGColor(sf::Color(255, 255, 255));
	testButton.SetPosition(20, 20);
	testButton.SetSize(100, 100);
	testButton.SetInputHandler(&MapEditor::CloseWindow);

	mainPanel.AddComponent(testButton);
	
	SetWindowInstance(mWindow);
}

void MapEditor::Run()
{
	while (mWindow->IsOpened())
	{
		sf::Event event;
		while (mWindow->GetEvent(event))
		{
			if (event.Type == sf::Event::Closed)
				mWindow->Close();
		}

		mainPanel.UpdateComponents();	

		// Draw block
		mWindow->Clear(sf::Color(220, 220, 220));
		mWindow->Draw(mainPanel);
		mWindow->Display();
	}
}

int MapEditor::CloseWindow(const sf::Input& input, SenGUI::Component* caller)
{
	SenGUI::Button* button = (SenGUI::Button*)caller;

	if (input.IsMouseButtonDown(sf::Mouse::Button::Left) && 
		button->IsClicked(input.GetMouseX(), input.GetMouseY()))
	{
		SenGUI::PanelBase *parent = caller->GetParent();
		if (parent == NULL)
			return -1;
		parent->SetVisible(false);
	}

	return 0;
}