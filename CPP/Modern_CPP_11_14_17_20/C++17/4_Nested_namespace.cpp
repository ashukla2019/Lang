/*
Nested Namespaces:
	Namespaces are a very convenient tool to organize and to structure the code base,
	putting together components like classes and functions that logically belong to the
	same group.
*/

####Before C++17: Below is the syntax for using the nested namespace

namespace Game {

	namespace Graphics {

		namespace Physics {

		class 2D {
			..........
		};
		}
	}
}

###When C++17:

// Below is the syntax to use the
// nested namespace in one line

namespace Game::Graphics::Physics {

	class 2D {
	..........
	};
}




