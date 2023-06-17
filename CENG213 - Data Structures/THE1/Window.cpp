#include "Window.h"

Window::Window() {
    this->activeTab = 0;
    tabs.append(Tab());
}

Tab Window::getActiveTab() {
    if (isEmpty())
        return Tab();
    else
        return tabs.getNodeAtIndex(activeTab)->data;
}

bool Window::isEmpty() const {
    if (tabs.getSize() == 0) return true;
    return false;
}

void Window::newTab(const Tab &tab) {
    tabs.insertAtIndex(tab, activeTab+1);
    activeTab++;
}

void Window::closeTab() {
    if (isEmpty()) return;
    tabs.removeNodeAtIndex(activeTab);
    if (isEmpty()) activeTab = -1;
    else if (activeTab >= tabs.getSize()) activeTab--;
}

void Window::moveActiveTabTo(int index) {
    if (index < 0 || activeTab == -1 || activeTab > tabs.getSize()-1 || tabs.getSize() <= 1)
        return;
    if (index >= tabs.getSize()-1 && activeTab == tabs.getSize()-1)
    	return;
    tabs.moveToIndex(activeTab, index);
    if (index < tabs.getSize())
        activeTab = index;
    else
        activeTab = tabs.getSize()-1;
}

void Window::changeActiveTabTo(int index) {
    if (index >= tabs.getSize())
        return;
    else if (index == -321654958)
        activeTab = tabs.getSize()-1;
    else if (index < 0)
        return;
    else
        activeTab = index;
}

void Window::addTab(Node<Tab> &tab) {
    if (tabs.isEmpty()) activeTab = 0;
    tabs.append(tab.data);
}

void Window::print() {
    if(tabs.isEmpty()) std::cout << "Window is empty" << std::endl;
    else std::cout << "The active tab is tab " << activeTab << std::endl;
    tabs.print();
}
