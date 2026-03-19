Subclass objects should be replaceable for base class objects without breaking the program.


class Bird {
    public:
        virtual void fly() = 0;
};

class Crow : public Bird {
    public:
        void fly() override {
            cout << "Crow is flying" << endl;
        }
};

class Penguin : public Bird {
    public:
        void fly() override {
            throw runtime_error("Penguins can't fly");
        }
};        
In the above example, we have a class called Bird which is a abstract class having a pure virtual
function called fly() 

We also have two subclasses Crow and Penguin that is inheriting Bird class. Since Penguins can’t
fly the method fly() is throwing runtime_error. 

Problem in above approach
Now let’s say we have a function that takes a Bird object and calls its fly() function.

void makeBirdFly(const Bird& bird) {
    bird.fly();
}        
If we call this method with Crow object, it will work as expected but if we call this method 
with Penguin object, it will throw a run time error. This violates the Liskov Substitution 
Principle because substituting an Penguin for a Bird results in unexpected behavior.
