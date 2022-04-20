#include "Essentials/Window.h"
#include <gum-gui.h>
#include <GUI/Basics/Tabs.h>
#include <GUI/Basics/Slider.h>
#include <GUI/Basics/Switch.h>
#include <GUI/Basics/Scroller.h>
#include <GUI/XMLGUILoader.h>

#include <iostream>

int main(int argc, char** argv)
{
    Gum::Window* pContextWindow = new Gum::Window(false, "GUI Example", ivec2(75, 75), true);
    GumGUI* pGUI = new GumGUI(pContextWindow);

    GUIWindow *testWindow = new GUIWindow(ivec2(10,10), ivec2(500, 500), "TestWindow", true);
    testWindow->setTitle("LongTitleeeeeeeeeeeee");

    Tabs *pTabs = new Tabs(ivec2(0,0), ivec2(100, 100), ivec2(100, 30));
    pTabs->setSizeInPercent(true, true);
    pTabs->addTab("Tab1");
    pTabs->addTab("Tab2", true);
    pTabs->addTab("Tab3");
    testWindow->addGUI(pTabs);


	Box* pPositionMapBox = new Box(vec2(25, 25), vec2(50, 50), 0);
    //pPositionMapBox->setTexture(GumEngine::Textures->getTexture("Cobblestone/ao.png"));
    pPositionMapBox->setSizeInPercent(true, true);
    pPositionMapBox->setPositionInPercent(true, true);
    pTabs->addGUIToTab(pPositionMapBox, "Tab1");

    Scroller* testScroller = new Scroller(ivec2(0, 0), ivec2(100, 100));
    testScroller->setSizeInPercent(true, true);

    Slider* testSlider = new Slider(ivec2(5, 50), 90, "pos");
    testSlider->setSizeInPercent(true, false);
    testSlider->setPositionInPercent(true, false);
    testScroller->addGUI(testSlider);


    Switch* testSwitch = new Switch(ivec2(10, -10), ivec2(20, 20), 10);
    testScroller->addGUI(testSwitch);

    Switch* testSwitch1 = new Switch(ivec2(10, 1000), ivec2(20, 20), 10);
    testScroller->addGUI(testSwitch1);


	Box* pStupid = new Box(vec2(25, 350), vec2(50, 50), 0);
    //pStupid->setTexture(GumEngine::Textures->getTexture("boii.jpg"));
    pStupid->setSizeInPercent(true, true);
    pStupid->setPositionInPercent(true, false);
    testScroller->addGUI(pStupid);

    pTabs->addGUIToTab(testScroller, "Tab2");

    pGUI->addWindow(testWindow);


    //XML Test
    /*GUIWindow *pXMLTestWindow = new GUIWindow(ivec2(520,20), ivec2(500, 500), "XMLTest", true);
    XMLGUILoader *pXMLGUILoader = new XMLGUILoader(GumGlobals::GUI_ASSETS_PATH + "/examplegui.xml");
    pXMLTestWindow->addGUI(pXMLGUILoader->getGUI());
    pGUI->addWindow(pXMLTestWindow);*/
}