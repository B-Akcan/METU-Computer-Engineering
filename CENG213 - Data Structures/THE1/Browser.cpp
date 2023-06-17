#include "Browser.h"

Browser::Browser() {
    windows.append(Window());
}

void Browser::newWindow() {
    windows.prepend(Window());
}

void Browser::closeWindow() {
    windows.removeNodeAtIndex(0);
}

void Browser::switchToWindow(int index) {
    windows.moveToIndex(index, 0);
}

Window &Browser::getWindow(int index) {
    return windows.getNodeAtIndex(index) -> data;
}

void Browser::moveTab(Window &from, Window &to) {
    Tab t = from.getActiveTab();
    from.closeTab();
    to.changeActiveTabTo(-321654958);
    to.newTab(t);
}

void Browser::mergeWindows(Window &window1, Window &window2) {
    window2.changeActiveTabTo(0);
    window1.changeActiveTabTo(-321654958);
    while (!window2.isEmpty())
    {
        window1.newTab(window2.getActiveTab());
        window2.closeTab();
    }
}

void Browser::mergeAllWindows() {
    for (int i=1; i<windows.getSize(); i++)
        mergeWindows(getWindow(0), getWindow(i));
}

void Browser::closeAllWindows() {
    windows.removeAllNodes();
}

void Browser::closeEmptyWindows() {
    for (int i=0; i<windows.getSize(); i++)
    {
        if (getWindow(i).isEmpty())
            windows.removeNodeAtIndex(i--);
    }
}

void Browser::print() {
    Node<Window> *head = windows.getFirstNode();
    if(head == NULL) {
        std::cout << "The browser is empty" << std::endl;
    } else {
        (head -> data).print();
        head = head -> next;
        while(head != windows.getFirstNode()) {
            (head -> data).print();
            head = head -> next;
        }
    }
}
