import java.util.*;
import java.util.stream.*;
import java.io.*;
import java.util.function.*;

public class QueryOLP {
	public static void main(String[] args) throws FileNotFoundException {
		BufferedReader br= new BufferedReader(new InputStreamReader(new FileInputStream(new File("courses.csv"))));

		Function<String, Course> mapToCourse = (line) -> {
			String[] p = line.split(", ");
			return new Course(Integer.parseInt(p[0]), p[1], p[2], Integer.parseInt(p[3]), Double.parseDouble(p[4]), Double.parseDouble(p[5]), Integer.parseInt(p[6]));
		};
    
		List<Course> crs = br.lines().skip(1).map(mapToCourse).collect(Collectors.toList());

// Query 1: Codes of all the courses in sorted order
		System.out.println("Query 1:"); 
		crs.stream()
				.map(c -> c.code)
				.sorted()
				.forEach(System.out::println);
		System.out.println("--------"); 

// Query 2: Instructors (with no duplicates) teaching courses with price under USD 1 in sorted order
		System.out.println("Query 2:");
		crs.stream()
				.filter(c -> c.price < 1.0)
				.map(c -> c.instructor)
				.distinct()
				.sorted()
				.forEach(System.out::println);
		System.out.println("--------"); 

// Query 3: Price of the cheapest course
		Double cheapestPrice = crs.stream()
				.map(c -> c.price)
				.reduce(Double.MAX_VALUE, (c1, c2) -> c1 < c2 ? c1 : c2);

		System.out.println("Query 3:"); 
		System.out.println(cheapestPrice);
		System.out.println("--------"); 

// Query 4: Instructor of the cheapest course
		String instructor = crs.stream()
						.filter(c -> c.price.equals(cheapestPrice))
						.map(c -> c.instructor)
						.findFirst()
						.orElse(null);

		System.out.println("Query 4:"); 
		System.out.println(instructor);
		System.out.println("--------"); 

// Query 5: Sum of the durations of the courses whose number of trainees are above the average
		Double avgTrainees = crs.stream()
						.map(c -> c.trainees)
						.mapToInt(i -> i)
						.average()
						.orElse(-1);
		Double sumOfDurations = crs.stream()
						.filter(c -> c.trainees > avgTrainees)
						.map(c -> c.duration)
						.mapToDouble(d -> d)
						.sum();

		System.out.println("Query 5:"); 
		System.out.println(sumOfDurations);
		System.out.println("--------"); 

	}
}
