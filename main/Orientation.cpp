#include <NewPing.h>

#define maxDistance 30

int getDistance(int trigPin, int echoPin, int surveys) {

    NewPing sonar(trigPin, echoPin, maxDistance);
    int total = 0;

    for (int i = 0; i < surveys; i++) {

        total += sonar.ping_cm();
        delay(5);

    }

    return total/surveys;

}

char getOrientation(int trigPin1,  int trigPin2, int echoPin1, int echoPin2, int surveys) {

    int distance1 = getDistance(trigPin1, echoPin1, surveys); //right side
    int distance2 = getDistance(trigPin2, echoPin2, surveys); //left side

    if (distance1 > 11) {
        return 'a';
    }

    else if (distance2 >= 9) {
        return 'c';
    }

    else {
        return 'b';
    }

}
