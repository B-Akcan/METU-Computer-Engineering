class Course {	// private not used just for simplicity
    Integer code;       // course code
    String subject;     // subject area
    String instructor;  // instructor's name
    Integer units;      // number of units/chapters
    Double duration;     // total duration in minutes
    Double price;        // price in USD
    Integer trainees;   // number of trainees
    Course(int c, String s, String i, int u, double d, double p, int t) {
        code=c;         subject=s;
	    instructor=i;	units=u;
        duration=d;     price=p;        
        trainees=t;
    }
}