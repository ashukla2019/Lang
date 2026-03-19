class Student:
    school_name = "ABC School"        # CLASS VARIABLE

    def __init__(self, name, marks):
        self.name = name              # INSTANCE VARIABLE
        self.marks = marks            # INSTANCE VARIABLE

    # INSTANCE METHOD
    def display(self):
        print("Name:", self.name)
        print("Marks:", self.marks)

    # INSTANCE METHOD
    def passed(self):
        return f"{self.name} passed" if self.marks >= 50 else f"{self.name} failed"

    # CLASS METHOD
    @classmethod
    def get_school_name(cls):
        return cls.school_name

    # STATIC METHOD
    @staticmethod
    def grade_from_marks(marks):
        if marks >= 90:
            return "A"
        elif marks >= 75:
            return "B"
        elif marks >= 50:
            return "C"
        else:
            return "F"

    # ----------------------
    # FUNCTION OVERLOADING
    # ----------------------
    #Python, however, is dynamically typed, and functions are resolved at runtime.
    #When you define a function twice with the same name:
    # Python uses *args to simulate method overloading:
    def show_info(self, *args):
        if len(args) == 0:
            print(f"Student: {self.name}")
        elif len(args) == 1:
            print(f"Student: {self.name}, Marks: {self.marks}, Extra: {args[0]}")
        else:
            print("Too many arguments!")


# --------------------------------
#      CHILD CLASS (INHERITANCE)
# --------------------------------
class CollegeStudent(Student):

    def __init__(self, name, marks, year):
        super().__init__(name, marks)  
        self.year = year            

    # ----------------------
    # FUNCTION OVERRIDING
    # ----------------------
    def display(self):
        # This replaces the parent's display() method
        print("=== College Student Info ===")
        print("Name:", self.name)
        print("Marks:", self.marks)
        print("Year:", self.year)


# ----------------------------
#   USING EVERYTHING
# ----------------------------

# Parent object
s1 = Student("John", 85)

# Child object
cs1 = CollegeStudent("Bob", 92, 2)

# ----------------------------
# Overriding Demo
# ----------------------------
print("\n--- Parent display() ---")
s1.display()

print("\n--- Overridden display() in Child ---")
cs1.display()   # child version runs, not parent version

# ----------------------------
# Overloading Demo
# ----------------------------
print("\n--- Method Overloading (simulated) ---")
s1.show_info()                # no arguments
s1.show_info("Batch A")       # one argument
s1.show_info("X", "Y")        # too many arguments


# ----------------------------
# Inherited Methods
# ----------------------------
print("\n--- Inherited Methods ---")
print(cs1.passed())
print(CollegeStudent.get_school_name())
print(CollegeStudent.grade_from_marks(cs1.marks))
