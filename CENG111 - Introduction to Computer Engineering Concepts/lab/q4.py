def healthStatus(height, mass):
	bmi=mass/(height**2)
	if bmi<18.5:
		return "underweight"
	elif bmi>=18.5 and bmi<24.9:
		return "healthy"
	elif bmi>=24.9 and bmi<30:
		return "overweight"
	elif bmi>=30:
		return "obese"
