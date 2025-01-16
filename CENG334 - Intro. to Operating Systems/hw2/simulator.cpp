#include <iostream>
#include <vector>
#include <string>
#include "WriteOutput.h"
#include "helper.h"
#include "monitor.h"
#include <queue>

using namespace std;

// Enum definitions
typedef enum PassingLane2
{
	DIRECTION_0_1 = 0,
	DIRECTION_1_0 = 1,
} PassingLane2;

typedef enum PassingLane4
{
	DIRECTION_0 = 0,
	DIRECTION_1 = 1,
	DIRECTION_2 = 2,
	DIRECTION_3 = 3,
} PassingLane4;

// Struct definitions
typedef struct Direction
{
	int from;
	int to;
} Direction;

typedef struct RoadConnector
{
	char connector_type;
	int connector_id;
	Direction direction;
} RoadConnector;

// Class declarations
class Car;
class NarrowBridge;
class Ferry;
class Crossroad;

// Function declarations
void take_input(int &N_N, int &F_N, int &C_N, int &CA_N, vector<NarrowBridge> &narrow_bridges, vector<Ferry> &ferries, vector<Crossroad> &crossroads, vector<Car> &cars);
void *drive(void *args);
struct timespec calculateTimeToWait(int time_in_ms);

// Class definitions
class Car
{
	private:
		int id;
		int travel_time;
		int path_length;
		vector<RoadConnector> path;

	public:
		Car()
		{}

		Car(int id_, int travel_time_, int path_length_, vector<RoadConnector> path_)
		{
			id = id_;
			travel_time = travel_time_;
			path_length = path_length_;
			path = path_;
		}

		int get_id()
		{
			return id;
		}

		int get_travel_time()
		{
			return travel_time;
		}

		int get_path_length()
		{
			return path_length;
		}

		vector<RoadConnector> get_path()
		{
			return path;
		}

		bool operator== (Car const& obj)
		{
			return this->id == obj.id;
		}
};

class NarrowBridge : Monitor
{
	private:
		int id;
		int travel_time;
		int maximum_wait_time;
		PassingLane2 current_passing_lane;
		bool car_passing;
		queue<int> queue_from;
		queue<int> queue_to;

		Condition cv_from, cv_to, cv0, cv1, cv2;
		struct timespec t;
		int x;

	public:
		NarrowBridge(int id_, int travel_time_, int maximum_wait_time_) : cv_from(this), cv_to(this), cv0(this), cv1(this), cv2(this)
		{
			id = id_;
			travel_time = travel_time_;
			maximum_wait_time = maximum_wait_time_;

			current_passing_lane = DIRECTION_0_1;
			car_passing = false;
		}

		void switch_passing_lane()
		{
			current_passing_lane = (PassingLane2) ((int) current_passing_lane + 1 % 2);
			car_passing = false;
		}

		bool isQueueEmpty()
		{
			if (current_passing_lane == DIRECTION_0_1)
				return queue_from.empty();
			else
				return queue_to.empty();
		}

		void addCarToQueue(int carID)
		{
			if (current_passing_lane == DIRECTION_0_1)
				queue_from.push(carID);
			else
				queue_to.push(carID);
		}

		int removeCarFromQueue()
		{
			if (current_passing_lane == DIRECTION_0_1)
			{
				int carID = queue_from.front();
				queue_from.pop();
				return carID;
			}
			else
			{
				int carID = queue_to.front();
				queue_to.pop();
				return carID;
			}
		}

		int getFrontOfQueue()
		{
			if (current_passing_lane == DIRECTION_0_1)
				return queue_from.front();
			else
				return queue_to.front();
		}

		int getSizeOfQueue()
		{
			if (current_passing_lane == DIRECTION_0_1)
				return queue_from.size();
			else
				return queue_to.size();
		}
		
		void pass(PassingLane2 direction, int carID)
		{
			__synchronized__;
			
			addCarToQueue(carID);

			beginning_nb:

			if (direction == current_passing_lane)
			{
				if (getSizeOfQueue() == 1)
					goto passing_first;

				if (car_passing)
				{
					t = calculateTimeToWait(PASS_DELAY);
					if (current_passing_lane == DIRECTION_0_1)
						x = pthread_cond_timedwait(&cv_from.cond, &mut, &t);
					else
						x = pthread_cond_timedwait(&cv_to.cond, &mut, &t);

					if (x == ETIMEDOUT)
					{
						car_passing = false;
						goto beginning_nb;
					}
				}


				if (getFrontOfQueue() == carID)
				{
					removeCarFromQueue();

					passing:

					car_passing = true;

					t = calculateTimeToWait(PASS_DELAY);
					x = pthread_cond_timedwait(&cv0.cond, &mut, &t);
					
					passing_first:

					WriteOutput(carID, 'N', id, START_PASSING);

					if (current_passing_lane == DIRECTION_0_1)
						cv_from.notify();
					else
						cv_to.notify();

					t = calculateTimeToWait(travel_time);
					x = pthread_cond_timedwait(&cv1.cond, &mut, &t);

					WriteOutput(carID, 'N', id, FINISH_PASSING);

					if (getSizeOfQueue() == 0)
					{
						car_passing = false;

						switch_passing_lane();
						if (current_passing_lane == DIRECTION_0_1)
							cv_from.notifyAll();
						else
							cv_to.notifyAll();
					}
				}

				else
				{
					removeCarFromQueue();
					addCarToQueue(carID);

					goto beginning_nb;
				}

			}

			else if (isQueueEmpty())
			{
				switch_passing_lane();
				if (current_passing_lane == DIRECTION_0_1)
					cv_from.notifyAll();
				else
					cv_to.notifyAll();

				goto beginning_nb;
			}

			else
			{
				t = calculateTimeToWait(maximum_wait_time);
				if (direction == DIRECTION_0_1)
					x = pthread_cond_timedwait(&cv_from.cond, &mut, &t);
				else
					x = pthread_cond_timedwait(&cv_to.cond, &mut, &t);

				if (x == ETIMEDOUT)
				{
					switch_passing_lane();
					if (current_passing_lane == DIRECTION_0_1)
						cv_from.notifyAll();
					else
						cv_to.notifyAll();

					goto passing_first;
				}

				else
					goto passing;
			}
		}

};

class Ferry : public Monitor
{
	private:
		int id;
		int travel_time;
		int maximum_wait_time;
		int capacity;
		int num_cars0;
		int num_cars1;
		struct timespec t;
		int x;

		Condition cv0, cv1, cv2, cv3;

	public:
		Ferry(int id_, int travel_time_, int maximum_wait_time_, int capacity_) : cv0(this), cv1(this), cv2(this), cv3(this)
		{
			id = id_;
			travel_time = travel_time_;
			maximum_wait_time = maximum_wait_time_;
			capacity = capacity_;

			num_cars0 = 0;
			num_cars1 = 0;
		}

		void pass(PassingLane2 direction, int carID)
		{
			__synchronized__;

			if (direction == DIRECTION_0_1)
			{
				num_cars0++;

				if (num_cars0 < capacity)
				{
					t = calculateTimeToWait(maximum_wait_time);
					x = pthread_cond_timedwait(&cv0.cond, &mut, &t);

					if (x == ETIMEDOUT)
					{
						cv0.notifyAll();
						num_cars0 = 0;
					}
				}

				else
				{
					cv0.notifyAll();
					num_cars0 = 0;
				}

				WriteOutput(carID, 'F', id, START_PASSING);
				t = calculateTimeToWait(travel_time);
				x = pthread_cond_timedwait(&cv2.cond, &mut, &t);
				WriteOutput(carID, 'F', id, FINISH_PASSING);
			}

			else
			{
				num_cars1++;

				if (num_cars1 < capacity)
				{
					t = calculateTimeToWait(maximum_wait_time);
					x = pthread_cond_timedwait(&cv1.cond, &mut, &t);

					if (x == ETIMEDOUT)
					{
						cv1.notifyAll();
						num_cars1 = 0;
					}
				}

				else
				{
					cv1.notifyAll();
					num_cars1 = 0;
				}

				WriteOutput(carID, 'F', id, START_PASSING);
				t = calculateTimeToWait(travel_time);
				x = pthread_cond_timedwait(&cv3.cond, &mut, &t);
				WriteOutput(carID, 'F', id, FINISH_PASSING);
			}
		}
};

class Crossroad : Monitor
{
	private:
		int id;
		int travel_time;
		int maximum_wait_time;
		Condition cv0, cv1, cv2, cv3, tmp0, tmp1;
		PassingLane4 current_passing_lane;
		queue<int> queue0, queue1, queue2, queue3;
		bool car_passing;
		struct timespec t;
		int x;

	public:
		Crossroad(int id_, int travel_time_, int maximum_wait_time_) : cv0(this), cv1(this), cv2(this), cv3(this), tmp0(this), tmp1(this)
		{
			id = id_;
			travel_time = travel_time_;
			maximum_wait_time = maximum_wait_time_;

			current_passing_lane = DIRECTION_0;
			car_passing = false;
		}

		void switch_passing_lane()
		{
			current_passing_lane = (PassingLane4) ((int) current_passing_lane + 1 % 4);
			car_passing = false;
		}

		bool isQueueEmpty()
		{
			switch (current_passing_lane)
			{
				case DIRECTION_0: return queue0.empty();
				case DIRECTION_1: return queue1.empty();
				case DIRECTION_2: return queue2.empty();
				case DIRECTION_3: return queue3.empty();
			}
			return NULL;
		}

		void addCarToQueue(int carID)
		{
			switch (current_passing_lane)
			{
				case DIRECTION_0: queue0.push(carID); break;
				case DIRECTION_1: queue1.push(carID); break;
				case DIRECTION_2: queue2.push(carID); break;
				case DIRECTION_3: queue3.push(carID); break;
			}
		}

		int removeCarFromQueue()
		{
			switch (current_passing_lane)
			{
				case DIRECTION_0:
				{
					int carID = queue0.front();
					queue0.pop();
					return carID;
				}
				case DIRECTION_1:
				{
					int carID = queue1.front();
					queue1.pop();
					return carID;
				}
				case DIRECTION_2:
				{
					int carID = queue2.front();
					queue2.pop();
					return carID;
				}
				case DIRECTION_3:
				{
					int carID = queue3.front();
					queue3.pop();
					return carID;
				}
			}
			return -1;
		}

		int getFrontOfQueue()
		{
			switch (current_passing_lane)
			{
				case DIRECTION_0: return queue0.front();
				case DIRECTION_1: return queue1.front();
				case DIRECTION_2: return queue2.front();
				case DIRECTION_3: return queue3.front();
			}
			return -1;
		}

		int getSizeOfQueue()
		{
			switch (current_passing_lane)
			{
				case DIRECTION_0: return queue0.size();
				case DIRECTION_1: return queue1.size();
				case DIRECTION_2: return queue2.size();
				case DIRECTION_3: return queue3.size();
			}
			return -1;
		}

		void pass(PassingLane4 direction, int carID)
		{
			__synchronized__;
			
			addCarToQueue(carID);

			beginning_c:

			if (direction == current_passing_lane)
			{
				if (getSizeOfQueue() == 1)
					goto passing_first_c;

				if (car_passing)
				{
					t = calculateTimeToWait(PASS_DELAY);
					switch (current_passing_lane)
					{
						case DIRECTION_0: x = pthread_cond_timedwait(&cv0.cond, &mut, &t); break;
						case DIRECTION_1: x = pthread_cond_timedwait(&cv1.cond, &mut, &t); break;
						case DIRECTION_2: x = pthread_cond_timedwait(&cv2.cond, &mut, &t); break;
						case DIRECTION_3: x = pthread_cond_timedwait(&cv3.cond, &mut, &t); break;
					}

					if (x == ETIMEDOUT)
					{
						car_passing = false;
						goto beginning_c;
					}
				}

				if (getFrontOfQueue() == carID)
				{
					removeCarFromQueue();

					passing_c:

					car_passing = true;

					t = calculateTimeToWait(PASS_DELAY);
					x = pthread_cond_timedwait(&tmp0.cond, &mut, &t);
					
					passing_first_c:

					WriteOutput(carID, 'C', id, START_PASSING);

					switch (current_passing_lane)
					{
						case DIRECTION_0: cv0.notify(); break;
						case DIRECTION_1: cv1.notify(); break;
						case DIRECTION_2: cv2.notify(); break;
						case DIRECTION_3: cv3.notify(); break;
					}

					t = calculateTimeToWait(travel_time);
					x = pthread_cond_timedwait(&tmp1.cond, &mut, &t);

					WriteOutput(carID, 'C', id, FINISH_PASSING);

					if (getSizeOfQueue() == 0)
					{
						car_passing = false;

						switch_passing_lane();
						switch (current_passing_lane)
						{
							case DIRECTION_0: cv0.notifyAll(); break;
							case DIRECTION_1: cv1.notifyAll(); break;
							case DIRECTION_2: cv2.notifyAll(); break;
							case DIRECTION_3: cv3.notifyAll(); break;
						}
					}
				}

				else
				{
					removeCarFromQueue();
					addCarToQueue(carID);

					goto beginning_c;
				}

			}

			else if (isQueueEmpty())
			{
				switch_passing_lane();
				switch (current_passing_lane)
				{
					case DIRECTION_0: cv0.notifyAll(); break;
					case DIRECTION_1: cv1.notifyAll(); break;
					case DIRECTION_2: cv2.notifyAll(); break;
					case DIRECTION_3: cv3.notifyAll(); break;
				}

				goto beginning_c;
			}

			else
			{
				t = calculateTimeToWait(maximum_wait_time);
				switch (direction)
				{
					case DIRECTION_0: x = pthread_cond_timedwait(&cv0.cond, &mut, &t); break;
					case DIRECTION_1: x = pthread_cond_timedwait(&cv1.cond, &mut, &t); break;
					case DIRECTION_2: x = pthread_cond_timedwait(&cv2.cond, &mut, &t); break;
					case DIRECTION_3: x = pthread_cond_timedwait(&cv3.cond, &mut, &t); break;
				}

				if (x == ETIMEDOUT)
				{
					switch_passing_lane();
					switch (current_passing_lane)
					{
						case DIRECTION_0: cv0.notifyAll(); break;
						case DIRECTION_1: cv1.notifyAll(); break;
						case DIRECTION_2: cv2.notifyAll(); break;
						case DIRECTION_3: cv3.notifyAll(); break;
					}
					goto passing_first_c;
				}

				else
					goto passing_c;
			}
		}
};

// Global variables
vector<NarrowBridge> narrow_bridges;
vector<Ferry> ferries;
vector<Crossroad> crossroads;
vector<Car> cars;

int main()
{
	int N_N, F_N, C_N, CA_N;
	take_input(N_N, F_N, C_N, CA_N, narrow_bridges, ferries, crossroads, cars);

	InitWriteOutput();

	pthread_t tids[CA_N];
	for (int i=0; i<CA_N; i++)
		pthread_create(&tids[i], NULL, &drive, (void*) &cars[i]);

	for (int i=0; i<CA_N; i++)
		pthread_join(tids[i], NULL);

	return 0;
}

void take_input(int &N_N, int &F_N, int &C_N, int &CA_N, vector<NarrowBridge> &narrow_bridges, vector<Ferry> &ferries, vector<Crossroad> &crossroads, vector<Car> &cars)
{
	cin >> N_N;
	for (int i = 0; i < N_N; i++)
	{
		int N_T, N_M;
		cin >> N_T >> N_M;
		
		NarrowBridge nb({i, N_T, N_M});
		narrow_bridges.push_back(nb);
	}
	
	cin >> F_N;
	for (int i = 0; i < F_N; i++)
	{
		int F_T, F_M, F_C;
		cin >> F_T >> F_M >> F_C;

		Ferry f({i, F_T, F_M, F_C});
		ferries.push_back(f);
	}
	
	cin >> C_N;
	for (int i = 0; i < C_N; i++)
	{
		int C_T, C_M;
		cin >> C_T >> C_M;

		Crossroad cr({i, C_T, C_M});
		crossroads.push_back(cr);
	}
	
	cin >> CA_N;
	for (int i = 0; i < CA_N; i++)
	{
		int CA_T, CA_P;
		cin >> CA_T >> CA_P;
		
		vector<RoadConnector> path;
		for (int j = 0; j < CA_P; j++)
		{
			char P_CM_type;
			int P_CM_id;
			int F_CM, T_CM;
			cin >> P_CM_type >> P_CM_id >> F_CM >> T_CM;
			
			Direction d = {F_CM, T_CM};
			RoadConnector rc = {P_CM_type, P_CM_id, d};
			path.push_back(rc);
		}
		
		Car c({i, CA_T, CA_P, path});
		cars.push_back(c);
	}
}

void *drive(void *args)
{
	Car *car = (Car*) args;

	int path_length = car->get_path_length();
	vector<RoadConnector> path = car->get_path();
	int carID = car->get_id();
	int travel_time = car->get_travel_time();

	for (int i=0; i<path_length; i++)
	{
		int current_connector_id = path[i].connector_id;
		char current_connector_type = path[i].connector_type;
		Direction direction = path[i].direction;
		
		WriteOutput(carID, current_connector_type, current_connector_id, TRAVEL);
		sleep_milli(travel_time);
		WriteOutput(carID, current_connector_type, current_connector_id, ARRIVE);

		switch (current_connector_type)
		{
			case 'N':
			{
				narrow_bridges[current_connector_id].pass((PassingLane2) direction.from, carID);
				break;
			}
			case 'F':
			{
				ferries[current_connector_id].pass((PassingLane2) direction.from, carID);
				break;
			}
			case 'C':
			{
				crossroads[current_connector_id].pass((PassingLane4) direction.from, carID);
				break;
			}
		}
	}

	return NULL;
}

struct timespec calculateTimeToWait(int time_in_ms)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	struct timespec t;
	t.tv_sec = current_time.tv_sec + time_in_ms / 1000;
	t.tv_nsec = current_time.tv_usec * 1000 + (time_in_ms % 1000) * 1000000;

	if (t.tv_nsec > 1000000000)
	{
		t.tv_sec++;
		t.tv_nsec %= 1000000000;
	}

	return t;
}




