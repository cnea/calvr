#include <menu/MenuSystem.h>
#include <menu/BoardMenu.h>
#include <config/ConfigManager.h>

#include <iostream>

using namespace cvr;

MenuSystem * MenuSystem::_myPtr = NULL;

MenuSystem::MenuSystem()
{
    _menu = NULL;
}

MenuSystem::~MenuSystem()
{
}

MenuSystem * MenuSystem::instance()
{
    if(!_myPtr)
    {
        _myPtr = new MenuSystem();
    }
    return _myPtr;
}

bool MenuSystem::init()
{
    _rootMenu = new SubMenu("CalVR");

    std::string menuType = ConfigManager::getEntry("type", "MenuSystem",
                                                   "BOARDMENU");
    if(menuType == "BOARDMENU")
    {
        _type = BOARDMENU;
        _menu = new BoardMenu();
    }
    else
    {
        std::cerr << "No menu of type " << menuType << std::endl;
        return false;
    }

    _menu->setMenu(_rootMenu);

    return true;
}

void MenuSystem::addMenuItem(MenuItem * item)
{
    _rootMenu->addItem(item);
}

void MenuSystem::updateStart()
{
    if(_menu)
    {
        _menu->updateStart();
    }
}

bool MenuSystem::processEvent(InteractionEvent * event)
{
    if(_menu)
    {
        return _menu->processEvent(event);
    }
    return false;
}

bool MenuSystem::processIsect(IsectInfo & isect, bool mouse)
{
    if(_menu)
    {
	return _menu->processIsect(isect,mouse);
    }
    return false;
}

void MenuSystem::updateEnd()
{
    if(_menu)
    {
	_menu->updateEnd();
    }
}

void MenuSystem::itemDelete(MenuItem * item)
{
    if(_menu)
    {
	_menu->itemDelete(item);
    }
}