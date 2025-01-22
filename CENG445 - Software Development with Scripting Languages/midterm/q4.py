import threading as th
import time
import random

class GameRoom:
    def __init__(self):
        self.nempty = 4
        self.ninside = 0

        self.mutex = th.RLock()
        self.can_enter = th.Condition(self.mutex)
        self.can_start = th.Condition(self.mutex)

    def enter(self, name):
        with self.mutex:

            while self.ninside > 0:
                self.can_enter.wait()
            
            print(f"{name} entered")

            self.nempty -= 1
            if self.nempty == 0:
                self.can_start.notify_all()

            while self.nempty > 0:
                self.can_start.wait()

            print(f"{name} started playing")
            self.ninside += 1
            

    def exit(self, name):
        with self.mutex:

            self.ninside -= 1

            print(f"{name} exitted")

            if self.ninside == 0:
                self.nempty = 4
                self.can_enter.notify_all()


def player(room,name):
	time.sleep(random.random()/100)
	room.enter(name)
	time.sleep(random.random()/100)
	room.exit(name)

gr = GameRoom()

t = []
for i in range(52):
	t.append(th.Thread(target=player, args=(gr, str(i))))

for tr in t:
	tr.start()

for tr in t:
	tr.join()